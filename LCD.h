#ifndef LCD_h
#define LCD_h

#include "Print.h"
#include "Arduino.h"
#include <inttypes.h>

//INSTRUCTIONS

//https://www.sparkfun.com/datasheets/LCD/HD44780.pdf

#define CLEAR_DISPLAY 0x01
#define RETURN_HOME 0x02 //2ms

//Entry mode set
#define ENTRY_MODE 0x04
#define INCREMENT 0x02
#define DECREMENT 0x00
#define DISPLAY_SHIFT_ON 0x01
#define DISPLAY_SHIFT_OFF 0x00

//Display control
#define DISPLAY_CONTROL 0x08
#define DISPLAY_ON 0x04
#define DISPLAY_OFF 0x00
#define CURSOR_ON 0x02
#define CURSOR_OFF 0x00
#define BLINKING_ON 0x01
#define BLINKING_OFF 0x00

//Display or cursor shift
#define DISPLAY_CURSOR_SHIFT 0x10
#define DISPLAY_SHIFT 0x08
#define CURSOR_SHIFT 0x00
#define SHIFT_RIGHT 0x04
#define SHIFT_LEFT 0x00

//Function set
#define FUNCTION_SET 0x20
#define EIGHT_BITS 0x10
#define FOUR_BITS 0x00
#define TWO_LINE 0x08
#define ONE_LINE 0x00
#define FIVE_TEN_FONT 0x04
#define FIVE_EIGHT_FONT 0x00

//Set CGRAM or DDRAM address
#define SET_CGRAM 0x40
#define SET_DDRAM 0x80

class LCD : public Print {
public:
	LCD(uint8_t rs, uint8_t rw, uint8_t en, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7); //4 bit mode
	LCD(uint8_t rs, uint8_t rw, uint8_t en, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7); //8 bit mode
	void clear();
	void home();
	void displayOn();
	void displayOff();
	void cursorOn();
	void cursorOff();
	void blinkOn();
	void blinkOff();
	void begin(uint8_t, uint8_t);
	void setCursor(uint8_t, uint8_t);
	void setCustomChar(uint8_t, uint8_t[]);
	virtual size_t write(uint8_t);
	using Print::write;
private:
	void command(uint8_t);
	void send(uint8_t);
	void write4(uint8_t);
	void write8(uint8_t);
	uint8_t rs_pin; // LOW: command.  HIGH: character.
	uint8_t rw_pin; // LOW: write to LCD.  HIGH: read from LCD.
	uint8_t en_pin; // activated by a HIGH pulse.
	uint8_t data_pins[8];
	uint8_t display_mode;
	uint8_t display_control;
	uint8_t display_function;
};

#endif
