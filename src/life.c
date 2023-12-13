#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "inout.h"
#define Time 1

int count(int lig, int col, bool univ[HEIGHT][WIDTH])
{
  int c=0, i, j;
  for(i=-1; i<2;i++)
  {
    for(j=-1; j<2;j++)
    {
      if(lig+i >= 0 && lig+i <= HEIGHT)
      {
        if(col+j >= 0 && col+j <= WIDTH)
        {
          if(lig+i != lig || col+j != col)
          {
            if(univ[lig+i][col+j] == 1)
            {
              c++;
            }
          }

        }
      }
    }
  }
  return c;
}


void evolve(bool univ[HEIGHT][WIDTH])
{
  bool univ2[HEIGHT][WIDTH]={0};
  int neigh;
  for (int i=0; i<HEIGHT; i++)
  {
    for (int j=0; j<WIDTH; j++)
    {
      neigh = count(i,j,univ);
      if(univ[i][j] == 0)
      {
        if(neigh == 3) univ2[i][j] = 1;
      }
      else
      {
        if(neigh <= 1 || neigh >= 4) univ2[i][j] = 0;
        if(neigh == 2 || neigh == 3) univ2[i][j] = 1;
      }
    }
  }
  for (int i=0; i<WIDTH;i++)
  {
    for (int j=0; j<HEIGHT;j++)
    {
      univ[i][j]=univ2[i][j];
    }
  }
}

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
int mode_chosing()
{
  char select_mode;
  int mode = -1;
  while(mode == -1)
  {
  if(select_mode=='M' ||select_mode=='m') mode = 0;
  else if (select_mode=='A' ||select_mode=='a') mode = 1;
  else scanf("%c",&select_mode);
  }
  return mode;
}
int main()
{
  //-----------------------------Début création des variables------------------------------//
  char button_press='0';
  bool univ[HEIGHT][WIDTH];
  const char * seed = "../seeds/beacon-10x10.life"; // seed à placer ici
  int mode;
  int cpt_generation = 0;

  //-----------------------------Fin création des variables------------------------------//
  //----------------------------Demande du mode-------------------------//
  system("clear");
  printf("(A)uto or (M)anual ?\n");
  mode = mode_chosing();
  printf("Mode : %d\n", mode);
  load_seed(seed,univ);
  Display(univ); // Premier affichage


  //----------------------------Début de la boucle -------------------------------------//
  while(1)
  {
    switch(mode)
    {
      case 0:
        scanf("%c",&button_press);
        if (button_press =='q') return 0;       // Q pour quitter
        else if (button_press =='a')
        {
          evolve(univ);
          Display(univ);  // A pour afficher la prochaine génération
        }
        else button_press ='0';
        break;
      case 1:
        evolve(univ);
        Display(univ);
        printf("Generation numéro %d\n", cpt_generation);
        cpt_generation++;
        sleep(Time);
        break;
    }

  }


  return 0;
}
