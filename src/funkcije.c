#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <strsafe.h>
#include "tipovi i deklaracije.h"

void T(char c)
{
	putchar(c);
}

void TT(char c, COORD S)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD Written;

	FillConsoleOutputCharacter(hOut, c, 1, S, &Written);
}

int Odabir_trake()
{
	int uu = 0;
	char z[10];

	printf("Odabrati nacin unosa trake:\n");
	printf("1. preko konzole\n");
	printf("2. preko tekstualnog fajla\n");
	printf("3. format unosa\n");
	printf("0. izlaz\n");
	while(uu == 0)
	{
		scanf("%s", &z);
		if(strlen(z) != 1)
		{
			printf("**Odabir nije validan\a\n");
			continue;
		}
		else
		{
			if(z[0] != '1' && z[0] != '2' && z[0] != '3' && z[0] != '0')
			{
				printf("**Odabir nije validan\a\n");
				continue;
			}
			else return atoi(z);
			if(z[0] == '0') return 0;
		}
	}
}

int Odabir_programa()
{
	int uu = 0;
	char z[10];

	printf("Odabrati nacin unosa programa:\n");
	printf("1. preko tekstualnog fajla\n");
	printf("2. odabir postojeceg programa\n");
	printf("3. format unosa\n");
	printf("0. izlaz\n");
	while(uu == 0)
	{
		scanf("%s", &z);
		if(strlen(z) != 1)
		{
			printf("**Odabir nije validan\a\n");
			continue;
		}
		else
		{
			if(z[0] != '1' && z[0] != '2' && z[0] != '3' && z[0] != '0')
			{
				printf("**Odabir nije validan\a\n");
				continue;
			}
			else return atoi(z);
		}
	}
}

int Odabir_postojeceg_programa()
{
	int uu = 0;
	char z[10];

	printf("Odabrati programa:\n");
	printf("1. nula funkcija	\n");
	printf("2. sledbenik		\n");
	printf("3. prva projekcija	\n");
	printf("4. zbir				\n");
	printf("5. deljivost sa 4	\n");
	printf("0. izlaz\n");
	while(uu == 0)
	{
		scanf("%s", &z);
		if(strlen(z) != 1)
		{
			printf("**Odabir nije validan\a\n");
			continue;
		}
		else
		{
			if(z[0] != '1' && z[0] != '2' && z[0] != '3' && z[0] != '4' && z[0] != '5' && z[0] != '0')
			{
				printf("**Odabir nije validan\a\n");
				continue;
			}
			else return atoi(z);
		}
	}
}

void pisi_traku(POKAZIVACI *P, int DUZ, char bl, int n)
{
	int i, b, d = 0, duzina = 0;
	Elem *tek;

	for(tek = P->pocetak; tek != NULL; tek = tek->next) duzina++;
	if(DUZ / 2 - 6 >= duzina + n) b = duzina;
	else
	{
		b = DUZ / 2 - 6;
		d = 1;
	}

	//prvi red
	T(196); T(196); T(196);
	for(i = 0; i<DUZ / 2 - 4; i++)
	{
		T(194);
		T(196);
	}
	T(194);
	T(196); T(196); T(196);
	T('\n');
	//drugi red
	T('.'); T('.'); T('.');
	T(179); T(bl);

	for(i = 0; i<n; i++)
	{
		T(179);
		T(bl);
	}

	for(i = 0, tek = P->pocetak; i<b; i++)
	{
		T(179);
		T(tek->a);
		tek = tek->next;
	}
	for(i = 0; i<DUZ / 2 - 6 - b - n; i++)
	{
		T(179);
		T(bl);
	}
	T(179);
	if(d == 0) T(bl); else T(tek->a);
	T(179);
	if(d == 0)
	{
		T('.'); T('.'); T('.');
	}
	else
	{
		T(' '); T(16); T(' ');
	}
	T('\n');
	//treci red
	T(196); T(196); T(196);
	for(i = 0; i<DUZ / 2 - 4; i++)
	{
		T(193);
		T(196);
	}
	T(193);
	T(196); T(196); T(196);
	T('\n');
}

