// Finished merge (Parker)

#include "WPILib.h"
#include "Robot.h"
#include "Input.h"


class Robot : public IterativeRobot 
{
// Interface
	DriverStation* ds;
	Joystick* gamePad;
	Joystick* shootPad;

// System
	Watchdog* watchdog;
	Compressor* compressor;
	
// Drivetrain
	OctocanumDrive* drivetrain;
	Input* input;
	
// Shooter
	Encoder* flipPot;
	DigitalInput* shooterSwitch;
	Shooter* shooter;
	Talon* winchMotor;
	Encoder* winchEncoder;
	Talon* rollerMotor;
	Talon* flipperMotor;
	DoubleSolenoid* armPneus;
	Solenoid* shooterReleaser;
	ArmControl* arms;

// System state
	bool autonDone;		// True when autonomous mode has finished executing

public:
	
void Robot::RobotInit() 
{
// DS
	SmartDashboard::init();
	ds = DriverStation::GetInstance();

// Watchdog
	watchdog = &GetWatchdog();
	Watchdog->SetExpiration(0.5);
	watchdog->SetEnabled(false);

// Drivetrain
	drivetrain = new OctocanumDrive();
	compressor = new Compressor(1, 8);

// Shooter
	flipPot = new Encoder(10, 11);
	armPneus = new DoubleSolenoid(5, 6);
	flipperMotor = new Talon(6);
	shooterSwitch = new DigitalInput(8);
	shooterReleaser = new Solenoid(7);
	winchMotor = new Talon(5); // relay
	winchEncoder = new Encoder(2, 3);
	rollerMotor = new Talon(7);
	arms = new ArmControl(rollerMotor, flipperMotor, armPneus, flipPot);
	shooter = new Shooter(winchMotor, shooterSwitch, shooterReleaser);

// Driver interfaces
	gamePad = new Joystick(1);
	shootPad = new Joystick(2);
	input = new Input(gamePad,
		shootPad,
		drivetrain,
		arms,
		shooter
	);

	this->SetPeriod(0.0);
}

void Robot::DisabledInit()
{
	compressor->Stop();
}

void Robot::DisabledPeriodic()
{
}


void Robot::AutonomousInit()
{
	autonDone = false;
	watchdog->SetEnabled(false);
	drivetrain->Enable();
	compressor->Start();
}

void Robot::AutonomousPeriodic()
{

}


void Robot::TeleopInit()
{
	watchdog->SetEnabled(true);
	
	drivetrain->Enable();
	compressor->Start();
}

void Robot::TeleopPeriodic() 
{
	watchdog->Feed();
	input->Update();

}


void Robot::TestInit()
{
	SmartDashboard::PutString("C++ Version", "__cplusplus");
	SmartDashboard::PutString("Compile date", "__DATE__");
	SmartDashboard::PutString("Compile time", "__TIME__");
}

void Robot::TestPeriodic()
{
}

};

START_ROBOT_CLASS(Robot);

