
/*
 * Pump.cpp
 * Only one pump is used in NTL.
 *
 * ------------------------------------------------|
 * GPIO|Pin|Config  |MCU Control/Input lines |TIVA |
 * ------------------------------------------------|
 * PE4 |p59|PWM2    |Drv_AirPump_PE4         |J1p5 |
 * ------------------------------------------------|
 *
 *  Created on: 22 Jul 2021
 *      Author: John Chee
 */

#include "Pump.h"

//=============================================================================
int main(void){
    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN); //config for 50MHz clock

    cl_pump oPump; //Air pump for pressuring chamber

    //----- Test pump turn on and off
    for (int i=0;i<100;i++){
    oPump.turn_On(); //Motor turns on. Air starts to flow out
    SysCtlDelay(2000000); //240ms

    oPump.turn_Off(); //Motor turns off. No air flow
    SysCtlDelay(30000000); //3600ms
    }

    while(1){

    }
}
//=============================================================================
