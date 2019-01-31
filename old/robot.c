#pragma config(Motor,  port1,           backLeft,      tmotorNone, openLoop)
#pragma config(Motor,  port2,           frontLeft,     tmotorNone, openLoop)
#pragma config(Motor,  port3,           flipperLeft,   tmotorNone, openLoop)
#pragma config(Motor,  port4,           leftFlywheel,  tmotorNone, openLoop)
#pragma config(Motor,  port5,           rightFlywheel, tmotorNone, openLoop)
#pragma config(Motor,  port6,           topIntake,     tmotorNone, openLoop)
#pragma config(Motor,  port7,           bottomIntake,  tmotorNone, openLoop)
#pragma config(Motor,  port8,           flipperRight,  tmotorNone, openLoop)
#pragma config(Motor,  port9,           frontRight,    tmotorNone, openLoop)
#pragma config(Motor,  port10,          backRight,     tmotorNone, openLoop)

void arcadeDrive();
void tankDrive();
void topRollerQuickRot();

int channelOne;
int channelTwo;
int channelThree;

task main()
{
	bool flywheelToggle = false;
	bool driveToggle = false;

	while(true){
		//Drive
		channelThree = vexRT[Ch3];
		channelTwo = vexRT[Ch2];
		channelOne = vexRT[Ch1];

		if(abs(channelOne) < 5)
			channelOne = 0;
		if(abs(channelTwo) < 5)
			channelTwo = 0;
		if(abs(channelThree) < 5)
			channelThree = 0;

		if(vexRT(Btn8U)){
			while(vexRT(Btn8U)){
			}
			driveToggle = !driveToggle;
		}

		if(!driveToggle)
			arcadeDrive();
		else
			tankDrive();

		//Flywheel
		if(vexRT(Btn7L)){
			while(vexRT(Btn7L)){
  		}
			flywheelToggle = !flywheelToggle;
		}

		if(flywheelToggle){
			motor[leftFlywheel] = 127;
			motor[rightFlywheel] = -127;
		}
		else{
			motor[leftFlywheel] = 0;
			motor[rightFlywheel] = 0;
		}

		//Bottom Intake
		if(vexRT[Btn6U]){
			motor[bottomIntake] = 127;
			motor[flipperLeft] = 127;
		  motor[flipperRight] = -127;
		}
		else if(vexRT[Btn6D]){
			motor[bottomIntake] = -127;
			motor[flipperLeft] = -127;
			motor[flipperRight] = 127;
		}
		else{
			motor[bottomIntake] = 0;
			motor[flipperLeft] = 0;
			motor[flipperRight] = 0;
		}

		//Top Intake
		if(vexRT[Btn5U])
			motor[topIntake] = 127;
		else if(vexRT[Btn5D])
			motor[topIntake] = -127;
		else
			motor[topIntake] = 0;

		if(vexRT[Btn7D]){ //top intake small turn
			topRollerQuickRot();
		}
	}
}

void arcadeDrive(){
	motor[frontLeft]= channelOne + channelTwo;
	motor[backLeft]= channelOne + channelTwo;
	motor[frontRight]= channelOne - channelTwo;
	motor[backRight]= channelOne - channelTwo;
}

void tankDrive(){
	motor[frontLeft] = channelThree;
	motor[backLeft] = channelThree;
	motor[frontRight] = -channelTwo;
	motor[backRight] = -channelTwo;
}

void topRollerQuickRot(){
	while(vexRT(Btn7D)){
  }
	motor[topIntake] = 127;
	wait10Msec(30);
	motor[topIntake] = 0;
}
