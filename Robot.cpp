//this will be the official main class

#include "WPILib.h"
#include "Input.h"

class Robot : public IterativeRobot {
	Joystick* gamepad; 
	OctocanumDrive* drivetrain;
	Input* input;
public:
	
void Robot::RobotInit() 
{
	SmartDashboard::init();
	gamepad = new Joystick(1);
	drivetrain = new OctocanumDrive();
	input = new Input(gamepad, drivetrain);
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
	drivetrain->Enable();
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

