/*
in
dzwiêk(sygna³)...pc4
ruch ............pc2
siat³o (ADC).....pc3
przycisk +.......pb4
przycick -.......pb3
przycisk opcja...pb2
przycisk menu....pb1
out
stycznik.........pc5
led red (czeka)..pd4
led orange(menu).pb6
led 1............pb0
led 2............pd7
led 3............pd6
led 4............pd5
led 5............pb5

ADC..............pc3
*******obs³uga*******
menu
menu  opcja_wyboru +/góra -/do_do³u
 O         O          O       O

1-tryb
2-czas oczekiwania na dwrugie klaniêcie
3-czas w trybie dzia³ania jako czujnik ruchu
4-próg oswietlenia
5-si³a klasniêcia
6-liczba klasniêæ
**podmenu**
add 3)1min 5min 10min 20min 30min 60min

******tryb czuwania*******
wciskaj¹c guzik od 2 do 4 w³¹cza pokazywanie sygna³ów
menu  pokarz_sygna³_mic poka¿_syg_oswietlenia pokarz_syg_ruch
 O         O                O                          O
*/
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
//in
#define sygnal (1<<PC4)
#define ruch (1<<PC2)
#define wartoscp (1<<PB4)
#define wartoscm (1<<PB3)
#define opcja (1<<PB2)
#define menu_guzik (1<<PB1)
//out
#define stycznik (1<<PC5)

#define czeka (1<<PD4)
#define menu_led (1<<PB6)
#define led1 (1<<PB0)
#define led2 (1<<PD7)
#define led3 (1<<PD6)
#define led4 (1<<PD5)
#define led5 (1<<PB7)
//
#define l1_s PORTB ^= led1
#define l1_on PORTB |= led1
#define l1_off PORTB &= ~led1
#define l3_on PORTD |= led3
#define l3_off PORTD &= ~led3
#define l5_on PORTB |= led5
#define l5_off PORTB &= ~led5
#define czeka_swap PORTD ^= czeka
#define czeka_on PORTD |= czeka
#define czeka_off PORTD &= ~czeka
#define stycznik_swap PORTC ^= stycznik
#define stycznik_on PORTC |= stycznik
#define stycznik_off PORTC &= ~stycznik

//zmienna pomocnicza-licznik u¿ywana w przerwaniu
//volatile uint8_t wykrycie_ruchu;
volatile uint16_t ton,cnt=0;
volatile uint8_t tryb=5;
volatile uint8_t tryb_chwilowy;
volatile uint8_t stan=0;
volatile uint8_t czujniki[3];
//definicja pocz¹tkowej wartoœci timera
#define timer_start 4 //31 zliczen na s

uint8_t klasniecie(uint8_t t, uint8_t stan_koncowy, uint8_t l_klasniec);
uint8_t klawisz_on(uint8_t klawisz);
uint8_t klawisz_onc(uint8_t klawisz);
uint8_t klawisz_sygnal(uint8_t klawisz);
uint8_t menu(uint8_t *t, uint8_t *t_on, uint8_t *swiatlo, uint8_t *l_klasniec);
uint8_t podmenu(uint8_t *x, uint8_t min, uint8_t max, uint8_t res);
uint16_t czas_dzialania(uint8_t t_on);
uint16_t prog_swiatla(uint8_t swiatlo);
//void wzmacniacz(uint8_t mikrofon);
void diody(uint8_t nr);
void diody_off(void);


