#ifndef _IR_H
#define _IR_H


class IR
{
  public:
          void Pin_init();
          static void drive_ir();
          static void Left_Receive();
          static void Right_Receive();
          void IR_detect();

  public:
          static int left_detect;
          static int right_detect;

  private:
          #define IR_DRIVE_PIN 9
          #define LEFT_RECEIVE_PIN A0
          #define RIGHT_RECEIVE_PIN A1
          #define COUNTER_INIT 100000UL
          
  };


  #endif
