/*----------------------------------------------------------------------------*/
    2 /* Copyright (c) FIRST 2008. All Rights Reserved.                                                         */
    3 /* Open Source Software - may be modified and shared by FRC teams. The code   */
    4 /* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
    5 /*----------------------------------------------------------------------------*/
    6 
    7 #include "RobotDrive.h"
    8 
    9 #include "CANJaguar.h"
   10 #include "GenericHID.h"
   11 #include "Joystick.h"
   12 #include "Jaguar.h"
   13 #include "NetworkCommunication/UsageReporting.h"
   14 #include "Utility.h"
   15 #include "WPIErrors.h"
   16 #include <math.h>
   17 
   18 #define max(x, y) (((x) > (y)) ? (x) : (y))
   19 
   20 const int32_t RobotDrive::kMaxNumberOfMotors;
   21 
   22 /*
   23  * Driving functions
   24  * These functions provide an interface to multiple motors that is used for C programming
   25  * The Drive(speed, direction) function is the main part of the set that makes it easy
   26  * to set speeds and direction independently in one call.
   27  */
   28 
   34 void RobotDrive::InitRobotDrive() {
   35         m_frontLeftMotor = NULL;
   36         m_frontRightMotor = NULL;
   37         m_rearRightMotor = NULL;
   38         m_rearLeftMotor = NULL;
   39         m_sensitivity = 0.5;
   40         m_maxOutput = 1.0;
   41         m_safetyHelper = new MotorSafetyHelper(this);
   42         m_safetyHelper->SetSafetyEnabled(true);
   43 }
   64 
   75 RobotDrive::RobotDrive(uint32_t frontLeftMotor, uint32_t rearLeftMotor,
   76                 uint32_t frontRightMotor, uint32_t rearRightMotor)
   77 {
   78         InitRobotDrive();
   79         m_rearLeftMotor = new Jaguar(rearLeftMotor);
   80         m_rearRightMotor = new Jaguar(rearRightMotor);
   81         m_frontLeftMotor = new Jaguar(frontLeftMotor);
   82         m_frontRightMotor = new Jaguar(frontRightMotor);
   83         for (int32_t i=0; i < kMaxNumberOfMotors; i++)
   84         {
   85                 m_invertedMotors[i] = 1;
   86         }
   87         SetLeftRightMotorOutputs(0.0, 0.0);
   88         m_deleteSpeedControllers = true;
   89 }
  137 RobotDrive::RobotDrive(SpeedController *frontLeftMotor, SpeedController *rearLeftMotor,
  138                                                 SpeedController *frontRightMotor, SpeedController *rearRightMotor)
  139 {
  140         InitRobotDrive();
  141         if (frontLeftMotor == NULL || rearLeftMotor == NULL || frontRightMotor == NULL || rearRightMotor == NULL)
  142         {
  143                 wpi_setWPIError(NullParameter);
  144                 return;
  145         }
  146         m_frontLeftMotor = frontLeftMotor;
  147         m_rearLeftMotor = rearLeftMotor;
  148         m_frontRightMotor = frontRightMotor;
  149         m_rearRightMotor = rearRightMotor;
  150         for (int32_t i=0; i < kMaxNumberOfMotors; i++)
  151         {
  152                 m_invertedMotors[i] = 1;
  153         }
  154         m_deleteSpeedControllers = false;
  155 }
  156 
  157 RobotDrive::RobotDrive(SpeedController &frontLeftMotor, SpeedController &rearLeftMotor,
  158                                                 SpeedController &frontRightMotor, SpeedController &rearRightMotor)
  159 {
  160         InitRobotDrive();
  161         m_frontLeftMotor = &frontLeftMotor;
  162         m_rearLeftMotor = &rearLeftMotor;
  163         m_frontRightMotor = &frontRightMotor;
  164         m_rearRightMotor = &rearRightMotor;
  165         for (int32_t i=0; i < kMaxNumberOfMotors; i++)
  166         {
  167                 m_invertedMotors[i] = 1;
  168         }
  169         m_deleteSpeedControllers = false;
  170 }
  171 
  176 RobotDrive::~RobotDrive()
  177 {
  178         if (m_deleteSpeedControllers)
  179         {
  180                 delete m_frontLeftMotor;
  181                 delete m_rearLeftMotor;
  182                 delete m_frontRightMotor;
  183                 delete m_rearRightMotor;
  184         }
  185         delete m_safetyHelper;
  186 }
  187 
  200 void RobotDrive::Drive(float outputMagnitude, float curve)
  201 {
  202         float leftOutput, rightOutput;
  203         static bool reported = false;
  204         if (!reported)
  205         {
  206                 nUsageReporting::report(nUsageReporting::kResourceType_RobotDrive, GetNumMotors(), nUsageReporting::kRobotDrive_ArcadeRatioCurve);
  207                 reported = true;
  208         }
  209 
  210         if (curve < 0)
  211         {
  212                 float value = log(-curve);
  213                 float ratio = (value - m_sensitivity)/(value + m_sensitivity);
  214                 if (ratio == 0) ratio =.0000000001;
  215                 leftOutput = outputMagnitude / ratio;
  216                 rightOutput = outputMagnitude;
  217         }
  218         else if (curve > 0)
  219         {
  220                 float value = log(curve);
  221                 float ratio = (value - m_sensitivity)/(value + m_sensitivity);
  222                 if (ratio == 0) ratio =.0000000001;
  223                 leftOutput = outputMagnitude;
  224                 rightOutput = outputMagnitude / ratio;
  225         }
  226         else
  227         {
  228                 leftOutput = outputMagnitude;
  229                 rightOutput = outputMagnitude;
  230         }
  231         SetLeftRightMotorOutputs(leftOutput, rightOutput);
  232 }
  233 
  241 void RobotDrive::TankDrive(GenericHID *leftStick, GenericHID *rightStick, bool squaredInputs)
  242 {
  243         if (leftStick == NULL || rightStick == NULL)
  244         {
  245                 wpi_setWPIError(NullParameter);
  246                 return;
  247         }
  248         TankDrive(leftStick->GetY(), rightStick->GetY(), squaredInputs);
  249 }
  250 
  251 void RobotDrive::TankDrive(GenericHID &leftStick, GenericHID &rightStick, bool squaredInputs)
  252 {
  253         TankDrive(leftStick.GetY(), rightStick.GetY(), squaredInputs);
  254 }
  255 
  265 void RobotDrive::TankDrive(GenericHID *leftStick, uint32_t leftAxis,
  266                 GenericHID *rightStick, uint32_t rightAxis, bool squaredInputs)
  267 {
  268         if (leftStick == NULL || rightStick == NULL)
  269         {
  270                 wpi_setWPIError(NullParameter);
  271                 return;
  272         }
  273         TankDrive(leftStick->GetRawAxis(leftAxis), rightStick->GetRawAxis(rightAxis), squaredInputs);
  274 }
  275 
  276 void RobotDrive::TankDrive(GenericHID &leftStick, uint32_t leftAxis,
  277                 GenericHID &rightStick, uint32_t rightAxis, bool squaredInputs)
  278 {
  279         TankDrive(leftStick.GetRawAxis(leftAxis), rightStick.GetRawAxis(rightAxis), squaredInputs);
  280 }
  281 
  282 
  289 void RobotDrive::TankDrive(float leftValue, float rightValue, bool squaredInputs)
  290 {
  291         static bool reported = false;
  292         if (!reported)
  293         {
  294                 nUsageReporting::report(nUsageReporting::kResourceType_RobotDrive, GetNumMotors(), nUsageReporting::kRobotDrive_Tank);
  295                 reported = true;
  296         }
  297 
  298         // square the inputs (while preserving the sign) to increase fine control while permitting full power
  299         leftValue = Limit(leftValue);
  300         rightValue = Limit(rightValue);
  301         if(squaredInputs)
  302         {
  303                 if (leftValue >= 0.0)
  304                 {
  305                         leftValue = (leftValue * leftValue);
  306                 }
  307                 else
  308                 {
  309                         leftValue = -(leftValue * leftValue);
  310                 }
  311                 if (rightValue >= 0.0)
  312                 {
  313                         rightValue = (rightValue * rightValue);
  314                 }
  315                 else
  316                 {
  317                         rightValue = -(rightValue * rightValue);
  318                 }
  319         }
  320 
  321         SetLeftRightMotorOutputs(leftValue, rightValue);
  322 }
  323 
  333 void RobotDrive::ArcadeDrive(GenericHID *stick, bool squaredInputs)
  334 {
  335         // simply call the full-featured ArcadeDrive with the appropriate values
  336         ArcadeDrive(stick->GetY(), stick->GetX(), squaredInputs);
  337 }
  338 
  348 void RobotDrive::ArcadeDrive(GenericHID &stick, bool squaredInputs)
  349 {
  350         // simply call the full-featured ArcadeDrive with the appropriate values
  351         ArcadeDrive(stick.GetY(), stick.GetX(), squaredInputs);
  352 }
  353 
  364 void RobotDrive::ArcadeDrive(GenericHID* moveStick, uint32_t moveAxis,
  365                                                                 GenericHID* rotateStick, uint32_t rotateAxis,
  366                                                                 bool squaredInputs)
  367 {
  368         float moveValue = moveStick->GetRawAxis(moveAxis);
  369         float rotateValue = rotateStick->GetRawAxis(rotateAxis);
  370 
  371         ArcadeDrive(moveValue, rotateValue, squaredInputs);
  372 }
  373 
  385 void RobotDrive::ArcadeDrive(GenericHID &moveStick, uint32_t moveAxis,
  386                                                                 GenericHID &rotateStick, uint32_t rotateAxis,
  387                                                                 bool squaredInputs)
  388 {
  389         float moveValue = moveStick.GetRawAxis(moveAxis);
  390         float rotateValue = rotateStick.GetRawAxis(rotateAxis);
  391 
  392         ArcadeDrive(moveValue, rotateValue, squaredInputs);
  393 }
  394 
  402 void RobotDrive::ArcadeDrive(float moveValue, float rotateValue, bool squaredInputs)
  403 {
  404         static bool reported = false;
  405         if (!reported)
  406         {
  407                 nUsageReporting::report(nUsageReporting::kResourceType_RobotDrive, GetNumMotors(), nUsageReporting::kRobotDrive_ArcadeStandard);
  408                 reported = true;
  409         }
  410 
  411         // local variables to hold the computed PWM values for the motors
  412         float leftMotorOutput;
  413         float rightMotorOutput;
  414 
  415         moveValue = Limit(moveValue);
  416         rotateValue = Limit(rotateValue);
  417 
  418         if (squaredInputs)
  419         {
  420                 // square the inputs (while preserving the sign) to increase fine control while permitting full power
  421                 if (moveValue >= 0.0)
  422                 {
  423                         moveValue = (moveValue * moveValue);
  424                 }
  425                 else
  426                 {
  427                         moveValue = -(moveValue * moveValue);
  428                 }
  429                 if (rotateValue >= 0.0)
  430                 {
  431                         rotateValue = (rotateValue * rotateValue);
  432                 }
  433                 else
  434                 {
  435                         rotateValue = -(rotateValue * rotateValue);
  436                 }
  437         }
  438 
  439         if (moveValue > 0.0)
  440         {
  441                 if (rotateValue > 0.0)
  442                 {
  443                         leftMotorOutput = moveValue - rotateValue;
  444                         rightMotorOutput = max(moveValue, rotateValue);
  445                 }
  446                 else
  447                 {
  448                         leftMotorOutput = max(moveValue, -rotateValue);
  449                         rightMotorOutput = moveValue + rotateValue;
  450                 }
  451         }
  452         else
  453         {
  454                 if (rotateValue > 0.0)
  455                 {
  456                         leftMotorOutput = - max(-moveValue, rotateValue);
  457                         rightMotorOutput = moveValue + rotateValue;
  458                 }
  459                 else
  460                 {
  461                         leftMotorOutput = moveValue - rotateValue;
  462                         rightMotorOutput = - max(-moveValue, -rotateValue);
  463                 }
  464         }
  465         SetLeftRightMotorOutputs(leftMotorOutput, rightMotorOutput);
  466 }
  467 
  484 void RobotDrive::MecanumDrive_Cartesian(float x, float y, float rotation, float gyroAngle)
  485 {
  486         static bool reported = false;
  487         if (!reported)
  488         {
  489                 nUsageReporting::report(nUsageReporting::kResourceType_RobotDrive, GetNumMotors(), nUsageReporting::kRobotDrive_MecanumCartesian);
  490                 reported = true;
  491         }
  492 
  493         double xIn = x;
  494         double yIn = y;
  495         // Negate y for the joystick.
  496         yIn = -yIn;
  497         // Compenstate for gyro angle.
  498         RotateVector(xIn, yIn, gyroAngle);
  499 
  500         double wheelSpeeds[kMaxNumberOfMotors];
  501         wheelSpeeds[kFrontLeftMotor] = xIn + yIn + rotation;
  502         wheelSpeeds[kFrontRightMotor] = -xIn + yIn - rotation;
  503         wheelSpeeds[kRearLeftMotor] = -xIn + yIn + rotation;
  504         wheelSpeeds[kRearRightMotor] = xIn + yIn - rotation;
  505 
  506         Normalize(wheelSpeeds);
  507 
  508         uint8_t syncGroup = 0x80;
  509 
  510         m_frontLeftMotor->Set(wheelSpeeds[kFrontLeftMotor] * m_invertedMotors[kFrontLeftMotor] * m_maxOutput, syncGroup);
  511         m_frontRightMotor->Set(wheelSpeeds[kFrontRightMotor] * m_invertedMotors[kFrontRightMotor] * m_maxOutput, syncGroup);
  512         m_rearLeftMotor->Set(wheelSpeeds[kRearLeftMotor] * m_invertedMotors[kRearLeftMotor] * m_maxOutput, syncGroup);
  513         m_rearRightMotor->Set(wheelSpeeds[kRearRightMotor] * m_invertedMotors[kRearRightMotor] * m_maxOutput, syncGroup);
  514 
  515         CANJaguar::UpdateSyncGroup(syncGroup);
  516         
  517         m_safetyHelper->Feed();
  518 }
  568 
  592 void RobotDrive::SetLeftRightMotorOutputs(float leftOutput, float rightOutput)
  593 {
  594         wpi_assert(m_rearLeftMotor != NULL && m_rearRightMotor != NULL);
  595 
  596         uint8_t syncGroup = 0x80;
  597 
  598         if (m_frontLeftMotor != NULL)
  599                 m_frontLeftMotor->Set(Limit(leftOutput) * m_invertedMotors[kFrontLeftMotor] * m_maxOutput, syncGroup);
  600         m_rearLeftMotor->Set(Limit(leftOutput) * m_invertedMotors[kRearLeftMotor] * m_maxOutput, syncGroup);
  601 
  602         if (m_frontRightMotor != NULL)
  603                 m_frontRightMotor->Set(-Limit(rightOutput) * m_invertedMotors[kFrontRightMotor] * m_maxOutput, syncGroup);
  604         m_rearRightMotor->Set(-Limit(rightOutput) * m_invertedMotors[kRearRightMotor] * m_maxOutput, syncGroup);
  605 
  606         CANJaguar::UpdateSyncGroup(syncGroup);
  607 
  608         m_safetyHelper->Feed();
  609 }
  610 
  614 float RobotDrive::Limit(float num)
  615 {
  616         if (num > 1.0)
  617         {
  618                 return 1.0;
  619         }
  620         if (num < -1.0)
  621         {
  622                 return -1.0;
  623         }
  624         return num;
  625 }
  626 
  630 void RobotDrive::Normalize(double *wheelSpeeds)
  631 {
  632         double maxMagnitude = fabs(wheelSpeeds[0]);
  633         int32_t i;
  634         for (i=1; i<kMaxNumberOfMotors; i++)
  635         {
  636                 double temp = fabs(wheelSpeeds[i]);
  637                 if (maxMagnitude < temp) maxMagnitude = temp;
  638         }
  639         if (maxMagnitude > 1.0)
  640         {
  641                 for (i=0; i<kMaxNumberOfMotors; i++)
  642                 {
  643                         wheelSpeeds[i] = wheelSpeeds[i] / maxMagnitude;
  644                 }
  645         }
  646 }
  647 
  651 void RobotDrive::RotateVector(double &x, double &y, double angle)
  652 {
  653         double cosA = cos(angle * (3.14159 / 180.0));
  654         double sinA = sin(angle * (3.14159 / 180.0));
  655         double xOut = x * cosA - y * sinA;
  656         double yOut = x * sinA + y * cosA;
  657         x = xOut;
  658         y = yOut;
  659 }
  660 
  661 /*
  662  * Invert a motor direction.
  663  * This is used when a motor should run in the opposite direction as the drive
  664  * code would normally run it. Motors that are direct drive would be inverted, the
  665  * Drive code assumes that the motors are geared with one reversal.
  666  * @param motor The motor index to invert.
  667  * @param isInverted True if the motor should be inverted when operated.
  668  */
  669 void RobotDrive::SetInvertedMotor(MotorType motor, bool isInverted)
  670 {
  671         if (motor < 0 || motor > 3)
  672         {
  673                 wpi_setWPIError(InvalidMotorIndex);
  674                 return;
  675         }
  676         m_invertedMotors[motor] = isInverted ? -1 : 1;
  677 }
  678 
  685 void RobotDrive::SetSensitivity(float sensitivity)
  686 {
  687         m_sensitivity = sensitivity;
  688 }
  689 
  694 void RobotDrive::SetMaxOutput(double maxOutput)
  695 {
  696         m_maxOutput = maxOutput;
  697 }
  698 
  699 
  700 
  701 void RobotDrive::SetExpiration(float timeout)
  702 {
  703         m_safetyHelper->SetExpiration(timeout);
  704 }
  705 
  706 float RobotDrive::GetExpiration()
  707 {
  708         return m_safetyHelper->GetExpiration();
  709 }
  710 
  711 bool RobotDrive::IsAlive()
  712 {
  713         return m_safetyHelper->IsAlive();
  714 }
  715 
  716 bool RobotDrive::IsSafetyEnabled()
  717 {
  718         return m_safetyHelper->IsSafetyEnabled();
  719 }
  720 
  721 void RobotDrive::SetSafetyEnabled(bool enabled)
  722 {
  723         m_safetyHelper->SetSafetyEnabled(enabled);
  724 }
  725 
  726 void RobotDrive::GetDescription(char *desc)
  727 {
  728         sprintf(desc, "RobotDrive");
  729 }
  730 
  731 void RobotDrive::StopMotor()
  732 {
  733         if (m_frontLeftMotor != NULL) m_frontLeftMotor->Disable();
  734         if (m_frontRightMotor != NULL) m_frontRightMotor->Disable();
  735         if (m_rearLeftMotor != NULL) m_rearLeftMotor->Disable();
  736         if (m_rearRightMotor != NULL) m_rearRightMotor->Disable();
  737 }
