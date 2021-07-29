

/**
 * main.c
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
