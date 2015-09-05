#include <NewTone.h>  //library that decides the tone of the buzzer
#include <NewPing.h>  //library that sets the trigger pin, echo pin, and max distance

// Select which PWM-capable pins are to be used.
#define RED_PIN    2  //Arduino pin tied to the red LED

#define TRIGGER_PIN  6  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     7  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 250 // Maximum distance we want to ping for (in centimeters).

#define ALARM 8 //Arduino pin tied to the buzzer

float sinVal;
int toneVal;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
    boolean triggered = false;   //Telling the system to not turn the buzzer on

void setup(){
   Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.  

   //set pinModes
   pinMode(RED_PIN,OUTPUT);

   //reset lights
   analogWrite(RED_PIN,0);

   pinMode(ALARM, OUTPUT);

  delay(5000); 
}

void alarm(){
   for (int x=0; x<180; x++) {
    // convert degrees to radians then obtain sin value
    sinVal = (sin(x*(3.1412/180)));
    // generate a frequency from the sin value
    toneVal = 2000+(int(sinVal*1000));
    NewTone(ALARM, toneVal);
  }
}

void loop(){
    if(triggered == true){  //Plays the alarm function above when the minimum distance is met
      alarm();
    }
    else{
      delay(50);// Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
      unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
      unsigned int distance = uS / US_ROUNDTRIP_CM;
      Serial.println(distance);
      if(distance < 25){
         triggered = true;  //Triggers the alarm if the minimum distance is met
      }
    }
   }
