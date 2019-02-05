#pragma once
class Window{
private:
    int maxH;
    int maxW;
    int x;
    int y;
public:
    Window(int W, int H){
        maxH = H;
        maxW = W;
        x = 0;
        y = 0;
    }
    int getmaxW(void){
        return maxW;
    }
    int getmaxH(void){
        return maxH;
    }
    int getX(void){
        return x;
    }
    int getY(void){
        return y;
    }
    int ini(){
        int errorcode;
        initwindow(maxW,maxH);
        errorcode=graphresult();

        return errorcode;
    }
};
