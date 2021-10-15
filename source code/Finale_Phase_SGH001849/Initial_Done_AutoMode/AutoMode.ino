#include <SoftwareSerial.h> //software serial library for serial communication b/w arduino & GSM

SoftwareSerial mySerial(6, 7);//connect Tx pin of GSM to pin 6 of arduino && Rx pin of GSM to pin no 7 of arduino


int led = 8;
String message;
int viru=0;
int relay=13;
int automode=0;


const int trigPin = 3;
const int echoPin = 2;
// defining variables.
long duration;
int distance;

const int trigPin2 = 5;
const int echoPin2 = 4;
// defining variables
long duration2;
int distance2;
//trig,echo 3,2 =overhead tank
//trig,echo 5,4 =undergrund tank
int flag=0;

void setup()

{  Serial.println("welcome");

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input     
  mySerial.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module 
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  

  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)

  delay(100);




  mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS

  delay(1000);

  Serial.println("gsm is ready to recieve msg on/off");

  pinMode(led,OUTPUT);
pinMode(relay,OUTPUT);
  digitalWrite(led,LOW);

    char remoteNum[20]="+917878928928";  // telephone number to send sms

  Serial.println("waiting for msg");
  
}




void loop()

{
        
        digitalWrite(relay,1);
      char remoteNum[20]="+919712128444";  // telephone number to send sms


  if (mySerial.available()>0){

  message = mySerial.readString();

  }

    if(message.indexOf("AUTO") > -1)
    {
      automode=1;
      Serial.println("Auto Mode");
    }
  
    if(automode==1)
    {
      
  
  if(viru==1)
  {
    digitalWrite(led,0);
  }
  
      
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance= duration*0.034/(2);
  int b=map(distance,2,26,100,0);
  // Prints the distance on the Serial Monitor
  Serial.print("Distance in first ultrasonic in percentage: ");
  Serial.println(b);
  delay(200);
  
  
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration2 = pulseIn(echoPin2, HIGH);
  // Calculating the distance
  distance2= (duration2)*0.034/(2);
  int c=map(distance2,2,26,100,0);
  // Prints the distance on the Serial Monitor
  Serial.print("Distance in second ultrasonic in percentage: ");
  Serial.println(c);
  delay(200);
  
    
  
  if((b)<10 && (c)>30)
  {
   viru=1;
  
        Serial.println("Pump is ON");
  
       digitalWrite(led,1);
  
       Serial.println("viru=1"); 
  
       mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  
       delay(1000);  // Delay of 1 second
  
       mySerial.println("AT+CMGS=\"+919712128444\"\r"); // Replace x with mobile number
  
       delay(1000);
  
       mySerial.println("Pump is turned on trough AUTO Mode");// The SMS text you want to send
  
       Serial.println("text is sended by viru 1");
  
       delay(100);
  }
    }
  
}
