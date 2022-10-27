#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.

#include <OneWire.h>
#include <DallasTemperature.h>


#define ONE_WIRE_BUS 8 


OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

int Buzz=11;
//  Variables
float Celsius = 0;
//float Fahrenheit = 0;

const int PulseWire = 0;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int LED13 = 13;          // The on-board Arduino LED, close to PIN 13.
int Threshold = 550;           // Determine which Signal to "count as a beat" and which to ignore.
int val;
int tempPin= 1;                               // Use the "Gettting Started Project" to fine-tune Threshold Value beyond default setting.
                               // Otherwise leave the default "550" value. 
                               
PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"


void setup() {   
  pinMode(Buzz,OUTPUT);
  sensors.begin();
  
  Serial.begin(9600);          // For Serial Monitor

  // Configure the PulseSensor object, by assigning our variables to it. 
  pulseSensor.analogInput(PulseWire);   
  pulseSensor.blinkOnPulse(LED13);       //auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(Threshold);   

  // Double-check the "pulseSensor" object was created and "began" seeing a signal. 
   if (pulseSensor.begin()) {
    //Serial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset.  
  }
}



void loop() {

 int myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".
sensors.requestTemperatures();

  Celsius = sensors.getTempCByIndex(0);
  //Fahrenheit = sensors.toFahrenheit(Celsius);
  if(Celsius>37||myBPM>100||myBPM<60){
    tone(Buzz,2000);
    delay(10);
    noTone(Buzz);
    delay(10);
  }
  else{
    digitalWrite(Buzz,LOW);
  }
  if(Celsius> -127){
    if(pulseSensor.sawStartOfBeat()) { 
      delay(30);
      Serial.println(myBPM);
      Serial.println(Celsius); 
    }
      
    }
  }

  
