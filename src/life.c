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
int main() {
  // Simple example. Replace by your own code.
  char button_press='0';
  bool univ[HEIGHT][WIDTH];
  while(1)
  {
      button_press ='0';
      load_seed("../seeds/beacon-10x10.life",univ);
      system("clear");
      Display(univ);
      while(button_press != 'a')
      {
        scanf("%c",&button_press);
        if (button_press =='q') return 0;
      }
      load_seed("../seeds/blinker-10x10.life",univ);
      system("clear");
      Display(univ);
      button_press ='0';
      while(button_press != 'a')
      {
        scanf("%c",&button_press);
        if (button_press =='q') return 0;
      }
  }

  return 0;
}
