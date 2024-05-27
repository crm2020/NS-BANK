/*------------------------------------------------------------------------
  Example sketch for Adafruit Thermal Printer library for Arduino.
  Demonstrates a few text styles & layouts, bitmap printing, etc.

  IMPORTANT: DECLARATIONS DIFFER FROM PRIOR VERSIONS OF THIS LIBRARY.
  This is to support newer & more board types, especially ones that don't
  support SoftwareSerial (e.g. Arduino Due).  You can pass any Stream
  (e.g. Serial1) to the printer constructor.  See notes below.
  ------------------------------------------------------------------------*/

#include "Adafruit_Thermal.h"
#include "bonlogo.h"

// Here's the new syntax when using SoftwareSerial (e.g. Arduino Uno) ----
// If using hardware serial instead, comment out or remove these lines:

#include "SoftwareSerial.h"
#define TX_PIN 6 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN 5 // Arduino receive   GREEN WIRE   labeled TX on printer

SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor


String location = "Wijnhaven Rotterdam";
String date = "10/04/2024";
String time = "12:05";
int transID = 12902;
String IBAN = "###########093";
int bedrag = 50;

void setup() {

  // This line is for compatibility with the Adafruit IotP project pack,
  // which uses pin 7 as a spare grounding point.  You only need this if
  // wired up the same way (w/3-pin header into pins 5/6/7):
  pinMode(7, OUTPUT); digitalWrite(7, LOW);

  mySerial.begin(19200);  // Initialize SoftwareSerial
  printer.begin();        // Init printer (same regardless of serial type)


  // Print the 80x80 logo:
  printer.printBitmap(bonlogo_width, bonlogo_height, bonlogo);
  printer.justify('L');
  printer.setFont('A');
  printer.setSize('M');
  printer.println("Nederlandse Staat Bank");

  printer.println();
  printer.setSize('S');
  printer.println(location); 
  printer.print("Datum: "); printer.print(date);
  printer.print("\tTijd: "); printer.println(time);
  printer.println(); printer.justify('L');
  printer.print("IBAN: "); printer.println(IBAN);
  printer.print("Transactie ID: "); printer.println(transID);

  printer.justify('C'); printer.println("-----------------------------");
  printer.println();
  printer.justify('R'); printer.print("Bedrag:\t"); printer.print(bedrag); printer.println(",00 EUR");
  printer.println();
  printer.justify('C'); printer.println("-----------------------------");
  printer.println("Bedankt voor het pinnen bij de");
  printer.println("Nederlandse Staat Bank."); printer.println();
  printer.println("Graag tot ziens!");
  printer.println(); printer.println(); printer.println();


  printer.sleep();      // Tell printer to sleep
  delay(3000L);         // Sleep for 3 seconds
  printer.wake();       // MUST wake() before printing again, even if reset
  printer.setDefault(); // Restore printer to defaults
}

void loop() {
}

/*

  // Font options
  printer.setFont('B');
  printer.println("FontB");
  printer.println("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
  printer.setFont('A');
  printer.println("FontA (default)");
  printer.println("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

  // Test inverse on & off
  printer.inverseOn();
  printer.println(F("Inverse ON"));
  printer.inverseOff();

  // Test character double-height on & off
  printer.doubleHeightOn();
  printer.println(F("Double Height ON"));
  printer.doubleHeightOff();

  // Set text justification (right, center, left) -- accepts 'L', 'C', 'R'
  printer.justify('R');
  printer.println(F("Right justified"));
  printer.justify('C');
  printer.println(F("Center justified"));
  printer.justify('L');
  printer.println(F("Left justified"));

  // Test more styles
  printer.boldOn();
  printer.println(F("Bold text"));
  printer.boldOff();

  printer.underlineOn();
  printer.println(F("Underlined text"));
  printer.underlineOff();

  printer.setSize('L');        // Set type size, accepts 'S', 'M', 'L'
  printer.println(F("Large"));
  printer.setSize('M');
  printer.println(F("Medium"));
  printer.setSize('S');
  printer.println(F("Small"));

  printer.justify('C');
  printer.println(F("normal\nline\nspacing"));
  printer.setLineHeight(50);
  printer.println(F("Taller\nline\nspacing"));
  printer.setLineHeight(); // Reset to default
  printer.justify('L');

  // Barcode examples:
  // CODE39 is the most common alphanumeric barcode:
  printer.printBarcode("ADAFRUT", CODE39);
  printer.setBarcodeHeight(100);
  // Print UPC line on product barcodes:
  printer.printBarcode("123456789123", UPC_A);

*/
