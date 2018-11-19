// Include Libraries
#include "Arduino.h"
#include "HX711.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

// Pin Definitions
#define DFPLAYER_PIN_RX  11
#define DFPLAYER_PIN_TX 10
#define LOADCELLHX711SF_PIN_DAT 3
#define LOADCELLHX711SF_PIN_CLK 2

// Global variables and defines
float bowlWeightFull = 0;
float tempWeight = 0;

// Constructors
HX711 scale;
SoftwareSerial dfPlayerSerial(DFPLAYER_PIN_TX, DFPLAYER_PIN_RX);
DFRobotDFPlayerMini myDFPlayer;

/* This code sets up the essentials for your circuit to work. It runs first every time your circuit is powered with electricity. */
void setup() {
  // Setup Serial which is useful for debugging
  // Use the Serial Monitor to view printed messages
  Serial.begin(9600);
  while (!Serial) ; // wait for serial port to connect. Needed for native USB
  Serial.println("start");

  dfPlayerSerial.begin(9600);
  if (!myDFPlayer.begin(dfPlayerSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while (true);
  }
  Serial.println(F("DFPlayer Mini online."));
  myDFPlayer.volume(30);
  
  scale.begin(LOADCELLHX711SF_PIN_DAT, LOADCELLHX711SF_PIN_CLK);
  scale.set_scale(2280.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();                // reset the scale to 0
  
  //get empty bowl weight
  bowlWeightFull = scale.get_units(10);
}

/* This code is the main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop. */
void loop() {
    tempWeight = scale.get_units(5);
    //when filling the bowl, update its weight
    if (tempWeight - bowlWeightFull > 100){
      bowlWeightFull = tempWeight;
      Serial.println("Fruit added");
    }
    // A fruit was taken from the bowl, play something
    else if (bowlWeightFull - tempWeight > 100)
    {
      myDFPlayer.next();
      Serial.println("Fruit Taken");
      bowlWeightFull = tempWeight;
      delay(3000);
      
    }
  }



/*******************************************************

     Circuito.io is an automatic generator of schematics and code for off
     the shelf hardware combinations.

     Copyright (C) 2016 Roboplan Technologies Ltd.

     This program is free software: you can redistribute it and/or modify
     it under the terms of the GNU General Public License as published by
     the Free Software Foundation, either version 3 of the License, or
     (at your option) any later version.

     This program is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     GNU General Public License for more details.

     You should have received a copy of the GNU General Public License
     along with this program.  If not, see <http://www.gnu.org/licenses/>.

     In addition, and without limitation, to the disclaimers of warranties
     stated above and in the GNU General Public License version 3 (or any
     later version), Roboplan Technologies Ltd. ("Roboplan") offers this
     program subject to the following warranty disclaimers and by using
     this program you acknowledge and agree to the following:
     THIS PROGRAM IS PROVIDED ON AN "AS IS" AND "AS AVAILABLE" BASIS, AND
     WITHOUT WARRANTIES OF ANY KIND EITHER EXPRESS OR IMPLIED.  ROBOPLAN
     HEREBY DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT
     NOT LIMITED TO IMPLIED WARRANTIES OF MERCHANTABILITY, TITLE, FITNESS
     FOR A PARTICULAR PURPOSE, NON-INFRINGEMENT, AND THOSE ARISING BY
     STATUTE OR FROM A COURSE OF DEALING OR USAGE OF TRADE.
     YOUR RELIANCE ON, OR USE OF THIS PROGRAM IS AT YOUR SOLE RISK.
     ROBOPLAN DOES NOT GUARANTEE THAT THE PROGRAM WILL BE FREE OF, OR NOT
     SUSCEPTIBLE TO, BUGS, SECURITY BREACHES, OR VIRUSES. ROBOPLAN DOES
     NOT WARRANT THAT YOUR USE OF THE PROGRAM, INCLUDING PURSUANT TO
     SCHEMATICS, INSTRUCTIONS OR RECOMMENDATIONS OF ROBOPLAN, WILL BE SAFE
     FOR PERSONAL USE OR FOR PRODUCTION OR COMMERCIAL USE, WILL NOT
     VIOLATE ANY THIRD PARTY RIGHTS, WILL PROVIDE THE INTENDED OR DESIRED
     RESULTS, OR OPERATE AS YOU INTENDED OR AS MAY BE INDICATED BY ROBOPLAN.
     YOU HEREBY WAIVE, AGREE NOT TO ASSERT AGAINST, AND RELEASE ROBOPLAN,
     ITS LICENSORS AND AFFILIATES FROM, ANY CLAIMS IN CONNECTION WITH ANY OF
     THE ABOVE.
********************************************************/
