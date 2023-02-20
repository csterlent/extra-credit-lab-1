#include <stdio.h>

int main(int argc, char **argv)
{
  // Make sure that the command was formatted right
  if (argc != 2)
  {
    printf("Usage: %s <file>\n", argv[0]);
    return 1;
  }

  // Open the file. Print an error and exit if something goes wrong
  FILE *input = fopen(argv[1], "r");
  if (!input)
  {
    printf("Cannot open %s\n", argv[1]);
    return 2;
  }

  // Get programmer preferences
  // pgprefs[i][j] results in Programmer (i+1)'s ranking for Department (j+1)
  int pgprefs[5][5];

  // Get department preferences
  // dpprefs[i][j] results in Department (i+1)'s ranking for Programmer (j+1)
  int dpprefs[5][5];

  for (int n = 0; n < 10; n++)
  {
    int data[5] = {0};
    fscanf(input, "%d %d %d %d %d",
        &data[0], &data[1], &data[2], &data[3], &data[4]
        );
    // Loop over the data array to store each item separately
    for (int j = 0; j < 5; j++)
    {
      // Calculate the Department or Programmer that this datum ranks
      unsigned int index = data[j]-1;
      if (index >= 5) // Do not use any bad index ever
      {
        return 3;
      }
      if (n < 5) // First 5 lines are Department preferences
      {
        // Interpret n, the line number, as the "cost" of each choice
        dpprefs[j][index] = n;
      }
      else // Last 5 lines are Programmer preferences
      {
        pgprefs[j][index] = n;
      }
    }
  }

  int pgtaken[5] = {0};

  // Loop over Departments to assign
  for (int dpindex = 0; dpindex < 5; dpindex++)
  {
    int *myprefs = dpprefs[dpindex];
    int bestfit;      // Index of the best-fitting Programmer
    int bestcost = 10; // Measure of how fitting the above Programmer is
    // Loop over candidate Programmers
    for (int pgindex = 0; pgindex < 5; pgindex++)
    {
      if (pgtaken[pgindex])
      {
        continue;
      }
      int cost = pgprefs[pgindex][dpindex];
      if (cost > bestcost)
      {
        continue;
      }
      if (cost < bestcost || myprefs[pgindex] < myprefs[bestfit])
      {
        bestfit = pgindex;
        bestcost = cost;
      }
    }
    pgtaken[bestfit] = 1;
    printf("Department #%d will get Programmer #%d\n", dpindex+1, bestfit+1);
  }

  return 0;
}
