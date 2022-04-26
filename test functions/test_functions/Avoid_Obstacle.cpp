#include "Avoid_Obstacle.h"
#include "Motor.h"
extern Motor Motor;

void Function::Obstacle_Avoid(int speed)
{
  Motor.Left(speed, 1000);
  delay(1000);
  Motor.Forward(speed, 1500);
  delay(1500);
  Motor.Right(speed, 1100);
  delay(1100);
  Motor.Forward(speed, 2600);
  delay(2600);
  Motor.Right(speed, 1200);
  delay(1200);
  Motor.Forward(speed, 1700);
  delay(1700);
  Motor.Left(speed, 1200);
  delay(1200);
  Motor.Forward(speed, 2200);
  delay(2200);
  Motor.Stop();
  delay(10000);

}
