//#define _SHOOTER




#include "WPILib.h"
#include "Input.h"

#include "Vision.h"


class Robot : public IterativeRobot 
{
	// Components
	DriverStation* ds;
	Joystick* gamepad; 
	OctocanumDrive* drivetrain;
	Input* input;
	Compressor* compressor;
	Watchdog* watchdog;
	Vision* vis;

	// System variables
	bool autonDone; //True when autonomous mode has executed
	bool ballLoaded;
public:
	
void Robot::RobotInit() 
{
	SmartDashboard::init();
	ds = DriverStation::GetInstance();
	gamepad = new Joystick(1);
	drivetrain = new OctocanumDrive();
	input = new Input(gamepad, drivetrain);
	compressor = new Compressor(1, 8);
	watchdog = &GetWatchdog();
	watchdog->SetEnabled(false);
		
	vis = new Vision();
}

void Robot::DisabledInit()
{
	ds->InTest(false);
	ds->InOperatorControl(false);
	ds->InAutonomous(false);
	ds->InDisabled(true);

	compressor->Stop();
	//shooter->release();
}

void Robot::DisabledPeriodic()
{
}

void Robot::AutonomousInit()
{
	ds->InTest(false);
	ds->InOperatorControl(false);
	ds->InAutonomous(true);
	ds->InDisabled(false);

	autonDone = false;
	drivetrain->Enable();
	compressor->Start();
}

void Robot::AutonomousPeriodic()
{
	if (!autonDone) return;

	drivetrain->Drop();
	Wait(0.75);
	drivetrain->Drive(0.0, 0.0, 0.2);
	//while the hot goal isn't in the crosshairs
		Wait(0.033);
	//end
	drivetrain->Drive(0.0, 0.2, 0.0);
	Wait(1);
	Wait(1);
	drivetrain->Drive(0.0, 0.0, 0.0);
	autonDone = true;
}


void Robot::TeleopInit()
{
	ds->InTest(false);
	ds->InOperatorControl(true);
	ds->InAutonomous(false);
	ds->InDisabled(false);

	drivetrain->Enable();
	compressor->Start();
}

void Robot::TeleopPeriodic() 
{
	input->Update();
	watchdog->Feed();
	vis->isHot();
}


void Robot::TestInit()
{
	ds->InTest(true);
	ds->InOperatorControl(false);
	ds->InAutonomous(false);
	ds->InDisabled(false);
}

void Robot::TestPeriodic()
{
}

};

START_ROBOT_CLASS(Robot);

