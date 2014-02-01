/*----------------------------------------------------------------------------*/
    2 /* Copyright (c) FIRST 2008. All Rights Reserved.                                                         */
    3 /* Open Source Software - may be modified and shared by FRC teams. The code   */
    4 /* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
    5 /*----------------------------------------------------------------------------*/
    6 
    7 #ifndef ROBOTDRIVE_H_
    8 #define ROBOTDRIVE_H_
    9 
   10 #include "ErrorBase.h"
   11 #include <stdlib.h>
   12 #include <vxWorks.h>
   13 #include "MotorSafety.h"
   14 #include "MotorSafetyHelper.h"
   15 
   16 class SpeedController;
   17 class GenericHID;
   18 
   27 class RobotDrive: public MotorSafety, public ErrorBase
   28 {
   29 public:
   30         typedef enum
   31         {
   32                 kFrontLeftMotor = 0,
   33                 kFrontRightMotor = 1,
   34                 kRearLeftMotor = 2,
   35                 kRearRightMotor = 3
   36         } MotorType;
   37 
   38         RobotDrive(uint32_t leftMotorChannel, uint32_t rightMotorChannel);
   39         RobotDrive(uint32_t frontLeftMotorChannel, uint32_t rearLeftMotorChannel,
   40                                 uint32_t frontRightMotorChannel, uint32_t rearRightMotorChannel);
   41         RobotDrive(SpeedController *leftMotor, SpeedController *rightMotor);
   42         RobotDrive(SpeedController &leftMotor, SpeedController &rightMotor);
   43         RobotDrive(SpeedController *frontLeftMotor, SpeedController *rearLeftMotor,
   44                                 SpeedController *frontRightMotor, SpeedController *rearRightMotor);
   45         RobotDrive(SpeedController &frontLeftMotor, SpeedController &rearLeftMotor,
   46                                 SpeedController &frontRightMotor, SpeedController &rearRightMotor);
   47         virtual ~RobotDrive();
   48 
   49         void Drive(float outputMagnitude, float curve);
   50         void TankDrive(GenericHID *leftStick, GenericHID *rightStick, bool squaredInputs = true);
   51         void TankDrive(GenericHID &leftStick, GenericHID &rightStick, bool squaredInputs = true);
   52         void TankDrive(GenericHID *leftStick, uint32_t leftAxis, GenericHID *rightStick, uint32_t rightAxis, bool squaredInputs = true);
   53         void TankDrive(GenericHID &leftStick, uint32_t leftAxis, GenericHID &rightStick, uint32_t rightAxis, bool squaredInputs = true);
   54         void TankDrive(float leftValue, float rightValue, bool squaredInputs = true);
   55         void ArcadeDrive(GenericHID *stick, bool squaredInputs = true);
   56         void ArcadeDrive(GenericHID &stick, bool squaredInputs = true);
   57         void ArcadeDrive(GenericHID *moveStick, uint32_t moveChannel, GenericHID *rotateStick, uint32_t rotateChannel, bool squaredInputs = true);
   58         void ArcadeDrive(GenericHID &moveStick, uint32_t moveChannel, GenericHID &rotateStick, uint32_t rotateChannel, bool squaredInputs = true);
   59         void ArcadeDrive(float moveValue, float rotateValue, bool squaredInputs = true);
   60         void MecanumDrive_Cartesian(float x, float y, float rotation, float gyroAngle = 0.0);
   61         void MecanumDrive_Polar(float magnitude, float direction, float rotation);
   62         void HolonomicDrive(float magnitude, float direction, float rotation);
   63         virtual void SetLeftRightMotorOutputs(float leftOutput, float rightOutput);
   64         void SetInvertedMotor(MotorType motor, bool isInverted);
   65         void SetSensitivity(float sensitivity);
   66         void SetMaxOutput(double maxOutput);
   67 
   68         void SetExpiration(float timeout);
   69         float GetExpiration();
   70         bool IsAlive();
   71         void StopMotor();
   72         bool IsSafetyEnabled();
   73         void SetSafetyEnabled(bool enabled);
   74         void GetDescription(char *desc);
   75 
   76 protected:
   77         void InitRobotDrive();
   78         float Limit(float num);
   79         void Normalize(double *wheelSpeeds);
   80         void RotateVector(double &x, double &y, double angle);
   81 
   82         static const int32_t kMaxNumberOfMotors = 4;
   83 
   84         int32_t m_invertedMotors[kMaxNumberOfMotors];
   85         float m_sensitivity;
   86         double m_maxOutput;
   87         bool m_deleteSpeedControllers;
   88         SpeedController *m_frontLeftMotor;
   89         SpeedController *m_frontRightMotor;
   90         SpeedController *m_rearLeftMotor;
   91         SpeedController *m_rearRightMotor;
   92         MotorSafetyHelper *m_safetyHelper;
   93         
   94 private:
   95         int32_t GetNumMotors()
   96         {
   97                 int motors = 0;
   98                 if (m_frontLeftMotor) motors++;
   99                 if (m_frontRightMotor) motors++;
  100                 if (m_rearLeftMotor) motors++;
  101                 if (m_rearRightMotor) motors++;
  102                 return motors;
  103         }
  104         DISALLOW_COPY_AND_ASSIGN(RobotDrive);
  105 };
  106 
  107 #endif
