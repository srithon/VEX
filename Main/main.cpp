/**************************************************
 *
 *
 * Team: 750E
 * Game: Turning Point
 * Main File
 *
 *
 ***************************************************/


#include "robot-config.h"

//using namespace for cleaner code
using namespace vex;

//constant for wheel diameter
const float WHEEL_DIAMETER = 4.125;

void pre_auton( void ) {

}


/**************************************************
 *
 * Auton methods
 * driveFor();
 * turn();
 * shoot();
 *
 **************************************************/

void driveFor( float tiles , int speed ){
    const float TILE_LENGTH = 12.5;
    float length = tiles * TILE_LENGTH;
    float circum =  3.141592653589 * WHEEL_DIAMETER;
    float rotations = length / circum;
    float degrees = 360 * rotations;

    RightMotorFront.startRotateFor(degrees, rotationUnits::deg, speed, velocityUnits::pct);
    LeftMotorFront.startRotateFor(degrees, rotationUnits::deg, speed, velocityUnits::pct);
    RightMotorBack.startRotateFor(degrees, rotationUnits::deg, speed, velocityUnits::pct);
    LeftMotorBack.rotateFor(degrees, rotationUnits::deg, speed, velocityUnits::pct);
}


void turn( float degrees ){
    const float TURNING_DIAMETER = 17.5;
    float turningRatio = TURNING_DIAMETER / WHEEL_DIAMETER;
    int turnSpeed = 60;

    RightMotorFront.startRotateFor(degrees * turningRatio / 2, rotationUnits::deg, turnSpeed, velocityUnits::pct);
    LeftMotorFront.startRotateFor(-degrees * turningRatio / 2, rotationUnits::deg, turnSpeed, velocityUnits::pct);
    RightMotorBack.startRotateFor(degrees * turningRatio / 2, rotationUnits::deg, turnSpeed, velocityUnits::pct);
    LeftMotorBack.rotateFor(-degrees * turningRatio / 2, rotationUnits::deg, turnSpeed, velocityUnits::pct);
}


void shoot( void ){
    LauncherMotor.rotateFor(1.4, timeUnits::sec, 100, velocityUnits::pct);
}

/*****AUTON SELECTOR*****/

int selectAuton() {
    Brain.Screen.clearScreen();

    Brain.Screen.drawRectangle(10, 10, 140, 50, color::red);
    Brain.Screen.drawRectangle(160, 10, 140, 50, color::red);
    Brain.Screen.drawRectangle(310, 10, 140, 50, color::red);

    Brain.Screen.drawRectangle(10, 80, 140, 50, color::blue);
    Brain.Screen.drawRectangle(160, 80, 140, 50, color::blue);
    Brain.Screen.drawRectangle(310, 80, 140, 50, color::blue);

    Brain.Screen.printAt(31, 35, "Front Flag");
    Brain.Screen.printAt(183, 35, "Front Plat");
    Brain.Screen.printAt(360, 35, "Back");

    Brain.Screen.printAt(31, 105, "Front Flag");
    Brain.Screen.printAt(185, 105, "Front Plat");
    Brain.Screen.printAt(360, 105, "Back");

    while(true) {
        if(Brain.Screen.pressing()) {
            int xPos = Brain.Screen.xPosition();
            int yPos = Brain.Screen.yPosition();

            if(yPos >= 10 && yPos <= 60) {
                if(xPos >= 10 && xPos <= 150) {
                    return 1;
                }
                else if(xPos >= 160 && xPos <= 300) {
                    return 2;
                }
                else if(xPos >= 310 && xPos <= 450){
                    return 3;
                }
            }
            else if(yPos >= 80 && yPos <= 130) {
                if(xPos >= 10 && xPos <= 150) {
                    return 4;
                }
                else if(xPos >= 160 && xPos <= 300) {
                    return 5;
                }
                else if(xPos >= 310 && xPos <= 450){
                    return 6;
                }
            }
        }
    }
}

/*****BLUE INSIDE AUTON*****/

void BlueInsidePlatform( void ){
    shoot(); //shoot high flag
    RollerMotor.spin(directionType::fwd,100,velocityUnits::pct); //turn on roller
    turn(160.0); //turn left to face cap w ball
    task::sleep(300); //stop for 0.3 seconds to avoid drifting
    driveFor(3.0, 100); //drive for 3 tiles to get ball
    driveFor(0.6, 40); //drive slowly to approach ball
    driveFor(-4.5, 100); //drive back and hit wall to align bot
    driveFor(0.48, 100); //drive slowly forward to avoid hitting wall when turning
    task::sleep(300); //sleep for 0.3 seconds
    turn(-170.0); //turn right to face flags
    task::sleep(300); //sleep for 0.3 seconds
    driveFor(2.4, 100); //drive forwards
    task::sleep(300); //sleep for 0.3 seconds
    RollerMotor.stop(); //stops roller
    shoot(); //shoot
    turn(-20.0);
    driveFor(1.6, 60); //drive slowly into low flag and align w wall
    driveFor(-5.4, 90); //drive backwards for platform
    turn(-153.0); //turn so that back is facing platform
    driveFor(-6.0, 100); //drive into platform
}

