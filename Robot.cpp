//this will be the official main class

#include "WPILib.h"
#include "Input.h"
#include "Shooter.h"

class Robot : public IterativeRobot 
{
	Joystick* gamepad;
	Joystick* shootPad;
	OctocanumDrive* drivetrain;
	Input* input;
	Compressor* compress;
	Shooter* shooter;

	
	bool autonDone; //Has auton executed?
	Talon* winchMotor;
	DigitalInput* winchSwitch;
	Solenoid* releaser;
	Shooter* shooter;
public:
	
void Robot::RobotInit() 
{
	SmartDashboard::init();
	gamepad = new Joystick(1);
	shootPad = new Joystick(2);
	drivetrain = new OctocanumDrive();
	input = new Input(gamepad, drivetrain);
	compress = new Compressor(1, 8);
	winchMotor = new Talon(5);
	winchSwitch = new DigitalInput(8);
	releaser = new Solenoid(9000); //STANDIN VALUE! CHANGE BEFORE USE!
	shooter = new Shooter(winchMotor, winchSwitch, releaser);
}

void Robot::DisabledInit()
{
	compress->Stop();
	shoot->release();
}

void Robot::DisabledPeriodic()
{
}



void Robot::AutonomousInit()
{
	autonDone = false;
}

void Robot::AutonomousPeriodic()
{
	if (!autonDone)
	{
		shoot->release();
		drivetrain->Drop();
		Wait(1.0);
		drivetrain->Drive(0, .2, 0);
		Wait(2.0); //Drive forward for 2 seconds at .2 power
		drivetrain->Drive(0, 0, 1);
		Wait(1.0);
		autonDone = true;
	}
}
void Robot::TeleopInit()
{
	drivetrain->Enable();
	compress->Start();
}

void Robot::TeleopPeriodic() 
{
	input->Update();
}

void Robot::TestInit()
{
}


void Robot::TestPeriodic()
{
}

};

START_ROBOT_CLASS(Robot);

