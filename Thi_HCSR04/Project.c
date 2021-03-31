/* Affichage des données de HC SR-04 sur 7 segements */

//Fonction pour afficher le numéro à la position correspondant
void afficheChiffre(char chiffre,int position){
  LATA = 0x01 << position;         	//Registre de sortie active les 4 afficheurs 7segments en fonction de la position
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

// Fonction de prendre data et appeler afficheChiffre pour l'affichage
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

//char uart_rd;
int compte, nombreaffiche, etape, tempo;

void main(void) {
  compte = 0;
  nombreaffiche = 0;
  etape = 0;      	// initialisation de l'étape impilsion et calcul

  TRISA  = 0x00;  	//
  TRISB  = 0x01;  	//   Entrée Microcontrôleur   echo RB0 trigger RB1
  TRISC  = 0x00;  	//
  TRISD  = 0x00;

  LATA = 0x00;    	// attribution des valeurs
  LATB = 0x00;
  LATD = 0x00;
  LATC = 0x00;
  ANSELA = 0;
  ANSELB = 0;
  ANSELC = 0;  	// Configure PORTC pins as digital
  ANSELD = 0;

  TRISC.B3 = 1;
  TRISC.B4 = 1;
  TRISC.B6 = 1;
  TRISC.B7 = 1;

  UART1_Init(9600);   // initialisation de UART
  Delay_ms(1000);



  // Partie de I2C
  //I2C1_Init(100000);	// initialisation I2C=


  //afficheNombre((int)nombreaffiche);
  while(1){
	switch(etape) {
   	case 0:  // génération d'une impulsion vers US
     	LATB1_bit = 1;
     	compte = 0;
     	etape++ ;
     	break;
   	case 1: // attente 1ms et retour à zéro
      	Delay_ms(1);
      	LATB1_bit = 0;
      	etape++ ;
      	break;
   	case 2 : // vérifier si RB0 =1 (existence d'un ECHO sur le PORTB puis attendre 10ms
      	if(PORTB & 0x01){ // vérification de la valeur du registre d'entrée  je teste l'echo
         	while(PORTB & 0x01){
              	delay_us(10);
              	compte++;
          	}
      	etape++;
      	}
      	break;
   	default : // calcul de la distance via le modèle constructeur
      	nombreaffiche = (int)compte*10/58.0;
      	afficheNombre(nombreaffiche);



  	/*
      	// I2C to 7 segment
      	Delay_100ms();
      	// Communication of I2C
      	I2C1_Start();
      	I2C1_Wr(0xA2);   	// send byte via I2C  (device address + W)	1010 001 0 = 10100010 = 0xA2
      	I2C1_Wr(2);      	// send byte (address of EEPROM location)  - location 2
      	I2C1_Wr(nombreaffiche);     	// send data (data to be written) 0B10101010  - data 0xAA est écrit à adresse 0x02
      	I2C1_Stop();
      	delay_ms(100);

      	I2C1_Start();          	// issue I2C start signal
      	I2C1_Wr(0xA2);         	// send byte via I2C  (device address + W)
      	I2C1_Wr(2);            	// send byte (data address)
      	I2C1_Repeated_Start(); 	// issue I2C signal repeated start
      	I2C1_Wr(0xA3);         	// send byte (device address + R)
      	tempo = I2C1_Rd(0u);    	// Read the data (NO acknowledge)
      	I2C1_Stop();           	// issue I2C stop signal
     	afficheNombre(tempo);
        	*/

        	UART1_Write(nombreaffiche);
    	etape=0;
    	break;
	}
  }
}
