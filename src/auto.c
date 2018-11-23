#include "main.h"
#include <math.h>

#include "movement.h"

 void setDriveLeft( int speed );
 void setDriveRight( int speed );
 void setIntake( int speed );
 void setArm( int speed );
 void setFly( int speed );
 void driveDistFromWall(int distance, int maxSpeed);
 void driveStraight( int travelDistanceA, int travelDistanceD, int maxSpeed, int direction );
 void pointTurn();
 void launchBall();
 void intakeBall();


void autonomous() {
  int posPotDiv[6] = {}; //pot 2 divisions, front left, front right, back left, back right, none
  int pathPotDiv[7] = {}; // pot 1 divisions, front auton 1, 2, 3, rear auton 1
  int midDistUpperLim = 1736, midDistLowerLim = 1665, midDistAvg = 1702;
  int highDistUpperLim = 3515, highDistLowerLim = 3441, highDistAvg = 3478;
  int maxSpeed = 110;
  int capDist = 1016;

  int flySpeed = 0;

  while(flySpeed < 110){ // spin up fly
    flySpeed += 2;
    setFly(flySpeed);
  }

  if(analogRead(POT_AUTON_2) > posPotDiv[0] && analogRead(POT_AUTON_2) < posPotDiv[1]){ // front left
    if(analogRead(POT_AUTON_1) > pathPotDiv[0] && analogRead(POT_AUTON_1) < pathPotDiv[1]){ //(start robot facing flags) mid > low > ball > high > low
      driveDistFromWall(midDistAvg, maxSpeed); //prepare for mid
      delay(1000); //wait until flywheel is fully spunup?
      launchBall();
      driveStraight(400, 500, maxSpeed, 1); //hit lowflag
      driveStraight(-400, -500, -maxSpeed, -1); //driveback
      pointTurn(); //turn 90 degrees
      //driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed); //backup against wall to square against wall?
      driveStraight(capDist*4/5, capDist, maxSpeed, 1);//drive toward ball
      intakeBall();
      driveStraight(-capDist*4/5, -capDist, -maxSpeed, -1); // drive back
      pointTurn();//face towards
      driveDistFromWall(highDistAvg, maxSpeed); // poisition self for high flag
      launchBall();
      setIntake(127);//launch ball
      pointTurn(); // turn toward center low flag
      driveStraight(1500, 1800, maxSpeed, 1); // run into low flag
      setFly(0); //fly stop
    } else if(analogRead(POT_AUTON_1) > pathPotDiv[1] && analogRead(POT_AUTON_1) < pathPotDiv[2]){ // (start robot facing center) mid > low > ball > high > low
      pointTurn(); // face flags
      driveDistFromWall(midDistAvg, maxSpeed); //prepare for mid
      delay(1000); //wait until flywheel is fully spunup?
      launchBall();
      driveStraight(400, 500, maxSpeed, 1); //hit lowflag
      driveStraight(-400, -500, -maxSpeed, -1); //driveback
      pointTurn(); //turn 90 degrees
      //driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed); //backup against wall to square against wall?
      driveStraight(capDist*4/5, capDist, maxSpeed, 1);//drive toward ball
      intakeBall();
      driveStraight(-capDist*4/5, -capDist, -maxSpeed, -1); // drive back
      pointTurn();//face towards
      driveDistFromWall(highDistAvg, maxSpeed); // poisition self for high flag
      launchBall();
      setIntake(127);//launch ball
      pointTurn(); // turn toward center low flag
      driveStraight(1500, 1800, maxSpeed, 1); // run into low flag
      setFly(0); //fly stop
    } else if(analogRead(POT_AUTON_1) > pathPotDiv[2] && analogRead(POT_AUTON_1) < pathPotDiv[3]){ // (start robot facing center)(center flags) ball > high > mid > low
      setIntake(30); //start intake
      driveStraight(capDist*4/5, capDist, maxSpeed, 1); //drive forward towards ball
      intakeBall();
      //driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed)//drive back into position
      pointTurn(); // faceflags
      driveDistFromWall(highDistAvg, maxSpeed); //position for high flag
      launchBall();
      driveDistFromWall(midDistAvg, maxSpeed);// position for mid flag
      launchBall();
      driveStraight(400, 500, maxSpeed, 1); //low flag
      setFly(0);
    } else if(analogRead(POT_AUTON_1) > pathPotDiv[3] && analogRead(POT_AUTON_1) < pathPotDiv[4]){ //(start robot facing flags) (center flags) ball > high > mid > low
      pointTurn(); // turn and face center
      setIntake(30); //start intake
      driveStraight(capDist*4/5, capDist, maxSpeed, 1); //drive forward towards ball
      intakeBall();
      //driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed)//drive back into position
      pointTurn(); // faceflags
      driveDistFromWall(highDistAvg, maxSpeed); //position for high flag
      launchBall();
      driveDistFromWall(midDistAvg, maxSpeed);// position for mid flag
      launchBall();
      driveStraight(400, 500, maxSpeed, 1); //low flag
      setFly(0);
    } else if(analogRead(POT_AUTON_1) > pathPotDiv[4] && analogRead(POT_AUTON_1) < pathPotDiv[5]){ //(start robot facing center) (side flags) ball > high > mid > low
      setIntake(30); //start intake
      driveStraight(capDist*4/5, capDist, maxSpeed, 1); //drive forward towards ball
      intakeBall();
      driveStraight(-capDist*4/5, -capDist, -maxSpeed, -1);//drive back into position
      pointTurn(); // faceflags
      driveDistFromWall(highDistAvg, maxSpeed);//get into position for high flag
      launchBall();
      driveDistFromWall(midDistAvg, maxSpeed); //get into position for mid
      intakeBall();
      launchBall();
      driveStraight(400, 500, maxSpeed, 1); // drive into low
      setFly(0);
    } else if(analogRead(POT_AUTON_1) > pathPotDiv[5] && analogRead(POT_AUTON_1) < pathPotDiv[6]){ //(start robot facing flags) (side flags) ball > high > mid > low
      pointTurn();
      setIntake(30); //start intake
      driveStraight(capDist*4/5, capDist, maxSpeed, 1); //drive forward towards ball
      intakeBall();
      driveStraight(-capDist*4/5, -capDist, -maxSpeed, -1);//drive back into position
      pointTurn(); // faceflags
      driveDistFromWall(highDistAvg, maxSpeed);//get into position for high flag
      launchBall();
      driveDistFromWall(midDistAvg, maxSpeed); //get into position for mid
      intakeBall();
      launchBall();
      driveStraight(400, 500, maxSpeed, 1); // drive into low
      setFly(0);
    }
  } else if(analogRead(POT_AUTON_2) > posPotDiv[1] && analogRead(POT_AUTON_2) < posPotDiv[2]){//front right
    if(analogRead(POT_AUTON_1) > pathPotDiv[0] && analogRead(POT_AUTON_1) < pathPotDiv[1]){ //(start robot facing flags) mid > low > ball > high > low
      driveDistFromWall(midDistAvg, maxSpeed); //prepare for mid
      delay(1000); //wait until flywheel is fully spunup?
      launchBall();
      driveStraight(400, 500, maxSpeed, 1); //hit lowflag
      driveStraight(-400, -500, -maxSpeed, -1); //driveback
      pointTurn(); //turn 90 degrees
      //driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed); //backup against wall to square against wall?
      driveStraight(capDist*4/5, capDist, maxSpeed, 1);//drive toward ball
      intakeBall();
      driveStraight(-capDist*4/5, -capDist, -maxSpeed, -1); // drive back
      pointTurn();//face towards
      driveDistFromWall(highDistAvg, maxSpeed); // poisition self for high flag
      launchBall();
      setIntake(127);//launch ball
      pointTurn(); // turn toward center low flag
      driveStraight(1500, 1800, maxSpeed, 1); // run into low flag
      setFly(0); //fly stop
    } else if(analogRead(POT_AUTON_1) > pathPotDiv[1] && analogRead(POT_AUTON_1) < pathPotDiv[2]){ // (start robot facing center) mid > low > ball > high > low
      pointTurn(); // face flags
      driveDistFromWall(midDistAvg, maxSpeed); //prepare for mid
      delay(1000); //wait until flywheel is fully spunup?
      launchBall();
      driveStraight(400, 500, maxSpeed, 1); //hit lowflag
      driveStraight(-400, -500, -maxSpeed, -1); //driveback
      pointTurn(); //turn 90 degrees
      //driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed); //backup against wall to square against wall?
      driveStraight(capDist*4/5, capDist, maxSpeed, 1);//drive toward ball
      intakeBall();
      driveStraight(-capDist*4/5, -capDist, -maxSpeed, -1); // drive back
      pointTurn();//face towards
      driveDistFromWall(highDistAvg, maxSpeed); // poisition self for high flag
      launchBall();
      setIntake(127);//launch ball
      pointTurn(); // turn toward center low flag
      driveStraight(1500, 1800, maxSpeed, 1); // run into low flag
      setFly(0); //fly stop
    } else if(analogRead(POT_AUTON_1) > pathPotDiv[2] && analogRead(POT_AUTON_1) < pathPotDiv[3]){ // (start robot facing center)(center flags) ball > high > mid > low
      setIntake(30); //start intake
      driveStraight(capDist*4/5, capDist, maxSpeed, 1); //drive forward towards ball
      intakeBall();
      //driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed)//drive back into position
      pointTurn(); // faceflags
      driveDistFromWall(highDistAvg, maxSpeed); //position for high flag
      launchBall();
      driveDistFromWall(midDistAvg, maxSpeed);// position for mid flag
      launchBall();
      driveStraight(400, 500, maxSpeed, 1); //low flag
      setFly(0);
    } else if(analogRead(POT_AUTON_1) > pathPotDiv[3] && analogRead(POT_AUTON_1) < pathPotDiv[4]){ //(start robot facing flags) (center flags) ball > high > mid > low
      pointTurn(); // turn and face center
      setIntake(30); //start intake
      driveStraight(capDist*4/5, capDist, maxSpeed, 1); //drive forward towards ball
      intakeBall();
      //driveStraight(int travelDistanceA, int travelDistanceD, int maxSpeed)//drive back into position
      pointTurn(); // faceflags
      driveDistFromWall(highDistAvg, maxSpeed); //position for high flag
      launchBall();
      driveDistFromWall(midDistAvg, maxSpeed);// position for mid flag
      launchBall();
      driveStraight(400, 500, maxSpeed, 1); //low flag
      setFly(0);
    } else if(analogRead(POT_AUTON_1) > pathPotDiv[4] && analogRead(POT_AUTON_1) < pathPotDiv[5]){ //(start robot facing center) (side flags) ball > high > mid > low
      setIntake(30); //start intake
      driveStraight(capDist*4/5, capDist, maxSpeed, 1); //drive forward towards ball
      intakeBall();
      driveStraight(-capDist*4/5, -capDist, -maxSpeed, -1);//drive back into position
      pointTurn(); // faceflags
      driveDistFromWall(highDistAvg, maxSpeed);//get into position for high flag
      launchBall();
      driveDistFromWall(midDistAvg, maxSpeed); //get into position for mid
      intakeBall();
      launchBall();
      driveStraight(400, 500, maxSpeed, 1); // drive into low
      setFly(0);
    } else if(analogRead(POT_AUTON_1) > pathPotDiv[5] && analogRead(POT_AUTON_1) < pathPotDiv[6]){ //(start robot facing flags) (side flags) ball > high > mid > low
      pointTurn();
      setIntake(30); //start intake
      driveStraight(capDist*4/5, capDist, maxSpeed, 1); //drive forward towards ball
      intakeBall();
      driveStraight(-capDist*4/5, -capDist, -maxSpeed, -1);//drive back into position
      pointTurn(); // faceflags
      driveDistFromWall(highDistAvg, maxSpeed);//get into position for high flag
      launchBall();
      driveDistFromWall(midDistAvg, maxSpeed); //get into position for mid
      intakeBall();
      launchBall();
      driveStraight(400, 500, maxSpeed, 1); // drive into low
      setFly(0);
    }
  } else if(analogRead(POT_AUTON_2) > posPotDiv[1] && analogRead(POT_AUTON_2) < posPotDiv[2]){ //back left
    if(analogRead(POT_AUTON_1) > pathPotDiv[0] && analogRead(POT_AUTON_1) < pathPotDiv[1]){ //(face flags) high > low
      driveDistFromWall(highDistAvg, maxSpeed); //drive forward to distance for high flag
      launchBall();
      driveStraight(700, 800, maxSpeed, 1);//hit low flag
      setFly(0);
    } else if(analogRead(POT_AUTON_1) > pathPotDiv[1] && analogRead(POT_AUTON_1) < pathPotDiv[2]){ //(face center) high > low
      pointTurn();
      driveDistFromWall(highDistAvg, maxSpeed); //drive forward to distance for high flag
      launchBall();
      driveStraight(700, 800, maxSpeed, 1);//hit low flag
      setFly(0);
    }
  } else if(analogRead(POT_AUTON_2) > posPotDiv[1] && analogRead(POT_AUTON_2) < posPotDiv[2]){ //back right
    if(analogRead(POT_AUTON_1) > pathPotDiv[0] && analogRead(POT_AUTON_1) < pathPotDiv[1]){ //(face flags) high > low
      driveDistFromWall(highDistAvg, maxSpeed); //drive forward to distance for high flag
      launchBall();
      driveStraight(700, 800, maxSpeed, 1);//hit low flag
      setFly(0);
    } else if(analogRead(POT_AUTON_1) > pathPotDiv[1] && analogRead(POT_AUTON_1) < pathPotDiv[2]){ //(face center) high > low
      pointTurn();
      driveDistFromWall(highDistAvg, maxSpeed); //drive forward to distance for high flag
      launchBall();
      driveStraight(700, 800, maxSpeed, 1);//hit low flag
      setFly(0);
    }
  } else{ // no auton lol

  }
}

