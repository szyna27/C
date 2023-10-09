#include<stdio.h>
#include<stdlib.h>
#define _USE_MATH_DEFINES
#include<math.h>
#pragma warning(disable: 4996)

#define M 100
#define eps 0.001

double szereg(double x, int &kp, int &lw) {
	int m = M * 2;
	double pwyraz, wyraz, wynik;
	char z = '-';

	while (x > M_PI) x -= 2 * M_PI;
	while (x < -M_PI) x += 2 * M_PI;

	kp = 0;
	lw = 1;
	wynik = pwyraz = wyraz = x;
	if (fabs(wyraz) < eps) {
		kp++;
		return wynik;
	}

	for (int i = 3; i < m; i += 2){
		wyraz = pwyraz * pow(x, 2) / i / (i-1);
		pwyraz = wyraz;
		lw++;
		if (z == '+') {
			wynik += wyraz;
			z = '-';
		}
		else {
			wynik -= wyraz;
			z = '+';
		}
		if (fabs(wyraz) < eps) {
			if (i == m - 1)
				kp++;
			kp++;
			break;
		}
	}
	return wynik;
}

int main() {
	double a, b, p, krok;
	int n, kp = 0, lw = 0;
	char kod[3][25] = {"limit wyrazow", "osiagniecie dokladnosci", "oba jednoczesnie"};
	FILE* fw = NULL;
	fw = fopen("projekt1.txt", "w");
	if (fw == NULL) {
		fprintf(stderr, "Nie mogę otworzyć pliku projekt1.txt do zapisu!\n");
		exit(1);
	}

	printf("Podaj granice przedzialu: [a,b] - liczby rzeczywiste\na = ");
	scanf("%lf", &a);
	printf("b = ");
	scanf("%lf", &b);
	printf("Na ile czesci chcesz podzielic przedzial?\nn = ");
	scanf("%d", &n);

	printf("---------------------------------------------------------------------------------------------------------------\n");
	printf("\tx\t\t\tf_szereg(x)\t\tf_scisle\tlw szeregu\twarunek stopu\n");
	printf("---------------------------------------------------------------------------------------------------------------\n");

	fprintf(fw,"-------------------------------------------------------------------------------------------\n");
	fprintf(fw,"\tx\t\t\tf_szereg(x)\t\tf_scisle\tlw szeregu\twarunek stopu\n");
	fprintf(fw,"-------------------------------------------------------------------------------------------\n");

	krok = (b - a) / n;
	for (double x = a; x < b + 0.5 * krok; x += krok) {
		p = szereg(x, kp, lw);
		printf("%16.9lf\t%16.9lf\t%16.9lf\t%d\t\t%s\n", x, p, sin(x), lw, kod[kp]);
		fprintf(fw, "%16.9lf\t%16.9lf\t%16.9lf\t%d\t\t%s\n", x, p, sin(x), lw, kod[kp]);
	}

	if (fw) {
		fclose(fw);
		fw = NULL;
	}

	return 0;
}