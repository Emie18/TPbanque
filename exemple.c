#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{	
	char  * chaine;
	int un;
	chaine = malloc(sizeof(char *) * 50);
	int nombre = 0;
	for ( int i = 0;i<4;i++)
	{
		printf("nombre :%d\n",nombre);
		nombre ++;
	}
	
	do
	{
		
		printf("Tapez '1' pour sortir\n");
		fgets(chaine,50,stdin);
		chaine[strlen(chaine)-1] = '\0';
		un = atoi(chaine);

	}while(un != 1);

	return 0;
 
	
}
