/*
 * ISR_Timers.cpp
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

//^^^^^------------------------------------------------------------------------
interrupt void IRQ_Vector_Timer0(){//ISR Vector for tm4c123gh6pm startup file
    cl_isr_mgr::dispatch_ISR(ID_Timer0);
}
//^^^^^------------------------------------------------------------------------

//::cc-------------------------------------------------------------------------
cl_isr_timer0::cl_isr_timer0(){ //Ctor

}
//::cc-------------------------------------------------------------------------

//::---------------------------------------------------------------------------
void cl_isr_timer0::exec_isr(int iUsrID){
    uint16_t ui16_Pressure_chamber_mmHg[5];

    TimerIntClear(TIMER0_BASE,TIMER_TIMA_TIMEOUT);//clear timer0A interrupt
    oLED_Dbg.on_Red();

    oChamber.exec_sm_maintain_Pressure_at_SetPt_mmHg();

/*
    oChamber.oPump.turn_On();
    oChamber.oPump.turn_Off();

    ui16_Pressure_chamber_mmHg[0] = oChamber.oSensors.sense_ChamberPress_mmHg();
    ui16_Pressure_chamber_mmHg[1] = oChamber.oSensors.sense_ChamberPress_mmHg();
    ui16_Pressure_chamber_mmHg[2] = oChamber.oSensors.sense_ChamberPress_mmHg();
    ui16_Pressure_chamber_mmHg[3] = oChamber.oSensors.sense_ChamberPress_mmHg();
    ui16_Pressure_chamber_mmHg[4] = oChamber.oSensors.sense_ChamberPress_mmHg();
*/

    oLED_Dbg.off_Red();

}
//::---------------------------------------------------------------------------

