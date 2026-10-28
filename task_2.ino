
#include <Servo.h>

Servo panServo;
Servo tiltServo;

// LDR connections
const int TL = A0;
const int TR = A1;
const int BL = A2;
const int BR = A3;

// Servo connections
const int PAN_PIN = 10;
const int TILT_PIN = 9;

int pan = 90;
int tilt = 90;

const int deadZone = 35;
const int minLight = 80;
const int minAngle = 10;
const int maxAngle = 170;

int readLight(int pin) {
  long total = 0;

  for (int i = 0; i < 5; i++) {
    total += analogRead(pin);
    delay(2);
  }

  return total / 5;
}

void setup() {
  Serial.begin(9600);

  panServo.attach(PAN_PIN);
  tiltServo.attach(TILT_PIN);

  panServo.write(pan);
  tiltServo.write(tilt);
}

void loop() {
  // Read and average each sensor
  int tl = readLight(TL);
  int tr = readLight(TR);
  int bl = readLight(BL);
  int br = readLight(BR);

  // Compare the four sides
  int leftLight = (tl + bl) / 2;
  int rightLight = (tr + br) / 2;
  int topLight = (tl + tr) / 2;
  int bottomLight = (bl + br) / 2;

  int totalLight = (tl + tr + bl + br) / 4;

  int oldPan = pan;
  int oldTilt = tilt;

  String status = "LOCKED";

  // Avoid tracking when it is too dark
  if (totalLight < minLight) {
    status = "DARK";
  } else {
    int horizontalError = leftLight - rightLight;
    int verticalError = topLight - bottomLight;

    // Horizontal correction
    if (horizontalError > deadZone) {
      pan--;
    } else if (horizontalError < -deadZone) {
      pan++;
    }

    // Vertical correction
    if (verticalError > deadZone) {
      tilt++;
    } else if (verticalError < -deadZone) {
      tilt--;
    }

    pan = constrain(pan, minAngle, maxAngle);
    tilt = constrain(tilt, minAngle, maxAngle);

    if (pan != oldPan || tilt != oldTilt) {
      status = "TRACKING";
    }
  }

  // Send commands only when a target angle changes
  if (pan != oldPan) {
    panServo.write(pan);
  }

  if (tilt != oldTilt) {
    tiltServo.write(tilt);
  }

  // Display sensor readings and status
  Serial.print("TL:");
  Serial.print(tl);
  Serial.print(" TR:");
  Serial.print(tr);
  Serial.print(" BL:");
  Serial.print(bl);
  Serial.print(" BR:");
  Serial.print(br);

  Serial.print(" | Top:");
  Serial.print(topLight);
  Serial.print(" Bottom:");
  Serial.print(bottomLight);
  Serial.print(" Left:");
  Serial.print(leftLight);
  Serial.print(" Right:");
  Serial.print(rightLight);

  Serial.print(" | Pan:");
  Serial.print(pan);
  Serial.print(" Tilt:");
  Serial.print(tilt);
  Serial.print(" | Status: ");
  Serial.println(status);

  delay(100);
}
