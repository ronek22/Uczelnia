#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#define SIZE 20 //SIZE - max dlugosc wyrazu

FILE *otworzPlik(char *nazwa, char *tryb);
void dodajSlowka(char *nazwa);
void losowanie(int kol[],int halfLicz);
void odpowiedz(char **lang, char **trans,char *from, char *to,int *kol, int size, int tr, int fls);
void usuwanie(char *nazwa);
void fiszki(char *nazwa);
void directory(char *folder, char *wyraz);

int main(){
	char wybor;
	char wyraz[20];
	char plik[30];
	int rodzaj;
	system("clear");
	printf("Witamy w programie 'Fiszki'\n");

	do
	{
		printf("Co wybierasz?\n1. Pocwicz slowka\n2. Dodaj nowe slowka do bazy\n3. Usuwanie\n4. Koniec\n>> ");
		scanf("%c", &wybor);
		system("clear");
		switch(wybor){
			case '1':
						printf("Czego chcesz sie uczyc?\n");
						directory("data",wyraz);
						snprintf(plik,30,"data/%s",wyraz);
						fiszki(plik);
						break;

			case '2':
						printf("Do którego pliku chcesz dodac slowka?\n");
						directory("data",wyraz);
						snprintf(plik,30,"data/%s",wyraz);
						system("clear");
						dodajSlowka(plik);
						break;

			case '3':
						printf("Z którego pliku chcesz usunac wyraz?\n");
						directory("data",wyraz);
						snprintf(plik,30,"data/%s",wyraz);
						system("clear");
						usuwanie(plik);
						break;

			default:
				printf("Do zobaczenia!\n");
		}//endswitch
	}while(wybor=='1' || wybor =='2' || wybor=='3');//endwhile

	return 0;
}

FILE *otworzPlik(char *nazwa, char *tryb){
	FILE *fp;
	if((fp=fopen(nazwa,tryb))==NULL) {
		printf("Nie moge otworzyc pliku\n");
		exit(1);
	}
	return fp;
}

void dodajSlowka(char *nazwa){
	FILE *plik = otworzPlik(nazwa,"a");
	int n,i;
	char ang[SIZE],pol[SIZE];

	printf("Ile slowek chcesz dodac? ");
	scanf("%d", &n);
	getchar(); //oczyszyczenie bufora

	for(i=0;i<n;i++){
		system("clear");
		printf("Wprowadź słówko po angielsku!\n");
		fgets(ang,SIZE,stdin); // zwraca z enterem
		printf("Wprowadz tlumaczenie.\n");
		fgets(pol,SIZE,stdin);
		fprintf(plik,"%s", ang);
		fprintf(plik,"%s", pol);
	}
	system("clear");
	fclose(plik);
}

void losowanie(int kol[],int halfLicz){
  int i,j;
  kol[0] = rand()%halfLicz;
  for(i = 1; i<halfLicz; i++){ //losowanie indeksow
      kol[i] = rand() % halfLicz;
      j = 0;
      for(j = 0; j<i; j++){
          while(kol[i] == kol[j]){
              kol[i] = rand()%halfLicz;
              j = 0;
          }
      }
  }
}

void odpowiedz(char **lang, char **trans,char *from, char *to,int *kol, int size, int tr, int fls){
	char odp[SIZE];
	char stillPlay;
	int temp=0;
	getchar(); //oczyszyczenie bufora
	int i;
	for(i = 0; i<size;i++)
	{
		if(fls<3)
		{
		system("clear");
		printf("\nPo %s: %sA po %s: ", from, lang[kol[i]], to);
		fgets(odp,SIZE,stdin);

				if(strcmp(odp,trans[kol[i]])==0)
				{
						printf("Gratulacje poprawna odpowiedz\n");
						while( getchar() != '\n' );
						tr++;
				} else
				{
						printf("Niestety zla odpowiedz\n");
						printf("\nPoprawna odpowiedz to:\n%s\n", trans[kol[i]]);
						while( getchar() != '\n' );
						fls++;
				}
		} else {
			printf("3 bledne odpowiedzi.\nGrasz dalej[c], czy od nowa[dow.klawisz]?\n\n");
			scanf("%c", &stillPlay);
			if(stillPlay=='c')
			{
				temp+= fls;
				fls = 0;
				getchar();
				continue;
			}
			else
				break;
		}

	}

	fls = temp+fls;
	printf("Twoj wynik\n===============\n%d pkt.\nPoprawnych: %d\nBlednych: %d\n\n", tr-fls,tr,fls);
	while( getchar() != '\n' );
}