int main(void){
	uint8_t t=3,t_on=3,swiatlo=3,l_klasniec=2;//,mikrofon=3;
	uint16_t prog,spr=0;
	prog=prog_swiatla(swiatlo);
	ton=czas_dzialania(t_on)*31;
	tryb_chwilowy=tryb;
	//1=klaskacz 2=czujnik ruchu z wyl przez klaniêcie
	//3=czujnik ruchu czasowe w³
//######## obs³uga przetwornika ADC #############
ADMUX |= (1<<REFS0);// | (1<<REFS1);
ADMUX |= (1<<MUX1) | (1<<MUX0);
ADCSRA |= (1<<ADEN) | (1<<ADPS1) | (1<<ADPS2);
//######## konfiguracja timera ##################
TIMSK |= (1<<TOIE0);           //Przerwanie overflow (przepe³nienie timera)
TCCR0 |= (1<<CS02) | (1<<CS00); // Ÿród³em CLK, preskaler 1024
TCNT0 = timer_start;//          //Pocz¹tkowa wartoœæ licznika
sei();//Globalne uruchomienie przerwañ
//###############################################
DDRC |= (stycznik);
DDRB |= (led1 | led5 | menu_led);
DDRD |= (led3 | led4 | led2 | menu_led | czeka);
PORTB |= (menu_guzik | opcja | wartoscp | wartoscm);
//PORTC |= sygnal;
//wzmacniacz(mikrofon);
czujniki[0]=1;
czujniki[1]=1;
czujniki[2]=1;
while(1){
	//stycznik_swap;
	//PORTB ^= led1;
	//_delay_ms(z++);
	/*
	if (tryb_chwilowy == 1){
       PORTB |=led2;
	}else{
		PORTB &= ~led2;
	}
	if (stan == 1){
       PORTB |=led1;
	}else{
		PORTB &= ~led1;
	}
	*/

/////////////////////////////
	if (klawisz_on(menu_guzik)){
		menu(&t,&t_on,&swiatlo,&l_klasniec);
		diody_off();
		//wzmacniacz(mikrofon);
		tryb_chwilowy=tryb;
		prog=prog_swiatla(swiatlo);//750-990
		ton=czas_dzialania(t_on)*31;
		tryb_chwilowy=tryb;
		cnt=0;
		if (stan == 0){
			tryb_chwilowy=tryb;
		}
		_delay_ms (200);
	}
/////////////////////////////

/////////////////////////////
	if (!klawisz_sygnal(sygnal)){
		if ( (czujniki[0] == 1) ){
			l1_on;
			}else{
				l1_off;
			}
		if ((tryb_chwilowy == 1) && (!(tryb == 1) && !(tryb == 3))){
			switch (stan){
				case 1:
					klasniecie(t,0,l_klasniec);
					break;
				case 0:
					klasniecie(t,0,l_klasniec);
					tryb_chwilowy = tryb;
					break;
			}
		}
		if ((stan == 1) && !(tryb == 3)){
				klasniecie(t,0,l_klasniec);
		}
		//l1_off;
	}
///////////////////

	if (!(swiatlo == 6)){
		ADCSRA |= (1<<ADSC);
		while (ADCSRA & (1<<ADSC));
	}

	if (stan ==0 ){
		if ((tryb > 3) && ((tryb_chwilowy == 1) && (ADC<prog))){
				if(spr == 0){
					cnt=0;
					spr=1;
				}else if (cnt>18600){//10min 31*60*10
					tryb_chwilowy=tryb;
					spr = 0;
				}
		}else{
			spr=0;
		}
/////////////////////////////
	if ((swiatlo == 6) || (ADC>prog)){
		if (!klawisz_sygnal(sygnal)){
			klasniecie(t,1,l_klasniec);
			tryb_chwilowy=1;
		}
/////////////////////////////
	if (!klawisz_onc(ruch)){
		if ((tryb_chwilowy == 2) || (tryb_chwilowy == 4)){
			stycznik_on;
			stan=1;
			tryb_chwilowy=1;
		}
/////////
		if (tryb == 3){
			stycznik_on;
			cnt=0;
			stan=1;
			//odliczanie od nowa jeli ruch
		}
/////////
		if (tryb_chwilowy == 5){
			stycznik_on;
			stan=1;
			cnt=0;
			tryb_chwilowy=1;

			//odliczanie
			//odliczanie od nowa jeli ruch
		}
	}
/////////////////////////////
	}
	}//stan ==0

/////////////////////////////
	if ((!klawisz_onc(ruch)) && ((tryb == 5) && stan == 1)){
		//wykrycie_ruchu=0;
		cnt=0;
	}

/////////////////////////////
	//diody_off();
	if ( (czujniki[0] == 1) && (!klawisz_sygnal(sygnal))){
		l1_on;
		}else{
			l1_off;
		}
	if ( (czujniki[2] == 1) && (!klawisz_onc(ruch))){
		l5_on;
		}else{
			l5_off;
		}
	if (czujniki[1]==1 && (ADC>(prog))){
		l3_on;
	}else{
		l3_off;
	}

	/////////////////////////////
		//diody_off();
		if (klawisz_on(opcja)){
			if (czujniki[0]==1){
				czujniki[0]=0;
				l1_off;
			}else{
				czujniki[0]=1;
			}
			_delay_ms(200);
		}
		if (klawisz_on(wartoscm)){
			if (czujniki[1]==1){
				czujniki[1]=0;
				l3_off;
			}else{
				czujniki[1]=1;
			}
			_delay_ms(200);
		}
		if (klawisz_on(wartoscp)){
			if (czujniki[2]==1){
				czujniki[2]=0;
				l5_off;
			}else{
				czujniki[2]=1;
			}
			_delay_ms(200);
		}

}
}

