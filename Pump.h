/*
 * Pump.h
 * Only one pump is used in NTL.
 *
 * ------------------------------------------------|
 * GPIO|Pin|Config  |MCU Control/Input lines |TIVA |
 * ------------------------------------------------|
 * PE4 |p59|PWM2    |Drv_AirPump_PE4         |J1p5 |
 * ------------------------------------------------|
 *
 *  Created on: 22 Jul 2021
 *      Author: John Chee
 */

#ifndef PUMP_H_
#define PUMP_H_

#include "Unit_Test_Mode.h"
#include "TM4C123GH6PM_Config_Pins.h"


 //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 class cl_pump : cl_tm4c123gh6pm_pins{ //exclude until receive H-drive IC
 private:
 protected:
 public:
     cl_pump(); //Ctor

     void turn_On();
     void turn_Off();

 };
 //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



#endif /* PUMP_H_ */
