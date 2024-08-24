#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);
// you can also call it with a different address and I2C interface
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40, Wire);



//int pwm = 0
#define SERVO_1   0
uint16_t servo1_angle = 100;
uint16_t servo1_min = 100;
uint16_t servo1_max = 2000 ;

// Shoulder elevationiii
#define SERVO_2   1
uint16_t servo2_angle = 1000;
uint16_t servo2_min = 1000;
uint16_t servo2_max = 2630;

int SERVO_FREQ = 50;


void setup() {
  Serial.begin(9600);
  Serial.println("GPIO test!");

  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ);  // Set to whatever you like, we don't use it in this demo!

  // if you want to really speed stuff up, you can go into 'fast 400khz I2C' mode
  // some i2c devices dont like this so much so if you're sharing the bus, watch
  // out for this!
  Wire.setClock(400000);
}

void loop() {
  for(servo1_angle = servo1_min; servo1_angle <= servo1_max; servo1_angle = servo1_angle + SERVO_FREQ){
    pwm.setPWM(SERVO_1, 0, int(float(servo1_angle) / 1000000 * SERVO_FREQ * 4096));
    delay(100);
    Serial.print("1: ");
    Serial.print(servo1_angle);
    Serial.print("\t2: ");
    Serial.print(servo2_angle);
    Serial.println("");
  }
  
  for(servo1_angle = servo1_max; servo1_angle >= servo1_min; servo1_angle = servo1_angle - SERVO_FREQ){
    pwm.setPWM(SERVO_1, 0, int(float(servo1_angle) / 1000000 * SERVO_FREQ * 4096));
    delay(100);
    Serial.print("1: ");
    Serial.print(servo1_angle);
    Serial.print("\t2: ");
    Serial.print(servo2_angle);
    Serial.println("");
  }
}
