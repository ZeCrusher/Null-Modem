#define __FCADRE

/*   FCADRE ver 6.00
 Utilitaire en Mode texte 80x25
 Réalisé le: 12/12/1994
 Dérnière modif: 17/01/96
 Programmation & conception: Tsakiropoulos Serge & Matheis laurent

 Ce PROGRAMME peut être utilis‚ dans un autre programme comme fonction
//*/
// Modifier … cause du projet .....
//	enum type_cadre { SIMPLE = 0, DOUBLE = 1, BARRE = 2, ETOILE = 3 };
#define SIMPLE		0
#define DOUBLE		1
#define BARRE 		2
#define ETOILE		3

#if !defined( __CONIO_H )
#include <conio.h>
#define __CONIO_H
#endif
#if !defined( __DOS_H )
#include <dos.h>
#define __DOS_H
#endif
#if !defined( __STRING_H )
#include <string.h>
#define __STRING_H
#endif


#define color(x,y)			textcolor(x);textbackground(y)
#define CLIGNOTEMENT 1
#define NON		 0
#define OUI		 1


//class Screen; // Annonce de la classe Screen

//class Screen {
//  public:
//};

typedef unsigned char byte;

void fond(int mode);
void fenetre(int x,int y,int x1,int y1,int color_barre,int color_cadre,int color_texte,char texte[78]);
void winp(int x,int y,int x1,int y1,int color_texte,int color_fond,int winp_color,char *texte);
void locatext(char x,char y,char *chaine,char attribut);    // ne fonctionne que pour un mode  80x25
void locatext132(char x,char y,char *chaine,char attribut); // ne fonctionne que pour un mode 132x ZZ
void locatcar(char x,char y,char chaine,char attribut);
void locatcar132(char x,char y,char chaine,char attribut);
void modif_fond(char x,char y,int longueur,char attribut,char type);
void debut_traitement(int x,int y);
void fin_traitement(void);
void space(int x,int y,int l,int color);
void space(int l,int color);
void curseur(int etat);
void cadre_plein(byte x,byte y,byte x1,byte y1,byte type_trait,byte color,byte color_fond,byte ombre=1);      // dessine le cadre
void fcadre_plein(byte x,byte y,byte x1,byte y1,byte type_trait,byte color,byte color_fond,byte ombre);     // dessine le cadre

