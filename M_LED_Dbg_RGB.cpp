/*
 * M_LED_Dbg_RGB.cpp
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

#include "LED_Dbg_RGB.h"

//=============================================================================
int main(void){


    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN); //config for 50MHz clock

    cl_led_dbg_rgb oLED_Dbg; //Ctor


    //------- Test Debug LEDs
    //Check whether the LEDs light up or off according to the instructions
    //For pulses, use oscilloscope to view with trig mode set to Normal

    //----- Test Debug Red Led        PF1    MCUp29  J1p10
    //-- Visual check
    oLED_Dbg.on_Red();      //On
    oLED_Dbg.off_Red();     //Off
    oLED_Dbg.toggle_Red();  //On
    oLED_Dbg.toggle_Red();  //Off

    //-- Oscilloscope check
    oLED_Dbg.pulse_Red();   //x1 pulse; width 720ns
    oLED_Dbg.pulse_x2_Red();//x2 pulses
    oLED_Dbg.pulse_x3_Red();//x3 pulses


    //----- Test Debug Green Led      PF3     MCUp31  J4p2
    //-- Visual check
    oLED_Dbg.on_Green();      //On
    oLED_Dbg.off_Green();     //Off
    oLED_Dbg.toggle_Green();  //On
    oLED_Dbg.toggle_Green();  //Off

    //-- Oscilloscope check
    oLED_Dbg.pulse_Green();   //x1 pulse; width 720ns
    oLED_Dbg.pulse_x2_Green();//x2 pulses
    oLED_Dbg.pulse_x3_Green();//x3 pulses


    //----- Test Debug Blue Led       PF2     MCUp30  J4p1
    //-- Visual check
    oLED_Dbg.on_Blue();      //On
    oLED_Dbg.off_Blue();     //Off
    oLED_Dbg.toggle_Blue();  //On
    oLED_Dbg.toggle_Blue();  //Off

    //-- Oscilloscope check
    oLED_Dbg.pulse_Blue();   //x1 pulse; width 720ns
    oLED_Dbg.pulse_x2_Blue();//x2 pulses
    oLED_Dbg.pulse_x3_Blue();//x3 pulses



    while(1){

    }
}
//=============================================================================
