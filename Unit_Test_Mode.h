/*
 * Unit_Test_Mode.h
 *
 *  Created on: 21 Jul 2021
 *      Author: John Chee
 */

#ifndef UNIT_TEST_MODE_H_
#define UNIT_TEST_MODE_H_

//!!! Uncomment the "#define ..." line if unit testing is reqd
#define Unit_Test_Mode
//#undef Unit_Test_Mode
//>>>>> Controls to select unit testing or production >>>>>>>>>>>>>>>>>>>>>>>>>
#ifdef Unit_Test_Mode
#define private public
#define protected public
#endif
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


#endif /* UNIT_TEST_MODE_H_ */
