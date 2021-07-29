/*
 * ISR_Timers.h
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
 *
 *  Created on: 29 Jul 2021
 *      Author: John Chee
 */

#ifndef ISR_TIMERS_H_
#define ISR_TIMERS_H_

#include "LED_Dbg_RGB.h"
#include "Timers.h"
#include "ISR_mgr.h"


//.............................................................................
extern "C" {
interrupt void IRQ_Vector_Timer0();
} //ISR Vectors; for tm4c123gh6pm startup file
//.............................................................................

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class cl_isr_timer0 : public cl_isr_base{
public:
    cl_led_dbg_rgb oLED_Dbg;

    cl_isr_timer0(); //Ctor
    virtual void exec_isr(int iUsrID);
};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++




#endif /* ISR_TIMERS_H_ */
