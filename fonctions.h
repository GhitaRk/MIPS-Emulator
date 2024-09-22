#ifndef __FONCTIONS_H__
#define __FONCTIONS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_MAX 20

void lire_instruction (char *fichier1, char *fichier2);
void traduction (char *instruction, FILE *fichier_retour);


#endif