void launchBall(){
  while(digitalRead(FLY_LIMIT) == LOW){
    setIntake(127); //launchball
  }
  delay(500); // wait until ball fully launched, not sure if needed
  setIntake(0);
}

void intakeBall(){
  while(digitalRead(FLY_LIMIT) == HIGH){
    setIntake(30); //intake bal;
  }
  setIntake(0);
}

void driveDistFromWall(int range, int maxSpeed){
  int rangeA = (ultrasonicGet(sonar) - range)/5 + range;
  int rangeD = range;

  int target;
  int deviation;
  int deviationCompensation;

  encoderReset( driveLeftOse );
  encoderReset( driveRightOse );

  while ( ultrasonicGet(sonar) > rangeA ) {
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

    delay(20);

  }


  while ( ultrasonicGet(sonar) > rangeD ) {

    int decelDistance = ultrasonicGet(sonar) - rangeD;
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

    delay(20);
  }

}

void driveStraight( int travelDistanceA, int travelDistanceD, int maxSpeed, int direction ){ //give travelDistance in OSE TICKS
  int totalProgress;
  int target;
  int deviation;
  int deviationCompensation;

  encoderReset( driveLeftOse );
  encoderReset( driveRightOse );

  while ( totalProgress < travelDistanceA ) {
    deviation = direction * (encoderGet( driveLeftOse ) - encoderGet( driveRightOse )); //so if it's a negative number it means it's turning to the left, positive = turn to right
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

    int decelDistance = totalProgress - travelDistanceD;
    int rate = floor( decelDistance / 100 );

    deviation = direction*(encoderGet( driveLeftOse ) - encoderGet( driveRightOse )); //so if it's a negative number it means it's turning to the left, positive = turn to right
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

void PointTurn( int turnDir ) {
  gyroReset(gyro);
  int leftEncDelta;
  int rightEncDelta;
  int leftEncStart = encoderGet( driveLeftOse );
  int rightEncStart = encoderGet( driveRightOse );
  if ( turnDir == 0 ) { //turning CW
    leftEncDelta = abs( leftEncStart - encoderGet( driveLeftOse ) );
    rightEncDelta = abs( rightEncStart - encoderGet( driveRightOse ) );
    while( gyroGet(gyro) < 925 ) {
      if ( leftEncDelta < 130 ) {
        setDriveLeft( 80 );
      } else if ( leftEncDelta > 135 ) {
        setDriveLeft( -30 );
      } else {
        setDriveLeft( 0 );
      }
      if ( rightEncDelta < 130 ) {
        setDriveRight( -80 );
      } else if ( rightEncDelta > 135 ) {
        setDriveRight( 30 );
      } else {
        setDriveRight( 0 );
      }
    }
  } else if ( turnDir == 1 ) { //turning CCW
    while( gyroGet(gyro) > -925 ) {
      if ( leftEncDelta < 130 ) {
        setDriveLeft( -80 );
      } else if ( leftEncDelta > 135 ) {
        setDriveLeft( 30 );
      } else {
        setDriveLeft( 0 );
      }
      if ( rightEncDelta < 130 ) {
        setDriveRight( 80 );
      } else if ( rightEncDelta > 135 ) {
        setDriveRight( -30 );
      } else {
        setDriveRight( 0 );
      }
    }
  }
}

void advancedPointTurn( int turnType, int maxSpeed) {
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
