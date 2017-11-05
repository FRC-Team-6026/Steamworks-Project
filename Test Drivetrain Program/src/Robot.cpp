#include "WPILib.h"
#include "CANTalon.h"
#include "ADIS16448_IMU.h"

#include <iostream>
#include <vector>

class Robot: public IterativeRobot
{
	DigitalOutput					indicatorLed;
	Joystick 						joy;
	JoystickButton 					buttonA;
	JoystickButton 					buttonB;
	JoystickButton					buttonX;
	JoystickButton					buttonY;
	JoystickButton					buttonLBumper;
	CANTalon 						frontLeft;
	CANTalon 						frontRight;
	CANTalon 						backLeft;
	CANTalon 						backRight;
	CANTalon 						gearHolder;
	//CANTalon						loader;
	CANTalon                        climb;
	RobotDrive 						drive;
	ADIS16448_IMU 					imu;
	std::shared_ptr<NetworkTable> 	table;
	AnalogInput 					ultra;
	SendableChooser<int*>			automode;
	int								automode1;
	int								automode2;
	int								automode3;
	double 							initEncPos;
	double							ultraRange;
	bool							forwardFlag;
	bool							turnLeftFlag;
	bool							turnRightFlag;
	bool							climbToggle;
	bool							climbMode;
	bool							reverse;
	bool							allowModeChange;
	double							initAngleX;
	Timer							timer1;
//	SendableChooser <int*>			autoChooser;
	//SmartDashboard sm;

public:
		Robot() : joy(0), /* gamepad at the first slot */
		indicatorLed(0),
		buttonA(&joy, 1),
		buttonB(&joy, 2),
		buttonX(&joy, 3),
		buttonY(&joy, 4),
		buttonLBumper(&joy, 5),
		frontLeft(1), /* device ID '0', moatch the RIO Web Config Page*/
		frontRight(4),
		backLeft(2),
		backRight(3),
		gearHolder(5),
		//loader(6),
		climb(7),
		drive(frontLeft,backLeft,frontRight,backRight),
		imu(),
		automode(),
		automode1(),
		automode2(),
		automode3(),
		ultra(0),
		initEncPos(),
		ultraRange(),
		forwardFlag(false),
		turnLeftFlag(false),
		turnRightFlag(false),
		climbToggle(false),
		climbMode(false),
		reverse(false),
		allowModeChange(true),
		initAngleX(0.0),
		timer1()
		//sm()
{
			//backLeft.SetControlMode(CANSpeedController::kFollower);
			//backLeft.Set(1.0);
			//backRight.SetControlMode(CANSpeedController::kFollower);
			//backRight.Set(4.0);
			table = NetworkTable::GetTable("GRIP/pegCont");
			//drive.SetExpiration(5.0);
			//frontLeft.SetVoltageRampRate(6.0);
			//frontRight.SetVoltageRampRate(6.0);
			//backLeft.SetVoltageRampRate(6.0);
			//backRight.SetVoltageRampRate(6.0);
			//autoChooser.AddDefault("Left", 0);
			//autoChooser.AddObject("Center", 1);
			//autoChooser.AddObject("Right", 2);

			automode.AddDefault("center", &automode1);
			automode.AddObject("left", &automode2);
			automode.AddObject("right", &automode3);
}


		void RobotInit()
		{
			CameraServer::GetInstance()->StartAutomaticCapture();
			indicatorLed.Set(1);

			/*
			while (true) {
				std::cout <<"Areas: ";
				std::vector<double> arr = table->GetNumberArray("Roll", llvm::ArrayRef<double>());
						for (unsigned int i = 0; i < arr.size(); i++){
							std::cout << arr[i] << " ";
						}
						std::cout << std::endl;
				//		Wait(1);
			}

		*/}

