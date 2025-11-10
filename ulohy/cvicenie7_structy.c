#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

typedef struct Svg_ Svg;

struct Svg_
{
  char *obrazok;
  int vyska;
  int sirka;
};

void svg_novy(Svg *self, const int vyska, const int sirka)
{
  int velkost = 512;
  self->obrazok = malloc(velkost * sizeof(char));
  if (self->obrazok == NULL)
  {
    exit(1);
  }
  self->vyska = vyska;
  self->sirka = sirka;
  snprintf(self->obrazok, velkost, "<?xml version=\"1.0\" standalone=\"no\"?>\n" "<svg width=\"%d\" height=\"%d\" viewBox=\"0 0 %d %d\" xmlns=\"http://www.w3.org/2000/svg\">\n", sirka, vyska, sirka, vyska);
}

void svg_pridaj_ciaru(Svg *self, int x1, int y1, int x2, int y2, int hrubka, const char *farba)
{
  char riadok_buffer[256];
  int dlzka_riadka = snprintf(riadok_buffer, sizeof(riadok_buffer), "  <line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke=\"%s\" stroke-width=\"%d\"/>\n", x1, y1, x2, y2, farba, hrubka);
  int aktualna_dlzka = strlen(self->obrazok);
  int potrebna_dlzka = aktualna_dlzka + dlzka_riadka + 16;
  char *novy_obrazok = (char *)realloc(self->obrazok, potrebna_dlzka);
  if (novy_obrazok == NULL)
  {
    exit(1);
  }
  self->obrazok = novy_obrazok;
  strcat(self->obrazok, riadok_buffer);
}

void svg_uloz(Svg *self, const char *nazov_suboru)
{
  if (self == NULL || self->obrazok == NULL)
  {
    exit(1);
  }
  strcat(self->obrazok, "</svg>\n");
  FILE *fp = fopen(nazov_suboru, "w");
  if (fp == NULL)
  {
    free(self->obrazok);
    self->obrazok = NULL;
    exit(1);
  }
  fprintf(fp, "%s", self->obrazok);
  fclose(fp);
  free(self->obrazok);
  self->obrazok = NULL;
}

typedef struct Akcia_ Akcia;

struct Akcia_
{
  int index_dna;
  char *nazov_akcie;
  float hodnota_rano;
  float hodnota_vecer;
  int pocet_obchodov;
  char *pocet_obchodov_string;
};

int akcia_index_dna(const Akcia *self)
{
  return self->index_dna;
}

void akcia_index_dna_set(Akcia *self, const int index_dna)
{
  self->index_dna = index_dna;
}

float akcia_hodnota_rano(const Akcia *self)
{
  return self->hodnota_rano;
}

void akcia_hodnota_rano_set(Akcia *self, const float hodnota_rano)
{
  self->hodnota_rano = hodnota_rano;
}

float akcia_hodnota_vecer(const Akcia *self)
{
  return self->hodnota_vecer;
}

void akcia_hodnota_vecer_set(Akcia *self, const float hodnota_vecer)
{
  self->hodnota_vecer = hodnota_vecer;
}

int akcia_pocet_obchodov(const Akcia *self)
{
  return self->pocet_obchodov;
}

void akcia_pocet_obchodov_set(Akcia *self, const int pocet_obchodov)
{
  self->pocet_obchodov = pocet_obchodov;
}

void akcia_nazov_akcie_set(Akcia *self, const char *nazov_akcie)
{
  strcpy(self->nazov_akcie, nazov_akcie);
}

void akcia_pocet_obchodov_string_set(Akcia *self, const char *pocet_obchodov_string)
{
  strcpy(self->pocet_obchodov_string, pocet_obchodov_string);
}

void akcia_nazov_free(Akcia *self, const int pocet_zaznamov)
{
  for (int i = 0; i < pocet_zaznamov; i++)
  {
    if (self[i].nazov_akcie != NULL)
    {
      free(self[i].nazov_akcie);
      self[i].nazov_akcie = NULL;
    }
    if (self[i].pocet_obchodov_string != NULL)
    {
      free(self[i].pocet_obchodov_string);
      self[i].pocet_obchodov_string = NULL;
    }
  }
}

void akcia_new(Akcia *self, const char *nazov_akcie, const int index_dna, const float hodnota_rano, const float hodnota_vecer, const int pocet_obchodov, const char *pocet_obchodov_string)
{
  self->nazov_akcie = (char *)malloc((strlen(nazov_akcie) + 1) * sizeof(char));
  if (self->nazov_akcie == NULL)
  {
    exit(1);
  }
  strcpy(self->nazov_akcie, nazov_akcie);
  akcia_index_dna_set(self, index_dna);
  akcia_hodnota_rano_set(self, hodnota_rano);
  akcia_hodnota_vecer_set(self, hodnota_vecer);
  akcia_pocet_obchodov_set(self, pocet_obchodov);
  self->pocet_obchodov_string = (char *)malloc((strlen(pocet_obchodov_string) + 1) * sizeof(char));
  if (self->pocet_obchodov_string == NULL)
  {
    exit(1);
  }
  strcpy(self->pocet_obchodov_string, pocet_obchodov_string);
}

