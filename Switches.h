/*
 * Switches.h
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
 * PA4 |p21|DI      |Sw5_Mute/Reset Alert_PA4|J2p8 |
 * PF0 |p28|DI      |Sw2_SysWakeup_PF0       |J2p4 |
 * PF4 |p5 |DI      |Sw1_Mode_PF4            |J4p10|
 * ------------------------------------------------|
 *
 *  Created on: 22 Jul 2021
 *      Author: John Chee
 */

#ifndef SWITCHES_H_
#define SWITCHES_H_

#include "Unit_Test_Mode.h"
#include "TM4C123GH6PM_Config_Pins.h"


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class cl_switches : cl_tm4c123gh6pm_pins{
private:
protected:
public:
    static bool bMem_Pulse;
    static bool bMem_MonMode;
    static bool bMem_PwrSense;
    static bool bMem_MuteAlert;
    static bool bMem_SysWakeup;
    static bool bMem_SysMode;

    cl_switches(); //Ctor
    //----- Switch name             DO   IC pin TIVA
    //--- Sw_Pulse              // PB0     45  J1p3
    bool read_Level_Pulse();
    bool is_pressed_Pulse();
    bool is_justPressed_Pulse();
    bool is_released_Pulse();
    bool is_justReleased_Pulse();

    //--- Sw_MonMode            // PB2     47  J2p2
    bool read_Level_MonMode();
    bool is_pressed_MonMode();
    bool is_justPressed_MonMode();
    bool is_released_MonMode();
    bool is_justReleased_MonMode();

    //--- Sw_PwrSense           // PB7       4   J2p6
    bool read_Level_PwrSense();
    bool is_pressed_PwrSense();
    bool is_justPressed_PwrSense();
    bool is_released_PwrSense();
    bool is_justReleased_PwrSense();

    //--- Sw_MuteAlert          // PA4       9   J2p8
    bool read_Level_MuteAlert();
    bool is_pressed_MuteAlert();
    bool is_justPressed_MuteAlert();
    bool is_released_MuteAlert();
    bool is_justReleased_MuteAlert();

    //--- Sw_SysWakeup          // PF0      28  J4p10
    bool read_Level_SysWakeup();
    bool is_pressed_SysWakeup();
    bool is_justPressed_SysWakeup();
    bool is_released_SysWakeup();
    bool is_justReleased_SysWakeup();

    //--- Sw_SysMode            // PF4       5   J2p4
    bool read_Level_SysMode();
    bool is_pressed_SysMode();
    bool is_justPressed_SysMode();
    bool is_released_SysMode();
    bool is_justReleased_SysMode();

};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


#endif /* SWITCHES_H_ */
