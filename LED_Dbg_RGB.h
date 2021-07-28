/*
 * LED_Dbg_RGB.h
 * This module drives 3 LEDs, R G B to assist in debugging
 * Simple functions are provided for all 3 Leds
 *  - On, Off, Toggle, Pulse - x1, x2, x3
 * Each pulse is about 720ns using 50 MHz SysClk
 *
 * ------------------------------------------------|
 * GPIO|Pin|Config  |MCU Control/Input lines |TIVA |
 * ------------------------------------------------|
 * PF1 |p29|DO      |Drv_LED1_Red_PF1        |J3p10|
 * PF2 |p30|DO      |Drv_LED2_Blue_PF2       |J4p1 |
 * PF3 |p31|DO      |Drv_LED3_Green_PF3      |J4p2 |
 * ------------------------------------------------|
 *
 *  Created on: 28 Jul 2021
 *      Author: John Chee
 */

#ifndef LED_DBG_RGB_H_
#define LED_DBG_RGB_H_

#include "Unit_Test_Mode.h"
#include "TM4C123GH6PM_Config_Pins.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class cl_led_dbg_rgb : cl_tm4c123gh6pm_pins{
private:
protected:
    static uint16_t ui16_Blink_cnt;  //Default Blink Cnt
    static uint16_t ui16_Dur_ms; //Default ON duration (ms)
    static uint32_t ui32_Period_ms; //Default Period in a repeat cycle (ms)
    static bool bF_TrigBlink; //1=trigger blinking process
public:

    cl_led_dbg_rgb();//Ctor

    //--- Red Led       PF1    MCUp29  J1p10
    void on_Red();
    void off_Red();
    void pulse_Red();   //LHL H=720ns
    void pulse_x2_Red();//LHLHL
    void pulse_x3_Red();//LHLHLHL
    void toggle_Red();

    //--- Green Led     PF3     MCUp31  J4p2
    void on_Green();
    void off_Green();
    void pulse_Green();
    void pulse_x2_Green();
    void pulse_x3_Green();
    void toggle_Green();

    //--- Blue Led      PF2     MCUp30  J4p1
    void on_Blue();
    void off_Blue();
    void pulse_Blue();
    void pulse_x2_Blue();
    void pulse_x3_Blue();
    void toggle_Blue();


};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



#endif /* LED_DBG_RGB_H_ */
