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

void pointTurn( int turnType, int maxSpeed) {
//turn type 1: 90 degree ccw, 2: 90 degree cw, 3: small ccw, 4: small cw.
  encoderReset( driveLeftOse );
  encoderReset( driveRightOse );
  gyroReset( gyro );

  int gyroTarget;
  int oseTarget;
  int oseLeftTarget;
  int oseRightTarget;
  int leftTargetDistance;
  int rightTargetDistance;
  int leftPercent;
  int rightPercent;
  bool turnComplete = false;

  double Ldeviation, Rdeviation;
  int leftPower, rightPower;

  if( turnType == 1 ) {
    //Anni
    gyroTarget = 900;
    oseLeftTarget = -130;
    oseRightTarget = 130;
    int leftOse = encoderGet(driveLeftOse);
    int rightOse = encoderGet(driveRightOse);

    while ( gyroGet( gyro ) < gyroTarget) {

      leftTargetDistance = oseLeftTarget - ( encoderGet(driveLeftOse) - leftOse ); // gives distance + direction to target. If 0, at target
      rightTargetDistance = oseRightTarget - ( encoderGet(driveRightOse) - rightOse ); //gives distance to target. If 0, at target.
      /*neg oseTarget means motors need to drive backwards.
      target distance neg means go back. Should be same sign as oseTarget
      target distance pos means go forward. Should be same sign as oseTarget
      */
      leftPercent = leftTargetDistance / oseTarget; //at start, should be 1 (distance = target). At finish, 0 (target distance = 0). Gets smaller and smaller
      rightPercent = rightTargetDistance / oseTarget; //will give us a direction because oseTarget tells us cw/ccw.
      //map this percentage from 0-1 on function
      //use function: y=-(2/3)(2x-1)^2 + 1 and then multiply by 100 to get motor value?
      setDriveLeft( ( ( -2 / 3 ) * ( 2 * ( (leftPercent) - 1 ) ^ 2 ) + 1 ) * 100 );
      setDriveRight( ( ( -2 / 3 ) * ( 2 * ( (rightPercent) - 1 ) ^ 2 ) + 1 ) * 100 );
    }

    //Victor
    while( abs(encoderGet(driveLeftOse) - oseTarget) <= 5 && abs(encoderGet(driveRightOse) - oseTarget) <= 5) {

        Ldeviation = encoderGet(driveLeftOse) - oseTarget;
        Rdeviation = encoderGet(driveRightOse) + oseTarget;

        leftPercent = encoderGet(driveLeftOse) / oseTarget;
        rightPercent = encoderGet(driveRightOse) / oseTarget;

        rightPower = ( ( -2 / 3 ) * ( 2 * ( (rightPercent) - 1 ) ^ 2 ) + 1 ) * 100;
        leftPower = ( ( -2 / 3 ) * ( 2 * ( (leftPercent) - 1 ) ^ 2 ) + 1 ) * 100 ;

        if(abs(Ldeviation) <= 5)
          setDriveLeft((abs(Ldeviation)/Ldeviation)*rightPower);
        else
          setDriveLeft(0);

        if(abs(Rdeviation) <= 5)
          setDriveRight((abs(Rdeviation)/Rdeviation)*leftPower);
        else
          setDriveRight(0);

    }

  } else if( turnType == 2 ) {

  } else if( turnType == 3 ) {

  } else if( turnType == 4 ) {

  }




}
