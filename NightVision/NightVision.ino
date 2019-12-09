/*
 * Motion Sensor Activated Light for Night Vision
 * https://www.instagram.com/siddhantshah2212
 * https://www.github.com/SiddhantShah2001/NightVision
 */

/*
 * Parts Needed:-
  
 * Arduino (Mega/Uno/Nano/Mini)
 * PIR (Passive Infra-red) Sensor Module
 * LDR (Light Dependent Resistor) Module (Active-Low Version)
 * BJT TIP122 or Logic Level N-Channel MOSFET (E.g IRLZ44N)
 * Heat-sink for Transistor (if Needed)
 * 10K Ohm Resistor (If using MOSFET)
 * 1K Ohm Resistor
 * 12V LED Strip (Any Color)
 * 12V DC Adapter
 * Jumper Wires
 */

/*
 * Wiring:-
  
 # PIR Module:
 * +ve/Vin -> Arduino Pin 13
 * -ve/Gnd -> Arduino GND
 * Out -> Arduino Pin 8
 
 # LDR Module:
 * +ve/Vin -> Arduino 5V/3.3V
 * -ve/Gnd -> Arduino GND
 * Out -> Arduino Pin 7
  
 # BJT:
 * Emitter -> Arduino GND
 * Collector -> LED Strip -VE/GND
 * Base -> 1K Ohm Resistor -> Arduino Pin 9

(If Using MOSFET) 
 # MOSFET:
 * Source -> Arduino GND
 * Drain -> LED Strip -VE/GND
 * Gate -> 1K Ohm Resistor -> Arduino Pin 9 
 * Additionally (Gate -> 10K Ohm Resistor -> SOURCE/GND)
 
 # LED Strip:
 * +ve/Vin -> Arduino VIN
 * -ve/Gnd -> Transistor Collector/Drain
 
 # 12V DC Adapter:
 * Adapter Male Pin -> Arduino DC Female Socket
 */

// Declaring I/O Pins
const int LDR = 7;  // Out-Pin from LDR Module.
const int PIR = 8;  // Out-Pin from PIR Module.
const int LED = 9;  // Output Pin for LED. (Connects to the Base of BJT TIP122 or Gate of Logic Level MOSFET via 1K Ohm Resistor)
const int VIN = 13; // Output Pin for PIR +ve/Vin.

// Global Variables
int i = 0;            // Variable for PWM Operation.
int tag = LOW;        // Variable for LDR to Reset Light State and Value.
int brightness = LOW; // Variable for PIR to set Light state.

// Setup Runs only Once, unless called for.
void setup ()
{
  Serial.begin(9600); // Initialise Serial Monitor with Baud-Rate of 9600
  Serial.println(""); // Skips the First Line for Head-room (Not Neccessary)
  
  pinMode(LDR, INPUT);  // Declare LDR-Pin as an Input
  pinMode(PIR, INPUT);  // Declare PIR-Pin as an Input
  pinMode(LED, OUTPUT); // Declare LED-Pin as an Output
  pinMode(VIN, OUTPUT); // Declare VIN-Pin as an Output
}

