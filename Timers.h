/*
 * Timers.h
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

#ifndef TIMERS_H_
#define TIMERS_H_


#include "Unit_Test_Mode.h"
#include "TM4C123GH6PM_Config_Pins.h"
#include "inc/tm4c123gh6pm.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class cl_timer0{
private:
    uint32_t ui32_Period_cnt; //counts required for timer to generate a period typ 10ms
protected:
public:

    cl_timer0();//Ctor, Periodic, 32-bit DnCnt; enable IRQ

    //--- Functions
    void set_Period_us(uint16_t ui16UsrPeriod_us); //10..50000
    void set_Period_ms(uint16_t ui16UsrPeriod_ms); //1..60000
    static void run_Timer0();
    static void stop_Timer0();

    //--- Interrupt control
    static void enable_Interrupt();
    static void disable_Interrupt();

};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



#endif /* TIMERS_H_ */
