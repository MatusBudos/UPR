#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int max_pocet_vyskytov(int *pocet_vyskytov, int velkost_pola)
{
  int max = 0;
  for (int i = 0; i < velkost_pola; i++)
  {
    if (pocet_vyskytov[i] > max)
    {
      max = pocet_vyskytov[i];
    }
  }
  return max;
}

void vytvor_histogram(int pocet_cisel, int rozsah_cisel, int *pocet_vyskytov, int velkost_pola)
{
  int aktualne = 0;
  for (int i = 0; i < pocet_cisel; i++)
  {
    scanf("%d", &aktualne);
    int docasne = 0;
    for (int j = 0; j < velkost_pola - 1; j++)
    {
      if (aktualne == rozsah_cisel + j)
      {
        pocet_vyskytov[docasne] += 1;
        docasne = 0;
        break;
      }
      else if (j == 8)
      {
        pocet_vyskytov[9] += 1;
        docasne = 0;
      }
      docasne += 1;
    }
  }
}

void vykresli_histogram(char druh, int *pocet_vyskytov, int rozsah_cisel, int velkost_pola)
{
  if (druh == 'h')
  {
    int pocet_cifier = (int)log10(rozsah_cisel + 8) + 1;
    for (int i = 0; i < velkost_pola; i++)
    {
      if (i == 9 && pocet_vyskytov[9] != 0)
      {
        printf("invalid: ");
      }
      else if (i != 9)
      {
        if (pocet_vyskytov[i] == 0)
        {
          printf("%*d", pocet_cifier, rozsah_cisel + i);
        }
        else
        {
          printf("%*d ", pocet_cifier, rozsah_cisel + i);
        }
      }
      for (int j = 0; j < pocet_vyskytov[i]; j++)
      {
        printf("#");
      }
      if (i < 9 || pocet_vyskytov[9] != 0)
      {
        printf("\n");
      }
    }
  }
  else if (druh == 'v')
  {
    for (int i = max_pocet_vyskytov(pocet_vyskytov, velkost_pola); i >= 0; i--)
    {
      for (int j = 0; j < 10; j++)
      {
        if (pocet_vyskytov[9] >= i && i != 0 && j == 0)
        {
          printf("#");
        }
        else if (pocet_vyskytov[j - 1] >= i && i != 0 && j != 0)
        {
          printf("#");
        }
        else if (i == 0)
        {
          if (j == 0)
          {
            printf("i");
          }
          else
          {
            printf("%d", j);
          }
        }
        else
        {
          printf(" ");
        }
      }
      printf("\n");
    }
  }
}

int main()
{
  char druh_histogramu;
  int velkost_pola = 10;
  int pocet_vyskytov[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int pocet_cisel = 0;
  int zaciatok_rozsahu = 0;
  scanf("%c", &druh_histogramu);
  scanf("%d %d", &pocet_cisel, &zaciatok_rozsahu);

  switch (druh_histogramu)
  {
  case ('h'):
    if (pocet_cisel >= 0 && zaciatok_rozsahu >= 0)
    {
      vytvor_histogram(pocet_cisel, zaciatok_rozsahu, pocet_vyskytov, velkost_pola);
      vykresli_histogram(druh_histogramu, pocet_vyskytov, zaciatok_rozsahu, velkost_pola);
    }
    else
    {
      printf("Niektoré zo zadaných čísel bolo záporné.");
    }
    break;

  case ('v'):
    if (pocet_cisel >= 0 && zaciatok_rozsahu >= 0)
    {
      vytvor_histogram(pocet_cisel, zaciatok_rozsahu, pocet_vyskytov, velkost_pola);
      vykresli_histogram(druh_histogramu, pocet_vyskytov, zaciatok_rozsahu, velkost_pola);
    }
    else
    {
      printf("Niektoré zo zadaných čísel bolo záporné.");
    }
    break;
  default:
    printf("Neplatny mod vykresleni\n");
    return 1;
  }

  return 0;
}