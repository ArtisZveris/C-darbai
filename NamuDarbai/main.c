#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct medis {
    int elementas;
    struct medis *kaire;
    struct medis *desine;
};

typedef struct medis Medis;
typedef Medis *MedisPtr;

void Uzduotis_1 ();
void Uzduotis_2 ();
void Uzduotis_3 ();
void Uzduotis_4 ();
void iterpti (MedisPtr *, int);
void spausdinti1(MedisPtr);
void spausdinti2(MedisPtr);
void spausdinti3(MedisPtr);
void spausdinti4(MedisPtr);

int main()
{
    Uzduotis_2();
    return 0;
}

void Uzduotis_1() {
    FILE * failas;
    char tekstas[40], eilute[200];
    int skaicius;

    printf("UZDUOTIS 1\n");
    printf("\nDuotas tipinis failas, kurio komponentai simboliai. Rasti kiek zodziu prasideda raide a.\n\n"); //Užduotis

    if ((failas = fopen("failas.dat", "wb")) == NULL){
        printf("Klaida atidarant faila!\n");
    } else {
        printf("Iveskite simbolius (teksta)\n");
        printf("Ivedimo pabaiga ctr+z \n");
        printf("?");
        scanf("%s", tekstas);
        while(!feof(stdin)) {
            fprintf(failas, "%s ", tekstas);
            printf("?");
            scanf("%s", tekstas);
        }
        fclose(failas);
    }

    if ((failas = fopen("failas.dat", "rb")) == NULL) {
        printf("Klaida atidarant faila!\n");
    } else {
        fgets(eilute, sizeof(eilute), failas);
        char *zodis = strtok(eilute, " ,");
        while(zodis != NULL) {
            if(zodis[0] == 'a') skaicius++;
            zodis = strtok(NULL, " ,");
        }
        fclose(failas);
    }

    printf("\nYra %d zodziai su pirma a raide\n", skaicius);
}

void Uzduotis_2() {
    FILE *failas;
    double skaicius;

    printf("UZDUOTIS 2\n\n");
    printf("Diske sukurkite tipizuota realiuju skaiciu faila. Skaiciu kiekis  nera zinomas.\n");
    printf("Po to, skaitydami duomenis is failo, apskaiciuokite suma elementu, esanciu nuo failo\n");
    printf("pradzios iki pirmo maksimalaus elemento (gali buti keli vienodi elementai, kuriu reiksme maksimali).\n");
    printf("Taip pat rasti sandauga elementu, esanciu nuo paskutinio maksimalaus elemento iki failo galo.\n\n");
/*    if((failas = fopen("failas.dat", "wb")) == NULL) {
        printf("Klaida atidarant faila!");
    } else {
        printf("Iveskite realius skaicius\n");
        printf("Ivedimo pabaiga ctr+z \n");
        printf("?");
        scanf("%lf", &skaicius);
        while(!feof(stdin)) {
            fprintf(failas, "%.2f ", skaicius);
            printf("?");
            scanf("%lf", &skaicius);
        }
        fclose(failas);
    }
*/
    if ((failas = fopen("failas.dat", "rb")) == NULL) {
        printf("Klaida atidarant faila!\n");
    } else {
        while(!feof(failas)){
            fscanf(failas, "%lf", &skaicius);
            printf("%.2f\n", skaicius);
        }
    }
}

void Uzduotis_3() {
    int i, reiksme;
    MedisPtr saknis = NULL;
    printf("Sukurti dvejetaini medi, realizuojant elemento iterpimo, pasalinimo, spausdinimo bei paieskos funkcijas.\n");
    printf("Perkelti to saraso visus elementus i dvikrypti ciklini sarasa. \nAtspausdinti visus dvikrypcio ciklinio saraso elementus.\n\n");
    printf("Iveskite 6 reiksmiu i medi\n");
    for (i=0; i<=5; i++) {
        scanf("%d", &reiksme);
        printf("Kita: \n");
        iterpti(&saknis, reiksme);
    }

    printf("Budas nr 1\n");
    spausdinti1(saknis);
    printf("\nBudas nr 2\n");
    spausdinti2(saknis);
    printf("\nBudas nr 3\n");
    spausdinti3(saknis);
    printf("\nBudas nr 4\n");
    spausdinti4(saknis);
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

void spausdinti1(MedisPtr MusuMedis) {
    if (MusuMedis != NULL) {
        spausdinti1(MusuMedis->kaire);
        printf("%3d", MusuMedis->elementas);
        spausdinti1(MusuMedis->desine);
    }
}

void spausdinti2(MedisPtr MusuMedis) {
    if(MusuMedis != NULL){
        printf("%3d", MusuMedis->elementas);
        spausdinti2(MusuMedis->kaire);
        spausdinti2(MusuMedis->desine);
    }
}

void spausdinti3(MedisPtr MusuMedis) {
    if(MusuMedis != NULL){
        spausdinti3(MusuMedis->kaire);
        spausdinti3(MusuMedis->desine);
        printf("%3d", MusuMedis->elementas);
    }
}

void spausdinti4(MedisPtr MusuMedis) {
    if(MusuMedis != NULL) {
        spausdinti4(MusuMedis->desine);
        printf("%3d", MusuMedis->elementas);
        spausdinti4(MusuMedis->kaire);
    }
}

