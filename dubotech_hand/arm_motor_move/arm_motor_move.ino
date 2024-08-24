// Dubotech Chair arm motor test code 

// Left Motor Pin Initial
int in1 = 10;
int in2 = 11;

// Right Motor Pin Initial
int in3 = 12;
int in4 = 13;
int t_delay = 10;

void setup() {
  // put your setup code here, to run once:
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
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
