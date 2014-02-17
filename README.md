Dreadbot-Test
=============


To do (In order of greatest to least importance):

* max speed should be configurable by the driver on the operator console.
	*What does this even mean?
* drive->Auto(float xdist, float ydist, float rot, bool drivemode); translate the position and rotation of the robot a specified number of inches and degrees
	*Unecessary, since the robot shoots, then goes forwards
* make sure each wheel is going at the speed it's set to be at with a PID controller and encoders.