// Positive Y-axis points towards the front
// Positive X-axis points towards the right

#include "DB2014_t.h"


// Robot class
class Robot : SimpleRobot {
public:
	Robot() {}
	void RobotInit() {
		watchdog = GetWatchdog();
		watchdog->SetEnabled(false);
		watchdog->SetExpiration();
		driver = DriverStation::GetInstance();
		lcd = DriverStationLCD::GetInstance();
		driverJoystick = new Joystick(1);
		compressor = new Compressor(1, 1);
		compressor->Start();
		drivetrain = new RobotDrive(
			Drive_FL->getDrivePin(),
		        Drive_RL->getDrivePin(),
		        Drive_FR->getDrivePin(),
		        Drive_RR->getDrivePin()
		);
		drivetrain->Limit(1.0f);
		drivetrain->InitRobotDrive();
		camera = AxisCamera::GetInstance("192.168.0.90");
	}
	void Autonomous() {
		watchdog->SetEnabled(true);
		driver->InAutonomous();
	}
	void OperatorControl() {
		watchdog->SetEnabled(true);
		driver->InOperatorControl();

		while (IsOperatorControl() && IsEnabled()) {
			TeleOpPeriodic();
			Wait(LRATE);
		}
	}
	void Disabled() {

		driver->InDisabled();
		compressor->Stop();

		Drive_FR->Disable();
		Drive_FL->Disable();
		Drive_RR->Disable();
		Drive_RL->Disable();

		watchdog->Disable();
	}
	void Test() {
		driver->InTest(true);
		#ifdef TEST_WATCHDOG
			watchdog->SetEnabled(true);
		#endif
		#ifdef TEST_MATCH
			double elapsed = 0;
			Autonomous();
			elapsed = 0;
			while (elapsed <= TELEOP_PERIOD) {
				TeleopPeriodic();
				elapsed += LRATE;
			}
			return;
		#elif TEST_AUTON
			Autonomous();
			return;
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

	struct InputData {
		bool ORshoot = false;
		byte wheelGear = 0;
		bool wheelMode = 0;
		float twist = 0;
		float xAxis = 0;
		float yAxis = 0;
		float zAxis = 0;
	} driverInput;
	
	struct OutputData {
		bool onTarget = false;
		float shooterYaw = 0;
		float shooterPitch = 45;
	} driverOutput;
	
	void TeleOpPeriodic() {
		drivetrain->Drive((float) sqrt(
		                  (driverInput.xAxis*driverInput.xAxis) +
		                  (driverInput.yAxis*driverInput.yAxis) +
		                  (driverInput.zAxis*driverInput.zAxis)), 0.0f
		);
		drivetrain->Normalize();
	}
	void UpdateControlData() {
		if (driver->IsNewControlData()) {
			driverInput.ORshoot = driverJoystick->getButton(1);
 			driverInput.autoShoot = driverJoystick->getTrigger();
 			driverInput.twist = driverJoystick->getTwist();
 			driverInput.xAxis = driverJoystick->getX();
 			driverInput.yAxis = driverJoystick->getY();
 			driverInput.zAxis = driverJoystick->getZ();
		}
	}
	void PrintfLn(const char* m) {
		lcd->PrintfLine();
		UpdateLCD();
	}

	void Printf(const char* m) {
		lcd->Printf();
		UpdateLCD();
	}
}; // End robot

START_ROBOT_CLASS(Robot);

