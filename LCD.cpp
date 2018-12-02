#include "LCD.h"


LCD::LCD(uint8_t rs, uint8_t rw, uint8_t en, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) {
	rs_pin = rs;
	rw_pin = rw;
	en_pin = en;
	data_pins[0] = d4;
	data_pins[1] = d5;
	data_pins[2] = d6;
	data_pins[3] = d7;

	display_function = FUNCTION_SET | FOUR_BITS;
	display_control = DISPLAY_CONTROL;
	display_mode = ENTRY_MODE;
}

void LCD::begin(uint8_t row, uint8_t col) {
	if(row == 1) {
		display_function |= ONE_LINE;
	}
	else if(row==2) {
		display_function |= TWO_LINE;
	}

	pinMode(rs_pin, OUTPUT);
  	pinMode(rw_pin, OUTPUT);
  	pinMode(en_pin, OUTPUT);

  	if(!(display_function & EIGHT_BITS)) {

	  	for(int i=0;i<4;i++) {
	  		pinMode(data_pins[i], OUTPUT);
	  	}

	  	//Initialize 4-bit interface
	  	delay(55);
	  	write4(0x03);
		delay(5);
		write4(0x03);
		delay(5);
		write4(0x03);
		delay(5);
		write4(0x02);

	}
	else {

		for(int i=0;i<8;i++) {
	  		pinMode(data_pins[i], OUTPUT);
	  	}

	  	//Initialize 8-bit interface
		delay(55);
		write8(0x30);
		delay(5);
		write8(0x30);
		delay(5);
		write8(0x30);
	}

	display_function |= FIVE_EIGHT_FONT;
	display_control |= DISPLAY_ON | CURSOR_OFF | BLINKING_OFF;
	display_mode |=  INCREMENT | DISPLAY_SHIFT_OFF;
	command(display_function);
	command(display_control);
	clear();
	command(display_mode);
	home();
}

void LCD::setCursor(uint8_t row, uint8_t col) {
	if(row==0) {
		command(SET_DDRAM + col);
	}
	if(row==1) {
		command(SET_DDRAM + 0x40 + col);
	}
}

void LCD::command(uint8_t value) {
	if(!(display_function & EIGHT_BITS)) {
		digitalWrite(rs_pin, LOW);
		digitalWrite(rw_pin, LOW);
		delay(1);
		write4(value>>4);
		delay(1);
		write4(value);
		delay(1);
	}
	else {
		digitalWrite(rs_pin, LOW);
		digitalWrite(rw_pin, LOW);
		delay(1);
		write8(value);
		delay(1);
	}
}

void LCD::send(uint8_t value) {
	if(!(display_function & EIGHT_BITS)) {
		digitalWrite(rs_pin, HIGH);
		digitalWrite(rw_pin, LOW);
		delay(1);
		write4(value>>4);
		delay(1);
		write4(value);
		delay(1);
	}
	else {
		digitalWrite(rs_pin, HIGH);
		digitalWrite(rw_pin, LOW);
		delay(1);
		write8(value);
		delay(1);
	}
}


void LCD::write4(uint8_t value) {
	digitalWrite(en_pin, HIGH);
	delay(1);
	for(int i=0; i<4; i++) {
		digitalWrite(data_pins[i], (value>>i) & 0x01);
	}
	digitalWrite(en_pin, LOW);
	delay(1);
}

void LCD::write8(uint8_t value) {
	digitalWrite(en_pin, HIGH);
	delay(1);
	for(int i=0; i<8; i++) {
		digitalWrite(data_pins[i], (value>>i) & 0x01);
	}
	digitalWrite(en_pin, LOW);
	delay(1);
}

void LCD::clear() {
	command(CLEAR_DISPLAY);
	delay(3);
}

void LCD::home() {
	command(RETURN_HOME);
	delay(3);
}

inline size_t LCD::write(uint8_t value) {
	send(value);
	return 1;
}