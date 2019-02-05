/*------------------------------------------------------------

Temat projektu: Gra komputerowa

Zakres projektu:
1. animowany napis (x)
2. Co najmniej jeden animowany element o nieregularnym kszta³cie i rozmiarze min. 10x10 punktów (x)
3. Co najmniej 4 animowane elementy (x)
4. Sta³e elementy graficzne (x)
5. Sterowanie animacj¹ przez co najmniej jednego u¿ytkownika. Sterowanie co najmniej poprzez klawiaturê (x)
6. Wybór przez u¿ytkownika poziomu gry, okreœlaj¹cego jej trudnoœæ (x)
7. Prezentacja ekranu Help (x)
8. Zakoñczenie gry w dowolnym momencie (x)
9. Zapis informacji o grze do lokalnego pliku (x)
10. Wykorzystanie tablicy struktur do przechowywania danych (x)
11. Przekazanie do funkcji przez wskaŸnik. (x)
12. Realizacja szkieletu programu z wykorzystaniem technik programowania obiektowego. (x)

------------------------------------------------------------*/





/*------------------------------------------------------------

Program glowny

------------------------------------------------------------*/

#include <iostream>

#include "helpers.h"
#include "control.h"
#include "window.h"
#include "renderable.h"
#include "complexobject.h"
#include "collector.h"
#include "player.h"
#include "background.h"
#include "state.h"






int main()
{
    Helpers::zarodek();
    int window_width=getmaxwidth()*2/3;
    int window_height=getmaxheight()*2/3;


    Window okno(window_width,window_height);
    int errorcode = okno.ini();
    if(errorcode!=grOk){
            printf("Blad BGI: %s\n",grapherrormsg(errorcode));
            printf("wcisnij dowolny klawisz aby zakonczyc");
            getch();

    }else{
       settextstyle( COMPLEX_FONT , HORIZ_DIR, 1);
       int col2[]={36,36,36};
       int col1[]={131,86,86};

       Control ctrl=Control(window_width/2);

       ComplexObject background[]={Background::mountains(window_width,window_height),
                           Background::buildings(window_width,window_height),
                           Background::ground(window_width,window_height),
                           Background::moon(window_width,window_height),
                           //Background::sparkle(window_width,window_height)
                           };
       ComplexObject shape=Player::glimmer(window_width,window_height);


       ComplexObject clouds[] = { Background::cloud(100,100,window_width,window_height,1),
                                  Background::cloud(150,80,window_width,window_height,2),
                                  Background::cloud(300,50,window_width,window_height,3)
                                };

       Collector kolekcjoner;

       kolekcjoner.add_to_objs(background,4);
       kolekcjoner.add_to_objs(&shape,1);
       kolekcjoner.add_to_objs(clouds,3);


       Player gamer = Player(shape);

       State stat;

       int new_game=ctrl.menu(window_width/2,ctrl);

       if(new_game==1){
            gamer.setData(Helpers::fill_structure(window_width/2));
            stat.setGamer(gamer);
            //stat.save_to_file();
       }

       else if(new_game==0){
            personal *dat=new personal[1];
            stat.setGamer(gamer);
            if(stat.load_from_file(dat,1)==1){
                gamer.setData(dat);
            }
            else{
                cleardevice();
                outtextxy(window_width/2,window_height/3,"Brak zapisow do wczytania");
                delay(1000);
                ctrl.set_q(true);
            }
            delete dat;
       }
       else if(new_game==2){
                outtextxy(window_width/2,window_height/3,"Do zobaczenia!");
                delay(1000);
       }
       long int timeA;

       while(ctrl.get_q()==false){
           if(ctrl.get_pauza()==false){
               cleardevice();
               kolekcjoner.player_to_front();
               kolekcjoner.merge_when_collide(ENEMY,0.5,2);
               timeA = GetTickCount();
               timeA = timeA-timeA%100;
               if(timeA%6000==0){
                    kolekcjoner.spawn_enemy(10,window_width,window_height);
               }
               if(timeA%4000==0){
                    kolekcjoner.spawn_collectible(10,window_width,window_height);
               }
               if(timeA%3000==0){
                    kolekcjoner.shrink_all(0.95,6);
               }
               gamer.kill_if_small(10);
               gamer.lvl_up(window_width/20,window_width/55);
               kolekcjoner.color_enemies(shape,col1,col2);


               setcolor(BLACK);
               Background::move_from_right_to_left(clouds,3,20,okno);

               kolekcjoner.render_all();
               Helpers::outtextdata(10,10,gamer.getData());
               delay(100);
               kolekcjoner.enemy_follow(shape,window_height/88,window_height/88);
               gamer.collide(kolekcjoner,0.5);

               gamer.move_player(15,window_height/58,ctrl,window_width,window_height);

               if(gamer.getData().life<0){
                    ctrl.set_pauza(true);
                    stat.setGamer(gamer);
                    cleardevice();
                    Helpers::loosing(window_width/2,window_height/3);
                    cleardevice();
                    stat.ask_to_save(window_width/2,window_height/3);
                    cleardevice();
                    stat.ranking(window_width/2,window_height/6);
                    delay(6000);
                    break;
               }
            }
            if(ctrl.rules_exit(window_width/2,ctrl)){

                stat.setGamer(gamer);
                stat.save_to_file();
            }
       }
       closegraph();
    }


    return 0;
}
