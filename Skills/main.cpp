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

//constant for DriverSkills
const bool DriverSkills = true;


/*****RUMBLE THREAD*****/
void rumbleTimer(void) {
    task::sleep(20000);
    Controller1.rumble("-");
    task::sleep(20000);
    Controller1.rumble("--");
    task::sleep(10000);
    Controller1.rumble("---");
}


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

/*****PROGRAMMING SKILLS*****/

void ProgrammingSkills( void ) {
    shoot();
    driveFor(3.2, 100);
}

/*****OPERATOR CONTROL*****/

/*************************************************
 * Controller Binds
*/

int getNumDirectionButtonsPressed()
{
	int n = 0;
	
	if (Controller1.ButtonLeft.pressing())
		n++;
	if (Controller1.ButtonRight.pressing())
		n++;
	if (Controller1.ButtonUp.pressing())
		n++;
/*	if (Controller1.ButtonDown.pressing())
    	n++;	*/
	
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
			RightMotorFront.spin(directionType::fwd, 40, velocityUnits::pct);
            LeftMotorFront.spin(directionType::fwd, 40, velocityUnits::pct);
            RightMotorBack.spin(directionType::fwd, 40, velocityUnits::pct);
            LeftMotorBack.spin(directionType::fwd, 40, velocityUnits::pct);
		}
	});
}

void usercontrol( void ) {

    if(DriverSkills) {
        thread rumbleThread = thread(rumbleTimer);
    }
	
	setUserControlBinds();

	float turningModifier = 0.80;
	//OPTIONAL - CHANGE TYPE TO DOUBLE

    while (1) {
		RightMotorFront.spin(directionType::fwd, (VERTICAL_AXIS->value() - (HORIZONTAL_AXIS->value() * turningModifier)), velocityUnits::pct);
		LeftMotorFront.spin(directionType::fwd, (VERTICAL_AXIS->value() + (HORIZONTAL_AXIS->value() * turningModifier)), velocityUnits::pct);
		RightMotorBack.spin(directionType::fwd, (VERTICAL_AXIS->value() - (HORIZONTAL_AXIS->value() * turningModifier)), velocityUnits::pct);
		LeftMotorBack.spin(directionType::fwd, (VERTICAL_AXIS->value() + (HORIZONTAL_AXIS->value() * turningModifier)), velocityUnits::pct);

        task::sleep(20);
    }
}


/*****MAIN METHOD*****/

int main() {

    pre_auton();

    comp.drivercontrol(usercontrol);

    while(1) {
        task::sleep(100);
    }
}
