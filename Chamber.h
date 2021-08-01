/*
 * Chamber.h
 * The chamber receives air from the pump and averages out pressure
 * fluctuations through its inherent capacitive effect. Fluctuations are
 * generated when air is being pumped in.
 * Chamber pressure is read and maintained at a fixed set point by turning
 * the pump motor on and off every 10 ms. The execution itself is performed
 * in ISR_Timer0_10ms.
 *
 *  Created on: 30 Jul 2021
 *      Author: John Chee
 */

#ifndef CHAMBER_H_
#define CHAMBER_H_

#include "Pump.h"
#include "Sensors.h"

//..... Limits.................................................................
#define MAX_Pressure_chamber_mmHg (80)
#define MAX_Duration_run_s (3600) //1 hour
#define DNCNT_DELAY 1   //Delay by downcounting ISR; to reduce on-duration for pump
//.............................................................................

//.............................................................................
struct st_sm_flags_t{
    bool bF_Run;
    bool bF_req_Abort;

};
//.............................................................................
//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
enum en_state_maintain_pressure_t {
    en_S0_Setup_mp,     //S0->S1
    en_S1_Decide_mp,    //S1->S2|S3|S4
    en_S2_PumpOn_mp,    //S2->S1|S4
    en_S3_PumpOff_mp,   //S3->S1|S4
    en_S4_WrapUp_mp,    //S4->S5
    en_S5_Idle_mp       //S5.
};
//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class cl_chamber {
private:
    uint32_t ui32_DnCnt_dur_10ms;

    //-- SM Cnt Trackers
    static uint32_t ui32_CntCyc_SM_maintain_pressure;
    static uint32_t ui32_CntCyc_SM_incr_pressure;
    static uint32_t ui32_CntCyc_SM_decr_pressure;
    static uint32_t ui32_CntCyc_SM_pump_dur;
    static uint32_t ui32_CntCyc_SM_exhaust_dur;

    //todo
    static uint16_t u16_DnCnt_Delay;
protected:
public:
    //----- Imported Objects
    cl_pump oPump;
    cl_sensors oSensors;

    //----- Flags
    static st_sm_flags_t st_SMF_maintain_pressure;
    static st_sm_flags_t st_SMF_incr_pressure;
    static st_sm_flags_t st_SMF_decr_pressure;
    static st_sm_flags_t st_SMF_pump_dur;
    static st_sm_flags_t st_SMF_exhaust_dur;

    //----- SM State Vars
    static en_state_maintain_pressure_t en_State_maintain_pressure;

    //----- Vars
    static uint16_t ui16_SetPt_mmHg;
    static uint16_t ui16_Thresh_mmHg;
    static uint32_t ui32_Dur_ms;
    static uint16_t ui16_Curr_Pressure_mmHg;


    cl_chamber(); //Ctor

    //------- Pressure-related functions
    //-- Set & read SetPt_pressure
    void set_SetPt_pressure_mmHg(uint16_t ui16Usr_SetPt_mmHg);
    uint16_t read_SetPt_pressure_mmHg();

    //-- Set & read Thresh_pressure
    void set_Thresh_pressure_mmHg(uint16_t ui16Usr_SetPt_mmHg);
    uint16_t read_Thresh_pressure_mmHg();

    //------- Time-related functions
    //-- Set & read dur
    void set_Dur_ms(uint32_t ui32Usr_Dur_ms);
    uint32_t read_Dur_ms();


    //------- State Machines -------
    //----- SMs on pressure -----
    //-- sm maintain pressure
    void trig_maintain_pressure_at_SetPt_mmHg(uint16_t ui16Usr_SetPt_mmHg);
    void abort_maintain_pressure_at_SetPt_mmHg();
    uint32_t exec_sm_maintain_Pressure_at_SetPt_mmHg();

    //-- sm incr pressure
    void trig_incr_pressure_to_mmHg(uint16_t ui16Usr_Thresh_mmHg);
    void abort_incr_pressure_to_mmHg();
    uint32_t exec_sm_increase_to_Pressure_mmHg();

    //-- sm decr pressure
    void trig_decr_pressure_to_mmHg(uint16_t ui16Usr_Thresh_mmHg);
    void abort_decr_pressure_to_mmHg();
    uint32_t exec_sm_decrease_to_Pressure_mmHg();

    //----- SM on time -----
    //-- sm pump duration
    void trig_pump_for_Dur_ms(uint32_t ui32Usr_Dur_ms);
    void abort_pump_for_Dur_ms();
    uint32_t exec_sm_pump_for_Dur_ms();

    //-- sm exhaust duration
    void trig_exhaust_for_Dur_ms(uint32_t ui32Usr_Dur_ms);
    void abort_exhaust_for_Dur_ms();
    uint32_t exec_sm_exhaust_for_Dur_ms();
};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



#endif /* CHAMBER_H_ */
