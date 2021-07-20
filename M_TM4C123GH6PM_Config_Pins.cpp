/*
 * TM4C123GH6PM_Config_Pins.h
 * Configure the MCU pins only for the NTL project.
 * The initialistaion of registers to perform functions are not done in this module.
 * Only digital inputs (DI) and digital outputs (DO) are defined in this module.
 * ------------------------------------------------|
 * GPIO|Pin|Config  |MCU Control/Input lines |TIVA |
 * ------------------------------------------------|
 * PE3 |p6 |AIN0    |BatteryVoltage_PE3      |J3p9 |
 * PE2 |p7 |AIN1    |ClogPressure_PE2        |J3p8 |
 * PB4 |p58|AIN10   |BackPressure_PB4        |J1p7 |
 * PE5 |p60|AIN8    |ChamberPressure_PE5     |J1p6 |
 * ------------------------------------------------|
 * PB0 |p45|DI      |Sw3_Pulse_PB0           |J1p3 |
 * PB2 |p47|DI      |Sw4_MonitorMode_PB2     |J2p2 |
 * PB7 |p4 |DI      |Sw6_PwrSense_PB7        |J2p6 |
 * PE0 |p9 |DI      |Sw5_Mute/Reset Alert_PE0|J2p3 |
 * PF0 |p28|DI      |Sw2_Wakeup_PF0          |J2p4 |<--
 * PF4 |p5 |DI      |Sw1_Mode_PF4            |J4p10|<--
 * ------------------------------------------------|
 * PB1 |p46|DO      |Drv_Valve_Bolus_PB1     |J1p4 |
 * PB6 |p1 |DO      |Drv_Valve_Exhaust_PB6   |J2p7 |
 * PE1 |p8 |DO      |Drv_Valve_TestBolus_PE1 |J3p7 |
 * PC4 |p16|DO      |LED_Send_Char_PC4       |J4p4 |
 * PC5 |p15|DO      |LED_Rcv_Char_PC5        |J4p5 |
 * PF1 |p29|DO      |Drv_LED1_Red_PF1        |J3p10|
 * PF2 |p30|DO      |Drv_LED2_Blue_PF2       |J4p1 |
 * PF3 |p31|DO      |Drv_LED3_Green_PF3      |J4p2 |
 * PB5 |p57|DO      |Buzzer_PB5              |J1p2 |
 * ------------------------------------------------|
 * PA6 |p23|I2C2    |IO_Expander_SCL_PA6     |J1p9 |
 * PA7 |p24|I2C2    |IO_Expander_SDA_PA7     |J1p10|
 * PA5 |p22|DI      |~Int_IO_Expander_PA5    |J1p8 |
 * ------------------------------------------------|
 * PE4 |p59|PWM2    |Drv_AirPump_PE4         |J1p5 |
 * ------------------------------------------------|
 * PD0 |p61|SSI1_Clk|EEPROM_Clk_PD0          |J3p3 |
 * PD1 |p62|SSI1_FSS|EEPROM_FSS_PD1          |J3p4 |
 * PD2 |p63|SSI1_Rx |EEPROM_Rx_PD2           |J3p5 |
 * PD3 |p64|SSI1_Tx |EEPROM_Tx_PD3           |J3p6 |
 * ------------------------------------------------|
 * PD6 |p53|DO      |RS485_En_Rcv_PD6        |J4p8 |
 * PD7 |p10|DO      |RS485_En_Send_PD7       |J4p9 |
 * PC6 |p14|U3Rx    |UART_Rx_PC6             |J4p6 |
 * PC7 |p13|U3Tx    |UART_Tx_PC7             |J4p7 |
 * ------------------------------------------------|
 *
 * Adapted from the outputs of TI's PinMux version 4.0.1532.
 *
 *  Created on: 15 Jul 2021
 *      Author: John Chee
 */

#include "TM4C123GH6PM_Config_Pins.h"

//=============================================================================
int main(void){
    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN); //config for 50MHz clock

    cl_tm4c123gh6pm_pins MCU;