void Podesavanje_prozora(int DUZ, int VIS)
{
	TCHAR szNewTitle[MAX_PATH];
	HWND wh = GetConsoleWindow();
	HANDLE outHndl = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dim = { DUZ,VIS };
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	SMALL_RECT r;
	/* Velicina i pozicija */
	GetConsoleScreenBufferInfo(outHndl, &csbi);

	r.Left = 0;
	r.Top = 0;
	r.Right = DUZ - 1;
	r.Bottom = VIS - 1;
	SetConsoleWindowInfo(outHndl, TRUE, &r);

	SetConsoleScreenBufferSize(outHndl, dim);
	MoveWindow(wh, DUZ * 4, VIS * 8, DUZ * 15, VIS * 15, TRUE);
	/* Naslov */
	StringCchPrintf(szNewTitle, MAX_PATH, TEXT("TURINGOVA MASINA %s"), "");
	SetConsoleTitle(szNewTitle);
}

void Prazan_red(int VIS)
{
	int i;

	for(i = 1; i <= VIS; i++) T('\n');
}

/* Pravljenje pokazivaca na pocetak i kraj liste */
POKAZIVACI *NapravitiP()
{
	POKAZIVACI *Pok;

	Pok = malloc(sizeof(POKAZIVACI));
	if(Pok != NULL)
	{
		Pok->pocetak = NULL;
		Pok->kraj = NULL;
		return Pok;
	}
	else return NULL;
}

POKAZIVACI *Unos(POKAZIVACI *P, char *t, char bl)
{
	Elem *pret = NULL;
	int i;

	if(strlen(t) == 0)
	{
		Elem *novi = malloc(sizeof(Elem));
		if(novi == NULL) exit(1);

		novi->a = bl;

		novi->next = novi->pre = NULL;
		P->pocetak = P->kraj = novi;
	}
	for(i = 0; i<strlen(t); i++)
	{
		Elem *novi = malloc(sizeof(Elem));
		if(novi == NULL) exit(1);

		novi->a = t[i];

		novi->next = NULL;
		if(pret == NULL) novi->pre = NULL;

		if(P->pocetak == NULL)
			P->pocetak = P->kraj = novi;
		else
		{
			pret->next = novi;
			novi->pre = pret;
			P->kraj = novi;
		}
		pret = novi;
	}
	return P;
}

void Brisanje(POKAZIVACI *P)
{
	Elem *tek;

	if(P == NULL) return;
	while(P->pocetak != NULL)
	{
		tek = P->pocetak;
		P->pocetak = P->pocetak->next;
		free(tek);
	}
	free(P);
}

/*Dodavanje jednog elementa na kraj trake */
void Na_kraj(POKAZIVACI *poc, char a)
{
	Elem *novi;

	novi = malloc(sizeof(Elem));
	if(novi == NULL) exit(1);
	novi->a = a;

	novi->pre = poc->kraj;
	novi->next = NULL;
	if(poc->pocetak == NULL) poc->pocetak = novi;
	else poc->kraj->next = novi;
	poc->kraj = novi;
}

/*Dodavanje jednog elementa na pocetak trake */
void Na_pocetak(POKAZIVACI *poc, char a)
{
	Elem *novi;

	novi = malloc(sizeof(Elem));
	if(novi == NULL) exit(1);
	novi->a = a;

	novi->next = poc->pocetak;
	novi->pre = NULL;
	if(poc->kraj == NULL) poc->kraj = novi;
	else poc->pocetak->pre = novi;
	poc->pocetak = novi;
}

POKAZIVACI *Izbaci_prvi(POKAZIVACI *poc)
{
	Elem *stari;

	stari = poc->pocetak;
	poc->pocetak = stari->next;
	poc->pocetak->pre = NULL;
	free(stari);
	return poc;
}

POKAZIVACI *Izbaci_poslednji(POKAZIVACI *poc)
{
	Elem *stari;

	stari = poc->kraj;
	poc->kraj = stari->pre;
	poc->kraj->next = NULL;
	free(stari);
	return poc;
}

void Kontrole(int DUZ, int VIS)
{
	int m, i;

	printf("Sledeci korak - k   ");
	printf("Start - s   ");
	printf("Stop - z   ");
	printf("Izlaz - esc");
	m = DUZ - 12 - 11 - 11 - 2 - 31;
	for(i = 0; i<m; i++)	printf(" ");
	printf("Korak: 0    \n");
	printf("Pomeranje trake:   ");
	printf("levo - v   ");
	printf("desno - b   ");
	m = DUZ - 19 - 11 - 12 - 14;
	for(i = 0; i<m; i++)	printf(" ");
	printf("Stanje: q0   ");
}

