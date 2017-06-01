#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "obwody.h"
#include "pole.h"
#include "pole3d.h"
#include "objetosc.h"

int main(){

  int wybor, podwybor, podwybor2;
  printf("Menu:\n");
  printf("1.Obwody figur plaskich.\n2.Pola figur plaskich.\n3.Pola figur przestrzennych.\n4.Objetosc figur przestrzennych.\n>> ");
  scanf("%d", &wybor);

  switch(wybor)
  {
    case 1:
      printf("1.Obwod kwadratu\n2.Obwod prostokata\n3.Obwod trojkata\n4.Obwod kola\n5.Obwod trapezu\n6.Obwod rombu\n7.Obwod rownolegloboku\n>> ");
      scanf("%d", &podwybor);
      switch(podwybor)
      {
        case 1:
          obwKwa();
          break;
        case 2:
          obwPro();
          break;
        case 3:
          obwTro();
          break;
        case 4:
          obwKol();
          break;
        case 5:
          obwTra();
          break;
        case 6:
          obwRom();
          break;
        case 7:
          obwRow();
          break;
        default:
          printf("Zly wybor.\n");
          break;
      } break;
    case 2:
      printf("1.Pole kwadratu.\n2.Pole prostokata\n3.Pole trojkata\n4.Pole kola\n5.Pole trapezu\n6.Pole rombu\n7.Pole rownolegloboku\n>> ");
      scanf("%d", &podwybor);
      switch(podwybor)
      {
        case 1:
          polKwa();
          break;
        case 2:
          polPro();
          break;
        case 3:
          polTro();
          break;
        case 4:
          polKol();
          break;
        case 5:
          polTra();
          break;
        case 6:
          polRom();
          break;
        case 7:
          polRow();
          break;
        default:
          printf("Zly wybor.\n");
          break;
      }break;
    case 3:
      printf("1.Pole graniastoslupow.\n2.Pole ostroslupow\n3.Pole figur obrotowych\n>> ");
      scanf("%d", &podwybor);
      switch(podwybor)
      {
        case 1:
          printf("1.Pole graniastoslupa prawidlowego czworokatnego\n2.Pole graniastoslupa prawidlowego trojkatnego\n3.Pole graniastoslupa prawidlowego szesciokatnego\n>> ");
          scanf("%d", &podwybor2);
            switch(podwybor2)
            {
                case 1:
                  polGraPra4();
                  break;
                case 2:
                  polGraPra3();
                  break;
                case 3:
                  polGraPra6();
                  break;
                default:
                  printf("Zly wybor.\n");
                  break;
            }
          break;

        case 2:
          printf("1.Pole ostroslupa prawidlowego czworokatnego\n2.Pole ostroslupa prawidlowego trojkatnego\n3.Pole ostroslupa prawidlowego szesciokatnego\n>> ");
          scanf("%d", &podwybor2);
            switch(podwybor2)
            {
                case 1:
                  polOstrPra4();
                  break;
                case 2:
                  polOstrPra3();
                  break;
                case 3:
                  polOstrPra6();
                  break;
                default:
                  printf("Zly wybor.\n");
                  break;
            }
          break;

          case 3:
            printf("1.Pole walca\n2.Pole stozka\n3.Pole kuli\n>> ");
            scanf("%d", &podwybor2);
              switch(podwybor2)
              {
                  case 1:
                    polWalca();
                    break;
                  case 2:
                    polStozka();
                    break;
                  case 3:
                    polKuli();
                    break;
                  default:
                    printf("Zly wybor.\n");
                    break;
            } break;
          } break;

        case 4:
        printf("1.Objetosc graniastoslupow.\n2.Objetosc ostroslupow\n3.Objetosc figur obrotowych\n>> ");
        scanf("%d", &podwybor);
        switch(podwybor)
        {
          case 1:
            printf("1.Objetosc graniastoslupa prawidlowego czworokatnego\n2.Objetosc graniastoslupa prawidlowego trojkatnego\n3.Objetosc graniastoslupa prawidlowego szesciokatnego\n>> ");
            scanf("%d", &podwybor2);
              switch(podwybor2)
              {
                  case 1:
                    polGraPra4();
                    break;
                  case 2:
                    objGraPra3();
                    break;
                  case 3:
                    objGraPra6();
                    break;
                  default:
                    printf("Zly wybor.\n");
                    break;
              }
            break;

          case 2:
            printf("1.Objetosc ostroslupa prawidlowego czworokatnego\n2.Objetosc ostroslupa prawidlowego trojkatnego\n3.Objetosc ostroslupa prawidlowego szesciokatnego\n>> ");
            scanf("%d", &podwybor2);
              switch(podwybor2)
              {
                  case 1:
                    objOstrPra4();
                    break;
                  case 2:
                    objOstrPra3();
                    break;
                  case 3:
                    objOstrPra6();
                    break;
                  default:
                    printf("Zly wybor.\n");
                    break;
              }
            break;

          case 3:
            printf("1.Objetosc walca\n2.Objetosc stozka\n3.Objetosc kuli\n>> ");
            scanf("%d", &podwybor2);
              switch(podwybor2)
              {
                  case 1:
                    objWalca();
                    break;
                  case 2:
                    objStozka();
                    break;
                  case 3:
                    objKuli();
                    break;
                  default:
                    printf("Zly wybor.\n");
                    break;
              }
            break;
          

        default:
          printf("Zly wybor.\n");
          break;
      }




  }//end_switch


}
