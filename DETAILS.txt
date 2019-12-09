# NightVision
Motion Sensor Activated Lights for Night Vision


Parts Needed:-
1. Arduino (Mega/Uno/Nano/Mini)
2. PIR (Passive Infra-red) Sensor Module
3. LDR (Light Dependent Resistor) Module (Active-Low Version)
4. BJT TIP122 or Logic Level N-Channel MOSFET (E.g IRLZ44N)
5. Heat-sink for Transistor (if Needed)
6. 10K Ohm Resistor (If using MOSFET)
7. 1K Ohm Resistor
8. 12V LED Strip (Any Color)
9. 12V DC Adapter
10. Jumper Wires


Wiring:-

PIR Module:
1. +ve/Vin  ->  Arduino Pin 13
2. -ve/Gnd  ->  Arduino GND
3. Out      ->  Arduino Pin 8

LDR Module:
1. +ve/Vin  ->  Arduino 5V/3.3V
2. -ve/Gnd  ->  Arduino GND
3. Out      -> Arduino Pin 7

BJT:
1. Emitter    ->  Arduino GND
2. Collector  ->  LED Strip -VE/GND
3. Base       ->  1K Ohm Resistor  ->  Arduino Pin 9

(If Using MOSFET)
MOSFET:
1. Source  ->  Arduino GND
2. Drain   ->  LED Strip -VE/GND
3. Gate    ->  1K Ohm Resistor  ->  Arduino Pin 9
Additionally (Gate  ->  10K Ohm Resistor  ->  SOURCE/GND)

LED Strip:
1. +ve/Vin  ->  Arduino VIN
2. -ve/Gnd  ->  Transistor Collector/Drain

12V DC Adapter:
1.Adapter Male Pin  ->  Arduino DC Female Socket
