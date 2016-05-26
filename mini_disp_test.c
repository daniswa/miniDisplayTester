





#include <avr/io.h>
#include <util/delay.h>

const int set = 0xFF;
const int clr = 0x00;
const int dataClkClr = 0x00;
const int dataClkSet = 0x5A;
const int dataSet = 0x08;
const int clkSet = 0x02;
const int data2Set = 0x10;
const int clk2Set = 0x40;

void allOn();
void allOff();
void initDisp();
void sendDigData();
void sendDispData(int);
void sendDispDp(int);
void sendDispSegs();
void miniDispMultiplex();

const int num[10][8] = {{0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x08},
						{0x08,0x00,0x08,0x08,0x08,0x00,0x00,0x08},
						{0x08,0x00,0x08,0x00,0x08,0x00,0x08,0x08},
						{0x00,0x08,0x08,0x00,0x00,0x00,0x08,0x08},
						{0x08,0x08,0x08,0x00,0x08,0x00,0x08,0x00},
						{0x08,0x08,0x08,0x08,0x08,0x00,0x08,0x00},
						{0x08,0x00,0x00,0x00,0x00,0x00,0x08,0x08},
						{0x08,0x08,0x08,0x08,0x08,0x00,0x08,0x08},
						{0x08,0x08,0x08,0x00,0x08,0x00,0x08,0x08},
						{0x08,0x08,0x00,0x08,0x08,0x00,0x08,0x08}};
							
const int dot[2][8] = {{0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x00},
					   {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}};
						   
