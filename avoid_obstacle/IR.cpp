/*
This program tests the Elegoo Tumbller IR sensors.
The infrared light emitted by the light source is received by the
photosensitive element through the reﬂection of the object to be
tested, so the interrupt will be triggered when reflected light
is detect. To distinguish this light from other light, we
turn this light on and off (presumably at a specific frequency (38kHz?),
and send only 39 flashes.
Presumably this is the only pattern the receiver responds to.
*/

// This is a different library than the one that came with the Tumbller code.
#include "PinChangeInterrupt.h"
//#include "PinChangeInt.h"
#include "IR.h"
// Pin definitions
//#define IR_DRIVE_PIN 9
//#define LEFT_RECEIVE_PIN A0
// #define LEFT_RECEIVE_PIN 10
//#define RIGHT_RECEIVE_PIN A1
//#define COUNTER_INIT 100000UL

// Global variables
volatile unsigned long counter = 0;
// volatile tells the compiler that this can be changed by an interrupt
// service routine, so don't optimize any code that involves this variable.
volatile int left_receive = 0;
volatile int right_receive = 0;

/*
The drive function for the IR illuminators.
in the Tumbller code this is called send38K ?????
what frequency is this?
1000000/18 = 55.556kHz max, need to take into account the digitalWrite time.
*/

static void IR::drive_ir( void )
{
  static unsigned long ir_send_time = 0;

  // this time check seems to make sure we don't send flashing IR light
  // more often that every 15 milliseconds.
  if (millis() - ir_send_time > 15)
    {
      for (int i = 0; i < 39; i++)
        {
          digitalWrite(IR_DRIVE_PIN, LOW);
          delayMicroseconds(9);
          digitalWrite(IR_DRIVE_PIN, HIGH);
          delayMicroseconds(9);
        }
      ir_send_time=millis();
    }
}

/*
The Interrupt service routines
In the Elegoo v1.1 source (Ultrasonic.h) the length of the pulse is
measured, by capturing the RISING and FALLING edges of the pulse,
but nothing is done with that information. So I didn't do that.
*/

static void IR::Left_Receive()
{
  // Set counter
  counter = COUNTER_INIT;
  // Turn LED on
  digitalWrite( LED_BUILTIN, 1 );
  left_receive++;
}

static void IR::Right_Receive()
{
  // Set counter
  counter = COUNTER_INIT;
  // Turn LED on
  digitalWrite( LED_BUILTIN, 1 );
  right_receive++;
}

/*
In checkObstacle() in the Elegoo v1.1 source (Ultrasonic.h) some kind
of filter is used. I ignored that.
*/

void IR::Pin_init()
{
//  IR::counter = 0;
//  IR::left_receive = 0;
//  IR::right_receive = 0;
  // setup for IR - set IR pins, and define interrupt service routines (ISRs)
  pinMode(LEFT_RECEIVE_PIN, INPUT_PULLUP);
  pinMode(RIGHT_RECEIVE_PIN, INPUT_PULLUP);
  pinMode(IR_DRIVE_PIN, OUTPUT);
  attachPCINT( digitalPinToPCINT(LEFT_RECEIVE_PIN), IR::Left_Receive, CHANGE );
  attachPCINT( digitalPinToPCINT(RIGHT_RECEIVE_PIN), IR::Right_Receive, CHANGE );
//  attachInterrupt(digitalPinToInterrupt(LEFT_RECEIVE_PIN), Left_Receive, CHANGE);
//  attachInterrupt(digitalPinToInterrupt(RIGHT_RECEIVE_PIN), Right_Receive, CHANGE);
  // Set LED to output when IR is sensing something.
  pinMode( LED_BUILTIN, OUTPUT );

//  Serial.begin(115200);
//  delay( 1000 );
//  Serial.println( "Testing the IR, which are the two silver boxes " );
//  Serial.println( "on the front sides of the motherboard." );
}

void IR::IR_detect()
{
  IR::left_detect = 0;
  IR::right_detect = 0;
  counter--;
  if ( counter <= 0 )
    {
      digitalWrite( LED_BUILTIN, 0 );
      counter = 0;
    }

  if ( left_receive > 0 )
    {
      IR::left_detect = 1;
      left_receive = 0;
    }

  if ( right_receive > 0 )
    {
      IR::left_detect = 1;
      right_receive = 0;
    }
  IR::drive_ir();
}
