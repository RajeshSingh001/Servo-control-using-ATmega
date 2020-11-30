 
#define F_CPU 1000000


#include <avr/io.h>
#include <util/delay.h>

#define Min_value_PWM 1      // in ms 
#define Max_value_PWM 2      // in ms 
#define PWM_Frequency 50  // in Hz
#define Prescaler 64
#define time_count ((F_CPU/(Prescaler*PWM_Frequency) - 1)/20)  // timer counts for 1ms, it's a formula in atmega datasheet

// Initialize 16bit Timer
// Fast PWM, Non-Inverting, N = 64;
//FAST PWM with ICR1 as TOP
//PWM frequency 50Hz
void init_pwm()
{
TCCR1A|= (1<<COM1A1)|(1<<COM1B1)|(1<<WGM11);
 
TCCR1B|= (1<<WGM13)|(1<<WGM12)|(1<<CS11)|(1<<CS10);

ICR1 = F_CPU /(Prescaler * PWM_Frequency) -1;

}
 
 
int main()
{
 // Set Angle here
 
unsigned short angle_20_degree = 40;
unsigned short angle_0_degree = 0;

 // Set PD5 and PD4 as output
 DDRD = (1<<4)|(1 << 5);

 init_pwm();

 while(1)
 {

  OCR1A = time_count * Min_value_PWM + (angle_20_degree * time_count*(Max_value_PWM - Min_value_PWM))/180;
 _delay_ms(1000);

 OCR1A = time_count * Min_value_PWM + (angle_0_degree * time_count*(Max_value_PWM - Min_value_PWM))/180;
 _delay_ms(1000);
  
}
}
