// Programmation TSK_  Serge  ( ZeCrusher )
//  TP serie
// 96-12-26 / 2024
// test de la communication d un port

#if !defined( __DOS_H )
 #include <dos.h>
 #define __DOS_H
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "fct\fcadre.cpp" /* #include "c:\tsk\fct\fcadre.cpp" */

#define ADR_COM1 0x3F8
#define ADR_COM2 0x2F8

#define REG_1 0x00 // Armement intéruptions (tout inhib‚)
#define REG_2 0x00 // je l'ai mis mais il ne sert … rien. (utile qu'en Lecture).
#define REG_3 0x03 // transmition 8 bits; 1 Bit d'arret; Paritée 000b; etc...(il y a aussi DLAB)
#define REG_4 0x00 // Controle du Modem et bit 2 pour g‚n‚rer l'int‚ruption.
#define REG_5_5 0x20 // Etat des lignes et bit 5 pour possibilité de placer ou pas un caractère
#define REG_5_0 0x01 // Etat des lignes et bit 0 pour savoir si on a recu un carac
#define REG_6 0x00 // Etat Modem (… blanc ici!)
#define REG_7 0x00 // … Blanc ici.
#define REG_8 0x0C // poids faible du diviseur de vitesse (=12=$0C)(pour 9600 Bauds)
#define REG_9 0x00 // poids fort du diviseur de vitesse (=0=$00)(pour 9600 Bauds)
#define COM1       0
#define COM2       1
#define color(x,y)	textcolor(x);textbackground(y)

void init_rs(int com_x,int initialise);
int test_rs(int com_x);
int lire_rs(int com_x);
void ecrire_rs(int com_x,char c);
void atts(void);

int lire_com(int com);
void ecrire_com(int com,unsigned char valeur);
void init_com(int com);


void version(void);

union REGS regs;


void main(char argc,char **argv)
{
	int t=0,i=65;
	int  val_recue=0;
	int com=COM2,cpt=0;
	char chaine[255]="Null-modem par  Serge [ TSK_ ARTWORK_  97/2024 ] ";

	clrscr();

	if (argc<2)	{
			textcolor(15);
			cprintf("\n\rParamŠtre requis manquant\n\r");
			textcolor(7);
			cprintf(" \n\rNULMODEM [COM1|COM2]\n\r\n\r");
			cprintf(" Brochage : 25 Broches     \n\r\n\r");
			cprintf("TxD  2 ÄÄÄÄÄÄ<3ÄÄÄÄÄ¿/ÄÄÄÄ3>ÄÄÄÄÄÄÄ 2  TxD ³ 2 et 3 Crois‚e \n\r");
			cprintf("RxD  3 ÄÄÄÄÄÄ<2ÄÄÄÄ/ÀÄÄÄÄÄ2>ÄÄÄÄÄÄÄ 3  RxD ³\n\r");
			cprintf("RTS  4 ÄÄ¿                      ÚÄÄ 4  RTS ³\n\r");
			cprintf("CTS  5 ÄÄÙ                      ÀÄÄ 5  CTS ³\n\r");
			cprintf("GND  7 ÄÄÄÄÄÄÄÄÄÄÄÄ<7>ÄÄÄÄÄÄÄÄÄÄÄÄÄ 7  GND ³ masse logique \n\r");
			cprintf("DSR  6 ÄÄ¿                      ÚÄÄ 6  DSR ³\n\r");
			cprintf("RCD  8 ÄÄ´                      ÃÄÄ 8  RCD ³\n\r");
			cprintf("DRT 20 ÄÄÙ                      ÀÄÄ 20 DRT ³\n\r");
// Mettre les chiffres en couleur ..

			locatext(66,1,"   TSK_ 1997   ",14+16*4);
			textcolor(7);
			exit(0);
	}
	version();

	if (strcmp(argv[1],"COM1")==0) {
		locatext(44,11,"COM1",4+16*15);
		com=ADR_COM1; // COM1;
	}
	else {
		locatext(44,11,"COM2",4+16*15);
		com=ADR_COM2;//COM2;
	}
	if (strcmp(argv[1],"com1")==0) {
		locatext(44,11,"COM1",4+16*15);
		com=ADR_COM1; // COM1;
	}
	else {
		locatext(44,11,"com2",4+16*15);
		com=ADR_COM2;//COM2;
	}

	locatext(1,25,"   TSK_ 97 ",15+16*12);
	init_com(com);

	do
	{

		i++;
		if (i>strlen(chaine)) {
			i=0;
		}

		ecrire_com(com,chaine[i]);
		locatext(20,17,"CaractŠre re‡ue ",0+16*15);
		delay(10);

		t=lire_com(com);
		if (t==chaine[i]) {
			locatext(20,16,"CaractŠre envoy‚e ",0+16*15);
			locatcar(43,16,chaine[i],1+16*15);
			locatext(20,14,"<<         Communication OK         >>",WHITE+16*GREEN);
			locatcar(43,17,t,2+16*15);
			if (cpt++>strlen(chaine)) { printf("\a");cpt=0; }
		}
		else {
			locatext(20,14,"##   Erreur  aucune communication   ##",12+16*4);
			locatext(20,18,"              ",WHITE+16*WHITE);

		}
	val_recue=0;
	}
	while (!kbhit());
	color(7,0);
	fond(1);
	clrscr();

}
//*/

