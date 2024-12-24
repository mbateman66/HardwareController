
#define PIN_LED_BLUE 32
#define PIN_LED_YELLOW 33
#define BAUDRATE 115200

bool blue = false;
bool yellow = false;

void toggle_blue() {
  blue=!blue;
  digitalWrite(PIN_LED_BLUE, blue);
}
void toggle_yellow() {
  yellow=!yellow;
  digitalWrite(PIN_LED_YELLOW, yellow);
}

void setup() {
  // Setup serial port
  Serial.begin(BAUDRATE);
  Serial.println("Starting");
  pinMode(PIN_LED_BLUE, OUTPUT);
  pinMode(PIN_LED_YELLOW, OUTPUT);

}

void loop() {
  while (Serial.available() > 0) {
    
    // Read the next character
    int chr = Serial.read();

    // Terminate a command with a CR
    if (chr == 'b') toggle_blue();
    else if (chr == 'y') toggle_yellow();
    else {
      Serial.print("Unknown command: ");
      Serial.println(chr);
    }
  }

}
