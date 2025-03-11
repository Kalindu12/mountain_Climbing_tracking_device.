
#include "DHT.h" //for humidity and tempertater
#include"TinyGPS++.h" //for gps
#include "SoftwareSerial.h" //for gps
#include <SoftwareSerial.h>//for gsm
#include <PulseSensorPlayground.h> // Includes the PulseSensorPlayground Library.
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h> 


#define USE_ARDUINO_INTERRUPTS true // for hartbeat
#define DHTPIN 7 //for humidity and tempertater
#define DHTTYPE DHT11//for humidity and tempertater 
#define SIM800_TX_PIN 2//for gsm
#define SIM800_RX_PIN 3//for gsm
#define I2C_ADDR 0x27 // Define I2C Address for controller
#define En_pin 2
#define Rw_pin 1
#define Rs_pin 0
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7
#define BACKLIGHT 3

DHT dht(DHTPIN, DHTTYPE);//for humidity and tempertater
LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);.

SoftwareSerial serial_connection(5,6);//for gps
SoftwareSerial serialSIM800(SIM800_TX_PIN,SIM800_RX_PIN);//for gsm
TinyGPSPlus gps; //for gps

// Variables
const int PulseWire = 0; // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int LED13 = 13; // The on-board Arduino LED, close to PIN 13.
int Threshold = 550; // Determine which Signal to "count as a beat" and which to ignore.
// Use the "Gettting Started Project" to fine-tune Threshold Value beyond default setting.
// Otherwise leave the default "550" value.
 
PulseSensorPlayground pulseSensor; // Creates an instance of the PulseSensorPlayground object called "pulseSensor"

void humiSetup(){

  Serial.println(F("DHTxx test!"));

  dht.begin();
}
void gpsSetup(){

  serial_connection.begin(9600);
  Serial.println("Gps Start");
}
void gsmSetup() {
  //Begin serial comunication with Arduino and Arduino IDE (Serial Monitor)
 
  while(!Serial);

 //Being serial communication witj Arduino and SIM800
  serialSIM800.begin(9600);
  delay(1000);
   
  Serial.println("Setup Complete!");
  Serial.println("Sending SMS...");
   
  //Set SMS format to ASCII
  serialSIM800.write("AT+CMGF=1\r\n");
  delay(1000);
 
  //Send new SMS command and message number
  serialSIM800.write("AT+CMGS=\"0702602650\"\r\n");
  delay(1000);
   
  //Send SMS content
  serialSIM800.write("code ek wada");
  delay(1000);
   
  //Send Ctrl+Z / ESC to denote SMS message is complete
  serialSIM800.write((char)26);
  delay(1000);
     
  Serial.println("SMS Sent!");
}
void pulseSensorSetUp(){
lcd.begin(20,4);
lcd.setBacklightPin(BACKLIGHT,POSITIVE);
lcd.setBacklight(HIGH);
 
// Configure the PulseSensor object, by assigning our variables to it.
pulseSensor.analogInput(PulseWire);
pulseSensor.blinkOnPulse(LED13); //auto-magically blink Arduino's LED with heartbeat.
pulseSensor.setThreshold(Threshold);
 
// Double-check the "pulseSensor" object was created and "began" seeing a signal.
if (pulseSensor.begin()) {
Serial.println("We created a pulseSensor Object !"); //This prints one time at Arduino power-up, or on Arduino reset.
lcd.setCursor(0,0);
lcd.print(" Heart Rate ");
}
void setup() {
Serial.begin(9600);
 humiSetup();
 gpsSetup();
gsmSetup();
pulseSensorSetUp()
}

void humiLoop(){
// Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
}

void gpsLoop(){
 while(serial_connection.available())
  {
    gps.encode(serial_connection.read());
  }
  if(gps.location.isUpdated())
  {
    Serial.print("Satelite count:");
    Serial.println(gps.satellites.value());
    Serial.print("Latitude:");
    Serial.println(gps.location.lat(),6);
    Serial.print("Longitude:");
    Serial.println(gps.location.lng(),6);

    Serial.print("Altitude Feet:");
    Serial.println(gps.altitude.feet());
    Serial.println("");

    Serial.println("Date: ");
    if(gps.date.isValid())
    {
      Serial.print(gps.date.month());
      Serial.print("/");
      Serial.print(gps.date.day());
      Serial.print("/");
      Serial.println(gps.date.year());
    }

    Serial.print("Time: ");
    if(gps.time.isValid())
    {
      if(gps.time.hour()< 10) Serial.print(F("0"));
      Serial.print(gps.time.hour());
      Serial.print(":");
      if(gps.time.minute()< 10) Serial.print(F("0"));
      Serial.print(gps.time.minute());
      Serial.print(":");
      if(gps.time.second()< 10) Serial.print(F("0"));
      Serial.print(gps.time.second());
      Serial.print(".GMT");
    }
    Serial.println("");
    delay(2000);
    }
}

void gsmloop() {

  
}

void pulsSensorLoop(){
int myBPM = pulseSensor.getBeatsPerMinute(); // Calls function on our pulseSensor object that returns BPM as an "int".
// "myBPM" hold this BPM value now.
if (pulseSensor.sawStartOfBeat()) { // Constantly test to see if "a beat happened".
Serial.println("♥ A HeartBeat Happened ! "); // If test is "true", print a message "a heartbeat happened".
Serial.print("BPM: "); // Print phrase "BPM: "
Serial.println(myBPM); // Print the value inside of myBPM.
lcd.setCursor(0,0);
//lcd.println("HeartBeat Happened !"); // If test is "true", print a message "a heartbeat happened".
lcd.setCursor(0,0);
lcd.print("BPM: "); // Print phrase "BPM: "
lcd.print(myBPM);
//..................................................................................................................................................................
/*if(222> myBPM||myBPM>230){
  lcd.setCursor(0,0);
  lcd.println("over ");
  lcd.println("limit" );}*/
}
delay(20); // considered best practice in a simple sketch.
}

void loop(){
humiLoop();
gpsLoop();
gsmloop();
pulsSensorLoop();
}