// Stepper motor connections
const int a = 16;  // Pin connected to coil A
const int b = 17;  // Pin connected to coil B
const int c = 18;  // Pin connected to coil C
const int d = 19;  // Pin connected to coil D

const int delayTime = 10;  // Delay between steps in milliseconds// Can go to 2 mili second delay minimum and will give fastest speed
const int targetSteps = 300;  // Set the target step count here (example: one full revolution)
const byte LED = 2;
int stepCount = 0;

// Sensor connections
const int sensorPin = 4;  // select the input pin for the sensor
int sensorValue = 0;  // variable to store the value coming from the sensor
const int threshold = 2820;  // Example threshold value for sensor
// 2817 Sensor/161 step, 2820/187, 2817/160, 2820/188 (This was my calculation of detection)

void setup() {
  // Initialize the motor pins as outputs
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(LED, OUTPUT);

  // Initialize the sensor pin
  //  pinMode(sensorPin, INPUT);// This is not required I dont know why when I was writing this

  Serial.begin(115200);  // Start serial communication at 115200 baud

  Serial.print("Count down: ");
  for (int i = 5; i >= 1; i--) {
    Serial.print(i);
    Serial.print("...");
    delay(1000);
  }
  Serial.println();

  // Step 1: Rotate the wheel until the sensor detects the reference point
  //  findReferencePoint();

  // Step 2: Move the wheel to the specific position from the reference point
  //  moveToPosition(150);  // Example position, change as needed
}

void loop() {
  //  // Step 1: Rotate the wheel until the sensor detects the reference point
  //  findReferencePoint();
  //
  //  // Step 2: Move the wheel to the specific position from the reference point
  //  moveToPosition(100);  // Example position, change as needed

  // Step 3: Proceed with the next tasks
  for (int i = 1; i <= 2; i++) {
    Serial.print("Test count_____________________________________________________: ");
    Serial.println(i);

    findReferencePoint();
    coolDown();
    moveToPosition(380);
    coolDown();
    //    Serial.println("Forward rotation:");
    //    runMotor(true);  // Run motor forward
    //    stepCount = 0;
    //
    //    delay(1000);  // Short delay before reverse rotation
    //
    //    Serial.println("Reverse rotation:");
    //    runMotor(false);  // Run motor reverse
    //    stepCount = 0;
  }

  // Halt the loop
  while (true) {
    // You can add some idle code here if needed
    digitalWrite(LED, HIGH);
    delay(1000);
    digitalWrite(LED, LOW);
    delay(1000);
  }
}

void findReferencePoint() {
  Serial.println("Finding reference point...");
  while (true) {
    // Rotate the motor forward to find the reference point
    stepMotor(0, 0, 1, 1);  // 1010
    stepMotor(0, 1, 1, 0);  // 0110
    stepMotor(1, 1, 0, 0);  // 0101
    stepMotor(1, 0, 0, 1);  // 1001

    //    sensorValue = analogRead(sensorPin);
    //    Serial.print("Sensor Value: ");
    //    Serial.println(sensorValue);


    if (sensorValue > threshold) {
      Serial.println("Reference point detected. Stopping motor.");
      stopMotor();
      break;
    }
  }
}

void moveToPosition(int steps) {
  Serial.print("Moving to position: ");
  Serial.println(steps);
  stepCount = 0;
  while (stepCount < steps) {
    stepMotor(1, 1, 0, 0);  // 1001
    stepMotor(0, 1, 1, 0);  // 0101
    stepMotor(0, 0, 1, 1);  // 0110
    stepMotor(1, 0, 0, 1);  // 1010
    stepCount++;
  }
  stopMotor();
  Serial.println("Reached the specified position.");
}

void runMotor(bool forward) {
  stepCount = 0;
  while (stepCount < targetSteps) {
    if (forward) {
      // Full-step sequence for forward rotation
      stepMotor(1, 1, 0, 0);  // 1010
      stepMotor(0, 1, 1, 0);  // 0110
      stepMotor(0, 0, 1, 1);  // 0101
      stepMotor(1, 0, 0, 1);  // 1001
    } else {
      // Full-step sequence for reverse rotation
      stepMotor(1, 0, 0, 1);  // 1001
      stepMotor(0, 0, 1, 1);  // 0101
      stepMotor(0, 1, 1, 0);  // 0110
      stepMotor(1, 1, 0, 0);  // 1010
    }

    // Increment the step counter
    stepCount++;

    // Print the step counter to the Serial Monitor
    Serial.print("Step count: ");
    Serial.println(stepCount);
  }

  stopMotor();

  // Print a message indicating the target has been reached
  Serial.println("Target step count reached. Motor stopped.");
  coolDown();
}

void stopMotor() {
  // Stop the motor by setting all pins to LOW
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
}

void coolDown() {
  Serial.print("Cool down: ");
  for (int i = 5; i >= 1; i--) {
    Serial.print(i);
    Serial.print("...");
    delay(1000);
  }
  Serial.println();
}

void stepMotor(int aState, int bState, int cState, int dState) {
  digitalWrite(a, aState);
  digitalWrite(b, bState);
  digitalWrite(c, cState);
  digitalWrite(d, dState);

  sensorValue = analogRead(sensorPin);
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);

  delay(delayTime);



  // Debugging: Print the state of the motor pins
  // Serial.print("Motor states: ");
  // Serial.print(aState);
  // Serial.print(bState);
  // Serial.print(cState);
  // Serial.println(dState);
}
