#ifndef _ULTRASONIC_H
#define _ULTRASONIC_H


class Ultrasonic
{
  public:
          void Pin_init();
          void Ultrasonic_detect();
          void Check();

  public:
          static char measure_flag;
          static unsigned long measure_prev_time;
          static unsigned long get_distance_prev_time;
          static double distance_value;
          static int front_detect;
          
  private:
          #define ECHO_PIN A3
          #define TRIG_PIN 11
          #define Distance_MIN 3
          #define Distance_MAX 35
          #define Obstacle_MIN 10
          #define distance_judgement (distance_value > Distance_MIN && distance_value < Distance_MAX)
          #define obstalce_judgement (Ultrasonic.distance_value < Obstacle_MIN)
          #define obstacle_judgement2 (Ultrasonic.distance_value < 10)

  };







#endif
