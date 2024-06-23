struct Motors {
    int enablePin;
    int clockwisePin;
    int antiClockwisePin;
};

Motors rightMotor = {5, 7, 4};
Motors leftMotor = {6, 8, 12};
int sensorPins[] = {A0, A1, A2, A3, A4};
int count = 0;
bool atjunc=false;
int sensorValues[5];

void setup() {
  Serial.begin(9600);
    pinMode(rightMotor.enablePin, OUTPUT);
    pinMode(leftMotor.enablePin, OUTPUT);
    pinMode(rightMotor.clockwisePin, OUTPUT);
    pinMode(leftMotor.clockwisePin, OUTPUT);
    pinMode(rightMotor.antiClockwisePin, OUTPUT);
    pinMode(leftMotor.antiClockwisePin, OUTPUT);

    for (int i = 0; i < 5; i++) {
        pinMode(sensorPins[i], INPUT);
    }
}

void moveMotors(int speed) {
    analogWrite(rightMotor.enablePin, speed);
    analogWrite(leftMotor.enablePin, speed);
}

void stopMotors() {
    digitalWrite(rightMotor.clockwisePin, LOW);
    digitalWrite(rightMotor.antiClockwisePin, LOW);
    digitalWrite(leftMotor.clockwisePin, LOW);
    digitalWrite(leftMotor.antiClockwisePin, LOW);
}

void moveLeftFast() {
    digitalWrite(rightMotor.clockwisePin, HIGH);
    digitalWrite(leftMotor.clockwisePin, LOW);
    digitalWrite(rightMotor.antiClockwisePin, LOW);
    digitalWrite(leftMotor.antiClockwisePin, HIGH);
}

void moveRightFast() {
    digitalWrite(rightMotor.clockwisePin, LOW);
    digitalWrite(leftMotor.clockwisePin, HIGH);
    digitalWrite(rightMotor.antiClockwisePin, HIGH);
    digitalWrite(leftMotor.antiClockwisePin, LOW);
}

void moveRight() {
    digitalWrite(rightMotor.clockwisePin, LOW);
    digitalWrite(leftMotor.clockwisePin, HIGH);
    digitalWrite(rightMotor.antiClockwisePin, LOW);
    digitalWrite(leftMotor.antiClockwisePin, LOW);
}

void moveLeft() {
    digitalWrite(rightMotor.clockwisePin, HIGH);
    digitalWrite(leftMotor.clockwisePin, LOW);
    digitalWrite(rightMotor.antiClockwisePin, LOW);
    digitalWrite(leftMotor.antiClockwisePin, LOW);
}

void moveMiddle() {
    digitalWrite(rightMotor.clockwisePin, HIGH);
    digitalWrite(leftMotor.clockwisePin, HIGH);
    digitalWrite(rightMotor.antiClockwisePin, LOW);
    digitalWrite(leftMotor.antiClockwisePin, LOW);
}

void loop() {
    
    while(1){
    getSensor();
      if(sensorValues[1]==1 && sensorValues[3]==1){
        moveMotors(120);
        moveMiddle();
        }
      else if(sensorValues[1]==0 && sensorValues[3]==1){
        moveMotors(60);
        moveRight();

      }
      else if(sensorValues[1]==1 && sensorValues[3]==0){
        moveMotors(60);
        moveLeft();
      }

      else if ((sensorValues[0] == 0) && (sensorValues[1] == 0) && (sensorValues[2] == 0) && (sensorValues[3] == 0) && (sensorValues[4] == 0) ) {
        
        while((sensorValues[0] == 0) && (sensorValues[1] == 0) && (sensorValues[2] == 0) && (sensorValues[3] == 0) && (sensorValues[4] == 0)){
          getSensor();
          moveMotors(120);
          moveMiddle(); 
          
        }

        count++;
        Serial.println("Count = ");
        Serial.print(count);
        Serial.println();
        if ((count == 4)) {
            moveMotors(75);
            moveLeftFast();
            delay(500);
            Serial.println("left");
        }
        else if ((count == 7) ) {
            moveMotors(75);
            moveLeftFast();
            delay(500);
            Serial.println("left");
        }   
        else if ((count == 20)) {
            moveMotors(75);
            moveLeftFast();
            delay(510);
            Serial.println("left");
        } 
        else if ((count == 11)) {
            moveMotors(75);
            moveRightFast();
            delay(500);
            Serial.println("Right"); 
        }
        else if ((count == 15)) {
            moveMotors(75);
            moveRightFast();
            delay(500);
            Serial.println("Right"); 
        }
        else if ((count == 19)) {
            moveMotors(75);
            moveRightFast();
            delay(510);
            Serial.println("Right"); 
        }
        else {
            moveMotors(120);
            moveMiddle();
            Serial.println("J"); 
        }
    } 
      else if(sensorValues[0]==0){
        moveMotors(60);
        moveRight();
      }
      else if(sensorValues[0]==0){
        moveMotors(60);
        moveLeft();
      }
      else {
        stopMotors();
    }
    }
  }

void getSensor(){
  for (int i = 0; i < 5; i++) {
      if(analogRead(sensorPins[i]) > 150){
        sensorValues[i] = 1;
      } else {
        sensorValues[i] = 0;
      }
  }
}
