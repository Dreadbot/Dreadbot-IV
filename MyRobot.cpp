#include "WPILib.h"
#include "Input.h"

class RobotDemo : public IterativeRobot
{
	Joystick* stick; 
	OctocanumDrive* biscuit;
	Input* football;
	
public:
	
void RobotDemo::RobotInit() 
{
	stick = new Joystick(1);
	biscuit = new OctocanumDrive();
	football = new Input(stick, biscuit);
	SmartDashboard::init();
}

void RobotDemo::DisabledInit() 
{
}

void RobotDemo::DisabledPeriodic()
{
}

void RobotDemo::AutonomousInit() 
{
}

void RobotDemo::AutonomousPeriodic() 
{
}

void RobotDemo::TeleopInit() 
{
}

void RobotDemo::TeleopPeriodic() 
{
	football->Update();
}

void RobotDemo::TestInit() {
}


void RobotDemo::TestPeriodic() 
{
}

};

START_ROBOT_CLASS(RobotDemo);

