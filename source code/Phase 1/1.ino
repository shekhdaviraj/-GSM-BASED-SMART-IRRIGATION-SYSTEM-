#include <SoftwareSerial.h> //software serial library for serial communication b/w arduino & GSM

SoftwareSerial mySerial(6, 7);//connect Tx pin of GSM to pin 6 of arduino && Rx pin of GSM to pin no 7 of arduino

//water pump  at pin no 8, Vcc of relay at 13
int led = 8;
String message;
int viru=0;

int relay=13;


void setup()

{  Serial.println("welcome");
    
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

 

  if(message.indexOf("ON") > -1){

    viru=1;

      Serial.println("Pump is  ON");

     digitalWrite(led,1);

     Serial.println("viru=1");

     

     }

    else if(message.indexOf("OFF") > -1){

       viru=0;

      Serial.println("Pump is OFF");

      digitalWrite(led,0);

      Serial.println("viru=0");

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

     

     }


 delay(10);
  }
 
}
