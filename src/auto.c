#include "main.h"
#include <math.h>

#include "movement.h"

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
