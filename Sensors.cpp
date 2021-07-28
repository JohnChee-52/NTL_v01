/*
 * Sensors.cpp
 * There are 6 signals that are being sensed.
 *   1. Battery voltage – mV
 *   2. Clog filter pressure – mmHg
 *   3. Backpressure – mmHg
 *   4. Chamber pressure – mmHg
 *   5. Cough pressure – mmHg
 *   6. MCU IC temperature – oCx10
 *   The sensors may be re-calibrated by updating their coefficients in the constructor
 *
 * ------------------------------------------------|
 * GPIO|Pin|Config  |MCU Control/Input lines |TIVA |
 * ------------------------------------------------|
 * PE3 |p6 |AIN0    |BatteryVoltage_PE3      |J3p9 |
 * PE2 |p7 |AIN1    |ClogPressure_PE2        |J3p8 |
 * PB4 |p58|AIN10   |BackPressure_PB4        |J1p7 |
 * PE5 |p60|AIN8    |ChamberPressure_PE5     |J1p6 |
 * PE0 |p9 |AIN3    |CoughPressure_PE0       |J2p3 |
 * -   |-  |TS      |MCU_Temperature_TS      |-    |
 * ------------------------------------------------|
 *
 * Calibration:
 *  Typically done at 2 pressures: 0 mmHg (Atmospheric), 40 mmHg.
 *  The gradient & offset coefficients are derived using (A = adc counts):
 *      m = P40 / (A40 - A0);
 *      c = -(A0 * m);
 *  Pressure Pn is then found by calculating:
 *      Pn = m * An  +  c
 *  Temperature oC of MCU IC:
 *      TEMP = 147.5 – ((75 * (VREFP – VREFN) * ADCVALUE) / 4096)
 * Note:
 *  Battery voltage is sensed via a voltage divider
 *  ADC precision error (on breadboard cct) is +- 0.1%
 *
 *
 *  Created on: 25 Jul 2021
 *      Author: John Chee
 */

#include "Sensors.h"

//..... Instantiate Static Variables ..........................................
uint16_t cl_sensors::ui16_BattVolt_mV;
uint16_t cl_sensors::ui16_ClogPressure_mmHg;
uint16_t cl_sensors::ui16_BackPressure_mmHg;
uint16_t cl_sensors::ui16_ChamberPressure_mmHg;
uint16_t cl_sensors::ui16_CoughPressure_mmHg;
uint16_t cl_sensors::ui16_MCU_Temperature_oCx10;
//-- Calibration coefficients
st_calib_t cl_sensors::st_ClogPressure;
st_calib_t cl_sensors::st_BackPressure;
st_calib_t cl_sensors::st_ChamberPressure;
st_calib_t cl_sensors::st_CoughPressure;
st_calib_t cl_sensors::st_MCU_Temperature;
//.............................................................................

//::cc-------------------------------------------------------------------------
cl_sensors::cl_sensors(){

    //--- Calibration coefficients
    //-- ClogPressure
    st_ClogPressure.ui16_m_coeff_x10k = 687;    //0.06873
    st_ClogPressure.ui16_c_coeff_x100 = 1983;    //-17.353

    //-- BackPressure
    st_BackPressure.ui16_m_coeff_x10k = 1140;   //0.11396
    st_BackPressure.ui16_c_coeff_x100 = 2131;   //-21.3105


    //-- ChamberPressure
    st_ChamberPressure.ui16_m_coeff_x10k = 1153; //0.11527
    st_ChamberPressure.ui16_c_coeff_x100 = 2455; //-24.5533


/*
    //TODO later when circuit has been defined ...
    //-- CoughPressure
    st_CoughPressure.ui16_m_coeff_x10k = ??;
    st_CoughPressure.ui16_c_coeff_100 = ??;
*/

    //-- CU_Temperature
    st_MCU_Temperature.ui16_m_coeff_x10k = 604; //-0.06042
    st_MCU_Temperature.ui16_c_coeff_x100 = 14750;//147.5

}
//::cc-------------------------------------------------------------------------

//--- Sense Voltage
//::---------------------------------------------------------------------------
uint16_t cl_sensors::sense_BattVolt_mV(){      // PE3 |p6 |J3p9
    digitise_Ain0_PE3_adc();
    ui16_BattVolt_mV = ((ui16_Ain0_PE3_adc + 1)* (uint32_t)3300 * 2) /4096; //x2 added to compensate for voltage divider
    return ui16_BattVolt_mV;
}
//::---------------------------------------------------------------------------

//--- Sense Pressure
//::---------------------------------------------------------------------------
uint16_t cl_sensors::sense_ClogPress_mmHg(){   // PE2 |p7 |J3p8
    digitise_Ain1_PE2_adc();
    ui16_ClogPressure_mmHg = ((ui16_Ain1_PE2_adc * st_ClogPressure.ui16_m_coeff_x10k) / 10000)
            - (st_ClogPressure.ui16_c_coeff_x100 / 100);
     return ui16_ClogPressure_mmHg;
}
//::---------------------------------------------------------------------------
uint16_t cl_sensors::sense_BackPress_mmHg(){    // PB4 |p58|J1p7
    digitise_Ain10_PB4_adc();
    ui16_BackPressure_mmHg = ((ui16_Ain10_PB4_adc * st_BackPressure.ui16_m_coeff_x10k) / 10000)
            - (st_BackPressure.ui16_c_coeff_x100 / 100);
    return ui16_BackPressure_mmHg;
}
//::---------------------------------------------------------------------------
uint16_t cl_sensors::sense_ChamberPress_mmHg(){ // PE5 |p60|J1p6
    digitise_Ain8_PE5_adc();
    ui16_ChamberPressure_mmHg = ((ui16_Ain8_PE5_adc * st_ChamberPressure.ui16_m_coeff_x10k) / 10000)
            - (st_ChamberPressure.ui16_c_coeff_x100 / 100);
    return ui16_ChamberPressure_mmHg;
}
//::---------------------------------------------------------------------------
uint16_t cl_sensors::sense_CoughPress_mmHg(){   // PE0 |p9 |J2p3
    digitise_Ain3_PE0_adc();
    ui16_CoughPressure_mmHg = ((ui16_Ain3_PE0_adc * st_CoughPressure.ui16_m_coeff_x10k) / 10000)
            - (st_CoughPressure.ui16_c_coeff_x100 / 100);
    return ui16_CoughPressure_mmHg;
}
//::---------------------------------------------------------------------------

//--- Sense Temperature
//::---------------------------------------------------------------------------
uint16_t cl_sensors::sense_MCU_temperature_oCx10(){ //internally connected
    digitise_Ain_MCU_TS_adc();
    ui16_MCU_Temperature_oCx10 = -(((ui16_Ain_MCU_TS_adc + 1) * st_MCU_Temperature.ui16_m_coeff_x10k) / 10000)
            + (st_MCU_Temperature.ui16_c_coeff_x100 / 100);
    return ui16_MCU_Temperature_oCx10;
}
//::---------------------------------------------------------------------------

