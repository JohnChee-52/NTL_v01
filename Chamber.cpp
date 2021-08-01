/*
 * Chamber.cpp
 *
 *  Created on: 30 Jul 2021
 *      Author: John Chee
 */

#include "Chamber.h"

//..... Instantiate Static Variables ..........................................
//--Flags
st_sm_flags_t cl_chamber::st_SMF_maintain_pressure;
st_sm_flags_t cl_chamber::st_SMF_incr_pressure;
st_sm_flags_t cl_chamber::st_SMF_decr_pressure;
st_sm_flags_t cl_chamber::st_SMF_pump_dur;
st_sm_flags_t cl_chamber::st_SMF_exhaust_dur;
//-- SM Cnt Trackers
uint32_t cl_chamber::ui32_CntCyc_SM_maintain_pressure;
uint32_t cl_chamber::ui32_CntCyc_SM_incr_pressure;
uint32_t cl_chamber::ui32_CntCyc_SM_decr_pressure;
uint32_t cl_chamber::ui32_CntCyc_SM_pump_dur;
uint32_t cl_chamber::ui32_CntCyc_SM_exhaust_dur;
//----- SM State Vars
en_state_maintain_pressure_t cl_chamber::en_State_maintain_pressure;
//-- Vars
uint16_t cl_chamber::u16_DnCnt_Delay;

uint16_t cl_chamber::ui16_SetPt_mmHg;
uint16_t cl_chamber::ui16_Thresh_mmHg;
uint32_t cl_chamber::ui32_Dur_ms;
uint16_t cl_chamber::ui16_Curr_Pressure_mmHg;
//.............................................................................

//::cc-------------------------------------------------------------------------
cl_chamber::cl_chamber(){ //Ctor
    //-- SM Cnt Trackers
    ui32_CntCyc_SM_maintain_pressure = 0;
    ui32_CntCyc_SM_incr_pressure = 0;
    ui32_CntCyc_SM_decr_pressure = 0;
    ui32_CntCyc_SM_pump_dur = 0;
    ui32_CntCyc_SM_exhaust_dur = 0;

    //-- SM states
    en_State_maintain_pressure = en_S5_Idle_mp;

    //-- Vars
    ui16_SetPt_mmHg = 30;
    ui16_Curr_Pressure_mmHg = oSensors.sense_ChamberPress_mmHg();
    u16_DnCnt_Delay = DNCNT_DELAY;
}
//::cc-------------------------------------------------------------------------

//------- Pressure-related functions
//-- Set & read SetPt_pressure
//::---------------------------------------------------------------------------
void cl_chamber::set_SetPt_pressure_mmHg(uint16_t ui16Usr_SetPt_mmHg){
    if (ui16Usr_SetPt_mmHg > MAX_Pressure_chamber_mmHg) {//Limit
        ui16Usr_SetPt_mmHg = MAX_Pressure_chamber_mmHg;
    }

    ui16_SetPt_mmHg = ui16Usr_SetPt_mmHg;
}
//::---------------------------------------------------------------------------
uint16_t cl_chamber::read_SetPt_pressure_mmHg(){
    return ui16_SetPt_mmHg;
}
//::---------------------------------------------------------------------------
//-- Set & read Thresh_pressure
//::---------------------------------------------------------------------------
void cl_chamber::set_Thresh_pressure_mmHg(uint16_t ui16Usr_Thresh_mmHg){
    if (ui16Usr_Thresh_mmHg > MAX_Pressure_chamber_mmHg) {//Limit
        ui16Usr_Thresh_mmHg = MAX_Pressure_chamber_mmHg;
    }

    ui16_Thresh_mmHg = ui16Usr_Thresh_mmHg;
}
//::---------------------------------------------------------------------------
uint16_t cl_chamber::read_Thresh_pressure_mmHg(){
    return ui16_Thresh_mmHg;
}
//::---------------------------------------------------------------------------


//------- Time-related functions
//-- Set & read dur
void cl_chamber::set_Dur_ms(uint32_t ui32Usr_Dur_ms){
    ui32_Dur_ms = ui32Usr_Dur_ms; //div by 10 because this will be used in ISR 10ms
}
//::---------------------------------------------------------------------------
uint32_t cl_chamber::read_Dur_ms(){
    return (ui32_Dur_ms);
}
//::---------------------------------------------------------------------------



//------- State Machines -------
//----- SMs on pressure -----

