#pragma once
#define ESC 27
#define F1 0x70
#define F4 0x73

class Control{
private:
    bool q;//=true;
    char global_key;//=0;
    int x;
    bool pauza;
//    bool kbhit;
public:
    Control(){
        q=false;
        global_key=0;
        x=0;
        pauza=false;
//    kbhit=false;
    }
    Control(int wx){
        x=wx;
        q=false;
        global_key=0;
        pauza=false;
    }
    void set_q(bool a){
        q=a;
    }
    bool get_q(void){
        return q;
    }
    void set_global_key(char c){
        global_key=c;
    }
    char get_global_key(void){
        return global_key;
    }
    int get_x(void){
        return x;
    }
    void set_pauza(bool a){
        pauza=a;
    }
    bool get_pauza(void){
        return pauza;
    }
    bool rules_exit(int x, Control &ctrl){
            int y=50;
            bool save=false;
            char option;
            settextjustify(CENTER_TEXT,CENTER_TEXT);
                if(GetKeyState(ESC)<0){
                    ctrl.set_pauza(true);
                    setcolor(WHITE);
                    outtextxy(x,y,"Chcesz zakonczyc? T czy N");
                    do{
                        option=getch();
                    }while(option!='t'&&option!='T'&&option!='n'&&option!='N');
                    if(option=='t'||option=='T'){
                        ctrl.set_q(true);
                        outtextxy(x,y,"Czy chcesz zapisac? T czy N");
                        do{
                            option=getch();
                        }while(option!='t'&&option!='T'&&option!='n'&&option!='N');
                        if(option=='t'||option=='T'){
                            ctrl.set_pauza(false);
                            save=true;
                        }
                        if(option=='n'||option=='N'){
                            setcolor(BLACK);
                            outtextxy(x,y,"Chcesz zakonczyc? T czy N");
                            ctrl.set_global_key('n');
                            ctrl.set_pauza(false);
                        }

                    }
                    if(option=='n'||option=='N'){
                        setcolor(BLACK);
                        outtextxy(x,y,"Chcesz zakonczyc? T czy N");
                        ctrl.set_global_key('n');
                        ctrl.set_pauza(false);
                        //setcolor(WHITE);

                    }
                }
                if(GetKeyState(F1)<0){
                    ctrl.set_pauza(true);
                    setcolor(WHITE);
                    settextjustify(LEFT_TEXT, CENTER_TEXT);
                    outtextxy(0,y,"ZASADY GRY");
                    setcolor(COLOR(131,86,86));
                    outtextxy(0,y+20,"Uciekaj przed ognikami w tym kolorze");
                    setcolor(COLOR(255,237,171));
                    outtextxy(0,y+40,"Zbieraj swiatelka o tym kolorze, aby zdobyc punkty i zwiekszyc rozmiar");
                    setcolor(COLOR(36,36,36));
                    outtextxy(0,y+60,"Gdy jestes wiekszy od ognikow, zmienia one kolor i mozesz je pochlanac");
                    setcolor(WHITE);
                    outtextxy(0,y+80,"Uwazaj zeby nie zniknac! Poruszanie: w s a d, zapis:F4 ");
                    outtextxy(0,y+100,"Aby zamknac nacisnij X");
                    do{
                        option=getch();
                    }while(option!='x'&&option!='X');
                    if(option=='x'||option=='X'){
                        setcolor(BLACK);
                        outtextxy(0,y,"ZASADY GRY");
                        outtextxy(0,y+20,"Uciekaj przed ognikami w tym kolorze");
                        outtextxy(0,y+40,"Zbieraj swiatelka o tym kolorze, aby zdobyc punkty i zwiekszyc rozmiar");
                        outtextxy(0,y+60,"Gdy jestes wiekszy od ognikow, zmienia one kolor i mozesz je pochlanac");
                        outtextxy(0,y+80,"Uwazaj zeby nie zniknac! Poruszanie: w s a d, zapis:F4 ");
                        outtextxy(0,y+100,"Aby zamknac nacisnij X");
                        ctrl.set_global_key('x');
                        ctrl.set_pauza(false);
                        //setcolor(WHITE);

                    }
                }
                if(GetKeyState(F4)<0){
                    ctrl.set_pauza(true);
                    setcolor(WHITE);
                    outtextxy(x,y,"Czy chcesz zapisac? T czy N");
                    do{
                        option=getch();
                    }while(option!='t'&&option!='T'&&option!='n'&&option!='N');
                    if(option=='t'||option=='T'){
                        ctrl.set_pauza(false);
                        save=true;
                    }
                    if(option=='n'||option=='N'){
                        setcolor(BLACK);
                        outtextxy(x,y,"Chcesz zakonczyc? T czy N");
                        ctrl.set_global_key('n');
                        ctrl.set_pauza(false);
                        //setcolor(WHITE);

                    }
                }
                return save;
    }
    int menu(int x, Control &ctrl){
        int y=50;
        settextjustify(CENTER_TEXT,CENTER_TEXT);
        outtextxy(x,y,"Nowa gra (N)");
        outtextxy(x,2*y,"Wczytaj gre (W)");
        outtextxy(x,3*y," Wyjdz (ESC)");
        do{
            if(GetKeyState('N')<0||GetKeyState('n')<0){
                //printf("nowa gra\n");
                cleardevice();
                return 1;

            }
            if(GetKeyState('W')<0||GetKeyState('w')<0){
                //printf("wczytanie pliku\n");
                cleardevice();
                return 0;
            }
            if(GetKeyState(ESC)<0){
                ctrl.set_q(true);
                break;
            }
            getch();
        }while(1);
        cleardevice();
        return 2;
    }
};
