/*
 * Valves.h
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

#ifndef VALVES_H_
#define VALVES_H_

#include "Unit_Test_Mode.h"
#include "TM4C123GH6PM_Config_Pins.h"


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class cl_valves : cl_tm4c123gh6pm_pins{
private:
protected:
public:
    cl_valves(); //Ctor

private:
    //--- Bolus Valve
    void open_bolus_nc();
    void close_bolus_nc();

    //--- Exhaust Valve
    void open_exhaust_nc();
    void close_exhaust_nc();

    //--- Outlet Port Valve
    void open_outlet_no();
    void close_outlet_no();

};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


#endif /* VALVES_H_ */