void Korak_ispis(int S, int DUZ, int VIS, int red)
{
	COORD m = { DUZ - 1 - 6, red };
	char b;
	int i, d = 0;

	for(i = 10000; i >= 1; i = i / 10)
	{
		b = '0' + (S % (i * 10)) / i;
		if(b != '0' || d)
		{
			m.X++;
			TT(b, m);
			d = 1;
		}
	}
}

void Stanje_ispis(int S, int DUZ, int VIS, int red)
{
	COORD m = { DUZ - 1 - 5, red };
	char b;
	int i, d = 0;

	if(S == -1 || S == -2)
	{
		m.X++;
		if(S == -1) TT('+', m);
		else TT('-', m);
		for(i = 0; i<4; i++)
		{
			m.X++;
			TT(' ', m);
		}
	}
	for(i = 10000; i >= 1; i = i / 10)
	{
		b = '0' + (S % (i * 10)) / i;
		if(b != '0' || d)
		{
			m.X++;
			TT(b, m);
			d = 1;
		}
	}
}


int Index(char *az, char s)
{
	int i;

	for(i = 0; i<strlen(az); i++) if(az[i] == s) return i;
	return -1;
}

int Analiza_programa(FILE *Dat, char **aazbuka, char **pprogram, int *maxQ, char bl)
{
	int i = 0, j, k = 0, duz, d, d2, tm = 0, ta = 0;
	char c, max[6], *azbuka, *program;

	program = calloc(20, sizeof(char));
	if(program == NULL) exit(1);
	duz = 0;

	while((c = fgetc(Dat)) != EOF)
	{
		if(c == ' ' || c == '\n') continue;
		if(duz != 0 && duz % 18 == 0) program = realloc(program, duz + 18);
		if(program == NULL) exit(1);
		program[duz] = c;
		duz++;
	}
	program[duz] = '\0';
	azbuka = calloc(strlen(program), sizeof(char));
	if(azbuka == NULL) exit(1);
	while(i<duz)
	{
		/* f(q *///////////////////////////
		if(program[i] != 'f') return 0; i++;
		if(program[i] != '(') return 0; i++;
		if(program[i] != 'q') return 0; i++;
		/* f(qi *//////////////////////////
		d = 0;
		while(program[i + d] >= '0' && program[i + d] <= '9')
		{
			max[tm] = program[i + d];
			tm++;
			d++;
		}
		max[tm] = '\0';
		if(d == 0) return 0;
		if(atoi(max)>*maxQ) *maxQ = atoi(max);
		d--; i++; tm = 0;
		/*f(qi,*/////////////////////////////
		if(program[i + d] != ',') return 0; i++;
		/*f(qi,ai*///////////////////////////
		for(j = 0; j<ta; j++)
		{
			if(azbuka[j] == program[i + d] || program[i + d] == 'b' && azbuka[j] == bl) k = 1;
		}
		if(k == 0)
		{
			if(program[i + d] == 'b') azbuka[ta] = bl;
			else azbuka[ta] = program[i + d];
			ta++;
		} k = 0; i++;
		/*f(qi,ai)->(q*//////////////////////
		if(program[i + d] != ')') return 0; i++;
		if(program[i + d] != '-') return 0; i++;
		if(program[i + d] != '>') return 0; i++;
		if(program[i + d] != '(') return 0; i++;
		if(program[i + d] != 'q') return 0; i++;
		/*f(qi,ai) -> (qj*///////////////////
		d2 = 0;
		while(program[i + d + d2] >= '0' && program[i + d + d2] <= '9')
		{
			max[tm] = program[i + d];
			tm++;
			d2++;
		}
		max[tm] = '\0';
		if(program[i + d + d2] == '+' || program[i + d + d2] == '-') d2++;
		if(d2 == 0) return 0;
		if(atoi(max)>*maxQ) *maxQ = atoi(max);
		d2--; i++; tm = 0;
		/*f(qi,ai) -> (qj,*/////////////////////
		if(program[i + d + d2] != ',') return 0; i++;
		/*f(qi,ai) -> (qj,aj*///////////////////
		for(j = 0; j<ta; j++)
		{
			if(azbuka[j] == program[i + d + d2] || program[i + d + d2] == 'b' && azbuka[j] == bl) k = 1;
		}
		if(k == 0)
		{
			if(program[i + d + d2] == 'b') azbuka[ta] = bl;
			else azbuka[ta] = program[i + d + d2];
			ta++;
		} k = 0; i++;
		/*f(qi,ai) -> (qj,aj,r)*////////////////
		if(program[i + d + d2] != ',') return 0; i++;
		if(program[i + d + d2] != '+' && program[i + d + d2] != '-') return 0; i++;
		if(program[i + d + d2] != '1') return 0; i++;
		if(program[i + d + d2] != ')') return 0; i++;
	}
	azbuka[ta] = '\0';
	*aazbuka = calloc(strlen(azbuka), sizeof(char));
	if(*aazbuka == NULL) exit(1);
	strcpy(*aazbuka, azbuka);
	*pprogram = calloc(strlen(program), sizeof(char));
	if(*pprogram == NULL) exit(1);
	strcpy(*pprogram, program);
	return 1;
}

