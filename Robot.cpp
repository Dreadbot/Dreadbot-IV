#include "WPILib.h"
#include "Input.h"

class Robot : public IterativeRobot {
	Joystick* gamepad; 
	OctocanumDrive* drivetrain;
	Input* input;
public:
	
void Robot::RobotInit() {
	gamepad = new Joystick(1);
	drivetrain = new OctocanumDrive();
	input = new Input(gamepad, drivetrain);
	SmartDashboard::init();
}

void Robot::DisabledInit() {
}

void Robot::DisabledPeriodic() {
}

void Robot::AutonomousInit() {
}

void Robot::AutonomousPeriodic() {
}

void Robot::TeleopInit() {
}

void Robot::TeleopPeriodic() {
	input->Update();
}

void Robot::TestInit() {
}


void Robot::TestPeriodic() {
}

};

START_ROBOT_CLASS(Robot);

