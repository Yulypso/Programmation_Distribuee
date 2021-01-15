#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * INF4033-LAB_1: Evolution de code
 * 28/08/2020
 * @author Thierry Khamphousone
 */

void display_sentence(char ** words, int line);

int main(void)
{
	char * sentence = NULL;
	sentence = (char*) malloc(sizeof(char));
	if(sentence == NULL)
	{
		return EXIT_FAILURE;
	}

	printf("Enter your sentence: ");
	scanf("%[^\n]", sentence);

	/*** Pour déterminer nombre de lignes et colonnes ***/
	int nbSpace=1, maxWordSize=1, maxWordSizeTmp=1;
	for(int p=0; p<strlen(sentence); p++)
	{
		maxWordSizeTmp++;
		if(sentence[p]==' ')
		{
			nbSpace++;
			if(maxWordSize < maxWordSizeTmp)
				maxWordSize = maxWordSizeTmp;
			maxWordSizeTmp=0;
		}
	}
	/****************************************************/

	char ** words=NULL;
	words = (char **) malloc((nbSpace) * sizeof(char*));
	for(int m=0; m<nbSpace; m++)
	{
		words[m] = (char*) malloc((maxWordSize) * sizeof(char));
	}
	if(words == NULL)
		return EXIT_FAILURE;

	int i=0, j=0, k=0;
	do
	{
		if(sentence[i]!=' ')
			words[j][k++]=sentence[i];
		else
		{
			words[j++][k]='\0';
			k=0;
		}
	} while(sentence[i++]!='\0');

	display_sentence(words, nbSpace);

	free(sentence);
	for(int u=0; u<nbSpace; u++){
		free(words[u]);
	}
	free(words);

	return EXIT_SUCCESS;
}

void display_sentence(char ** words, int line)
{
	printf("\n");
	for(int i=0;i<line;i++)
		printf("%s\n", words[i]);
}
