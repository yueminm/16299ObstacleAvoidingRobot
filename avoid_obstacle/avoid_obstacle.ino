#include "Motor.h"
#include "Ultrasonic.h"
#include "IR.h"
#include "MsTimer2.h"



extern Motor Motor;
extern Ultrasonic Ultrasonic;
extern IR IR;

// input goal position
float x_goal = 10.;
float y_goal = 10.;

// initialize global variables
static int IR::left_detect = 0;
static int IR::right_detect = 0;
static int Ultrasonic::front_detect = 0;
char Ultrasonic::measure_flag = 0;
unsigned long Ultrasonic::measure_prev_time = 0;
unsigned long Ultrasonic::get_distance_prev_time = 0;
static double Ultrasonic::distance_value = 1000000;

// default velocity
int v = 60;
float v_scale = 0.00016667;

// initialize current position
float x = 0.;
float y = 0.;
float theta = 0.;
float theta_goal = 0.;

// initialize time
int time_cur = 0;
int time_prev = 0;

// initialize constants
float omega = 0.00174533;

// initialize flags
int turn_at_start = 0;
int move_body_length = 0;
int robot_motion = 0; // 0 for straight, 1 for left, 2 for right

// set PID gains
float P_gain = 0.98;
float I_gain = 0.33;

void setup() 
{
  Motor.Pin_init();
  Ultrasonic.Pin_init();
  IR.Pin_init();
}


void loop() 
{
  // update location
  time_cur = millis();
  float dt = time_cur - time_prev;
  if (robot_motion == 0) {
    x = x + dt*v*v_scale*cos(theta);
    y = y + dt*v*v_scale*sin(theta);
  }

  else if (robot_motion == 1){
    theta = theta + dt*omega;
  }

  else if (robot_motion == 2){
    theta = theta - dt*omega;
  }

  // check whether goal is reached
  if (abs(x_goal-x) <= 1 and abs(y_goal-y)<= 1){
    Motor.Stop();
    exit(0);
  }

  // sensor detection
  IR.IR_detect();
  Ultrasonic.Ultrasonic_detect();
  
  // case 1: no detect- turn and go straight
  if (Ultrasonic::front_detect == 0 and IR::left_detect == 0 and IR::right_detect == 0 and move_body_length == 0) {
    
    // turn at beginning
    theta_goal = atan2((y_goal-y), (x_goal-x));
    float theta_turn = theta_goal - theta;
    float t_turn = abs(theta_turn / omega);
    if (theta_turn >= 0) {
      Motor.Left(v);
      delay(t_turn);
      theta += t_turn*omega;
    }
    else {
      Motor.Right(v);
      delay(t_turn);
      theta -= t_turn*omega;
    }

    // go straight
    Motor.Forward(v);
    time_prev = millis();
    robot_motion = 0;
  }

  // case 2: right IR sensor- turn left
  else if  (IR::right_detect == 1) {
    Motor.Left(v);
    time_prev = millis();
    move_body_length = 1;
    robot_motion = 1;
  }

  // case 3: left IR sensor- turn right
  else if (IR::left_detect == 1) {
    Motor.Right(v);
    time_prev = millis();
    move_body_length = 1;
    robot_motion = 2;
  }

  // case 4: ultrasonic sensor- turn left
  else if (Ultrasonic::front_detect == 1){
    Motor.Left(v);
    time_prev = millis();
    move_body_length = 1;
    robot_motion = 1;
  }

  // case 5: move body length
  else if (move_body_length == 1){
    Motor.Forward(v);
    delay(800);
    time_prev = millis();
    move_body_length = 0;
    robot_motion = 0;
  }
}
