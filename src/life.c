#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "inout.h"
#include <time.h>
#define Time 1

int nmod(int val)
{
  if(val==-1) return HEIGHT-1;
  else return val%HEIGHT;
}

void randomseed(bool univ[HEIGHT][WIDTH],int perc)
{
  srand(time(NULL));
  bool univ2[HEIGHT][WIDTH]={0};
  for (int i=0; i<HEIGHT; i++)
  {
    for (int j=0; j<WIDTH; j++)
    {

      if(rand()%101<= perc) univ2[i][j] = 1;
      else univ2[i][j] = 0;
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


int count(int lig, int col, bool univ[HEIGHT][WIDTH],int Periodic)
{
  int neigh=0, i, j;
  for(i=-1; i<2;i++)
  {
    for(j=-1; j<2;j++)
    {
      if(Periodic == 0 && univ[lig+i][col+j] == 1 && (lig+i >= 0 && lig+i <= HEIGHT && col+j >= 0 && col+j <= WIDTH)&&(lig+i != lig || col+j != col))
      {
        neigh++;
      }
      else if(univ[nmod(lig+i)][nmod(col+j)] == 1 && (lig+i != lig || col+j != col))
      {
        neigh++;
      }
    }
  }
  return neigh;
}

void evolve(bool univ[HEIGHT][WIDTH], int Periodic, int reborn, int mindeath, int maxdeath)
{
  bool univ2[HEIGHT][WIDTH]={0};
  int neigh;
  for (int i=0; i<HEIGHT; i++)
  {
    for (int j=0; j<WIDTH; j++)
    {
      neigh = count(i,j,univ, Periodic);
      if(univ[i][j] == 0)
      {
        if(neigh == reborn) univ2[i][j] = 1;
      }
      else
      {
        if(neigh <= mindeath || neigh >= maxdeath) univ2[i][j] = 0;
        else univ2[i][j] = 1;
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
      printf("%d  ", univ[i][j]);
    }
    printf("\n");
  }
}

int Menu(int Mode, char** seed, int *Periodic, int* life, int* death_min, int* death_max, int* display, int* random, int* percentage )
{

  switch (Mode)
  {
    case 0 :      //Menu principal
      printf("Menu \n\n");
      printf("1. Seed selection \n");
      printf("2. Universe properties \n");
      printf("3. Life & Death option \n");
      printf("4. Display mode \n\n");
      printf("5. RUN \n\n");
      printf("Enter the section's number  ");
      scanf("%d", &Mode);
      system("clear");
      break;

    case 1 :     // Menu de sélection des seeds

      printf("Seed selection \n\n");
      printf("1. Beacon \n");
      printf("2. Blinker \n");
      printf("3. Empty \n");
      printf("4. Full \n");
      printf("5. Glider \n");
      printf("6. Random \n\n");
      printf("7. Back to Menu \n\n");
      printf("Enter the number of a section ");
      int select_seed = 0;
      scanf("%d", &select_seed);

      switch (select_seed)        //Lien de la seed
      {
        case 1 :
          *seed = "../seeds/beacon-10x10.life";
          *random = 0;
          break;
        case 2 :
          *seed = "../seeds/blinker-10x10.life";
          *random = 0;
          break;
        case 3 :
          *seed = "../seeds/empty-10x10.life";
          *random = 0;
          break;
        case 4 :
          *seed = "../seeds/full-10x10.life";
          *random = 0;
          break;
        case 5 :
          *seed = "../seeds/glider-10x10.life";
          *random = 0;
          break;
        case 6 :
          *seed = "../seeds/empty-10x10.life";
          *random = 1;
          printf("Spawning probability (0-100): ");
          scanf("%d",percentage);
          break;
        case 7 :
          break;
      }
      Mode = 0;
      system("clear");
      break;

    case 2 :
      printf("Universe properties \n\n");       //Section Universe properties
      printf("1. Non-Periodic Universe \n");
      printf("2. Periodic Universe \n");
      printf("Enter the number of a section ");
      scanf("%d", Periodic);
      Mode = 0;
      system("clear");
      break;

    case 3 :
      printf("Life & Death option \n\n");         //Section life&death option
      printf("1. Life conditions \n");
      printf("2. Death conditions\n");
      int choix_life;
      scanf("%d",&choix_life );

      switch(choix_life)
      {
        case 1 :
          printf("Number of neighbours to reborn : ");
          scanf("%d", life);
          break;
        case 2 :
          printf("Number of neighbours min to die: ");
          scanf("%d", death_min);
          printf("\n Number of neighbours max to die: ");
          scanf("%d", death_max);
          break;
      }
      Mode = 0;
      system("clear");
      break;

    case 4 :                              // Section Display mode
      printf("Display Mode \n\n");
      printf("1. Manual \n");
      printf("2. Auto \n");
      printf("Enter the number of a section ");
      scanf("%d",display);
      Mode = 0;
      system("clear");
      break;

  }
  return Mode;

}
int main()
{
  //-----------------------------Début création des variables------------------------------//
  char button_press='0';
  bool univ[HEIGHT][WIDTH];
  // Valeurs par défaut
  int mode = 0;   //valeur initiale du mode --> menu de sélection
  int cpt_generation = 0;
  char * seed = "../seeds/beacon-10x10.life"; // seed à placer ici
  int Periodic = 0;
  int life = 3;
  int deathMin = 1;
  int deathMax = 4;
  int display_mode = 1;
  int random = 0;
  int percentage = 50;

  //-----------------------------Fin création des variables------------------------------//
  //----------------------------Demande du mode-------------------------//
  system("clear");
  while (mode != 5)
  {
    mode = Menu(mode,&seed,&Periodic,&life,&deathMin,&deathMax,&display_mode, &random, &percentage);
  }
 // mode = mode_chosing();

  load_seed(seed,univ);
  if(random == 1) randomseed(univ, percentage);
  Display(univ); // Premier affichage


  //----------------------------Début de la boucle -------------------------------------//
  while(1)
  {
    switch(display_mode)
    {

      case 1:

        scanf("%c",&button_press);
        if (button_press =='q') return 0;       // Q pour quitter
        else if (button_press =='a')
        {
          evolve(univ,Periodic,life,deathMin,deathMax);
          Display(univ);  // A pour afficher la prochaine génération
          printf("seed = %s\nPeriodic = %d\nlife = %d\ndeathMin = %d\ndeathMax = %d\ndisplay Mode = %d \n",seed, Periodic, life, deathMin, deathMax, display_mode);
        }
        else button_press ='0';
        break;

      case 2:

        evolve(univ,Periodic,life,deathMin,deathMax);
        Display(univ);
        printf("Generation number %d\n", cpt_generation);
        printf("seed = %s\nPeriodic = %d\nlife = %d\ndeathMin = %d\ndeathMax = %d\ndisplay Mode = %d \n",seed, Periodic, life, deathMin, deathMax, display_mode);
        cpt_generation++;
        sleep(Time);
        break;
    }

  }


  return 0;
}
