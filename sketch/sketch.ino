//TODO
#include <ADCTouch.h>
#include "tinyServo85.h"

#define STARTUP_DELAY 5000

#define SERVO_PIN 1
#define TOUCH_PIN 1 //this is analog "1" not the same as the digital pin

#define TOUCH_SAMPLE_PERIOD 10
#define TOUCH_DELTA 30
#define SAMPLE_AVERAGE_NUM 4

#define MILLI_PER_DEGREE 20
#define SERVO_NEUTRAL_POSITION 0
#define SERVO_LIGHT_OFF_POSITION 90
// I think the library requires these but Im not sure
#define SVOMINPULSE 1000
#define SVOMAXPULSE 2000


tinyServo85 servo;

int get_touch_value() {
  return ADCTouch.read(TOUCH_PIN, __AVR_ATtiny85__);
}

bool is_pad_touched() {
  static int threshold = get_touch_value() + TOUCH_DELTA;
  static int last_values[SAMPLE_AVERAGE_NUM];
  static int i = 0;
  static int sum = 0;

  sum -= last_values[i];
  last_values[i] = get_touch_value();
  sum += last_values[i];

  if (++i == SAMPLE_AVERAGE_NUM)
    i = 0;

  return (sum / SAMPLE_AVERAGE_NUM) > threshold;
}

void move_servo(int pos) {
  static int last_pos = pos;
  do {
    if (last_pos > pos)
      last_pos--;
    else if (last_pos < pos)
      last_pos++;
    servo.setServo(SERVO_PIN, last_pos);
    delay(MILLI_PER_DEGREE);
  } while(last_pos != pos);
}

void turn_off_light_switch() {
  move_servo(SERVO_LIGHT_OFF_POSITION);
  //delay(SERVO_MOVE_TIME);
  move_servo(SERVO_NEUTRAL_POSITION);
}

void setup() 
{
  // setup servo
  servo.setCTC();
  servo.attachServo(SERVO_PIN);
  move_servo(SERVO_NEUTRAL_POSITION);

  // setup touch
  delay(STARTUP_DELAY); // give user time to move hand away
  
  // initialize all values of static array
  for(int i; i < SAMPLE_AVERAGE_NUM; i++)
    is_pad_touched();
} 

void loop() 
{ 
  if (is_pad_touched()) {
    turn_off_light_switch();
  }
  //delay(TOUCH_SAMPLE_PERIOD);
}