void Smestanje_programa(qsr ***F, char *pr, char *az, char bl)
{
	int i = 0, t = 0, d, q1, q2, a1;
	char br[6], a2;

	do
	{
		t += 3;
		d = 0;
		while(pr[t] >= '0' && pr[t] <= '9')
		{
			br[d] = pr[t];
			t++;
			d++;
		}
		br[d] = '\0';
		q1 = atoi(br);
		t++;
		for(i = 0; i<strlen(az); i++)
		{
			if(az[i] == pr[t] || pr[t] == 'b' && az[i] == bl)
			{
				a1 = i; break;
			}
		}

		t += 6;
		d = 0;
		while(pr[t] >= '0' && pr[t] <= '9' || pr[t] == '+' || pr[t] == '-')
		{
			br[d] = pr[t];
			t++;
			d++;
		}
		br[d] = '\0';
		if(br[0] == '+') q2 = -1;
		else if(br[0] == '-') q2 = -2;
		else q2 = atoi(br);
		t++;
		if(pr[t] == 'b') a2 = bl;
		else a2 = pr[t];
		t += 2;

		F[q1][a1]->q = q2;
		F[q1][a1]->a = a2;
		if(pr[t] == '+') F[q1][a1]->r = 1;
		else F[q1][a1]->r = -1;

		t += 3;
	} while(pr[t] != '\0');
}

void Animacija_CP(COORD g, char a, int brz)
{
	TT(' ', g); g.Y--; TT(30, g); Sleep(brz);
	g.Y -= 2; TT('/', g); Sleep(brz);
	TT('\\', g); Sleep(brz);
	TT(a, g); Sleep(brz);
	g.Y += 2; TT(' ', g); g.Y++; TT(30, g); Sleep(brz);
}

COORD Animacija_GD(COORD g, int p, int brz)
{
	TT(' ', g); g.X += p; TT(30, g); Sleep(brz);
	TT(' ', g); g.X += p; TT(30, g); Sleep(brz);
	return g;
}

void pomeri(POKAZIVACI *P, int DUZ, char bl, int n)
{
	int i, b, d = 0, duzina = 0;
	Elem *tek;
	COORD g = { 4,1 };

	for(tek = P->pocetak; tek != NULL; tek = tek->next) duzina++;
	b = duzina;

	// red
	if(n >= 0)
	{
		TT(bl, g);
		g.X += 2;
	}

	for(i = 0; i<n; i++)
	{
		if(i == DUZ / 2 - 6) break;
		TT(bl, g);
		g.X += 2;
	}
	tek = P->pocetak;

	if(n + b <= DUZ / 2 - 6)
	{
		if(n<0)
		{
			for(i = 0; i<abs(n) - 1; i++) tek = tek->next;
			i--;
		}
		else i = 0;
		for(; i<b; i++)
		{
			if(tek == NULL) break;
			TT(tek->a, g);
			g.X += 2;
			tek = tek->next;
		}
		for(i = 0; i<DUZ / 2 - 6 - b - n + 1; i++)
		{
			TT(bl, g);
			g.X += 2;
		}
		TT('.', g); g.X++;
		TT('.', g); g.X++;
		TT('.', g);

	}
	else
	{
		if(n<0) for(i = 0; i<abs(n) - 1; i++) tek = tek->next;
		while(tek)
		{
			if(g.X >= DUZ - 4) break;
			TT(tek->a, g);
			g.X += 2;
			tek = tek->next;
		}
		TT(' ', g); g.X++;
		TT(16, g); g.X++;
		TT(' ', g);
	}
	g.X = 0;
	if(n<0)
	{
		TT(' ', g); g.X++;
		TT(17, g); g.X++;
		TT(' ', g);
	}
	else
	{
		TT('.', g); g.X++;
		TT('.', g); g.X++;
		TT('.', g);
	}
}