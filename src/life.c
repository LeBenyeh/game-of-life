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
  srand(time(NULL)); // initialisation de la foncion random
  //-----------------------------Remplissage du tableau aléatoire sur la seed empty------------------------------------//
  for (int i=0; i<HEIGHT; i++)
  {
    for (int j=0; j<WIDTH; j++)
    {
      if(rand()%101<= perc) univ[i][j] = 1; // on module à 101 pour obtenir des valeurs entre 0 et 100.
      else univ[i][j] = 0;
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
//Affiche l'univers
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
  // Cette fonction affiche le menu pour l'utilisateur dans lequel il pourra choisir les differents paramètres proposés en entrant le nombre de la section demandée

  switch (Mode)
  {
    case 0 : //Menu principal
      printf("Menu \n\n");
      printf("1. Seed selection \n");
      printf("2. Universe properties \n");
      printf("3. Life & Death option \n");
      printf("4. Display mode \n\n");
      printf("5. RUN");
      printf("\n\nEnter the section's number ");
      scanf("%d", &Mode);
      system("clear");
      break;

    case 1 :// Menu de sélection des seeds

      printf("Seed selection \n\n");
      printf("1. Beacon \n");
      printf("2. Blinker \n");
      printf("3. Empty \n");
      printf("4. Full \n");
      printf("5. Glider \n");
      printf("6. Random \n\n");
      printf("7. Back to Menu");
      printf("\n\nEnter the section's number ");
      int scanSeed = 0;
      scanf("%d", &scanSeed);

      switch (scanSeed)//Lien de la seed
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

    case 2 : //Section Universe properties
      printf("Universe properties \n\n");
      printf("1. Non-Periodic Universe \n");
      printf("2. Periodic Universe \n");
      printf("\n3. Back to Menu");
      printf("\n\nEnter the section's number ");
      int scanPeriodic;
      scanf("%d", &scanPeriodic);
      switch(scanPeriodic)
      {
        case 1 :
          *Periodic = 0;
          break;
        case 2 :
          *Periodic = 1;
          break;
        case 3 :
          break;
      }
      Mode = 0;
      system("clear");
      break;

    case 3 : //Section life&death option
      printf("Life & Death option \n\n");
      printf("1. Life conditions \n");
      printf("2. Death conditions");
      printf("\n\n3. Back to Menu");
      printf("\n\nEnter the section's number ");
      int scanLife;
      scanf("%d",&scanLife );

      switch(scanLife)
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
        case 3 :
          break;
      }
      Mode = 0;
      system("clear");
      break;

    case 4 : // Section Display mode
      printf("Display Mode \n\n");
      printf("1. Manual \n");
      printf("2. Auto ");
      printf("\n\n3. Back to Menu");
      printf("\n\nEnter the section's number ");
      int scanDisplay;
      scanf("%d",&scanDisplay);
      switch(scanDisplay)
      {
        case 1 :
          *display = 1;
          break;
        case 2 :
          *display = 2;
          break;
        case 3 :
          break;

      }
      Mode = 0;
      system("clear");
      break;
    default :
      printf("!!! ERROR PLEASE ENTER A VALID NUMBER !!!\n");
      Mode = 0;
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
    // Le menu restera jusqu'au 5.RUN, on récupère toutes les valeurs grâce à des pointeurs. Ces valeurs seront utilisées dans la boucle
  }
  load_seed(seed,univ);   // Chargement de la seed dans l'univers
  if(random == 1) randomseed(univ, percentage);
  Display(univ); // Premier affichage
  printf("seed = %s\nPeriodic = %d\nlife = %d\ndeathMin = %d\ndeathMax = %d\ndisplay Mode = %d \n", // affichage des paramètres sélectionnés
         seed, Periodic, life, deathMin, deathMax, display_mode);
  printf("\n\n\n[N]ext Or [S]top :   \n");


  //----------------------------Début de la boucle -------------------------------------//
  while(1)
  {
    switch(display_mode)
    {

      case 1:     // Mode Manuel

        scanf("%c",&button_press);
        if (button_press =='s'||button_press =='S') return 0;       // Q pour quitter
        else if (button_press =='n'||button_press =='N')            // A pour afficher la prochaine génération
        {
          evolve(univ,Periodic,life,deathMin,deathMax);
          Display(univ);
          printf("seed = %s\nPeriodic = %d\nlife = %d\ndeathMin = %d\ndeathMax = %d\ndisplay Mode = %d \n",
                 seed, Periodic, life, deathMin, deathMax, display_mode);
          printf("\n\n\n[N]ext Or [S]top :   ");
        }
        else button_press ='0';
        break;

      case 2:     //Mode automatique

        evolve(univ,Periodic,life,deathMin,deathMax);
        Display(univ);
        printf("Generation number %d\n", cpt_generation);
        printf("seed = %s\nPeriodic = %d\nlife = %d\ndeathMin = %d\ndeathMax = %d\ndisplay Mode = %d \n",
               seed, Periodic, life, deathMin, deathMax, display_mode);
        cpt_generation++;
        sleep(Time);// attente du programme en secondes
        break;
    }

  }


  return 0;
}
