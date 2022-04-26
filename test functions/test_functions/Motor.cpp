#include <Arduino.h>
#include "Motor.h"
#include "PinChangeInt.h"
#include "MsTimer2.h"
//#include "Ultrasonic.h"

long r = 10;
float c = 0.31415;

void Motor::Pin_init()
{
  pinMode(AIN1, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(PWMA_LEFT, OUTPUT);
  pinMode(PWMB_RIGHT, OUTPUT);
  pinMode(STBY_PIN, OUTPUT);
  digitalWrite(STBY_PIN, HIGH);
}

void Motor::Stop()
{
  analogWrite(PWMA_LEFT, 0);
  analogWrite(PWMB_RIGHT, 0);
}

void Motor::Forward(int speed, float t)
{
  digitalWrite(AIN1, 0);
  digitalWrite(BIN1, 0);
  analogWrite(PWMA_LEFT, speed);
  analogWrite(PWMB_RIGHT, speed);
  Motor::x_position += speed * c * t / 1000. * cos(Motor::orientation);
  Motor::y_position += speed * c * t / 1000. * sin(Motor::orientation);
}

void Motor::Back(int speed, float t)
{
  digitalWrite(AIN1, 1);
  digitalWrite(BIN1, 1);
  analogWrite(PWMA_LEFT, speed);
  analogWrite(PWMB_RIGHT, speed);
  Motor::x_position -= speed * c * t / 1000. * cos(Motor::orientation);
  Motor::y_position -= speed * c * t / 1000. * sin(Motor::orientation);
}


void Motor::Left(int speed, float t)
{
  digitalWrite(AIN1, 1);
  digitalWrite(BIN1, 0);
  analogWrite(PWMA_LEFT, speed);
  analogWrite(PWMB_RIGHT, speed);
  Motor::orientation += speed * c / r * t / 1000.;
  
}

void Motor::Right(int speed, float t)
{
  digitalWrite(AIN1, 0);
  digitalWrite(BIN1, 1);
  analogWrite(PWMA_LEFT, speed);
  analogWrite(PWMB_RIGHT, speed);
  Motor::orientation -= speed * c / r * t / 1000.0;
}

void Motor::Control(int PIN, int PIN_value, int PWM_pin, int speed)
{
  digitalWrite(PIN, PIN_value);
  analogWrite(PWM_pin, speed);
}

void Motor::Encoder_init()
{
  attachInterrupt(digitalPinToInterrupt(ENCODER_RIGHT_A_PIN), EncoderCountRightA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_LEFT_A_PIN), EncoderCountLeftA, CHANGE);
//  attachInterrupt(digitalPinToInterrupt(ENCODER_RIGHT_A_PIN), EncoderCountRightA, CHANGE);
}

unsigned long Motor::encoder_count_right_a;
//Getting Right Wheel Speed.
static void Motor::EncoderCountRightA()
{
  Motor::encoder_count_right_a++;
}


unsigned long Motor::encoder_count_left_a;
//Getting Left Wheel Speed.
static void Motor::EncoderCountLeftA()
{
  Motor::encoder_count_left_a++;
}
