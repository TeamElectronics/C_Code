#include <main.h>


int32 lecture(void);
int32 limite = 0;

#INT_RDA
void RDA_isr(void){
   limite = lecture();
   printf("changement de limite");
}

void main()
{
   #define toint(c)  ((c & 0x5F) > '9' ? c - '7' : c - '0')//conversion d'un char en int (0,9)
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_8|RTCC_8_BIT); // 409us overflow
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_1);      //13,1 ms overflow
   enable_interrupts(GLOBAL);
   setup_low_volt_detect(FALSE);
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
   float time=0;
   int32 distance=0;
   printf("sieugyfsiekfn");
   //limite = lecture();//demande de la limite de distance 
   while(true){
      output_high(pin_b7); //debut impulsion sur le trigger de la sonde ultrasons
      delay_us(10);
      output_low(pin_b7);//fin impulsion
      while(!input(PIN_b3));//tant que la pin b3 est a low
      set_timer1(0);//mise a 0 du timer 1
      while(input(PIN_b3));//tant que la pin b3 est a high
      time=get_timer1();//recupération du timer
      distance = time*17/100;//calcul de la distance
      // printf("distance: %f cm\t temps: %f\r\n",distance, time);
      //             printf("distance: %ld limite: %ld\r\n",distance,limite);//envois de la distance par le port com
      if(distance<limite){//si la distance est assez grande
         printf("O");
         output_low(PIN_B0);
         output_high(PIN_B1);
      }else{
         printf("N");
         output_low(PIN_B1);
         output_high(PIN_B0);
      }
      printf("%ld\r\n",distance);
      delay_ms(300);
   }

}

int32 lecture(){
      char entre[5];//buffer de 5 characteres
      int32 sorti=0;
      int i=0,x=0,y=1;//sorti=int voulu
      gets(entre);//attent une chaine de charactere fini par CR
         for(x=0;x<5;x++){//boucle lisant le buffer
            if(entre[x]=='\r'){break;}//quand le char == \r => fin du int
         }
         for(i=x-1;i>0;i--){//boucle traduisant les char en un int
            sorti+=toint(entre[i])*y;//sorti est incremanté du int* dixaine/centaine
            y*=10;
         }
         sorti+=toint(entre[0])*y;//la boucle ne veut pas se finir a 0 alors voila :'(
         //printf("int : %d\r\n",sorti);
         return sorti;
}

