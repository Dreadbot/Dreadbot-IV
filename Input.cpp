#include "Input.h"

Input::Input(Joystick* newStick, 
	Joystick* newP2Stick,
	OctocanumDrive* newDrive,
	armControl* newArms,
	Shooter* newShooter)
{
	stick = newStick;
	p2Stick = newP2Stick;
	drive = newDrive;
	arms = newArms;
	shooter = newShooter;
	dance = false;
}
void Input::Update()
{
	float x = stick->GetRawAxis(MEC_X);
	float y = stick->GetRawAxis(MEC_Y);
	float r = stick->GetRawAxis(MEC_R);

	bool drop = stick->GetRawButton(DROP);
	bool dance = stick->GetRawButton(DANCE_ENABLE);

	SmartDashboard::PutBoolean("Traction Mode: ", drop); 
	SmartDashboard::PutNumber("Flipper Value: ", arms->getFlipPot());

	if (x < 0.1 && x > -0.1) x = 0.0;
	if (y < 0.1 && y > -0.1) y = 0.0;
	if (r < 0.1 && r > -0.1) r = 0.0;
	
	drive->Drive(x, y, r);

	if (dance)
	{
		drive->valve0->Set(stick->GetRawButton(DANCE_RIGHT));
		drive->valve1->Set(stick->GetRawButton(DANCE_LEFT));
	}
	else
	{
		if (!drop) drive->Drop();
		else drive->Raise();
	}
	shooter->update();
	if (stick->GetRawButton(TRIGGER)) shooter->shoot();

	//Player 2 Controls
	float flipAxis = p2Stick->GetRawAxis(FLIPPER);
	float armAxis = p2Stick->GetRawAxis(ARMS);
	
	//Deadzone
	if (flipAxis <= 0.1 && flipAxis >= -0.1) flipAxis = 0;
	if (armAxis <= 0.1 && flipAxis >= -0.1) armAxis = 0;

	//Set controls
	arms->moveFlipper(flipAxis);
	if (armAxis > 0.5) arms->moveArms(DoubleSolenoid::kForward);
	if (armAxis < -0.5) arms->moveArms(DoubleSolenoid::kReverse);
	if (armAxis < -0.5 && armAxis > 0.5) arms->moveArms(DoubleSolenoid::kOff);
	if (p2Stick->GetRawButton(SHOOTER_RESET)) shooter->setReset();
	if (p2Stick->GetRawButton(ARM_MECS_IN)) arms->moveWheels(1);
	else if (p2Stick->GetRawAxis(ARM_MECS_OUT)) arms->moveWheels(-1);
	else arms->moveWheels(0);

}
