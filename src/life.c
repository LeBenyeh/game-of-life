#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "inout.h"
void Display(bool univ[HEIGHT][WIDTH])
{
  for (int i =0; i<WIDTH;i++)
  {
    for(int j=0; j<HEIGHT; j++)
    {
      printf("%d", univ[i][j]);
    }
    printf("\n");
  }
}

void next_gen(bool univ[HEIGHT][WIDTH]) // Sert à print l'univers à la génération n+1
{
  load_seed("../seeds/beacon-10x10.life",univ); // A remplacer par l'univers n+1 déjà calculé
  system("clear");
  Display(univ);
}
int main() {

  //-----------------------------Début création des variables------------------------------//
  char button_press='0';
  bool univ[HEIGHT][WIDTH];

  //-----------------------------Fin création des variables------------------------------//
  Display(univ);
  while(1)      // Début de la boucle
  {

    scanf("%c",&button_press);
    if (button_press =='q') return 0;       // Q pour quitter
    else if (button_press =='a') next_gen(univ);  // A pour afficher la prochaine génération
    else button_press ='0';
  }

  return 0;
}
