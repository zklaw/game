#pragma once
#include <math.h>
//#include "window.h"
//#include "helpers.h"
//#include "control.h"
//#include "collector.h"
#define ELL 1
#define POL 7

class Renderable{
protected:
    int type;
    int color[3];
    int ell_props[4];
    int *pol_props;
    int fill_style;
public:
    Renderable(){
        type=0;
        for(int i=0;i<3;i++){
                color[i]=0;
        }
        for(int i=0;i<4;i++){
                ell_props[i]=0;
        }
        pol_props=0;
        fill_style=SOLID_FILL;

    }
    Renderable(int arr[], int col[],int style){
            type=ELL;
            fill_style = style;
            for(int i=0;i<4;i++){
                ell_props[i]=arr[i];
            }
            for(int i = 0; i<3; i++){
                color[i]=col[i];
            }
         //   setcolor(COLOR(color[0],color[1],color[2]));
    }
    Renderable(int arr[], int col[],int style,bool ell){

            type=ELL;
            fill_style = style;
            if(ell){
                for(int i=0;i<4;i++){
                    ell_props[i]=arr[i];
                }
            }
            else{
                for(int i=0;i<3;i++){
                    ell_props[i]=arr[i];
                }
                ell_props[3]=ell_props[2];
            }
            for(int i=0;i<4;i++){
                //printf("ell_props[%d]=%d\n",i,ell_props[i]);
            }
            for(int i = 0; i<3; i++){
                color[i]=col[i];
            }
         //   setcolor(COLOR(color[0],color[1],color[2]));
    }
    Renderable(int n_v, int ver[], int col[], int style){
        type=POL;
        fill_style = style;
        pol_props=new int[n_v*2+1];
        pol_props[0]=n_v;
        for(int i=0;i<n_v*2;i++){
        pol_props[i+1]=ver[i];
        }
        for(int i=0;i<3;i++){
            color[i] = col[i];
        }
      //  setcolor(COLOR(color[0],color[1],color[2]));

    }
    int get_number_vertexes(void){
        return pol_props[0];
    }
    void set_ell_props(int x, int y, int r_x,int r_y){
        ell_props[0]=x;
        ell_props[1]=y;
        ell_props[2]=r_x;
        ell_props[3]=r_y;
    }
    void set_radius(int r_x, int r_y){
        if(type==ELL){
            ell_props[2]=r_x;
            ell_props[3]=r_y;
        }
    }
    int* get_radius(){
        if(type==ELL){
            int radius[2]={ell_props[2],ell_props[3]};
            return radius;
        }
        return 0;
    }
    void set_size(int r){
        float multiplier=(float)r/(float)this->bounding_circle()[2];
        this->scale(multiplier);
    }
    void set_color(int col[]){
        for(int i=0;i<3;i++){
            color[i]=col[i];
        }
    }
    void render(void){
        if(type==ELL){
            setfillstyle(fill_style,COLOR(color[0],color[1],color[2]));
            fillellipse(ell_props[0],ell_props[1],ell_props[2],ell_props[3]);
        }
        else if(type==POL){
            int *vertexes=new int[pol_props[0]*2];
            for(int i=0;i<pol_props[0]*2;i++){
                vertexes[i]=pol_props[i+1];
            }
            setfillstyle(fill_style, COLOR(color[0],color[1],color[2]));
            fillpoly(pol_props[0],vertexes);
        }
    }
   /* static void render_all(){
        for(int i=0; i<objs.size(); i++){
            objs[i].render();
        }
    }*/
    /*static void clean(void){
        cleardevice();
    }*/

    int* getCenter(void){
        int center[2];
        if(type==ELL){
            center[0]=ell_props[0];
            center[1]=ell_props[1];
        }
        else if(type==POL){
            int suma=0;
            for(int i=0;i<pol_props[0]*2+1;i=i+2){
                suma=suma+pol_props[i+1];
            }
            center[0]=suma/pol_props[0];
            suma=0;
            for(int i=1;i<pol_props[0]*2+1;i=i+2){
                suma=suma+pol_props[i+1];
            }
            center[1]=suma/pol_props[0];
        }
        return center;
    }

