#include <stdio.h>

int main()
{
	int nombre = 0;
	for ( int i = 0;i<4;i++)
	{
		printf("nombre :%d\n",nombre);
		nombre ++;
	}
	int jeu = 10 ;
	int plus;
	printf("10 + ");
	scanf("%d",&plus);
	jeu = 10 + plus;
	printf("= %d\n",jeu);
}
