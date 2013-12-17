#include <SPI.h>
#include <Ethernet.h>
#include <avr/io.h>
#include <avr/interrupt.h>

// the html/js which is uploaded to yaler
#include "yalerskript.h"

// definitions concerning yaler service
#include "webdefs.h"

/** The code also needs:
    yalerapi:   functions to access yaler service (via POST/GET)
    interrupts: definition of interrupt routine and setup 
*/

int fireIntensity;     // denotes intensity of LED (0..255)

byte yellowLED = 3;    // 2 LEDs connected to pin 3 and 6, respectively.
byte redLED = 6;       // If you want to add more, connect them to a pwm pin!!

// these variables are changed inside interrupt routine
// thus, they need to be volatile
volatile byte randomLED;    // denotes which LED is toggled
volatile long randOn = 0;   // Initialize a variable for the ON time

const byte FIRE_ON = 1, FIRE_OFF = 0;
volatile int ledState = FIRE_ON; // flags if randomLED is on or off.

/** the setup method **/
void setup() {
  
  // we begin with setting up yaler communication...
  Serial.begin(9600);
  Serial.println("setup");
  Ethernet.begin(mac);
  htmlLength = sizeof(html) - 1;
  Serial.print("Length of html script: "); Serial.println(htmlLength);

  // taken from yaler sample code
  ledUriOffset = 9;//sizeof("PUT /") + sizeof(yalerId) + sizeof("/led/") - 3 * 1;
  // for debugging: Serial.print("ledURIOffset = "); Serial.println(ledUriOffset);

  // now initalising the camp fire...
  randomSeed (analogRead (0));    // randomize
  pinMode(yellowLED, OUTPUT);        // sets the digital pin as output
  pinMode(redLED, OUTPUT);        // sets the digital pin as output
  fireIntensity = 150;
  analogWrite(yellowLED, fireIntensity);
  analogWrite(redLED, fireIntensity);
  
  randOn = random(10, 30);    
  randomLED = yellowLED;
  initInterrupt();
}

/**
 ** Inside the loop there is only the communication with yaler.
 ** The flcikering of the LEDs is done with the timer interrupt
 ** (see sketch interrupts).
 **/
 void loop() {
  EthernetClient client;
  client.connect(server, 80);
  if (client.connected()) {
    Serial.println("connected");
    Serial.println(Ethernet.localIP());
    
    // for debugging: Serial.println("1. sendYalerPostRequest");
    sendYalerPostRequest(client);
    // for debugging: Serial.println("2. receiveYalerResponse");
    receiveYalerResponse(client);
    // for debugging: Serial.println("3. sendGetResponse");
    if (yalerState == YALER_UPGRADED) {
      Serial.println("upgraded");
      receiveRequest(client);
      if (state == DONE) {
        if (isPut) {
          sendPutResponse(client);
        } else {
          sendGetResponse(client);
        }
      }
    } else {
      Serial.println("timeout");
    }
    client.stop();
  }
}


