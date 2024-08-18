#include <Arduino.h>
#include <Wire.h>  // Required for I2C communication with the servo driver
#include <Adafruit_PWMServoDriver.h>  // Servo driver

// I2C PCA9685 PWM servo driver
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);
#define SERVO_FREQ  50  // Frequency of the servos; 50Hz

// Waist rotation
#define SERVO_1   0
uint16_t servo1_angle = 1130;
uint16_t servo1_min = 300;
uint16_t servo1_max = 2700;

// Shoulder elevation
#define SERVO_2   1
uint16_t servo2_angle = 1700;
uint16_t servo2_min = 470;
uint16_t servo2_max = 2630;

// Elbow elevation
#define SERVO_3   2
uint16_t servo3_angle = 1630;
uint16_t servo3_min = 1000;
uint16_t servo3_max = 2800;

// Wrist elevation
#define SERVO_4   3
uint16_t servo4_angle = 1800;
uint16_t servo4_min = 500;
uint16_t servo4_max = 2600;

// Wrist rotation
#define SERVO_5   4
uint16_t servo5_angle = 700;
uint16_t servo5_min = 500;
uint16_t servo5_max = 2500;

// Gripper open
#define SERVO_6   5
uint16_t servo6_angle = 600;
uint16_t servo6_min = 550;
uint16_t servo6_max = 1250;

// Should debug serial lines be printed?
bool debug = true;

