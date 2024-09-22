#include "fonctions.h"


// fonction qui convertie un string binaire negatif en positif
void NegToPos(char *nbr, int taille)
{
  int i, retenue = 1;
  for (i=taille-1; i>=0; i--) { // complément à 1
    if(nbr[i]=='0')  nbr[i]= '1';
    else if (nbr[i]=='1') nbr[i]='0';
  }
  for (i=taille-1; i>=0; i--) {
    if (nbr[i] == '0' && retenue == 0) {
      nbr[i] = '0';
    }
    else if (nbr[i] == '1' && retenue == 0) {
      nbr[i] = '1';
    }
    else if (nbr[i] == '0' && retenue == 1) {
      nbr[i] = '1';
      retenue = 0;
    }
    else if (nbr[i] == '1' && retenue == 1) {
      nbr[i] = '0';
      retenue = 1;
    }
  }
  if (retenue == 1) printf("Erreur, nbr trop petit\n");
}


// fonction qui convertie un string decimal en binaire (taille est le nombre de bit de retour)
char * decToBin(char *decimale, int taille)
{
  int negatif = 0;
  char *binaire = malloc(taille * sizeof(char));
  int *tab = malloc(taille * sizeof(int));
  int i, j = 0, nbr = atoi(decimale); // converti le string en int

  if (decimale[0] == '-') {
    negatif = 1;
    nbr = -nbr;
  }


  for(i=0; i<taille; i++) binaire[i] = '0';
  for(i=0; i<taille; i++) tab[i] = 0;

  for(i=0; nbr > 0; i++) {
  tab[i] = nbr%2;
  nbr = nbr/2;
  }
  for(i=taille-1; i>=0; i--) {
    binaire[j] = tab[i] + 48;
    j ++;
  }
  if (negatif == 1) NegToPos(binaire, taille);
  return binaire;
}


//Ecrit l'instruction en hexa dans le fichier de retour
void binToHex(FILE *fichier, char *instruction)
{
  int i = 0;
  while(i < 32) {
    if (instruction[i] == '0' && instruction[i+1] == '0' && instruction[i+2] == '0' && instruction[i+3] == '0') fprintf(fichier, "0");
    else if (instruction[i] == '0' && instruction[i+1] == '0' && instruction[i+2] == '0' && instruction[i+3] == '1') fprintf(fichier, "1");
    else if (instruction[i] == '0' && instruction[i+1] == '0' && instruction[i+2] == '1' && instruction[i+3] == '0') fprintf(fichier, "2");
    else if (instruction[i] == '0' && instruction[i+1] == '0' && instruction[i+2] == '1' && instruction[i+3] == '1') fprintf(fichier, "3");
    else if (instruction[i] == '0' && instruction[i+1] == '1' && instruction[i+2] == '0' && instruction[i+3] == '0') fprintf(fichier, "4");
    else if (instruction[i] == '0' && instruction[i+1] == '1' && instruction[i+2] == '0' && instruction[i+3] == '1') fprintf(fichier, "5");
    else if (instruction[i] == '0' && instruction[i+1] == '1' && instruction[i+2] == '1' && instruction[i+3] == '0') fprintf(fichier, "6");
    else if (instruction[i] == '0' && instruction[i+1] == '1' && instruction[i+2] == '1' && instruction[i+3] == '1') fprintf(fichier, "7");
    else if (instruction[i] == '1' && instruction[i+1] == '0' && instruction[i+2] == '0' && instruction[i+3] == '0') fprintf(fichier, "8");
    else if (instruction[i] == '1' && instruction[i+1] == '0' && instruction[i+2] == '0' && instruction[i+3] == '1') fprintf(fichier, "9");
    else if (instruction[i] == '1' && instruction[i+1] == '0' && instruction[i+2] == '1' && instruction[i+3] == '0') fprintf(fichier, "A");
    else if (instruction[i] == '1' && instruction[i+1] == '0' && instruction[i+2] == '1' && instruction[i+3] == '1') fprintf(fichier, "B");
    else if (instruction[i] == '1' && instruction[i+1] == '1' && instruction[i+2] == '0' && instruction[i+3] == '0') fprintf(fichier, "C");
    else if (instruction[i] == '1' && instruction[i+1] == '1' && instruction[i+2] == '0' && instruction[i+3] == '1') fprintf(fichier, "D");
    else if (instruction[i] == '1' && instruction[i+1] == '1' && instruction[i+2] == '1' && instruction[i+3] == '0') fprintf(fichier, "E");
    else if (instruction[i] == '1' && instruction[i+1] == '1' && instruction[i+2] == '1' && instruction[i+3] == '1') fprintf(fichier, "F");
    i += 4;
  }
  fprintf(fichier, "\n");
}

