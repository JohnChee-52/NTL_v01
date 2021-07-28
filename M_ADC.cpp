/*
 * M_ADC.cpp
 * This module digitises 5 input channels & 1 internal channel and returns adc counts.
 *  Ain0  - battery voltage
 *  Ain1  - clog (filter) pressure
 *  Ain10 - backpressure
 *  Ain8  - chamber pressure
 *  Ain3  - cough pressure
 *  TS    - temperature sensor of MCU IC (internal)
 * Note:
 *  Battery voltage is sensed via a voltage divider
 *  ADC precision error (on breadboard cct) is +- 0.1%
 * ------------------------------------------------|
 * GPIO|Pin|Config  |MCU Control/Input lines |TIVA |
 * ------------------------------------------------|
 * PE3 |p6 |AIN0    |BatteryVoltage_PE3      |J3p9 |
 * PE2 |p7 |AIN1    |ClogPressure_PE2        |J3p8 |
 * PB4 |p58|AIN10   |BackPressure_PB4        |J1p7 |
 * PE5 |p60|AIN8    |ChamberPressure_PE5     |J1p6 |
 * PE0 |p9 |AIN3    |CoughPressure_PE0       |J2p3 |
 * -   |-  |TS      |MCU temperature         |-    |
 * ------------------------------------------------|
 *
 * Note:
 *  GPIO pin for ADC inputs is configured through inheritance of "cl_tm4c123gh6pm_pins"
 *  Sequencers 0, 1, 3 are used (8-sample, 4-sample, 1-sample)
 *  Sequencer 2 is not used (4-sample)
 *
 *
 *  Created on: 23 Jul 2021
 *      Author: John Chee
 */

#include "ADC.h"

//=============================================================================
int main(void){


    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN); //config for 50MHz clock

    cl_adc oADC;

    //----- Test Analog Inputs

    uint16_t Data_L[6]; //for 100mV
    uint16_t Data_M[6]; //for 1650mV
    uint16_t Data_H[6]; //for 3000mV

    //------- Use controlled voltage source to test.
    //Apply voltages and step over each instruction.

    //-- PE3 |p6 |AIN0    |BatteryVoltage_PE3      |J3p9 |
    Data_L[0] = oADC.digitise_Ain0_PE3_adc();  //0x7C|124 <-- at 100mV
    Data_M[0] = oADC.digitise_Ain0_PE3_adc();  //0x800|2048 <-- at 1650mV
    Data_H[0] = oADC.digitise_Ain0_PE3_adc();  //0xE8B|3723 <-- at 3000mV


    //-- PE2 |p7 |AIN1    |ClogPressure_PE2        |J3p8 |
    Data_L[1] = oADC.digitise_Ain1_PE2_adc();  //0x7C|124 <-- at 100mV
    Data_M[1] = oADC.digitise_Ain1_PE2_adc();  //0x800|2048 <-- at 1650mV
    Data_H[1] = oADC.digitise_Ain1_PE2_adc();  //0xE8B|3723 <-- at 3000mV


    //-- PB4 |p58|AIN10   |BackPressure_PB4        |J1p7 |
    Data_L[2] = oADC.digitise_Ain10_PB4_adc();  //0x7C|124 <-- at 100mV
    Data_M[2] = oADC.digitise_Ain10_PB4_adc();  //0x800|2048 <-- at 1650mV
    Data_H[2] = oADC.digitise_Ain10_PB4_adc();  //0xE8B|3723 <-- at 3000mV


    //-- PE5 |p60|AIN8    |ChamberPressure_PE5     |J1p6 |
    Data_L[3] = oADC.digitise_Ain8_PE5_adc();  //0x7C|124 <-- at 100mV
    Data_M[3] = oADC.digitise_Ain8_PE5_adc();  //0x800|2048 <-- at 1650mV
    Data_H[3] = oADC.digitise_Ain8_PE5_adc();  //0xE8B|3723 <-- at 3000mV

    //-- PE0 |p9 |AIN3    |CoughPressure_PE0       |J2p3 |
    Data_L[4] = oADC.digitise_Ain3_PE0_adc();  //0x7C|124 <-- at 100mV
    Data_M[4] = oADC.digitise_Ain3_PE0_adc();  //0x800|2048 <-- at 1650mV
    Data_H[4] = oADC.digitise_Ain3_PE0_adc();  //0xE8B|3723 <-- at 3000mV

    //-- MCU IC Temperature
    Data_L[5] = oADC.digitise_Ain_MCU_TS_adc();  //0x7C|124 <-- around 26 oC
    Data_M[5] = oADC.digitise_Ain_MCU_TS_adc();  //0x800|2047 <-- around 26 oC
    Data_H[5] = oADC.digitise_Ain_MCU_TS_adc();  //0xE8B|3723 <-- around 26 oC


    //----- Just to avoid warning "never used"
    Data_L[0]++;
    Data_M[0]++;
    Data_H[0]++;


    while(1){

    }
}
//=============================================================================
