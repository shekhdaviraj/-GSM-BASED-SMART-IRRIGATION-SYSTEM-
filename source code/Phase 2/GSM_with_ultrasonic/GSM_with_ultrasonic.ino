#include <SoftwareSerial.h> //software serial library for serial communication b/w arduino & GSM
SoftwareSerial mySerial(8, 9);//connect Tx pin of GSM to pin 8 of arduino && Rx pin of GSM to pin no 9 of arduino


int led = 13;
String message;
int flag=0;
int trig = 12;
int echo = 11;

void setup() {
  
Serial.println("welcome");

  mySerial.begin(9600);   // Setting the baud rate of GSM Module  

  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)

  delay(100);




  mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS

  delay(1000);

  Serial.println("gsm is ready to recieve msg on/off");

  pinMode(led,OUTPUT);

  digitalWrite(led,LOW);

    char remoteNum[20]="+919712128444";  // telephone number to send sms

    //char txtMsg[20]="LED IS ON";

  

  Serial.println("waiting for msg");


  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT); 
}




void loop() {
   char remoteNum[20]="+919712128444";  // telephone number to send sms

     // char txtMsg[20]="LED IS ON";

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
  
  

  if (mySerial.available()>0){

  message = mySerial.readString();

  }




  if(message.indexOf("ON") > -1){

    flag=1;

      Serial.println("LED ON");

     digitalWrite(led,1);

     Serial.println("flag=1");

     

     }

    else if(message.indexOf("OFF") > -1){

       flag=0;

      Serial.println("LED OFF");

      digitalWrite(led,0);

      Serial.println("flag=0");

     }

  else if(message.indexOf("info") > -1)

  {  

    if(flag==1)

     {

      mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode

     delay(1000);  // Delay of 1 second

     mySerial.println("AT+CMGS=\"+919712128444\"\r"); // Replace x with mobile number

     delay(1000);

     mySerial.println("your power is on");// The SMS text you want to send

     Serial.println("text is sended by viru 1");

     delay(100);

     mySerial.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module 

      delay(1000);

     }

     else if(message.indexOf("waterlevel") > -1)

  {  

    

      mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode

     delay(1000);  // Delay of 1 second

     mySerial.println("AT+CMGS=\"+919712128444\"\r"); // Replace x with mobile number

     delay(1000);

     mySerial.print("Current water level is ");// The SMS text you want to send
     mySerial.print(hp);

     Serial.println("water level is sended");

     delay(100);

     mySerial.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module 

      delay(1000);

     
  }

     else

     {

      mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode

     delay(1000);  // Delay of 1 second

     mySerial.println("AT+CMGS=\"+919712128444\"\r"); // Replace x with mobile number

     delay(1000);

      mySerial.println("your power is off");// The SMS text you want to send

      Serial.println("text is sended flag=0");

     delay(100);

     mySerial.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module 

      delay(1000);

     }
 }
delay(10);
delay(1000);

}