// Variable to keep track of the current stage
int stage = 1;
bool target = false;  // Loop control variable
int inputValue;
void setup() {
  Serial.begin(9600);

  // Initialize PWM servo driver
  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ);

  //  // Move servos to home position
  //  pwm.setPWM(SERVO_1, 0, int(float(servo1_angle) / 1000000 * SERVO_FREQ * 4096));
  //  pwm.setPWM(SERVO_2, 0, int(float(servo2_angle) / 1000000 * SERVO_FREQ * 4096));
  //  pwm.setPWM(SERVO_3, 0, int(float(servo3_angle) / 1000000 * SERVO_FREQ * 4096));
  //  pwm.setPWM(SERVO_4, 0, int(float(servo4_angle) / 1000000 * SERVO_FREQ * 4096));
  //  pwm.setPWM(SERVO_5, 0, int(float(servo5_angle) / 1000000 * SERVO_FREQ * 4096));
  //  pwm.setPWM(SERVO_6, 0, int(float(servo6_angle) / 1000000 * SERVO_FREQ * 4096));

  Serial.println("Initialized. Use the keyboard to control the servos manually or let it run through stages.");
}
void inver_kin(int i) {
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
  //      stage = 3;  // Move to the next stage
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

  // Manual control using serial input
  //  ---------------------------------------- Manual Control Uncomment this ---------------------------------------------
  //  if (Serial.available() > 0) {
  //    char command = Serial.read();
  //
  //    switch (command) {
  //      case 'W':
  //      case 'w':
  //        if (servo2_angle < servo2_max) servo2_angle += 5;
  //        break;
  //      case 'S':
  //      case 's':
  //        if (servo2_angle > servo2_min) servo2_angle -= 5;
  //        break;
  //      case 'A':
  //      case 'a':
  //        if (servo1_angle > servo1_min) servo1_angle -= 5;
  //        break;
  //      case 'D':
  //      case 'd':
  //        if (servo1_angle < servo1_max) servo1_angle += 5;
  //        break;
  //      case 'I':
  //      case 'i':
  //        if (servo3_angle < servo3_max) servo3_angle += 5;
  //        break;
  //      case 'K':
  //      case 'k':
  //        if (servo3_angle > servo3_min) servo3_angle -= 5;
  //        break;
  //      case 'J':
  //      case 'j':
  //        if (servo5_angle > servo5_min) servo5_angle -= 5;
  //        break;
  //      case 'L':
  //      case 'l':
  //        if (servo5_angle < servo5_max) servo5_angle += 5;
  //        break;
  //      case 'U':
  //      case 'u':
  //        if (servo4_angle > servo4_min) servo4_angle -= 5;
  //        break;
  //      case 'O':
  //      case 'o':
  //        if (servo4_angle < servo4_max) servo4_angle += 5;
  //        break;
  //      case 'C':
  //      case 'c':
  //        servo6_angle = servo6_max; // Close gripper
  //        break;
  //      case 'V':
  //      case 'v':
  //        servo6_angle = servo6_min; // Open gripper
  //        break;
  //    }
//  ---------------------------------------- Manual Control Uncomment this ---------------------------------------------
  if (Serial.available() > 0) {
    // Read the input as a string and convert it to an integer
    inputValue = Serial.parseInt();

    // Validate the input to ensure it's between 1 and 10
    if (inputValue >= 1 && inputValue <= 10) {
      // Map the input range [1, 10] to the output range [-100, 100]
      int outputValue = map(inputValue, 1, 10, -100, 100);

      // Print the input and corresponding output values
      inver_kin(outputValue);
    }

  }



    //    for (int i = -100; i <= 100; i++) {
    //      servo2_angle = (1600 + (0.8 * abs(i)));
    //      int aa = map(i, -100, 100, -250, 250);
    //      servo3_angle = 1870 + aa;
    //      int bb = map(i, -100, 100, -280, 280);
    //      servo4_angle = 1500 - bb;
    //      Serial.println(i);  // Print the current value of i
    //      pwm.setPWM(SERVO_1, 0, int(float(servo1_angle) / 1000000 * SERVO_FREQ * 4096));
    //      pwm.setPWM(SERVO_2, 0, int(float(servo2_angle) / 1000000 * SERVO_FREQ * 4096));
    //      pwm.setPWM(SERVO_3, 0, int(float(servo3_angle) / 1000000 * SERVO_FREQ * 4096));
    //      pwm.setPWM(SERVO_4, 0, int(float(servo4_angle) / 1000000 * SERVO_FREQ * 4096));
    //      delay(10);         // Optional: Add a delay of 100 milliseconds between prints
    //    }
    //    for (int i = 100; i >= -100; i--) {
    //      servo2_angle = (1600 + (0.8 * abs(i)));
    //      int aa = map(i, -100, 100, -250, 250);
    //      servo3_angle = 1870 + aa;
    //      int bb = map(i, -100, 100, -280, 280);
    //      servo4_angle = 1400 - bb;
    //      Serial.println(i);  // Print the current value of i
    //      pwm.setPWM(SERVO_1, 0, int(float(servo1_angle) / 1000000 * SERVO_FREQ * 4096));
    //      pwm.setPWM(SERVO_2, 0, int(float(servo2_angle) / 1000000 * SERVO_FREQ * 4096));
    //      pwm.setPWM(SERVO_3, 0, int(float(servo3_angle) / 1000000 * SERVO_FREQ * 4096));
    //      pwm.setPWM(SERVO_4, 0, int(float(servo4_angle) / 1000000 * SERVO_FREQ * 4096));
    //      delay(10);         // Optional: Add a delay of 100 milliseconds between prints
    //    }
    //    // Update servos based on manual input
    //  pwm.setPWM(SERVO_1, 0, int(float(servo1_angle) / 1000000 * SERVO_FREQ * 4096));
    //  pwm.setPWM(SERVO_2, 0, int(float(servo2_angle) / 1000000 * SERVO_FREQ * 4096));
    //  pwm.setPWM(SERVO_3, 0, int(float(servo3_angle) / 1000000 * SERVO_FREQ * 4096));
    //  pwm.setPWM(SERVO_4, 0, int(float(servo4_angle) / 1000000 * SERVO_FREQ * 4096));
    //  pwm.setPWM(SERVO_5, 0, int(float(servo5_angle) / 1000000 * SERVO_FREQ * 4096));
    //  pwm.setPWM(SERVO_6, 0, int(float(servo6_angle) / 1000000 * SERVO_FREQ * 4096));
    //
    //  if (debug) {
    Serial.print("1: ");
    Serial.print(servo1_angle);
    Serial.print("\t2: ");
    Serial.print(servo2_angle);
    Serial.print("\t3: ");
    Serial.print(servo3_angle);
    Serial.print("\t4: ");
    Serial.print(servo4_angle);
    //    Serial.print("\t5: ");
    //    Serial.print(servo5_angle);
    //    Serial.print("\t6: ");
    //    Serial.print(servo6_angle);
    Serial.println();
  }
  //}
  //}

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
