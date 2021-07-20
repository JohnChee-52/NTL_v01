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

#ifndef TM4C123GH6PM_CONFIG_PINS_H_
#define TM4C123GH6PM_CONFIG_PINS_H_

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"

/*
// Make this header have a C binding when compiling with C++ compiler.
#ifdef __cplusplus
extern "C"
{
#endif
*/

//-----------------------------------------------------------------------------
//extern void TM4C123GH6PM_Config_Pins(void);
//extern void PinoutSet(void);
//-----------------------------------------------------------------------------

//!!! Uncomment the "#define ..." line if unit testing is reqd
#define Unit_Test_Mode
//#undef Unit_Test_Mode
//>>>>> Controls to select unit testing or production >>>>>>>>>>>>>>>>>>>>>>>>>
#ifdef Unit_Test_Mode
#define private public
#define protected public
#endif
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

enum en_ov_spl_t {enOvSplx2=2, enOvSplx4=4, enOvSplx8=8, enOvSplx16=16, enOvSplx64=64};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class cl_tm4c123gh6pm_pins{
private:
protected:
    uint32_t aui32ADC_Buf[8];
    uint32_t ui32ADC_Value_avg;

/*
    //--- Analog inputs
    uint16_t digitize_Ain0_PE3();  //MCUp6
    uint16_t digitize_Ain1_PE2();  //MCUp7
    uint16_t digitize_Ain10_PB4(); //MCUp58
    uint16_t digitize_Ain8_PE5();  //MCUp60
*/

    //--- Digital inputs
    bool read_DI_PB0(); //MCUp45
    bool read_DI_PB2(); //MCUp47
    bool read_DI_PB7(); //MCUp4
    bool read_DI_PE0(); //MCUp9
    bool read_DI_PF0(); //MCUp28
    bool read_DI_PF4(); //MCUp5
    bool read_DI_PA5(); //MCUp22

    //--- Digital outputs
    void drv_H_PB1(); //MCUp46
    void drv_L_PB1(); //MCUp46

    void drv_H_PB6(); //MCUp1
    void drv_L_PB6(); //MCUp1

    void drv_H_PE1(); //MCUp8
    void drv_L_PE1(); //MCUp8

    void drv_H_PC4(); //MCUp16
    void drv_L_PC4(); //MCUp16

    void drv_H_PC5(); //MCUp15
    void drv_L_PC5(); //MCUp15

    void drv_H_PF1(); //MCUp29
    void drv_L_PF1(); //MCUp29

    void drv_H_PF2(); //MCUp30
    void drv_L_PF2(); //MCUp30

    void drv_H_PF3(); //MCUp31
    void drv_L_PF3(); //MCUp31

    void drv_H_PB5(); //MCUp57
    void drv_L_PB5(); //MCUp57

    void drv_H_PD6(); //MCUp53
    void drv_L_PD6(); //MCUp53

    void drv_H_PD7(); //MCUp10
    void drv_L_PD7(); //MCUp10

   //--- I2C (Inter-integrated Circuit)



    //--- PWM output(Pulse width modulation)


    //--- SSI (Synchronous Serial Interface)


    //--- UART Serial Communications



public:
    cl_tm4c123gh6pm_pins(); //Ctor
    //--- ADC
    void set_HW_OverSampling(en_ov_spl_t enUsr_OvSplCnt); //enOvSplx2,4,8,16,64


};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


/*
#ifdef __cplusplus
}
#endif
*/


#endif /* TM4C123GH6PM_CONFIG_PINS_H_ */
