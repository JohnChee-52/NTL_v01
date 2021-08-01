/*
 * M_Sensors.cpp
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
 * Calibration of pressure sensors:
 *  Typically done at 2 pressures: 0 mmHg (Atmospheric), 40 mmHg.
 *  The gradient & offset coefficients are derived using (A = adc counts):
 *      m = P40 / (A40 - A0);
 *      c = -(A0 * m);
 *  Pressure Pn is then found by calculating:
 *      Pn = m * An  +  c
 *  Pressure Sensitivities:
 *      MP3V5050GC6U = 54mv/kPa   10mV/1.38mmHg     1mmHg/7.25mV
 *      MPXV5100DP   = 90mv/kPa   10mV/0.83mmHg     1mmHg/12mV
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

//=============================================================================
int main(void){


    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN); //config for 50MHz clock

    cl_sensors oSensor;

    uint16_t u16_mV[10];
    uint16_t u16_mmHg;
    uint16_t u16_oCx10; //tenths of oC

    //------- Test: Sense Voltage
    //-- Apply 1.65Vdc to PE3, reading should be 3.3V, since battery is divided by 2 for sensing
    u16_mV[0] = oSensor.sense_BattVolt_mV(); //3300 mV <-- PE3 |p6 |J3p9
    u16_mV[1] = oSensor.sense_BattVolt_mV();
    u16_mV[2] = oSensor.sense_BattVolt_mV();
    u16_mV[3] = oSensor.sense_BattVolt_mV();
    u16_mV[4] = oSensor.sense_BattVolt_mV();
    u16_mV[5] = oSensor.sense_BattVolt_mV();
    u16_mV[6] = oSensor.sense_BattVolt_mV();
    u16_mV[7] = oSensor.sense_BattVolt_mV();
    u16_mV[8] = oSensor.sense_BattVolt_mV();
    u16_mV[9] = oSensor.sense_BattVolt_mV();

    //------- Verify: Sense Pressures
    //Apply air pressure to various sensors and check that pressure reading increased

    //-- Clog Pressure Sensor:
    u16_mmHg = oSensor.sense_ClogPress_mmHg();    //Pressure increased <-- PE2 |p7 |J3p8

    //-- BackPressure Sensor:
    u16_mmHg = oSensor.sense_BackPress_mmHg();    //RRPressure increased <-- PB4 |p58|J1p7

    //-- Chamber Pressure Sensor:
    u16_mmHg = oSensor.sense_ChamberPress_mmHg(); //Pressure increased <-- PE5 |p60|J1p6

    //-- Cough Pressure Sensor:
    u16_mmHg = oSensor.sense_CoughPress_mmHg();   //Pressure increased <-- PE0 |p9 |J2p3

    //----- Test: Sense Temperature
    //MCU IC temperature:
    u16_oCx10 = oSensor.sense_MCU_temperature_oCx10(); //internally connected

    //----- Just to avoid warning "never used"
    u16_mV[9] ++;
    u16_mmHg ++;
    u16_oCx10 ++; //tenths of oC


    while(1){

    }
}
//=============================================================================
