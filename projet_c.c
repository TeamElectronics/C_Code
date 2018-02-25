#include <projet_c.h>

void main()
{
   setup_low_volt_detect(FALSE);
   int limite =5,cpt=0;
   while(TRUE)
   {
      output_d(cpt);
      //TODO: User Code
      if(cpt>=limite){
         output_b(1);
      }else{
         output_b(2);
      }
      delay_ms(200);
      cpt++;
   }

}
