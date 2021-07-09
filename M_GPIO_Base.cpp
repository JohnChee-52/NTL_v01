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

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class cl_led_red_pf1 : public cl_gpio_base {
private:
protected:
    uint8_t ui8_Blink_Cnt;  //Default Blink Cnt
    uint16_t ui16_Duration_ms; //Default ON duration (ms)
    uint32_t ui32_Period_ms; //Default Period in a repeat cycle (ms)

    void start_blinking(); //Initiate generation of pulse train
    uint8_t get_BlinkCnt(); //Get blink cnt from memory
    uint16_t get_Duration_ms();//Get duration from memory
    uint16_t get_Period_ms();//Get period from memory
public:
    cl_led_red_pf1();
    void drive_H(); //Drive pin High
    void drive_L(); //Drive pin Low
    bool is_GPIO_H();//1=Drive is in high state.
    void set_BlinkCnt(uint8_t ui8_UsrCnt);//Set repeat cnt
    void set_Dur_ms(uint16_t ui16_UsrDuration);//Set duration for ON time in ms
    void set_Period_ms(uint32_t ui32_UsrPeriod);//Set duration for repeat period in ms
};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//cc---------------------------------------------------------------------------
cl_led_red_pf1::cl_led_red_pf1(){//Use Pin PF1 to drive Red LED
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); //enable GPIO port F
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1); //set port PF1 to drive Red LED
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);//switch off Red LED 324ns
}
//cc---------------------------------------------------------------------------
//::---------------------------------------------------------------------------
void cl_led_red_pf1::drive_H(){   //Drive active pin High
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);//switch on Red LED 324ns
}
//::---------------------------------------------------------------------------
void cl_led_red_pf1::drive_L(){ //Drive active pin Low
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);//switch on Red LED 324ns
}
//::---------------------------------------------------------------------------
bool cl_led_red_pf1::is_GPIO_H(){//1=Drive is in high state
    return GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_1);
}
//::---------------------------------------------------------------------------
void cl_led_red_pf1::set_BlinkCnt(uint8_t ui8_UsrCnt){ //Set blink cnt
    ui8_Blink_Cnt = ui8_UsrCnt;
}
//::---------------------------------------------------------------------------
void cl_led_red_pf1::set_Dur_ms(uint16_t ui16_UsrDuration){ //Set duration for ON time in ms
    ui16_Duration_ms = ui16_UsrDuration;
}
//::---------------------------------------------------------------------------
void cl_led_red_pf1::set_Period_ms(uint32_t ui32_UsrPeriod){ //Set duration for repeat period in ms
    ui32_Period_ms = ui32_UsrPeriod;
}
//::---------------------------------------------------------------------------
void cl_led_red_pf1::start_blinking(){ //Blink Led for a number of times as stored in memory
    en_GPIO_State = Setup;
}
//::---------------------------------------------------------------------------
uint8_t cl_led_red_pf1::get_BlinkCnt(){ //Get blink cnt from memory
    return ui8_Blink_Cnt;
}
//::---------------------------------------------------------------------------
uint16_t cl_led_red_pf1::get_Duration_ms(){//Get duration from memory
    return ui16_Duration_ms;
}
//::---------------------------------------------------------------------------
uint16_t cl_led_red_pf1::get_Period_ms(){//Get period from memory
    return ui32_Period_ms;
}
//::---------------------------------------------------------------------------

//=============================================================================
int main(){
    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN); //config for 40MHz clock

    //------- Test GPIO-Base class function (indirectly through LED's inherited functions)
    cl_led_red_pf1 oLED_Red_PF1; //Ctor: ui8_Blink_Cnt=3 ui16_Duration_ms=100 ui32_Period_ms=250

    oLED_Red_PF1.drive_H(); //LEDRed turns on
    oLED_Red_PF1.drive_L(); //LEDRed turns off
    oLED_Red_PF1.pulse_HL(); //LEDRed pulse once (800ns) -_
    oLED_Red_PF1.pulse2_HLHL(); //LEDRed pulses twice (1.2us) -_-_
    oLED_Red_PF1.toggle();//LEDRed turns on
    oLED_Red_PF1.toggle();//LEDRed turns off

#ifdef Unit_Test_Mode
    //Test private/protected functions
    oLED_Red_PF1.set_BlinkCnt(6); //.ui8_Blink_Cnt=6
    oLED_Red_PF1.start_blinking(); //.en_GPIO_State=Setup
#endif

    //----- Test function - primitive
    oLED_Red_PF1.set_Dur_ms(700); //.ui16_Duration_ms=700
    oLED_Red_PF1.set_Period_ms(1000); //.ui32_Period_ms=1000;
    oLED_Red_PF1.blink(5); //.ui8_Blink_Cnt=5;
    oLED_Red_PF1.blink(2, 300); //.ui8_Blink_Cnt=2; .ui32_Period_ms=300 .ui16_Duration_ms=150

    //----- Test functions - complex
    //-- Blink using parameters from memory
    oLED_Red_PF1.set_Dur_ms(20); //.ui16_Duration_ms=700
    oLED_Red_PF1.set_Period_ms(30); //.ui32_Period_ms=1000;
    oLED_Red_PF1.blink(); //Trigger blinking

    //--Simulate time-interrupt service of every 10ms
    //                                 LEDRed
    oLED_Red_PF1.exec_SM_blink_10ms(); //On
    oLED_Red_PF1.exec_SM_blink_10ms(); //On
    oLED_Red_PF1.exec_SM_blink_10ms();
    oLED_Red_PF1.exec_SM_blink_10ms(); //On
    oLED_Red_PF1.exec_SM_blink_10ms(); //On
    oLED_Red_PF1.exec_SM_blink_10ms();
    oLED_Red_PF1.exec_SM_blink_10ms();
    oLED_Red_PF1.exec_SM_blink_10ms();
    oLED_Red_PF1.exec_SM_blink_10ms();

    while(1){

    }
}
//=============================================================================
