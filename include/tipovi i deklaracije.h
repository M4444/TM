/* Element liste */
typedef struct elem
{
	char a;
	struct elem *next;
	struct elem *pre;
} Elem;

/* Pokazivaci na krajevi liste */
typedef struct pokazivaci
{
	Elem *pocetak;
	Elem *kraj;
} POKAZIVACI;

/* Blok sa podatcima */
typedef struct QSR
{
	int q;
	char a;
	int r;
} qsr;

POKAZIVACI *NapravitiP();
POKAZIVACI *Unos(POKAZIVACI *, char *, char);
void Brisanje(POKAZIVACI *);
void Na_kraj(POKAZIVACI *, char);
void Na_pocetak(POKAZIVACI *, char);
POKAZIVACI *Izbaci_prvi(POKAZIVACI *);
POKAZIVACI *Izbaci_poslednji(POKAZIVACI *);

void Podesavanje_prozora(int, int);
void Prazan_red(int);

int Odabir_trake();
int Odabir_programa();
int Odabir_postojeceg_programa();

void pisi_traku1(char *, int, char);
void pisi_traku(POKAZIVACI *, int, char, int);
void razmak(int p);
void T(char);
void TT(char, COORD);
void Kontrole(int, int);
void Korak_ispis(int, int, int, int);
void Stanje_ispis(int, int, int, int);

int Index(char *, char);
int Analiza_programa(FILE *, char **, char **, int *, char);
void Smestanje_programa(qsr ***, char *, char *, char);

void Animacija_CP(COORD, char, int);
COORD Animacija_GD(COORD, int, int);

void pomeri(POKAZIVACI *, int, char, int);