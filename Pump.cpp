/*
 * Pump.cpp
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

#include "Pump.h"

//::cc-------------------------------------------------------------------------
cl_pump::cl_pump(){ //Ctor

}
//::cc-------------------------------------------------------------------------

//::---------------------------------------------------------------------------
void cl_pump::turn_On(){
    drv_H_PE4();
}
//::---------------------------------------------------------------------------
void cl_pump::turn_Off(){
    drv_L_PE4();
}
//::---------------------------------------------------------------------------

/*
//::cc-------------------------------------------------------------------------
cl_pump::cl_pump(){ //Ctor
    //!---- this config is not needed when H-bridge is used, because  TM4C123gh6pm has configured it for PWM
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE); //enable GPIO port E
    MAP_GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_4); //Overwrite prev config
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_4); //set port PE4 to DO
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_4, 0);//Drive to L
    //!----
}
//::cc-------------------------------------------------------------------------

//::---------------------------------------------------------------------------
void cl_pump::turn_On(){
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_4, GPIO_PIN_4);//Drive to H
}
//::---------------------------------------------------------------------------
void cl_pump::turn_Off(){
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_4, 0);//Drive to L
}
//::---------------------------------------------------------------------------
*/
