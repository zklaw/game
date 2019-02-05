#pragma once
#include <time.h>
#include <stdio.h>
#include <graphics.h>
#include "personal.h"
//#include "state.h"
#define ENTER 13

class Helpers{
public:
    static void zarodek(void){
        int zaro;
        time_t tt;
        zaro = time(&tt);
        srand(zaro);
        }
    static personal default_fill_structure(personal &structure){
        for(int i=0;i<10;i++){
            structure.name[i]='.';
        }
        structure.name[10]='\0';
       // printf("data.name:%s\n",data.name);
        structure.life=0;
        structure.difficulty=0;
        structure.points=0;
    }
    static personal fill_structure(int x){
        personal data;
        int counter=0;
        for(int i=0;i<10;i++){
            data.name[i]='.';
        }
        data.name[10]='\0';
       // printf("data.name:%s\n",data.name);
        data.difficulty=0;
        data.points=0;
        settextjustify(CENTER_TEXT,CENTER_TEXT);
        char option;

            setcolor(WHITE);
            outtextxy(x,50,"Wpisz imie. Max 10 znakow, ponizej 10 znakow zatwierdz ENTER");
            outtextxy(x,70,data.name);
            do{ //zapytanie o imie
                if(kbhit()){
                    setcolor(BLACK);
                    outtextxy(x,70,data.name);
                    data.name[counter]=getch();
                    if(data.name[counter]==ENTER){
                            for(counter;counter<10;counter++){
                                data.name[counter]=' ';
                            }
                            counter++;
                    }
                    setcolor(WHITE);
                    outtextxy(x,70,data.name);
                    //printf("data.name:%s\n",data.name);
                    counter++;
                }
            }while(counter<10);
            //printf("data.name:%s\n",data.name);
            setcolor(BLACK);
            outtextxy(x,50,"Wpisz imie. Max 10 znakow, ponizej 10 znakow zatwierdz ENTER");
            outtextxy(x,70,data.name);
            setcolor(WHITE);
            do{ //zapytanie o poziom
                setcolor(WHITE);
                outtextxy(x,50,"Wybierz poziom trudnosci. Nacisnij 1, 2 lub 3");
                if(kbhit()){
                    do{
                    option=getch();
                    }while(option!='1'&&option!='2'&&option!='3');
                    if(option=='1'||option=='2'||option=='3'){
                        if(option=='1'){
                            option=1;
                        }
                        if(option=='2'){
                            option=2;
                        }
                        if(option=='3'){
                            option=3;
                        }
                        data.difficulty=option;
                        setcolor(BLACK);
                        outtextxy(x,50,"Wybierz poziom trudnosci. Nacisnij 1, 2 lub 3");
                        setcolor(WHITE);
                    }
                }
            }while(data.difficulty==0);
            if(data.difficulty==1){
                data.life=5;
            }
            if(data.difficulty==2){
                data.life=3;
            }
            if(data.difficulty==3){
                data.life=1;
            }
        return data;
    }
    static void outtextdata(int x,int y,personal data){
        static char points[100];
        sprintf(points,"punkty: %d, zycie: %d, imie: %s",data.points,data.life,data.name);
        setcolor(WHITE);
        settextjustify(LEFT_TEXT, TOP_TEXT);
        outtextxy(x,y,points);
        setcolor(BLACK);
    }
    static int getMax(int arr[],int N){
        int maximum=arr[0];
        for(int i=1;i<N;i++){
            if(arr[i]>maximum){
                maximum=arr[i];
            }
        }
        return maximum;
    }
    static int getMin(int arr[],int N){
        int minimum=arr[0];
        for(int i=1;i<N;i++){
            if(arr[i]<minimum){
                minimum=arr[i];
            }
        }
        return minimum;
    }
    static void loosing(int x, int y){
        setcolor(WHITE);
        settextjustify(CENTER_TEXT,CENTER_TEXT);
        outtextxy(x,y,"PRZEGRALES!");
        delay(600);
        //cleardevice();
    }

};
