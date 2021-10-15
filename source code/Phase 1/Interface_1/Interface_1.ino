
#include <SoftwareSerial.h> //software serial library for serial communication b/w arduino & GSM

SoftwareSerial mySerial(8, 9);//connect Tx pin of GSM to pin 8 of arduino && Rx pin of GSM to pin no 9 of arduino


int led = 13;
String message;
int viru=0;

const int trigPin = 10;
const int echoPin = 11;
// defining variables
long duration;
int distance;

const int trigPin2 = 5;
const int echoPin2 = 6;
// defining variables
long duration2;
int distance2;

int flag=0;

void setup()

{  Serial.println("welcome");

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

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

}




void loop()

{

      char remoteNum[20]="+919712128444";  // telephone number to send sms

     // char txtMsg[20]="LED IS ON";

   

  if (mySerial.available()>0){

  message = mySerial.readString();

  }




  if(message.indexOf("ON") > -1){

    viru=1;

      Serial.println("LED ON");

     digitalWrite(led,1);

     Serial.println("viru=1");

     

     }

    else if(message.indexOf("OFF") > -1){

       viru=0;

      Serial.println("LED OFF");

      digitalWrite(led,0);

      Serial.println("viru=0");

     }

     else if(message.indexOf("watrelevel") > -1){
      flag=1;
     }

       
      else if(message.indexOf("info") > -1)

  {  

    if(viru==1)

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


     else

     {

      mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode

     delay(1000);  // Delay of 1 second

     mySerial.println("AT+CMGS=\"+919712128444\"\r"); // Replace x with mobile number

     delay(1000);

      mySerial.println("your power is off");// The SMS text you want to send

      Serial.println("text is sended viru=0");

     delay(100);

     mySerial.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module 

      delay(1000);

     }


     if(flag==1)
       {
      Serial.println("Water level command...");

      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      // Sets the trigPin on HIGH state for 10 micro seconds
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      // Reads the echoPin, returns the sound wave travel time in microseconds
      duration = pulseIn(echoPin, HIGH);
      //   Calculating the distance
      distance= duration*0.034/(2);
      // Prints the distance on the Serial Monitor
      Serial.print("Distance in inch in first tank: ");
      Serial.println(distance);
      mySerial.print("Water level in 1st tank is: ");// The SMS text you want to send
      mySerial.println(distance);// The SMS text you want to send
      delay(100);
      mySerial.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module 
      delay(1000);
      Serial.println("Water level in first tank is sended to by GSM");
      delay(200);
      

      digitalWrite(trigPin2, LOW);
      delayMicroseconds(2);
      // Sets the trigPin on HIGH state for 10 micro seconds
      digitalWrite(trigPin2, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin2, LOW);
      // Reads the echoPin, returns the sound wave travel time in microseconds
      duration2 = pulseIn(echoPin2, HIGH);
      //   Calculating the distance
      distance2= duration2*0.034/(2);
      // Prints the distance on the Serial Monitor
      Serial.print("Distance in inch in second tank: ");
      Serial.println(distance2);
      mySerial.print("Water level in 2nd tank is ");// The SMS text you want to send
       mySerial.println(distance2);// The SMS text you want to send
      delay(100);
      mySerial.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module 
      delay(1000);
      Serial.println("Water level in second tank is sended to by GSM");
      delay(200);

      flag=0;
      Serial.print("Value of flag=");
      Serial.println(flag);
     }

 delay(10);
  }
}
