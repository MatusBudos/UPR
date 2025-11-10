#include <stdio.h>

int main()
{
  int obrazec = 0;
  int a = 0;
  int b = 0;
  int ciselko = 0;
  printf("Zadaj tri cisla v tomto formate: obrazec a b: ");
  scanf("%d%d%d", &obrazec, &a, &b);

  switch (obrazec)
  {
  case (0):
    for (int vyska = 0; vyska < b; vyska++)
    {
      for (int sirka = 0; sirka < a; sirka++)
        printf("X");
      printf("\n");
    }
    break;

  case (1):
    for (int vyska = 0; vyska < b; vyska++)
    {
      for (int sirka = 0; sirka < a; sirka++)
      {
        if (vyska == 0 || vyska == b - 1)
          printf("X");
        else if (sirka == 0 || sirka == a - 1)
          printf("X");
        else
          printf(" ");
      }
      printf("\n");
    }
    break;

  case (2):
    for (int vyska = 0; vyska < b; vyska++)
    {
      for (int sirka = 0; sirka < a; sirka++)
      {
        if (vyska == 0 || vyska == b - 1)
          printf("X");
        else if (sirka == 0 || sirka == a - 1)
          printf("X");
        else
        {
          printf("%d", ciselko % 10);
          ciselko++;
        }
      }
      printf("\n");
    }
    break;

  case (3):
    for (int vyska = 0; vyska < a; vyska++)
    {
      for (int i = 0; i < vyska; i++)
        printf(" ");
      printf("X\n");
    }
    break;

  case (4):
    for (int vyska = 0; vyska < a; vyska++)
    {
      for (int i = 0; i < a - vyska - 1; i++)
        printf(" ");
      printf("X\n");
    }
    break;

  case (5):
    for (int vyska = 0; vyska < a; vyska++)
    {
      int podstava = a * 2 - 1;
      for (int i = 0; i < podstava; i++)
      {
        if (i == podstava / 2 - vyska ||i == podstava / 2 + vyska)
          printf("X");
        else if(vyska == a-1)
          printf("X");
        else
          printf(" ");
      }
      printf("\n");
    }
    break;

    case (6):
    for (int vyska = 0; vyska < b; vyska++)
    {
      for(int sirka = 0; sirka <a; sirka++)
      {
        if(vyska == 0 || sirka == a/2)
        printf("X");
        else
        printf(" ");
      }
      printf("\n");
    }
    break;

    case (7):
    for (int vyska = 0; vyska < b; vyska++)
    {
      for(int sirka = 0; sirka <a; sirka++)
      {
        if(vyska == 0 || vyska == b/2 || (vyska > b/2 && sirka == 0) || (vyska < b/2 && (sirka == 0 || sirka == a-1)))
        printf("X");
        else
        printf(" ");
      }
      printf("\n");
    }
    break;

    case (9):
    for (int vyska = 0; vyska < b; vyska++)
    {
      for (int sirka = 0; sirka < a; sirka++)
      {
        if (vyska == 0 || vyska == b - 1)
          printf("X");
        else if (sirka == 0 || sirka == a - 1)
          printf("X");
        else
        {
          int vysledok = (sirka - 1) * (b - 2) + vyska - 1;
          printf("%d", vysledok %10);
        }                 
      }
      printf("\n");
    }
    break;
  }

  return 0;
}