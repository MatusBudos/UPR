#include <stdio.h>

int main()
{

  int suma = 250;
  int bankovky[] = {5000, 2000, 1000, 500, 200, 100};
  int pocty[] = {0, 0, 0, 0, 0, 0};
  for (int i = 0; i < 6; i++)
  {
    while (suma >= bankovky[i])
    {
      pocty[i]++;
      suma = suma - bankovky[i];
    }
  }
  for (int i = 0; i < 6; i++)
  {
    printf("Bankovka %d: %dx\n", bankovky[i], pocty[i]);
  }

  return 0;
}