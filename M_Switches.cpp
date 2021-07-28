/*
 * M_Switches.cpp
 * NTL uses 6 switches, of which 4 are user-accessible:
 * 1.  Sw_Pulse
 * 2.  Sw_MonMode
 * 3.  Sw_PwrSense
 * 4.  Sw_MuteAlert
 * The remaining 2 switches are PCBA mounted, for use during firmware development:
 * 1.  Sw_SysWakeup
 * 2.  Sw_SysMode
 *
 * Switches are connected to the GPIO pins as follows:
 * ------------------------------------------------|
 * GPIO|Pin|Config  |MCU Control/Input lines |TIVA |
 * ------------------------------------------------|
 * PB0 |p45|DI      |Sw3_Pulse_PB0           |J1p3 |
 * PB2 |p47|DI      |Sw4_MonitorMode_PB2     |J2p2 |
 * PB7 |p4 |DI      |Sw6_PwrSense_PB7        |J2p6 |
 * PA4 |p9 |DI      |Sw5_Mute/Reset Alert_PA4|J2p8 |
 * PF0 |p28|DI      |Sw2_SysWakeup_PF0       |J2p4 |
 * PF4 |p5 |DI      |Sw1_Mode_PF4            |J4p10|
 * ------------------------------------------------|
 *
 *  Created on: 22 Jul 2021
 *      Author: John Chee
 */
#include "Switches.h"

