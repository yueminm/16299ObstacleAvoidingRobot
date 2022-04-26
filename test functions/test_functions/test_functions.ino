#include "Motor.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "MsTimer2.h"
#include "Ultrasonic.h"
#include "Avoid_obstacle.h"

//extern Timer2 Timer2;
//extern Mpu6050 Mpu6050;
extern Motor Motor;
//extern Balanced Balanced;
extern Ultrasonic Ultrasonic;
//extern IR IR;
extern Function Function;



void setup() 
{
  Motor.Pin_init();
//  IR.Pin_init();
  Ultrasonic.Pin_init();
  Motor.Encoder_init();
//  Timer2.init(TIMER);
//  Mpu6050.init();
  Serial.begin(9600);
  delay(100);
}

int v = 50;

char Ultrasonic ::measure_flag = 0;
unsigned long Ultrasonic ::measure_prev_time = 0;
unsigned long Ultrasonic::get_distance_prev_time = 0;
double Ultrasonic ::distance_value;

float Motor::x_position = 0.;
float Motor::y_position = 0.;
float Motor::orientation = 0.;
float Motor::dt = 0.015;


void loop() 
{
  Motor.Forward(50, 1000);
  delay(1000);
  Motor.Right(50, 500);
  delay(500);
  Motor.Left(50, 1000);
  delay(1000);
  Motor.Forward(50, 1000);
  delay(1000);
  Motor.Stop();
  Serial.print("x: ");
  Serial.print(Motor::x_position, 6);
  Serial.print("     y: ");
  Serial.print(Motor::y_position, 6);
  Serial.print("     theta: ");
  Serial.println(Motor::orientation, 6);
  delay(100000000);
//    Ultrasonic.Get_Distance();
////    Serial.println(Ultrasonic::distance_value);
//    if (Ultrasonic::distance_value > 12) {
////      Serial.println("go");
//      Motor.Forward(v);
//    }
//    if (Ultrasonic::distance_value < 12) {
////      Serial.println("avoid");
//      Function.Obstacle_Avoid(v);
//    }

    
}
