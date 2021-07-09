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

#include "GPIO_Base.h"
/*
//... Instantiate static variables ............................................
//en_gpio_state_t cl_gpio_base::en_GPIO_State;
//.............................................................................
*/
//cc---------------------------------------------------------------------------
cl_gpio_base::cl_gpio_base() {//Use GPIO PF1 as Red LED
    en_GPIO_State = Idle;
//    ui8_Blink_Cnt = 3;  //3=Default Blink Cnt
//    ui16_Duration_ms = 200; //100=Default High duration (ms)
//    ui32_Period_ms = 500; //250=Default Period in a repeat cycle (ms)
//    bF_BlinkMode = false; //Default - not in blink mode
}
//cc---------------------------------------------------------------------------
//~cc--------------------------------------------------------------------------
cl_gpio_base::~cl_gpio_base(){ //Dtor
    //Nil
}
//~cc--------------------------------------------------------------------------
//::---------------------------------------------------------------------------
void cl_gpio_base::pulse_HL(){ //Drive pin with a High-Low pulse -_ (600ns)
    drive_H();
    drive_L();
}
//::---------------------------------------------------------------------------
void cl_gpio_base::pulse2_HLHL(){ //Drive pin with 2 pulses -_-_ (1.2 us)
    drive_H();
    drive_L();
    drive_H();
    drive_L();
}
//::---------------------------------------------------------------------------
void cl_gpio_base::toggle(){ //Toggle drive on pin
    if(is_GPIO_H()){
        drive_L();
    }else{
        drive_H();
    }
}
//::---------------------------------------------------------------------------
void cl_gpio_base::set_BlinkCnt(uint8_t ui8_UsrCnt){ //Set blink cnt
//    ui8_Blink_Cnt = ui8_UsrCnt;
}
//::---------------------------------------------------------------------------
void cl_gpio_base::set_Dur_ms(uint16_t ui16_UsrDuration){ //Set duration for ON time in ms
//    ui16_Duration_ms = ui16_UsrDuration;
}
//::---------------------------------------------------------------------------
void cl_gpio_base::set_Period_ms(uint32_t ui32_UsrPeriod){ //Set duration for repeat period in ms
//    ui32_Period_ms = ui32_UsrPeriod;
}
//::---------------------------------------------------------------------------
void cl_gpio_base::start_blinking(){ //Blink Led for a number of times as stored in memory
    en_GPIO_State = Setup;
}
//::---------------------------------------------------------------------------
void cl_gpio_base::blink(){//Blink Led for a number of times as stored in memory
    start_blinking();
}
//::---------------------------------------------------------------------------
void cl_gpio_base::blink(uint8_t ui8_UsrBlink_Cnt){ //Blink Led a number of times
    set_BlinkCnt(ui8_UsrBlink_Cnt); //Set repeat cnt
    start_blinking();
}
//::---------------------------------------------------------------------------
void cl_gpio_base::blink(uint8_t ui8_UsrBlink_Cnt, uint16_t ui16_UsrBlink_Period_ms){ //Blink Led at this period
    set_Period_ms(ui16_UsrBlink_Period_ms); //Set duration for repeat period in ms    start_blink();
    set_Dur_ms(ui16_UsrBlink_Period_ms / 2); //Set duration for half of period
    set_BlinkCnt(ui8_UsrBlink_Cnt); //Set repeat cnt
    start_blinking();
}
//::---------------------------------------------------------------------------
uint8_t cl_gpio_base::get_BlinkCnt(){ //Get blink cnt from memory
    return 0; //Virtual fn, dummy
}
//::---------------------------------------------------------------------------
uint16_t cl_gpio_base::get_Duration_ms(){//Get duration from memory
    return 0; //Virtual fn, dummy
}
//::---------------------------------------------------------------------------
uint16_t cl_gpio_base::get_Period_ms(){//Get period from memory
    return 0; //Virtual fn, dummy
}
//::---------------------------------------------------------------------------
bool cl_gpio_base::isTriggered(){ //1=trigger start of blink process
    return false; //Virtual fn, dummy
}
//::---------------------------------------------------------------------------
void cl_gpio_base::clr_Trigger(){ //1=clear trigger of blink process
    //Virtual fn, dummy
}
//::---------------------------------------------------------------------------
//::---------------------------------------------------------------------------
void cl_gpio_base::exec_SM_blink_10ms(){ //Execute generation of pulse train (in 10ms IRQ)
    switch(en_GPIO_State){
    case Setup:
        ui8_Cycle_DnCnt = get_BlinkCnt();
        ui16_Dur_DnCnt = get_Duration_ms() / 10; //Assuming 10ms interrupt
        ui32_Period_DnCnt = get_Period_ms() / 10; //Assuming 10ms interrupt
        en_GPIO_State = Run; //----->> Continue immediatedly to next state
    case Run: //GPIO pin is H only when ui16_Duration_DnCnt>0
        if(ui16_Dur_DnCnt > 0){
            drive_H();//GPIO pin goes H
            ui16_Dur_DnCnt--;
        } else {
            drive_L();//GPIO pin goes L
        }

        if(ui32_Period_DnCnt > 0){ //Decr Period Cnt
            ui32_Period_DnCnt--;
            if (ui32_Period_DnCnt == 0){
                ui16_Dur_DnCnt = get_Duration_ms() / 10; //Reset Duration
                ui32_Period_DnCnt = get_Period_ms() / 10; //Assuming 10ms interrupt
                if(ui8_Cycle_DnCnt > 0){
                    ui8_Cycle_DnCnt--;
                    if(ui8_Cycle_DnCnt == 0){
                        en_GPIO_State = Idle; //----->>Idle, as all blinks are done
                    }
                }
            }
        }
        break;
    case Idle:
        if(isTriggered()){
            en_GPIO_State = Setup;
            clr_Trigger();
        }
        //do nothing
        break;
    }
}
//::---------------------------------------------------------------------------