const int segments[8][8] = {{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08},
							{0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
							{0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00},
							{0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00},
							{0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x00},
							{0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00},
							{0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x00},
							{0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00}};

int main(void){
   _delay_ms(500);
   DDRD = set;
   void initDisp();

   while(1){
	   PORTD = 0x01;

	   if(PIND0 == 0){
		   miniDispMultiplex();
	   }
	   int i;
	   int j;
	   int k;
	   allOn();
	   _delay_ms(3000);
	   allOff();
	   _delay_ms(1000);
		sendDispSegs();
		sendDigData();

		for(i = 0;i < 10;i++){
			sendDispData(i);
		}

		for(j = 0;j < 3;j++){

			for(k = 0;k < 2;k++){
				sendDispDp(k);
			}
		}
	}
}

void initDisp(){
	int j = 0;
	int k = 0;
	int l = 0;
	PORTD = dataClkClr;
	_delay_us(1);
	PORTD = dataSet;
	_delay_us(1);
	PORTD = dataClkSet;
	_delay_us(1);
	PORTD = dataSet;
	_delay_us(1);

	for(j = 0;j < 4;j++){

		for(k = 0;k < 8;k++){
			PORTD = dataClkClr;
			_delay_us(1);
			PORTD = clkSet;
			_delay_us(1);
			PORTD = dataClkClr;
		}
	}

	for(l = 0;l < 3;l++){
		_delay_us(1);
		PORTD = clkSet;
		_delay_us(1);
		PORTD = dataClkClr;
	}
	_delay_ms(200);
}

void allOn(){
	int i;

	for(i = 0;i < 36;i++){
		PORTD = dataClkClr;
		_delay_us(1);
		PORTD = dataSet;
		_delay_us(1);
		PORTD = dataClkSet;
		_delay_us(1);
		PORTD = dataSet;
	}
}

void allOff(){
	int i;
	PORTD = dataClkClr;
	_delay_us(1);
	PORTD = dataSet;
	_delay_us(1);
	PORTD = dataClkSet;
	_delay_us(1);
	PORTD = dataSet;
	_delay_us(1);

	for(i = 0;i < 35;i++){
		PORTD = dataClkClr;
		_delay_us(1);
		PORTD = clkSet;
		_delay_us(1);
		PORTD = dataClkClr;
	}
}

void sendDispSegs(){
	int i;
	int j;
	int k;
	int l;
	int m;
	int n;

	for(i = 1;i < 5;i++){

		for(j = 0;j < 8;j++){
			PORTD = dataClkClr;
			_delay_us(1);
			PORTD = dataSet;
			_delay_us(1);
			PORTD = dataClkSet;
			_delay_us(1);
			PORTD = dataSet;
			_delay_us(1);

			for(k = 4;k > 0;k--){

				if(k == i){

					for(l = 7;l >= 0;l--){
						PORTD = (dataClkClr | segments[j][l]);
						_delay_us(1);
						PORTD = (clkSet | segments[j][l]);
						_delay_us(1);
						PORTD = (dataClkClr | segments[j][l]);
					}
				}else{

					for(m = 0;m < 8;m++){
						PORTD = dataClkClr;
						_delay_us(1);
						PORTD = clkSet;
						_delay_us(1);
						PORTD = dataClkClr;
					}
				}
			}

			for(n = 0;n < 3;n++){
				PORTD = dataClkClr;
					_delay_us(1);
					PORTD = clkSet;
					_delay_us(1);
					PORTD = dataClkClr;
			}
			_delay_ms(500);
		}
	}
}

void sendDigData(){
	int i;
	int j;
	int k;
	int l;
	int m;
	int n;

	for(i = 1;i < 5;i++){

		for(j = 0;j < 10;j++){
			PORTD = dataClkClr;
			_delay_us(1);
			PORTD = dataSet;
			_delay_us(1);
			PORTD = dataClkSet;
			_delay_us(1);
			PORTD = dataSet;
			_delay_us(1);

			for(k = 4;k > 0;k--){

				if(k == i){

					for(l = 0;l < 8;l++){
						PORTD = (dataClkClr | num[j][l]);
						_delay_us(1);
						PORTD = (clkSet | num[j][l]);
						_delay_us(1);
						PORTD = (dataClkClr | num[j][l]);
					}
				}else{

					for(m = 0;m < 8;m++){
						PORTD = dataClkClr;
						_delay_us(1);
						PORTD = clkSet;
						_delay_us(1);
						PORTD = dataClkClr;
					}
				}
			}

			for(n = 0;n < 3;n++){
				PORTD = dataClkClr;
				_delay_us(1);
				PORTD = clkSet;
				_delay_us(1);
				PORTD = dataClkClr;
			}
			_delay_ms(500);
		}
	}
}

void sendDispData(int value){
	int j = 0;
	int k = 0;
	int l = 0;
	PORTD = dataClkClr;
	_delay_us(1);
	PORTD = dataSet;
	_delay_us(1);
	PORTD = dataClkSet;
	_delay_us(1);
	PORTD = dataSet;
	_delay_us(1);

	for(j = 0;j < 4;j++){

		for(k = 0;k < 8;k++){
			PORTD = (dataClkClr | num[value][k]);
			_delay_us(1);
			PORTD = (clkSet | num[value][k]);
			_delay_us(1);
			PORTD = (dataClkClr | num[value][k]);
		}
	}

	for(l = 0;l < 3;l++){
		PORTD = dataClkClr;
		_delay_us(1);
		PORTD = clkSet;
		_delay_us(1);
		PORTD = dataClkClr;
	}
	_delay_ms(500);
}

void sendDispDp(int value){
	int j = 0;
	int k = 0;
	int l = 0;
	PORTD = dataClkClr;
	_delay_us(1);
	PORTD = dataSet;
	_delay_us(1);
	PORTD = dataClkSet;
	_delay_us(1);
	PORTD = dataSet;
	_delay_us(1);

	for(j = 0;j < 4;j++){

		for(k = 0;k < 8;k++){
			PORTD = (dataClkClr | dot[value][k]);
			_delay_us(1);
			PORTD = (clkSet | dot[value][k]);
			_delay_us(1);
			PORTD = (dataClkClr | dot[value][k]);
		}
	}

	for(l = 0;l < 3;l++){
		PORTD = dataClkClr;
		_delay_us(1);
		PORTD = clkSet;
		_delay_us(1);
		PORTD = dataClkClr;
	}
	_delay_ms(250);
}

void miniDispMultiplex(){
	int j = 0;
	int k = 0;
	int l = 0;
	int m = 0;
	PORTD = dataClkClr;
	_delay_us(1);
	PORTD = dataSet & data2Set;
	_delay_us(1);
	PORTD = dataClkSet;
	_delay_us(1);
	PORTD = dataSet & data2Set;
	_delay_us(1);

	for(j = 0;j < 4;j++){

		for(k = 0;k < 8;k++){
			PORTD = (dataClkClr | num[1][k] | num[3][k]);
			_delay_us(1);
			PORTD = (clkSet | num[1][k] | num[3][k]);
			_delay_us(1);
			PORTD = (dataClkClr | num[1][k] | num[3][k]);
		}

		for(k = 0;k < 8;k++){
			PORTD = (dataClkClr | num[2][m] | num[4][m]);
			_delay_us(1);
			PORTD = (clk2Set | num[2][m] | num[4][m]);
			_delay_us(1);
			PORTD = (dataClkClr | num[2][m] | num[4][m]);
		}
	}

	for(l = 0;l < 3;l++){
    	PORTD = dataClkClr;
    	_delay_us(1);
    	PORTD = dataSet & data2Set;
    	_delay_us(1);
    	PORTD = dataClkClr;
    }
    _delay_ms(250);
}