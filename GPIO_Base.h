/** GPIO_Base.cpp
 * Abstract GPIO Base Class including blink function.
 * Inheriting this abstract class automatically provides many functions
 * including blinking.  A blink occurs when a pin goes high momentarily.
 * This is achieved by driving the pin high and when down count
 * reaches zero, drive back to low. Down count occurs in the function
 * ISR_exec_blink_10ms() at every 10ms IRQ. A blink counter supports multiple
 * blink specification.
 * Note:
 * 1. An abstract class can only be tested after being inherited by a
 * derived class. The functions of the abstract class then appear as functions
 * of the derived class.
 * 2. Private and protected functions can be accessed for unit testing by
 *    defining the token "Unit_Test_Mode". The macro functions then change the
 *    keyword "private" and "protected" into the keyword "public"
 * 3. The following are special consideration pins, that need to be unlock
 *    before being used as GPIOs
 *   Tiva Pins GPIO    Peripheral  Fn
 *    J2,p10   PA2     SSI0Clk
 *    J2,p9    PA3     SSI0Fss
 *    J2,p8    PA4     SSI0Rx
 *    J1,p8    PA5     SSI0Tx
 *    J2,p2    PB2     I2C0SCL
 *    J4,p3    PB3     I2C0SDA
 *    J4,p9    PD7     NMI,U2Tx
 *    J2,p4    PF0     NMI
 *
 *    -        PA0     U0Rx -Debug
 *    -        PA1     U0Tx -Debug
 *    -        PC0     TCk - JTAG
 *    -        PC1     TMS - JTAG
 *    -        PC2     TDI - JTAG
 *    -        PC3     TDO - JTAG
 *
 * 1.Example Usage (Base class is inherited into class cl_led_red_pf1)
 *    class cl_led_red_pf1 : public cl_gpio_base {
 *    private:
 *    public:
 *        cl_led_red_pf1();
 *        void drive_H(); //Drive pin High
 *        void drive_L(); //Drive pin Low
 *        bool is_drive_H();//1=Drive is in high state.
 *    };
 *
 * Created by: J Chee          J110
 */

#ifndef GPIO_BASE_H_
#define GPIO_BASE_H_

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

//!!! Uncomment the "#define ..." line if unit testing is reqd
//#define Unit_Test_Mode
//>>>>> Controls to select unit testing or production >>>>>>>>>>>>>>>>>>>>>>>>>
#ifdef Unit_Test_Mode
#define private public
#define protected public
#endif
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class cl_gpio_base{
private:
    uint8_t ui8_Cycle_DnCnt;  //CycleDnCnt>0 initiates pulse generation; starts sounding beeper
    uint32_t ui32_Period_DnCnt;  //Period Cnt>0 timeout to zero; decrements cycle cnt and turn on Led
    uint16_t ui16_Dur_DnCnt;  //Duration downcounts time out to zero, then beeper is turned off
    uint8_t ui8_DrvPinBitMap; //Drive Pin bit map pattern
protected:
    enum en_gpio_state_t {Idle, Setup, Run};
    en_gpio_state_t en_GPIO_State;

    virtual void start_blinking(); //Initiate generation of pulse train
    virtual uint8_t get_BlinkCnt(); //Get blink cnt from memory
    virtual uint16_t get_Duration_ms();//Get duration from memory
    virtual uint16_t get_Period_ms();//Get period from memory
    virtual bool isTriggered(); //1=trigger start of blink process
    virtual void clr_Trigger(); //1=clear trigger of blink process
public:
    cl_gpio_base() ; //Ctor
    ~cl_gpio_base() ; //Dtor
    //--- Basic Functions
    //-- Direct HW interaction
    virtual void drive_H() = 0; //Drive active pin High; HW dependent
    virtual void drive_L() = 0; //Drive active pin Low; HW dependent
    virtual bool is_GPIO_H() = 0; //1=Drive is in high state; HW dependent
    //-- Layered HW interaction
    void pulse_HL(); //Drive pin with a High-Low pulse -_ (600ns)
    void pulse2_HLHL(); //Drive pin with 2 pulses -_-_ (1.2 us)
    void toggle(); //Toggle drive on pin

    //--- State Machine Functions
    virtual void set_BlinkCnt(uint8_t ui8_UsrCnt);//Set repeat cnt
    virtual void set_Dur_ms(uint16_t ui16_UsrDuration);//Set duration for ON time in ms
    virtual void set_Period_ms(uint32_t ui32_UsrPeriod);//Set duration for repeat period in ms
    void blink(uint8_t ui8_UsrBlink_Cnt); //Trigger blink GPIO Pin a number of times
    void blink(uint8_t ui8_UsrBlink_Cnt, uint16_t ui16_UsrBlink_Period_ms); //Trigger bBlink GPIO Pin at this period
    void blink(); //Trigger Blink GPIO Pin for a number of times as stored in memory
    //¨¨SM execution - typ by Timer Interrupt service
    void exec_SM_blink_10ms(); //Execute generation of pulse train (in 10ms IRQ)
};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


#endif /* GPIO_BASE_H_ */
