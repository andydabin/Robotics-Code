#ifndef MAIN_H_
#define MAIN_H_

#include <API.h>

#ifdef __cplusplus
extern "C" {
#endif


void autonomous();

void initializeIO();

void initialize();

void operatorControl();


#ifdef __cplusplus
}
#endif

#define NOT_REVERSED false
#define REVERSED true

#define JOY_MASTER 1
#define JOY_SLAVE 2

#define AXIS_LEFT_H 4
#define AXIS_LEFT_V 3
#define AXIS_RIGHT_H 1
#define AXIS_RIGHT_V 2

#define MOT_INTAKE 1
#define MOT_LDRIVE_1 2
#define MOT_LDRIVE_2 3
#define MOT_LDRIVE_3 4
#define MOT_FLY_1 5
#define MOT_FLY_2 6
#define MOT_RDRIVE_1 7
#define MOT_RDRIVE_2 8
#define MOT_RDRIVE_3 9
#define MOT_ARM 10

#define INTAKE_IN 127
#define INTAKE_OUT -127
#define INDEX_IN 127
#define INDEX_OUT -127

#define OSE_FLYWHEEL_TOP 1
#define OSE_FLYWHEEL_BOTTOM 2
#define OSE_DRIVE_LEFT_TOP 11
#define OSE_DRIVE_LEFT_BOTTOM 12
#define OSE_DRIVE_RIGHT_TOP 5
#define OSE_DRIVE_RIGHT_BOTTOM 6

#define POT_AUTON_1 1
#define POT_AUTON_2 2

#define GYRO_INPUT 7


Encoder flyOSE;

#endif