void BlueInsideLowFlag( void ){
    shoot(); //shoot high flag
    RollerMotor.spin(directionType::fwd,100,velocityUnits::pct); //turn on roller
    turn(150.0); //turn left to face cap w ball
    task::sleep(300); //stop for 0.3 seconds to avoid drifting
    driveFor(3.0, 100); //drive for 3 tiles to get ball
    driveFor(0.6, 40); //drive slowly to approach ball
    driveFor(-4.5, 100); //drive back and hit wall to align bot
    driveFor(0.48, 100); //drive slowly forward to avoid hitting wall when turning
    task::sleep(300); //sleep for 0.3 seconds
    turn(-165.0); //turn right to face flags
    task::sleep(300); //sleep for 0.3 seconds
    driveFor(2.4, 100); //drive forwards
    task::sleep(300); //sleep for 0.3 seconds
    RollerMotor.stop(); //stops roller
    shoot(); //shoot
    turn(-20.0);
    driveFor(1.6, 60); //drive slowly into low flag and align w wall
    driveFor(2.0, 40); //drive backwards for medium flag
}


/*****OUTSIDE AUTON*****/

void Outside ( void ){
    RollerMotor.spin(directionType::rev,100,velocityUnits::pct);
    driveFor(3.6, 40);
}


/*****RED INSIDE AUTON*****/

void RedInsidePlatform( void ){
    shoot(); //shoot high flag
    RollerMotor.spin(directionType::fwd,100,velocityUnits::pct); //turn on roller
    turn(-160.0); //turn left to face cap w ball
    task::sleep(300); //stop for 0.3 seconds to avoid drifting
    driveFor(3.0, 100); //drive for 3 tiles to get ball
    driveFor(0.6, 40); //drive slowly to approach ball
    driveFor(-4.5, 100); //drive back and hit wall to align bot
    driveFor(0.41, 100); //drive slowly forward to avoid hitting wall when turning
    task::sleep(300); //sleep for 0.3 seconds
    turn(140.0); //turn right to face flags
    driveFor(2.55, 100); //drive forwards to hit medium flag
    shoot(); //shoot
    task::sleep(300); //sleep for 0.3 seconds
    RollerMotor.stop(); //stop roller motor
    driveFor(-4.36, 100); //drive back to reach platform
    task::sleep(300); //sleep for 0.3 seconds
    turn(135.0); //turn so that back is facing platform
    task::sleep(300);
    driveFor(-5.0, 100); //drive into platform

}

void RedInsideLowFlag( void ){
    shoot(); //shoot high flag
    RollerMotor.spin(directionType::fwd,100,velocityUnits::pct); //turn on roller
    turn(-160.0); //turn left to face cap w ball
    task::sleep(300); //stop for 0.3 seconds to avoid drifting
    driveFor(3.0, 100); //drive for 3 tiles to get ball
    driveFor(0.6, 40); //drive slowly to approach ball
    driveFor(-4.5, 100); //drive back and hit wall to align bot
    driveFor(0.41, 100); //drive slowly forward to avoid hitting wall when turning
    task::sleep(300); //sleep for 0.3 seconds
    turn(140.0); //turn right to face flags
    task::sleep(300); //sleep for 0.3 seconds
    driveFor(0.5, 40); //drive slowly initially
    turn(22.0); //turn to face low flag
    task::sleep(300); //sleep for 0.3 seconds
    driveFor(2.7, 100); //drive forwards
    task::sleep(300); //sleep for 0.3 seconds
    RollerMotor.stop(); //stops roller
    driveFor(1.6, 60); //drive slowly into low flag and align w wall
    driveFor(-2.0, 40); //drive backwards for medium flag
    turn(-27.0); //turn to aim for medium flag
    shoot(); //shoot
    turn(22.0);
}

/*************************************************
 * Controller Binds
*/

int getNumDirectionButtonsPressed()
{
	int n = 0;
	
    /*
    Replace with
    
    if (SLOW_LEFT->pressing())
		n++;
	if (SLOW_RIGHT->pressing())
		n++;
	if (SLOW_UP->pressing())
		n++;
    
    if using diff buttons
    */
    
	if (Controller1.ButtonLeft.pressing())
		n++;
	if (Controller1.ButtonRight.pressing())
		n++;
	if (Controller1.ButtonUp.pressing())
		n++;
		
	return n;
}

