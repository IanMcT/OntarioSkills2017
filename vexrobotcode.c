#pragma config(Motor,  port1,            ,             tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,            ,             tmotorServoContinuousRotation, openLoop, reversed, driveRight)
#pragma config(Motor,  port5,            ,             tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port6,            ,             tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port9,            ,             tmotorServoContinuousRotation, openLoop, driveLeft)
#pragma config(Motor,  port10,           ,             tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// claw is 5
// arm is 6
/*int lowArmThresh = 0, lowClawThresh = 0;
int highArmThresh = 1270, highClawThresh = 300;
int armPos = 0, clawPos = 0; */
int armPower;
int clawPower;
int xPower;
int yPower;
int dirMulti = 1;
float speed = 1.0;

void armControl()
{
	if(vexRT[Btn6U]) armPower = 127;
	else if(vexRT[Btn6D]) armPower = -127;
	//else
	motor[port6] = armPower;

}

void clawControl()
{
	if(vexRT[Btn5U]) clawPower = 127;
	if(vexRT[Btn5D]) clawPower = -127;

	motor[port5] = clawPower;
}

void dirMultiControl()
{
	if(vexRT[Btn8R])
	{
		dirMulti *= -1;
	}
	wait1Msec(2);
}

void speedControl()
{
	int speedChange = 0.1;
	if(vexRT[Btn7D] && speed > 0)
	{
		speed -= speedChange;
	}
	else if(vexRT[Btn7U] && speed < 1)
	{
		speed += speedChange;
	}
	wait1Msec(5);
}

void drive()
{
	if(abs(vexRT[Ch1]) > 15)
	{
		int power = -1*vexRT[Ch1];
		motor[port1] = power;
		motor[port2] = power;
		motor[port9] = -power;
		motor[port10] = -power;
	}
	else{
		xPower = vexRT[Ch4];
		yPower = vexRT[Ch3];
		if(abs(xPower) > 10 || abs(yPower) > 10)
		{
			int powerFront = ((yPower + xPower) * dirMulti);
			int powerBack = ((yPower + xPower*-1) * dirMulti);

			/*if(powerFront < -127) powerFront = -127;
			if(powerFront > 127) powerFront = 127;
			if(powerBack < -127) powerBack = -127;
			if(powerBack > 127) powerBack = 127;*/

			motor[port2] = powerFront;
			motor[port1] = powerBack;
			motor[port10] = powerFront;
			motor[port9] = powerBack;
		}
		else
		{
				motor[port2] = 0;
			motor[port1] = 0;
			motor[port10] = 0;
			motor[port9] =0;
		}
	}
}

task main(){
	//moveMotorTarget(2, 0, 300);
	//int power;
	while(1==1){
		/*power = vexRT[Ch2];
		motor[port8] = power;
		motor[port9]=power;
		motor[port2]=power;
		motor[port3]=power;
		wait1Msec(1);*/
		dirMultiControl();
		speedControl();
		drive();
		armControl();
		clawControl();
		armPower = 0; //12;
		clawPower = 0;
		xPower = 0;
		yPower = 0;
		wait1Msec(1);
	}
}
