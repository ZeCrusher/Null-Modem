#define __FCADRE

/*   FCADRE ver 6.00
 Utilitaire en Mode texte 80x25
 Réalisé le: 12/12/1994
 Dernière modif: 17/01/96
 Programmation & conception: ZeCrusher
 Ce PROGRAMME peut être utilisé dans un autre programme  comme fonction
//*/
// Modifier … cause du projet pcboss
//	enum type_cadre { SIMPLE = 0, DOUBLE = 1, BARRE = 2, ETOILE = 3 };

#define SIMPLE		0
#define DOUBLE		1
#define ETOILE		3
#define BARRE 		2
#define NO_CADRE	4


#if !defined( __DOS_H )
#include <dos.h>
#define __DOS_H
#endif
#if !defined( __CONIO_H )
#include <conio.h>
#define __CONIO_H
#endif
#if !defined( __STDIO_H )
#include <stdio.h>
#define __STDIO_H
#endif
#if !defined( __STRING_H )
#include <string.h>
#define __STRING_H
#endif
//#include <graphics.h>


 #define color(x,y)			textcolor(x);textbackground(y)
 #define CLG_OFF	 0
 #define CLG_ON 	 1
 #define NON		 0
 #define OUI		 1
 #define CVGA     	-1

	typedef unsigned char byte;

void atts(void);

void fond(int mode);
void fenetre(int x,int y,int x1,int y1,int color_barre,int color_cadre,int color_texte,char texte[78]);
void winp(int x,int y,int x1,int y1,int color_texte,int color_fond,int winp_color,char *texte);
void locatext(char x,char y,char *chaine,char attribut);    // ne fonctionne que pour un mode  80x25
void locatext132(char x,char y,char *chaine,char attribut); // ne fonctionne que pour un mode 132x ZZ
void locatcar(char x,char y,char chaine,char attribut);
void locatcar132(char x,char y,char chaine,char attribut);
void modif_fond(char x,char y,int longueur,char attribut,char type=0);
void debut_traitement(int x,int y);
void fin_traitement(void);
void space(int x,int y,int l,int color);
void space(int l,int color);
void cadre_plein(byte x,byte y,byte x1,byte y1,byte type_trait,byte color,byte color_fond,byte ombre);     // dessine le cadre
void fcadre_plein(byte x,byte y,byte x1,byte y1,byte type_trait,byte color,byte color_fond,byte ombre);     // dessine le cadre
void curseur(int etat);
void atts(void);

/*
class ScreenText {
	int x,y,l,h,dsd;
	public:
	int n;
	void drawin(int x1,int y1,int l1,int h1);
};
void ScreenText::drawin(int x1,int y1,int l1,int h1)
{
	cadre_plein(x1,y1,x1+l,y1+h);      // dessine le cadre
	gotoxy(x1+1,y1+1);
	printf("n >%d",n);
	gotoxy(x1+1,y1+2);
	printf("dsd >%d",dsd);
	dsd=1;
}*/

	char buffer_f[4000];

/*
void main(void)
{
	clrscr();
	cadre_plein(24,7,56,11,NO_CADRE,LIGHTGRAY,BLUE,1);  // cadre rep

	getch();

}

*/



void winp(int x,int y,int x1,int y1,int color_texte,int color_fond,int winp_color,char *texte)
{
	cadre_plein(x,y,x1,y1,0,winp_color,winp_color,1);      // dessine le cadre
	modif_fond(x,y,x1-x+1,color_texte+16*color_fond,1);
	locatext(x,y,texte,color_texte+16*color_fond);
}

void debut_traitement(int x,int y)
{
	gettext(1, 1, 80, 25, buffer_f);
	cadre_plein(x,y,x+53,y+2,SIMPLE,YELLOW,BLUE,1);
	locatext(x+1,y+1," Lecture des r‚pertoires et des fichiers du disque ",31);
}

void fin_traitement(void)
{
	puttext(1, 1, 80, 25 ,buffer_f);
}

