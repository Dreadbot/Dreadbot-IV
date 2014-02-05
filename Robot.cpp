#include "WPILib.h"
#include "Input.h"

class Robot : public IterativeRobot
{
	Joystick* stick; 
	OctocanumDrive* biscuit;
	Input* football; //nice
	
public:
	
void Robot::RobotInit() 
{
	stick = new Joystick(1);
	biscuit = new OctocanumDrive();
	football = new Input(stick, biscuit);
	SmartDashboard::init();
}

void Robot::DisabledInit() 
{
}

void Robot::DisabledPeriodic()
{
}

void Robot::AutonomousInit() 
{
}

void Robot::AutonomousPeriodic() 
{
}

void Robot::TeleopInit() 
{
}

void Robot::TeleopPeriodic() 
{
	football->Update();
}

void Robot::TestInit()
{
}


void Robot::TestPeriodic() 
{
}

};

START_ROBOT_CLASS(Robot);

