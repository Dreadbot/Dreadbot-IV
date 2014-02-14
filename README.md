Dreadbot-Test
=============


To do:
Drivetrain:
* For arcade drive, assign the forward/backward and rotation axes to separate joysticks.  (Having both on one joystick is apparently really annoying)
* Enable both mechanum (strafe) and arcade drive control via the D-pad.
* Fix the issue where the the robot locks the motor controller inputs at apparently random times and keeps them locked at that value until the robot is power-cycled.
  * Could be that the input class breaks when there's a blip in communication with the driver station (this happens a lot)
* The behavior of the dropper is iffy on the first drop. (Record what happens so we can fix it)
* There are encoders on the axles now, so we should be able to add some traction-control code to help drive smoother.
* Max speed should be configurable by the driver on the gamepad.
* Make it dance (i.e. add the other valves and have a function to change them.)
