#include <mega16.h>
#include <delay.h>
#include <alcd.h>

#define SPIN A.0
#include <DHT11/DHT11.h>

#define DK1 PORTC.0
#define DK2 PORTC.1

unsigned char hum = 0;
char temp = 0;

unsigned char tempLimit = 20;

unsigned char number[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

void readData(unsigned int number) {
    unsigned int x;
    x = number;
    lcd_putchar(x / 10 + 48);
    x = x % 10;
    lcd_putchar(x + 48);
}

void handleTemp(char temp, unsigned char tempLimit) {
     if (temp < tempLimit) {
        PORTB.0 = 0;
        PORTB.1 = 1;
     }
     else if (temp == tempLimit) {
        PORTB.0 = 1;
        PORTB.1 = 1;
     }
     else if (temp > tempLimit) {
        PORTB.0 = 1;
        PORTB.1 = 0;
     }
}

void warningTemp() {
    if (temp >= 40) {
        PORTB.5 = 0;
        PORTB.6 = 1;
    }
    else if (temp <= 10) {
        PORTB.5 = 1;
        PORTB.6 = 0;
    }
    else {
       PORTB.5 = 1;
       PORTB.6 = 1;
    }
}

void handleHum(unsigned char hum) {
    if (hum < 80)
    {
        PORTB.4 = 0;
    }
    else
    {
        PORTB.4 = 1;
    }
}

void display(unsigned int x) {
    unsigned int a, b;
    b = x % 10;
    a = x / 10;

    DK1 = 0;
    PORTD = number[a];
    delay_ms(10);
    DK1 = 1;

    DK2 = 0;
    PORTD = number[b];
    delay_ms(10);
    DK2 = 1;
}

void displayHumidity(unsigned char hum) {
    lcd_gotoxy(0,0);
    lcd_putsf("Humidity: ");
    readData(hum);
    lcd_gotoxy(12, 0);
    lcd_putchar(37);
}

void displayTemperature(char temp) {
   lcd_gotoxy(0,1);
   lcd_putsf("Temp: ");
   readData(temp);
   lcd_gotoxy(8,1);
   lcd_putchar(223);
   lcd_putchar(67);
}

void displayWarning(char temp) {
    if (temp >= 40 ) {
        lcd_clear();
        lcd_gotoxy(0,0);
        lcd_puts("temp too high");
    }
    if (temp <= 10) {
       lcd_clear();
        lcd_gotoxy(0,0);
        lcd_puts("temp too low");
    }
}

void setTempLimit(void){
   if (PINB.2 == 0) {
     tempLimit++;
     while (PINB.2 == 0) {
        display(tempLimit);
     }
   }
   if (PINB.3 == 0) {
    tempLimit--;
    while(PINB.3 == 0) {
       display(tempLimit);
    }
   }
}

void main(void)
{
// Input/Output Ports initialization
// Port A initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
DDRA=(0<<DDA7) | (0<<DDA6) | (0<<DDA5) | (0<<DDA4) | (0<<DDA3) | (0<<DDA2) | (0<<DDA1) | (0<<DDA0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);

// Port B initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
DDRB=(1<<DDB7) | (1<<DDB6) | (1<<DDB5) | (1<<DDB4) | (0<<DDB3) | (0<<DDB2) | (1<<DDB1) | (1<<DDB0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
PORTB=(0<<PORTB7) | (1<<PORTB6) | (1<<PORTB5) | (1<<PORTB4) | (1<<PORTB3) | (1<<PORTB2) | (1<<PORTB1) | (1<<PORTB0);

// Port C initialization
// Function: Bit7=Out Bit6=Out Bit5=Out Bit4=Out Bit3=Out Bit2=Out Bit1=Out Bit0=Out
DDRC=(1<<DDC7) | (1<<DDC6) | (1<<DDC5) | (1<<DDC4) | (1<<DDC3) | (1<<DDC2) | (1<<DDC1) | (1<<DDC0);
// State: Bit7=0 Bit6=0 Bit5=0 Bit4=0 Bit3=0 Bit2=0 Bit1=0 Bit0=0
PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (1<<PORTC1) | (1<<PORTC0);

// Port D initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
DDRD=(1<<DDD7) | (1<<DDD6) | (1<<DDD5) | (1<<DDD4) | (1<<DDD3) | (1<<DDD2) | (1<<DDD1) | (1<<DDD0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
PORTD=(1<<PORTD7) | (1<<PORTD6) | (1<<PORTD5) | (1<<PORTD4) | (1<<PORTD3) | (1<<PORTD2) | (1<<PORTD1) | (1<<PORTD0);

// Timer/Counter 0 initialization
TCCR0=(0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<WGM01) | (0<<CS02) | (0<<CS01) | (0<<CS00);
TCNT0=0x00;
OCR0=0x00;

// Timer/Counter 1 initialization
TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (0<<CS12) | (0<<CS11) | (0<<CS10);
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;

// Timer/Counter 2 initialization
ASSR=0<<AS2;
TCCR2=(0<<PWM2) | (0<<COM21) | (0<<COM20) | (0<<CTC2) | (0<<CS22) | (0<<CS21) | (0<<CS20);
TCNT2=0x00;
OCR2=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<OCIE0) | (0<<TOIE0);

// External Interrupt(s) initialization
MCUCR=(0<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);
MCUCSR=(0<<ISC2);

UCSRB=(1<<RXCIE) | (0<<TXCIE) | (0<<UDRIE) | (0<<RXEN) | (0<<TXEN) | (0<<UCSZ2) | (0<<RXB8) | (0<<TXB8);

ACSR=(1<<ACD) | (0<<ACBG) | (0<<ACO) | (0<<ACI) | (0<<ACIE) | (0<<ACIC) | (0<<ACIS1) | (0<<ACIS0);

ADCSRA=(1<<ADEN) | (1<<ADSC) | (1<<ADATE) | (0<<ADIF) | (1<<ADIE) | (0<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
SFIOR=(0<<ADTS2) | (0<<ADTS1) | (0<<ADTS0);

SPCR=(0<<SPIE) | (0<<SPE) | (0<<DORD) | (0<<MSTR) | (0<<CPOL) | (0<<CPHA) | (0<<SPR1) | (0<<SPR0);

TWCR=(0<<TWEA) | (0<<TWSTA) | (0<<TWSTO) | (0<<TWEN) | (0<<TWIE);

lcd_init(16);
#asm("sei")

while (1) {
        display(tempLimit);
        setTempLimit();

        readDHT11(&temp,&hum);
        displayHumidity(hum);
        handleHum(hum);

        displayTemperature(temp);
        handleTemp(temp, tempLimit);
        warningTemp();
        displayWarning(temp);
      }
}

