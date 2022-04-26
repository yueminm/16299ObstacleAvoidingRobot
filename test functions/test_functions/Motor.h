#ifndef _MOTOR_H
#define _MOTOR_H


class Motor
{
  public:
          void Pin_init();
          /*Measuring_speed*/
          void Encoder_init();
           
          void Control(int AIN1_value,int BIN1_value,int PWM_pin,int speed);
          
          void Stop();
          void Forward(int speed, float t);
          void Back(int speed, float t);
          void Left(int speed, float t);
          void Right(int speed, float t);
          static void EncoderCountRightA();
          static void EncoderCountLeftA();

  public:
          static unsigned long encoder_count_right_a;
          static unsigned long encoder_count_left_a;
          static float x_position;
          static float y_position;
          static float orientation;
          static float dt;
          
          
          
  private:
          /*Motor pin*/
          #define AIN1 7
          #define PWMA_LEFT 5
          #define BIN1 12
          #define PWMB_RIGHT 6
          #define STBY_PIN 8
          
          /*Encoder measuring speed  pin*/
          #define ENCODER_LEFT_A_PIN 2
          #define ENCODER_RIGHT_A_PIN 4

  };







#endif
