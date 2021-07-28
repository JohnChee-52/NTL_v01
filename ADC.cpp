/*
 * ADC.cpp
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

//..... Instantiate Static Variables ..........................................
uint16_t cl_adc::ui16_Ain0_PE3_adc;
uint16_t cl_adc::ui16_Ain1_PE2_adc;
uint16_t cl_adc::ui16_Ain10_PB4_adc;
uint16_t cl_adc::ui16_Ain8_PE5_adc;
uint16_t cl_adc::ui16_Ain3_PE0_adc;
uint16_t cl_adc::ui16_Ain_MCU_TS_adc;

uint32_t cl_adc::ui32_Adc_data[8]; //Raw data buf x4
uint32_t cl_adc::ui32_Adc_data_avg; //Averaged Raw data
//.............................................................................

//::cc-------------------------------------------------------------------------
cl_adc::cl_adc(){
    //Only Sequencers 0 & 3 is used (1,2 are not used)
    //Note: GPIO pin for ADC inputs has been configured through inheritance of cl_tm4c123gh6pm_pins

    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0); //Enable ADC subsystem
    SysCtlDelay(1000); //120us - wait for ADC HW to stabilise

    //--- Config Sequencer 0 (8-sample FIFO) for Ain0_PE3, Ain1_PE2, Ain10_PB4, Ain8_PE5
    ADCSequenceDisable(ADC0_BASE, 0);//Disable sequencer 0 for configuring
    ADCSequenceConfigure(ADC0_BASE,0, ADC_TRIGGER_PROCESSOR, 0);// Sequencer0, uP trig, highest priority
    ADCSequenceStepConfigure(ADC0_BASE,0,0,ADC_CTL_CH0);//1st sample (Ain0 J3p9)
    ADCSequenceStepConfigure(ADC0_BASE,0,1,ADC_CTL_CH0);//2nd "
    ADCSequenceStepConfigure(ADC0_BASE,0,2,ADC_CTL_CH1);//1st sample (Ain1 J3p8)
    ADCSequenceStepConfigure(ADC0_BASE,0,3,ADC_CTL_CH1);//2nd "
    ADCSequenceStepConfigure(ADC0_BASE,0,4,ADC_CTL_CH10);//1st sample (Ain10 J1p7)
    ADCSequenceStepConfigure(ADC0_BASE,0,5,ADC_CTL_CH10);//2nd "
    ADCSequenceStepConfigure(ADC0_BASE,0,6,ADC_CTL_CH8);//1st sample (Ain8 J1p6)
    ADCSequenceStepConfigure(ADC0_BASE,0,7,ADC_CTL_CH8|ADC_CTL_IE|ADC_CTL_END);//2nd sample (Ain8), en IRQ, end seq.
    ADCSequenceEnable(ADC0_BASE,0);//Enable sequencer 0

    //--- Config Sequencer 1 (4-sample FIFO) for Ain3_PE0
    ADCSequenceDisable(ADC0_BASE, 1);//Disable sequencer 1 for configuring
    ADCSequenceConfigure(ADC0_BASE,1, ADC_TRIGGER_PROCESSOR, 1);//Sequencer1, uP trig, high priority
    ADCSequenceStepConfigure(ADC0_BASE,1,0,ADC_CTL_CH3);//1st sample of ADC_CTL_CH3 (Ain3 J2p3)
    ADCSequenceStepConfigure(ADC0_BASE,1,1,ADC_CTL_CH3|ADC_CTL_IE|ADC_CTL_END);//4th sample (Ain3) en IRQ, end seq.
    ADCSequenceEnable(ADC0_BASE,1);//Enable sequencer 1

    //--- Config Sequencer 3 (1-sample FIFO) for built-in temperature sensor
    ADCSequenceDisable(ADC0_BASE, 3);//Disable sequencer 3 for configuring
    ADCSequenceConfigure(ADC0_BASE,3, ADC_TRIGGER_PROCESSOR, 3);//Config ADC0 to use Sequencer3, uP trig, lowest priority
    ADCSequenceStepConfigure(ADC0_BASE,3,0,ADC_CTL_TS|ADC_CTL_IE|ADC_CTL_END);
    ADCSequenceEnable(ADC0_BASE,3);//Enable sequencer 3

    //--- Hardware oversampling to improve accuracy
    set_HW_OverSampling(enOvSplx16); //x16
}
//::cc-------------------------------------------------------------------------


//--- ADC
//::---------------------------------------------------------------------------
void cl_adc::set_HW_OverSampling(en_ov_spl_t enUsr_OvSplCnt){//enOvSplx2,4,8,16,64
    ADCHardwareOversampleConfigure(ADC0_BASE,enUsr_OvSplCnt);
}
//::---------------------------------------------------------------------------


//------- Analog inputs
//--- PE3 |p6 |AIN0    |BatteryVoltage_PE3      |J3p9 |
//::---------------------------------------------------------------------------
uint32_t cl_adc::digitise_Ain0_PE3_adc(){ //MCUp6  J3p9
    ADCIntClear(ADC0_BASE,0); //clear interrupt flag of Sequencer0
    ADCProcessorTrigger(ADC0_BASE,0);//trigger digitisation
    while(!ADCIntStatus(ADC0_BASE,0,false)){}; //wait for end of conversion
    ADCSequenceDataGet(ADC0_BASE,0,&ui32_Adc_data[0]); //get ADC data into 2 word array
    ui32_Adc_data_avg = (ui32_Adc_data[0]+ui32_Adc_data[1] + 1)/2; //average with +0.5 roundoff.
    ui16_Ain0_PE3_adc = (uint16_t)ui32_Adc_data_avg;
    return ui16_Ain0_PE3_adc;
}
//::---------------------------------------------------------------------------
//--- PE2 |p7 |AIN1    |ClogPressure_PE2        |J3p8 |
//::---------------------------------------------------------------------------
uint32_t cl_adc::digitise_Ain1_PE2_adc(){ //MCUp7  J3p8
    ADCIntClear(ADC0_BASE,0); //clear interrupt flag of Sequencer0
    ADCProcessorTrigger(ADC0_BASE,0);//trigger digitisation
    while(!ADCIntStatus(ADC0_BASE,0,false)){}; //wait for end of conversion
    ADCSequenceDataGet(ADC0_BASE,0,&ui32_Adc_data[0]); //get ADC data into 2 word array
    ui32_Adc_data_avg=(ui32_Adc_data[2]+ui32_Adc_data[3] + 1)/2; //average with +0.5 roundoff.
    ui16_Ain1_PE2_adc = (uint16_t)ui32_Adc_data_avg;
    return ui16_Ain1_PE2_adc;
}
//::---------------------------------------------------------------------------
//--- PB4 |p58|AIN10   |BackPressure_PB4        |J1p7 |
//::---------------------------------------------------------------------------
uint32_t cl_adc::digitise_Ain10_PB4_adc(){//MCUp58 J1p7
    ADCIntClear(ADC0_BASE,0); //clear interrupt flag of Sequencer0
    ADCProcessorTrigger(ADC0_BASE,0);//trigger digitisation
    while(!ADCIntStatus(ADC0_BASE,0,false)){}; //wait for end of conversion
    ADCSequenceDataGet(ADC0_BASE,0,&ui32_Adc_data[0]); //get ADC data into 2 word array
    ui32_Adc_data_avg=(ui32_Adc_data[4]+ui32_Adc_data[5] + 1)/2; //average with +0.5 roundoff.
    ui16_Ain10_PB4_adc = (uint16_t)ui32_Adc_data_avg;
    return ui16_Ain10_PB4_adc;
}
//::---------------------------------------------------------------------------
//--- PE5 |p60|AIN8    |ChamberPressure_PE5     |J1p6 |
//::---------------------------------------------------------------------------
uint32_t cl_adc::digitise_Ain8_PE5_adc(){ //MCUp60 J1p6
    ADCIntClear(ADC0_BASE,0); //clear interrupt flag of Sequencer0
    ADCProcessorTrigger(ADC0_BASE,0);//trigger digitisation
    while(!ADCIntStatus(ADC0_BASE,0,false)){}; //wait for end of conversion
    ADCSequenceDataGet(ADC0_BASE,0,&ui32_Adc_data[0]); //get ADC data into 2 word array
    ui32_Adc_data_avg=(ui32_Adc_data[6]+ui32_Adc_data[7] + 1)/2; //average with +0.5 roundoff.
    ui16_Ain8_PE5_adc = (uint16_t)ui32_Adc_data_avg;
    return ui16_Ain8_PE5_adc;
}
//::---------------------------------------------------------------------------
//--- PE0 |p9 |AIN3    |CoughPressure_PE0       |J2p3 |
//::---------------------------------------------------------------------------
uint32_t cl_adc::digitise_Ain3_PE0_adc(){ //MCUp9  J2p3
    ADCIntClear(ADC0_BASE,1); //clear interrupt flag of Sequencer1
    ADCProcessorTrigger(ADC0_BASE,1);//trigger digitisation
    while(!ADCIntStatus(ADC0_BASE,1,false)){}; //wait for end of conversion
    ADCSequenceDataGet(ADC0_BASE,1,&ui32_Adc_data[0]); //get ADC data into 2 word array
    ui32_Adc_data_avg=(ui32_Adc_data[0]+ui32_Adc_data[1] + 1)/2; //average with +0.5 roundoff.
    ui16_Ain3_PE0_adc = (uint16_t)ui32_Adc_data_avg;
    return ui16_Ain3_PE0_adc;
}
//::---------------------------------------------------------------------------
//--- -   |-  |TS      |MCU temperature         |-    |
//::---------------------------------------------------------------------------
uint32_t cl_adc::digitise_Ain_MCU_TS_adc(){  //MCU inbuilt temperature sensor
    ADCIntClear(ADC0_BASE,3); //clear interrupt flag of ADC0 sequencer 3.
    ADCProcessorTrigger(ADC0_BASE,3);//PE3 AIn0: trigger  conversion thru ADC0 sequencer 1
    while(!ADCIntStatus(ADC0_BASE,3,false)){}; //wait for end of conversion
    ADCSequenceDataGet(ADC0_BASE,3,&ui32_Adc_data_avg); //get ADC data
    ui16_Ain_MCU_TS_adc = (uint16_t)ui32_Adc_data_avg;
    return ui16_Ain_MCU_TS_adc;
    //ui32_Temperature_oC = (1475 - ((2475 * ui16_Ain_MCU_TS_adc)) / 4096)/10;
}
//::---------------------------------------------------------------------------

