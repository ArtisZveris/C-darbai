#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct medis {
    int elementas;
    struct medis *kaire;
    struct medis *desine;
};

typedef struct medis Medis;
typedef Medis *MedisPtr;

struct Node {
    int data;
    struct node *next;
    struct node *prev;
};
struct Node* head;
struct Node* tail;

struct Node* GetNewNode (int x){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = x;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

struct sarasas {
    char data;
    struct sarasas *next;
};
struct sarasas* sarasasPtr;

void meniu();
void Uzduotis_1 ();
void Uzduotis_2 ();
void Uzduotis_3 ();
void Uzduotis_4 ();
void iterpti (MedisPtr *, int);
void spausdinti(MedisPtr);
bool paieska(MedisPtr, int);
MedisPtr salinti(Medis *, int);

void MedisToNode (MedisPtr);
void InsertAtTail(int);
void PrintNode();
//4 Uzduotis
void IterptiSarasa(char*);
void SpausdintiSarasa();

int main()
{
	meniu();
    return 0;
}

void meniu() {
	int i;
	system("cls");
	printf("\n=====================\n");
	printf("  Uzduotys 5 variantas\n");
	printf("=====================\n\n");
	printf("[1] - Uzduotis nr 1\n");
	printf("[2] - Uzduotis nr 2\n");
	printf("[3] - Uzduotis nr 3\n");
	printf("[4] - Uzduotis nr 4\n");
	printf("[0] - Baigti darba\n");
	scanf("%d", &i);

	switch (i) {
		case 0:
			break;
		case 1:
			system("cls");
			Uzduotis_1();
			break;
		case 2:
			system("cls");
			Uzduotis_2();
			break;
        case 3:
            system("cls");
			Uzduotis_3();
			break;
        case 4:
			system("cls");
			Uzduotis_4();
			break;
		default:
			meniu();
	}
}

void Uzduotis_1() {
    FILE * failas;
    char tekstas[40];
    int skaicius = 0, i=0, j;

    printf("UZDUOTIS 1\n");
    printf("\nDuotas tipinis failas, kurio komponentai simboliai. Rasti kiek zodziu prasideda raide a.\n\n"); //U�duotis

    if ((failas = fopen("failas.dat", "wb+")) == NULL){
        printf("Klaida atidarant faila!\n");
    } else {
        printf("Iveskite simbolius (teksta)\n");
        printf("Ivedimo pabaiga ctr+z \n");
        printf("?");
        scanf("%s", tekstas);
        while(!feof(stdin)) {
            fwrite(&tekstas, sizeof(tekstas), 1, failas);
            printf("?");
            scanf("%s", tekstas);
            i++;
        }
    }
	rewind(failas);
	for(j=0; j<i; j++){
		fread(&tekstas, sizeof(tekstas), 1, failas);
		char *zodis = strtok(tekstas, " ,");
		if(zodis[0] == 'a')
            skaicius++;
		zodis = strtok(NULL, " ,");
	}
    fclose(failas);

    printf("\nYra %d zodziai su pirma a raide\n", skaicius);
	system("pause");
	meniu();
}

void Uzduotis_2() {
    FILE *failas;
    double skaicius, max = 0, suma = 0, sandauga = 1;
    int i = 0, j;

    printf("UZDUOTIS 2\n\n");
    printf("Diske sukurkite tipizuota realiuju skaiciu faila. Skaiciu kiekis  nera zinomas.\n");
    printf("Po to, skaitydami duomenis is failo, apskaiciuokite suma elementu, esanciu nuo failo\n");
    printf("pradzios iki pirmo maksimalaus elemento (gali buti keli vienodi elementai, kuriu reiksme maksimali).\n");
    printf("Taip pat rasti sandauga elementu, esanciu nuo paskutinio maksimalaus elemento iki failo galo.\n\n");

    if((failas = fopen("failas.dat", "wb+")) == NULL) {
        printf("Klaida atidarant faila!");
    } else {
        printf("Iveskite realius skaicius\n");
        printf("Ivedimo pabaiga ctr+z \n");
        printf("?");
        scanf("%lf", &skaicius);
        while(!feof(stdin)) {
            fwrite(&skaicius, sizeof(double), 1, failas);
            printf("?");
            scanf("%lf", &skaicius);
            i++;
        }
		rewind(failas);
		printf("Elementai: ");
        for (j=0;j<i;j++){
            fread(&skaicius, sizeof(double), 1, failas);
			if(skaicius > max) {
				max = skaicius;
			}
            printf("%.2f ", skaicius);
        }
		rewind(failas);
		skaicius = 0;
		while (skaicius != max) {
			suma = suma + skaicius;
			fread(&skaicius, sizeof(double), 1, failas);
			i--;
		}
		for (j=0; j<i; j++) {
			fread(&skaicius, sizeof(double), 1, failas);
			sandauga = sandauga * skaicius;
			if (skaicius == max) sandauga = 1;
		}
		if (max == 0) sandauga = 0;

		printf("\nMaksimalus skaicius yra: %.2lf ", max);
		printf("\nSuma yra (iki pirmo maksimalaus): %.2lf", suma);
		printf("\nSandauga yra (nuo paskutinio maksimalaus): %2.lf\n", sandauga);
        fclose(failas);
    }
	system("pause");
	meniu();
}

void Uzduotis_3() {
    int i, reiksme, kiekis;
    MedisPtr saknis = NULL;

	system("cls");
    printf("Uzduotis 3\n\n");
    printf("Sukurti dvejetaini medi, realizuojant elemento iterpimo, pasalinimo, \n");
    printf("spausdinimo bei paieskos funkcijas.");
    printf("Perkelti to saraso visus elementus i dvikrypti ciklini sarasa.\n");
    printf("Atspausdinti visus dvikrypcio ciklinio saraso elementus.\n\n");
    //Meniu
    while (!0) {
        printf("[1] - Iterpti\n");
        printf("[2] - Pasalinti\n");
        printf("[3] - Spausdinti\n");
        printf("[4] - Ieskoti\n");
        printf("[5] - Perkelti visus elementus i dvikrypti ciklini sarasa ir atspausdinti\n");
        printf("[0] - Gryzti atgal\n");
        scanf("%d", &i);
        printf("\n");
        switch (i) {
            case 0:
                meniu();
                exit(0);
                break;
            case 1:
                printf("Kiek bus ivedama reiksmiu?\n");
                printf("?");
                scanf("%d", &kiekis);
                for (i=0; i<kiekis; i++) {
                    printf("Reiksme: ");
                    scanf("%d", &reiksme);
					if(paieska(saknis, reiksme))
					{
						i--;
						printf("Elemento iterpti negalima. Jis jau egzistuoja.\n");
					} else {
						iterpti(&saknis, reiksme);
					}
                }
                printf("\n");
                break;
            case 2:
                printf("Kokia reiksme norite pasalinti?\n");
                printf("Reiksme: ");
                scanf("%d", &reiksme);
                if(paieska(saknis, reiksme)) {
                    printf("Elementas %d sekmingai pasalintas\n", reiksme);
                } else {
                    printf("Tokio elemnto nera!\n");
                }
                printf("\n");
                break;
            case 3:
                printf("Medis:\n");
                spausdinti(saknis);
                printf("\n\n");
                break;
            case 4:
                printf("Ko ieskoti?\n?");
                scanf("%d", &reiksme);
                if(paieska(saknis, reiksme))
                    printf("Reiksme %d yra musu medyje!\n", reiksme);
                else
                    printf("Tokios reiksmes medyje nera!\n");
                break;
            case 5:
                if(saknis == NULL)
                    printf("Medis yra tuscias!\n\n");
                else {
                    MedisToNode(saknis);
                    PrintNode();
               }
                break;
            default:
                printf("Neteisingas pasirinkimas!\n");
                break;
        }
    }
    system("pause");
	meniu();
}

void Uzduotis_4() {
    char simbolis[20];
    sarasasPtr = NULL;

    printf("UZDUOTIS 4\n\n");
    printf("Duotas vienkryptis sarasas. Suskaiciuoti kiek jame yra skirtingu mazuju raidziu\n");
    printf("Iveskite simbolius (teksta)\n");
    printf("Ivedimo pabaiga ctr+z \n");
    printf("?");
    scanf("%s", simbolis);
    while(!feof(stdin)) {
        IterptiSarasa(simbolis);
		SpausdintiSarasa();
		printf("?");
		scanf("%s", simbolis);
    }
}

void iterpti(MedisPtr *MusuMedis, int elem) {
    if(*MusuMedis == NULL) {
        *MusuMedis = (Medis*)malloc(sizeof(Medis));
        (*MusuMedis)->elementas = elem;
        (*MusuMedis)->kaire = NULL;
        (*MusuMedis)->desine = NULL;
    } else if (elem < (*MusuMedis)->elementas) {
        iterpti(&((*MusuMedis)->kaire), elem);
    } else if (elem > (*MusuMedis)->elementas) {
        iterpti(&((*MusuMedis)->desine), elem);
    } else {
        printf("Elemento iterpti negalima. Jis jau egzistuoja.\n");
    }
}

void spausdinti(MedisPtr MusuMedis) {
    if (MusuMedis != NULL) {
        spausdinti(MusuMedis->kaire);
        printf("%3d", MusuMedis->elementas);
        spausdinti(MusuMedis->desine);
    }
}

bool paieska(MedisPtr MusuMedis, int elem) {
	if(MusuMedis == NULL) {
        return false;
	} else if((MusuMedis)->elementas == elem) {
        return true;
	} else if(elem < (MusuMedis)->elementas) {
        return paieska((MusuMedis)->kaire, elem);
	} else {
        return paieska((MusuMedis)->desine, elem);
	}
}

MedisPtr salinti(Medis *MusuMedis, int elem) {
    struct medis *p;

    if(!MusuMedis) {
            return MusuMedis;
    }

    if(MusuMedis->elementas == elem) {
        if(MusuMedis->kaire == MusuMedis->desine) {
            free(MusuMedis);
            return(p);
        } else if(MusuMedis->kaire == NULL) {
            p = MusuMedis->desine;
            free(MusuMedis);
            return(p);
        } else if(MusuMedis->desine == NULL) {
            p = MusuMedis->kaire;
            free(MusuMedis);
            return(p);
        } else {
            p = MusuMedis->kaire;
            while(p->desine != NULL) {
                p = p->desine;
            }
            MusuMedis->elementas = p->elementas;
            MusuMedis->kaire = salinti(MusuMedis->kaire, p->elementas);
        }
    }
    if(MusuMedis->elementas < elem) {
        MusuMedis->desine = salinti(MusuMedis->desine, elem);
    } else {
        MusuMedis->kaire = salinti(MusuMedis->kaire, elem);
    }
    return MusuMedis;
}

void InsertAtTail(int x) {
    struct Node* newNode = GetNewNode(x);

    if(head == NULL) {
        newNode->data = x;
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        newNode->next = head;
        newNode->prev = tail;
        tail = newNode;
        head->prev = tail;
    }
}

void PrintNode() {
    if(head == NULL)
        return;
    struct Node* temp = head;
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while(temp != head);
	printf("\n");
}

void MedisToNode(MedisPtr MusuMedis) {
    if(MusuMedis != NULL) {
		InsertAtTail(MusuMedis->elementas);
		MedisToNode(MusuMedis->kaire);
		MedisToNode(MusuMedis->desine);
	}
}

void IterptiSarasa(char* value) {
    struct sarasas* temp = (struct sarasas*)malloc(sizeof(struct sarasas));
    temp->data = *value;
    temp->next = sarasasPtr;
    sarasasPtr = temp;
}

void SpausdintiSarasa() {
    int mazosraides = 0;
	struct sarasas* temp = sarasasPtr;
    printf("Musu sarasas\n");
    while(temp != NULL) {
        printf("%c ", temp->data);
		temp = temp->next;
    }
	printf("\n");
	printf("Skirtingu mazuju raidziu yra: %d ", mazosraides);
}