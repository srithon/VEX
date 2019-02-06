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


/**************************************************/
/*Auton Constants*/

const bool RedInside = false;
const bool BlueInside = true;
const bool Outside = false;
const bool ProgrammingSkills = false;
const bool DriverSkills = false;
/**************************************************/


void pre_auton( void ) {

}


/**************************************************
*
* Auton methods
* driveFor(float tiles, int speed);
* turn(float degrees);
* shoot(void);
*
**************************************************/


void driveFor(float tiles, int speed){
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


void turn(float degrees){
    const float TURNING_DIAMETER = 17.5;
    float turningRatio = TURNING_DIAMETER / WHEEL_DIAMETER;
    int turnSpeed = 60;

    RightMotorFront.startRotateFor(degrees * turningRatio / 2, rotationUnits::deg, turnSpeed, velocityUnits::pct);
    LeftMotorFront.startRotateFor(-degrees * turningRatio / 2, rotationUnits::deg, turnSpeed, velocityUnits::pct);
    RightMotorBack.startRotateFor(degrees * turningRatio / 2, rotationUnits::deg, turnSpeed, velocityUnits::pct);
    LeftMotorBack.rotateFor(-degrees * turningRatio / 2, rotationUnits::deg, turnSpeed, velocityUnits::pct);
}


void shoot(void){
    LauncherMotor.rotateFor(1.4, timeUnits::sec, 100, velocityUnits::pct);
}


/**************************************************/
/*Rumble Thread*/

void rumbleTimer(void) {
    task::sleep(20000);
    Controller1.rumble("-");
    task::sleep(20000);
    Controller1.rumble("--");
    task::sleep(10000);
    Controller1.rumble("---");
}

/**************************************************/

void autonomous(void) {

    //Positive = counter-clockwise
    //Negative = clockwise

    if(BlueInside){
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

        //8 point auton with platform
        /*driveFor(2.55, 100); //drive forwards to hit medium flag
        shoot(); //shoot
        task::sleep(300); //sleep for 0.3 seconds
        RollerMotor.stop(); //stop roller motor
        driveFor(-4.23, 100); //drive back to reach platform
        task::sleep(300); //sleep for 0.3 seconds
        turn(-152.0); //turn so that back is facing platform
        driveFor(-5.0, 100); //drive into platform*/

        //9 point auton with low flag and platform
        //driveSlowlyFor(0.5); //drive slowly initially
        //turn(-20.0); //turn to face low flag
        task::sleep(300); //sleep for 0.3 seconds
        driveFor(2.4, 100); //drive forwards
        task::sleep(300); //sleep for 0.3 seconds
        RollerMotor.stop(); //stops roller
        shoot(); //shoot
        turn(-20.0);
        driveFor(1.6, 60); //drive slowly into low flag and align w wall
        driveFor(-5.4, 60); //drive backwards for platform
        turn(-153.0); //turn so that back is facing platform
        driveFor(-6.0, 100); //drive into platform
    }

    if(Outside){
        RollerMotor.spin(directionType::rev,100,velocityUnits::pct);
        driveFor(3.6, 40);
    }

    if(RedInside){
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

        //8 point auton with platform
        /*driveFor(2.55, 100); //drive forwards to hit medium flag
        shoot(); //shoot
        task::sleep(300); //sleep for 0.3 seconds
        RollerMotor.stop(); //stop roller motor
        driveFor(-4.36, 100); //drive back to reach platform
        task::sleep(300); //sleep for 0.3 seconds
        turn(135.0); //turn so that back is facing platform
        task::sleep(300);
        driveFor(-5.0, 100); //drive into platform*/

        //6 point auton without platform
        driveFor(0.5, 40); //drive slowly initially
        turn(22.0); //turn to face low flag
        task::sleep(300); //sleep for 0.3 seconds
        driveFor(2.7, 100); //drive forwards
        task::sleep(300); //sleep for 0.3 seconds
        RollerMotor.stop(); //stops roller
        driveFor(1.6, 60); //drive slowly into low flag and align w wall
        driveFor(-2.0, 40); //drive backwards for medium flag
        shoot(); //shoot
        turn(22.0);
    }

    if(ProgrammingSkills){
        shoot();
        driveFor(3.2, 100);
    }
}


void usercontrol(void) {

    double driveSpeedMultiplier = 1.00;

    if(DriverSkills) {
        thread rumbleThread = thread(rumbleTimer);
    }

    while (1) {

        int left = Controller1.Axis3.value();
        int right = -(Controller1.Axis1.value());

        RightMotorFront.spin(directionType::fwd, (left + right) * driveSpeedMultiplier, velocityUnits::pct);
        LeftMotorFront.spin(directionType::fwd, (left - right) * driveSpeedMultiplier, velocityUnits::pct);
        RightMotorBack.spin(directionType::fwd, (left + right) * driveSpeedMultiplier, velocityUnits::pct);
        LeftMotorBack.spin(directionType::fwd, (left - right) * driveSpeedMultiplier, velocityUnits::pct);

        if(Controller1.ButtonR1.pressing()){
            LauncherMotor.spin(directionType::fwd, 100, velocityUnits::pct);
        }
        else{
            LauncherMotor.stop();
        }

        if (Controller1.ButtonR2.pressing()){
            driveSpeedMultiplier = 0.20;
        } else {
            driveSpeedMultiplier = 1.00;
        }


        if(Controller1.ButtonL1.pressing()){
            RollerMotor.spin(directionType::rev, 100, velocityUnits::pct);
        }
        else if(Controller1.ButtonL2.pressing()){
            RollerMotor.spin(directionType::fwd, 100, velocityUnits::pct);
        }
        else{
            RollerMotor.stop();
        }

        if(Controller1.ButtonLeft.pressing()){
            RightMotorFront.spin(directionType::fwd, 7, velocityUnits::pct);
            LeftMotorFront.spin(directionType::rev, 7, velocityUnits::pct);
            RightMotorBack.spin(directionType::fwd, 7, velocityUnits::pct);
            LeftMotorBack.spin(directionType::rev, 7, velocityUnits::pct);
        }
        else if(Controller1.ButtonRight.pressing()){
            RightMotorFront.spin(directionType::rev, 7, velocityUnits::pct);
            LeftMotorFront.spin(directionType::fwd, 7, velocityUnits::pct);
            RightMotorBack.spin(directionType::rev, 7, velocityUnits::pct);
            LeftMotorBack.spin(directionType::fwd, 7, velocityUnits::pct);
        }

        if(Controller1.ButtonUp.pressing()){
            RightMotorFront.spin(directionType::fwd, 35, velocityUnits::pct);
            LeftMotorFront.spin(directionType::fwd, 35, velocityUnits::pct);
            RightMotorBack.spin(directionType::fwd, 35, velocityUnits::pct);
            LeftMotorBack.spin(directionType::fwd, 35, velocityUnits::pct);
        }


        task::sleep(20);
    }
}


int main() {

    pre_auton();

    comp.autonomous(autonomous);
    comp.drivercontrol(usercontrol);

    while(1) {
      task::sleep(100);
    }

}
