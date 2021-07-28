/*
 * M_Valves.cpp
 * There are three valves used in NTL as follows:
 * 1. Bolus Valve (NC) – releases air from pressure chamber to form an air bolus.:
 * 2. Exhaust Valve  (NC)– releases air to exhaust chamber.
 * 3. Outlet Valve (NO) – closes outlet to check that air bolus generation.
 * The valves are electrically connected as shown
 * |------------------------------------------------|
 * |GPIO|Pin|Config  |MCU Control/Input lines |TIVA |
 * |------------------------------------------------|
 * |PB1 |p46|DO      |Drv_Valve_Bolus_PB1     |J1p4 |
 * |PB6 |p1 |DO      |Drv_Valve_Exhaust_PB6   |J2p7 |
 * |PE1 |p8 |DO      |Drv_Valve_TestBolus_PE1 |J3p7 |
 * |------------------------------------------------|
 *
 *  Created on: 21 Jul 2021
 *      Author: John Chee
 */

#include "Valves.h"

//=============================================================================
 int main(void){
    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN); //config for 50MHz clock

    cl_valves oValve;

    //----- Test valves
    //Using +5Vdc for Valve voltage (although the valves are rated for +6V)
    //Qualitatively, You will hear 3 sets of clicks
    // 1. Bolus valve x3 sharp clicks
    // 2. Exhaust valve x4 sharp clicks
    // 3. Outlet valve x5 soft clicks
    //A valve that response will generate a click which can be felt.
    //Current drawn when a valve is shown by the DC power supply.

    //-- Control of Bolus Valve
    for(int i=0;i<3;i++){ //Open close valve 3 times
        oValve.open_bolus_nc(); //incr by 232 mA
        SysCtlDelay(1000000); //120ms
        oValve.close_bolus_nc(); //incr by 0mA
        SysCtlDelay(1000000); //120ms
    }

    SysCtlDelay(14000000); //2s

    //-- Control of Exhaust Valve
    for(int i=0;i<4;i++){ //Open close valve 4 times
        oValve.open_exhaust_nc();//incr by 232 mA
        SysCtlDelay(1000000); //120ms
        oValve.close_exhaust_nc();//incr by 0mA
        SysCtlDelay(1000000); //120ms
    }

    SysCtlDelay(14000000); //2s

    //-- Control of Outlet Port Valve
    for(int i=0;i<5;i++){ //Close open valve 5 times
        oValve.close_outlet_no();//incr by 40 mA
        SysCtlDelay(1000000); //120ms
        oValve.open_outlet_no();//incr by 0mA
        SysCtlDelay(1000000); //120ms
    }


	while(1){
	    //Nothing to do
	}
}
//=============================================================================
