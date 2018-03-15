#include <avr/sleep.h>

volatile int pwm_counter = 0;
volatile int dir = 0;
volatile int move_count = 0;

ISR(TIMER0_COMPA_vect)
{
  if(dir == 0)
  {
    if(pwm_counter < 100)
      PORTB = PORTB | (1 << PB1);
    else
      PORTB = PORTB & (0 << PB1);
    
  }
  else
  {
    if(pwm_counter < 700)
      PORTB = PORTB | (1 << PB1);
    else
      PORTB = PORTB & (0 << PB1);      
  }

  if(pwm_counter > 10000)
  {
    pwm_counter = 0;
  }
  else
  {
    pwm_counter++;
  }
  
  if(move_count > 990)
    {
      move_count = 0;
      dir = !dir;
    }
    else
      move_count++;

}

void setup() {
  
  TCCR0A = 0x23;
  TCCR0B = 0x09;
  OCR0A = 15; //Period is 1 us, therefore no prescaler
  OCR0B = 0;
  TIMSK0 |= (1<<OCIE0A);
  sei();

  Serial.begin(9600);
  DDRB|= (1<<PB1);
  
}

void loop() {
  sleep_cpu();
}
