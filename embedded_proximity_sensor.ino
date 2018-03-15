#include <avr/sleep.h>

volatile int micro_counter = 0;
volatile int signal_counter = 0;
volatile int dis = 0;  

ISR(TIMER0_COMPA_vect)
{
  
  if(signal_counter == 0)
  {
    PORTB = PORTB | (1 << PB0);
    micro_counter = 0;
    signal_counter++;
    micro_counter++;
  }
  else if(signal_counter > 10)
  {
    PORTB = PORTB & (0 << PB0);
    signal_counter++;
    micro_counter++;
    if(signal_counter >= 2000)
    {
      signal_counter = 0;
    }
  }
  else
  {
    signal_counter++;
    micro_counter++;
  }
}
  
ISR(INT0_vect)
{
  dis = (micro_counter - 130) * (15 - 2) / (280-130)+2; //Mapping function
  Serial.println(dis);
  micro_counter = 0;
}

void setup() {
  DDRB = 0x01;

  TCCR0A = 0x23;
  TCCR0B = 0x09;
  OCR0A = 15; //Period is 1us, thefrefore no prescaler
  TIMSK0 = (1<<OCIE0A);
  
  EIMSK |= 1<<INT0;
  EICRA |= 1<<ISC01;
  sei();
  
  Serial.begin(9600);

}

void loop() {
  sleep_cpu();      
}
