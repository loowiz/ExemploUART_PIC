/*=======================================================
					SENAI A. Jacob Lafer
					====================

Nome do projeto:	Serial RS-232
Versão:				1.1
Últiva revisão:		07/08/2022
Cliente:			SENAI
Desenvolvimento:	Luiz Ricardo Bitencourt

Descritivo Funcional:
Utilização da comunicação Serial com o módulo USART do PIC.

Inputs:
- 

Outputs:
- Port D: Comunicação com o Display (Data Pins)
- E0: Pino RS do Display
- E1: Pino E (Enable) do Display
- E2: Pino RW do Display

Serial:
- RC6: Pino para recepção serial
- RC7: Pino para transmissão serial

=========================================================*/
#include<xc.h>                          // Biblioteca padrão para o PIC18F4550
#include "lcd_4vias.h"                  // Biblioteca com funções do LCD
#include "serial.h"						// Biblioteca com funções da USART


// ==========================================================
// CONFIGURAÇÕES DO MICROCONTROLADOR
// ==========================================================
#pragma config  FOSC    = HS
#pragma config  PLLDIV  = 1
#pragma config  CPUDIV  = OSC1_PLL2
#pragma config  USBDIV  = 1
#pragma config  BORV    = 0
#pragma config  WDTPS   = 1
#pragma config  MCLRE   = ON
#pragma config	PWRT=ON, LVP=OFF, IESO=OFF, WDT=OFF, PBADEN=OFF, BOR=OFF
#pragma config  CCP2MX=ON, LPT1OSC=OFF, ICPRT=OFF, XINST=OFF, VREGEN=OFF
#pragma config  CP0=OFF, CP1=OFF, CP2=OFF, CP3=OFF, CPB=OFF, CPD=OFF, WRTD = OFF
#pragma config  WRT0=OFF, WRT1=OFF, WRT2=OFF, WRT3=OFF, WRTC = OFF, WRTB = OFF
#pragma config  EBTR0=OFF, EBTR1=OFF, EBTR2=OFF, EBTR3=OFF, EBTRB=OFF
// ==========================================================


//======================================================
// Programa Principal
//======================================================
void main(void){
    // -------------------------------------------------
	// Declaração de variáveis locais
	// -------------------------------------------------
	char caractere_serial = '\0';
    // -------------------------------------------------
	
    
    // -------------------------------------------------
	// Configurações iniciais
	// -------------------------------------------------
	IniciaLCD();            // Inicializa Display
	LimpaLCD();             // Limpa Display
	Inicializa_Serial();    // Inicializa módulo serial
    
    TRISB = 0b00000011;     // Port B, sa?das do RB2 at? RB7
    // -------------------------------------------------
	

    // -------------------------------------------------
	// Recursos ativados uma única vez na inicialização
	// -------------------------------------------------	
	PosicionaLCD(1,1);
	StringLCD("   SENAI  118   ");
	PosicionaLCD(2,1);
	StringLCD("Serial: ");
	// -------------------------------------------------	
    
    
    // -------------------------------------------------	
    // Loop principal
    // -------------------------------------------------	
	while(1){
		if(Verifica_Serial() == 1){
			PosicionaLCD(2,9);
			caractere_serial = Ler_Serial();
			EscreveLCD(caractere_serial);
			Escreve_Serial(caractere_serial);
		}	
	}
    // ------------------------------------------------------
}
