#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef enum
{
  doprava = 0,
  dolu = 1,
  dolava = 2,
  hore = 3
} Smer;

struct Korytnacka
{
  int riadok;
  int stlpec;
  Smer smer;
};

struct Korytnacka korytnacky[3];

void presun_kurzora_na_zaciatok()
{
  printf("\x1b[1;1H");
  fflush(stdout);
}

void vygeneruj_random_cisla(int *random_cisla, int min, int max, int count)
{

  unsigned int seed = time(0);
  for (int i = 0; i < count; i++)
  {
    random_cisla[i] = rand_r(&seed) % (max - min + 1) + min;
  }
}

int index_2d_na_1d(int radek, int sloupec, int sirka)
{
  return radek * sirka + sloupec;
}

void vykresli(char *platno, const int riadky, const int stlpce)
{
  for (int i = 0; i < riadky; i++)
  {
    for (int j = 0; j < stlpce; j++)
    {
      const int index = index_2d_na_1d(i, j, stlpce);
      printf("%c", platno[index]);
    }
    printf("\n");
  }
}

void inicializacia_pola(char *platno, const int riadky, const int stlpce, const int pocet_random, const int *random_cisla)
{
  for (int i = 0; i < riadky; i++)
  {
    for (int j = 0; j < stlpce; j++)
    {
      const int index = index_2d_na_1d(i, j, stlpce);
      /*for (int x = 0; x < pocet_random; x++)
      {                                 //Vypnutie/zapnutie prekazok
        if (index == random_cisla[x])
        {
          platno[index] = '#';
          break;
        }
        else
        {*/
       platno[index] = '.';
      //platno[index] = ' ';
      //}
      //}
    }
  }
}

void array_free(char **arr)
{
  if (*arr)
  {
    free(*arr);
    *arr = NULL;
  }
}

void vytvor_korytnacku(struct Korytnacka korytnacka[3], int *pocet, char *nieco)
{
  if (*pocet < 3)
  {
    korytnacka[*pocet].riadok = 0;
    korytnacka[*pocet].stlpec = 0;
    korytnacka[*pocet].smer = doprava;
    *pocet += 1;
  }
}

void otacanie(const char znak, const int pocet)
{
  if (znak == 'r')
  {
    for (int i = 0; i < pocet; i++)
    {
      korytnacky[i].smer = (korytnacky[i].smer + 1) % 4;
    }
  }
  else
  {
    for (int i = 0; i < pocet; i++)
    {
      korytnacky[i].smer = (korytnacky[i].smer - 1 + 4) % 4;
    }
  }
}

void pohyb(char *platno, const int pocet, const int riadky, const int stlpce, char *nieco)
{
  for (int i = 0; i < pocet; i++)
  {
    int idx = index_2d_na_1d(korytnacky[i].riadok, (korytnacky[i].stlpec), stlpce);
    if (korytnacky[i].smer == 0)
    {
      int index = index_2d_na_1d(korytnacky[i].riadok, (korytnacky[i].stlpec + 1) % stlpce, stlpce);
      if (platno[index] != '#')
      {
        //platno[idx] = nieco[i];
        korytnacky[i].stlpec = (korytnacky[i].stlpec + 1) % stlpce;
        //nieco[i] = platno[index];
        //platno[index] = 'z';
      }
    }
    else if (korytnacky[i].smer == 1)
    {
      int index = index_2d_na_1d((korytnacky[i].riadok + 1) % riadky, korytnacky[i].stlpec, stlpce);
      if (platno[index] != '#')
      {
       //platno[idx] = nieco[i];
        korytnacky[i].riadok = (korytnacky[i].riadok + 1) % riadky;
        //nieco[i] = platno[index];
        //platno[index] = 'z';
      }
    }
    else if (korytnacky[i].smer == 2)
    {
      int index = index_2d_na_1d(korytnacky[i].riadok, (korytnacky[i].stlpec - 1 + stlpce) % stlpce, stlpce);
      if (platno[index] != '#')
      {
        //platno[idx] = nieco[i];
        korytnacky[i].stlpec = (korytnacky[i].stlpec - 1 + stlpce) % stlpce;
        //nieco[i] = platno[index];
        //platno[index] = 'z';
      }
    }
    else if (korytnacky[i].smer == 3)
    {
      int index = index_2d_na_1d((korytnacky[i].riadok - 1 + riadky) % riadky, korytnacky[i].stlpec, stlpce);
      if (platno[index] != '#')
      {
        //platno[idx] = nieco[i];
        korytnacky[i].riadok = (korytnacky[i].riadok - 1 + riadky) % riadky;
        //nieco[i] = platno[index];
        //platno[index] = 'z';
      }
    }
  }
}

void zmena_znaku(char *platno, const int pocet, const int stlpce, char *nieco)
{
  for (int i = 0; i < pocet; i++)
  {
    int index = index_2d_na_1d(korytnacky[i].riadok, korytnacky[i].stlpec, stlpce);
    /*Animacia
    if (platno[index] == 'z')
    {
      if (nieco[i] == ' ')
      {
        nieco[i] = 'o';
      }
      else if (nieco[i] == 'o')
      {
        nieco[i] = ' ';
      }
    }*/
    /*Bez animacie*/
    if (platno[index] == '.')
    {
      platno[index] = 'o';
    }
    else
    {
      platno[index] = '.';
    }
  }
}

int main()
{
  int pocet_kor = 0;
  int riadky = 0;
  int stlpce = 0;
  int random_cisla[5];
  int pocet_random = 5;

  scanf("%d %d", &riadky, &stlpce);
  char *platno = NULL;
  char nieco[3] = {' ', ' ', ' '};
  vygeneruj_random_cisla(random_cisla, 1, (riadky * stlpce - 1), pocet_random);
  platno = (char *)malloc(riadky * stlpce * sizeof(char));
  inicializacia_pola(platno, riadky, stlpce, pocet_random, random_cisla);
  vytvor_korytnacku(korytnacky, &pocet_kor, nieco);
  //[0] = 'z';
  char znak;
  int cyklus = 1;
  while (cyklus)
  {
    scanf(" %c", &znak);
    switch (znak)
    {
    case ('r'):
      otacanie('r', pocet_kor);
      break;

    case ('l'):
      otacanie('l', pocet_kor);
      break;

    case ('m'):
      /*Animácia
      usleep(400000);
      printf("\x1b[2J\x1b[1;1F");
      presun_kurzora_na_zaciatok();*/
      pohyb(platno, pocet_kor, riadky, stlpce, nieco);
      //vykresli(platno, riadky, stlpce);
      break;

    case ('o'):
      zmena_znaku(platno, pocet_kor, stlpce, nieco);
      break;

    case ('f'):
      vytvor_korytnacku(korytnacky, &pocet_kor, nieco);
      //platno[0] = 'z';
      break;
    case ('x'):
      /*Animácia
      usleep(400000);
      printf("\x1b[2J\x1b[1;1F");
      presun_kurzora_na_zaciatok();
      for (int i = 0; i < pocet_kor; i++)
      {
        int index = index_2d_na_1d(korytnacky[i].riadok, korytnacky[i].stlpec, stlpce);
        platno[index] = nieco[i];
      }
        */
      vykresli(platno, riadky, stlpce);
      cyklus = 0;
      break;
    }
  }

  array_free(&platno);

  return 0;
}