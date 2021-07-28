/*
 * Switches.cpp
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

//..... Instantiate Static Variables ..........................................
bool cl_switches::bMem_Pulse;
bool cl_switches::bMem_MonMode;
bool cl_switches::bMem_PwrSense;
bool cl_switches::bMem_MuteAlert;
bool cl_switches::bMem_SysWakeup;
bool cl_switches::bMem_SysMode;
//.............................................................................

//::cc-------------------------------------------------------------------------
cl_switches::cl_switches(){ //Ctor
}
//::cc-------------------------------------------------------------------------


//--- Sw_Pulse              // PB0     45  J1p3
//::---------------------------------------------------------------------------
bool cl_switches::read_Level_Pulse(){
    bMem_Pulse =  read_DI_PB0();
    return bMem_Pulse;
}
//::---------------------------------------------------------------------------
bool cl_switches::is_pressed_Pulse(){
    bMem_Pulse =  read_DI_PB0();
    return (bMem_Pulse ? false : true);
}
//::---------------------------------------------------------------------------
bool cl_switches::is_justPressed_Pulse(){
    bool bF_JustPressed;
    bool bF_CurrLevel; //Current level of switch

    bF_CurrLevel = read_DI_PB0();
    if(bMem_Pulse && (! bF_CurrLevel)){
        bF_JustPressed = true;
    }else{
        bF_JustPressed = false;
    }
    bMem_Pulse = bF_CurrLevel;
    return bF_JustPressed;
}
//::---------------------------------------------------------------------------
bool cl_switches::is_released_Pulse(){
    bMem_Pulse =  read_DI_PB0();
    return (bMem_Pulse ? true : false);
}
//::---------------------------------------------------------------------------
bool cl_switches::is_justReleased_Pulse(){
    bool bF_JustReleased;
    bool bF_CurrLevel;

    bF_CurrLevel = read_DI_PB0();
    if((! bMem_Pulse) && bF_CurrLevel){
        bF_JustReleased = true;
    }else{
        bF_JustReleased = false;
    }
    bMem_Pulse = bF_CurrLevel;
    return bF_JustReleased;
}
//::---------------------------------------------------------------------------

//--- Sw_MonMode            // PB2     47  J2p2
//::---------------------------------------------------------------------------
bool cl_switches::read_Level_MonMode(){
    bMem_MonMode =  read_DI_PB2();
    return bMem_MonMode;
}
//::---------------------------------------------------------------------------
bool cl_switches::is_pressed_MonMode(){
    bMem_MonMode =  read_DI_PB2();
    return (bMem_MonMode ? false : true);
}
//::---------------------------------------------------------------------------
bool cl_switches::is_justPressed_MonMode(){
    bool bF_JustPressed;
    bool bF_CurrLevel; //Current level of switch

    bF_CurrLevel = read_DI_PB2();
    if(bMem_MonMode && (! bF_CurrLevel)){
        bF_JustPressed = true;
    }else{
        bF_JustPressed = false;
    }
    bMem_MonMode = bF_CurrLevel;
    return bF_JustPressed;
}
//::---------------------------------------------------------------------------
bool cl_switches::is_released_MonMode(){
    bMem_MonMode =  read_DI_PB2();
    return (bMem_MonMode ? true : false);
}
//::---------------------------------------------------------------------------
bool cl_switches::is_justReleased_MonMode(){
    bool bF_JustReleased;
    bool bF_CurrLevel;

    bF_CurrLevel = read_DI_PB2();
    if((! bMem_MonMode) && bF_CurrLevel){
        bF_JustReleased = true;
    }else{
        bF_JustReleased = false;
    }
    bMem_MonMode = bF_CurrLevel;
    return bF_JustReleased;
}
//::---------------------------------------------------------------------------

//--- Sw_PwrSense           // PB7       4   J2p6
//::---------------------------------------------------------------------------
bool cl_switches::read_Level_PwrSense(){
    bMem_PwrSense =  read_DI_PB7();
    return bMem_PwrSense;
}
//::---------------------------------------------------------------------------
bool cl_switches::is_pressed_PwrSense(){
    bMem_PwrSense =  read_DI_PB7();
    return (bMem_PwrSense ? false : true);
}
//::---------------------------------------------------------------------------
bool cl_switches::is_justPressed_PwrSense(){
    bool bF_JustPressed;
    bool bF_CurrLevel; //Current level of switch

    bF_CurrLevel = read_DI_PB7();
    if(bMem_PwrSense && (! bF_CurrLevel)){
        bF_JustPressed = true;
    }else{
        bF_JustPressed = false;
    }
    bMem_PwrSense = bF_CurrLevel;
    return bF_JustPressed;
}
//::---------------------------------------------------------------------------
bool cl_switches::is_released_PwrSense(){
    bMem_PwrSense =  read_DI_PB7();
    return (bMem_PwrSense ? true : false);
}
//::---------------------------------------------------------------------------
bool cl_switches::is_justReleased_PwrSense(){
    bool bF_JustReleased;
    bool bF_CurrLevel;

    bF_CurrLevel = read_DI_PB7();
    if((! bMem_PwrSense) && bF_CurrLevel){
        bF_JustReleased = true;
    }else{
        bF_JustReleased = false;
    }
    bMem_PwrSense = bF_CurrLevel;
    return bF_JustReleased;
}
//::---------------------------------------------------------------------------

//--- Sw_MuteAlert          // PA4       9   J2p8
//::---------------------------------------------------------------------------
bool cl_switches::read_Level_MuteAlert(){
    bMem_MuteAlert =  read_DI_PA4();
    return bMem_MuteAlert;
}
//::---------------------------------------------------------------------------
bool cl_switches::is_pressed_MuteAlert(){
    bMem_MuteAlert =  read_DI_PA4();
    return (bMem_MuteAlert ? false : true);
}
//::---------------------------------------------------------------------------
bool cl_switches::is_justPressed_MuteAlert(){
    bool bF_JustPressed;
    bool bF_CurrLevel; //Current level of switch

    bF_CurrLevel = read_DI_PA4();
    if(bMem_MuteAlert && (! bF_CurrLevel)){
        bF_JustPressed = true;
    }else{
        bF_JustPressed = false;
    }
    bMem_MuteAlert = bF_CurrLevel;
    return bF_JustPressed;
}
//::---------------------------------------------------------------------------
bool cl_switches::is_released_MuteAlert(){
    bMem_MuteAlert =  read_DI_PA4();
    return (bMem_MuteAlert ? true : false);
}
//::---------------------------------------------------------------------------
bool cl_switches::is_justReleased_MuteAlert(){
    bool bF_JustReleased;
    bool bF_CurrLevel;

    bF_CurrLevel = read_DI_PA4();
    if((! bMem_MuteAlert) && bF_CurrLevel){
        bF_JustReleased = true;
    }else{
        bF_JustReleased = false;
    }
    bMem_MuteAlert = bF_CurrLevel;
    return bF_JustReleased;
}
//::---------------------------------------------------------------------------

//--- Sw_SysWakeup          // PF0      28  J4p10
//::---------------------------------------------------------------------------
bool cl_switches::read_Level_SysWakeup(){
    bMem_SysWakeup =  read_DI_PF0();
    return bMem_SysWakeup;
}
//::---------------------------------------------------------------------------
bool cl_switches::is_pressed_SysWakeup(){
    bMem_SysWakeup =  read_DI_PF0();
    return (bMem_SysWakeup ? false : true);
}
//::---------------------------------------------------------------------------
bool cl_switches::is_justPressed_SysWakeup(){
    bool bF_JustPressed;
    bool bF_CurrLevel; //Current level of switch

    bF_CurrLevel = read_DI_PF0();
    if(bMem_SysWakeup && (! bF_CurrLevel)){
        bF_JustPressed = true;
    }else{
        bF_JustPressed = false;
    }
    bMem_SysWakeup = bF_CurrLevel;
    return bF_JustPressed;
}
//::---------------------------------------------------------------------------
bool cl_switches::is_released_SysWakeup(){
    bMem_SysWakeup =  read_DI_PF0();
    return (bMem_SysWakeup ? true : false);
}
//::---------------------------------------------------------------------------
bool cl_switches::is_justReleased_SysWakeup(){
    bool bF_JustReleased;
    bool bF_CurrLevel;

    bF_CurrLevel = read_DI_PF0();
    if((! bMem_SysWakeup) && bF_CurrLevel){
        bF_JustReleased = true;
    }else{
        bF_JustReleased = false;
    }
    bMem_SysWakeup = bF_CurrLevel;
    return bF_JustReleased;
}
//::---------------------------------------------------------------------------

//--- Sw_SysMode            // PF4       5   J2p4
//::---------------------------------------------------------------------------
bool cl_switches::read_Level_SysMode(){
    bMem_SysMode =  read_DI_PF4();
    return bMem_SysMode;
}
//::---------------------------------------------------------------------------
bool cl_switches::is_pressed_SysMode(){
    bMem_SysMode =  read_DI_PF4();
    return (bMem_SysMode ? false : true);
}
//::---------------------------------------------------------------------------
bool cl_switches::is_justPressed_SysMode(){
    bool bF_JustPressed;
    bool bF_CurrLevel; //Current level of switch

    bF_CurrLevel = read_DI_PF4();
    if(bMem_SysMode && (! bF_CurrLevel)){
        bF_JustPressed = true;
    }else{
        bF_JustPressed = false;
    }
    bMem_SysMode = bF_CurrLevel;
    return bF_JustPressed;
}
//::---------------------------------------------------------------------------
bool cl_switches::is_released_SysMode(){
    bMem_SysMode =  read_DI_PF4();
    return (bMem_SysMode ? true : false);
}
//::---------------------------------------------------------------------------
bool cl_switches::is_justReleased_SysMode(){
    bool bF_JustReleased;
    bool bF_CurrLevel;

    bF_CurrLevel = read_DI_PF4();
    if((! bMem_SysMode) && bF_CurrLevel){
        bF_JustReleased = true;
    }else{
        bF_JustReleased = false;
    }
    bMem_SysMode = bF_CurrLevel;
    return bF_JustReleased;
}
//::---------------------------------------------------------------------------


