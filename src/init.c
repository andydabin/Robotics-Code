#include "main.h"



void initializeIO() {

}

Encoder driveLeftOse;
Encoder driveRightOse;
Gyro gyro;

void initialize() {

  flyOSE = encoderInit(OSE_FLYWHEEL_TOP, OSE_FLYWHEEL_BOTTOM, NOT_REVERSED);
  driveLeftOse = encoderInit(OSE_DRIVE_LEFT_TOP, OSE_DRIVE_LEFT_BOTTOM, NOT_REVERSED);
  driveRightOse = encoderInit(OSE_DRIVE_RIGHT_TOP, OSE_DRIVE_RIGHT_BOTTOM, NOT_REVERSED);
  gyro = gyroInit(GYRO_INPUT, 0);
  gyroReset( gyro );

}
