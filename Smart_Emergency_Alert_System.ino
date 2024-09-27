// Define pins
const int buttonPin = 2; // Pin for emergency button
const int smokeSensorPin = 3; // Pin for smoke sensor digital output
const int buzzerPin = 8; // Pin for buzzer
const int ledPin = 9; // Optional: Pin for LED indication

bool alertActive = false; // Variable to track alert state

void setup() {
  // Initialize pin modes
  pinMode(buttonPin, INPUT_PULLUP); // Button with internal pull-up resistor
  pinMode(smokeSensorPin, INPUT); // Smoke sensor digital input
  pinMode(buzzerPin, OUTPUT); // Buzzer output
  pinMode(ledPin, OUTPUT); // Optional: LED output

  // Initialize serial communication for alert message
  Serial.begin(9600);
  Serial.println("Emergency Service System Initialized.");
}

void loop() {
  // Check if the emergency button is pressed or smoke is detected
  if (digitalRead(buttonPin) == LOW || digitalRead(smokeSensorPin) == HIGH) {
    if (!alertActive) { // Check if the alert is not already active
      alertActive = true;
      activateAlert(); // Activate alert when button is pressed or smoke detected
    }
  } else {
    if (alertActive) { // Check if the alert is active and button is released, and no smoke is detected
      alertActive = false;
      resetAlert(); // Reset alert when button is released and no smoke detected
    }
  }
}

void activateAlert() {
  // Simulate sending an alert to the emergency service center
  Serial.println("Emergency Alert Activated! Notifying Service Center...");
  
  // Activate buzzer and LED for alert
  digitalWrite(buzzerPin, HIGH);
  digitalWrite(ledPin, HIGH); // Optional: Turn on LED
  delay(500); // Alert for 0.5 seconds

  // Send a continuous alert until the button is released or smoke is no longer detected
  while (digitalRead(buttonPin) == LOW || digitalRead(smokeSensorPin) == HIGH) {
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(ledPin, HIGH); // Optional: Keep LED on
    delay(500);
    digitalWrite(buzzerPin, LOW);
    digitalWrite(ledPin, LOW); // Optional: Turn off LED
    delay(500);
  }
}

void resetAlert() {
  // Simulate alert reset message
  Serial.println("Emergency Alert Deactivated.");
  
  // Turn off buzzer and LED
  digitalWrite(buzzerPin, LOW);
  digitalWrite(ledPin, LOW); // Optional: Turn off LED
}