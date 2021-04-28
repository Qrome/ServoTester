/** The MIT License (MIT)

Copyright (c) 2021 David Payne

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <Servo.h>

#define BUTTON_PIN 2   
#define SERVO_PIN8 8
#define SERVO_PIN9 9
#define SERVO_PIN10 10

const int center = 90; //90 is center (0-179)
int pos = center;

Servo servo_8;
Servo servo_9;
Servo servo_10;

const int stepValue = 5;
int direct = 1;


/**** SETUP ****/
void setup()
{
  pinMode(13, OUTPUT);  // LED
  servo_8.attach(SERVO_PIN8);
  servo_9.attach(SERVO_PIN9);
  servo_10.attach(SERVO_PIN10);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  Serial.begin(9600);
  Serial.println("Servo Center & Tester");
  digitalWrite(13, HIGH);
  centerServos();
  delay(500);
  digitalWrite(13, LOW);
}

/**** LOOP ****/
void loop()
{
  if (digitalRead(BUTTON_PIN) == HIGH) {
    if (pos >= 179 || pos <= 0) {
      direct = direct * -1;
    }
    pos = pos + (stepValue * direct);
    digitalWrite(13, HIGH);
    writeToServos(pos);
  } else if (pos != center) {
    digitalWrite(13, LOW);
    centerServos();
  }
}

void centerServos() {
  pos = center;
  writeToServos(pos);
  Serial.println("Servo(s) Centered!");
}

void writeToServos(int pos) {
  servo_8.write(pos);
  servo_9.write(pos);
  servo_10.write(pos);
  
  double pwmValue = map(pos, 0, 179, 1000, 2000);
  Serial.println("PWM Value: " + String(pwmValue));
  delay(30);
}
