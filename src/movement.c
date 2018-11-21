#include "main.h"

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
