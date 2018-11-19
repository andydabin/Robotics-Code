/** @file auto.c
 * @brief File for autonomous code
 *
 * This file should contain the user autonomous() function and any functions related to it.
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"
#include <math.h>

/*
 * Runs the user autonomous code. This function will be started in its own task with the default
 * priority and stack size whenever the robot is enabled via the Field Management System or the
 * VEX Competition Switch in the autonomous mode. If the robot is disabled or communications is
 * lost, the autonomous task will be stopped by the kernel. Re-enabling the robot will restart
 * the task, not re-start it from where it left off.
 *
 * Code running in the autonomous task cannot access information from the VEX Joystick. However,
 * the autonomous function can be invoked from another task if a VEX Competition Switch is not
 * available, and it can access joystick information if called in this way.
 *
 * The autonomous task may exit, unlike operatorControl() which should never exit. If it does
 * so, the robot will await a switch to another mode or disable/enable cycle.
 */

Encoder driveLeftOse;
Encoder driveRightOse;
Gyro gyro;


 void setDriveLeft( int speed );
 void setDriveRight( int speed );
 void setIntake( int speed );
 void setArm( int speed );
 void setFly( int speed );
 void driveStraight( int travelDistanceA, int travelDistanceD, int maxSpeed );
 void pointTurn();


void autonomous() {
}

void driveStraight( int travelDistanceA, int travelDistanceD, int maxSpeed ){ //give travelDistance in OSE TICKS
  int totalProgress;
  int target;
  int deviation;
  int deviationCompensation;

  encoderReset( driveLeftOse );
  encoderReset( driveRightOse );

  while ( totalProgress < travelDistanceA ) {
    deviation = encoderGet( driveLeftOse ) - encoderGet( driveRightOse ); //so if it's a negative number it means it's turning to the left, positive = turn to right
    target = target + 4 > maxSpeed ? maxSpeed : target + 4;
    deviationCompensation = abs( deviation ) * 3;

    if ( deviation > 0 ) { //itc turn to right
      if ( target + deviationCompensation < maxSpeed ) {
        setDriveLeft( target );
        setDriveRight( target + deviationCompensation );
      } else {
        setDriveLeft( target - deviationCompensation );
        setDriveRight( target );
      }
    } else if ( deviation < 0 ) {
      if ( target + deviationCompensation < maxSpeed ) {
        setDriveLeft( target + deviationCompensation );
        setDriveRight( target );
      } else {
        setDriveRight( target );
        setDriveLeft( target - deviationCompensation );
      }
    } else {
      setDriveRight( target );
      setDriveLeft( target );
    }

    totalProgress = ( ( encoderGet( driveLeftOse ) + encoderGet( driveRightOse ) )/ 2 );
    delay(20);

  }

  while ( totalProgress < travelDistanceD ) {

    int decelDistance = travelDistanceD - travelDistanceD;
    int rate = floor( decelDistance / 100 );

    deviation = encoderGet( driveLeftOse ) - encoderGet( driveRightOse ); //so if it's a negative number it means it's turning to the left, positive = turn to right
    target = target - rate > 30 ? target - rate : 30;
    deviationCompensation = abs( deviation ) * 3;

    if ( deviation > 0 ) { //robot turn to right
      if ( target + deviationCompensation < maxSpeed ) {
        setDriveLeft( target );
        setDriveRight( target + deviationCompensation );
      } else {
        setDriveLeft( target - deviationCompensation );
        setDriveRight( target );
      }
    } else if ( deviation < 0 ) { //robot turn to left
      if ( target + deviationCompensation < maxSpeed ) {
        setDriveLeft( target + deviationCompensation );
        setDriveRight( target );
      } else {
        setDriveRight( target );
        setDriveLeft( target - deviationCompensation );
      }
    } else {
      setDriveRight( target );
      setDriveLeft( target );
    }

    totalProgress = ( ( encoderGet( driveLeftOse ) + encoderGet( driveRightOse ) )/ 2 );
    delay(20);

  }
}

void pointTurn( int targetDegrees, int maxSpeed ) {

  encoderReset( driveLeftOse );
  encoderReset( driveRightOse );
  gyroReset( gyro );

  int targetTicks = targetDegrees; //add math here
  int ticksA = targetTicks * 2 / 3;
  int ticksD = targetTicks - ticksA;

  if( targetDegrees < 0 ) {//target < 0 means that we want to be turning left

  }

}

void setDriveLeft( int speed ) {

	motorSet( MOT_LDRIVE_1, speed );
	motorSet( MOT_LDRIVE_2, speed );
	motorSet( MOT_LDRIVE_3, speed );

}

void setDriveRight( int speed ) {

	motorSet( MOT_RDRIVE_1, -speed );
	motorSet( MOT_RDRIVE_2, -speed );
	motorSet( MOT_RDRIVE_3, -speed );

}

void setArm( int speed ) {

	motorSet( MOT_ARM, speed );

}

void setIntake( int speed ) {

	motorSet( MOT_INTAKE, speed );

}

void setFly( int speed ) {

	motorSet( MOT_FLY_1, -speed );
	motorSet( MOT_FLY_2, -speed );

}
