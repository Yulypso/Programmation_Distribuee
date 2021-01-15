#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/* Correction par Thierry Khamphousone */ 
/* TD2 : Programmation Système */ 

void affichetableau(char ** sentence, int nbmot, int max)
{
	int i,j;

	for(i=0;i<nbmot;i++)
	{
		for(j=0;j<max;j++)
		{
			printf("%c", sentence[i][j]); 
			//on affiche char par char
		}
		printf("\n");
		//le saut de ligne doit s'effectuer après le mot
	}
}


int main(void)
{
	char **words;
	char sentence[150];
	int i=0,j=0,k=0;
	printf("Entrez votre phrase:");
	scanf("%[^\n]", sentence); //pour récupérer toute la phrase et non seulement le premier mot.

	int max=1, word=1; //il y a minimum 1 mot de taille 1
	
	for(i=0;i<strlen(sentence);i++)
	{
		k++;
		if(sentence[i]==' ')
		{
			word++;
			k=0;
		}
		if(k>max)
		{
			max=k;
		}
		//k++; il faut compter avant, sinon le premier n'est pas compté 
	}

	words=(char**)malloc(sizeof(char*)*word);


	for(i=0;i<word;i++)
	{
		words[i]=(char*)malloc(sizeof(char)*max);
	}



	
	
	i=0;
	j=0;
	k=1; //car on doit rajouter la première occurence 

	while(sentence[i++]!='\0') //on oublie la première occurence...
	{
	 	if(sentence[i]!=' ')
		{
			words[j][k++]=sentence[i];
		}
		else
		{
			words[j++][k]='\0';
			k=0;
		}
	} 
	
	words[0][0]=sentence[0]; //première occurence rajoutée

	affichetableau(words, word, max);


	for(int u=0; u<word; u++){ //penser à free les mallocs.
		free(words[u]);
	}
	free(words);

	return 0;
}
