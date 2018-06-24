#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "tipovi i deklaracije.h"

#define DUZINA 80
#define VISINA 20

void main()
{
	int i, j, duz = 0, u = 0, uu = 0, maxQ = -1, v, k, brz = 100, st, aa, desno = 0, rd = 0, rl = 0;
	char *traka, *azbuka/*=NULL*/, *program/*=NULL*/, c, fajl[100], ca, blanko = 'b';
	FILE *Dat = NULL;
	POKAZIVACI *pok;
	Elem *tek;
	qsr ***f;
	int korak = 0, pauza = 1, kraj = 0;
	COORD g = { 6,4 };

	Podesavanje_prozora(DUZINA, VISINA);
	printf("Turingova masina\n\n");
	/* Unos trake */
	do
	{
		u = Odabir_trake();
		if(u == 0) exit(1);
		if(u == 3)
		{
			printf("- razmaci ce biti zanemareni\n");
			printf("- simbol za blako znak je b\n");
			printf("- vise redova u datoteci ce se posmatrati kao jedan\n\n");
		}
	} while(u == 3);

	switch(u)
	{
	default:
	case 1:	printf("Uneti sadrzaj trake:\n");
		traka = calloc(20, sizeof(char));
		if(traka == NULL) exit(1);
		duz = 0;
		c = getchar();
		while((c = getchar()) != '\n')
		{
			if(c == ' ') continue;
			if(duz != 0 && duz % 20 == 0) traka = realloc(traka, duz + 20);
			if(traka == NULL) exit(1);
			if(c == 'b') traka[duz] = blanko;
			else traka[duz] = c;
			duz++;
		}
		traka[duz] = '\0';
		break;

	case 2:	while(Dat == NULL)
	{
		printf("Uneti ime tekstualnog fajla sa sadrzajem trake:\n");
		scanf("%s", fajl);
		Dat = fopen(fajl, "r");
		if(Dat == NULL) printf("**Greska pri ucitacanju datoteke\n");
	}
			traka = calloc(20, sizeof(char));
			if(traka == NULL) exit(1);
			duz = 0;
			while((c = fgetc(Dat)) != EOF)
			{
				if(c == ' ' || c == '\n') continue;
				if(duz != 0 && duz % 20 == 0) traka = realloc(traka, duz + 20);
				if(traka == NULL) exit(1);
				if(c == 'b') traka[duz] = blanko;
				else traka[duz] = c;
				duz++;
			}
			traka[duz] = '\0';
			break;
	}
	/* Skladistenje trake */
	pok = NapravitiP();
	if(pok == NULL) printf("*** Ucitavanje nije uspelo ***\a\n");
	pok = Unos(pok, traka, blanko);
	if(pok == NULL) printf("**Traka je prazna\n");
	free(traka);
	/* Unos i analiza programa */
	do
	{
		u = Odabir_programa();
		switch(u)
		{
		case 0: exit(1); break;
		case 1:
			while(Dat == NULL)
			{
				printf("Uneti ime tekstualnog fajla sa sadrzajem programa:\n");
				scanf("%s", fajl);
				Dat = fopen(fajl, "r");
				if(Dat == NULL) printf("**Greska pri ucitacanju datoteke\n");
			}
			u = Analiza_programa(Dat, &azbuka, &program, &maxQ, blanko);
			if(u == 0) printf("**Pogresan format");
			break;
		case 2:
			uu = Odabir_postojeceg_programa();
			switch(uu)
			{
			case 0: exit(1); break;
			case 1:
				azbuka = calloc(2, sizeof(char));
				if(azbuka == NULL) exit(1);
				strcpy(azbuka, "b1");
				program = calloc(18 * 3, sizeof(char));
				if(program == NULL) exit(1);
				strcpy(program, "f(q0,1)->(q1,1,+1)f(q1,1)->(q1,b,+1)f(q1,b)->(q+,b,-1)");
				maxQ = 1;
				break;
			case 2:
				azbuka = calloc(2, sizeof(char));
				if(azbuka == NULL) exit(1);
				strcpy(azbuka, "b1");
				program = calloc(18 * 2, sizeof(char));
				if(program == NULL) exit(1);
				strcpy(program, "f(q0,1)->(q1,1,-1)f(q1,b)->(q+,1,-1)");
				maxQ = 1;
				break;
			case 3:
				azbuka = calloc(3, sizeof(char));
				if(azbuka == NULL) exit(1);
				strcpy(azbuka, "b10");
				program = calloc(18 * 5, sizeof(char));
				if(program == NULL) exit(1);
				strcpy(program, "f(q0,1)->(q1,1,+1)f(q1,1)->(q1,1,+1)f(q1,0)->(q2,b,+1)f(q2,1)->(q2,b,+1)f(q2,b)->(q+,b,+1)");
				maxQ = 2;
				break;
			case 4:
				azbuka = calloc(3, sizeof(char));
				if(azbuka == NULL) exit(1);
				strcpy(azbuka, "b10");
				program = calloc(18 * 7, sizeof(char));
				if(program == NULL) exit(1);
				strcpy(program, "f(q0,1)->(q1,1,+1)f(q1,1)->(q1,1,+1)f(q1,0)->(q2,1,+1)f(q2,1)->(q2,1,+1)f(q2,b)->(q3,b,-1)f(q3,1)->(q4,b,-1)f(q4,1)->(q+,b,-1)");
				maxQ = 4;
				break;
			case 5:
				azbuka = calloc(3, sizeof(char));
				if(azbuka == NULL) exit(1);
				strcpy(azbuka, "b10");
				program = calloc(18 * 8, sizeof(char));
				if(program == NULL) exit(1);
				strcpy(program, "f(q0,1)->(q1,1,+1)f(q1,0)->(q1,0,+1)f(q1,1)->(q1,1,+1)f(q1,b)->(q2,b,-1)f(q2,0)->(q3,0,-1)f(q2,1)->(q-,1,+1)f(q3,0)->(q+,0,+1)f(q3,1)->(q-,1,+1)");
				maxQ = 3;
				break;
			} break;
		case 3:
			printf("- razmaci ce biti zanemareni\n");
			printf("- f(qi,ai) -> (qj,aj,r)\n");
			printf("  * q - unutrasnje stanje\n");
			printf("  * a - podatak sa trake\n");
			printf("  * r - smer kretanja glave (+1 ili -1)\n");
			printf("  * i = {0, 1,.., n}\n");
			printf("  * j = {0, 1,.., n, +, -}\n\n");
			break;
		}

	} while(u == 3 || u == 0);
	/* Skladistenje programa */
	v = maxQ + 1;
	k = strlen(azbuka);
	f = (qsr ***)malloc(v * sizeof(qsr **));
	if(f == NULL) exit(1);
	for(i = 0; i<v; i++)
	{
		f[i] = (qsr **)malloc(k * sizeof(qsr *));
		if(f[i] == NULL) exit(1);
		for(j = 0; j<k; j++)
		{
			f[i][j] = (qsr *)malloc(sizeof(qsr));
			if(f[i][j] == NULL) exit(1);
		}
	}
	/* Popunjavanje NULL vrednostima */
	for(i = 0; i<v; ++i)
	{
		for(j = 0; j<k; ++j)
		{
			f[i][j]->q = -3;
			f[i][j]->a = '\0';
			f[i][j]->r = 0;
		}
	}
	Smestanje_programa(f, program, azbuka, blanko);
	/* Ispis aplikacije u konzoli */
	pisi_traku(pok, DUZINA, blanko, 0);
	Prazan_red(VISINA - 4 - 1 - 1);
	Kontrole(DUZINA, VISINA);
	printf("\n");
	g.X += 2 * 0;
	TT(30, g);
	/* Rad aplikacije */
	tek = pok->pocetak;
	st = 0;
	i = 0;
	while(kraj != 1)
	{
		if(pauza == 0 || korak != 0)
		{
			ca = tek->a;
			aa = Index(azbuka, ca);
			if(aa == -1)
			{
				printf("** Simbol %c se ne nalazi u azbuci programa", ca);
				break;
			}
			if(f[st][aa]->r == 0)
			{
				printf("** Simbol %c nije regulisan stanjem q%d", ca, st);
				break;
			}
			if(g.X == DUZINA - 6)
			{
				--desno;
				pomeri(pok, DUZINA, blanko, desno - rl);
				TT(' ', g);
				g.X -= 2;
				TT(30, g);
				Sleep(2 * brz);
			}
			if(g.X == 4)
			{
				++desno;
				pomeri(pok, DUZINA, blanko, desno - rl);
				TT(' ', g);
				g.X += 2;
				TT(30, g);
				Sleep(2 * brz);
			}
			Animacija_CP(g, f[st][aa]->a, brz);
			tek->a = f[st][aa]->a;

			if(f[st][aa]->r == 1)
			{
				if(tek->next == NULL)
				{
					Na_kraj(pok, blanko);
					rd++;
				}
				tek = tek->next;
				if(tek->pre == pok->pocetak && tek->pre->a == 'b')
				{
					pok = Izbaci_prvi(pok);
					rl--;
				}
				g = Animacija_GD(g, 1, brz);
			}
			if(f[st][aa]->r == -1)
			{
				if(tek->pre == NULL)
				{
					Na_pocetak(pok, blanko);
					rl++;
				}
				tek = tek->pre;
				if(tek->next == pok->kraj && tek->next->a == 'b')
				{
					pok = Izbaci_poslednji(pok);
					rd--;
				}
				g = Animacija_GD(g, -1, brz);
			}
			st = f[st][aa]->q;
			i++;
			Korak_ispis(i, DUZINA, VISINA, VISINA - 1 - 1 - 1);
			Stanje_ispis(st, DUZINA, VISINA, VISINA - 1 - 1);
		}
		korak = 0;
		Sleep(brz);
		if(kbhit())
		{
			c = getch();
			switch(c)
			{
			case 'K': case 'k': korak = 1; break;
			case 'S': case 's': pauza = 0; break;
			case 'Z': case 'z': pauza = 1; break;
			case 'B': case 'b':
				if(g.X<DUZINA - 6)
				{
					++desno;
					pomeri(pok, DUZINA, blanko, desno - rl);
					TT(' ', g);
					g.X += 2;
					TT(30, g);
				} break;
			case 'V': case 'v':
				if(g.X >= 6)
				{
					--desno;
					pomeri(pok, DUZINA, blanko, desno - rl);
					TT(' ', g);
					g.X -= 2;
					TT(30, g);
				} break;
			case 27: kraj = 1;
			default: break;
			}
		}
		if(st == -1)
		{
			printf("Pozitivan zavrserak");
			break;
		}
		if(st == -2)
		{
			printf("Negativan zavrserak");
			break;
		}
	}
	Sleep(brz);
	while(!kbhit())
	{
		Sleep(brz);
	}
	/* Dealokacija memorije */
	Brisanje(pok);

	for(i = 0; i<v; i++)
	{
		for(j = 0; j<k; j++)
		{
			free(f[i][j]);
		}
		free(f[i]);
	}
	free(f);
}