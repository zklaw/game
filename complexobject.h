#pragma once
//#include "renderable.h"
#define COLLECTIBLE 1
#define ENEMY 0
#define NEUTRAL 3
#define PLAYER 4

class ComplexObject{
private:
    int num_of_objects;
    Renderable *objects;
    bool collid=false;
    int type=NEUTRAL;
    int power;

public:
    ComplexObject(){
        num_of_objects=0;
        objects=0;
    }
    ComplexObject(int n,Renderable objs[]){
        num_of_objects=n;
        objects=new Renderable[num_of_objects];
        for(int i=0;i<num_of_objects;i++){
            objects[i]=objs[i];
        }
    }
    ComplexObject(int n,Renderable objs[], bool coll, int t,int points){
        num_of_objects=n;
        objects=new Renderable[num_of_objects];
        for(int i=0;i<num_of_objects;i++){
            objects[i]=objs[i];
        }
        collid=coll;
        type=t;
        power=points;
    }
    void render(void){
        for(int i=0;i<num_of_objects;i++){
            objects[i].render();
        }
    }
    void setCollid(bool coll){
        collid=coll;
    }
    int* getCenter(void){
        int center[2]={0,0};
        for(int i=0;i<num_of_objects;i++){
            center[0]=center[0]+objects[i].getCenter()[0];
            center[1]=center[1]+objects[i].getCenter()[1];
        }
        center[0]=center[0]/num_of_objects;
        center[1]=center[1]/num_of_objects;
        return center;
    }

    bool getCollid(void){
        return collid;
    }
    int getType(void){
        return type;
    }
    void setType(int t){
        type=t;
    }
    int getPower(void){
        return power;
    }
    void setPower(int points){
        power=points;
    }
    void changePosition(int x, int y){
        int vec[2];
        vec[0]=x-getCenter()[0];
        vec[1]=y-getCenter()[1];
        for(int i=0;i<num_of_objects;i++){
            objects[i].moving(vec[0],vec[1]);
        }
    }
    void moving(int x, int y){
        for(int i=0;i<num_of_objects;i++){
            objects[i].moving(x,y);
        }
    }
    int metric(ComplexObject obj){
            int x=this->getCenter()[0]-obj.getCenter()[0];
            int y=this->getCenter()[1]-obj.getCenter()[1];
            int z=sqrt(pow(x,2)+pow(y,2));
            return z;
    }
    static ComplexObject sparkle(int type, int center_ellipse[],int light_ellipse[],int points){
        int color_center[3];
        int color_light[3];

        if(type==COLLECTIBLE){
            color_center[0] = 255;
            color_center[1] = 237;
            color_center[2] = 171;
            color_light[0] = 56;
            color_light[1] = 52;
            color_light[2] = 38;
        }
        else if(type==ENEMY){
            color_center[0] = 36;
            color_center[1] = 36;
            color_center[2] = 36;
            color_light[0] = 56;
            color_light[1] = 56;
            color_light[2] = 56;
        }
        Renderable sparkle_center(center_ellipse,color_center,SOLID_FILL);
        Renderable sparkle_light(light_ellipse,color_light,CLOSE_DOT_FILL);
        Renderable sparkle_r[]={sparkle_light,sparkle_center};
        ComplexObject sparkle(2,sparkle_r);
        sparkle.setType(type);
        sparkle.setCollid(true);
        sparkle.setPower(points);
        return sparkle;
    }
    void glimmer_set_color(int col[]){
        objects[1].set_color(col);
    }
    bool is_on_screen(Window screen){
        for(int i=0;i<num_of_objects;i++){
            if(objects[i].is_on_screen(screen)){
                return true;
            }
        }
        return false;
    }
    int* bounding_circle(void){

        if(num_of_objects>1){
            int color[]={0,0,0};
            int *tempCircle=objects[0].get_bounding_circle_for_two(objects[1]);


            /*int tempC[3];
            for(int i=0;i<3;i++){
                tempC[i]=tempCircle[i];
            }*/
            Renderable tempEll(tempCircle,color,SOLID_FILL,false);
           // printf("tempEll[center] = %d, %d\n",tempEll.getCenter()[0],tempEll.getCenter()[1]);
            for(int i=2; i<num_of_objects;i++){
                tempCircle=tempEll.get_bounding_circle_for_two(objects[i]);
                tempEll.set_ell_props(tempCircle[0],tempCircle[1],tempCircle[2],tempCircle[2]);
            }
            return tempCircle;
        }
        else if(num_of_objects==1){
            return objects[0].bounding_circle();
        }
        else{
            int arr[]={0,0,0};
            return arr;
        }
    }
    void follow(ComplexObject &followed,int x, int y){

        int arr[2];
        arr[0]=followed.getCenter()[0];
        arr[1]=followed.getCenter()[1];
        int this_center[2]={this->getCenter()[0],this->getCenter()[1]};
        if(this_center[0]>arr[0]){
            this->moving(-x,0);

        }
        if(this_center[0]<arr[0]){
            this->moving(x,0);
        }
        if(this_center[1]>arr[1]){
            this->moving(0,-y);

        }
        if(this_center[1]<arr[1]){
            this->moving(0,y);

        }
    }
    void scale(float a){
        for(int i=0;i<num_of_objects;i++){
            objects[i].scale(a);
        }
    }
    void set_size(int r){

        float multiplier=(float)r/(float)this->bounding_circle()[2];
        this->scale(multiplier);

    }
    void glimmer_scale_r_out(float p){
        int r=(float)objects[1].get_radius()[0]*p;
        objects[0].set_radius(r,r);
    }
};