//=============================================================================
 int main(void){


    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN); //config for 50MHz clock

    cl_switches oSwitch;

    //------- Test Switches
    //These tests are done by pressing the switch in checking the status written by the functions.

    bool bF_Sw_Status;

    //----- Test Sw_Pulse
    //-- Press & release switch
    bF_Sw_Status = oSwitch.read_Level_Pulse(); //1 <- not pressed
    bF_Sw_Status = oSwitch.read_Level_Pulse(); //0 <- pressed
    bF_Sw_Status = oSwitch.read_Level_Pulse(); //1 <- not pressed


    bF_Sw_Status = oSwitch.is_pressed_Pulse(); //0 <- not pressed
    bF_Sw_Status = oSwitch.is_pressed_Pulse(); //1 <- pressed
    bF_Sw_Status = oSwitch.is_pressed_Pulse(); //0 <- not pressed

    bF_Sw_Status = oSwitch.is_justPressed_Pulse(); //0 <- not pressed
    bF_Sw_Status = oSwitch.is_justPressed_Pulse(); //1 <- pressed
    bF_Sw_Status = oSwitch.is_justPressed_Pulse(); //0 <-  "
    bF_Sw_Status = oSwitch.is_justPressed_Pulse(); //0 <- not pressed
    bF_Sw_Status = oSwitch.is_justPressed_Pulse(); //0 <-  "


    bF_Sw_Status = oSwitch.is_released_Pulse(); //1 <- released
    bF_Sw_Status = oSwitch.is_released_Pulse(); //0 <- not released
    bF_Sw_Status = oSwitch.is_released_Pulse(); //1 <- released

    bF_Sw_Status = oSwitch.is_justReleased_Pulse(); //0 <- released
    bF_Sw_Status = oSwitch.is_justReleased_Pulse(); //0 <- not released (ie =pressed)
    bF_Sw_Status = oSwitch.is_justReleased_Pulse(); //0 <-  "
    bF_Sw_Status = oSwitch.is_justReleased_Pulse(); //1 <- released
    bF_Sw_Status = oSwitch.is_justReleased_Pulse(); //0 <-  "
    bF_Sw_Status = oSwitch.is_justReleased_Pulse(); //0 <-  "
    bF_Sw_Status = oSwitch.is_justReleased_Pulse(); //0 <-  "



    //----- Test Sw_MonMode
    bF_Sw_Status = oSwitch.read_Level_MonMode(); //1 <- not pressed
    bF_Sw_Status = oSwitch.read_Level_MonMode(); //0 <- pressed
    bF_Sw_Status = oSwitch.read_Level_MonMode(); //1 <- not pressed


    bF_Sw_Status = oSwitch.is_pressed_MonMode(); //0 <- not pressed
    bF_Sw_Status = oSwitch.is_pressed_MonMode(); //1 <- pressed
    bF_Sw_Status = oSwitch.is_pressed_MonMode(); //0 <- not pressed

    bF_Sw_Status = oSwitch.is_justPressed_MonMode(); //0 <- not pressed
    bF_Sw_Status = oSwitch.is_justPressed_MonMode(); //1 <- pressed
    bF_Sw_Status = oSwitch.is_justPressed_MonMode(); //0 <-  "
    bF_Sw_Status = oSwitch.is_justPressed_MonMode(); //0 <- not pressed
    bF_Sw_Status = oSwitch.is_justPressed_MonMode(); //0 <-  "


    bF_Sw_Status = oSwitch.is_released_MonMode(); //1 <- released
    bF_Sw_Status = oSwitch.is_released_MonMode(); //0 <- not released
    bF_Sw_Status = oSwitch.is_released_MonMode(); //1 <- released

    bF_Sw_Status = oSwitch.is_justReleased_MonMode(); //0 <- released
    bF_Sw_Status = oSwitch.is_justReleased_MonMode(); //0 <- not released (ie =pressed)
    bF_Sw_Status = oSwitch.is_justReleased_MonMode(); //0 <-  "
    bF_Sw_Status = oSwitch.is_justReleased_MonMode(); //1 <- released
    bF_Sw_Status = oSwitch.is_justReleased_MonMode(); //0 <-  "
    bF_Sw_Status = oSwitch.is_justReleased_MonMode(); //0 <-  "
    bF_Sw_Status = oSwitch.is_justReleased_MonMode(); //0 <-  "



    //----- Test Sw_PwrSense
    bF_Sw_Status = oSwitch.read_Level_PwrSense(); //1 <- not pressed
    bF_Sw_Status = oSwitch.read_Level_PwrSense(); //0 <- pressed
    bF_Sw_Status = oSwitch.read_Level_PwrSense(); //1 <- not pressed


    bF_Sw_Status = oSwitch.is_pressed_PwrSense(); //0 <- not pressed
    bF_Sw_Status = oSwitch.is_pressed_PwrSense(); //1 <- pressed
    bF_Sw_Status = oSwitch.is_pressed_PwrSense(); //0 <- not pressed

    bF_Sw_Status = oSwitch.is_justPressed_PwrSense(); //0 <- not pressed
    bF_Sw_Status = oSwitch.is_justPressed_PwrSense(); //1 <- pressed
    bF_Sw_Status = oSwitch.is_justPressed_PwrSense(); //0 <-  "
    bF_Sw_Status = oSwitch.is_justPressed_PwrSense(); //0 <- not pressed
    bF_Sw_Status = oSwitch.is_justPressed_PwrSense(); //0 <-  "


    bF_Sw_Status = oSwitch.is_released_PwrSense(); //1 <- released
    bF_Sw_Status = oSwitch.is_released_PwrSense(); //0 <- not released
    bF_Sw_Status = oSwitch.is_released_PwrSense(); //1 <- released

    bF_Sw_Status = oSwitch.is_justReleased_PwrSense(); //0 <- released
    bF_Sw_Status = oSwitch.is_justReleased_PwrSense(); //0 <- not released (ie =pressed)
    bF_Sw_Status = oSwitch.is_justReleased_PwrSense(); //0 <-  "
    bF_Sw_Status = oSwitch.is_justReleased_PwrSense(); //1 <- released
    bF_Sw_Status = oSwitch.is_justReleased_PwrSense(); //0 <-  "
    bF_Sw_Status = oSwitch.is_justReleased_PwrSense(); //0 <-  "
    bF_Sw_Status = oSwitch.is_justReleased_PwrSense(); //0 <-  "



    //----- Test Sw_MuteAlert
    bF_Sw_Status = oSwitch.read_Level_MuteAlert(); //1 <- not pressed
    bF_Sw_Status = oSwitch.read_Level_MuteAlert(); //0 <- pressed
    bF_Sw_Status = oSwitch.read_Level_MuteAlert(); //1 <- not pressed


    bF_Sw_Status = oSwitch.is_pressed_MuteAlert(); //0 <- not pressed
    bF_Sw_Status = oSwitch.is_pressed_MuteAlert(); //1 <- pressed
    bF_Sw_Status = oSwitch.is_pressed_MuteAlert(); //0 <- not pressed

    bF_Sw_Status = oSwitch.is_justPressed_MuteAlert(); //0 <- not pressed
    bF_Sw_Status = oSwitch.is_justPressed_MuteAlert(); //1 <- pressed
    bF_Sw_Status = oSwitch.is_justPressed_MuteAlert(); //0 <-  "
    bF_Sw_Status = oSwitch.is_justPressed_MuteAlert(); //0 <- not pressed
    bF_Sw_Status = oSwitch.is_justPressed_MuteAlert(); //0 <-  "


    bF_Sw_Status = oSwitch.is_released_MuteAlert(); //1 <- released
    bF_Sw_Status = oSwitch.is_released_MuteAlert(); //0 <- not released
    bF_Sw_Status = oSwitch.is_released_MuteAlert(); //1 <- released

    bF_Sw_Status = oSwitch.is_justReleased_MuteAlert(); //0 <- released
    bF_Sw_Status = oSwitch.is_justReleased_MuteAlert(); //0 <- not released (ie =pressed)
    bF_Sw_Status = oSwitch.is_justReleased_MuteAlert(); //0 <-  "
    bF_Sw_Status = oSwitch.is_justReleased_MuteAlert(); //1 <- released
    bF_Sw_Status = oSwitch.is_justReleased_MuteAlert(); //0 <-  "
    bF_Sw_Status = oSwitch.is_justReleased_MuteAlert(); //0 <-  "
    bF_Sw_Status = oSwitch.is_justReleased_MuteAlert(); //0 <-  "



    //----- Test Sw_SysWakeup
    bF_Sw_Status = oSwitch.read_Level_SysWakeup(); //1 <- not pressed
    bF_Sw_Status = oSwitch.read_Level_SysWakeup(); //0 <- pressed
    bF_Sw_Status = oSwitch.read_Level_SysWakeup(); //1 <- not pressed


    bF_Sw_Status = oSwitch.is_pressed_SysWakeup(); //0 <- not pressed
    bF_Sw_Status = oSwitch.is_pressed_SysWakeup(); //1 <- pressed
    bF_Sw_Status = oSwitch.is_pressed_SysWakeup(); //0 <- not pressed

    bF_Sw_Status = oSwitch.is_justPressed_SysWakeup(); //0 <- not pressed
    bF_Sw_Status = oSwitch.is_justPressed_SysWakeup(); //1 <- pressed
    bF_Sw_Status = oSwitch.is_justPressed_SysWakeup(); //0 <-  "
    bF_Sw_Status = oSwitch.is_justPressed_SysWakeup(); //0 <- not pressed
    bF_Sw_Status = oSwitch.is_justPressed_SysWakeup(); //0 <-  "


    bF_Sw_Status = oSwitch.is_released_SysWakeup(); //1 <- released
    bF_Sw_Status = oSwitch.is_released_SysWakeup(); //0 <- not released
    bF_Sw_Status = oSwitch.is_released_SysWakeup(); //1 <- released

    bF_Sw_Status = oSwitch.is_justReleased_SysWakeup(); //0 <- released
    bF_Sw_Status = oSwitch.is_justReleased_SysWakeup(); //0 <- not released (ie =pressed)
    bF_Sw_Status = oSwitch.is_justReleased_SysWakeup(); //0 <-  "
    bF_Sw_Status = oSwitch.is_justReleased_SysWakeup(); //1 <- released
    bF_Sw_Status = oSwitch.is_justReleased_SysWakeup(); //0 <-  "
    bF_Sw_Status = oSwitch.is_justReleased_SysWakeup(); //0 <-  "
    bF_Sw_Status = oSwitch.is_justReleased_SysWakeup(); //0 <-  "



    //----- Test Sw_SysMode
    bF_Sw_Status = oSwitch.read_Level_SysMode(); //1 <- not pressed
    bF_Sw_Status = oSwitch.read_Level_SysMode(); //0 <- pressed
    bF_Sw_Status = oSwitch.read_Level_SysMode(); //1 <- not pressed


    bF_Sw_Status = oSwitch.is_pressed_SysMode(); //0 <- not pressed
    bF_Sw_Status = oSwitch.is_pressed_SysMode(); //1 <- pressed
    bF_Sw_Status = oSwitch.is_pressed_SysMode(); //0 <- not pressed

    bF_Sw_Status = oSwitch.is_justPressed_SysMode(); //0 <- not pressed
    bF_Sw_Status = oSwitch.is_justPressed_SysMode(); //1 <- pressed
    bF_Sw_Status = oSwitch.is_justPressed_SysMode(); //0 <-  "
    bF_Sw_Status = oSwitch.is_justPressed_SysMode(); //0 <- not pressed
    bF_Sw_Status = oSwitch.is_justPressed_SysMode(); //0 <-  "


    bF_Sw_Status = oSwitch.is_released_SysMode(); //1 <- released
    bF_Sw_Status = oSwitch.is_released_SysMode(); //0 <- not released
    bF_Sw_Status = oSwitch.is_released_SysMode(); //1 <- released

    bF_Sw_Status = oSwitch.is_justReleased_SysMode(); //0 <- released
    bF_Sw_Status = oSwitch.is_justReleased_SysMode(); //0 <- not released (ie =pressed)
    bF_Sw_Status = oSwitch.is_justReleased_SysMode(); //0 <-  "
    bF_Sw_Status = oSwitch.is_justReleased_SysMode(); //1 <- released
    bF_Sw_Status = oSwitch.is_justReleased_SysMode(); //0 <-  "
    bF_Sw_Status = oSwitch.is_justReleased_SysMode(); //0 <-  "
    bF_Sw_Status = oSwitch.is_justReleased_SysMode(); //0 <-  "


    //----- Just to avoid warning "never used"
    if(bF_Sw_Status);

    while(1){

    }
}
//=============================================================================