		void RobotPeriodic()
		{
			//SmartDashboard::PutNumber("Forward Control", direction);
		//	SmartDashboard::PutNumber("shooter voltage",gearHolder.GetOutputVoltage());
		//	SmartDashboard::PutNumber("motor1", frontLeft.GetOutputVoltage());
		//	SmartDashboard::PutNumber("motor2", frontRight.GetOutputVoltage());
		//	SmartDashboard::PutNumber("motor3", backLeft.GetOutputVoltage());
		//	SmartDashboard::PutNumber("motor4", backRight.GetOutputVoltage());
		//	SmartDashboard::PutData("imu", &imu);
	//		SmartDashboard::PutNumber("AutoMode", *autoChooser.GetSelected());
		//	std::vector<double> arr = table->GetNumberArray("centerX", llvm::ArrayRef<double>());
		//	if (arr.size() == 2)
		//	{
		//	//std::cout << "Targets aquired: " << arr[0] << ", " << arr[1] << std::endl;
		//	SmartDashboard::PutNumber("target center1", arr[0]);
		//	SmartDashboard::PutNumber("target center2", arr[1]);
		//	}

			//std::cout << (int)table->GetBoolean("motor1") << std::endl;
			//double temp = table->GetNumber("AngleX", -1.0);
		//	SmartDashboard::PutNumber("debug current bl", backLeft.GetOutputCurrent());
		//	SmartDashboard::PutNumber("debug current br", backRight.GetOutputCurrent());

		//	SmartDashboard::PutNumber("angle x", imu.GetAngleX());
		//	SmartDashboard::PutNumber("angle y", imu.GetAngleY());

		//	SmartDashboard::PutNumber("left position", frontLeft.GetEncPosition());
		//	SmartDashboard::PutNumber("right position", frontRight.GetEncPosition());

		//	double temp = ultra.GetVoltage();

			// Units are measured in mm
			ultraRange = ultra.GetVoltage() * (1/.977 * 1000);

		//	SmartDashboard::PutNumber("Ultrasonic Range", ultraRange);


			SmartDashboard::PutData("chooser", &automode);

			//std::cout << imu.GetAngleZ() << std::endl;

			//SmartDashboard::PutNumber("initanglex", initAngleX);

			//SmartDashboard::PutNumber("currentangle", imu.GetAngleX());

			/*if (automode.GetSelected() == &automode1)
			{
				//std::cout << "mode1" <<std::endl;
			}
			else if (automode.GetSelected() == &automode2)
			{
				//std::cout << "mode2" <<std::endl;
			}
			else if (automode.GetSelected() == &automode3)
			{
				//std::cout << "mode3" <<std::endl;
			}*/
			//std::cout << "\n" << std::endl;
	//		SmartDashboard::PutBoolean("forwardflag", forwardFlag);
//			SmartDashboard::PutBoolean("turnLeftFlag", turnLeftFlag);


		}

		void TeleopInit()
		{
			//frontLeft.SetSafetyEnabled(true);
			//frontRight.SetSafetyEnabled(true);
			//backLeft.SetSafetyEnabled(true);
			//backRight.SetSafetyEnabled(true);

			//frontLeft.SetExpiration(0.5);
			//frontRight.SetExpiration(0.5);
			//backLeft.SetExpiration(0.5);
			//backRight.SetExpiration(0.5);

			if (!(bool)gearHolder.IsRevLimitSwitchClosed() && !(bool)gearHolder.IsRevLimitSwitchClosed())
					{
					gearHolder.Set(-0.25);
					}
		}




			void TeleopPeriodic()
			{
				//double Forward = joy.GetAxis(Joystick::AxisType::kThrottleAxis); //joy.GetY(Joystick:: kRightHand);

// GEAR HOLDER CODE

				if (buttonA.Get() && (bool)gearHolder.IsFwdLimitSwitchClosed())
				{
					indicatorLed.Set(1);
					gearHolder.Set(-0.25);
				}
				else if (buttonA.Get() && (bool)gearHolder.IsRevLimitSwitchClosed())
				{
					indicatorLed.Set(0);
					gearHolder.Set(0.25);
				}



// CLIMB MODE CODE

				//SmartDashboard::PutBoolean("climbtoggle", climbToggle);
				//SmartDashboard::PutBoolean("climbmode", climbMode);

				if (buttonX.Get() && !climbToggle && allowModeChange)
				{
					climbToggle = true;
				}

				else if (buttonX.Get() && climbToggle && allowModeChange)
				{
					climbToggle = false;
				}


				if (buttonY.Get())
				{
					climb.Set(0.8);
					climbToggle = false;
				}
				else if (climbToggle)
				{
					climb.Set(0.4);
				}
				else
				{
					climb.Set(0.0);
				}

			/*	if (climbToggle)
				{
					climb.Set(0.2);
				}
				else if (climbMode)
				{
					climb.Set(joy.GetAxis(Joystick::AxisType::kThrottleAxis) * .5);
				}
				else
				{
					climb.Set(0.0);
				}

				if (buttonX.Get() && climbToggle)
				{
					climbToggle = false;
				}
				else if (buttonX.Get() && !climbToggle)
				{
					climbToggle = true;
				}

				if (buttonY.Get() && climbToggle)
				{
					climbMode = true;
					climbToggle = false;
				}
				else if (buttonY.Get() && climbMode)
				{
					climbMode = false;
				}
*/


				//if (!climbMode)  //Turns off drive functions when in climb mode
				//{

				if (buttonLBumper.Get() && !reverse)
				{
					reverse = true;
				}


				if (buttonLBumper.Get() && reverse)
				{
					reverse = false;
				}


					double turn = -1.0 * joy.GetAxis(Joystick::AxisType::kXAxis); //joy.GetX(Joystick:: kLeftHand);

					double direction = 0.0;

					double accelerator = .75;

					if (buttonB.Get())
					{
						accelerator = 1.0;
					}
					else
					{
						accelerator = .75;
					}

					if (joy.GetAxis(Joystick::AxisType::kThrottleAxis) > 0.0)
					{
						direction = joy.GetAxis(Joystick::AxisType::kThrottleAxis);

					}
					else if (joy.GetAxis(Joystick::AxisType::kTwistAxis) > 0.0)
					{
						direction = -1 * joy.GetAxis(Joystick::AxisType::kTwistAxis);

					}
					//drive.ArcadeDrive(joy, true);
					drive.ArcadeDrive(direction *  accelerator, turn, true);
					//drive.ArcadeDrive(direction, -0.2, true);
					Wait(0.005);	//	Wait for the motors to update. This removes the "A timeout has been exceeded..." Error
			//	}
				//frontLeft.Set (leftAxis);
				//frontRight.Set (leftAxis*-1);



				//if (climbToggle && buttonB.Get)
				/*else if (buttonB.Get()){
					climb.Set(0.5);
				}
				else
				{
					climb.Set(0.0);
				}
*/

				//SmartDashboard::PutString("Hi", "World");


				allowModeChange = !buttonX.Get();

			}// end void TeleopPeriodic()

