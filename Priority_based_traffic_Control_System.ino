// Pin definitions for traffic lights (g = green, y = yellow, r = red)
int g1 = A2;  // Green light for Highway
int y1 = 2;   // Yellow light for Highway
int r1 = 3;   // Red light for Highway

int g2 = 4;   // Green light for Street 1
int y2 = 5;   // Yellow light for Street 1
int r2 = 6;   // Red light for Street 1

int g3 = 7;   // Green light for Street 2
int y3 = 8;   // Yellow light for Street 2
int r3 = 9;   // Red light for Street 2

int g4 = 10;  // Green light for Street 3
int y4 = 11;  // Yellow light for Street 3
int r4 = 12;  // Red light for Street 3

// Motion sensor pins to detect cars waiting at Street 1 and Street 3
int motion2 = A0;  // Motion sensor for Street 1
int motion4 = A1;  // Motion sensor for Street 3

void setup() {
  // Initialize all traffic light pins as OUTPUT
  pinMode(A2, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  
  // Initialize motion sensor pins as INPUT to detect waiting cars
  pinMode(motion2, INPUT);
  pinMode(motion4, INPUT);
  
  // Start serial communication for debugging and status messages
  Serial.begin(9600);
}

void loop() {
  // Reset all yellow and red lights to ensure clean start
  digitalWrite(y1, LOW);
  digitalWrite(r1, LOW);
  digitalWrite(g2, LOW);
  digitalWrite(y2, LOW);
  digitalWrite(y3, LOW);
  digitalWrite(r3, LOW);
  digitalWrite(g4, LOW);
  digitalWrite(y4, LOW);

  // Highway is open (green light on highway), streets are closed (red lights)
  analogWrite(g1, 255); // Green light on highway at maximum brightness
  digitalWrite(r2, HIGH);  // Red light for Street 1
  digitalWrite(g3, HIGH);  // Green light for Street 2 (assumed open for continuous flow)
  digitalWrite(r4, HIGH);  // Red light for Street 3
  
  Serial.println("HIGHWAY OPEN!");

  // Initialize a flag to check for waiting cars
  int r = 0;

  // Check for waiting cars for 15 seconds (1 second delay per iteration)
  for (int i = 1; i < 15; i++) {
    if (digitalRead(motion2) == HIGH || digitalRead(motion4) == HIGH) {
      r = 1;  // Set flag if cars are detected at Street 1 or Street 3
    }
    delay(1000);  // Wait for 1 second
  }
  
  Serial.println("CHECKING FOR CARS WAITING");

  // If cars are detected, switch the traffic light sequence
  if (r == 1) {  
    Serial.println("CARS DETECTED");

    // Turn off the highway green light, turn on yellow
    digitalWrite(g1, LOW);  
    digitalWrite(y1, HIGH);  
    digitalWrite(g3, LOW);   // Turn off green for Street 2
    digitalWrite(y3, HIGH);  // Turn on yellow for Street 2
    delay(2000);             // Wait 2 seconds for yellow light transition

    // Close highway (red light on), Street 2 also closed
    digitalWrite(r1, HIGH);  
    digitalWrite(y1, LOW);  
    digitalWrite(r3, HIGH);  
    digitalWrite(y3, LOW);

    // Open streets for cars (green lights for Street 1 and Street 3)
    digitalWrite(r2, LOW);  
    digitalWrite(g2, HIGH);  
    digitalWrite(r4, LOW);  
    digitalWrite(g4, HIGH);
    
    Serial.println("Street OPEN!!");
    delay(5000);  // Allow street traffic for 5 seconds

    // Start yellow light transition for streets (prepare to close streets)
    digitalWrite(g2, LOW);  
    digitalWrite(y2, HIGH);  
    digitalWrite(g4, LOW);  
    digitalWrite(y4, HIGH);
    delay(2000);  // Wait 2 seconds for yellow light transition

    // Close streets (red lights on for Street 1 and Street 3)
    digitalWrite(r2, HIGH);  
    digitalWrite(r4, HIGH);

    Serial.println("Street CLOSED!!");
  } 
  else {
    // No cars detected, keep the highway open
    Serial.println("NO CARS DETECTED!");
  }
}
