#ifndef SSD1306_COMMANDS
#define SSD1306_COMMANDS

uint8_t DISPLAY_INIT[25];
void send_cmd(uint8_t commands[], size_t len);
void send_data(uint8_t buffer[8][128]);
#endif
