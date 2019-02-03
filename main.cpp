#include "robot-config.h"

vex::competition Competition;

const float TILE_LENGTH = 12.5;
const float TURNING_DIAMETER = 17.5;
const float WHEEL_DIAMETER = 4.125;

const bool RedInside = false;
const bool BlueInside = false;
const bool Outside = false;
const bool ProgrammingSkills = false;
const bool DriverSkills = false;



void pre_auton( void ) {

}

void driveFor( float tiles ){
    float length = tiles * TILE_LENGTH;
    float circum =  3.141592653589 * WHEEL_DIAMETER;
    float rotations = length / circum;
    float degrees = 360 * rotations;

    RightMotorFront.startRotateFor(degrees, vex::rotationUnits::deg, 100, vex::velocityUnits::pct);
    LeftMotorFront.startRotateFor(degrees, vex::rotationUnits::deg, 100, vex::velocityUnits::pct);
    RightMotorBack.startRotateFor(degrees, vex::rotationUnits::deg, 100, vex::velocityUnits::pct);
    LeftMotorBack.rotateFor(degrees, vex::rotationUnits::deg, 100, vex::velocityUnits::pct);

}

void turn( float degrees ){
    float turningRatio = TURNING_DIAMETER / WHEEL_DIAMETER;

    int turnSpeed = 60;

    RightMotorFront.startRotateFor(degrees * turningRatio / 2, vex::rotationUnits::deg, turnSpeed, vex::velocityUnits::pct);
    LeftMotorFront.startRotateFor(-degrees * turningRatio / 2, vex::rotationUnits::deg, turnSpeed, vex::velocityUnits::pct);
    RightMotorBack.startRotateFor(degrees * turningRatio / 2, vex::rotationUnits::deg, turnSpeed, vex::velocityUnits::pct);
    LeftMotorBack.rotateFor(-degrees * turningRatio / 2, vex::rotationUnits::deg, turnSpeed, vex::velocityUnits::pct);
}

void shoot( void ){
    LauncherMotor.rotateFor(1.4, vex::timeUnits::sec, 100, vex::velocityUnits::pct);
}

void driveSlowlyFor( float tiles  ){

    float length = tiles * TILE_LENGTH;
    float circum =  3.141592653589 * WHEEL_DIAMETER;
    float rotations = length / circum;
    float degrees = 360 * rotations;

    RightMotorFront.startRotateFor(degrees, vex::rotationUnits::deg, 40, vex::velocityUnits::pct);
    LeftMotorFront.startRotateFor(degrees, vex::rotationUnits::deg, 40, vex::velocityUnits::pct);
    RightMotorBack.startRotateFor(degrees, vex::rotationUnits::deg, 40, vex::velocityUnits::pct);
    LeftMotorBack.rotateFor(degrees, vex::rotationUnits::deg, 40, vex::velocityUnits::pct);
}

void driveMediumFor( float tiles  ){

    float length = tiles * TILE_LENGTH;
    float circum =  3.141592653589 * WHEEL_DIAMETER;
    float rotations = length / circum;
    float degrees = 360 * rotations;

    RightMotorFront.startRotateFor(degrees, vex::rotationUnits::deg, 60, vex::velocityUnits::pct);
    LeftMotorFront.startRotateFor(degrees, vex::rotationUnits::deg, 60, vex::velocityUnits::pct);
    RightMotorBack.startRotateFor(degrees, vex::rotationUnits::deg, 60, vex::velocityUnits::pct);
    LeftMotorBack.rotateFor(degrees, vex::rotationUnits::deg, 60, vex::velocityUnits::pct);
}

void rumbleTimer(void) {
    vex::task::sleep(20000);
    Controller1.rumble("-");
    vex::task::sleep(20000);
    Controller1.rumble("--");
    vex::task::sleep(10000);
    Controller1.rumble("---");
}

