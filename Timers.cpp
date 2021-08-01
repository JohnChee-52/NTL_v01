/*
 * Timers.cpp
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

//::cc-------------------------------------------------------------------------
cl_timer0::cl_timer0(){ //Ctor, One-Shot, 32-bit DnCnt; enable IRQ
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0); //Enable Timer0 HW module
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0)){}; //Wait for module to be ready
    TimerConfigure(TIMER0_BASE,TIMER_CFG_PERIODIC); //Set Timer0 as 64-bit periodic

    ui32_Period_cnt = (SysCtlClockGet() * (uint64_t)(10)) / 1000; //Calc for 10ms
    TimerLoadSet(TIMER0_BASE, TIMER_A, (ui32_Period_cnt - 1));//Set timer0 to interrupt every 10ms
    IntEnable(INT_TIMER0A);//NVIC setup to respond Timer0 interrupt

    //Don't enable Timer0 interrupt so that it can be controlled in main()
    //TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT); //Allow Timer0 to accept interrupt
}
//::cc-------------------------------------------------------------------------

//--- Functions
//::---------------------------------------------------------------------------
void cl_timer0::set_Period_us(uint16_t ui16UsrPeriod_us){ //10..50000
    if(ui16UsrPeriod_us>50000) ui16UsrPeriod_us = 50000; //Limit max user range to 50000us
    if(ui16UsrPeriod_us<10) ui16UsrPeriod_us = 10; //Limit min user range to 10us
    ui32_Period_cnt = (SysCtlClockGet() * (uint64_t)(ui16UsrPeriod_us)) / 1000000; //Calc cnt value for timer0A
    TimerLoadSet(TIMER0_BASE, TIMER_A, ui32_Period_cnt - 1);//Set timer0A to interrupt every 700us (typ)
}
//::---------------------------------------------------------------------------
void cl_timer0::set_Period_ms(uint16_t ui16UsrPeriod_ms){ //1..60000
    if(ui16UsrPeriod_ms>60000) ui16UsrPeriod_ms = 60000; //Limit max user range to 60s
    if(ui16UsrPeriod_ms<1) ui16UsrPeriod_ms = 1; //Limit min user range to 1ms
    ui32_Period_cnt = (SysCtlClockGet() * (uint64_t)(ui16UsrPeriod_ms)) / 1000; //Calc cnt value for timer0A
    TimerLoadSet(TIMER0_BASE, TIMER_A, ui32_Period_cnt - 1);//Set timer0 to interrupt, typ every 0.5s
}
//::---------------------------------------------------------------------------
void cl_timer0::run_Timer0(void){
    TimerEnable(TIMER0_BASE, TIMER_A);//Enable Timer device to operate
}
//::---------------------------------------------------------------------------
void cl_timer0::stop_Timer0(void){
    TimerDisable(TIMER0_BASE, TIMER_A);//Disable Timer device to operate
}
//::---------------------------------------------------------------------------


//--- Interrupt control
//::---------------------------------------------------------------------------
void cl_timer0::enable_Interrupt(){
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);//interrupt upon TIMER0A timeout
}
//::---------------------------------------------------------------------------
void cl_timer0::disable_Interrupt(){
    TimerIntDisable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);//interrupt upon TIMER0A timeout
}
//::---------------------------------------------------------------------------