    void changePosition(int x, int y){
        int* actualPosition;
        actualPosition=getCenter();
        int vec[2];
        vec[0]=x-actualPosition[0];
        vec[1]=y-actualPosition[1];
        if(type==ELL){
            ell_props[0]=ell_props[0]+vec[0];
            ell_props[1]=ell_props[1]+vec[1];
        }
        else if(type==POL){
            for(int i=0;i<pol_props[0]*2+1;i=i+2){
                pol_props[i+1]=pol_props[i+1]+vec[0];
            }
             for(int i=1;i<pol_props[0]*2+1;i=i+2){
                pol_props[i+1]=pol_props[i+1]+vec[1];
            }
        }
    }

    void moving(int x, int y){
        if(type==ELL){
            ell_props[0]=ell_props[0]+x;
            ell_props[1]=ell_props[1]+y;
        }
        else if(type==POL){
            for(int i=0;i<pol_props[0]*2+1;i=i+2){
                pol_props[i+1]=pol_props[i+1]+x;
            }
             for(int i=1;i<pol_props[0]*2+1;i=i+2){
                pol_props[i+1]=pol_props[i+1]+y;
            }
        }
    }

    int* bounding_circle(void){
        int arr[3];
        if(type==ELL){

            arr[0]=ell_props[0];
            arr[1]=ell_props[1];
            if(ell_props[2]>ell_props[3]){
                arr[2]=ell_props[2];
            }
            else{
                arr[2]=ell_props[3];
            }
        }
        else if(type==POL){
            int lengths[pol_props[0]];
            arr[0]=this->getCenter()[0];
            arr[1]=this->getCenter()[1];
            //printf("arr[0]=%d,arr[1]=%d\n",arr[0],arr[1]);
            for(int i=0;i<pol_props[0];i++){
                lengths[i]=sqrt(pow(arr[0]-pol_props[2*i+1],2)+pow(arr[1]-pol_props[2*i+2],2));
            }
            arr[2]=Helpers::getMax(lengths,pol_props[0]);
        }
        return arr;
    }
    bool is_on_screen(Window screen){
        //sprawdzenie czy wystaje na X na lewo
        if(this->bounding_circle()[2]<abs(this->getCenter()[0]-screen.getX())&&this->getCenter()[0]<screen.getX()){
            return false;
        }
        //sprawdzenie czy wystaje na X na prawo
        if(this->bounding_circle()[2]<abs(this->getCenter()[0]-(screen.getX()+screen.getmaxW()))&&this->getCenter()[0]>(screen.getmaxW()+screen.getX())){
            return false;
        }
        //sprawdzenie czy wystaje na Y do gory
        if(this->bounding_circle()[2]<abs(this->getCenter()[1]-screen.getY())&&this->getCenter()[1]<screen.getY()){
            return false;
        }
        //sprawdzenie czy wystaje na Y na dol
        if(this->bounding_circle()[2]<abs(this->getCenter()[1]-(screen.getY()+screen.getmaxH()))&&this->getCenter()[0]>(screen.getmaxH()+screen.getY())){
            return false;
        }
        return true;
    }
    int* get_bounding_circle_for_two(Renderable x){
        int z=sqrt(pow(this->getCenter()[0]-x.getCenter()[0],2)+pow(this->getCenter()[1]-x.getCenter()[1],2));
        if(this->bounding_circle()[2]>=x.bounding_circle()[2]&&z<this->bounding_circle()[2]&&z<x.bounding_circle()[2]*2){
               /* for(int i=0;i<3;i++){
                    printf("this->bounding_circle()[%d]=%d\n",i,this->bounding_circle()[i]);
                */
            return this->bounding_circle();
        }
        else if(this->bounding_circle()[2]<=x.bounding_circle()[2]&&z<x.bounding_circle()[2]&&z<this->bounding_circle()[2]*2){
                /*for(int i=0;i<3;i++){
                    printf("x.bounding_circle()[%d]=%d\n",i,x.bounding_circle()[i]);
                }*/
            return x.bounding_circle();
        }

        int arr[3];
        arr[0]=(this->getCenter()[0]+x.getCenter()[0])/2;
        arr[1]=(this->getCenter()[1]+x.getCenter()[1])/2;
        arr[2]=(this->bounding_circle()[2]+x.bounding_circle()[2]+z)/2;

        return arr;
    }
    void scale(float a){
        if(type==ELL){
            ell_props[2]=(float)ell_props[2]*a;
            ell_props[3]=(float)ell_props[3]*a;
        }
        else if(type==POL){
            for(int i=1;i<pol_props[0]*2;i++){
                pol_props[i]=(float)pol_props[i]*a;
            }
        }
    }
};