//############ Procedura obs³ugi przerwania od przepe³nienia timera ############
ISR(TIMER0_OVF_vect)
{
  TCNT0 = timer_start;          //Pocz¹tkowa wartoœæ licznika
  //cnt=(cnt+1)*wykrycie_ruchu;     //zwiêksza zmienn¹ licznik
  cnt++;
  if(((cnt==(ton) && (stan == 1))) && ((tryb==3) || (tryb == 5)))  //jeœli 31 przerwania (czyli ok 1 s)
  {
    stycznik_off; //suma modulo 2 (XOR) stanu poprzedniego
    //PORTB ^= led1;
    cnt=0;     //zeruje zmienn¹ licznik
    stan = 0;
    tryb_chwilowy=tryb;
  }
  //wykrycie_ruchu=1;
}
//##############################################################################

uint16_t prog_swiatla(uint8_t swiatlo){
	switch (swiatlo){
	case 1:
		return 400;
		break;
	case 2:
		return 500;
		break;
	case 3:
		return 600;
		break;
	case 4:
		return 850;
		break;
	case 5:
		return 950;
		break;
	case 6:
		return 2000;
		break;
	}
	return 2000;
}

uint8_t klasniecie(uint8_t t, uint8_t stan_koncowy, uint8_t l_klasniec){
	//diody_off();
	if ( (czujniki[0] == 1) ){
		l1_on;
		}else{
			l1_off;
		}
	if (l_klasniec == 2){
		_delay_ms (50);
		czeka_swap;
		for (int i=1;i<=t*100;i++){
			_delay_ms (10);
			if (!klawisz_sygnal(sygnal)){
				switch (stan_koncowy){
					case 1:
						stycznik_on;
						break;
					case 0:
						stycznik_off;
						break;
				}
				stan=stan_koncowy;
				czeka_off;
				i=t*1000;
				_delay_ms (200);
			}
		}
		czeka_off;
	}else{
		switch (stan_koncowy){
			case 1:
				stycznik_on;
				break;
			case 0:
				stycznik_off;
				break;
		}
		_delay_ms (200);
		stan=stan_koncowy;
	}
	cnt=0;
	l1_off;
	_delay_ms (300);
	return 0;
}

void diody_off(){
PORTB &= ~(led1 | led5);
PORTD &= ~(led3 | led4 | led2);
}

void diody(uint8_t nr){
	switch(nr){
				case 1:
					diody_off();
					PORTB |= led1;
					break;
				case 2:
					diody_off();
					PORTD |= led2;
					break;
				case 3:
					diody_off();
					PORTD |= led3;
					break;
				case 4:
					diody_off();
					PORTD |= led4;
					break;
				case 5:
					diody_off();
					PORTB |= led5;
					break;
				case 6:
					diody_off();
					PORTB |= led5;
					PORTB |= led1;
					break;
				case 7:
					diody_off();
					PORTB |= led5;
					PORTD |= led2;
					break;
				default:
					diody_off();
					break;
				}
}

