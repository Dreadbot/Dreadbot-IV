/* Swerve drive-enabled robot structure
 * (not really tested or anything)
*/


// Positive Y-axis points towards the front
// Positive X-axis points towards the right

#include "DB2014_t.h"


// Robot class
class Robot : SimpleRobot {
public:

	Robot() {}


	// Robot-wide initialization code; called whenever the robot starts up (i.e. enabled)
	void RobotInit() {
		println("Initialization routine started");

		watchdog = GetWatchdog();
		watchdog->SetEnabled(false);
		// Watchdog expiration value should be inversely proportional to the potential head-crushing and/or human eating capabilities of the robot.
		watchdog->SetExpiration(); // Default timeout is .5s. Change argument according to above statement
		println("Watchdog enabled");

		driver = DriverStation::GetInstance();
		lcd = DriverStationLCD::GetInstance();
		driverJoystick = new Joystick(1);
		println("Driver station referenced and configured (kind of)");

		compressor = new Compressor(1, 1);
		compressor->Start();
		println("Compressor started");

		// Enable the drive modules
		Drive_FR->Enable();
		Drive_FL->Enable();
		Drive_RR->Enable();
		Drive_RL->Enable();

		// Initialize the drivetrain
		drivetrain = new RobotDrive(Drive_FL->getDrivePin(),
		                            Drive_RL->getDrivePin(),
		                            Drive_FR->getDrivePin(),
		                            Drive_RR->getDrivePin()
		);
		drivetrain->Limit(1.0f);
		drivetrain->InitRobotDrive();

		println("Drive modules enabled");

		// Find camera
		camera = AxisCamera::GetInstance("192.168.0.90");
		println("Camera enabled");
	}


	// Runs when the autonomous period starts
	void Autonomous() {
		watchdog->SetEnabled(true); // Mortalize fido
		driver->InAutonomous();
	}

	// Runs when autonomous ends and tele-op starts
	void OperatorControl() {
		watchdog->SetEnabled(true);
		driver->InOperatorControl();

		while (IsOperatorControl() && IsEnabled()) {
			TeleOpPeriodic();
			Wait(LRATE);
		}
	}


	// Runs when the field is disabled
	void Disabled() {

		driver->InDisabled();
		compressor->Stop();

		Drive_FR->Disable();
		Drive_FL->Disable();
		Drive_RR->Disable();
		Drive_RL->Disable();

		watchdog->Disable();
	}


	// Test code: Runs once when the robot is put into test mode.
	void Test() {
		driver->InTest(true);


		// Enable the watchdog if TEST_WATCHDOG is defined
		#ifdef TEST_WATCHDOG
			watchdog->SetEnabled(true);
		#endif



		// Simulate a full match
		#ifdef TEST_MATCH
			double elapsed = 0;
			Autonomous();
			elapsed = 0;

			while (elapsed <= TELEOP_PERIOD) {
				TeleopPeriodic();
				elapsed += LRATE;
			}

			return;



		// Simulate Autonomous period
		#elif TEST_AUTON
			Autonomous();
			return;



		// Simulate TeleOp period
		#elif TEST_TELEOP
			double elapsed = 0;
			Autonomous();
			elapsed = 0;

			while (elapsed <= TELEOP_PERIOD) {
				TeleOpPeriodic();
				Wait(LRATE);
				elapsed += LRATE;
			}

			return;



		// Free drive mode (i.e. without time constraints)
		#elif TEST_FREEDRIVE
			while (IsEnabled()) {
				UpdateControlData();
				TeleOpPeriodic();
				Wait(LRATE);
			}
		#endif


		driver->InTest(false);
	}


private:


	RobotDrive* drivetrain;
	AxisCamera* camera;
	Watchdog* watchdog;
	DriverStation* driver;
	Compressor* compressor;
	DriverStationLCD* lcd;

	Joystick* driverJoystick;

	// Initialize drive modules
	SwerveDrive* Drive_FR(1, 2, 1.0, 1.0);
	SwerveDrive* Drive_FL(3, 4, -1.0, 1.0);
	SwerveDrive* Drive_RR(5, 6, 1.0, -1.0);
	SwerveDrive* Drive_RL(7, 8, -1.0, -1.0);


	// Control data from the driver station
	struct InputData {
		bool autoShoot = false;
		bool ORshoot = false;
		float twist = 0;
		float xAxis = 0;
		float yAxis = 0;
		float zAxis = 0;
	} driverInput;

	// Data that should be physically represented
	struct OutputData {
		bool onTarget = false;
		float shooterYaw = 0;
		float shooterPitch = 45;
	} driverOutput;




	// TeleOpPeriodic is called once every (LRATE) second(s) in teleop mode
	void TeleOpPeriodic() {
		drivetrain->Drive((float) sqrt(
		                  (driverInput.xAxis*driverInput.xAxis) +
		                  (driverInput.yAxis*driverInput.yAxis) +
		                  (driverInput.zAxis*driverInput.zAxis)), 0.0f
		);
		drivetrain->Normalize();
	}


	// Attempt to get new control data from the driver station
	void UpdateControlData() {
		if (driver->IsNewControlData()) {
			driverInput.ORshoot = driverJoystick->getButton(1);
 			driverInput.autoShoot = driverJoystick->getTrigger();
 			driverInput.twist = driverJoystick->getTwist();
 			driverInput.xAxis = driverJoystick->getX();
 			driverInput.yAxis = driverJoystick->getY();
 			driverInput.zAxis = driverJoystick->getZ();
		}/*
		aimed
		while (driverInput.autoShoot) {
			Aim
			if ()
		}*/
	}

	// Print a line of text to the driver station LCD
	void PrintfLn(const char* m) {
		lcd->PrintfLine();
		UpdateLCD();
	}

	// Print text to the driver station LCD
	void Printf(const char* m) {
		lcd->Printf();
		UpdateLCD();
	}
};

// End robot class //////////////////





START_ROBOT_CLASS(Robot);

