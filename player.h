#pragma once
//#include "complexobject.h"
#define F1 0x70

class Player{
private:
    ComplexObject object;
    personal data;
public:
    Player(){
    }
    Player(personal d){
        object=ComplexObject();
        data=d;
    }
    Player(ComplexObject & o, personal d){
        object=o;
        data=d;
    }
    Player(ComplexObject & o){
        object=o;
    }
    personal getData(void){
        return data;
    }
    void setData(personal d){
        data=d;
    }
    void setData(personal *d){
        for(int i=0;i<11;i++){
            data.name[i]=d->name[i];
        }
        data.difficulty=d->difficulty;
        data.points=d->points;
        data.life=d->life;
    }
    void setLife(int l){
        data.life=l;
    }
    static ComplexObject ship(int x,int y,int a, int color[]){
        int tab[]={ x,y,//1
                    x,y-4*a,//2
                    x+2*a,y-3*a,//3
                    x+2*a,y-8*a,//4
                    x+5*a,y-4*a,//5
                    x+11*a,y-4*a,//6
                    x+14*a,y-a,//7
                    x+8*a,y-a,//8
                    x+9*a,y-0.5*a,//9
                    x+8*a,y,//10
                    x+4*a,y,//11
                    x+4*a,y-a,//12
                    x+2*a,y-a,//13
                    x,y//14
                    };
        Renderable ship(14,tab,color,SOLID_FILL);
        Renderable sh[]={ship};
        ComplexObject s(1,sh);
        s.setType(PLAYER);
        return s;
    }
    static ComplexObject glimmer(int window_width,int window_height){

        int r_in=window_width/48;
        int r_out=window_width/34;
        int x=window_width/2;
        int y=window_height/2;

        int lg_center[]={x,y,r_in,r_in};
        int lg_light[]={x,y,r_out,r_out};
        int col_lg_center[3] = {255,237,171};
        int col_lg_light[3] = {134,125,90};
        Renderable light_center(lg_center,col_lg_center,SOLID_FILL);
        Renderable light_light(lg_light,col_lg_light,WIDE_DOT_FILL);
        Renderable arr[]={light_light,light_center};
        ComplexObject glimmer(2,arr);
        glimmer.setType(PLAYER);
       // glimmer.setType(NEUTRAL);
        return glimmer;
    }
    ComplexObject getComplexObject(void){
        return object;
    }

    void move_player(int d,int speed,Control &ctrl,int window_width, int window_height){

       if(GetKeyState('w')<0||GetKeyState('W')<0){
            if(object.getCenter()[1]>0){
            object.moving(0,-speed);
            }
        }
        if(GetKeyState('d')<0||GetKeyState('D')<0){
            if(object.getCenter()[0]<window_width){
            object.moving(speed,0);
            }
        }
        if(GetKeyState('s')<0||GetKeyState('S')<0){
            if(object.getCenter()[1]<window_height){
                object.moving(0,speed);
            }
        }
        if(GetKeyState('a')<0||GetKeyState('A')<0){
            if(object.getCenter()[0]>0){
                object.moving(-speed,0);
            }
        }
        if(GetKeyState(ESC)<0){
            ctrl.set_pauza(true);
        }
        if(GetKeyState(F1)<0){
            ctrl.set_pauza(true);
        }
    delay(d);
    }
    void collide(Collector &coll,float sens){
        vector<ComplexObject> objs;
        objs=coll.get_objs();
        int sensibility1=this->getComplexObject().bounding_circle()[2]*sens;
        int sensibility2;
        for(int i=0;i<objs.size();i++){
            //metric czyli wektor odleglosci srodkow
            //jezeli odleglosc jest mniejsza niz czulosc i obiekt jest do zderzania

                if(objs[i].getType()==COLLECTIBLE){
                  //  printf("typ COLLECTIBLE\n");
                    sensibility2=objs[i].bounding_circle()[2]*sens;
                    if(objs[i].metric(object)<sensibility1+sensibility2&&objs[i].getCollid()){
                        data.points=data.points+objs[i].getPower();
                        object.scale(1.25);
                        coll.delete_obj(i);
                        objs.erase (objs.begin()+i);
                    }

                }
                if(objs[i].getType()==ENEMY){
                 //   printf("typ ENEMY\n");
                    sensibility2=objs[i].bounding_circle()[2]*sens;
                    if(objs[i].metric(object)<sensibility1+sensibility2&&objs[i].getCollid()){
                        if(object.bounding_circle()[2]>objs[i].bounding_circle()[2]){
                            data.points=data.points+objs[i].getPower();
                            object.scale(1.25);
                        }
                        else{
                            data.life=data.life-objs[i].getPower();
                        }
                        coll.delete_obj(i);
                        objs.erase (objs.begin()+i);
                    }
                }
               // printf("delete_obj(%d)\n",i);


        }
    }
    void kill_if_small(int sensibility){
        if(object.bounding_circle()[2]<sensibility){
            data.life=-1;
        }
    }
    void lvl_up(int player_size, int reduce_to){
        if(object.bounding_circle()[2]>player_size){
            data.life=data.life+1;
            object.set_size(reduce_to);
        }
    }
};