// Loop Runs Forever.
void loop ()
{
  int state = digitalRead(PIR);   // Variable to Read the PIR Sensor Value.
  int ambient = digitalRead(LDR); // Variable to Read the LDR Sensor Value.
  ambient = !ambient;             // Set Variable-"ambient" to the Opposite of it's Original Value. 
  i = constrain(i, 0, 255);       // Constrain Function Limits the Variable-"i" to be within the 0 - 255 Range.

  if (ambient == LOW && tag == LOW) // If the Value of Variables "ambient" & "tag" are "LOW" (If the Ambiance is Dark).
  {
    digitalWrite(VIN, HIGH);        // Set PIR +ve/Vin Pin to "HIGH" (Turn On Motion Sensor).
    brightness = LOW;               // Set Variable-"brightness"  to "LOW".
    i = 0;                          // Set Variable-"i" to "0".
    tag = HIGH;                     // Set Variable-"tag" to "HIGH" (To avoid re-executing this "if" statement).
  }
  else if (ambient == HIGH) // If the Value of Variable-"ambient" is "HIGH" (If the Ambiance is Bright).
  {
    digitalWrite(VIN, LOW); // Set PIR +ve/Vin Pin to "LOW" (Turn Off Motion Sensor).
    digitalWrite(LED, LOW); // Set LED Pin to "LOW" (Turn Off Light).
    brightness = LOW;       // Set Variable-"brightness" to "LOW".
    i = 0;                  // Set Variable-"i" to "0".
    tag = LOW;              // Set Variable-"tag" to "LOW" (To make the above Declared "if" statement Executable when it's Dark again).
  }

  if (state == HIGH && brightness == LOW && i <= 0) // If the Value of Variables "state", "brightness" are "LOW" & "i" is "0" (If the current Output Value of PIR Sensor is "HIGH" and Previous Value of Light was "LOW").  
  {
    Serial.println("Motion Sensed");                // Print Text on a new Line with String "Motion Sensed" on Serial Monitor (Display Text "Motion Sensed" on Serial Monitor).
    Serial.print("Value ON: ");                     // Print Text with String "Value ON: " on Serial Monitor (Display Text "Value ON: " on Serial Monitor).
    
    for (i = 0; i <= 255; i++)                      // For the Variable-"i" with Current Value "0" and "i" Smaller than or Equal to "255", Value of "i" + "1" (Starting with "i" as "0" and Increasing it's Value untill 255 by "1").
    {
      int ambient = digitalRead(LDR);     // Re-Declaration of Variable-"ambient" to use it inside a "for" Loop.
      ambient = !ambient;                 // Set Variable-"ambient" to the Opposite of it's Original Value.
      if (ambient == HIGH)                // If the Value of Variable-"ambient" is "HIGH" (Exit the Loop and return to "OFF" State if it's Dark again).
      {
        Serial.println("");               // Finish and Skip Current Text Line on Serial Monitor.
        Serial.println("Ambient : HIGH"); // Print Text on a new Line with String "Ambient : HIGH" on Serial Monitor (Display Text "Ambient : HIGH" on Serial Monitor).
        break;                            // Exit the "for" Loop.
      }
      Serial.print(i);                              // Print Text with the Value of Variable-"i" on the "Value ON: " Line on Serial Monitor (Display the changed current Value of "i" after Text String "Value ON: " on the Same Line).
      Serial.print("  |  ");                        // Print Text with String "  |  " on Serial Monitor (Create Gap for the Next Values of "i" to be Printed).
      analogWrite(LED, i);                          // Set the PWM Duty Cycle Value for LED Pin as "i" (PWM Value is equal to the value of "i").
      delay(100);                                   // Delay for 100mS to slowly Increase the Brightness, the Time taken from 0% to 100% Brightness is 100*255 = 25500mS. Increase or Decrease the time for Longer or Shorter Rise Time (A gap of 100mS before the Next value to PWM is assigned).
    }
    Serial.println("");                             // Finish and Skip the On-going Line.
    Serial.println("");                             // Skip one Line

    brightness = HIGH;                              // Set Variable-"brightness" to "HIGH".
  }

  else if (state == LOW && brightness == HIGH) // Else If the above conditions don't match anymore and the Value of Variable-"state" is "LOW" and Value of Variable-"brightness" is "HIGH" (Otherwise If the above mentioned "if" Parameters don't match anymore i.e the PIR Sensor Value is "LOW" and the previous value of Light was "HIGH").
  {
    Serial.print("Value OFF: ");               // Print Text with String ("Value OFF: ") on Serial Monitor (Display Text "Value OFF: " on Serial Monitor).
    for (i = 255; i >= 0; i--)                 // For the Variable-"i" with Current Value "255" and "i" Greater than or Equal to "0", Value of "i" - "1" (Starting with "i" as "255" and decreasing it's Value untill 0 by "1").
    {
      int state = digitalRead(PIR); // Re-Declaration of Variable-"state" to use it inside a "for" Loop.
      if (state == HIGH)            // If the Value of Variable-"state" is "HIGH" (If the Motion was Retriggered while turning Off LED, the Light turns back On).
      {
        for (i; i <= 255; i++)      // For the Variable-"i", "i" Smaller than or Equal to "255", Value of "i" + "1" (Starting with "i" and Increasing it's Value untill 255 by "1").
        {
          Serial.print(i);          // Print Text with the Value of Variable-"i" on the "Value OFF: " Line on Serial Monitor (Display the changed current Value of "i" after Text String "Value OFF: " on the Same Line).
          Serial.print("  |  ");    // Print Text with String "  |  " on Serial Monitor (Create Gap for the Next Values of "i" to be Printed).
          analogWrite(LED, i);      // Set the PWM Duty Cycle Value for LED Pin as "i" (PWM Value is equal to the value of "i").
          delay(10);                // Delay for 10mS to slowly Increase the Brightness, the Time taken from 0% to 100% Brightness is 10*255 = 2550mS. Increase or Decrease the time for Longer or Shorter Rise Time (A gap of 10mS before the Next value to PWM is assigned).
        }
        break;                      // Exit the "for" Loop.
      }
      Serial.print(i);                         // Print Text with the Value of Variable-"i" on the "Value OFF: " Line on Serial Monitor (Display the changed current Value of "i" after Text String "Value OFF: " on the Same Line).
      Serial.print("  |  ");                   // Print Text with String "  |  " on Serial Monitor (Create Gap for the Next Values of "i" to be Printed).
      analogWrite(LED, i);                     // Set the PWM Duty Cycle Value for LED Pin as "i" (PWM Value is equal to the value of "i").
      delay(25);                               // Delay for 25mS to slowly Decrease the Brightness, the Time taken from 100% to 0% Brightness is 25*255 = 6375mS. Increase or Decrease the time for Longer or Shorter Fall Time (A gap of 25mS before the Next value to PWM is assigned).
    }
    Serial.println("");                        // Finish and Skip the On-going Line.
    Serial.println("");                        // Skip One Line.

    brightness = LOW;                          // Set Variable-"brightness" to "LOW".

    if (i > 0)                                 // If the Final Value of "i" was Greater than "0" (If Motion was re-triggered)
    {
      brightness = HIGH;                       // Set Variable-"brightness" to "HIGH".
    }
  }
}