bool checkOnlyDirectionButtonPressed()
{ //returns true if only one direction button is pressed
	return (getNumDirectionButtonsPressed() == 1);
}

// sets controller binds for user control
void setUserControlBinds(void)
{
	/* RIGHT BUMPERS */
	LAUNCH_BUTTON->pressed([] ()
	{ // these are called anonymous functions
		LauncherMotor.spin(directionType::fwd, 100, velocityUnits::pct);
	});
	LAUNCH_BUTTON->released([] ()
	{
		LauncherMotor.stop();
	});
	
	/* LEFT BUMPERS	*/
	INTAKE_IN->pressed([] ()
	{
		if (!INTAKE_OUT->pressing())
		{ //if ButtonL2 is pressed, don't do anything
			RollerMotor.spin(directionType::rev, 100, velocityUnits::pct);
		}
	});
	INTAKE_IN->released([] ()
	{
		if (!INTAKE_OUT->pressing())
		{ //if ButtonL2 is pressed, don't do anything
			RollerMotor.stop();
		}
	});
	
	INTAKE_OUT->pressed([] ()
	{
		if (!INTAKE_IN->pressing())
		{ //if ButtonL1 is pressed, don't do anything
			RollerMotor.spin(directionType::fwd, 100, velocityUnits::pct);
		}
	});
	INTAKE_OUT->released([] ()
	{
		if (!INTAKE_IN->pressing())
		{ //if ButtonL1 is pressed, don't do anything
			RollerMotor.stop();
		}
	});
	
	/*	DIRECTION BUTTONS	*/
	SLOW_LEFT->pressed([] ()
	{
		/*
		 * ONLY RUNS THE CODE IF NONE OF THE OTHER
		 * DIRECTION BUTTONS ARE PRESSED
		 */
		 
		if (checkOnlyDirectionButtonPressed())
		{
			RightMotorFront.spin(directionType::fwd, 7, velocityUnits::pct);
            LeftMotorFront.spin(directionType::rev, 7, velocityUnits::pct);
            RightMotorBack.spin(directionType::fwd, 7, velocityUnits::pct);
            LeftMotorBack.spin(directionType::rev, 7, velocityUnits::pct);
		}
	});
	SLOW_RIGHT->pressed([] ()
	{
		if (checkOnlyDirectionButtonPressed())
		{
			RightMotorFront.spin(directionType::rev, 7, velocityUnits::pct);
            LeftMotorFront.spin(directionType::fwd, 7, velocityUnits::pct);
            RightMotorBack.spin(directionType::rev, 7, velocityUnits::pct);
            LeftMotorBack.spin(directionType::fwd, 7, velocityUnits::pct);
		}
	});
	SLOW_UP->pressed([] ()
	{
		if (checkOnlyDirectionButtonPressed())
		{
			RightMotorFront.spin(directionType::fwd, 35, velocityUnits::pct);
            LeftMotorFront.spin(directionType::fwd, 35, velocityUnits::pct);
            RightMotorBack.spin(directionType::fwd, 35, velocityUnits::pct);
            LeftMotorBack.spin(directionType::fwd, 35, velocityUnits::pct);
		}
	});
}

/*****OPERATOR CONTROL*****/

void usercontrol( void )
{
	setUserControlBinds();

    while (1)
	{
		RightMotorFront.spin(directionType::fwd, (VERTICAL_AXIS->value() - HORIZONTAL_AXIS->value()), velocityUnits::pct);
		LeftMotorFront.spin(directionType::fwd, (VERTICAL_AXIS->value() + HORIZONTAL_AXIS->value()), velocityUnits::pct);
		RightMotorBack.spin(directionType::fwd, (VERTICAL_AXIS->value() - HORIZONTAL_AXIS->value()), velocityUnits::pct);
		LeftMotorBack.spin(directionType::fwd, (VERTICAL_AXIS->value() + HORIZONTAL_AXIS->value()), velocityUnits::pct);
		
        task::sleep(20);
    }
}


/*****MAIN METHOD*****/

int main() {

    pre_auton();

    switch(selectAuton()) {
        case 1:
            comp.autonomous( RedInsideLowFlag );
            break;
        case 2:
            comp.autonomous( RedInsidePlatform );
            break;
        case 3:
            comp.autonomous( Outside );
            break;
        case 4:
            comp.autonomous( BlueInsideLowFlag );
            break;
        case 5:
            comp.autonomous( BlueInsidePlatform );
            break;
        case 6:
            comp.autonomous( Outside );
            break;
    }

    Brain.Screen.clearScreen();

    comp.drivercontrol( usercontrol );

    while(1) {
        task::sleep(100);
    }
}
