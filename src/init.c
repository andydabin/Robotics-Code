#include "main.h"

void initializeIO() {
  pinMode(FLY_LIMIT, INPUT);
}

void initialize() {

  flyOSE = encoderInit(OSE_FLYWHEEL_TOP, OSE_FLYWHEEL_BOTTOM, NOT_REVERSED);
  driveLeftOse = encoderInit(OSE_DRIVE_LEFT_TOP, OSE_DRIVE_LEFT_BOTTOM, REVERSED);
  driveRightOse = encoderInit(OSE_DRIVE_RIGHT_TOP, OSE_DRIVE_RIGHT_BOTTOM, NOT_REVERSED);
  gyro = gyroInit(GYRO_INPUT, 0);
  gyroReset( gyro );
  sonar = ultrasonicInit(4, 3);

}
