  
#include <SoftwareSerial.h> //software serial library for serial communication b/w arduino & GSM

SoftwareSerial mySerial(13, 7);//connect Tx pin of GSM to pin 6 of arduino && Rx pin of GSM to pin no 7 of arduino

const int sensor_pin = A0;  /* Soil moisture sensor O/P pin */
int led = 8;
String message;
int viru=0;
int relay=12;
int buzzer=1;
int light=2;

const int trigPin = 3;
const int echoPin = 4;
// defining variables.
long duration;
int distance;

const int trigPin2 = 6;
const int echoPin2 = 5;
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
        float moisture_percentage;
  int sensor_analog;
        digitalWrite(relay,1);
        digitalWrite(light,1);
     // char remoteNum[20]="+919712128444";  // telephone number to send sms


  if (mySerial.available()>0){

  message = mySerial.readString();

  }

 if(message.indexOf("ON") > -1){

    viru=1;

      Serial.println("LED ON");

     digitalWrite(led,1);

     Serial.println("viru=1");
     Serial.print("flag=");
      Serial.println(flag);

     

     }

    else if(message.indexOf("OFF") > -1){

       viru=0;

      Serial.println("LED OFF");

      digitalWrite(led,0);

      Serial.println("viru=0");
      Serial.print("flag=");
      Serial.println(flag);
     }

    
       
      else if(message.indexOf("INFO") > -1)

  {  
    

    if(viru==1)

     {

      mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode

     delay(1000);  // Delay of 1 second

     mySerial.println("AT+CMGS=\"+919712128444\"\r"); // Replace x with mobile number

     delay(1000);

     mySerial.println("your power is on");// The SMS text you want to send
     mySerial.println("\n");// The SMS text you want to send

     Serial.println("text is sended by viru 1");
     // digitalWrite(buzzer,1);
     delay(100);

     
      delay(1000);

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
      int b=map(distance,0,28,100,1);
       //mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode

     delay(1000);  // Delay of 1 second

     //mySerial.println("AT+CMGS=\"+919712128444\"\r"); // Replace x with mobile number

     //delay(1000);
      mySerial.print("\n");// The SMS text you want to send
      mySerial.print("Water level in overheadtank in percentage: ");// The SMS text you want to send
      mySerial.println(b);
      //digitalWrite(buzzer,1);
      //Serial.println("text is sended viru=0");

     delay(100);

//     mySerial.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module 

      delay(1000);
      // Prints the distance on the Serial Monitor
      Serial.print("Water level in percentage in forheadtank: ");
      Serial.println(b);
     
      Serial.println("Water level in first tank is sended to by GSM");
      delay(200);
      


      //  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode

     delay(1000);  // Delay of 1 second

    // mySerial.println("AT+CMGS=\"+919712128444\"\r"); // Replace x with mobile number

     //delay(1000);
      digitalWrite(trigPin2, LOW);
      delayMicroseconds(2);
      // Sets the trigPin on HIGH state for 10 micro seconds
      digitalWrite(trigPin2, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin2, LOW);
      // Reads the echoPin, returns the sound wave travel time in microseconds
      duration2 = pulseIn(echoPin2, HIGH);
      //   Calculating the distance
      distance2= (duration2)*0.034/(2);
      // Prints the distance on the Serial Monitor
      Serial.print("Distance in inch in second tank: ");
      Serial.println(distance2);
      int c=map(distance2,0,28,100,1);
     // mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode

     delay(1000);  // Delay of 1 second

    // mySerial.println("AT+CMGS=\"+919712128444\"\r"); // Replace x with mobile number

     delay(1000);
     mySerial.print("\n");// The SMS text you want to send
      mySerial.print("Water level in 2nd tank in is underground tank");// The SMS text you want to send
       mySerial.println(c);// The SMS text you want to send
      delay(100);
      mySerial.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module 
      delay(1000);
      Serial.println("Water level in second tank is sended to by GSM");
      delay(200);
      digitalWrite(buzzer,1);
      delay(1000);
      digitalWrite(buzzer,0);
      delay(1000);
     }


     if(viru==0)

     {

      mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode

     delay(1000);  // Delay of 1 second

     mySerial.println("AT+CMGS=\"+919712128444\"\r"); // Replace x with mobile number

     delay(1000);

      mySerial.println("your power is off");// The SMS text you want to send

      Serial.println("text is sended viru=0");

     delay(100);

    // mySerial.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module 

      delay(1000);

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
       //mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode

     delay(1000);  // Delay of 1 second

     //mySerial.println("AT+CMGS=\"+919712128444\"\r"); // Replace x with mobile number

     //delay(1000);
      int b=map(distance,0,28,100,1);
      mySerial.println("\n");
      mySerial.println("Water level in forhead tank:  ");// The SMS text you want to send
      mySerial.println(b);
      mySerial.println(" %");
      mySerial.println("\n");

      //Serial.println("text is sended viru=0");

     delay(100);

     //mySerial.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module 

      delay(1000);
      // Prints the distance on the Serial Monitor
      Serial.print("Water level in percentage in forheadtank: ");
      Serial.println(b);
     
      Serial.println("Water level in first tank is sended to by GSM");
      delay(200);
      


      //  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode

     delay(1000);  // Delay of 1 second

    // mySerial.println("AT+CMGS=\"+919712128444\"\r"); // Replace x with mobile number

     //delay(1000);
      digitalWrite(trigPin2, LOW);
      delayMicroseconds(2);
      // Sets the trigPin on HIGH state for 10 micro seconds
      digitalWrite(trigPin2, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin2, LOW);
      // Reads the echoPin, returns the sound wave travel time in microseconds
      duration2 = pulseIn(echoPin2, HIGH);
      //   Calculating the distance
      distance2= (duration2)*0.034/(2);
      int c=map(distance2,0,28,100,1);
      // Prints the distance on the Serial Monitor
      Serial.print("Distance in inch in second tank: ");
      Serial.println(c);
      
      //mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode

     delay(1000);  // Delay of 1 second

     //mySerial.println("AT+CMGS=\"+919712128444\"\r"); // Replace x with mobile number

     delay(1000);
      mySerial.println("Water level in bottom tank:  ");// The SMS text you want to send
      
       mySerial.print(c);// The SMS text you want to send
       mySerial.print("%");
      delay(100);
      mySerial.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module 
      delay(1000);
      digitalWrite(buzzer,1);
      delay(1000);
      digitalWrite(buzzer,0);
      //Serial.println("Water level in second tank is sended to by GSM");
      delay(200);

     }

 

 delay(10);
  
  }
  else if(message.indexOf("ONTIMER")>-1)
  {delay(10000);
    if(message.indexOf("30")>-1)
    {
      digitalWrite(led,HIGH);
      delay(180000);
      digitalWrite(led,LOW);
    }
    else if(message.indexOf("60")>-1)
    {
      digitalWrite(led,HIGH);
      delay(360000);
      digitalWrite(led,LOW);
    }
    else if(message.indexOf("01")>-1)
    {
      digitalWrite(led,HIGH);
      delay(60000);
      digitalWrite(led,LOW);
    }
    else if(message.indexOf("90)>-1)
    {
      digitalWrite(led,HIGH);
      delay(540000);
      digitalWrite(led,LOW);
    }
   else if(message.indexOf("120")>-1)
    {
      digitalWrite(led,HIGH);
      delay(720000);
      digitalWrite(led,LOW);
    }
    else if(message.indexOf("150")>-1)
    {
      digitalWrite(led,HIGH);
      delay(900000);
      digitalWrite(led,LOW);
    }
    else if(message.indexOf("180")>-1)
    {
      digitalWrite(led,HIGH);
      delay(1080000);
      digitalWrite(led,LOW);
    }
  }

else if(message.indexOf("HUMIDITY") > -1){
mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode

     delay(1000);  // Delay of 1 second

     mySerial.println("AT+CMGS=\"+919712128444\"\r"); // Replace x with mobile number

     delay(1000);
//Serial.println("Message received of humidity....");
      sensor_analog = analogRead(sensor_pin);
  moisture_percentage = ( 100 - ( (sensor_analog/1023.00) * 100 ) );
  Serial.print("Moisture Percentage = ");
  Serial.print(moisture_percentage);
  Serial.print("%\n\n");
  
  //mySerial.print("Humadity in sensor:  ");// The SMS text you want to send
//mySerial.println(moisture_percentage);
if(moisture_percentage<65)
      {
        mySerial.print("You should ON your water pump");
        
      }
      else if(moisture_percentage>=65&&moisture_percentage<=75)
      {
        mySerial.print("You should ON your water pump after 1 day");
       
        delay(86400000);
        digitalWrite(led,1);
        delay(3600000);
        digitalWrite(led,0);
        
      }
      else if(moisture_percentage>75&&moisture_percentage<=85)
      {
        mySerial.print("You should ON your water pump after 2 day");
        
        delay(172800000);
        digitalWrite(led,1);
        delay(3600000);
        digitalWrite(led,0);
      }
      else
      {
        mySerial.print("You don't need to turn ON your pump");   
           
      }
  delay(100);
      mySerial.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module 
      digitalWrite(buzzer,1);
      delay(1000);
      digitalWrite(buzzer,0);
      Serial.println("Humidity is sent through gsm");
  delay(1000); 
     }
}
