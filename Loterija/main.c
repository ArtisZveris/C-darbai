#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	FILE * failas;
	int Numeris_1, i;
	
	if((failas = fopen("BILIETAI.txt", "w")) == NULL) {
		printf("Klaida atidarant failą BILIETAI.txt\n");
	} else {
		srand(time(NULL));
		for(i=0; i<9999; i++) {
			Numeris_1 = rand() % 9999;
			fprintf(failas, "%04d\n", Numeris_1);
		}
	}
	fclose(failas);
	system("pause");
	return 0;
}
