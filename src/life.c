#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "inout.h"
void Display(bool univ[HEIGHT][WIDTH])
{
  system("clear");
  for (int i =0; i<WIDTH;i++)
  {
    for(int j=0; j<HEIGHT; j++)
    {
      printf("%d", univ[i][j]);
    }
    printf("\n");
  }
}

int main() {

  //-----------------------------Début création des variables------------------------------//
  char button_press='0';
  bool univ[HEIGHT][WIDTH];
  const char * seed = "../seeds/beacon-10x10.life"; // seed à placer ici

  //-----------------------------Fin création des variables------------------------------//


  load_seed(seed,univ);
  Display(univ); // Premier affichage

  //----------------------------Début de la boucle -------------------------------------//
  while(1)
  {

    scanf("%c",&button_press);
    if (button_press =='q') return 0;       // Q pour quitter
    else if (button_press =='a') Display(univ);  // A pour afficher la prochaine génération
    else button_press ='0';
  }

  return 0;
}
