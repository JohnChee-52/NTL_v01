/*
 * Timers.h
 * TimerO is set to be a periodic timer, typ 10ms period, for ISR servicing
 * The period may be adjusted, and interrupt response to end of period may
 * be eanbled or disabled.
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

//#include "ISR_mgr.h"

/*//.............................................................................
extern "C" {
interrupt void IRQ_Vector_Timer0();
} //ISR Vectors; for tm4c123gh6pm startup file
//.............................................................................

//^^^^^------------------------------------------------------------------------
interrupt void IRQ_Vector_Timer0(){//ISR Vector for tm4c123gh6pm startup file
    cl_isr_mgr::dispatch_ISR(ID_Timer0);
}
//^^^^^------------------------------------------------------------------------
*/


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