void spracovanie_dat(const int pocet_zaznamov, Akcia *pole_akcii)
{
  char riadok[101] = {};
  for (int i = 0; i < pocet_zaznamov; i++)
  {
    akcia_new(&pole_akcii[i], "", 0, 0, 0, 0, "");
    fgets(riadok, 101, stdin);
    if (riadok[strlen(riadok) - 1] == '\n')
    {
      riadok[strlen(riadok) - 1] = 0;
    }
    char *slovo = strtok(riadok, ",");
    int posun = 0;
    while (slovo != NULL)
    {
      if (slovo[strlen(slovo) - 1] == '\n')
      {
        slovo[strlen(slovo) - 1] = 0;
      }
      if (posun == 0)
      {
        akcia_index_dna_set(&pole_akcii[i], atoi(slovo));
        posun += 1;
      }
      else if (posun == 1)
      {
        free(pole_akcii[i].nazov_akcie);
        pole_akcii[i].nazov_akcie = (char *)malloc(strlen(slovo) + 1);
        akcia_nazov_akcie_set(&pole_akcii[i], slovo);
        posun += 1;
      }
      else if (posun == 2)
      {
        akcia_hodnota_rano_set(&pole_akcii[i], atof(slovo));
        posun += 1;
      }
      else if (posun == 3)
      {
        akcia_hodnota_vecer_set(&pole_akcii[i], atof(slovo));
        posun += 1;
      }
      else if (posun == 4)
      {
        akcia_pocet_obchodov_set(&pole_akcii[i], atoi(slovo));
        free(pole_akcii[i].pocet_obchodov_string);
        pole_akcii[i].pocet_obchodov_string = (char *)malloc(strlen(slovo) + 1);
        if (pole_akcii[i].pocet_obchodov_string == NULL)
        {
          exit(1);
        }
        akcia_pocet_obchodov_string_set(&pole_akcii[i], slovo);
        posun = 0;
      }
      slovo = strtok(NULL, ",");
    }
  }
}

void uprava_cisla(Akcia *pole_akcii, const int pocet_zaznamov)
{
  int povodna_dlzka = 0;
  for (int i = 0; i < pocet_zaznamov; i++)
  {
    int pocet_oddelovacov = 0;
    int nova_dlzka = 0;
    povodna_dlzka = strlen(pole_akcii[i].pocet_obchodov_string);
    char *riadok = (char *)malloc((povodna_dlzka + 1) * sizeof(char));
    strcpy(riadok, pole_akcii[i].pocet_obchodov_string);
    if (povodna_dlzka % 3 == 0)
    {
      pocet_oddelovacov = povodna_dlzka / 3 - 1;
    }
    else
    {
      pocet_oddelovacov = povodna_dlzka / 3;
    }
    free(pole_akcii[i].pocet_obchodov_string);
    nova_dlzka = povodna_dlzka + pocet_oddelovacov;
    char *novy_retazec = malloc((nova_dlzka + 1) * sizeof(char));
    if (novy_retazec == NULL)
    {
      return;
    }
    pole_akcii[i].pocet_obchodov_string = novy_retazec;
    int index = 0;
    for (int j = 0; j < povodna_dlzka; j++)
    {
      pole_akcii[i].pocet_obchodov_string[index] = riadok[j];
      index += 1;
      if (nova_dlzka % 3 == 0)
      {
        pole_akcii[i].pocet_obchodov_string[index] = '_';
        index += 1;
      }
      nova_dlzka -= 1;
    }
    pole_akcii[i].pocet_obchodov_string[index - 1] = 0;
    free(riadok);
    riadok = NULL;
  }
}

