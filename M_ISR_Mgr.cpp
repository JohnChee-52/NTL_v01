/** ISR_Mgr.cpp
 * ISR callback with full C++ flexibility.
 * C++ functions are accessed indirectly via the "this" pointer. This
 * access mode is incompatible with the way an MCU accesses interrupt
 * service functions (ISRs), which is by directly executing the functions
 * whose addresses are stored in startup file. To overcome this incompatiblity,
 * pseudo-ISR addresses are stored instead. The MCU executes the pseudo-ISR
 * which calls a helper function to dispatch the actual ISR for execution.
 * The ISR address is fetched from the vector table of function pointers
 * managed by an ISR_manager. The table is populated at run time during program
 * initialisation by calling the ISR_manager to register the addresses of
 * actual ISRs.
 * The whole process of setting up the interrupt system is summarised as follows:
 * 1. Create an ISR class with inheritance from an abstract base class
 *    to ensure interface compatibility across all other ISR classes.
 * 2. Write the actual ISR code within the derived class' execute-isr
 *    function ie within  "void exec_isr(int iUsrID);" where "UsrId" is the
 *    offset position where the ISR address is stored in the ISR manager's
 *    vector table.
 * 3. Create an IRQ Vector ("C" compatible) which points the isr_mgr's
 *    static dispatch function "void dispatch_ISR(int iUsrID);"
 * 4. Register the IRQ Vector in the startup file corrs to that hw
 *    subsystem that will generate the interrupt.
 * 5. In the main program, define each of the derived classes' positions
 *    in the vector table of ISR manager by using "enum" to generate
 *    sequential UsrIds (corrs to the offset positions in the table).
 * 6. Declare objects of the ISR derived classes to construct the objects.
 * 7. Register the address of each ISR object into the vector table via
 *    the ISR_manager's fn: "register_ISR(int iUsrID, pcl_isr_t pcl_UsrISR);"
 * 8. Enable the interrupts of various MCU subsystems in use, so that the
 *    MCU will respond to subsystem requests for interrupt service.
 * When the code is written properly (correctly) and run, whenever an
 * interrupt occurs, the IRQ vector causes the ISR Mgr to select the
 * function pointer from its vector table, and run the ISR function that the
 * pointer points to.

 *
 * Ref: Scott Meyers "Effective C++ in an embedded environment"(2012)
 * Created by:  JChee       I904    rev I909
 */

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

#include "inc/tm4c123gh6pm.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"

#include "LED_Dbg_RGB.h"
#include "Timers.h"

#include "ISR_mgr.h"

//Note: cl_timer_isr, cl_switch_isr are dummy classes to test out cl_isr_mgr


//TT----- Test-setup codes ----------------------------------------------------

extern "C" { //IRQ Vector to be declared in 2 parts in "tm4c123gh6pm_startup_ccs.c" file
interrupt void IRQ_Vector_Timer0();
}//

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class cl_timer_isr : public cl_isr_base{
public:
    cl_led_dbg_rgb oLED_Dbg; //Ctor

    cl_timer_isr(); //Ctor
    virtual void exec_isr(int iUsrID);
};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//::cc-------------------------------------------------------------------------
cl_timer_isr::cl_timer_isr(){ //Ctor
}
//::cc-------------------------------------------------------------------------
//::---------------------------------------------------------------------------
void cl_timer_isr::exec_isr(int iUsrID){//write interrupt servicing code here
    TimerIntClear(TIMER0_BASE,TIMER_TIMA_TIMEOUT);//clear timer0A interrupt
    oLED_Dbg.on_Red();  //trig on PF1 (Tiva J3p10) to check timing
    oLED_Dbg.off_Red(); //Set breakpoint here to view Red LED light up
}
//::---------------------------------------------------------------------------
//^^irq------------------------------------------------------------------------
interrupt void IRQ_Vector_Timer0(){//IRQ Vector for tm4c123gh6pm startup file
    cl_isr_mgr::dispatch_ISR(ID_Timer0);
}
//^^irq------------------------------------------------------------------------
//TT----- End of Test-setup Codes ---------------------------------------------



//=============================================================================
int main(){
    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN); //config for 50MHz clock

    cl_led_dbg_rgb oLED_Dbg; //Ctor
    oLED_Dbg.on_Red();
    oLED_Dbg.off_Red();

    cl_timer0 oTimer0; //1ms timebase, ready for interrupt
    oTimer0.set_Period_us(100);

    cl_isr_mgr oIsrMgr;
    cl_timer_isr oTimerISR; //Construct Timer interrupt service object


    oIsrMgr.register_ISR(ID_Timer0, &oTimerISR); //.apcl_VTable[0]=0x200001F0

    oTimer0.enable_Interrupt();
    oTimer0.run_Timer0();

    IntMasterEnable();//Enable all interrupt system to generate interrupts

    while(1){
    }
}
//=============================================================================