			void AutonomousInit()
			{

				initAngleX = imu.GetAngleZ();

			if (!gearHolder.IsFwdLimitSwitchClosed())
			{
				gearHolder.Set(.25);
			}

			if (automode.GetSelected() == &automode1)	//center
			{
				//std::cout << "mode1" <<std::endl;
				forwardFlag = false;
				turnLeftFlag = false;
				turnRightFlag = false;
			}
			else if (automode.GetSelected() == &automode2) //left
			{
				//std::cout << "mode2" <<std::endl;
				forwardFlag = true;
				turnLeftFlag = false;
				turnRightFlag = true;
			}
			else if (automode.GetSelected() == &automode3) //right
			{
				forwardFlag = true;
				turnRightFlag = false;
				turnLeftFlag = true;
				//std::cout << "mode3" <<std::endl;
			}
			}

			void AutonomousPeriodic(){

				double targ1 = 320.0;
				double targ2 = 320.0;
				std::vector<double> arr = table->GetNumberArray("centerX", llvm::ArrayRef<double>());
							if (arr.size() == 2)
							{
								targ1 = arr[0];
								targ2 = arr[1];
							}

				if (forwardFlag)
				{

					timer1.Reset();
					timer1.Start();

					if( turnRightFlag ){ // in left position, reduce forward by ~5%
						while (timer1.Get() < 1.95)
						{
							drive.Drive(.35, 0.0);
						}
					}else{
						while (timer1.Get() < 2.18)
						{
							drive.Drive(.35, 0.0);
						}
					}
					drive.Drive(0.0, 0.0);
					forwardFlag = false;
				}

				if (turnLeftFlag)
				{
					while (imu.GetAngleZ() > (initAngleX - 35.0))
					{
						//Fixed Turn Speed
						drive.Drive(.35, -1.0);
					}
					std::vector<double> temp_arr;
					while (temp_arr.size() != 2)
					{
						temp_arr = table->GetNumberArray("centerX", llvm::ArrayRef<double>());
						drive.Drive(.25, -1.0);
					}
					drive.Drive(0.0, 0.0);
					turnLeftFlag = false;

				}

				if (turnRightFlag)
				{
					while (imu.GetAngleZ() < (initAngleX + 35.0))
					{
						//Fixed Turn Speed
						drive.Drive(.35, 1.0);
					}
					std::vector<double> temp_arr2;
					while (temp_arr2.size() != 2)
					{
						temp_arr2 = table->GetNumberArray("centerX", llvm::ArrayRef<double>());
						drive.Drive(.25, 1.0);
					}
					drive.Drive(0.0, 0.0);
					turnRightFlag = false;
				}

//				double my_angle;
//				my_angle = imu.GetAngleX();


				double mid = (((((targ1 + targ2)/2.0)-320.0)/320.0));
//				double mid = 1.0;
				SmartDashboard::PutNumber("Tempmidpoint", mid);
//				double Turn = 0.0;

//				if (mid >= (320 + 40)){
//
//					//Target is on the right
//					Turn = 1.00;
//					Speedy = 0.2;
//				}
//				else if (mid <= (320 - 40)){
//
//					//Target is on the left
//					Turn = -1.00;
//					Speedy = 0.2;
//				}
//				else {
//					//Target is somewhat on the center
//				Turn = 0;
//				Speedy = 0.2;
//				}
			//Tracking Drive Speed           Tracking Turn Gain
					drive.Drive(.3, (mid/2)* 1.0);





			}


			//to do list:
			//look at motor encoders, look into changing forward direction drivemodes, creating
			//deadband for joystick, actually looking into the manual if we have time after
			//school somehow, driving in automanous, enhance shooting code, aiming?, IMU?

};

START_ROBOT_CLASS(Robot);
