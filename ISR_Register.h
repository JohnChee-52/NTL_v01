/** ISR_Register.cpp
 * This class registers the ISRs in use and gives each one a unique ID
 *
 * Created by: JChee        I906 rev K712
 */

#ifndef ISR_REGISTER_H_
#define ISR_REGISTER_H_

//***** User Defined IDs ************************************************
enum en_ISR_ID {
    ID_Timer0,
    ID_Sw1,
    ID_Sw2,
    ID_Sw3,
    ID_Sw4,
    ID_Sw5,
    ID_Sw6,
    ID_UART2,
    ID_RS485,
    ID_CPanel,
    ID_SysTick
};
const int iNo_of_ISRs = 11;
//*****************************************************************************


#endif /* ISR_REGISTER_H_ */
