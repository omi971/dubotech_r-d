// Sharp Sensor Test code
// Sharp IR GP2Y0A41SK0F (4-30cm, analog)

#define l1_sharp A0
#define r1_sharp A1
#define l2_sharp A2 // Ektu Problem ase maybe sensor or wiring ee
#define r2_sharp A3

void measureDistance(float volt=0){  
  int distance = 13*pow(volt, -1); // worked out from datasheet graph
  
  if (distance <= 30){
    Serial.println(distance);   // print the distance
  }
  else {
    Serial.println("Distance is out of range...!!!");
  }
}

void setup() {
  Serial.begin(9600); // start the serial port
}

void loop() {  

//  ------------ Measure L1 Sharp Distance ------------------
  float volt = analogRead(l1_sharp)*0.0048828125;  // value from sensor * (5/1024)
  Serial.print("L1 Motor Distance: ");
  measureDistance(volt);
//  delay(500); // slow down serial port 

//  ------------ Measure L2 Sharp Distance ------------------
  volt = analogRead(l2_sharp)*0.0048828125;  // value from sensor * (5/1024)
  Serial.print("L2 Motor Distance: ");
  measureDistance(volt);
//  delay(500); // slow down serial port 

//  ------------ Measure R1 Sharp Distance ------------------
  volt = analogRead(r1_sharp)*0.0048828125;  // value from sensor * (5/1024)
  Serial.print("R1 Motor Distance: ");
  measureDistance(volt);
//  delay(500); // slow down serial port 

//  ------------ Measure R2 Sharp Distance ------------------
  volt = analogRead(r2_sharp)*0.0048828125;  // value from sensor * (5/1024)
  Serial.print("R2 Motor Distance: ");
  measureDistance(volt);

  
  delay(500); // slow down serial port 
}
