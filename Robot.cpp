//this will be the official main class

#include "WPILib.h"
#include "Input.h"

class Robot : public IterativeRobot {
	Joystick* gamepad; 
	OctocanumDrive* drivetrain;
	Input* input;
	Compressor* compress;
public:
	
void Robot::RobotInit() 
{
	SmartDashboard::init();
	gamepad = new Joystick(1);
	drivetrain = new OctocanumDrive();
	input = new Input(gamepad, drivetrain);
	compress = new Compressor(1, 8);
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
	//compress->Start();
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