// fonction qui récupère un élement de l'instruction et retourne l'indice de fin de cet élement dans l'instruction
int recuperer_elem(char *instruction, char *element, int indice)
{
  int i = 0;
  while(instruction[indice] == ' ' || instruction[indice] == ',' || instruction[indice] == '(' || instruction[indice] == '$' || instruction[indice] == ')') indice ++;
  while(instruction[indice] != ' ' && instruction[indice] != ',' && instruction[indice] != '(' && instruction[indice] != '$' && instruction[indice] != ')') {
    element[i] = instruction[indice];
    indice ++;
    i ++;
  }
  return indice;
}

// récupère chaque ligne d'instruction une par une est la traduit via "traduction()"
void lire_instruction (char *fichier1, char *fichier2)
{
  int i, j = 0;
  char *instruction = malloc(TAILLE_MAX * sizeof(char));

  FILE * fichier, *fichier_retour;
  fichier = fopen(fichier1, "r");
  fichier_retour = fopen(fichier2, "w");
  if(fichier == NULL || fichier_retour == NULL) {
    perror("Probleme ouverture fichier");
    exit(1);
  }

  while(fgets(instruction, TAILLE_MAX, fichier) != NULL) { //tant qu'on n'est pas à la fin du fichier
    fseek(fichier, j, SEEK_SET);
    fgets(instruction, TAILLE_MAX, fichier);
    i = strlen(instruction);
    j+=i;
    traduction(instruction, fichier_retour);
  }

  fclose(fichier);
  fclose(fichier_retour);
  free(instruction);
}



