/*
 * Project: Motion Alarm with LCD Display
 * Components: PIR Sensor, LED, Buzzer, 16x2 LCD
 *
 * This code triggers an alarm and displays a message on the
 * LCD when motion is detected.
 */

// Include the LCD library
#include <LiquidCrystal.h>

// --- PIN DEFINITIONS ---
// Alarm components
const int pirPin = 2;
const int ledPin = 13;
const int buzzerPin = 8;

// LCD pins (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 7, 6, 5, 4);

int pirState = LOW;
int lastPirState = LOW;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(pirPin, INPUT);

  lcd.begin(16, 2);

  Serial.begin(9600);
  
  // --- CALIBRATION ---
  Serial.println("Calibrating sensor...");
  lcd.print("Calibrating..."); // Show message on LCD
  
  delay(20000); // 20 second calibration time
  
  Serial.println("Sensor ready!");
  lcd.clear(); 
  lcd.print("System Ready"); 
}

void loop() {
  // Read the state of the PIR sensor
  pirState = digitalRead(pirPin);

  // Check if motion has just STARTED
  if (pirState == HIGH && lastPirState == LOW) {
    Serial.println("Motion detected! ALARM!");
    
    // Display alarm message on LCD
    lcd.clear();
    lcd.print("! MOTION !"); // Top row
    lcd.setCursor(0, 1);    // Move to second row
    lcd.print("!  ALARM !");

    // Trigger the 3-beep alarm
    for (int i = 0; i < 3; i++) {
      digitalWrite(ledPin, HIGH);
      digitalWrite(buzzerPin, HIGH);
      delay(150);
      digitalWrite(ledPin, LOW);
      digitalWrite(buzzerPin, LOW);
      delay(150);
    }
    
    lastPirState = HIGH;
  }

  // Check if motion has just STOPPED
  if (pirState == LOW && lastPirState == HIGH) {
    Serial.println("Motion stopped. Alarm off.");
    
    // Reset the LCD to the ready state
    lcd.clear();
    lcd.print("System Ready");
    
    lastPirState = LOW;
  }

  delay(50); // Small delay for stability
}