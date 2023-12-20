int nmod(int val)
{
  if(val==-1) return 9;
  else return val%HEIGHT;
}

int finalcount(int lig, int col, bool univ[HEIGHT][WIDTH]
{
  int Periodic, c=0, i, j;
  if(Periodic = 1)
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
