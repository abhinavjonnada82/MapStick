/*
* Arduino Wireless Communication Tutorial
*     Receiver Code

* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
/*
****Pin Config****
D6 -> LED
D7 -> vibMot_Lidar
D8 -> vibMot_US
D9 -> CE
D10 -> CSN
D11 -> MOSI
D12 -> MISO
D13 -> SCK

*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define vibMot_Lidar 7
#define vibMot_US 8
#define led 6

RF24 radio(9, 10); // CE, CSN

const byte address[6] = "69696";
int lidar_nano,ultra_nano;
int count = 0;

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(vibMot_Lidar, OUTPUT);
  pinMode(vibMot_US, OUTPUT);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  //Serial.println("Test");
  //digitalWrite(led, HIGH);
  if (radio.available()) 
  {
  radio.read(&ultra_nano, sizeof(int));


  if (ultra_nano < 0)
 {
  ultra_nano = ultra_nano * -1;
  Serial.print("ULTRA SONIC DISTANCE   = ");
  Serial.print(ultra_nano);

 }
 else
 {
     lidar_nano = ultra_nano;
     Serial.print("\t\tLidar DISTANCE   = ");
     Serial.println(lidar_nano);
 
}
  }
}
 





/*
* Arduino Wireless Communication Tutorial
* 	Receiver Code

* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
/*
****Pin Config****
D6 -> LED
D7 -> vibMot_Lidar
D8 -> vibMot_US
D9 -> CE
D10 -> CSN
D11 -> MOSI
D12 -> MISO
D13 -> SCK

*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define vibMot_Lidar 7
#define vibMot_US 6
#define led 6

RF24 radio(9, 10); // CE, CSN

const byte address[6] = "69696";
int distance_nano = 9999;
int lidar_nano = 9999;
int ultra_nano = 9999;
int count = 0;

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(vibMot_Lidar, OUTPUT);
  pinMode(vibMot_US, OUTPUT);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  //Serial.println("Test");
  lidar_nano = 9999;
  ultra_nano = 9999;
  //digitalWrite(led, HIGH);
  if (radio.available())
  {
  radio.read(&distance_nano, sizeof(int));
  ultra_nano = distance_nano;
  lidar_nano = distance_nano;
  if (ultra_nano < 0)
 {
  ultra_nano = ultra_nano * -1;
 
  Serial.print("ULTRA SONIC DISTANCE   = ");
  Serial.print(ultra_nano);
   
   if (ultra_nano >= 20 && ultra_nano <= 120) {
   	 
     	digitalWrite(vibMot_US, HIGH);
     	delay(500);
     	digitalWrite(vibMot_US, LOW);
     	delay(500);

     	 
     	}

 }
 else
 {
	 
 	Serial.print("\t\tLidar DISTANCE   = ");
 	Serial.println(lidar_nano);
 
 
 	if (lidar_nano >= 118) {
   	 
     	digitalWrite(vibMot_Lidar, HIGH);
     	delay(500);
     	digitalWrite(vibMot_Lidar, LOW);
     	delay(500);

     	 
     	}
    	 
 	}
    
	 
  }
}
 




