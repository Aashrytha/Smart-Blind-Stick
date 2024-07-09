#define tr1 5
#define ec1 4
#define tr2 9  
#define ec2 8
int but=11;
int buz=13;
#include <TinyGPS.h>
TinyGPS gps;
float flat=0, flon=0;
void read_gps()
{
    bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (Serial.available())
    {
      char c = Serial.read();
      if (gps.encode(c)) 
        newData = true;
    }
  }

  if (newData)
  {

    unsigned long age;
    gps.f_get_position(&flat,&flon,&age);

  }
}
void setup() {
  pinMode(but,INPUT_PULLUP);
  pinMode(buz,OUTPUT);
  Serial.begin(9600); 
  pinMode(ec1,INPUT);
  pinMode(ec2,INPUT);
  pinMode(tr1,OUTPUT);
  pinMode(tr2,OUTPUT);
  Serial.begin(9600);
 Serial.println("AT");
 delay(1500);
Serial.println("AT+CMGF=1");

}

void loop() {
 int bval=digitalRead(but);
digitalWrite(tr1,1);
delay(0.001);
digitalWrite(tr1,0);
int dst1=pulseIn(ec1,1)/58.2;
digitalWrite(tr2,1);
delay(0.001);
digitalWrite(tr2,0);
int dst2=pulseIn(ec2,1)/58.2;
Serial.println("D1:");
Serial.println(dst1);
Serial.println("D2:");
Serial.println(dst2);
delay(1000);
if((dst1<20||dst2<20))
  {
    digitalWrite(buz,1);
    delay(500);
    digitalWrite(buz,0);
     
  }
 else
 {
   digitalWrite(buz,0);
 }
 if(bval==0)
    {  
      //read_gps();    
       send_sms(1);
   }
}
 void send_sms(int sts)
{ 
  //read_gps();
Serial.println("Sending SMS...");
Serial.println("AT");    
delay(1000);  
Serial.println("ATE0");    
delay(1000);  
Serial.println("AT+CMGF=1");    
delay(1000);  
Serial.print("AT+CMGS=\"8121054656\"\r\n");// Replace x with mobile number
delay(1000);
if(sts==1)
Serial.println("MR X needs your help find him ASAP");
Serial.println("https://www.google.com/maps/search/?api=1&query=" + String(16.4963)+ "," + String(80.5007));
delay(100);
Serial.println((char)26);// ASCII code of CTRL+Z
delay(6000);
Serial.println("AT");    
delay(1000);  
Serial.println("ATE0");    
delay(1000);  
Serial.println("AT+CMGF=1");    
delay(1000);  
Serial.print("AT+CMGS=\"8121054656\"\r\n");// Replace x with mobile number
delay(1000);
if(sts==1)
Serial.println("MR X needs your help find him ASAP: ");
Serial.println("https://www.google.com/maps/search/?api=1&query=" + String(16.4963)+ "," + String(80.5007));
delay(100);
Serial.println((char)26);// ASCII code of CTRL+Z
delay(2000);
  }
