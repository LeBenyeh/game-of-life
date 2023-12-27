void randomseed(bool univ[HEIGHT][WIDTH],int perc) 
{
  srand(time(NULL));
  bool univ2[HEIGHT][WIDTH]={0};
  for (int i=0; i<HEIGHT; i++)
  {
    for (int j=0; j<WIDTH; j++)
    {

      if(rand()%101< perc) univ2[i][j] = 1;
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

int nmod(int val)
{
  if(val==-1) return HEIGHT-1;
  else return val%HEIGHT;
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
