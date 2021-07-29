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

#include "ISR_mgr.h"


//... Instantiate Static Objects ..............................................
cl_isr_mgr::pcl_isr_t cl_isr_mgr::apcl_VTable[iNo_of_ISRs]; //Vector table for class addrs
//.............................................................................
//-----------------------------------------------------------------------------
cl_isr_mgr::cl_isr_mgr(){ //ctor
//Nil
}
//-----------------------------------------------------------------------------
void cl_isr_mgr::register_ISR(int iUsrID, cl_isr_mgr::pcl_isr_t pcl_UsrISR){
    cl_isr_mgr::apcl_VTable[iUsrID] = pcl_UsrISR;
}
//-----------------------------------------------------------------------------
void cl_isr_mgr::dispatch_ISR(int iUsrID){
     cl_isr_mgr::apcl_VTable[iUsrID]->exec_isr(iUsrID);//Invoke ISR via virtual call
}
//-----------------------------------------------------------------------------

