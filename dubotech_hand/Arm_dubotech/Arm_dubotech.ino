// Arm motor move
// Arm Dubotech
// Double Servo driver test
// Scanner


#include <Arduino.h>
#include <Wire.h>  // Required for I2C communication with the servo driver
#include <Adafruit_PWMServoDriver.h>  // Servo driver

// I2C PCA9685 PWM servo driver
//--------------- Right ARM -------------------------
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);

//--------------- Left ARM -------------------------
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);
#define SERVO_FREQ  50  // Frequency of the servos; 50Hz

// Waist rotation
#define SERVO_1   0
uint16_t servo1_angle = 1060;
uint16_t servo1_min = 1000;
uint16_t servo1_max = 2700;

// Shoulder elevationiii
#define SERVO_2   1
uint16_t servo2_angle = 1000;
uint16_t servo2_min = 1000;
uint16_t servo2_max = 2630;

// Elbow elevation
#define SERVO_3   2
uint16_t servo3_angle = 2340;
uint16_t servo3_min = 1000;
uint16_t servo3_max = 2700;

// Wrist elevation
#define SERVO_4   3
uint16_t servo4_angle = 1450;
uint16_t servo4_min = 500;
uint16_t servo4_max = 2600;

// Wrist rotation
#define SERVO_5   4
uint16_t servo5_angle = 1600;
uint16_t servo5_min = 1600;
uint16_t servo5_max = 2200;

// Gripper open
#define SERVO_6   5
uint16_t servo6_angle = 1000;
uint16_t servo6_min = 100;
uint16_t servo6_max = 2700;

// Should debug serial lines be printed?
bool debug = true;

// Variable to keep track of the current stage
int stage = 1;
int c_rate = 10;
bool target = false;  // Loop control variable
int inputValue;
void setup() {
  Serial.begin(9600);

  // Initialize PWM servo driver
  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ);

  //  // Move servos to home position
  //    pwm.setPWM(SERVO_1, 0, int(float(servo1_angle) / 1000000 * SERVO_FREQ * 4096));
  //    pwm.setPWM(SERVO_2, 0, int(float(servo2_angle) / 1000000 * SERVO_FREQ * 4096));
  //    pwm.setPWM(SERVO_3, 0, int(float(servo3_angle) / 1000000 * SERVO_FREQ * 4096));
  //    pwm.setPWM(SERVO_4, 0, int(float(servo4_angle) / 1000000 * SERVO_FREQ * 4096));
  //    pwm.setPWM(SERVO_5, 0, int(float(servo5_angle) / 1000000 * SERVO_FREQ * 4096));
  //    pwm.setPWM(SERVO_6, 0, int(float(servo6_angle) / 1000000 * SERVO_FREQ * 4096));

  Serial.println("Initialized. Use the keyboard to control the servos manually or let it run through stages.");
}

// Function to move servo gradually to the target angle
void moveServoGradually(uint8_t servo_num, uint16_t &current_angle, uint16_t target_angle) {
  int step = (current_angle < target_angle) ? 2 : -2;
  while (current_angle != target_angle) {
    current_angle += step;
    if ((step > 0 && current_angle > target_angle) || (step < 0 && current_angle < target_angle)) {
      current_angle = target_angle;
    }
    pwm.setPWM(servo_num, 0, int(float(current_angle) / 1000000 * SERVO_FREQ * 4096));
    delay(10);  // Adjust delay for speed control
  }
}



void inver_kin(int i) {
  //  servo2_angle = (1600 + (0.8 * abs(i)));
  servo2_angle = (1600 + (0.8 * abs(i)));
  int aa = map(i, -100, 100, -250, 250);
  servo3_angle = 1870 + aa;
  int bb = map(i, -100, 100, -280, 280);
  servo4_angle = 1500 - bb;
  Serial.println(i);  // Print the current value of i
  pwm.setPWM(SERVO_1, 0, int(float(servo1_angle) / 1000000 * SERVO_FREQ * 4096));
  pwm.setPWM(SERVO_2, 0, int(float(servo2_angle) / 1000000 * SERVO_FREQ * 4096));
  pwm.setPWM(SERVO_3, 0, int(float(servo3_angle) / 1000000 * SERVO_FREQ * 4096));
  pwm.setPWM(SERVO_4, 0, int(float(servo4_angle) / 1000000 * SERVO_FREQ * 4096));
  delay(100);         // Optional: Add a delay of 100 milliseconds between prints
}

