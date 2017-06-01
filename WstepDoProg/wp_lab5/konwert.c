#include <stdio.h>

float MetrNaCale(float metry){
	return 39.37 * metry;
}

float CaleNaMetry(float cale){
	return 0.0254 * cale; 
}

float KmNaMile(float km){
	return 0.62137119 * km;
}

float MileNaKm(float mile){
	return 1.609344 * mile;
}

float PodajLiczbe(){
	float a;
	printf("Podaj dlugosc: ");
	scanf("%f", &a);
	return a;
}

float wynik;

int main(){
	int wybor;
	float odcinek;
	printf("Wybierz z jakiej jednostki na jaka chcesz zamienic.");
	printf("\n1.Metry na cale\n2.Cale na metry\n3.Kilometry na Mile\n4.Mile na kilometry\n>> ");
	scanf("%d", &wybor);

	switch(wybor) {
		case 1: 
			odcinek=PodajLiczbe();
			wynik=MetrNaCale(odcinek);
			printf("%f metr = %f cal\n",odcinek,wynik);
			break;
		case 2:
			odcinek=PodajLiczbe();
			wynik=CaleNaMetry(odcinek);
			printf("%f cal = %f metr\n",odcinek,wynik);
			break;
		case 3:
			odcinek=PodajLiczbe();
			wynik=KmNaMile(odcinek);
			printf("%f km = %f mile\n",odcinek,wynik);
			break;
		case 4:
			odcinek=PodajLiczbe();
			wynik=MileNaKm(odcinek);
			printf("%f mile = %f km\n",odcinek,wynik);
			break;
	}

	return 0;
}
