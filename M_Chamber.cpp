

/**
 * main.c
 */
#include <assert.h>
#include "Chamber.h"

//=============================================================================
int main(void){


    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN); //config for 50MHz clock

    cl_chamber oChamber;

    uint16_t ui16_mmHg;
    uint32_t ui32_Dur_cnt;

    //------- Test Pressure-related functions
    //-- Set & read SetPt_pressure
    oChamber.set_SetPt_pressure_mmHg(32);
    assert(oChamber.ui16_SetPt_mmHg == 32);
    ui16_mmHg = oChamber.read_SetPt_pressure_mmHg();
    assert(ui16_mmHg == 32);

    oChamber.set_SetPt_pressure_mmHg(81);
    assert(oChamber.ui16_SetPt_mmHg == 80); //limited
    ui16_mmHg = oChamber.read_SetPt_pressure_mmHg();
    assert(ui16_mmHg == 80);


    //-- Set & read Thresh_pressure
    oChamber.set_Thresh_pressure_mmHg(45);
    assert(oChamber.ui16_Thresh_mmHg == 45);
    ui16_mmHg = oChamber.read_Thresh_pressure_mmHg();
    assert(ui16_mmHg == 45);

    oChamber.set_Thresh_pressure_mmHg(85);
    assert(oChamber.ui16_Thresh_mmHg == 80);
    ui16_mmHg = oChamber.read_Thresh_pressure_mmHg();
    assert(ui16_mmHg == 80);

    //----- Test trig & abort
    //-- Maintain pressure
    oChamber.st_SMF_maintain_pressure.bF_req_Abort = true;
    oChamber.trig_maintain_pressure_at_SetPt_mmHg(35);
    assert(oChamber.ui16_SetPt_mmHg == 35);
    assert(oChamber.st_SMF_maintain_pressure.bF_Run == true);
    assert(oChamber.st_SMF_maintain_pressure.bF_req_Abort == false);

    oChamber.abort_maintain_pressure_at_SetPt_mmHg();
    assert(oChamber.st_SMF_maintain_pressure.bF_req_Abort == true);

    //-- Increase Pressure
    oChamber.trig_incr_pressure_to_mmHg(40);
    assert(oChamber.ui16_Thresh_mmHg == 40);
    assert(oChamber.st_SMF_incr_pressure.bF_Run == true);
    oChamber.abort_incr_pressure_to_mmHg();
    assert(oChamber.st_SMF_incr_pressure.bF_req_Abort == true);

    //-- Decrease Pressure
    oChamber.trig_decr_pressure_to_mmHg(20);
    assert(oChamber.ui16_Thresh_mmHg == 20);
    assert(oChamber.st_SMF_decr_pressure.bF_Run == true);
    oChamber.abort_decr_pressure_to_mmHg();
    assert(oChamber.st_SMF_decr_pressure.bF_req_Abort == true);


    //------- Test Time-related functions
    //-- Set & read dur
    oChamber.set_Dur_ms(123400);
    assert(oChamber.ui32_Dur_ms == 123400);
    ui32_Dur_cnt = oChamber.read_Dur_ms();
    assert(ui32_Dur_cnt == 123400);

    //-- Trig & abort pumping
    oChamber.trig_pump_for_Dur_ms(1000);
    assert(oChamber.ui32_Dur_ms == 1000);
    assert(oChamber.st_SMF_pump_dur.bF_Run == true);

    oChamber.st_SMF_pump_dur.bF_Run = false;
    oChamber.trig_pump_for_Dur_ms(3600001);
    assert(oChamber.ui32_Dur_ms == 3600000);
    assert(oChamber.st_SMF_pump_dur.bF_Run == true);

    oChamber.st_SMF_pump_dur.bF_req_Abort = false;
    oChamber.abort_pump_for_Dur_ms();
    assert(oChamber.st_SMF_pump_dur.bF_req_Abort == true);


    //-- Trig & abort exhausting
    oChamber.trig_exhaust_for_Dur_ms(123456);
    assert(oChamber.ui32_Dur_ms == 123456);
    assert(oChamber.st_SMF_exhaust_dur.bF_Run == true);

    oChamber.st_SMF_exhaust_dur.bF_Run = false;
    oChamber.trig_exhaust_for_Dur_ms(3600001);
    assert(oChamber.ui32_Dur_ms == 3600000);
    assert(oChamber.st_SMF_exhaust_dur.bF_Run == true);

    oChamber.st_SMF_exhaust_dur.bF_req_Abort = false;
    oChamber.abort_exhaust_for_Dur_ms();
    assert(oChamber.st_SMF_exhaust_dur.bF_req_Abort == true);

    //------- Test State Machines
    uint32_t ui32_SM_Cycle_cnt;

    //------- Test SMs on pressure
    //----- Test sm maintain pressure
    //-- Prepare for test
    oChamber.en_State_maintain_pressure = en_S5_Idle_mp;
    oChamber.ui32_CntCyc_SM_maintain_pressure = 0;
    oChamber.st_SMF_maintain_pressure.bF_Run = false;
    oChamber.st_SMF_maintain_pressure.bF_req_Abort = false;

    //-- en_S5_Idle_mp
    ui32_SM_Cycle_cnt = oChamber.exec_sm_maintain_Pressure_at_SetPt_mmHg();
    assert(oChamber.en_State_maintain_pressure == en_S5_Idle_mp);
    assert(oChamber.ui32_CntCyc_SM_maintain_pressure == 0);

    //-- trig state machine
    oChamber.trig_maintain_pressure_at_SetPt_mmHg(30);

    //-- en_S0_Setup_mp,     //S0->S1
    ui32_SM_Cycle_cnt = oChamber.exec_sm_maintain_Pressure_at_SetPt_mmHg();
    assert(oChamber.en_State_maintain_pressure == en_S1_Decide_mp);
    assert(oChamber.ui32_CntCyc_SM_maintain_pressure == 1);


    //-- en_S1_Decide_mp,    //S1->S2   [S2|S3|S4]
    oChamber.ui16_Curr_Pressure_mmHg = 29;
    ui32_SM_Cycle_cnt = oChamber.exec_sm_maintain_Pressure_at_SetPt_mmHg();
    assert(oChamber.en_State_maintain_pressure == en_S2_PumpOn_mp);
    assert(oChamber.ui32_CntCyc_SM_maintain_pressure == 2);

    //-- en_S1_Decide_mp,    //S1->S3   [S2|S3|S4]
    oChamber.ui16_Curr_Pressure_mmHg = 30;
    oChamber.en_State_maintain_pressure = en_S1_Decide_mp; //restore sm for test
    ui32_SM_Cycle_cnt = oChamber.exec_sm_maintain_Pressure_at_SetPt_mmHg();
    assert(oChamber.en_State_maintain_pressure == en_S3_PumpOff_mp);
    assert(oChamber.ui32_CntCyc_SM_maintain_pressure == 3);

    //-- en_S1_Decide_mp,    //S1->S4   [S2|S3|S4]
    oChamber.en_State_maintain_pressure = en_S1_Decide_mp; //restore sm for test
    oChamber.st_SMF_maintain_pressure.bF_req_Abort = true;
    ui32_SM_Cycle_cnt = oChamber.exec_sm_maintain_Pressure_at_SetPt_mmHg();
    assert(oChamber.en_State_maintain_pressure == en_S4_WrapUp_mp);
    assert(oChamber.ui32_CntCyc_SM_maintain_pressure == 4);


    //-- en_S2_PumpOn_mp,    //S2->S1   [S1|S4]
    oChamber.en_State_maintain_pressure = en_S2_PumpOn_mp; //restore sm for test
    oChamber.st_SMF_maintain_pressure.bF_req_Abort = false;
    ui32_SM_Cycle_cnt = oChamber.exec_sm_maintain_Pressure_at_SetPt_mmHg();
    assert(oChamber.en_State_maintain_pressure == en_S2_PumpOn_mp);
    assert(oChamber.ui32_CntCyc_SM_maintain_pressure == 5);
    assert(oChamber.u16_DnCnt_Delay == 4);

    //-- en_S2_PumpOn_mp,    //S2->S1   [S1|S4]
    ui32_SM_Cycle_cnt = oChamber.exec_sm_maintain_Pressure_at_SetPt_mmHg();
    assert(oChamber.en_State_maintain_pressure == en_S2_PumpOn_mp);
    assert(oChamber.ui32_CntCyc_SM_maintain_pressure == 6);
    assert(oChamber.u16_DnCnt_Delay == 3);

    //-- en_S2_PumpOn_mp,    //S2->S1   [S1|S4]
    oChamber.u16_DnCnt_Delay = 0;
    ui32_SM_Cycle_cnt = oChamber.exec_sm_maintain_Pressure_at_SetPt_mmHg();
    assert(oChamber.en_State_maintain_pressure == en_S1_Decide_mp);
    assert(oChamber.ui32_CntCyc_SM_maintain_pressure == 7);
    assert(oChamber.u16_DnCnt_Delay == 0);


    //-- en_S2_PumpOn_mp,    //S2->S4   [S1|S4]
    oChamber.en_State_maintain_pressure = en_S2_PumpOn_mp; //restore sm for test
    oChamber.st_SMF_maintain_pressure.bF_req_Abort = true;
    ui32_SM_Cycle_cnt = oChamber.exec_sm_maintain_Pressure_at_SetPt_mmHg();
    assert(oChamber.en_State_maintain_pressure == en_S4_WrapUp_mp);
    assert(oChamber.ui32_CntCyc_SM_maintain_pressure == 8);


    //-- en_S3_PumpOff_mp,   //S3->S1   [S1|S4]
    oChamber.en_State_maintain_pressure = en_S3_PumpOff_mp; //restore sm for test
    oChamber.st_SMF_maintain_pressure.bF_req_Abort = false;
    ui32_SM_Cycle_cnt = oChamber.exec_sm_maintain_Pressure_at_SetPt_mmHg();
    assert(oChamber.en_State_maintain_pressure == en_S1_Decide_mp);
    assert(oChamber.ui32_CntCyc_SM_maintain_pressure == 9);

    //-- en_S3_PumpOff_mp,   //S3->S4   [S1|S4]
    oChamber.en_State_maintain_pressure = en_S3_PumpOff_mp; //restore sm for test
    oChamber.st_SMF_maintain_pressure.bF_req_Abort = true;
    ui32_SM_Cycle_cnt = oChamber.exec_sm_maintain_Pressure_at_SetPt_mmHg();
    assert(oChamber.en_State_maintain_pressure == en_S4_WrapUp_mp);
    assert(oChamber.ui32_CntCyc_SM_maintain_pressure == 10);


    //-- en_S4_WrapUp_mp,    //S4->S5
    oChamber.st_SMF_maintain_pressure.bF_req_Abort = true;
    ui32_SM_Cycle_cnt = oChamber.exec_sm_maintain_Pressure_at_SetPt_mmHg();
    assert(oChamber.en_State_maintain_pressure == en_S5_Idle_mp);
    assert(oChamber.ui32_CntCyc_SM_maintain_pressure == 11);
    assert(oChamber.st_SMF_maintain_pressure.bF_Run == false);
    assert(oChamber.st_SMF_maintain_pressure.bF_req_Abort == false);


    //-- en_S5_Idle_mp       //S5.
    ui32_SM_Cycle_cnt = oChamber.exec_sm_maintain_Pressure_at_SetPt_mmHg();
    assert(oChamber.en_State_maintain_pressure == en_S5_Idle_mp);
    assert(oChamber.ui32_CntCyc_SM_maintain_pressure == 11); //Sm has stopped executing


    //-- en_S5_Idle_mp       //S5.
    ui32_SM_Cycle_cnt = oChamber.exec_sm_maintain_Pressure_at_SetPt_mmHg();
    assert(oChamber.en_State_maintain_pressure == en_S5_Idle_mp);
    assert(oChamber.ui32_CntCyc_SM_maintain_pressure == 11);
    //----- End Test sm maintain pressure


//todo

    //----- Test sm incr pressure
    //-- Prepare for test
    ui32_SM_Cycle_cnt = oChamber.exec_sm_increase_to_Pressure_mmHg();



    //----- Test sm decr pressure
    //-- Prepare for test
    ui32_SM_Cycle_cnt = oChamber.exec_sm_decrease_to_Pressure_mmHg();


    //------- SMs on time
    //----- Test sm pump duration
    //-- Prepare for test
    ui32_SM_Cycle_cnt = oChamber.exec_sm_pump_for_Dur_ms();

    //----- Test sm exhaust duration
    //-- Prepare for test
   ui32_SM_Cycle_cnt = oChamber.exec_sm_exhaust_for_Dur_ms();


    //----- Just to avoid warning :never used"
    ui16_mmHg++;
    ui32_Dur_cnt++;
    ui32_SM_Cycle_cnt++;


    while(1){

    }
}
//=============================================================================
