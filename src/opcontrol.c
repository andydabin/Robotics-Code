#include "main.h"
#include <math.h>

#include "movement.h"

void taskDrive( void * parameter );
void taskFly( void * parameter );
void taskFlyRPM( void * parameter );
void taskArm( void * parameter );

int intakemode = 0; // 0 = not moving, 1 = IN, 2 = OUT
bool intakeTogglePrev = false;

void operatorControl() {

	TaskHandle driveTaskHandle = taskCreate( taskDrive, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT );
	TaskHandle flyTaskHandle = taskCreate( taskFly, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT );
	TaskHandle flyRPMTaskHandle = taskCreate( taskFlyRPM, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT );
	TaskHandle armTaskHandle = taskCreate( taskArm, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT );

	delay( 3600000 );

	taskDelete( driveTaskHandle );
	taskDelete( flyTaskHandle );
	taskDelete( flyRPMTaskHandle );
	taskDelete( armTaskHandle );

}

void taskDrive( void * parameter ) {
	while ( true ) {

		double factor = abs( joystickGetAnalog( JOY_MASTER, AXIS_LEFT_V ) ) / 127.0 ;

		double left = joystickGetAnalog( JOY_MASTER, AXIS_LEFT_V ) + joystickGetAnalog( JOY_MASTER, AXIS_RIGHT_H ) * ( 0.3 + 0.4 * sqrt( factor ) );

		double right = joystickGetAnalog( JOY_MASTER, AXIS_LEFT_V ) - joystickGetAnalog( JOY_MASTER, AXIS_RIGHT_H ) * ( 0.3 + 0.4 * sqrt( factor ) );

		setDriveLeft( left );
		setDriveRight( right );

		delay( 20 );

	}
}

double flyspeed;

void taskFly( void * parameter ) {

	flyspeed = 0;

	while ( true ) {

		if ( joystickGetDigital( JOY_MASTER, 5, JOY_UP) ) {
			setIntake( INTAKE_IN );
		} else if ( joystickGetDigital( JOY_MASTER, 5, JOY_DOWN) ){
			setIntake( INTAKE_OUT );
		} else {
			setIntake( 0 );
		}

		if ( joystickGetDigital( JOY_MASTER, 6, JOY_UP) ) {
			flyspeed = flyspeed + 2 > 110 ? 110 : flyspeed + 2;
		} else {
			flyspeed = flyspeed - 1 < 0 ? 0 : flyspeed - 1;
		}

		setFly( flyspeed );

		delay( 20 );

	}
}

double prevtick;
volatile double rpm;

void taskFlyRPM( void * parameter ) {

	rpm = 0;

	encoderReset( flyOSE );
	prevtick = encoderGet( flyOSE );

	delay( 20 );

	while ( true ) {

		rpm = ( encoderGet( flyOSE ) - prevtick ) * 3600 / ( 0.02 * 360);

		delay( 20 );

	}
}

int armmode; // 0 = not moving/manual, 1 = auto up, -1 = auto down
int counter;

void taskArm( void * parameter ) {

	armmode = 0;
	counter = 0;

	while ( true ) {

		/*
		if ( joystickGetDigital( JOY_MASTER, 8, JOY_LEFT ) ) {

			setArm( 127 );

			armmode = 0;
			counter = 0;

		} else if ( joystickGetDigital( JOY_MASTER, 8, JOY_DOWN ) ) {

			setArm( -127 );

			armmode = 0;
			counter = 0;

		} else {

			if ( armmode == 0 && joystickGetDigital( JOY_MASTER, 8, JOY_UP ) ) {

				armmode = 1;
				counter = 40;

			} else if ( armmode == 0 && joystickGetDigital( JOY_MASTER, 8, JOY_RIGHT ) ) {

				armmode = -1;
				counter = 40;

			}

			if ( armmode == 0 || counter <= 0 ) {

				setArm( 0 );

				counter = 0;
				armmode = 0;

			} else if ( armmode == 1 ) {

				setArm( 127 );

				counter--;

			} else if ( armmode == -1 ) {

				setArm( -127 );

				counter--;

			}

		}
		*/

		if ( joystickGetDigital( JOY_MASTER, 8, JOY_LEFT ) ) {

			setArm( 80 );

		} else if ( joystickGetDigital( JOY_MASTER, 8, JOY_DOWN ) ) {

			setArm( -80 );

		} else {

			setArm( 0 );

		}

		delay( 20 );

	}

}
