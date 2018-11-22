#include "main.h"
#include <math.h>

#include "movement.h"

 void setDriveLeft( int speed );
 void setDriveRight( int speed );
 void setIntake( int speed );
 void setArm( int speed );
 void setFly( int speed );
 void driveStraight( int travelDistanceA, int travelDistanceD, int maxSpeed );
 void pointTurn();


void autonomous() {
  int posPotDiv[6] = {}; //pot 2 divisions
  int pathPotDiv[6] = {}; // pot 1 divisions

  if(analogRead(POT_AUTON_2) > posPotDiv[0] && analogRead(POT_AUTON_2) < posPotDiv[1]){ // front left
    if(analogRead(POT_AUTON_1) > pathPotDiv[0] && analogRead(POT_AUTON_1) < pathPotDiv[1]){ //(start robot facing flags) mid > low > ball > high > low
      setFly(int speed);  //start spinning up flywheel
      driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed); //prepare for mid or high flag
      wait(unsigned long time); //wait until flywheel is fully spunup?
      setIntake(int speed); //launchball
      driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed); //hit lowflag
      setFly(0); //stop flywheel
      driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed); //driveback
      pointTurn(); //turn 90 degrees
      driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed); //backup against wall to square against wall?
      driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed);//drive toward ball
      wait(); //wait until intake has properly intaked balled
      setIntake(0); //stop intake
      driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed); // drive back
      pointTurn();//face towards
      setFly(int speed);
      driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed); // poisition self for high/midflag flag
      wait(); //wait until fly fully spun up
      setIntake(int speed);//launch ball
      pointTurn(); // turn toward center low flag
      driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed); // run into low flag
      setFly(0); //fly stop
    } else if(analogRead(analogRead(POT_AUTON_1) > pathPotDiv[1] && analogRead(POT_AUTON_1) < pathPotDiv[2])){ // (start robot facing center) ball > high > mid > low
      setIntake(30); //start intake
      driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed //drive forward towards ball
      //driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed)//drive back into position
      setFly(int speed);
      pointTurn(); // faceflags
      driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed); //position for high flag
      setIntake(127); // launchball
      wait(unsigned long time);
      setIntake(0); //stop intake
      driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed); // position for mid flag
      setIntake(127); // launchball
      wait(unsigned long time);
      setIntake(0); //stop intake
      driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed); //low flag
    } else if(analogRead(analogRead(POT_AUTON_1) > pathPotDiv[2] && analogRead(POT_AUTON_1) < pathPotDiv[3])){ //(start robot facing flags) ball > high > mid > low
      pointTurn(); // turn and face center
      setIntake(30); //start intake
      driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed //drive forward towards ball
      //driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed)//drive back into position
      setFly(int speed);
      pointTurn(); // faceflags
      driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed); //position for high flag
      setIntake(127); // launchball
      wait(unsigned long time);
      setIntake(0); //stop intake
      driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed); // position for mid flag
      setIntake(127); // launchball
      wait(unsigned long time);
      setIntake(0); //stop intake
      driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed); //low flag
    } else if(analogRead(analogRead(POT_AUTON_1) > pathPotDiv[3] && analogRead(POT_AUTON_1) < pathPotDiv[4])){ // (start robot facing center) mid > low > ball > high > low
      pointTurn(); // face flags
      setFly(int speed);  //start spinning up flywheel
      driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed); //prepare for mid or high flag
      wait(unsigned long time); //wait until flywheel is fully spunup?
      setIntake(int speed); //launchball
      driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed); //hit lowflag
      setFly(0); //stop flywheel
      driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed); //driveback
      pointTurn(); //turn 90 degrees
      driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed); //backup against wall to square against wall?
      driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed);//drive toward ball
      wait(); //wait until intake has properly intaked balled
      setIntake(0); //stop intake
      driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed); // drive back
      pointTurn();//face towards
      setFly(int speed);
      driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed); // poisition self for high/midflag flag
      wait(); //wait until fly fully spun up
      setIntake(int speed);//launch ball
      pointTurn(); // turn toward center low flag
      driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed); // run into low flag
      setFly(0); //fly stop
    }
  } else if(analogRead(POT_AUTON_2) > posPotDiv[1] && analogRead(POT_AUTON_2) < posPotDiv[2]){//front right
    if(analogRead(POT_AUTON_1) > pathPotDiv[0] && analogRead(POT_AUTON_1) < pathPotDiv[1]){ //(start robot facing flags) mid > low > ball > high > low
      setFly(int speed);  //start spinning up flywheel
      driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed); //prepare for mid or high flag
      wait(unsigned long time); //wait until flywheel is fully spunup?
      setIntake(int speed); //launchball
      driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed); //hit lowflag
      setFly(0); //stop flywheel
      driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed); //driveback
      pointTurn(); //turn 90 degrees
      driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed); //backup against wall to square against wall?
      driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed);//drive toward ball
      wait(); //wait until intake has properly intaked balled
      setIntake(0); //stop intake
      driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed); // drive back
      pointTurn();//face towards
      setFly(int speed);
      driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed); // poisition self for high/midflag flag
      wait(); //wait until fly fully spun up
      setIntake(int speed);//launch ball
      pointTurn(); // turn toward center low flag
      driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed); // run into low flag
      setFly(0); //fly stop
    } else if(analogRead(analogRead(POT_AUTON_1) > [1] && analogRead(POT_AUTON_1) < [2])){ // (start robot facing center) ball > high > mid > low
      setIntake(30); //start intake
      driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed //drive forward towards ball
      //driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed)//drive back into position
      setFly(int speed);
      pointTurn(); // faceflags
      driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed); //position for high flag
      setIntake(127); // launchball
      wait(unsigned long time);
      setIntake(0); //stop intake
      driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed); // position for mid flag
      setIntake(127); // launchball
      wait(unsigned long time);
      setIntake(0); //stop intake
      driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed); //low flag
    } else if(analogRead(analogRead(POT_AUTON_1) > pathPotDiv[2] && analogRead(POT_AUTON_1) < pathPotDiv[3])){ //(start robot facing flags) ball > high > mid > low
      pointTurn(); // turn and face center
      setIntake(30); //start intake
      driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed //drive forward towards ball
      //driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed)//drive back into position
      setFly(int speed);
      pointTurn(); // faceflags
      driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed); //position for high flag
      setIntake(127); // launchball
      wait(unsigned long time);
      setIntake(0); //stop intake
      driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed); // position for mid flag
      setIntake(127); // launchball
      wait(unsigned long time);
      setIntake(0); //stop intake
      driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed); //low flag
    }else if(analogRead(analogRead(POT_AUTON_1) > pathPotDiv[3] && analogRead(POT_AUTON_1) < pathPotDiv[4])){ // (start robot facing center) mid > low > ball > high > low
      pointTurn(); // face flags
      setFly(int speed);  //start spinning up flywheel
      driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed); //prepare for mid or high flag
      wait(unsigned long time); //wait until flywheel is fully spunup?
      setIntake(int speed); //launchball
      driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed); //hit lowflag
      setFly(0); //stop flywheel
      driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed); //driveback
      pointTurn(); //turn 90 degrees
      driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed); //backup against wall to square against wall?
      driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed);//drive toward ball
      wait(); //wait until intake has properly intaked balled
      setIntake(0); //stop intake
      driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed); // drive back
      pointTurn();//face towards
      setFly(int speed);
      driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed); // poisition self for high/midflag flag
      wait(); //wait until fly fully spun up
      setIntake(int speed);//launch ball
      pointTurn(); // turn toward center low flag
      driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed); // run into low flag
      setFly(0); //fly stop
    }
  } else if(analogRead(POT_AUTON_2) > posPotDiv[1] && analogRead(POT_AUTON_2) < posPotDiv[2]){ //back left

  } else if(analogRead(POT_AUTON_2) > posPotDiv[1] && analogRead(POT_AUTON_2) < posPotDiv[2]){ //back right

  } else{ // no auton lol

  }


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
      setDriveLeft( ( ( -2 / 3 ) * ( 2 * (leftPercent) - 1 ) ^ 2 + 1 ) * 100 );
      setDriveRight( ( ( -2 / 3 ) * ( 2 * (rightPercent) - 1 ) ^ 2 + 1 ) * 100 );
    }

    //Victor
    while( abs(encoderGet(driveLeftOse) - oseTarget) <= 5 && abs(encoderGet(driveRightOse) - oseTarget) <= 5) {

        Ldeviation = encoderGet(driveLeftOse) - oseTarget;
        Rdeviation = encoderGet(driveRightOse) + oseTarget;

        leftPercent = encoderGet(driveLeftOse) / oseTarget;
        rightPercent = encoderGet(driveRightOse) / oseTarget;

        rightPower = ( ( -2 / 3 ) * ( 2 * (rightPercent) - 1 ) ^ 2 + 1 ) * 100;
        leftPower = ( ( -2 / 3 ) * ( 2 * (leftPercent) - 1 ) ^ 2 + 1 ) * 100 ;

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
