#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>
#include <Serial.h>

// Standard SPI pin assignments on Arduino
#define SCLK_PIN 13   // Clock
#define MOSI_PIN 11   // Master Out Slave In (COPI)
#define DC_PIN   15   // Data/Command
#define CS_PIN   14   // Chip Select, can use any GPIO except A6/A7
#define RST_PIN  9    // Reset
// Square and ball definitions
#define SQUARE_X     32
#define SQUARE_Y     62
#define SQUARE_W     65
#define SQUARE_H     18
#define BALL_RADIUS  3

//Button enums
//These are the pins the buttons and vibration motor is connected to. 
enum buttons {
    BTN_UP = 2,
    BTN_LEFT = 3,
    BTN_RIGHT = 4,
    BTN_START = 5,
    BTN_A = 6,
    BTN_B = 7,
    BTN_DOWN = 8,
    VIBRA = 9
};

// Ball position and velocity
int ballX = SQUARE_X + SQUARE_W / 2;
int ballY = SQUARE_Y + SQUARE_H / 2;
int velX = 2;
int velY = 1;

int16_t yPos = 26;
int16_t recWidth = 0;

int direction = 1;
int lowerBound = 26;
int upperBound = 27;

// Create an instance of the display
Adafruit_SSD1351 display = Adafruit_SSD1351(128, 128, &SPI, CS_PIN, DC_PIN, RST_PIN);
GFXcanvas16 canvas(128, 128);

void setup() {
    SPI.begin();
    // Initialize display
    display.begin(13000000);
    display.fillScreen(0x0000);

    Serial.begin(9600);

    //Set pinMode for buttons and vibration
    pinMode(BTN_UP, INPUT_PULLUP);
    pinMode(BTN_LEFT, INPUT_PULLUP);
    pinMode(BTN_RIGHT, INPUT_PULLUP);
    pinMode(BTN_START, INPUT_PULLUP);
    pinMode(BTN_A, INPUT_PULLUP);
    pinMode(BTN_B, INPUT_PULLUP);
    pinMode(BTN_DOWN, INPUT_PULLUP);
    pinMode(VIBRA, OUTPUT);

    digitalWrite(VIBRA, LOW);

}

// Array and function to display button press on display
char buttonText[20] = "Hejsan";
void setDisplayText(char* buttonText, const char* newText, size_t bufferSize) {
   
    strncpy(buttonText, newText, bufferSize - 1);    // Change text on the display
    buttonText[bufferSize - 1] = '\0';  // null termination
}

void loop() {

    canvas.fillScreen(0x0000); // Clear canvas (not display)
     //print text and symbols
    static const unsigned char PROGMEM image_Space_bits[] = {0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0x00,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xe0,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x80,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0x00};
    static const unsigned char PROGMEM image_FaceNormal_bits[] = {0x00,0x00,0x00,0x00,0x3c,0x00,0x01,0xe0,0x7a,0x00,0x03,0xd0,0x7e,0x00,0x03,0xf0,0x7e,0x00,0x03,0xf0,0x7e,0x00,0x03,0xf0,0x3c,0x00,0x01,0xe0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x40,0x00,0x00,0x10,0x40,0x00,0x00,0x10,0x40,0x00,0x00,0x08,0x80,0x00,0x00,0x07,0x00,0x00};
    canvas.setTextColor(0xFFFF);
    canvas.setTextSize(1);
    canvas.setTextWrap(false);
    canvas.setCursor(46, 9);
    canvas.print("WOHOO!");
    canvas.setCursor(33, 46);
    canvas.print(buttonText);
    canvas.drawBitmap(32, 62, image_Space_bits, 65, 18, 0xFFFF);
    canvas.drawBitmap(49, yPos, image_FaceNormal_bits, 29, 14, 0xFFFF);

    // Update the y position
    yPos += direction;
    recWidth += 2;

    if (yPos >= upperBound || yPos <= lowerBound) {
        direction = -direction; // Reverse direction at the bounds
    }

    // Update ball position
    ballX += velX;
    ballY += velY;

    // Check for collisions
    if (ballX <= SQUARE_X + BALL_RADIUS || ballX >= SQUARE_X + SQUARE_W - BALL_RADIUS) {
        velX = -velX; // Reverse the horizontal velocity
    }
    if (ballY <= SQUARE_Y + BALL_RADIUS || ballY >= SQUARE_Y + SQUARE_H - BALL_RADIUS) {
        velY = -velY; // Reverse the vertical velocity
    }

    // Draw the ball at the new position
    canvas.drawCircle(ballX, ballY, BALL_RADIUS, 0xA800);

    //draw canvas
    display.drawRGBBitmap(0, 0, canvas.getBuffer(), canvas.width(), canvas.height());


    //Serial prints and display update for buttons and vibration testing
    if (!digitalRead(BTN_UP)) {
       setDisplayText(buttonText, "BTN_UP Pressed", 20); 
        Serial.println("Button UP pressed");        
    }

    else if (!digitalRead(BTN_LEFT)) {
        setDisplayText(buttonText, "BTN_LEFT pressed", 20);
        Serial.println("Button LEFT pressed");
     
    }
    else if (!digitalRead(BTN_RIGHT)) {
        setDisplayText(buttonText, "BTN_RIGHT Pressed", 20);
        Serial.println("Button RIGHT pressed");
    }
        
    else if (!digitalRead(BTN_START)) {
        setDisplayText(buttonText, "BTN_START Pressed", 20);
        Serial.println("Button START pressed");   
    }
   
    else if (!digitalRead(BTN_DOWN)) {
        setDisplayText(buttonText, "BTN_DOWN Pressed", 20);
        Serial.println("Button DOWN pressed");  
    }
    
    else if (!digitalRead(BTN_A)) {
        setDisplayText(buttonText, "BTN_A pressed", 20);
        Serial.println("Button A pressed Vibration ON");
        digitalWrite(VIBRA, HIGH);
    }
    else if (!digitalRead(BTN_B)) {
        setDisplayText(buttonText, "BTN_B Pressed", 20);
        Serial.println("Button B pressed Vibration OFF");
        digitalWrite(VIBRA, LOW);
    }
    else {
        setDisplayText(buttonText, "No buttons pressed", 20);
    }
}
