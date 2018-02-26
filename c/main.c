#include <main.h>

void main()
{
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_1);      //13,1 ms overflow

   setup_low_volt_detect(FALSE);

   while(TRUE)
   {
      delay_ms(100);
      output_high(pin_b0);
      output_high(pin_b7);
      delay_us(30);
      output_low(pin_b7);
      //delay_ms(100);
      output_low(pin_b0);
      output_high(pin_b1);
      while(!input(PIN_b3));
      set_timer1(0);
      while(input(pin_b3));
      output_low(pin_b1);
      int time=get_timer1();
      output_d(time);
      printf("0x01");
      delay_ms(100);
   }


}
