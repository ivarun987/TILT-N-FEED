#include <SoftwareSerial.h>
//RX TX on Bluetooth module, digital pins
SoftwareSerial  BTSerial(2, 3);
//button digital pin
const int button = 13;
//value returned by button
int val = 0;

//Analog read pins for accelerometer
const int xPin = 0;
const int yPin = 1;
const int zPin = 2;

//Baseline values for accelerometer, we only
//care about the absolute value of the change 
//in acceleration
int xbl, ybl, zbl;

//Thresholds for fishfood shake
int threshold[3] = { 80, 40, 40 };

void setup() {
  BTSerial.begin(9600);
  Serial.begin(9600);
  //Defining button pin as input
  pinMode(button, INPUT);
  int xbla[50], ybla[50], zbla[50];
  for(int i = 0; i < 50; i++) {
    xbla[i] = analogRead(xPin);
    ybla[i] = analogRead(yPin);
    zbla[i] = analogRead(zPin);
  }
  xbl = sum(xbla) / 50;
  ybl = sum(ybla) / 50;
  zbl = sum(zbla) / 50;
}

int sum(int array[]) {
  int sum = 0;
  for (int i = 0; i < sizeof(array); i++) {
    sum = sum + array[i];
  }
  return sum;
}

void loop() {
  //read the analog values from the accelerometer
  int xRead = abs(analogRead(xPin) - xbl);
  int yRead = abs(analogRead(yPin) - ybl);
  int zRead = abs(analogRead(zPin) - zbl);

  //read the value from the button, 
  //whether it is pressed or not
  val = digitalRead(button);

  Serial.println(val);

  //Check if button is pressed and the controller is shaked
  if(val == HIGH && (xRead > threshold[0] || 
  yRead > threshold[1] || zRead > threshold[2])) {
    BTSerial.println("H");
  }
  delay(2000);
}
