/*
 * M_Timers.cpp
 * Timer0 has been configured as a 64-bit periodic timer that runs
 * continuously. The periodicity is programmable from microseconds to 60s.
 * Typically, Timer0 will be used to generate 10 ms periodic interrupts,
 * so that the timer’s ISR can run in “real time” (i.e. fast relative to
 * human reflex).
 * For an Interrupt Service Routine (ISR) to be served by an interrupt, it
 * must have its ID defined in ISR_Register.h, and the ISR manager must
 * register it during program initialisation in main().
 *
 * Note: In periodic mode, the 2nd period onwards is accurate in duration.
 *
 *  Created on: 28 Jul 2021
 *      Author: John Chee
 */

#include "Timers.h"
//=============================================================================
int main(void){


    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN); //config for 50MHz clock

    cl_timer0 oTimer0;

    //----- Test Set Period
    oTimer0.set_Period_us(100); //10..50000
    oTimer0.set_Period_ms(10); //1..60000

    //----- Test Control interrupts
    oTimer0.enable_Interrupt();
    oTimer0.disable_Interrupt();
    oTimer0.run_Timer0();

    while(1){

    }
}
//=============================================================================
