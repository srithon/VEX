#include "robot-config.h"

vex::competition Competition;

const float TILE_LENGTH = 12.5;
const float TURNING_DIAMETER = 17.5;
const float WHEEL_DIAMETER = 4.125;

const bool RedInside = false;
const bool BlueInside = false;
const bool Outside = true;
const bool Skills = false;



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
    
    RightMotorFront.startRotateFor(degrees * turningRatio / 2, vex::rotationUnits::deg, 100, vex::velocityUnits::pct);
    LeftMotorFront.startRotateFor(-degrees * turningRatio / 2, vex::rotationUnits::deg, 100, vex::velocityUnits::pct);
    RightMotorBack.startRotateFor(degrees * turningRatio / 2, vex::rotationUnits::deg, 100, vex::velocityUnits::pct);
    LeftMotorBack.rotateFor(-degrees * turningRatio / 2, vex::rotationUnits::deg, 100, vex::velocityUnits::pct);
}

void shoot( void ){
    LauncherMotor.rotateFor(1, vex::timeUnits::sec, 100, vex::velocityUnits::pct);
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

void autonomous( void ) {
    
    //Positive = counter-clockwise
    //Negative = clockwise
    
    if(BlueInside){
        shoot();
        turn(160.0);
        driveFor(3.2);
        driveSlowlyFor(0.6);
        RollerMotor.startRotateFor(1500,vex::rotationUnits::deg,100,vex::velocityUnits::pct);
        driveFor(-2.8);
    }
    
    if(Outside){
        RollerMotor.spin(vex::directionType::rev,100,vex::velocityUnits::pct);
        driveSlowlyFor(3.6);
    }
    
    if(RedInside){
        shoot();
        turn(-160.0);
        driveFor(3.2);
        RollerMotor.startRotateFor(-1200,vex::rotationUnits::deg,100,vex::velocityUnits::pct);
        driveSlowlyFor(0.6);
        driveFor(-2.8);
    }
    
    if(Skills){
        shoot();
        driveFor(3.2);
    }
}


void usercontrol( void ) {
    Controller1.Screen.print("Welcome Aboard Captain");
    Controller1.Screen.newLine();
    Controller1.Screen.print("Get ready to rumble!!!");
    Controller1.Screen.newLine();

    Controller1.Screen.print("FORWARD MODE!");
    Controller1.Screen.newLine();
    Controller1.rumble("--..-");
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