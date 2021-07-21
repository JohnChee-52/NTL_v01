/*
 * Valves.cpp
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

//::cc-------------------------------------------------------------------------
cl_valves::cl_valves(){ //Ctor

}
//::cc-------------------------------------------------------------------------

//--- Bolus Valve
//::---------------------------------------------------------------------------
void cl_valves::open_bolus_nc(){
    drv_H_PB1();
}
//::---------------------------------------------------------------------------
void cl_valves::close_bolus_nc(){
    drv_L_PB1();
}
//::---------------------------------------------------------------------------

//--- Exhaust Valve
//::---------------------------------------------------------------------------
void cl_valves::open_exhaust_nc(){
    drv_H_PB6();
}
//::---------------------------------------------------------------------------
void cl_valves::close_exhaust_nc(){
    drv_L_PB6();
}
//::---------------------------------------------------------------------------

//--- Outlet Port Valve
//::---------------------------------------------------------------------------
void cl_valves::open_outlet_no(){
    drv_L_PE1();
}
//::---------------------------------------------------------------------------
void cl_valves::close_outlet_no(){
    drv_H_PE1();
}
//::---------------------------------------------------------------------------

