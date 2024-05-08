#ifndef GBGAME_MACROS_H
#define GBGAME_MACROS_H
// Color definitions
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

//pins used for SPI communication by the DisplayManager
#define DC_PIN   15   // Data/Command
#define CS_PIN   14   // Chip Select, can use any GPIO except A6/A7
#define RST_PIN  9    // Reset

//Pins used by the ultrasonic sensor
#define TRIG_PIN 16    //D16
#define ECHO_PIN 17    //D17

//flags used as conditions for threads
#define SCREEN_UPDATE_FLAG  (1UL << 1)
#define ADVANCE_GAME_FLAG  (1UL << 2)

#define MAIN_MENU (1UL << 1)
#define DISTANCE_GAME (1UL << 2)


#endif //GBGAME_MACROS_H
