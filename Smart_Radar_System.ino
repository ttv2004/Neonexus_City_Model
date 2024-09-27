#include <Servo.h>
#include <LiquidCrystal.h>

// Create Servo and LCD objects
Servo myservo; // Create a servo object to control a servo motor
LiquidCrystal lcd(7, 6, 5, 4, 3, 2); // Create an LCD object with pins (rs, enable, d4, d5, d6, d7)

// Define constants and variables
int pos = 0; // Variable to store the servo position
const int trigPin = 9; // Pin for ultrasonic sensor trigger
const int echoPin = 10; // Pin for ultrasonic sensor echo
const int motor = 11; // Pin for servo motor control
const int buzzer = 12; // Pin for buzzer
const int ledPin1 = 13; // Pin for first LED
const int ledPin2 = 8; // Pin for second LED
float distanceCm, DistanceSec, duration; // Variables for distance calculations

void setup() {
  // Attach servo to motor pin and initialize LCD
  myservo.attach(motor); 
  lcd.begin(16, 2); // Initialize the LCD with 16 columns and 2 rows
  
  // Set pin modes for ultrasonic sensor, buzzer, and LEDs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  
  // Define the alert distance threshold
  DistanceSec = 40; // Set the safety distance threshold in cm
  Serial.begin(9600); // Initialize serial communication for debugging
}

void loop() {
  // Sweep the servo from 0 to 180 degrees
  for (pos = 0; pos <= 180; pos += 1) { 
    myservo.write(pos); // Move the servo to the current position
    measureDistance(); // Measure the distance at the current position
    
    // Check if an object is detected within the safety distance
    if (distanceCm <= DistanceSec) {
      // If the object is within half of the safety distance, issue an alert
      if (distanceCm <= DistanceSec / 2) {
        alertCondition(); // Execute alert condition (buzzer and LED)
      } else {
        warningCondition(); // Execute warning condition (LED only)
      }
    } else {
      // No object within safety distance, turn off buzzer and LEDs
      resetAlerts();
    }
    
    // Display the distance and angle on the LCD
    displayLCD();
    delay(80); // Short delay for smooth servo movement
  }

  // Sweep the servo back from 180 to 0 degrees
  for (pos = 180; pos >= 0; pos -= 1) { 
    myservo.write(pos); // Move the servo to the current position
    measureDistance(); // Measure the distance at the current position
    
    // Check if an object is detected within the safety distance
    if (distanceCm <= DistanceSec) {
      // If the object is within half of the safety distance, issue an alert
      if (distanceCm <= DistanceSec / 2) {
        alertCondition(); // Execute alert condition (buzzer and LED)
      } else {
        warningCondition(); // Execute warning condition (LED only)
      }
    } else {
      // No object within safety distance, turn off buzzer and LEDs
      resetAlerts();
    }
    
    // Display the distance and angle on the LCD
    displayLCD();
    delay(80); // Short delay for smooth servo movement
  }
}

// Function to measure the distance using the ultrasonic sensor
void measureDistance() {
  // Send a short pulse to trigger the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Measure the duration of the echo pulse
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance in centimeters
  distanceCm = duration * 0.034 / 2;
  Serial.println(duration); // Debugging: print the measured duration
}

// Function to handle alert condition (object within close proximity)
void alertCondition() {
  tone(buzzer, 1000); // Send 1KHz sound signal to buzzer
  digitalWrite(ledPin1, LOW); // Turn off LED 1
  digitalWrite(ledPin2, HIGH); // Turn on LED 2
  
  // Display alert message on the LCD
  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("Alert...!");
  delay(700);
  noTone(buzzer); // Stop the buzzer sound
}

// Function to handle warning condition (object within moderate proximity)
void warningCondition() {
  digitalWrite(buzzer, HIGH); // Turn on the buzzer
  digitalWrite(ledPin2, LOW); // Turn off LED 2
  digitalWrite(ledPin1, HIGH); // Turn on LED 1
  delay(100);
  digitalWrite(buzzer, LOW); // Turn off the buzzer
}

// Function to reset alerts (no object detected within safety distance)
void resetAlerts() {
  digitalWrite(buzzer, LOW); // Turn off the buzzer
  digitalWrite(ledPin1, LOW); // Turn off LED 1
  digitalWrite(ledPin2, LOW); // Turn off LED 2
}

// Function to display distance and angle on the LCD
void displayLCD() {
  lcd.setCursor(0, 0);
  lcd.print("Distance:"); 
  lcd.print(distanceCm); 
  lcd.print("cm"); 
  delay(10); // Short delay to allow for LCD update
  lcd.setCursor(0, 1);
  lcd.print("Angle:");
  lcd.print(pos);
  lcd.print("deg");
}