uint8_t menu(uint8_t *t, uint8_t *t_on, uint8_t *swiatlo, uint8_t *l_klasniec){
	uint8_t out=0,opcjam=1,zmp;
	PORTB |= menu_led;
	l1_on;
	_delay_ms (200);
	while(out == 0){
		_delay_ms (100);
		/////////////////////////////
		if (klawisz_on(menu_guzik)){
			out=1;
		}
		/////////////////////////////
		diody(opcjam);
		/////////////////////////////
		if (klawisz_on(wartoscp)){
			opcjam++;
			diody(opcjam);
			if (opcjam > 5){
				opcjam=1;
				diody(opcjam);
			}
		}
		if (klawisz_on(wartoscm)){
					opcjam--;
					diody(opcjam);
					if (opcjam <1 ){
						opcjam=5;
						diody(opcjam);
					}
				}
		/////////////////////////////
		if (klawisz_on(opcja)){
			switch (opcjam){
			case 1:
				zmp=tryb;
				out=podmenu(&zmp,1,5,5);
				tryb=zmp;
				break;
			case 2:
				zmp=*t;
				out=podmenu(&zmp,1,7,3);
				*t=zmp;
				break;
			case 3:
				zmp=*t_on;
				out=podmenu(&zmp,1,5,4);
				*t_on=zmp;
				break;
			case 4:
				zmp=*swiatlo;
				out=podmenu(&zmp,1,5,6);
				*swiatlo=zmp;
				break;
			//case 5:
				//zmp=*mikrofon;
				//out=podmenu(&zmp,1,5,3);
				//*mikrofon=zmp;
				//break;
			case 5:
				zmp=*l_klasniec;
				out=podmenu(&zmp,1,2,2);
				*l_klasniec=zmp;
				break;
			}
			if (out == 0) diody(opcjam);
		}
		if (out != 0){
			PORTB &= ~menu_led;
			diody_off();
		}
	}
	return 0;
}

void wzmacniacz(uint8_t mikrofon){

}

uint8_t podmenu(uint8_t *x, uint8_t min, uint8_t max, uint8_t res){
	uint8_t o=0,out=0;
	czeka_on;
	while(out == 0){
		diody((*x));
		_delay_ms(200);
		if (klawisz_on(wartoscp)){
			(*x)++;
			if ((*x) > max){
				*x=min;
			}
		}
		if (klawisz_on(wartoscm)){
			(*x)--;
			if ((*x)<min){
				(*x)=max;
			}
		}
		if (klawisz_on(wartoscp) && klawisz_on(wartoscm)){
			(*x)=res;
			//czujnik swiatla wylaczony
		}
		if (klawisz_on(opcja)){
			out=1;
		}
		if (klawisz_on(menu_guzik)){
			o=1;
			out=1;
		}
	}
	czeka_off;
	return o;
}

uint16_t czas_dzialania(uint8_t t_on){
	switch (t_on){
	case 1:
		return 60;
		break;
	case 2:
		return 60*5;
		break;
	case 3:
		return 60*10;
		break;
	case 4:
		return 60*20;
		break;
	case 5:
		return 60*30;
		break;
	case 6:
		return 60*60;
		break;
	}
	return 60;
}

uint8_t klawisz_on(uint8_t klawisz)
{
	if  ( !((PINB) & klawisz) ){
				_delay_ms(50);
				if (!((PINB) & klawisz)) return 1;
	}
	return 0;
}

uint8_t klawisz_onc(uint8_t klawisz)
{
	if  ( !((PINC) & klawisz) ){
				_delay_ms(50);
				if (!((PINC) & klawisz)) return 1;
	}
	return 0;
}

uint8_t klawisz_sygnal(uint8_t klawisz)
{
	if  ( !((PINC) & klawisz) ){
			_delay_ms(0);
			if (  !((PINC) & klawisz))
				return 1;
			}
			return 0;
}