void fenetre(int x,int y,int x1,int y1,int color_barre,int color_cadre,int color_texte,char texte[78])
{
    int taille=0,position=0;
	taille=strlen(texte);
	cadre_plein(x,y,x1,y1,0,color_cadre,color_cadre,1);  // cadre rep
    for (int i=0;i<(x1-x)+1;i++)
		locatcar(i+x,y,' ',color_barre+16*color_barre);
	if (taille<x1-x) {
		position=(((x1-x)/2)-(taille/2)+x);
	}
	else {
		position=x;
	}
		locatext(position,y,texte,color_texte+16*color_barre);
}

void fcadre_plein(byte x,byte y,byte x1,byte y1,byte type_trait,byte color,byte color_fond,byte ombre)      // dessine le cadre
{
	for (int j=y+1;j<y1+1;j++) {
		atts();
		for (int i=x;i<x1+1;i++) {
			cadre_plein(x,y,i,j,type_trait,color_fond,color_fond,0);      // dessine le cadre
		}
	}
	cadre_plein(x,y,x1,y1,type_trait,color,color_fond,ombre);      // dessine le cadre

}
void cadre_plein(byte x,byte y,byte x1,byte y1,byte type_trait,byte color,byte color_fond,byte ombre)      // dessine le cadre
{
  byte chg,chd,cbd,cbg;   // caractère d'angle               ex: ÛÀÈ
  byte bord_hor_bas,bord_hor_hau; // caractère horyzontal    ex:Í Ä ß
  byte bord_v_droite,bord_v_gauche;  // caractère vertical   ex:ÝÞ º ³
  byte aux=0;  				// variable auxiliaire
  char *ptr_ecran;  //initialisation du pointeur ...
  ptr_ecran=(char*) 0xB8000000L;
  int val=0;


	if (ombre==1)	{
		for(int e=0;e<(y1-y)+1;e++) {
			val=(e+y)*160+x1*2;
			*(ptr_ecran+val+1)=8; // écriture de l'attribut dans l'adresse écran.
			*(ptr_ecran+val+3)=8; // écriture de l'attribut dans l'adresse écran.
		}
		val=y1*160+(x+1)*2;
		for (int s=0;s<(x1-x);s++)
			*(ptr_ecran+val+s*2+1)=8;
	}

	if (type_trait==SIMPLE) 	{  //  cadre 0 du Type ÀÄÄÙ
		bord_v_gauche=179;bord_v_droite=179;bord_hor_hau=196;bord_hor_bas=196;chg=218;chd=191;cbd=217;cbg=192;
	}
	if (type_trait==DOUBLE)	{  // cadre 1 du Type ÈÍÍ¼
		bord_v_gauche=186;bord_v_droite=186;bord_hor_hau=205;bord_hor_bas=205;chg=201;chd=187;cbd=188;cbg=200;
	}
	if (type_trait==BARRE)	{  // cadre 2 du type ÛßßÛ
		// Voir police de caractere sous DOS PCBOSS ver 1.00
		bord_v_gauche=221;bord_v_droite=222;bord_hor_hau=198;bord_hor_bas=199;chg=206;chd=197;cbd=202;cbg=204;
	}
	if (type_trait==ETOILE)	{   // cadre 3 du type ****
		bord_v_gauche=42;bord_v_droite=42;bord_hor_hau=42;bord_hor_bas=42;chg=42;chd=42;cbd=42;cbg=42;
	}
	if (type_trait==NO_CADRE)	{   // cadre 4 du type PCC
		bord_v_gauche=32;bord_v_droite=32;bord_hor_hau=32;bord_hor_bas=32;chg=32;chd=32;cbd=32;cbg=32;
	}
	if (x<1) x=1;
	if (x>80) x=80;
	if (x1<1) x1=1;
	if (x1>80) x1=80;
	if (y<1) y=1;
	if (y>24) y=24;
	if (y1<1) y1=1;
	if (y1>24) y1=24;
	if (x>x1)	{
		aux=x1;x1=x;x=aux;
	}
	if (y>y1)	{
		aux=y1;y1=y;y=aux;
	}

	if (x1-x>=3 && y1-y>=2)	 {
			for (int j=y;j<=y1;j++)		{
				locatcar(x,j,bord_v_gauche,color+16*color_fond);
				locatcar(x1,j,bord_v_droite,color+16*color_fond);
			}

			for (int i=x;i<=x1;i++)    	{
				locatcar(i,y1,bord_hor_bas,color+16*color_fond);
				locatcar(i,y,bord_hor_hau,color+16*color_fond);
			}
			locatcar(x,y,chg,color+16*color_fond);
			locatcar(x1,y,chd,color+16*color_fond);
			locatcar(x,y1,cbg,color+16*color_fond);
			locatcar(x1,y1,cbd,color+16*color_fond);
			for(int i2=0;i2<(y1-(y+1));i2++) {
				modif_fond(x+1,y+1+i2,x1-(x+1),color+16*color_fond,1);
			}

	}

}

