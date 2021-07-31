/*
 * Sensors.h
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

#ifndef SENSORS_H_
#define SENSORS_H_

#include "Unit_Test_Mode.h"
#include "ADC.h"

struct st_calib_t{
    uint16_t ui16_m_coeff_x10k;
    uint16_t ui16_c_coeff_x100;
};


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class cl_sensors : cl_adc {
private:
    static uint32_t ui32_Adc_data[8]; //Raw data buf x4
    static uint32_t ui32_Adc_data_avg; //Averaged Raw data

protected:
public:


    static st_calib_t st_ClogPressure;
    static st_calib_t st_BackPressure;
    static st_calib_t st_ChamberPressure;
    static st_calib_t st_CoughPressure;
    static st_calib_t st_MCU_Temperature;

    static uint16_t ui16_BattVolt_mV;
    static uint16_t ui16_ClogPressure_mmHg;
    static uint16_t ui16_BackPressure_mmHg;
    static uint16_t ui16_ChamberPressure_mmHg;
    static uint16_t ui16_CoughPressure_mmHg;
    static uint16_t ui16_MCU_Temperature_oCx10;

    cl_sensors(); //Ctor

    //--- Sense Voltage
    uint16_t sense_BattVolt_mV();       // PE3 |p6 |J3p9

    //--- Sense Pressure
    uint16_t sense_ClogPress_mmHg();    // PE2 |p7 |J3p8
    uint16_t sense_BackPress_mmHg();    // PB4 |p58|J1p7
    uint16_t sense_ChamberPress_mmHg(); // PE5 |p60|J1p6
    uint16_t sense_CoughPress_mmHg();   // PE0 |p9 |J2p3

    //--- Sense Temperature
    uint16_t sense_MCU_temperature_oCx10(); //internally connected


};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++




#endif /* SENSORS_H_ */
