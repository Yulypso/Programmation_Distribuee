#include <stdio.h>
#include <string.h>

void affichetableau(char ** sentence, int nbmot, int max)
{

	int i,j;

	for(i=0;i<nbmot;i++)
	{
		for(j=0;j<max;j++)
		{
			printf("%s\n", sentence[i][j]);
		}
	}
}


int main(void)
{
char **words;
char sentence[150];
int i=0,j=0,k=0, max=0, word=0;
printf("Entrez votre phrase:");
scanf("%s", sentence);
for(i=0;i<strlen(sentence);i++)
{
	if(sentence[i]==' ')
	{
		word++;
		if(k>max)
		{
			max=k;
		}
		k=0;
	}
	k++;
}
words=(char**)malloc(sizeof(char*)*word);
for(i=0;i<word;i++)
{
	words[i]=(char*)malloc(sizeof(char)*max);
}
i=0;
j=0;
k=0;
while(sentence[i++]!='\0')
(
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
affichetableau(words, word, max);
return 0;
}
