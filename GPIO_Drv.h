/*
 * GPIO_Drv.h
 *
 * --------------------------------------------
 * GPIO|Functn |MCU Ctrl/Input line     |TIVA
 * --------------------------------------------
 * PA5 |DI     |~Int_IO_Expandr_PA5     |J1p8
 * PA6 |I2C3   |IO_Expander_SCL_PA6     |J1p9
 * PA7 |I2C3   |IO_Expander_SDA_PA7     |J1p10
 * --------------------------------------------
 * PB0 |DI     |Sw3_Pulse_PB0           |J1p3
 * PB1 |DO     |Drv_Valve_Bolus_PB1     |J1p4
 * PB2 |DI|Sw4_MonitorMode_PB2          |J2p2
 * PB4 | AIN10 |BackPressure_PB4        |J1p7
 * PB5 |DO,PWM3|Buzzer_PB5              |J1p2
 * PB6 |DO     |Drv_Valve_Exhaust_PB6   |J2p7
 * PB7 |DI     |Sw6_PwrSense_PB7        |J2p6
 * --------------------------------------------
 * PC4 |DO     |LED_Send_Char_PC4       |J4p4
 * PC5 |DO     |LED_Rcv_Char_PC5        |J4p5
 * PC6 |U3Rx   |UART_Rx_PC6             |J4p6
 * PC7 |U3Tx   |UART_Tx_PC7             |J4p7
 * --------------------------------------------
 * PD0 |SSI1_Clk|EEPROM_Clk_PD0         |J3p3
 * PD1 |SSI1_FSS|EEPROM_FSS_PD1         |J3p4
 * PD2 |SSI1_Rx|EEPROM_Rx_PD2           |J3p5
 * PD3 |SSI1_Tx|EEPROM_Tx_PD3           |J3p6
 * PD6 |DO     |RS485_En_Rcv_PD6        |J4p8
 * PD7 |DO     |RS485_En_Send_PD7            |J4p9
 * --------------------------------------------
 * PE0 |DI     |Sw5_Mute/Rst Alert_PE0  |J2p3
 * PE1 |DO     |Drv_Valve_TestBolus_PE1 |J3p7
 * PE2 | AIN1  |ClogPressure_PE2        |J3p8
 * PE3 | AIN0  |BatteryVoltage_PE3      |J3p9
 * PE4 |PWM    |Drv_AirPump_PE4         |J1p5
 * PE5 | AIN8  |ChamberPressure_PE5     |J1p6
 * --------------------------------------------
 * PF0 |DI     |Sw1_Wakeup_PF0          |-
 * PF1 |DO     |Drv_LED1_Red_PF1        |-
 * PF2 |DO     |Drv_LED2_Blue_PF2       |-
 * PF3 |DO     |Drv_LED3_Green_PF3      |-
 * PF4 |DI     |Sw2_Mode_PF4            |-
 * PFO |~Wake  |~CP_Int_Wake_PF0        |J2p4
 * --------------------------------------------
 * Rset|Reset  |~Reset                  |J2p5
 *
 *
 *  Created on: 1 Jul 2021
 *      Author: John Chee
 */

#ifndef GPIO_DRV_H_
#define GPIO_DRV_H_

//!!! Uncomment the "#define ..." line if unit testing is required
#define Unit_Test_Mode
//#undef Unit_Test_Mode
//>>>>> Controls to select unit testing or production >>>>>>>>>>>>>>>>>>>>>>>>>
#ifdef Unit_Test_Mode
#define private public
#define protected public
#endif
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class cl_gpio_drv_pa {
private:
protected:
public:
    cl_gpio_drv_pa();
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//cc---------------------------------------------------------------------------
cl_gpio_drv_pa::cl_gpio_drv_pa(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA); //enable GPIO port A
    GPIODirModeSet(GPIO_PORTA_BASE, GPIO_PIN_5, GPIO_DIR_MODE_IN);
    GPIOPadConfigSet(GPIO_PORTA_BASE, GPIO_PIN_5, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

}
//cc---------------------------------------------------------------------------
//::---------------------------------------------------------------------------
//::---------------------------------------------------------------------------


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class cl_gpio_drv_pb {
private:
protected:
public:
    cl_gpio_drv_pb();
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//cc---------------------------------------------------------------------------
cl_gpio_drv_pb::cl_gpio_drv_pb(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB); //enable GPIO port B
    //--- Set to digital outputs
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_6|GPIO_PIN_5|GPIO_PIN_1); //set to DO for PB6,PB5,PB1
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_6|GPIO_PIN_5|GPIO_PIN_1, 0);//Drive pins to L

    //--- Set to digital inputs
    GPIODirModeSet(GPIO_PORTB_BASE, GPIO_PIN_7|GPIO_PIN_2|GPIO_PIN_0, GPIO_DIR_MODE_IN);
    GPIOPadConfigSet(GPIO_PORTB_BASE, GPIO_PIN_7|GPIO_PIN_2|GPIO_PIN_0, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

}
//cc---------------------------------------------------------------------------
//::---------------------------------------------------------------------------
//::---------------------------------------------------------------------------


#endif /* GPIO_DRV_H_ */