int test_rs(int com_x)
{
	union REGS regs;
	regs.h.ah=3;
	regs.x.dx=com_x;  // 0 pour com 1 et 1 pour com 2
	int86(0x14,&regs,&regs);

	return(regs.h.ah & 0x01);
}
void ecrire_rs(int com_x,char c)
{
	union REGS regs;

	regs.h.ah=0x01;
	regs.h.al=c;
	regs.x.dx=com_x;
	int86(0x14,&regs,&regs);

}
void init_rs(int com_x,int initialise)
{
	union REGS regs;

	regs.h.ah=0;
	regs.x.dx=com_x;  // 0 pour com 1 et 1 pour com 2
	regs.h.al=initialise;
	int86(0x14,&regs,&regs);

}
int lire_rs(int com_x)
{
	union REGS regs;

	regs.h.ah=2;
	regs.x.dx=com_x;  // 0 pour com 1 et 1 pour com 2
	int86(0x14,&regs,&regs);

	return(regs.h.al);
}
void version(void)
{
	fond(0);
	cadre_plein(14,5,65,19,0,WHITE,WHITE,1);  // cadre rep
	locatext(14,5,"            Test le cable  Null-Modem               ",WHITE+16*LIGHTRED);
	locatext(20,8,"\7",12+16*WHITE);
	locatext(22,8,"Ce programme teste le cable branch‚  ",0+16*WHITE);
	locatext(22,9," sur un Port de communication",0+16*WHITE);
	locatext(20,11,"\7",12+16*WHITE);
	locatext(22,11,"Etat du test en cours",0+16*WHITE);

}
void init_com(int com)
{
	//configure le com
	outportb(com+3,REG_3);
	//D‚finit la vitesse
	//‚criture du poids faible du diviseur
	outportb(com+3,REG_3+0X80);//bit 7 de LCR pour DLAB=1
	outportb(com+0,REG_8);
	//‚criture du poids fort du diviseur
	outportb(com+1,REG_9);
	//Inhibe les int‚ruptions de l'UART
	outportb(com+3,REG_3);//bit 7 de LCR pour DLAB=0
	outportb(com+4,REG_4);
	outportb(com+1,REG_1);
}

void ecrire_com(int com,unsigned char valeur)
{
	int v;
	//teste le bit 5 du registre 5 pour voir s'il y la place d'envoyer un caractŠre
	v=inportb(com+5)&(REG_5_5);
	if (v!=0)	{
		//ecrire le caractŠre sur le registre 0
		outportb(com+0,valeur);
	}
}

int lire_com(int com)
{
	int v;
	//teste le bit 5 du registre 5 pour voir s'il y la place d'envoyer un caractŠre
	v=inportb(com+5)&(REG_5_0);

	if (v!=0)	{	//lecture du com avec le registre 0
		return(inportb(com+0));
	}
	else return(777);
}
void atts(void)
{
	asm	 mov dx,0x3Da
	deb1:
	asm	in al,dx
	asm	test al,8
	asm	jne deb1
	deb2:
	asm	in al,dx
	asm	test al,8
	asm	je deb2

}

