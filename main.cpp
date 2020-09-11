/*
 * Blink
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */

#include <Arduino.h>
#include <analog_in.h>
#include <digital_out.h>
#include <digital_in.h>

//int sensorValue = 0; //variable
int pin_A_Button = 0;
int pin_switch = 12;
int pinG = 11;
int pinR = 10;

Analog_in Button(pin_A_Button);
Digital_in Switch(pin_switch);
Digital_out LED_g(pinG);
Digital_out LED_r(pinR);


void setup()
{
  // initialize LED digital pin as an output.
  Button.init();
  Switch.init();
  LED_g.init();
  LED_r.init();
}

void timer1()
{
    pinMode(pinG, OUTPUT);
    OCR1A = 0x3D08;

    TCCR1B |= (1 << WGM12);
    // Mode 4, CTC on OCR1A

    TIMSK1 |= (1 << OCIE1A);
    //Set interrupt on compare match

    TCCR1B |= (1 << CS12) | (1 << CS10);
    // set prescaler to 1024 and start the timer


    sei();
    // enable interrupts


    while (1)
    {
        // we have a working Timer
    }
}

ISR (TIMER1_COMPA_vect)
{
    // action to be done every 1 sec
  if(Switch.state_d()){
    if(Button.state_a()){
      LED_g.set_hi();
      LED_r.set_lo();
    }
    else{
      LED_g.set_lo();
      LED_r.set_hi();
    }
  }
  else{
    if(Button.state_a()){
      LED_r.set_hi();
      LED_g.set_lo();
    }
    else{
      LED_r.set_lo();
      LED_g.set_hi();
    }
  }

}

void loop()
{
  timer1();
}