void locatext(char x,char y,char *chaine,char attribut)
{
	char far * ptr_ecran;
	int cpt=0;
	x--;y--;
	ptr_ecran=(char far *)0xb8000000L;
	do
	{
		*(ptr_ecran+y*160+2*x+cpt)=*chaine++;
		*(ptr_ecran+y*160+2*x+1+cpt)=attribut;
		cpt=cpt+2;
	}
	while(*chaine!=0);
}
void modif_fond(char x,char y,int longueur,char attribut,char type)
{
	char far * ptr_ecran;
	int cpt=0;
	x--;y--;
	ptr_ecran=(char far *)0xb8000000L;
	for (int i=0;i<longueur;i++)	{
		if (type==1) *(ptr_ecran+y*160+2*x+cpt)=' ';
		*(ptr_ecran+y*160+2*x+1+cpt)=attribut;
		cpt=cpt+2;
	}

}

void locatext132(char x,char y,char *chaine,char attribut)
{
	char far * ptr_ecran;
	int cpt=0;
	x--;y--;
	ptr_ecran=(char far *)0xb8000000L;
	do
	{
		*(ptr_ecran+y*264+2*x+cpt)=*chaine++;
		*(ptr_ecran+y*264+2*x+1+cpt)=attribut;
		cpt=cpt+2;
	}
	while(*chaine!=0);
}

void locatcar(char x,char y,char chaine,char attribut)
{
	char far * ptr_ecran;
	x--;y--;
	ptr_ecran=(char far *)0xb8000000L;
	*(ptr_ecran+y*160+2*x)=chaine;
	*(ptr_ecran+y*160+2*x+1)=attribut;
}
void locatcar132(char x,char y,char chaine,char attribut)
{
	char far * ptr_ecran;
	int cpt=0;
	x--;y--;
	ptr_ecran=(char far *)0xb8000000L;
		*(ptr_ecran+y*264+2*x+cpt)=chaine;
		*(ptr_ecran+y*264+2*x+1+cpt)=attribut;
		cpt=cpt+2;

}
void fond(int mode)
{
	union REGS regs;

	regs.x.ax=0x1003;

	if (mode==CLG_OFF) {
		regs.h.bl=0; // 0 pour supprimer le clignotement
	}
	if (mode==CLG_ON) {
		regs.h.bl=1; // 1 pour le clignotement
	}
	int86(0x10, &regs, &regs);
}
//  Surcharge de fonction
void space(int x,int y,int l,int color)
{   for(int tmp=0;tmp<l;tmp++) locatcar(x+tmp,y,' ',color);
}
void space(int l,int color)
{  for(int tmp=0;tmp<l;tmp++) locatcar(wherex()+tmp,wherey(),' ',color);
}
void curseur(int etat)
{
	if (etat==NON) _setcursortype(_NOCURSOR);
	if (etat==OUI) _setcursortype(_SOLIDCURSOR);
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