/*
    //----- Test Analog Inputs

    uint16_t Data_ZeroLevel[4];
    uint16_t Data_MidLevel[4];
    uint16_t Data_MaxLevel[4];
    //Use controlled voltage source to test. Apply voltages and step over the instruction.

    //-- PE3 |p6 |AIN0    |BatteryVoltage_PE3      |J3p9 |
    //Apply 0.1V to J3p9
    Data_ZeroLevel[0] = MCU.digitize_Ain0_PE3(); //Data_ZeroLevel[0]=0x7C
    //Apply 1.65V to J3p9
    Data_MidLevel[0] = MCU.digitize_Ain0_PE3();  //Data_MidLevel[0]=0x7FF
    //Apply 3.0V to J3p9
    Data_MaxLevel[0] = MCU.digitize_Ain0_PE3();  //Data_MaxLevel[0]=0xE8B

    //-- PE2 |p7 |AIN1    |ClogPressure_PE2        |J3p8 |
    //Apply 0.1V to J3p8
    Data_ZeroLevel[1] = MCU.digitize_Ain1_PE2(); //Data_ZeroLevel[1]=0x7C
    //Apply 1.65V to J3p8
    Data_MidLevel[1] = MCU.digitize_Ain1_PE2();  //Data_MidLevel[1]=0x7FF
    //Apply 3.0V to J3p8
    Data_MaxLevel[1] = MCU.digitize_Ain1_PE2();  //Data_MaxLevel[1]=0xE8B

    //-- PB4 |p58|AIN10   |BackPressure_PB4        |J1p7 |
    //Apply 0.1V to J1p7
    Data_ZeroLevel[2] = MCU.digitize_Ain10_PB4(); //Data_ZeroLevel[2]=0x7C
    //Apply 1.65V to J1p7
    Data_MidLevel[2] = MCU.digitize_Ain10_PB4();  //Data_MidLevel[2]=0x7FF
    //Apply 3.0V to J1p7
    Data_MaxLevel[2] = MCU.digitize_Ain10_PB4();  //Data_MaxLevel[2]=0xE8B

    //-- PE5 |p60|AIN8    |ChamberPressure_PE5     |J1p6 |
    //Apply 0.1V to J1p6
    Data_ZeroLevel[3] = MCU.digitize_Ain8_PE5(); //Data_ZeroLevel[3]=0x7C
    //Apply 1.65V to J1p6
    Data_MidLevel[3] = MCU.digitize_Ain8_PE5();  //Data_MidLevel[3]=0x7FF
    //Apply 3.0V to J1p6
    Data_MaxLevel[3] = MCU.digitize_Ain8_PE5();  //Data_MaxLevel[3]=0xE8B

    //----- Just to avoid warning "never used"
    Data_ZeroLevel[0]++;
    Data_MidLevel[0]++;
    Data_MaxLevel[0]++;
*/

    //----- Test Digital Inputs
    //Set a H and L voltage to the input pin and check the level read
    // eg. use a switch
    bool bLevel; //Level seen by MCU

    //-- PB0 |p45|Sw3_Pulse_PB0           |J1p3 |
    bLevel = MCU.read_DI_PB0(); //H = when input voltage is H
    bLevel = MCU.read_DI_PB0(); //L = when input voltage is L
    bLevel = MCU.read_DI_PB0(); //H = when input voltage is H

    //-- PB2 |p47|Sw4_MonitorMode_PB2     |J2p2 |
    bLevel = MCU.read_DI_PB2(); //H = when input voltage is H
    bLevel = MCU.read_DI_PB2(); //L = when input voltage is L
    bLevel = MCU.read_DI_PB2(); //H = when input voltage is H

    //-- PB7 |p4 |Sw6_PwrSense_PB7        |J2p6 |
    bLevel = MCU.read_DI_PB7(); //H = when input voltage is H
    bLevel = MCU.read_DI_PB7(); //L = when input voltage is L
    bLevel = MCU.read_DI_PB7(); //H = when input voltage is H

    //-- PE0 |p9 |Sw5_Mute/Reset Alert_PE0|J2p3 |
    bLevel = MCU.read_DI_PE0(); //H = when input voltage is H
    bLevel = MCU.read_DI_PE0(); //L = when input voltage is L
    bLevel = MCU.read_DI_PE0(); //H = when input voltage is H

    //-- PF0 |p28|Sw2_Wakeup_PF0          |J4p10|
//    while(1){
    bLevel = MCU.read_DI_PF0(); //H = when input voltage is H
    bLevel = MCU.read_DI_PF0(); //L = when input voltage is L
    bLevel = MCU.read_DI_PF0(); //H = when input voltage is H
//    }

    //-- PF4 |p5 |Sw1_Mode_PF4             |J2p4 |
    bLevel = MCU.read_DI_PF4(); //H = when input voltage is H
    bLevel = MCU.read_DI_PF4(); //L = when input voltage is L
    bLevel = MCU.read_DI_PF4(); //H = when input voltage is H

    //----- Just to avoid warning "never used"
    if(bLevel);

    //----- Test Digital Outputs
    //Use Oscilloscope to view the High and low states at the various pins of the MCU

    //-- PB1 |p46|Drv_Valve_Bolus_PB1     |J1p4 |
    MCU.drv_L_PB1(); //L
    MCU.drv_H_PB1(); //H
    MCU.drv_L_PB1(); //L

    //-- PB6 |p1 |Drv_Valve_Exhaust_PB6   |J2p7 |
    MCU.drv_L_PB6(); //L
    MCU.drv_H_PB6(); //H
    MCU.drv_L_PB6(); //L

    //-- PE1 |p8 |Drv_Valve_TestBolus_PE1 |J3p7 |
    MCU.drv_L_PE1(); //L
    MCU.drv_H_PE1(); //H
    MCU.drv_L_PE1(); //L

    //-- PC4 |p16|LED_Send_Char_PC4       |J4p4 |
    MCU.drv_L_PC4(); //L
    MCU.drv_H_PC4(); //H
    MCU.drv_L_PC4(); //L

    //-- PC5 |p15|LED_Rcv_Char_PC5        |J4p5 |
    MCU.drv_L_PC5(); //L
    MCU.drv_H_PC5(); //H
    MCU.drv_L_PC5(); //L

    //-- PF1 |p29|Drv_LED1_Red_PF1        |J3p10|
    MCU.drv_L_PF1(); //L
    MCU.drv_H_PF1(); //H
    MCU.drv_L_PF1(); //L

    //-- PF2 |p30|Drv_LED2_Blue_PF2       |J4p1 |
    MCU.drv_L_PF2(); //L
    MCU.drv_H_PF2(); //H
    MCU.drv_L_PF2(); //L

    //-- PF3 |p31|Drv_LED3_Green_PF3      |J4p2 |
    MCU.drv_L_PF3(); //L
    MCU.drv_H_PF3(); //H
    MCU.drv_L_PF3(); //L

    //-- PB5 |p57|Buzzer_PB5              |J1p2 |
    MCU.drv_L_PB5(); //L
//    while(1){
    MCU.drv_H_PB5(); //H
    MCU.drv_L_PB5(); //L
//    }

    //----- Test I2C (Inter-integrated Circuit)



    //----- Test PWM output(Pulse width modulation)


    //----- Test SSI (Synchronous Serial Interface)


    //----- Test UART Serial Communications



     while(1){

    }
}
//=============================================================================


