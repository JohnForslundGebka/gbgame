#ifndef GBGAME_IMAGES_H
#define GBGAME_IMAGES_H
#include <Arduino.h>

static constexpr const unsigned char PROGMEM image_light_bits[] = {0x20,0x04,0x13,0xc8,0x04,0x20,0x08,0x10,0xa9,0x15,0x09,0x90,0x09,0x10,0x24,0x24,0x42,0x42,0x01,0x00,0x03,0xc0,0x00,0x00,0x03,0xc0,0x00,0x00,0x01,0x80,0x00,0x00};
static constexpr const unsigned char PROGMEM image_hand_notice_bits[] = {0x0c,0x00,0x33,0x00,0xc0,0xfe,0x86,0x81,0x0a,0xff,0x33,0x20,0x03,0xe0,0x04,0x20,0x83,0xe0,0x64,0x40,0x1f,0x80};
static constexpr unsigned char PROGMEM image_music_fast_forward_bits[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x40,0x00,0xc0,0x60,0x00,0xb0,0x58,0x00,0x8c,0x46,0x00,0x83,0x41,0x80,0x8c,0x46,0x00,0xb0,0x58,0x00,0xc0,0x60,0x00,0x80,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
static constexpr unsigned char PROGMEM image_music_fast_backward_bits[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x80,0x03,0x01,0x80,0x0d,0x06,0x80,0x31,0x18,0x80,0xc1,0x60,0x80,0x31,0x18,0x80,0x0d,0x06,0x80,0x03,0x01,0x80,0x01,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
static constexpr unsigned char PROGMEM image_music_record_button_bits[] = {0x07,0xc0,0x18,0x30,0x20,0x08,0x43,0x84,0x4c,0x64,0x88,0x22,0x90,0x12,0x90,0x12,0x90,0x12,0x88,0x22,0x4c,0x64,0x43,0x84,0x20,0x08,0x18,0x30,0x07,0xc0,0x00,0x00};
static constexpr unsigned char PROGMEM image_hand_notice_bits_up[] = {0x18,0x00,0x28,0x00,0x28,0x00,0x28,0x00,0x28,0x00,0x2f,0x80,0x2a,0xc0,0x3a,0xa0,0x46,0xa0,0x5e,0xa0,0x91,0x60,0x88,0x20,0x44,0x20,0x44,0x40,0x20,0x40,0x30,0x80};
static constexpr unsigned char PROGMEM image_hand_notice_bits_left[] = {0x01,0xf8,0x02,0x26,0x07,0xc1,0x04,0x20,0x07,0xc0,0x04,0xcc,0xff,0x50,0x81,0x61,0x7f,0x03,0x00,0xcc,0x00,0x30};
static constexpr unsigned char PROGMEM image_Background_bits[] = {0x7f,0x80,0x00,0x00,0x00,0x00,0x00,0x07,0xff,0xff,0xff,0xf0,0x00,0x00,0x00,0x00,0x80,0xc0,0x00,0x00,0x00,0x00,0x00,0x0c,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0xbe,0x60,0x00,0x00,0x00,0x00,0x00,0x18,0xff,0xed,0xaa,0x8c,0x00,0x00,0x00,0x00,0x81,0x3f,0xff,0xff,0xff,0xff,0xff,0xf1,0x00,0x00,0x00,0x47,0xff,0xff,0xff,0xfe,0xbc,0x80,0x00,0x00,0x00,0x00,0x00,0x02,0x6d,0x57,0xff,0x20,0x00,0x00,0x00,0x01,0x82,0x7f,0xff,0xff,0x55,0x7f,0xff,0xfc,0x80,0x00,0x00,0x9f,0xff,0xff,0xff,0xd5,0xf9,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x1f,0xff,0xfe,0x40,0x00,0x00,0x00,0x01,0x7c,0xff,0xff,0xff,0xff,0xaa,0xbf,0xfe,0x3f,0xff,0xff,0x36,0xff,0xff,0xff,0xad,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x00,0x01,0x80,0x00,0x00,0x00,0x01,0x03,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x00,0x00,0x7f,0xff,0xff,0xff,0xfe};
static constexpr unsigned char PROGMEM image_Space_bits[] = {0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0x00,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xe0,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x80,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0x00};
static constexpr unsigned char PROGMEM image_Background_1_bits[] = {0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x00,0x00,0x7f,0xff,0xff,0xff,0xfe,0x03,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x00,0x01,0x80,0x00,0x00,0x00,0x01,0x7c,0xff,0xff,0xff,0xff,0xaa,0xbf,0xfe,0x3f,0xff,0xff,0x36,0xff,0xff,0xff,0xad,0xf9,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x1f,0xff,0xfe,0x40,0x00,0x00,0x00,0x01,0x82,0x7f,0xff,0xff,0x55,0x7f,0xff,0xfc,0x80,0x00,0x00,0x9f,0xff,0xff,0xff,0xd5,0xbc,0x80,0x00,0x00,0x00,0x00,0x00,0x02,0x6d,0x57,0xff,0x20,0x00,0x00,0x00,0x01,0x81,0x3f,0xff,0xff,0xff,0xff,0xff,0xf1,0x00,0x00,0x00,0x47,0xff,0xff,0xff,0xfe,0xbe,0x60,0x00,0x00,0x00,0x00,0x00,0x18,0xff,0xed,0xaa,0x8c,0x00,0x00,0x00,0x00,0x80,0xc0,0x00,0x00,0x00,0x00,0x00,0x0c,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x7f,0x80,0x00,0x00,0x00,0x00,0x00,0x07,0xff,0xff,0xff,0xf0,0x00,0x00,0x00,0x00};
static constexpr unsigned char PROGMEM image_FaceCharging_bits[] = {0x02,0x00,0x00,0x40,0x06,0x00,0x00,0xc0,0x0c,0x00,0x01,0x80,0x18,0x00,0x03,0x00,0x3f,0x00,0x07,0xe0,0x3f,0x00,0x07,0xe0,0x06,0x00,0x00,0xc0,0x0c,0x00,0x01,0x80,0x18,0x00,0x03,0x00,0x10,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x00,0x00,0x10,0x40,0x00,0x00,0x0f,0x80,0x00};
static constexpr unsigned char PROGMEM image_Smile_bits[] = {0x03,0xf0,0x00,0x0f,0xfc,0x00,0x1f,0xfe,0x00,0x3f,0xff,0x00,0x7f,0xff,0x80,0x7f,0xff,0x80,0xff,0xff,0xc0,0xf3,0xf3,0xc0,0xe1,0xe1,0xc0,0xe1,0xe1,0xc0,0xf3,0xf3,0xc0,0xff,0xff,0xc0,0x7f,0xff,0x80,0x7d,0xef,0x80,0x3e,0x1f,0x00,0x1f,0xfe,0x00,0x0f,0xfc,0x00,0x03,0xf0,0x00};
static constexpr unsigned char PROGMEM image_Restoring_bits[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xfe,0x00,0x00,0x00,0x07,0x01,0x80,0x00,0x00,0x18,0x00,0x40,0x00,0x00,0x20,0x7e,0x40,0x00,0x00,0x43,0xff,0xc0,0x00,0x00,0x87,0x81,0x80,0x00,0x00,0x8c,0x00,0x02,0x00,0x01,0x10,0x00,0x05,0x00,0x01,0x10,0x00,0x08,0x80,0x02,0x20,0x00,0x10,0x40,0x02,0x20,0x00,0x20,0x20,0x04,0x40,0x00,0x40,0x10,0x04,0x40,0x00,0x80,0x08,0x04,0x40,0x00,0xf8,0xf8,0x7c,0x7c,0x00,0xf8,0xf8,0x40,0x04,0x00,0x08,0x80,0x60,0x0c,0x00,0x08,0x80,0x70,0x1c,0x00,0x11,0x00,0x38,0x38,0x00,0x11,0x00,0x1c,0x70,0x00,0x22,0x00,0x0e,0xe0,0x00,0x22,0x00,0x07,0xc0,0x00,0xc4,0x00,0x03,0x80,0x00,0x84,0x00,0x00,0x06,0x07,0x08,0x00,0x00,0x09,0xf8,0x10,0x00,0x00,0x08,0x00,0x70,0x00,0x00,0x0e,0x03,0xe0,0x00,0x00,0x07,0xff,0x80,0x00,0x00,0x01,0xfc,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
static constexpr unsigned char PROGMEM image_cloud_upload_2_bits[] = {0x00,0x00,0x00,0x07,0xc0,0x00,0x08,0x20,0x00,0x10,0x10,0x00,0x30,0x08,0x00,0x40,0x0e,0x00,0x80,0x01,0x00,0x80,0x00,0x80,0x41,0x00,0x80,0x33,0x9f,0x00,0x07,0xc0,0x00,0x01,0x00,0x00,0x03,0x00,0x00,0x02,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00};
static constexpr unsigned char PROGMEM image_envelope_bits[] = {0x00,0x00,0x00,0x7f,0xff,0x00,0xc0,0x01,0x80,0xc0,0x01,0x80,0xa0,0x02,0x80,0x90,0x04,0x80,0x88,0x08,0x80,0x84,0x10,0x80,0x82,0x20,0x80,0x85,0xd0,0x80,0x88,0x08,0x80,0x90,0x04,0x80,0xa0,0x02,0x80,0xc0,0x01,0x80,0x7f,0xff,0x00,0x00,0x00,0x00};
static constexpr unsigned char PROGMEM image_hour_glass_75_bits[] = {0xff,0xe0,0x40,0x40,0x40,0x40,0x51,0x40,0x5f,0x40,0x2e,0x80,0x15,0x00,0x0a,0x00,0x0a,0x00,0x11,0x00,0x24,0x80,0x44,0x40,0x4e,0x40,0x5f,0x40,0x7f,0xc0,0xff,0xe0};
static constexpr unsigned char PROGMEM image_Cry_dolph_bits[] = {0x00,0x00,0x1f,0xff,0x80,0x00,0x00,0x00,0x00,0x7f,0xff,0xf0,0x00,0x00,0x00,0x01,0xe0,0x00,0x7c,0x00,0x00,0x00,0x07,0x80,0x00,0x0f,0x00,0x00,0x00,0x0e,0x00,0x00,0x03,0x80,0x00,0x00,0x18,0x00,0x00,0x00,0xc0,0x00,0x00,0x30,0x00,0x00,0x00,0x60,0x00,0x00,0x60,0x00,0x00,0x00,0x30,0x00,0x00,0xc0,0x00,0x00,0x00,0x18,0x00,0x01,0x80,0x00,0x00,0x00,0x18,0x00,0x01,0x80,0x00,0x00,0x00,0x0c,0x00,0x03,0x00,0x00,0x00,0x00,0x0c,0x00,0x03,0x00,0x00,0x00,0x00,0x06,0x00,0x06,0x00,0x00,0x00,0x00,0x06,0x00,0x06,0x00,0x00,0x00,0x00,0x03,0x00,0x06,0x00,0x00,0x00,0x00,0x03,0x00,0x0c,0x00,0x00,0x00,0x00,0x03,0x00,0x0c,0x00,0x00,0x00,0x00,0x01,0x00,0x0c,0x00,0x00,0x00,0x00,0x01,0x80,0x18,0x00,0x00,0x04,0x00,0x01,0x80,0x18,0x00,0x00,0x78,0x00,0x11,0x80,0x18,0x00,0x00,0x00,0x00,0x0f,0x80,0x30,0x00,0x00,0x00,0x00,0x01,0x80,0x30,0x00,0xe0,0x00,0x00,0x01,0x80,0x30,0x05,0xf8,0x00,0x00,0x07,0x80,0x30,0x0a,0xff,0xe0,0x00,0x0f,0x80,0x30,0x05,0x7f,0xe0,0x00,0x0f,0x80,0x30,0x0a,0xff,0xe0,0x0d,0xc7,0x80,0x30,0x05,0x9f,0x80,0x40,0x21,0x80,0x60,0x03,0x10,0x00,0x00,0x01,0x80,0x60,0x02,0x20,0x00,0x00,0x01,0x80,0x60,0x02,0x20,0x00,0x00,0x05,0x80,0x60,0x02,0x40,0x00,0x00,0x03,0x80,0x60,0x01,0x80,0x00,0x00,0x01,0x80,0x60,0x00,0x00,0x00,0x00,0x00,0xc0,0x60,0x00,0x01,0xe0,0x00,0x00,0x60,0x60,0x00,0x06,0x18,0x00,0x00,0x30,0xc0,0x01,0x08,0x06,0x00,0x00,0x18,0xc0,0x01,0x00,0x01,0x00,0x00,0x0c,0xc0,0x00,0x80,0x00,0x80,0x00,0x0c,0xc0,0x00,0x00,0x00,0x60,0x00,0x0c,0xc0,0x02,0x00,0x00,0x18,0x00,0x06,0xc0,0x02,0x00,0x58,0x06,0x00,0x06,0xc0,0x10,0x00,0xae,0x01,0x80,0x06,0xc0,0x00,0x00,0x17,0x80,0x70,0x06,0xc0,0x02,0x02,0xab,0xe0,0x0f,0xfc,0xc0,0x00,0x00,0x05,0xfc,0x00,0x0c,0xc0,0x02,0x00,0xaa,0xff,0x80,0x18,0xc0,0x12,0x00,0x01,0x7f,0xf0,0xf0,0xc0,0x12,0x00,0x2a,0xbf,0xff,0xe0,0xc0,0x12,0x00,0x01,0x5f,0xef,0x00,0xc0,0x0c,0x00,0x0a,0xaf,0xd6,0x00};
#endif //GBGAME_IMAGES_H