//fonctions qui recoit l'instruction sous forme assembleur et l'ecrit en hexa dans le fichier retour
void traduction (char *instruction, FILE *fichier_retour)
{
  char *test = malloc(5 * sizeof(char));
  char *instruction_bin = malloc(32 * sizeof(char)); //contient l'instruction en binaire
  char *opcode = malloc(6 * sizeof(char));
  char *registre = malloc(2 * sizeof(char));
  char *registre2 = malloc(2 * sizeof(char));
  char *registre3 = malloc(2 * sizeof(char));
  char *rs = malloc(5 * sizeof(char));
  char *rt = malloc(5 * sizeof(char));
  char *rd = malloc(5 * sizeof(char));
  char *sa = malloc(5 * sizeof(char));
  char *base = malloc(5 * sizeof(char));
  char *instr_index = malloc(26 * sizeof(char));
  char *offset = malloc(16 * sizeof(char));
  char *immediate = malloc(16 * sizeof(char));
  char *mot = malloc (7* sizeof(char));          //contient l'opcode en lettre
  int j = 0;

  j = recuperer_elem(instruction, mot, j);

  if (strcmp(mot,"ADD") == 0) {
    // on récupère les valeurs et les convertit en binaire
    opcode = "100000";
    j = recuperer_elem(instruction, registre, j);
    strncpy(rd, decToBin(registre, 5), 5);
    j = recuperer_elem(instruction, registre2, j);
    strncpy(rs, decToBin(registre2, 5), 5);
    j = recuperer_elem(instruction, registre3, j);
    strncpy(rt, decToBin(registre3, 5), 5);
    // on ecrit les valeurs binaires dans le bon ordre
    strcat(instruction_bin, "000000");
    strcat(instruction_bin, rs);
    strcat(instruction_bin, rt);
    strcat(instruction_bin, rd);
    strcat(instruction_bin, "00000");
    strcat(instruction_bin, opcode);
  }
  else if (strcmp(mot,"ADDI")==0) {
    opcode = "001000";
    j = recuperer_elem(instruction, registre, j);
    strncpy(rt, decToBin(registre, 5), 5);
    j = recuperer_elem(instruction, registre2, j);
    strncpy(rs, decToBin(registre2, 5), 5);
    j = recuperer_elem(instruction, immediate, j);
    strncpy(immediate, decToBin(immediate, 16), 16);

    strcat(instruction_bin, opcode);
    strcat(instruction_bin, rs);
    strcat(instruction_bin, rt);
    strcat(instruction_bin, immediate);
  }
  else if (strcmp(mot,"AND")==0) {
    opcode = "100100";
     // on récupère les valeurs et les convertit en binaire
    j = recuperer_elem(instruction, registre, j);
    strncpy(rd, decToBin(registre, 5), 5);
    j = recuperer_elem(instruction, registre2, j);
    strncpy(rs, decToBin(registre2, 5), 5);
    j = recuperer_elem(instruction, registre3, j);
    strncpy(rt, decToBin(registre3, 5), 5);
    // on ecrit les valeurs binaires dans le bon ordre
    strcat(instruction_bin, "000000");
    strcat(instruction_bin, rs);
    strcat(instruction_bin, rt);
    strcat(instruction_bin, rd);
    strcat(instruction_bin, "00000");
    strcat(instruction_bin, opcode);
  }
  else if (strcmp(mot,"BEQ")==0) {
    opcode = "000100";
    j = recuperer_elem(instruction, registre, j);
    strncpy(rs, decToBin(registre, 5), 5);
    j = recuperer_elem(instruction, registre2, j);
    strncpy(rt, decToBin(registre, 5), 5);
    j = recuperer_elem(instruction, offset, j);
    strncpy(offset, decToBin(offset, 16), 16);

    strcat(instruction_bin, opcode);
    strcat(instruction_bin, rs);
    strcat(instruction_bin, rt);
    strcat(instruction_bin, offset);
  }
  else if (strcmp(mot,"BGTZ")==0) {
    opcode = "000111";
    j = recuperer_elem(instruction, registre, j);
    strncpy(rs, decToBin(registre, 5), 5);
    j = recuperer_elem(instruction, offset, j);
    strncpy(offset, decToBin(offset, 16), 16);

    strcat(instruction_bin, opcode);
    strcat(instruction_bin, rs);
    strcat(instruction_bin, "00000");
    strcat(instruction_bin, offset);
  }
  else if (strcmp(mot,"BLEZ")==0)  {
    opcode = "000110";
    j = recuperer_elem(instruction, registre, j);
    strncpy(rs, decToBin(registre, 5), 5);
    j = recuperer_elem(instruction, offset, j);
    strncpy(offset, decToBin(offset, 16), 16);

    strcat(instruction_bin, opcode);
    strcat(instruction_bin, rs);
    strcat(instruction_bin, "00000");
    strcat(instruction_bin, offset);
  }
  else if (strcmp(mot,"BNE")==0) {
    opcode = "000101";
    j = recuperer_elem(instruction, registre, j);
    strncpy(rs, decToBin(registre, 5), 5);
    j = recuperer_elem(instruction, registre2, j);
    strncpy(rt, decToBin(registre2, 5), 5);
    j = recuperer_elem(instruction, offset, j);
    strncpy(offset, decToBin(offset, 16), 16);

    strcat(instruction_bin, opcode);
    strcat(instruction_bin, rs);
    strcat(instruction_bin, rt);
    strcat(instruction_bin, offset);
  }
  else if (strcmp(mot,"DIV")==0) {
  	opcode = "011010";
    j = recuperer_elem(instruction, registre, j);
    strncpy(rs, decToBin(registre, 5), 5);
    j = recuperer_elem(instruction, registre2, j);
    strncpy(rt, decToBin(registre2, 5), 5);

    strcat(instruction_bin, "000000");
    strcat(instruction_bin, rs);
    strcat(instruction_bin, rt);
    strcat(instruction_bin, "0000000000");
    strcat(instruction_bin, opcode);
  }
  else if (strcmp(mot,"J")==0) {
    opcode = "000010";
    j = recuperer_elem(instruction, registre, j);
    strncpy(instr_index, decToBin(registre, 26), 26);

	strcat(instruction_bin, opcode);
    strcat(instruction_bin, instr_index);

  }
  else if (strcmp(mot,"JAL") == 0) {
    opcode =  "000011";
    j = recuperer_elem(instruction, registre, j);
    strncpy(instr_index, decToBin(registre, 26), 26);

    strcat(instruction_bin, opcode);
    strcat(instruction_bin, instr_index);
  }
  else if (strcmp(mot,"JR") == 0) {
    opcode = "001000";
    j = recuperer_elem(instruction, registre, j);
    strncpy(rs, decToBin(registre, 5), 5);

    strcat(instruction_bin, "000000");
    strcat(instruction_bin, rs);
    strcat(instruction_bin, "0000000000");
    strcat(instruction_bin, "00000");               //  hint ??? pour l'instant on met 00000
    strcat(instruction_bin, opcode);
  }
  else if (strcmp(mot,"LUI") == 0) {
    opcode = "001111";
    j = recuperer_elem(instruction, registre, j);
    strncpy(rt, decToBin(registre, 5), 5);
    j = recuperer_elem(instruction, immediate, j);
    strncpy(immediate, decToBin(immediate, 16), 16);

    strcat(instruction_bin, opcode);
    strcat(instruction_bin, "00000");
    strcat(instruction_bin, rt);
    strcat(instruction_bin, immediate);
  }
  else if (strcmp(mot,"LW") == 0) {
    opcode  = "100011";
    j = recuperer_elem(instruction, registre, j);
    strncpy(rt, decToBin(registre, 5), 5);
    j = recuperer_elem(instruction, offset, j);
    strncpy(offset, decToBin(offset, 16), 16);
    j = recuperer_elem(instruction, base, j);
    strncpy(base, decToBin(base, 5), 5);

    strcat(instruction_bin, opcode);
    strcat(instruction_bin, base);
    strcat(instruction_bin, rt);
    strcat(instruction_bin, offset);
  }
  else if (strcmp(mot,"MFHI") == 0) {
    opcode = "010000";
    j = recuperer_elem(instruction, registre, j);
    strncpy(rd, decToBin(registre, 5), 5);

    strcat(instruction_bin, "0000000000000000");
    strcat(instruction_bin, rd);
    strcat(instruction_bin, "00000");
    strcat(instruction_bin, opcode);
  }
  else if (strcmp(mot,"MFLO") == 0) {
    opcode = "010010";
    j = recuperer_elem(instruction, registre, j);
    strncpy(rd, decToBin(registre, 5), 5);

    strcat(instruction_bin, "0000000000000000");
    strcat(instruction_bin, rd);
    strcat(instruction_bin, "00000");
    strcat(instruction_bin, opcode);
  }
  else if (strcmp(mot,"MULT") == 0) {
    opcode = "011000";
    j = recuperer_elem(instruction, registre, j);
    strncpy(rs, decToBin(registre, 5), 5);
    j = recuperer_elem(instruction, registre2, j);
    strncpy(rt, decToBin(registre2, 5), 5);

    strcat(instruction_bin, "000000");
    strcat(instruction_bin, rs);
    strcat(instruction_bin, rt);
    strcat(instruction_bin, "0000000000");
    strcat(instruction_bin, opcode);
  }
  else if (mot[0] == 'N' && mot[1] == 'O' && mot[2] == 'P') {
    opcode = "000000";
    strcat(instruction_bin, "00000000000000000000000000");
    strcat(instruction_bin, opcode);
  }
  else if (strcmp(mot,"OR") == 0) {
    opcode = "100101";
    j = recuperer_elem(instruction, registre, j);
    strncpy(rd, decToBin(registre, 5), 5);
    j = recuperer_elem(instruction, registre2, j);
    strncpy(rs, decToBin(registre2, 5), 5);
    j = recuperer_elem(instruction, registre3, j);
    strncpy(rt, decToBin(registre3, 5), 5);

    strcat(instruction_bin, "000000");
    strcat(instruction_bin, rs);
    strcat(instruction_bin, rt);
    strcat(instruction_bin, rd);
    strcat(instruction_bin, "00000");
    strcat(instruction_bin, opcode);
  }
  else if (strcmp(mot,"ROTR") == 0) {
    opcode = "000010";
    j = recuperer_elem(instruction, registre, j);
    strncpy(rd, decToBin(registre, 5), 5);
    j = recuperer_elem(instruction, registre2, j);
    strncpy(rt, decToBin(registre2, 5), 5);
    j = recuperer_elem(instruction, registre3, j);
    strncpy(sa, decToBin(registre3, 5), 5);

    strcat(instruction_bin, "00000000001");
                                                    //strcat(instruction_bin, Rl);??
    strcat(instruction_bin, rt);
    strcat(instruction_bin, rd);
    strcat(instruction_bin, sa);
    strcat(instruction_bin, opcode);
  }
  else if (strcmp(mot,"SLL") == 0) {
    opcode = "000000";
    j = recuperer_elem(instruction, registre, j);
    strncpy(rd, decToBin(registre, 5), 5);
    j = recuperer_elem(instruction, registre2, j);
    strncpy(rt, decToBin(registre2, 5), 5);
    j = recuperer_elem(instruction, registre3, j);
    strncpy(sa, decToBin(registre3, 5), 5);

    strcat(instruction_bin, "00000000000");
    strcat(instruction_bin, rt);
    strcat(instruction_bin, rd);
    strcat(instruction_bin, sa);
    strcat(instruction_bin, opcode);
  }
  else if (strcmp(mot,"SLT") == 0) {
    opcode = "101010";
    j = recuperer_elem(instruction, registre, j);
    strncpy(rd, decToBin(registre, 5), 5);
    j = recuperer_elem(instruction, registre2, j);
    strncpy(rs, decToBin(registre2, 5), 5);
    j = recuperer_elem(instruction, registre3, j);
    strncpy(rt, decToBin(registre3, 5), 5);

    strcat(instruction_bin, "000000");
    strcat(instruction_bin, rs);
    strcat(instruction_bin, rt);
    strcat(instruction_bin, rd);
    strcat(instruction_bin, "00000");
    strcat(instruction_bin, opcode);
  }
  else if (strcmp(mot,"SRL") == 0) {
    opcode = "000010";
    j = recuperer_elem(instruction, registre, j);
    strncpy(rd, decToBin(registre, 5), 5);
    j = recuperer_elem(instruction, registre2, j);
    strncpy(rt, decToBin(registre2, 5), 5);
    j = recuperer_elem(instruction, registre3, j);
    strncpy(sa, decToBin(registre3, 5), 5);

    strcat(instruction_bin, "00000000000");     //R0??
    strcat(instruction_bin, rt);
    strcat(instruction_bin, rd);
    strcat(instruction_bin, sa);
    strcat(instruction_bin, opcode);
  }
  else if (strcmp(mot,"SUB") == 0) {
    opcode = "100010";
    j = recuperer_elem(instruction, registre, j);
    strncpy(rd, decToBin(registre, 5), 5);
    j = recuperer_elem(instruction, registre2, j);
    strncpy(rs, decToBin(registre2, 5), 5);
    j = recuperer_elem(instruction, registre3, j);
    strncpy(rt, decToBin(registre3, 5), 5);

    strcat(instruction_bin, "000000");
    strcat(instruction_bin, rs);
    strcat(instruction_bin, rt);
    strcat(instruction_bin, rd);
    strcat(instruction_bin, "00000");
    strcat(instruction_bin, opcode);
  }
  else if (strcmp(mot,"SW") == 0) {
    opcode = "101011";
    j = recuperer_elem(instruction, registre, j);
    strncpy(rt, decToBin(registre, 5), 5);
    j = recuperer_elem(instruction, offset, j);
    strncpy(offset, decToBin(offset, 16), 16);
    j = recuperer_elem(instruction, registre2, j);
    strncpy(base, decToBin(registre2, 5), 5);

    strcat(instruction_bin, opcode);
    strcat(instruction_bin, base);
    strcat(instruction_bin, rt);
    strcat(instruction_bin, offset);
  }
  else if (strcmp(mot,"SYSCALL")==0) {
    opcode = "001100";

    strcat(instruction_bin,"000000");
    strcat(instruction_bin, "00000000000000000000");  // code ????  pour l'instant on met 0
    strcat(instruction_bin, opcode);

  }
  else if (strcmp(mot,"XOR") == 0) {
    opcode = "100110";
    j = recuperer_elem(instruction, registre, j);
    strncpy(rd, decToBin(registre, 5), 5);
    j = recuperer_elem(instruction, registre2, j);
    strncpy(rs, decToBin(registre2, 5), 5);
    j = recuperer_elem(instruction, registre3, j);
    strncpy(rt, decToBin(registre3, 5), 5);

    strcat(instruction_bin, "000000");
    strcat(instruction_bin, rs);
    strcat(instruction_bin, rt);
    strcat(instruction_bin, rd);
    strcat(instruction_bin, "00000");
    strcat(instruction_bin, opcode);
  }
  binToHex(fichier_retour, instruction_bin);

}
