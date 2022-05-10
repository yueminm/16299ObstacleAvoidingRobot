#include <Arduino.h>
#include "Ultrasonic.h"
#include "MsTimer2.h"

void Ultrasonic::Pin_init()
{
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
}

long duration;

void Ultrasonic::Ultrasonic_detect()
{
  Ultrasonic::front_detect = 0;
  if (millis() - Ultrasonic::get_distance_prev_time > 80)
  { 
    delayMicroseconds(1);
    Ultrasonic::get_distance_prev_time = millis();
    Ultrasonic::measure_flag = 0;
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    duration = pulseIn(ECHO_PIN, HIGH);
    Ultrasonic::distance_value = duration * 0.034 / 2;
  }
  if (Ultrasonic::distance_value <= 12)
  {
    Ultrasonic::front_detect = 1;
  }
}
