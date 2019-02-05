#pragma once
#include <vector>
using namespace std;

class Collector{
private:
    vector<ComplexObject> objs;
public:
    void add_to_objs(ComplexObject *obj,int N){
       for(int i=0;i<N;i++){
                objs.push_back(obj[i]);
       }
    }
    void render_all(){
        for(int i=0; i<objs.size(); i++){
            objs[i].render();
        }
    }
    vector<ComplexObject> get_objs(void){
        return objs;
    }
    void delete_obj(int i){
            objs.erase (objs.begin()+i);
    }
    int count_type(int type){
        int counter=0;
        for(int i=0;i<objs.size();i++){
            if(objs[i].getType()==type){
                counter++;
            }
        }
        return counter;
    }
    void enemy_follow(ComplexObject &followed,int x,int y){
        for(int i=0;i<objs.size();i++){
            if(objs[i].getType()==ENEMY){
                objs[i].follow(followed,x,y);
            }
        }
    }
    void spawn_enemy(int power,int window_width, int window_height){

        int x,y,r_out,r_in;
        int i = rand() / (float(RAND_MAX)+1)* 4;
        int scale = 1 + rand() / (float(RAND_MAX)+1)* (3-1);

        r_in=window_width/100*scale;
        r_out=window_width/55*scale;


        if(i==0){
            x=-r_out;
            y= rand() / (float(RAND_MAX)+1)* window_height;
        }
        else if(i==1){
            x=rand() / (float(RAND_MAX)+1)* window_width;
            y= -r_out;
        }
        else if(i==2){
            x=window_width+r_out;
            y= rand() / (float(RAND_MAX)+1)* window_height;
        }
        else if(i==3){
            x=rand() / (float(RAND_MAX)+1)* window_width;
            y= window_height+r_out;
        }

        int sp_center[]={x,y,r_in,r_in};
        int sp_light[]={x,y,r_out,r_out};
        ComplexObject enemy_sparkle[] = {ComplexObject::sparkle(ENEMY,sp_center,sp_light,scale)};

        this->add_to_objs(enemy_sparkle,1);

    }
    void spawn_collectible(int power,int window_width, int window_height){
        //printf("typ collectible ilosc:%d\n",this->count_type(COLLECTIBLE));
        if(this->count_type(COLLECTIBLE)<3){

            int r_in=window_width/100;
            int r_out=window_width/55;

            int x=r_out + rand() / (float(RAND_MAX)+1)* (window_width-2*r_out);
            int y=r_out + rand() / (float(RAND_MAX)+1)* (window_height-2*r_out);

            int sp_center[]={x,y,r_in,r_in};
            int sp_light[]={x,y,r_out,r_out};

            ComplexObject sparkle[] = {ComplexObject::sparkle(COLLECTIBLE,sp_center,sp_light,10)};

            this->add_to_objs(sparkle,1);
        }
    }
    void merge_when_collide(int type, float sens, float scale){
        int sensibility1;
        int sensibility2;
        for(int i=0;i<objs.size();i++){
            if(objs[i].getType()==type){
                sensibility1=objs[i].bounding_circle()[2]*sens;
                for(int j=i+1;j<objs.size();j++){
                    sensibility2=objs[j].bounding_circle()[2]*sens;
                    if(objs[j].getType()==type){
                        if(objs[i].metric(objs[j])<sensibility1+sensibility2){
                            objs[i].scale(scale);
                            objs[i].setPower(objs[i].getPower()+1);
                            this->delete_obj(j);
                        }
                    }
                }
            }
        }
    }
    void unavailable_to_kill_enemy(ComplexObject &gamer,ComplexObject &object,int col1[],int col2[]){
        if(object.bounding_circle()[2]>gamer.bounding_circle()[2]){
            object.glimmer_set_color(col1);
        }
        else{
            object.glimmer_set_color(col2);
        }
    }
    void shrink_all(float a, int sensibility){
        for(int i=0;i<objs.size();i++){
            if(objs[i].getType()==ENEMY||objs[i].getType()==COLLECTIBLE||objs[i].getType()==PLAYER){
                objs[i].scale(a);
                objs[i].glimmer_scale_r_out(48.0/34.0);
                if(objs[i].bounding_circle()[2]<sensibility&&objs[i].getType()!=PLAYER){
                    this->delete_obj(i);
                }
            }
        }
    }
    void color_enemies(ComplexObject &gamer,int col1[],int col2[]){
        for(int i=0;i<objs.size();i++){
            if(objs[i].getType()==ENEMY){
                this->unavailable_to_kill_enemy(gamer,objs[i],col1,col2);
            }
        }
    }
    void player_to_front(void){
        for(int i=0;i<objs.size();i++){
             if(objs[i].getType()==PLAYER){
                    objs.push_back(objs[i]);
                    this->delete_obj(i);
                    break;
             }
        }
    }

};