void akcia_vypis_akcii(Akcia *pole_akcii, const int pocet_zaznamov, char *dana_akcia_nazov, Svg svg)
{
  int povodne_x = 5;
  float povodne_y = 60;
  float nove_y = 0;
  int dana_akcia = 0;
  int pocet_overenych = 0;
  printf("<html>\n<body>\n<div>\n");
  for (int i = 0; i < pocet_zaznamov; i++)
  {
    if (strcmp(pole_akcii[i].nazov_akcie, dana_akcia_nazov) == 0 && pocet_overenych == 0)
    {
      dana_akcia = i;
      pocet_overenych += 1;
    }
    else if (strcmp(pole_akcii[i].nazov_akcie, dana_akcia_nazov) == 0 && akcia_pocet_obchodov(&pole_akcii[i]) > akcia_pocet_obchodov(&pole_akcii[dana_akcia]))
    {
      dana_akcia = i;
    }
  }
  if (pocet_overenych == 0)
  {
    printf("Ticker %s was not found\n</div>\n", dana_akcia_nazov);
  }
  else
  {
    //Bonus svg_novy(&svg, 128, 128);
    printf("<h1>%s: highest volume</h1>\n<div>Day: %d</div>\n<div>Start price: %.2f</div>\n<div>End price: %.2f</div>\n<div>Volume: %s</div>\n</div>\n", dana_akcia_nazov, akcia_index_dna(&pole_akcii[dana_akcia]), akcia_hodnota_rano(&pole_akcii[dana_akcia]), akcia_hodnota_vecer(&pole_akcii[dana_akcia]), pole_akcii[dana_akcia].pocet_obchodov_string);
  }
  printf("<table>\n<thead>\n<tr><th>Day</th><th>Ticker</th><th>Start</th><th>End</th><th>Diff</th><th>Volume</th></tr>\n</thead>\n<tbody>\n");
  for (int i = pocet_zaznamov - 1; i >= 0; i--)
  {
    if (strcmp(dana_akcia_nazov, pole_akcii[i].nazov_akcie) == 0)
    {
      printf("<tr>\n\t<td><b>%d</b></td>\n\t<td><b>%s</b></td>\n\t<td><b>%.2f</b></td>\n\t<td><b>%.2f</b></td>\n\t<td><b>%.2f</b></td>\n\t<td><b>%s</b></td>\n</tr>\n", akcia_index_dna(&pole_akcii[i]), pole_akcii[i].nazov_akcie, akcia_hodnota_rano(&pole_akcii[i]), akcia_hodnota_vecer(&pole_akcii[i]), akcia_hodnota_vecer(&pole_akcii[i]) - akcia_hodnota_rano(&pole_akcii[i]), pole_akcii[i].pocet_obchodov_string);
    }
    else
    {
      printf("<tr>\n\t<td>%d</td>\n\t<td>%s</td>\n\t<td>%.2f</td>\n\t<td>%.2f</td>\n\t<td>%.2f</td>\n\t<td>%s</td>\n</tr>\n", akcia_index_dna(&pole_akcii[i]), pole_akcii[i].nazov_akcie, akcia_hodnota_rano(&pole_akcii[i]), akcia_hodnota_vecer(&pole_akcii[i]), akcia_hodnota_vecer(&pole_akcii[i]) - akcia_hodnota_rano(&pole_akcii[i]), pole_akcii[i].pocet_obchodov_string);
    }
  }
  /*Bonus
  for(int i = 0; i < pocet_zaznamov; i++)
  {
    if (strcmp(dana_akcia_nazov, pole_akcii[i].nazov_akcie) == 0)
    {
      int rozdiel = (pole_akcii[i].hodnota_vecer - pole_akcii[i].hodnota_rano) * 5;
      nove_y = povodne_y - rozdiel;
      if(rozdiel > 0)
      {
        svg_pridaj_ciaru(&svg, povodne_x, povodne_y, povodne_x, nove_y, 1, "green");
      }
      else
      {
        svg_pridaj_ciaru(&svg, povodne_x, povodne_y, povodne_x, nove_y, 1, "red");
      }
      povodne_y = nove_y;
      povodne_x += 5;
    }
  }
  svg_uloz(&svg, "obrazok.svg");
  */
  printf("</tbody>\n</table>\n</body>\n</html>\n");
}

int main(int argc, char **argv)
{
  int pocet_zaznamov = 0;
  if (argc < 3)
  {
    printf("Wrong parameters\n");
    return 1;
  }

  char *nazov_akcie = argv[1];
  char *pocet_zaznam = argv[2];
  pocet_zaznamov = atoi(pocet_zaznam);
  nazov_akcie = argv[1];
  Akcia *pole_akcii = (Akcia *)malloc(pocet_zaznamov * sizeof(Akcia));
  if (pole_akcii == NULL)
  {
    return 1;
  }
  spracovanie_dat(pocet_zaznamov, pole_akcii);
  uprava_cisla(pole_akcii, pocet_zaznamov);
  Svg svg;
  akcia_vypis_akcii(pole_akcii, pocet_zaznamov, nazov_akcie, svg);
  akcia_nazov_free(pole_akcii, pocet_zaznamov);
  free(pole_akcii);
  pole_akcii = NULL;
  return 0;
}