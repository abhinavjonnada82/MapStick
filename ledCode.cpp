/* Lidar and Ultrasonic Mapstic Code
  Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
  NRD24L01 will need to use pins:
  D4 -> OPEN
  D5 -> LED
  D6 -> Trig
  D7 -> Echo
  D8 -> BUZZER
  D4-> CE
  D2 -> CSN
  D11 -> MOSI
  D12 -> MISO
  D13 ->SCK
*/

#include <Wire.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define LIDARLite_ADDRESS 0x62                 	// Default I2C Address of LIDAR-Lite.
#define RegisterMeasure 0x00                   	// Register to write to initiate ranging.
#define MeasureValue 0x04                      	// Value to initiate ranging.
#define RegisterHighLowB 0x8f                  	// Register to get both High and Low bytes in 1 v  call.
                                               	//Ultrasonic pins
#define ultraLed	5
#define lidarLed	1
#define trigPin 6
#define echoPin 7
#define buzzer 8                                	//NRF24L01



RF24 radio(4, 2); // CE, CSN
const byte address[6] = "69696";              	//Address for NRF24L01

long Test1 = -1;
long distance_lidar = 9999;                     	// Distance measured for lidar
long distance_ultra = 9999;                     	// Distance measured for ultrasonic
long duration;                                	//measured return from ultrasonic

void setup()
{

  // Serial output
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(ultraLed, OUTPUT);
  pinMode(lidarLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.println("< START >");

  // LIDAR control
  Wire.begin();  // join i2c bus


  //---------------------------------------------NRF24L01
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

// Get a measurement from the LIDAR Lite
int lidarGetRange(void)
{
  int val = -1;
  Wire.beginTransmission((int)LIDARLite_ADDRESS); // transmit to LIDAR-Lite
  Wire.write((int)RegisterMeasure);           	// sets register pointer to  (0x00)
  Wire.write((int)MeasureValue);              	// sets register pointer to  (0x00)
  Wire.endTransmission();                     	// stop transmitting

  delay(200); // Wait 20ms for transmit

  Wire.beginTransmission((int)LIDARLite_ADDRESS); // transmit to LIDAR-Lite
  Wire.write((int)RegisterHighLowB);          	// sets register pointer to (0x8f)
  Wire.endTransmission();                     	// stop transmitting

  delay(200); // Wait 20ms for transmit

  Wire.requestFrom((int)LIDARLite_ADDRESS, 2); 	// request 2 bytes from LIDAR-Lite

  if (2 <= Wire.available())                   	// if two bytes were received
  {
	val = Wire.read();                         	// receive high byte (overwrites previous reading)
	val = val << 8;                            	// shift high byte to be high 8 bits
	val |= Wire.read();                        	// receive low byte as lower 8 bits
  }
  return val;
}
//prints output to serial monitor
void serialPrintRange(int usDistance, int lidarDistance)
{
  //print value of ultrasonic
  Serial.print("Ultrasonic Distance (cm): ");

  Serial.print(usDistance);
  radio.write(&usDistance, sizeof(int));
 
 
  Serial.print("\t\t Lidar Distance (cm): ");
  Serial.println(lidarDistance);
  radio.write(&lidarDistance, sizeof(lidarDistance));
}

//Run lidar and ultrasonic
void loop()

{
	/*
 	uint8_t pipe =0 ;
  if (radio.available(&pipe)){
 //
  //  digitalWrite(buzzer, HIGH);
  //  Serial.println("Radio NOt avala");
   // digitalWrite(led, HIGH);
	delay(2000);
	//digitalWrite(buzzer, LOW);
	digitalWrite(led, LOW);
 	//radio.flush_rx();
	setup();
  }
 
else
*/
{
  //return ultrasonic distance
 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(2);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
                                                                                                                               	 
  distance_lidar = lidarGetRange();
 
  //return lidar distance
  distance_ultra = (duration / 2) / 29.1;
   //delay(2000);

 




 if (distance_ultra >= 20 && distance_ultra <= 120) {
 	 
  	digitalWrite(ultraLed, HIGH);
  	digitalWrite(buzzer, HIGH);
  	delay(500);
  	digitalWrite(ultraLed, LOW);
  	digitalWrite(buzzer, LOW);
  	delay(500);

 }

   if (distance_lidar >= 125)
   {

  	digitalWrite(lidarLed, HIGH);
  	delay(500);
  	digitalWrite(lidarLed, LOW);
  	 
  	}




  //-------for debug------------



  serialPrintRange(distance_ultra * -1 , distance_lidar);
}
}








