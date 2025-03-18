//TODO
#include <ADCTouch.h>
#include "tinyServo85.h"

#define STARTUP_DELAY 5000

#define SERVO_PIN 1
#define TOUCH_PIN 1 //this is analog "1" not the same as the digital pin

#define TOUCH_SAMPLE_PERIOD 50
#define TOUCH_THRESHOLD 50

#define MILLI_PER_DEGREE 50
#define SERVO_NEUTRAL_POSITION 0
#define SERVO_LIGHT_OFF_POSITION 90
#define SERVO_MOVE_TIME 500
// I think the library requires these but Im not sure
#define SVOMINPULSE 1000
#define SVOMAXPULSE 2000


tinyServo85 servo;

int get_touch_value() {
  return ADCTouch.read(TOUCH_PIN, __AVR_ATtiny85__);
}

bool is_pad_touched() {
  static int initial_touch_value = get_touch_value();
  return get_touch_value > initial_touch_value + TOUCH_THRESHOLD;
}

void turn_off_light_switch() {
  servo.setServo(SERVO_PIN, SERVO_LIGHT_OFF_POSITION);
  delay(SERVO_MOVE_TIME);
  servo.setServo(SERVO_PIN, SERVO_NEUTRAL_POSITION);
}

void setup() 
{
  // setup servo
  servo.setCTC();
  servo.attachServo(SERVO_PIN);
  servo.homeServos();

  // setup touch
  delay(STARTUP_DELAY); // give user time to move hand away
  is_pad_touched();
} 

void loop() 
{ 
  if (is_pad_touched()) {
    turn_off_light_switch();
  }
  delay(TOUCH_SAMPLE_PERIOD);
}