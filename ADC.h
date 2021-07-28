/*
 * ADC.h
 * This module digitises 5 input channels & 1 internal channel and returns adc counts.
 *  Ain0  - battery voltage
 *  Ain1  - clog (filter) pressure
 *  Ain10 - backpressure
 *  Ain8  - chamber pressure
 *  Ain3  - cough pressure
 *  TS    - temperature sensor of MCU IC (internal)
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

#ifndef ADC_H_
#define ADC_H_


#include "Unit_Test_Mode.h"
#include "TM4C123GH6PM_Config_Pins.h"
#include "driverlib/adc.h"


enum en_ov_spl_t {enOvSplx2=2, enOvSplx4=4, enOvSplx8=8, enOvSplx16=16, enOvSplx64=64};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class cl_adc : cl_tm4c123gh6pm_pins{
private:
    static uint32_t ui32_Adc_data[8]; //Raw data buf x4
    static uint32_t ui32_Adc_data_avg; //Averaged Raw data

protected:
    //--- Analog Data
    static uint16_t ui16_Ain0_PE3_adc;
    static uint16_t ui16_Ain1_PE2_adc;
    static uint16_t ui16_Ain10_PB4_adc;
    static uint16_t ui16_Ain8_PE5_adc;
    static uint16_t ui16_Ain3_PE0_adc;
    static uint16_t ui16_Ain_MCU_TS_adc;

    //--- Analog inputs
    uint32_t digitise_Ain0_PE3_adc();  //MCUp6  J3p9
    uint32_t digitise_Ain1_PE2_adc();  //MCUp7  J3p8
    uint32_t digitise_Ain10_PB4_adc(); //MCUp58 J1p7
    uint32_t digitise_Ain8_PE5_adc();  //MCUp60 J1p6
    uint32_t digitise_Ain3_PE0_adc();  //MCUp9  J2p3
    uint32_t digitise_Ain_MCU_TS_adc();  //MCU inbuilt temperature sensor

public:
    cl_adc(); //Ctor

    //--- ADC
    void set_HW_OverSampling(en_ov_spl_t enUsr_OvSplCnt); //enOvSplx2,4,8,16,64

/*
    uint16_t conv_BattVolt_to_mV();
    uint16_t conv_ClogPress_to_mmHg();
    uint16_t conv_BackPress_to_mmHg();
    uint16_t conv_ChamberPress_to_mmHg();
    uint16_t conv_MCU_temperature_mC();
*/

};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



#endif /* ADC_H_ */
