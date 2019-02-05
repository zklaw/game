#pragma once
class Background{
private:
public:
    static ComplexObject ground(int window_width,int window_height){
        int gd[] = {0,window_height,
                    window_width,window_height,
                    window_width,0.9*window_height,
                    0,0.9*window_height};
        int col_gd[3] = {76,43,9};
        Renderable gd_renderable(4,gd,col_gd,INTERLEAVE_FILL);
        Renderable gd_r[]={gd_renderable};
        ComplexObject ground(1,gd_r);

        return ground;
    }
    static ComplexObject mountains(int window_width,int window_height){
        int mn[]={0,window_height,//1
                 0,window_height*3/4,//2
                 window_width/10,window_height*2.75/4,//3
                 window_width/5,window_height*2.95/4,//4
                 window_width/3,window_height*2.65/4,//5
                 window_width/2.75,window_height*2.50/4,//6
                 window_width/2,window_height*2.6/4,//7
                 window_width/1.55,window_height*3/4,//8
                 window_width*4/5,window_height*2.6/4,//9
                 window_width,window_height*2.5/4,//10
                 window_width,window_height,//11
                 0,window_height//12
                };
        int col_mn[3] = {81,53,89};
        Renderable moun(12,mn,col_mn,CLOSE_DOT_FILL);
        Renderable mount[]={moun};
        ComplexObject mountains(1,mount);

        return mountains;
    }
    static ComplexObject buildings(int window_width,int window_height){
        int bd[]={0,window_height,//1
                 0, window_height*0.8,//2
                 window_width*2/34,window_height*0.8,//3
                 window_width*2/34,window_height*0.7,//4
                 window_width*4/34,window_height*0.7,//5
                 window_width*4/34,window_height*0.85,//6
                 window_width*6/34,window_height*0.85,//7
                 window_width*6/34,window_height*0.7,//8
                 window_width*10/34,window_height*0.7,//9
                 window_width*10/34,window_height*0.8,//10
                 window_width*12/34,window_height*0.8,//11
                 window_width*12/34,window_height*0.85,//12
                 window_width*14/34,window_height*0.85,//13
                 window_width*14/34,window_height*0.7,//14
                 window_width*18/34,window_height*0.7,//15
                 window_width*18/34,window_height*0.85,//16
                 window_width*21/34,window_height*0.85,//17
                 window_width*21/34,window_height*0.8,//18
                 window_width*24/34,window_height*0.8,//19
                 window_width*24/34,window_height*0.85,//20
                 window_width*26/34,window_height*0.85,//21
                 window_width*26/34,window_height*0.88,//22
                 window_width*30/34,window_height*0.88,//23
                 window_width*30/34,window_height*0.85,//24
                 window_width*32/34,window_height*0.85,//25
                 window_width*32/34,window_height*0.8,//26
                 window_width*34/34,window_height*0.8,//27

                 window_width,window_height,//28
                 0,window_height//29
                };
        int col_bd[3] = {92,92,92};
        Renderable bud(29,bd,col_bd,INTERLEAVE_FILL);
        Renderable build[]={bud};
        ComplexObject buildings(1,build);

        return buildings;
    }
    static ComplexObject moon(int window_width,int window_height){
        int mo_center[]={window_width*3/4,window_height/3,window_width/12,window_width/12};
        int mo_light[]={window_width*3/4,window_height/3,window_width/8,window_width/8};
        int col_mo_center[3] = {176,176,176};
        int col_mo_light[3] = {146,146,146};
        Renderable moon_center(mo_center,col_mo_center,SOLID_FILL);
        Renderable moon_light(mo_light,col_mo_light,CLOSE_DOT_FILL);
        Renderable mo[]={moon_light,moon_center};
        ComplexObject moon=ComplexObject(2,mo);
        return moon;
    }
    static ComplexObject cloud(int x, int y, int window_width,int window_height,int type){
        int cl[12];
        if(type==1){
             cl[0] = x;
             cl[1] = y;
             cl[2] = x+window_width/10;
             cl[3] = y+window_height/20;
             cl[4] = x+window_width*2/10;
             cl[5] = y+window_height/25;
             cl[6] = x+window_width*4/10;
             cl[7] = y+window_height/19;
             cl[8] = x+window_width*5/10;
             cl[9] = y+window_height/30;
             cl[10] = x;
             cl[11] = y;
        }
        if(type==2){
             cl[0] = x;
             cl[1] = y;
             cl[2] = x+window_width/5;
             cl[3] = y+window_height/5;
             cl[4] = x+window_width*2/5;
             cl[5] = y+window_height/8;
             cl[6] = x+window_width*4/5;
             cl[7] = y+window_height/15;
             cl[8] = x+window_width*5/5;
             cl[9] = y+window_height/9;
             cl[10] = x;
             cl[11] = y;
        }
        if(type==3){
             cl[0] = x;
             cl[1] = y;
             cl[2] = x+window_width/8;
             cl[3] = y+window_height/18;
             cl[4] = x+window_width*2/8;
             cl[5] = y+window_height/25;
             cl[6] = x+window_width*6/8;
             cl[7] = y+window_height/21;
             cl[8] = x+window_width*8/8;
             cl[9] = y+window_height/22;
             cl[10] = x;
             cl[11] = y;
        }
        int col_cl[3]={64,64,64};
        Renderable c(6,cl,col_cl,INTERLEAVE_FILL);
        Renderable cl_arr[] = {c};
        ComplexObject cloud(1,cl_arr);
        return cloud;
    }
    static void move_from_right_to_left(ComplexObject *objects, int N, int speed, Window screen){
        int *arr;
        for(int i=0;i<N;i++){
            arr=objects[i].bounding_circle();
            if(arr[0]<(screen.getX()-arr[2])){
                objects[i].changePosition(screen.getmaxW()+arr[2],arr[1]);

            }
            else{
                objects[i].moving(-speed/(i+1),0);
            }
        }
    }
};
