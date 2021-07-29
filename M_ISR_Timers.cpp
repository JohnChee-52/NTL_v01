/*
 * M_ISR_Timers.cpp
 * This module is for the user to use, and so it will change as project develops.
 * For an Interrupt Service Routine (ISR) to be served by an interrupt it
 * must have its ID defined in ISR_Register.h, and the ISR manager must
 * register ISR during program initialisation in main().
 * In addition, an interrupt vector function must be written which tells the
 * ISR manager to dispatch its address when responding to the interrupt.
 * The vector function must then be recorded in the project start-up file.
 * Working example: For Timer0A
 *  In ISR_Register.h, the ISR is registered as ID_Timer0.
 *  In main(), the ISR manager registers this ID together with the ISR’s address.
 *      oIsrMgr.register_ISR(ID_Timer0, &oISR_Timer0);
 *  In ISR_Timers.h, the interrupt vector is declared in “C” format using
 *      extern "C" {interrupt void IRQ_Vector_Timer0();}
 *  In ISR_timers.cpp the interrupt vector is defined:
 *      interrupt void IRQ_Vector_Timer0(){cl_isr_mgr::dispatch_ISR(ID_Timer0);}
 *  In the project start-up file tm4c123gh6pm_start-up_ccs.c, the vector is
 *  recorded two locations:
 *      1)  extern void IRQ_Vector_Timer0(); at line 57
 *      2)  IRQ_Vector_Timer0,   // Timer 0 subtimer A at line 106
 *  Also in main(), both device and master level interrupts must be enabled:
 *      oTimer0.enable_Interrupt();
 *      IntMasterEnable();//Enable all interrupt system to generate interrupts
 *
 *  Created on: 29 Jul 2021
 *      Author: John Chee
 */


#include <ISR_Timers.h>
#include "LED_Dbg_RGB.h"

//=============================================================================
int main(){
    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN); //config for 50MHz clock

    cl_led_dbg_rgb oLED_Dbg; //Ctor
    oLED_Dbg.on_Red(); //PF1 | Tiva J3,p10
    oLED_Dbg.off_Red();

    cl_timer0 oTimer0; //1ms timebase, ready for interrupt
    oTimer0.set_Period_us(100);

    cl_isr_mgr oIsrMgr;
    cl_isr_timer0 oISR_Timer0; //Construct Timer interrupt service object


    oIsrMgr.register_ISR(ID_Timer0, &oISR_Timer0); //.apcl_VTable[0]=0x200001F0

    oTimer0.enable_Interrupt();
    oTimer0.run_Timer0();

    IntMasterEnable();//Enable all interrupt system to generate interrupts

    while(1){
        //Use oscilloscope to observe a 270ns pulse every 100 us at PF1 (J3p10)
    }
}
//=============================================================================
