//TODO
#ifdef SERIAL_MODE
  #include <SoftwareSerial.h>
  #define RX 3
  #define TX 4
  SoftwareSerial Serial(RX, TX);
#endif

#include <ADCTouch.h>

#define STARTUP_DELAY 5000



#define PAD 1 //This is not the same "1" as the digital pin
#define TOUCH_THRESHOLD 70
bool is_pad_touched() {
  static int last_touch_value = ADCTouch.read(PAD, __AVR_ATtiny85__);
  return ADCTouch.read(PAD, __AVR_ATtiny85__) - last_touch_value > TOUCH_THRESHOLD;
}


#define SERVO 1
void turn_off_light_switch() {
  analogWrite(SERVO, 200);
  delay(500);
  analogWrite(SERVO, 150);
  delay(5000);
}

void setup() 
{

  pinMode(SERVO, OUTPUT);
  digitalWrite(SERVO, LOW);

  //Delay to give time to move hand away
  delay(STARTUP_DELAY);

#ifdef SERIAL_MODE
  Serial.begin(9600);
  Serial.println("starting");
#endif
} 

#define SAMPLE_PERIOD 50
void loop() 
{ 
  if (is_pad_touched()) {
    #ifdef SERIAL_MODE
      Serial.begin(9600);
      Serial.println("starting");
    #endif
    turn_off_light_switch();
  }
  delay(SAMPLE_PERIOD);
}