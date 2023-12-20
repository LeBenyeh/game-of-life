int nmod(int val)
{
  if(val==-1) return 9;
  else return val%HEIGHT;
}

int count(int lig, int col, bool univ[HEIGHT][WIDTH])
{
  int Periodic, c=0, i, j;
  if(Periodic == 1)
  {
    for(i=-1; i<2;i++)
    {
      for(j=-1; j<2;j++)
      {
        if(lig+i >= 0 && lig+i <= HEIGHT && col+j >= 0 && col+j <= WIDTH)
        {
          if(lig+i != lig || col+j != col)
          {
            if(univ[lig+i][col+j] == 1)
            {
              c++;
  }}}}}}
  else
  {
    for(i=-1; i<2;i++)
    {
      for(j=-1; j<2;j++)
      {
        if(lig+i != lig || col+j != col)
        {
          if(univ[nmod(lig+i)][nmod(col+j)] == 1)
          {
            c++;
  }}}}}
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
