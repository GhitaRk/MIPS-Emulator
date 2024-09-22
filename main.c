#include "fonctions.h"






void recupererInstru(int pc, FILE* fichier, char* instruction)
{
    int i=0,j=0;
	 while(pc != 0)
        {
        fseek(fichier, j, SEEK_SET);
        fgets(instruction, 20, fichier);
        i = strlen(instruction);
        j+=i;
        pc--;
        }
}


int main(int argc, char * argv[])
{
    char* instruction = malloc(20*sizeof(char));
    FILE *fich;
    fich = fopen("in3.txt","r");
    if(fich != NULL)
    {
        recupererInstru(10, fich, instruction);
        printf("%s\n",instruction);
    }
    else{
     printf("error");
    }fclose(fich);
  return 0;
}
