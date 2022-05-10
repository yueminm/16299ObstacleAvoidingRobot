#ifndef _MOTOR_H
#define _MOTOR_H


class Motor
{
  public:
          void Pin_init();          
          static void Stop();
          void Forward(int speed);
          void Back(int speed);
          void Left(int speed);
          void Right(int speed);
          
  private:
          /*Motor pin*/
          #define AIN1 7
          #define PWMA_LEFT 5
          #define BIN1 12
          #define PWMB_RIGHT 6
          #define STBY_PIN 8
  };







#endif
