/* Water Level Meter

Measuring water level with ultrasonic sensor HR S04.

Hackathon 2020
*/

int trig = 12;
int echo = 11;

void setup()
{
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT); 
}

void loop()
{
  long t = 0, h = 0, hp = 0;
  
  // Transmitting pulse
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  
  // Waiting for pulse
  t = pulseIn(echo, HIGH);
  
  // Calculating distance 
  h = t / 58;
 
  h = h - 6;  // offset correction
  h = 50 - h;  // water height, 0 - 50 cm
  
  hp = 2 * h;  // distance in %, 0-100 %
  
  // Sending to computer
  Serial.print(hp);
  // Serial.print(" cm\n");
  Serial.print("\n");
  
  delay(1000);
}