void autonomous( void ) {

    //Positive = counter-clockwise
    //Negative = clockwise

    if(BlueInside){
        shoot(); //shoot high flag
        RollerMotor.spin(vex::directionType::fwd,100,vex::velocityUnits::pct); //turn on roller
        turn(150.0); //turn left to face cap w ball
        vex::task::sleep(300); //stop for 0.3 seconds to avoid drifting
        driveFor(3.0); //drive for 3 tiles to get ball
        driveSlowlyFor(0.6); //drive slowly to approach ball
        driveFor(-4.5); //drive back and hit wall to align bot
        driveFor(0.48); //drive slowly forward to avoid hitting wall when turning
        vex::task::sleep(300); //sleep for 0.3 seconds
        turn(-165.0); //turn right to face flags
        vex::task::sleep(300); //sleep for 0.3 seconds

        //8 point auton with platform
        /*driveFor(2.55); //drive forwards to hit medium flag
         shoot(); //shoot
         vex::task::sleep(300); //sleep for 0.3 seconds
         RollerMotor.stop(); //stop roller motor
         driveFor(-4.23); //drive back to reach platform
         vex::task::sleep(300); //sleep for 0.3 seconds
         turn(-152.0); //turn so that back is facing platform
         driveFor(-5.0); //drive into platform*/

        //6 point auton without platform
        //driveSlowlyFor(0.5); //drive slowly initially
        //turn(-20.0); //turn to face low flag
        vex::task::sleep(300); //sleep for 0.3 seconds
        driveFor(2.4); //drive forwards
        vex::task::sleep(300); //sleep for 0.3 seconds
        RollerMotor.stop(); //stops roller
        turn(20.0);
        shoot(); //shoot
        turn(-20.0);
        driveMediumFor(1.6); //drive slowly into low flag and align w wall
        driveSlowlyFor(2.0); //drive backwards for medium flag
    }

    if(Outside){
        RollerMotor.spin(vex::directionType::rev,100,vex::velocityUnits::pct);
        driveSlowlyFor(3.6);
    }

    if(RedInside){
        shoot(); //shoot high flag
        RollerMotor.spin(vex::directionType::fwd,100,vex::velocityUnits::pct); //turn on roller
        turn(-160.0); //turn left to face cap w ball
        vex::task::sleep(300); //stop for 0.3 seconds to avoid drifting
        driveFor(3.0); //drive for 3 tiles to get ball
        driveSlowlyFor(0.6); //drive slowly to approach ball
        driveFor(-4.5); //drive back and hit wall to align bot
        driveFor(0.41); //drive slowly forward to avoid hitting wall when turning
        vex::task::sleep(300); //sleep for 0.3 seconds
        turn(140.0); //turn right to face flags
        vex::task::sleep(300); //sleep for 0.3 seconds

        //8 point auton with platform
        /*driveFor(2.55); //drive forwards to hit medium flag
         shoot(); //shoot
         vex::task::sleep(300); //sleep for 0.3 seconds
         RollerMotor.stop(); //stop roller motor
         driveFor(-4.36); //drive back to reach platform
         vex::task::sleep(300); //sleep for 0.3 seconds
         turn(135.0); //turn so that back is facing platform
         vex::task::sleep(300);
         driveFor(-5.0); //drive into platform*/

        //6 point auton without platform
        driveSlowlyFor(0.5); //drive slowly initially
        turn(22.0); //turn to face low flag
        vex::task::sleep(300); //sleep for 0.3 seconds
        driveFor(2.7); //drive forwards
        vex::task::sleep(300); //sleep for 0.3 seconds
        RollerMotor.stop(); //stops roller
        driveMediumFor(1.6); //drive slowly into low flag and align w wall
        driveSlowlyFor(-2.0); //drive backwards for medium flag
        turn(-27.0); //turn to aim for medium flag
        shoot(); //shoot
        turn(22.0);
    }

    if(ProgrammingSkills){
        shoot();
        driveFor(3.2);
    }
}


void usercontrol( void ) {

    if(DriverSkills) {
        vex::thread rumbleThread = vex::thread(rumbleTimer);
    }

    while (1) {

        int left = Controller1.Axis3.value();
        int right = -(Controller1.Axis1.value());

        RightMotorFront.spin(vex::directionType::fwd, (left + right), vex::velocityUnits::pct);
        LeftMotorFront.spin(vex::directionType::fwd, (left - right), vex::velocityUnits::pct);
        RightMotorBack.spin(vex::directionType::fwd, (left + right), vex::velocityUnits::pct);
        LeftMotorBack.spin(vex::directionType::fwd, (left - right), vex::velocityUnits::pct);

        if(Controller1.ButtonR1.pressing()){
            LauncherMotor.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
        }
        else{
            LauncherMotor.stop();
        }

        if(Controller1.ButtonL1.pressing()){
            RollerMotor.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
        }
        else if(Controller1.ButtonL2.pressing()){
            RollerMotor.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
        }
        else{
            RollerMotor.stop();
        }

        if(Controller1.ButtonLeft.pressing()){
            RightMotorFront.spin(vex::directionType::fwd, 7, vex::velocityUnits::pct);
            LeftMotorFront.spin(vex::directionType::rev, 7, vex::velocityUnits::pct);
            RightMotorBack.spin(vex::directionType::fwd, 7, vex::velocityUnits::pct);
            LeftMotorBack.spin(vex::directionType::rev, 7, vex::velocityUnits::pct);
        }
        else if(Controller1.ButtonRight.pressing()){
            RightMotorFront.spin(vex::directionType::rev, 7, vex::velocityUnits::pct);
            LeftMotorFront.spin(vex::directionType::fwd, 7, vex::velocityUnits::pct);
            RightMotorBack.spin(vex::directionType::rev, 7, vex::velocityUnits::pct);
            LeftMotorBack.spin(vex::directionType::fwd, 7, vex::velocityUnits::pct);
        }

        if(Controller1.ButtonUp.pressing()){
            RightMotorFront.spin(vex::directionType::fwd, 35, vex::velocityUnits::pct);
            LeftMotorFront.spin(vex::directionType::fwd, 35, vex::velocityUnits::pct);
            RightMotorBack.spin(vex::directionType::fwd, 35, vex::velocityUnits::pct);
            LeftMotorBack.spin(vex::directionType::fwd, 35, vex::velocityUnits::pct);
        }

        if(Controller1.ButtonX.pressing()){
            OneBarMotor.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
        }
        else if(Controller1.ButtonB.pressing()){
            OneBarMotor.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
        }
        else if(Controller1.ButtonA.pressing()){
            OneBarMotor.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
        }
        else{
            OneBarMotor.stop();
        }

        vex::task::sleep(20);
    }
}


int main() {

    pre_auton();

    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );

    while(1) {
        vex::task::sleep(100);
    }

}
