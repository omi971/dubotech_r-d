// Dubotech External Motor Move

// L1
int in1 = 2;
int in2 = 3;

//L2
int in3 = 4;
int in4 = 5;

//R1
int in5 = 6;
int in6 = 7;

//R2
int in7 = 8;
int in8 = 9;

int t_delay = 10;

void setup() {
  // put your setup code here, to run once:
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    char command = Serial.read();
  
    switch (command) {
//  ---------------------- Left Motor Forward ----------------------
      case 'W':
      case 'w':
        Serial.println("Forward");
        digitalWrite(in1,HIGH);
        digitalWrite(in2,LOW);
        delay(t_delay);
        break;
        
//  ---------------------- Left Motor Backward----------------------
      case 'S':
      case 's':
        Serial.println("backward");
        digitalWrite(in1,LOW);
        digitalWrite(in2,HIGH);
        delay(t_delay);
        break;

//  ---------------------- Right Motor Forward ----------------------
      case 'A':
      case 'a':
        Serial.println("Right Motor Forward");
        digitalWrite(in3,LOW);
        digitalWrite(in4,HIGH);
        delay(t_delay);
        break;

//  ---------------------- Right Motor Backward ----------------------
      case 'd':
      case 'D':
        Serial.println("Right Motor Backward");
        digitalWrite(in3,HIGH);
        digitalWrite(in4,LOW);
        delay(t_delay);
        break;


//  ---------------------- Stop ----------------------
      case 'x':
      case 'X':
        Serial.println("Stop");
        digitalWrite(in1,HIGH);
        digitalWrite(in2,HIGH);
        
        digitalWrite(in3,HIGH);
        digitalWrite(in4,HIGH);
        delay(t_delay);
        break;
    }
  }
}