void usuwanie(char *nazwa){
	FILE *plik=otworzPlik(nazwa,"r");
	char wers[SIZE];
	char **pol;
	char **ang;
	int i, j, licz = 0,indAn = 0,indPl = 0,usun;

	while(fgets(wers,SIZE,plik) != NULL) licz++;
	int halfLicz = licz/2;

	pol = malloc(halfLicz*sizeof(char*));
	ang = malloc(halfLicz*sizeof(char*));

	for (i = 0; i < halfLicz; i++){
			pol[i] = malloc((SIZE+1) * sizeof(char));
			ang[i] = malloc((SIZE+1)* sizeof(char));
	}

	rewind(plik);

	//kopiowanie wyrazow do odp. tablic
	licz = 0;
	while(fgets(wers,SIZE,plik)!=NULL){
		if(licz%2==0){
				strcpy(ang[indAn],wers);
				indAn++;
		} else {
				strcpy(pol[indPl],wers);
				indPl++;
		}
		licz++;
	}

	for(i=0; i<halfLicz;i++){
		printf("%d.%s",i,ang[i]);
	}

	printf("Ktory wyraz chcesz usunac?\n");
	scanf("%d", &usun);

	fclose(plik);


	FILE *zapis = otworzPlik(nazwa,"w");

	for(i=0; i<halfLicz;i++){
		if(i==usun){
			//do nothing
		} else{
			fprintf(zapis,"%s", ang[i]);
			fprintf(zapis,"%s", pol[i]);
		}
	}

	system("clear");
	free(pol);
	free(ang);
	fclose(zapis);

}

void fiszki(char *nazwa) {
		FILE *plik=otworzPlik(nazwa,"r");
		char wers[SIZE];
		char **pol;
		char **ang;
		int *kol; //kolejnosc
		int i, j, licz = 0,indAn = 0,indPl = 0, prawda = 0, falsz = 0,choose;
		char stillLearn;
		srand(time(NULL)); //uruchomienie generatora


		while(fgets(wers,SIZE,plik) != NULL) licz++;
		int halfLicz = licz/2;

		pol = malloc(halfLicz*sizeof(char*));
		ang = malloc(halfLicz*sizeof(char*));
		kol = malloc(halfLicz*sizeof(int));

		for (i = 0; i < halfLicz; i++){
				pol[i] = malloc((SIZE+1) * sizeof(char));
				ang[i] = malloc((SIZE+1)* sizeof(char));
		}

		rewind(plik);

		//kopiowanie wyrazow do odp. tablic
		licz = 0;
		while(fgets(wers,SIZE,plik)!=NULL){
			if(licz%2==0){
					strcpy(ang[indAn],wers);
					indAn++;
			} else {
					strcpy(pol[indPl],wers);
					indPl++;
			}
			licz++;
	}

		printf("1.Angielsko-polskie\n2.Polsko-Angielskie\n>> ");
		scanf("%d", &choose);

		switch (choose) {
			case 1:
				printf("Angielsko-Polskie\n");
				do{
					losowanie(kol,halfLicz);
					odpowiedz(ang, pol,"angielsku", "polsku",kol,indAn,prawda,falsz);
					printf("Czy chcesz jeszcze ćwiczyć?\nJeśli tak, wcisniej [1],\njeśli nie, wcisnij cokolwiek innego\ni zatwierdz.");
					scanf("%c", &stillLearn);
				}while(stillLearn=='1');

				break;
			case 2:
				printf("Polsko-Angielskie\n");
				do{
					losowanie(kol,halfLicz);
					odpowiedz(pol, ang,"polsku","angielsku",kol,indAn,prawda,falsz);
					printf("Czy chcesz jeszcze ćwiczyć?\nJeśli tak, wcisniej [1],\njeśli nie, wcisnij cokolwiek innego\ni zatwierdz.");
					scanf("%c", &stillLearn);
				}while(stillLearn=='1');
				break;
			default:
				printf("Nie ma takiej opcji\n");
				break;
		}
		system("clear");

		//zwolnienie pamieci z tabelii
		free(pol);
		free(ang);
		free(kol);

		fclose(plik);
}

void directory(char *folder, char *wyraz){
	char **pliki;
	int wybor,i;

	pliki = malloc(20*sizeof(char*));
	for (i = 0; i < 20; i++)
		pliki[i] = malloc((21)* sizeof(char));

	i = 0;
	DIR *d;
	struct dirent *dir;
	d = opendir(folder);
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			if(dir->d_type == DT_REG)
			{
				pliki[i]=dir->d_name;
				i++;
				printf("%d. %s\n", i, dir->d_name);
			}
		}
		closedir(d);
	}

	do
	{
		printf("%s", ">> ");
		scanf("%d", &wybor);
		wybor--;
		if (wybor>i-1 || wybor < 0){
			printf("Nie ma takiego pliku! Wprowadz jeszcze raz\n");
			continue;
		}
		strcpy(wyraz, pliki[wybor]);

	}while(wybor>i-1 || wybor <0);


	free(pliki);
}