//-- Trig & abort maintain pressure
//::---------------------------------------------------------------------------
void cl_chamber::trig_maintain_pressure_at_SetPt_mmHg(uint16_t ui16Usr_SetPt_mmHg){
    set_SetPt_pressure_mmHg(ui16Usr_SetPt_mmHg);
    st_SMF_maintain_pressure.bF_Run = true;
    st_SMF_maintain_pressure.bF_req_Abort = false;
    en_State_maintain_pressure = en_S0_Setup_mp;
}
//::---------------------------------------------------------------------------
void cl_chamber::abort_maintain_pressure_at_SetPt_mmHg(){
    st_SMF_maintain_pressure.bF_req_Abort = true;
}
//::---------------------------------------------------------------------------
//-- sm maintain pressure
//todo
//::sm------------------------------------------------------------------------
uint32_t cl_chamber::exec_sm_maintain_Pressure_at_SetPt_mmHg(){
    if (st_SMF_maintain_pressure.bF_Run){
        ui32_CntCyc_SM_maintain_pressure++;

        switch(en_State_maintain_pressure){
        case en_S0_Setup_mp:     //S0->S1
            ui16_Curr_Pressure_mmHg = oSensors.sense_ChamberPress_mmHg();
            en_State_maintain_pressure = en_S1_Decide_mp; //-->change state
            break;

        case en_S1_Decide_mp:    //S1->S2|S3|S4
            if (ui16_Curr_Pressure_mmHg < ui16_SetPt_mmHg){
                u16_DnCnt_Delay = DNCNT_DELAY;
                oPump.turn_On();
                en_State_maintain_pressure = en_S2_PumpOn_mp; //-->change state S1->S2
            }else{
                oPump.turn_Off();
                en_State_maintain_pressure = en_S3_PumpOff_mp; //-->change state S1->S3
            }
            if(st_SMF_maintain_pressure.bF_req_Abort){
                oPump.turn_Off(); //redundant, precaution
                en_State_maintain_pressure = en_S4_WrapUp_mp; //-->change state S1->S4
            }
            break;

        case en_S2_PumpOn_mp:    //S2->S1|S4
            oPump.turn_Off();
            if(u16_DnCnt_Delay > 0){
                u16_DnCnt_Delay --;
            }else{ //u16_DnCnt_Delay == 0
                ui16_Curr_Pressure_mmHg = oSensors.sense_ChamberPress_mmHg();
                en_State_maintain_pressure = en_S1_Decide_mp; //-->change state S2->S1
            }

            if(st_SMF_maintain_pressure.bF_req_Abort){
                oPump.turn_Off(); //redundant, precaution
                en_State_maintain_pressure = en_S4_WrapUp_mp; //-->change state S1->S4
            }
            break;

        case en_S3_PumpOff_mp:   //S3->S1|S4
            ui16_Curr_Pressure_mmHg = oSensors.sense_ChamberPress_mmHg();
            en_State_maintain_pressure = en_S1_Decide_mp; //-->change state S3->S1

            if(st_SMF_maintain_pressure.bF_req_Abort){
                en_State_maintain_pressure = en_S4_WrapUp_mp; //-->change state S1->S4
            }
            break;

        case en_S4_WrapUp_mp:    //S4->S5
            st_SMF_maintain_pressure.bF_Run = false;
            st_SMF_maintain_pressure.bF_req_Abort = false;
            en_State_maintain_pressure = en_S5_Idle_mp; //-->change state S3->S4
            break;

        case en_S5_Idle_mp:      //S5.
            //Nothing to do
            break;

        }
    }
    return ui32_CntCyc_SM_maintain_pressure;
}
//::sm------------------------------------------------------------------------




//-- Trig & abort incr pressure
//::---------------------------------------------------------------------------
void cl_chamber::trig_incr_pressure_to_mmHg(uint16_t ui16Usr_Thresh_mmHg){
    set_Thresh_pressure_mmHg(ui16Usr_Thresh_mmHg);
    st_SMF_incr_pressure.bF_Run = true;
}
//::---------------------------------------------------------------------------
void cl_chamber::abort_incr_pressure_to_mmHg(){
    st_SMF_incr_pressure.bF_req_Abort = true;
}
//::---------------------------------------------------------------------------
//-- sm incr pressure
//::---------------------------------------------------------------------------
uint32_t cl_chamber::exec_sm_increase_to_Pressure_mmHg(){

}
//::---------------------------------------------------------------------------



//-- Trig & abort decr pressure
//::---------------------------------------------------------------------------
void cl_chamber::trig_decr_pressure_to_mmHg(uint16_t ui16Usr_Thresh_mmHg){
    set_Thresh_pressure_mmHg(ui16Usr_Thresh_mmHg);
    st_SMF_decr_pressure.bF_Run = true;
}
//::---------------------------------------------------------------------------
void cl_chamber::abort_decr_pressure_to_mmHg(){
    st_SMF_decr_pressure.bF_req_Abort = true;
}
//::---------------------------------------------------------------------------
//-- sm decr pressure
//::---------------------------------------------------------------------------
uint32_t cl_chamber::exec_sm_decrease_to_Pressure_mmHg(){

}
//::---------------------------------------------------------------------------



//----- SMs on time -----
//-- Trig & abort pumping
//::---------------------------------------------------------------------------
void cl_chamber::trig_pump_for_Dur_ms(uint32_t ui32Usr_Dur_ms){
    if (ui32Usr_Dur_ms > (MAX_Duration_run_s * 1000)) {//Limit
        ui32Usr_Dur_ms = (MAX_Duration_run_s * 1000);
    }
    ui32_Dur_ms = ui32Usr_Dur_ms;

    st_SMF_pump_dur.bF_Run = true;
}
//::---------------------------------------------------------------------------
void cl_chamber::abort_pump_for_Dur_ms(){
    st_SMF_pump_dur.bF_req_Abort = true;
}
//::---------------------------------------------------------------------------
//-- sm pump duration
//::---------------------------------------------------------------------------
uint32_t cl_chamber::exec_sm_pump_for_Dur_ms(){

}
//::---------------------------------------------------------------------------



//-- Trig & abort exhausting
//::---------------------------------------------------------------------------
void cl_chamber::trig_exhaust_for_Dur_ms(uint32_t ui32Usr_Dur_ms){
    if (ui32Usr_Dur_ms > (MAX_Duration_run_s * 1000)) {//Limit
        ui32Usr_Dur_ms = (MAX_Duration_run_s * 1000);
    }
    ui32_Dur_ms = ui32Usr_Dur_ms;

    st_SMF_exhaust_dur.bF_Run = true;
}
//::---------------------------------------------------------------------------
void cl_chamber::abort_exhaust_for_Dur_ms(){
    st_SMF_exhaust_dur.bF_req_Abort = true;

}
//::---------------------------------------------------------------------------
//-- sm exhaust duration
//::---------------------------------------------------------------------------
uint32_t  cl_chamber::exec_sm_exhaust_for_Dur_ms(){

}
//::---------------------------------------------------------------------------