void loop() {
  servo3_min = 3400 - servo1_angle;
  servo3_max = servo3_min + 750;

  // Stage-based servo control
  //  while (!target) {
  //    if (stage == 1) {
  //      // Stage 1: servo 4 -> 2130, servo 2 -> 1900
  //      moveServoGradually(SERVO_4, servo4_angle, 2130);
  //      moveServoGradually(SERVO_2, servo2_angle, 1900);
  //      stage = 2;  // Move to the next stage
  //    }
  //    else if (stage == 2) {
  //      // Stage 2: servo 4 -> 1970, servo 2 -> 1850
  //      moveServoGradually(SERVO_4, servo4_angle, 1970);
  //      moveServoGradually(SERVO_2, servo2_angle, 1850);
  //    stage = 3;  // Move to the next stage
  //    }
  //    else if (stage == 3) {
  //      // Stage 3: servo 4 -> 1870, servo 2 -> 1640
  //      moveServoGradually(SERVO_4, servo4_angle, 1870);
  //      moveServoGradually(SERVO_2, servo2_angle, 1640);
  //      stage = 4;  // Move to the next stage
  //    }
  //    else if (stage == 4) {
  //      // Stage 4: servo 4 -> 1680, servo 2 -> 1450
  //      moveServoGradually(SERVO_4, servo4_angle, 1680);
  //      moveServoGradually(SERVO_2, servo2_angle, 1450);
  //      target = true;  // End the loop after completing all stages
  //    }
  //  }

  //   Manual control using serial input
  ////  Comment this lines if you want to run ink.py code
  if (Serial.available() > 0) {
    char command = Serial.read();

    switch (command) {
      case 'W':
      case 'w':
        if (servo2_angle < servo2_max) servo2_angle += c_rate;
        servo3_min = 3400 - servo2_angle;
        servo3_max = servo3_min + 700;
        if (servo3_angle > servo3_max) {
          servo3_angle = servo3_max;
        }
        else if (servo3_angle < servo3_min) {
          servo3_angle = servo3_min;
        }
        break;
      case 'S':
      case 's':
        if (servo2_angle > servo2_min) servo2_angle -= c_rate;
        servo3_min = 3400 - servo2_angle;
        servo3_max = servo3_min + 750;
        if (servo3_angle > servo3_max) {
          servo3_angle = servo3_max;
        }
        else if (servo3_angle < servo3_min) {
          servo3_angle = servo3_min;
        }
        break;
      case 'A':
      case 'a':
        if (servo1_angle > servo1_min) servo1_angle -= c_rate;
        break;
      case 'D':
      case 'd':
        if (servo1_angle < servo1_max) servo1_angle += c_rate;
        break;
      case 'I':
      case 'i':
        if (servo3_angle < servo3_max) servo3_angle += c_rate;
        break;
      case 'K':
      case 'k':
        if (servo3_angle > servo3_min) servo3_angle -= c_rate;
        break;
      case 'J':
      case 'j':
        if (servo5_angle > servo5_min) servo5_angle -= c_rate;
        break;
      case 'L':
      case 'l':
        if (servo5_angle < servo5_max) servo5_angle += c_rate;
        break;
      case 'U':
      case 'u':
        if (servo4_angle > servo4_min) servo4_angle -= c_rate;
        break;
      case 'O':
      case 'o':
        if (servo4_angle < servo4_max) servo4_angle += c_rate;
        break;
      case 'C':
      case 'c':
        if (servo6_angle > servo6_min) servo6_angle -= c_rate; // Close gripper
        break;
      case 'V':
      case 'v':
        if (servo6_angle < servo6_max) servo6_angle += c_rate; // Open gripper
        break;
    }
    //  if (Serial.available() > 0) {
    //    // Read the input as a string and convert it to an integer
    //    inputValue = Serial.parseInt();
    //
    //    // Validate the input to ensure it's between 1 and 10
    //    if (inputValue >= 1 && inputValue <= 10) {
    //      // Map the input range [1, 10] to the output range [-100, 100]
    //      int outputValue = map(inputValue, 1, 10, -100, 100);
    //
    //      // Print the input and corresponding output values
    //      inver_kin(outputValue);
    //    }
    //    if (inputValue == 12){
    //      if (servo6_angle < servo6_max) servo6_angle += 10;
    //      }
    //    if (inputValue == 13){
    //      if (servo6_angle > servo6_min) servo6_angle -= 10;
    //      }
    //    if (inputValue == 15){
    //      if (servo1_angle < servo1_max) servo1_angle += 15;
    //      }
    //    if (inputValue == 16){
    //      if (servo1_angle > servo1_min) servo1_angle -= 15;
    //      }
    //    if (inputValue == 17){
    //      if (servo5_angle > servo5_min) servo5_angle -= 30;
    //      }
    //    if (inputValue == 18){
    //      if (servo5_angle < servo5_max) servo5_angle += 30;
    //      }
    //  }

    //-----------------------------------------------------------
    //        for (int i = -100; i <= 100; i++) {
    //          servo2_angle = (1600 + (0.8 * abs(i)));
    //          int aa = map(i, -100, 100, -250, 250);
    //          servo3_angle = 1870 + aa;
    //          int bb = map(i, -100, 100, -280, 280);
    //          servo4_angle = 1500 - bb;
    //          Serial.println(i);  // Print the current value of i
    //          pwm.setPWM(SERVO_1, 0, int(float(servo1_angle) / 1000000 * SERVO_FREQ * 4096));
    //          pwm.setPWM(SERVO_2, 0, int(float(servo2_angle) / 1000000 * SERVO_FREQ * 4096));
    //          pwm.setPWM(SERVO_3, 0, int(float(servo3_angle) / 1000000 * SERVO_FREQ * 4096));
    //          pwm.setPWM(SERVO_4, 0, int(float(servo4_angle) / 1000000 * SERVO_FREQ * 4096));
    //          delay(10);         // Optional: Add a delay of 100 milliseconds between prints
    //        }
    //        for (int i = 100; i >= -100; i--) {
    //          servo2_angle = (1600 + (0.8 * abs(i)));
    //          int aa = map(i, -100, 100, -250, 250);
    //          servo3_angle = 1870 + aa;
    //          int bb = map(i, -100, 100, -280, 280);
    //          servo4_angle = 1400 - bb;
    //          Serial.println(i);  // Print the current value of i
    //          pwm.setPWM(SERVO_1, 0, int(float(servo1_angle) / 1000000 * SERVO_FREQ * 4096));
    //          pwm.setPWM(SERVO_2, 0, int(float(servo2_angle) / 1000000 * SERVO_FREQ * 4096));
    //          pwm.setPWM(SERVO_3, 0, int(float(servo3_angle) / 1000000 * SERVO_FREQ * 4096));
    //          pwm.setPWM(SERVO_4, 0, int(float(servo4_angle) / 1000000 * SERVO_FREQ * 4096));
    //          delay(10);         // Optional: Add a delay of 100 milliseconds between prints
    //        }
    //-----------------------------------------------------------
    // Update servos based on manual input


    pwm.setPWM(SERVO_1, 0, int(float(servo1_angle) / 1000000 * SERVO_FREQ * 4096));
    pwm.setPWM(SERVO_2, 0, int(float(servo2_angle) / 1000000 * SERVO_FREQ * 4096));
    pwm.setPWM(SERVO_3, 0, int(float(servo3_angle) / 1000000 * SERVO_FREQ * 4096));
    pwm.setPWM(SERVO_4, 0, int(float(servo4_angle) / 1000000 * SERVO_FREQ * 4096));
    pwm.setPWM(SERVO_5, 0, int(float(servo5_angle) / 1000000 * SERVO_FREQ * 4096));
    pwm.setPWM(SERVO_6, 0, int(float(servo6_angle) / 1000000 * SERVO_FREQ * 4096));
    delay(20);
    if (debug) {
      Serial.print("1: ");
      Serial.print(servo1_angle);
      Serial.print("\t2: ");
      Serial.print(servo2_angle);
      Serial.print("\t3: ");
      Serial.print(servo3_angle);
      Serial.print("\t3: ");
      Serial.print(servo3_min);
      Serial.print("\t3: ");
      Serial.print(servo3_max);
      Serial.print("\t4: ");

      Serial.print(servo4_angle);
      Serial.print("\t5: ");
      Serial.print(servo5_angle);
      Serial.print("\t6: ");
      Serial.print(servo6_angle);
      Serial.println();
    } //// if closing bracker manual code
  }
}// Loop Close bracket
