#line 1 "C:/Users/Public/Documents/Mikroelektronika/mikroC PRO for PIC/Examples/Thi_HCSR04/Project.c"



void afficheChiffre(char chiffre,int position){
 LATA = 0x01 << position;
 switch(chiffre){
 case 0:LATD0_bit = 1;LATD1_bit = 1;LATD2_bit = 1;LATD3_bit = 1;
 LATD4_bit = 1;LATD5_bit = 1;LATD6_bit = 0;LATD7_bit = 0;
 break;
 case 1:LATD0_bit = 0;LATD1_bit = 1;LATD2_bit = 1;LATD3_bit = 0;
 LATD4_bit = 0;LATD5_bit = 0;LATD6_bit = 0;LATD7_bit = 0;
 break;
 case 2:LATD0_bit = 1;LATD1_bit = 1;LATD2_bit = 0;LATD3_bit = 1;
 LATD4_bit = 1;LATD5_bit = 0;LATD6_bit = 1;LATD7_bit = 0;
 break;
 case 3:LATD0_bit = 1;LATD1_bit = 1;LATD2_bit = 1;LATD3_bit = 1;
 LATD4_bit = 0;LATD5_bit = 0;LATD6_bit = 1;LATD7_bit = 0;
 break;
 case 4:LATD0_bit = 0;LATD1_bit = 1;LATD2_bit = 1;LATD3_bit = 0;
 LATD4_bit = 0;LATD5_bit = 1;LATD6_bit = 1;LATD7_bit = 0;
 break;
 case 5:LATD0_bit = 1;LATD1_bit = 0;LATD2_bit = 1;LATD3_bit = 1;
 LATD4_bit = 0;LATD5_bit = 1;LATD6_bit = 1;LATD7_bit = 0;
 break;
 case 6:LATD0_bit = 1;LATD1_bit = 0;LATD2_bit = 1;LATD3_bit = 1;
 LATD4_bit = 1;LATD5_bit = 1;LATD6_bit = 1;LATD7_bit = 0;
 break;
 case 7:LATD0_bit = 1;LATD1_bit = 1;LATD2_bit = 1;LATD3_bit = 0;
 LATD4_bit = 0;LATD5_bit = 0;LATD6_bit = 0;LATD7_bit = 0;
 break;
 case 8:LATD0_bit = 1;LATD1_bit = 1;LATD2_bit = 1;LATD3_bit = 1;
 LATD4_bit = 1;LATD5_bit = 1;LATD6_bit = 1;LATD7_bit = 0;
 break;
 case 9:LATD0_bit = 1;LATD1_bit = 1;LATD2_bit = 1;LATD3_bit = 1;
 LATD4_bit = 0;LATD5_bit = 1;LATD6_bit = 1;LATD7_bit = 0;
 break;
 default:
 break;
 }
}


void afficheNombre(int var){
 char chiffre0,chiffre1,chiffre2,chiffre3;
 chiffre3 = var/1000;

 var -= chiffre3*1000;
 chiffre2 = var/100;

 var -= chiffre2*100;
 chiffre1 = var/10;

 var -= chiffre1*10;
 chiffre0 = (int)var;

 afficheChiffre(chiffre0,0);
 Delay_ms(1);
 afficheChiffre(chiffre1,1);
 Delay_ms(1);
 afficheChiffre(chiffre2,2);
 Delay_ms(1);
 afficheChiffre(chiffre3,3);
 Delay_ms(1);
}


int compte, nombreaffiche, etape, tempo;

void main(void) {
 compte = 0;
 nombreaffiche = 0;
 etape = 0;

 TRISA = 0x00;
 TRISB = 0x01;
 TRISC = 0x00;
 TRISD = 0x00;

 LATA = 0x00;
 LATB = 0x00;
 LATD = 0x00;
 LATC = 0x00;
 ANSELA = 0;
 ANSELB = 0;
 ANSELC = 0;
 ANSELD = 0;

 TRISC.B3 = 1;
 TRISC.B4 = 1;
 TRISC.B6 = 1;
 TRISC.B7 = 1;

 UART1_Init(9600);
 Delay_ms(1000);








 while(1){
 switch(etape) {
 case 0:
 LATB1_bit = 1;
 compte = 0;
 etape++ ;
 break;
 case 1:
 Delay_ms(1);
 LATB1_bit = 0;
 etape++ ;
 break;
 case 2 :
 if(PORTB & 0x01){
 while(PORTB & 0x01){
 delay_us(10);
 compte++;
 }
 etape++;
 }
 break;
 default :
 nombreaffiche = (int)compte*10/58.0;
 afficheNombre(nombreaffiche);
#line 151 "C:/Users/Public/Documents/Mikroelektronika/mikroC PRO for PIC/Examples/Thi_HCSR04/Project.c"
 UART1_Write(nombreaffiche);
 etape=0;
 break;
 }
 }
}
