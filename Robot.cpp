//#define _SHOOTER




#include "WPILib.h"
#include "Input.h"
#ifdef _SHOOTER
	#include "Shooter.h"
#endif


class Robot : public IterativeRobot 
{
	// Components
	DriverStation* ds;
	Joystick* gamepad;
	OctocanumDrive* drivetrain;
	Input* input;
	Compressor* compressor;
	Watchdog* watchdog;
	#ifdef _SHOOTER
		Shooter* shooter;
		Talon* winchMotor;
		Encoder* winchEncoder;
	#endif

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
	#ifdef _SHOOTER
		winchMotor = new Talon(5); // relay
		winchEncoder = new Encoder(2, 3);
		shooter = new Shooter(winchMotor, winchEncoder);
	#endif
}

void Robot::DisabledInit()
{
	compressor->Stop();
	//shooter->release();
}

void Robot::DisabledPeriodic()
{
}



void Robot::AutonomousInit()
{

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
	#ifdef _SHOOTER
		shoot->release();
	#endif
	Wait(1);
	drivetrain->Drive(0.0, 0.0, 0.0);
	autonDone = true;
}


void Robot::TeleopInit()
{

	drivetrain->Enable();
	compressor->Start();
}

void Robot::TeleopPeriodic() 
{
	input->Update();
//	watchdog->Feed();
}


void Robot::TestInit()
{
}

void Robot::TestPeriodic()
{
}

};

START_ROBOT_CLASS(Robot);

