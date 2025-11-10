#include "drawing.h"

void vykresli_auto()
{
  for (int i = 0; i < 5; i++)
  {
    for (int j = 0; j < 10; j++)
    {
      if (i == 0)
      {
        if (j > 1 && j < 8)
        {
          set_red_color();
          draw_pixel();
          move_right();
        }
        else
        {
          move_right();
        }
      }
      else if (i == 1)
      {
        if (j == 2 || j == 6)
        {
          set_blue_color();
          draw_pixel();
          move_right();
        }
        else if (j > 0 && j < 8)
        {
          set_red_color();
          draw_pixel();
          move_right();
        }
        else
        {
          move_right();
        }
      }
      else if (i > 1 && i < 4)
      {
        set_red_color();
        draw_pixel();
        move_right();
      }
      else if (i == 4)
      {
        if (j == 2 || j == 7)
        {
          set_yellow_color();
          draw_pixel();
          move_right();
        }
        else
        {
          move_right();
        }
      }
    }
    move_down();
    for (int x = 0; x < 10; x++)
    {
      move_left();
    }
  }
}

void vykresli_cestu()
{
  move_to(5, 1);
  for (int i = 0; i < 100; i++)
  {
    set_white_color();
    draw_pixel();
    move_right();
  }
  move_to(11, 1);
  for (int i = 0; i < 100; i++)
  {
    if (i % 2 == 0)
    {
      set_white_color();
      draw_pixel();
      move_right();
    }
    else
    {
      move_right();
    }
  }
  move_to(17, 1);
  for (int i = 0; i < 100; i++)
  {
    set_white_color();
    draw_pixel();
    move_right();
  }
}

void vyber_farby(int farba)
{
  switch (farba)
  {
  case (0):
    set_red_color();
    break;
  case (1):
    set_green_color();
    break;
  case (2):
    set_blue_color();
    break;
  case (3):
    set_white_color();
    break;
  case (4):
    set_yellow_color();
    break;
  default:
    set_black_color();
  }
}

void print_ciara(int dlzka, int farba)
{
  for (int i = 0; i <= dlzka * 2; i++)
  {
    if (i % 2 == 0)
    {
      vyber_farby(farba);
      draw_pixel();
      move_right();
    }
    else
    {
      set_black_color();
      draw_pixel();
      move_right();
    }
  }
  move_to(1, 1);
}

void print_schody(int pocet, int farba, int smer)
{
  vyber_farby(farba);
  for (int i = 0; i < pocet; i++)
  {
    if (smer == 0)
    {
      for (int i = 0; i < 3; i++)
      {
        draw_pixel();
        move_right();
      }
      move_left();
      move_down();
      draw_pixel();
    }
    else
    {
      for (int i = 0; i < 3; i++)
      {
        draw_pixel();
        move_right();
      }
      move_left();
      move_up();
      draw_pixel();
    }
  }
  move_to(1, 1);
}

void print_kvetina(int sirka, int vyska)
{
  for (int i = 0; i < vyska; i++)
  {
    for (int j = 0; j < sirka; j++)
    {
      if (i == vyska / 4 && j == sirka / 2)
      {
        set_yellow_color();
        draw_pixel();
        move_right();
      }
      else if (i <= vyska / 2)
      {
        set_white_color();
        draw_pixel();
        move_right();
      }
      else if (i > vyska / 2 && j == sirka / 2)
      {
        set_green_color();
        draw_pixel();
        move_right();
      }
      else
      {
        move_right();
      }
    }
    move_down();
    for (int x = 0; x < sirka; x++)
    {
      move_left();
    }
  }
  for (int i = 0; i < sirka; i++)
  {
    move_right();
  }
  for (int i = 0; i < vyska; i++)
  {
    move_up();
  }
}

void print_luka(int riadky, int stlpce)
{
  for (int i = 0; i < riadky; i++)
  {
    for (int j = 0; j < stlpce; j++)
    {
      move_right();
      print_kvetina(5, 8);
    }
    move_to(11, 1);
  }
}

void animacia()
{
  for (int i = 0; i < 25; i++)
  {
    vykresli_cestu();
    move_to(12, i+5);
    vykresli_auto();
    animate_ms(200);
    clear_screen();
  }
}

int main()
{
  // Keep this line here
  clear_screen();

  // Load the input - what should be drawn.
  int drawing = 0;
  scanf("%d", &drawing);

  // Put your drawing code here
  switch (drawing)
  {
  case (0):
    print_ciara(12, 0);
    move_to(4, 60);
    print_ciara(7, 1);
    move_to(6, 20);
    print_ciara(20, 2);
    move_to(4, 10);
    print_ciara(7, 3);
    move_to(10, 15);
    print_ciara(20, 4);
    break;
  case (1):
    print_schody(10, 4, 0);
    move_to(20, 10);
    print_schody(8, 2, 1);
    move_to(14, 30);
    print_schody(5, 3, 0);
    move_to(5, 40);
    print_schody(6, 0, 1);
    break;
  case (2):
    move_to(4, 40);
    print_kvetina(11, 5);
    move_to(2, 10);
    print_kvetina(5, 7);
    move_to(10, 20);
    print_kvetina(7, 5);
    move_to(7, 60);
    print_kvetina(9, 9);
    break;
  case (3):
    print_luka(2, 9);
    break;
  case (4):
    animacia();
    break;
  default:
    printf("NIC");
  }

  // Keep this line here
  end_drawing();

  return 0;
}
