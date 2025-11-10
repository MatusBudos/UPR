#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int dlzka_pola(const char *s)
{
  int len = 0;
  while (s[len] != 0)
  {
    len++;
  }
  return len;
}
int prevod_cislo(const char *buf)
{
  int cislo = 0;
  for (int i = 0; i < dlzka_pola(buf); i++)
  {
    cislo = cislo * 10 + (buf[i] - '0');
  }
  return cislo;
}
int je_velke(const char nieco)
{
  if (nieco > 64 && nieco < 91)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}
int je_male(const char nieco)
{
  if (nieco > 96 && nieco < 123)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}
void zisti_medzery(const char *substr, int *medzery)
{
  int dlzka = dlzka_pola(substr);
  for (int i = 0; i < dlzka; i++)
  {
    if (substr[i] == 32)
    {
      *medzery += 1;
    }
  }
}
void velke_male(const char *substr, int *velke, int *male)
{
  int dlzka = dlzka_pola(substr);
  for (int i = 0; i < dlzka; i++)
  {
    if (je_velke(substr[i]))
    {
      *velke += 1;
    }
    else if (je_male(substr[i]))
    {
      *male += 1;
    }
  }
}
void normalizacia(char *substr)
{
  int aktual_velke = 0;
  int aktual_male = 0;
  velke_male(substr, &aktual_velke, &aktual_male);
  int dlzka = dlzka_pola(substr);
  if (aktual_velke > 0)
  {
    if (!je_velke(substr[0]))
    {
      substr[0] = substr[0] - 32;
    }
    for (int i = 1; i < dlzka; i++)
    {
      if (je_velke(substr[i]))
      {
        substr[i] = substr[i] + 32;
      }
    }
  }
  else
  {
    for (int i = 0; i < dlzka; i++)
    {
      substr[i] = substr[i] - 32;
    }
  }
  for (int i = 1; i < dlzka; i++)
  {
    if (substr[i - 1] == substr[i])
    {
      int j = i;
      while (substr[j] != '\0')
      {
        substr[j] = substr[j + 1];
        j++;
      }
      dlzka -= 1;
      i -= 1;
    }
  }
}
void vymaz_medzery(char *riadok, const int *postavenie, int *dlzka)
{
  while (riadok[*postavenie] == ' ')
  {
    for (int j = *postavenie + 1; j <= *dlzka; j++)
    {
      riadok[j - 1] = riadok[j];
    }
    *dlzka -= 1;
  }
}
int oddel_slovo(char *riadok, char *slovo, int *postavenie)
{
  int i = 0;
  while (riadok[*postavenie] != ' ' && riadok[*postavenie] != '\n' && riadok[*postavenie] != 0)
  {
    slovo[i] = riadok[*postavenie];
    *postavenie += 1;
    i++;
  }
  slovo[i] = '\0';
  if (i > 0)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}
int main()
{
  int male = 0;
  int velke = 0;
  int medzery = 0;
  int normal_medzery = 0;
  int normal_velke = 0;
  int normal_male = 0;
  char riadok[51] = {};
  int pocet_riadkov = 0;
  int postavenie = 0;
  char slovo[51] = {};
  fgets(riadok, sizeof(riadok), stdin);
  if (riadok[dlzka_pola(riadok) - 1] == '\n')
  {
    riadok[dlzka_pola(riadok) - 1] = 0;
  }
  pocet_riadkov = prevod_cislo(riadok);
  for (int i = 0; i < pocet_riadkov; i++)
  {
    male = 0;
    velke = 0;
    medzery = 0;
    normal_medzery = 0;
    normal_male = 0;
    normal_velke = 0;
    fgets(riadok, 51, stdin);
    zisti_medzery(riadok, &medzery);
    int dlzka = dlzka_pola(riadok);
    if (riadok[dlzka - 1] == '\n')
    {
      riadok[dlzka - 1] = 0;
      dlzka -= 1;
    }
    vymaz_medzery(riadok, &postavenie, &dlzka);
    oddel_slovo(riadok, slovo, &postavenie);

    char *substr = slovo;

    while (substr)
    {
      velke_male(substr, &velke, &male);
      normalizacia(substr);
      velke_male(substr, &normal_velke, &normal_male);
      printf("%s", substr);
      vymaz_medzery(riadok, &postavenie, &dlzka);
      for (int i = 0; i < 51; i++)
      {
        slovo[i] = 0;
        substr[i] = 0;
      }
      if (oddel_slovo(riadok, slovo, &postavenie))
      {
        for (int i = 0; i < dlzka_pola(slovo); i++)
        {
          substr[i] = slovo[i];
        }
        printf(" ");
        normal_medzery += 1;
      }
      else
      {
        substr = NULL;
        dlzka = 51;
        postavenie = 0;
      }
    }
    printf("\nlowercase: %d -> %d\n", male, normal_male);
    printf("uppercase: %d -> %d\n", velke, normal_velke);
    printf("spaces: %d -> %d\n", medzery, normal_medzery);
    if (i != pocet_riadkov - 1)
    {
      printf("\n");
    }
  }
  return 0;
}