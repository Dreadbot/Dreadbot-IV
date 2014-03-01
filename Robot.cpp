#include "WPILib.h"
#include "Input.h"
#include "Vision.h"
#include "Valve.h"

class Robot : public IterativeRobot 
{
	// Components
	DriverStation* ds;
	Joystick* gamepad;
	Joystick* shootPad;
	OctocanumDrive* drivetrain;
	Input* input;

	Compressor* compressor;
	Watchdog* watchdog;

	Vision* camera;
	AnalogChannel* flipPot;
	DigitalInput* shooterSwitch;
	Shooter* shooter;
	Relay* winchMotor; //This thing asked me to RELAY a message: It's a relay!
	Talon* rollerMotor;
	Talon* flipperMotor;
	DoubleSolenoid* armPneus;
	Valve* shooterReleaser;
	ArmControl* arms;

	// System variables
	bool autonDone; //True when autonomous mode has executed
	bool ballLoaded;

public:
	
void Robot::RobotInit() 
{
	SmartDashboard::init();
	ds = DriverStation::GetInstance();
	gamepad = new Joystick(1);
	shootPad = new Joystick(2);
	drivetrain = new OctocanumDrive();
	compressor = new Compressor(1, 8);

	watchdog = &GetWatchdog();
	watchdog->SetEnabled(false);

	camera = new Vision();
	flipPot = new AnalogChannel(2);
	armPneus = new DoubleSolenoid(5, 6);
	flipperMotor = new Talon(6);
	shooterSwitch = new DigitalInput(8);
	shooterReleaser = new Valve(7, 8);
	winchMotor = new Relay(5);
	rollerMotor = new Talon(7);

	shooter = new Shooter(winchMotor, shooterSwitch, shooterReleaser);
	arms = new ArmControl(rollerMotor, flipperMotor, armPneus, flipPot);
	input = new Input(gamepad,
		shootPad,
		drivetrain,
		arms,
		shooter);
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

}
void Robot::TeleopInit()
{
	drivetrain->Enable();
	compressor->Start();
}

void Robot::TeleopPeriodic() 
{
	input->Update();
	SmartDashboard::PutBoolean("Test", true);
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

