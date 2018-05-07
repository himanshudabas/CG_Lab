#include <iostream>
#include <stdio.h>
#include "graphics.h"
#include <cmath>

using namespace std;

void DDA(int X0, int Y0, int X1, int Y1)
{

    int dx = X1 - X0;
    int dy = Y1 - Y0;
 
    float m = float(dy)/float(dx);
    if(m == 1) {
        int x = X0;
        int y = Y0;
        for(int i=0; i<=dx; i++) {
            putpixel(x,y,BLUE);
            x+=1;
            y+=1;
            delay(10);
        }
        cout<<"x:"<<x<<"y:"<<y;
    } else if (m < 1) {
        float x = X0;
        float y = Y0;
        for(int i=0; i<=dx; i++) {
            putpixel(x,round(y),RED);
            x+=1;
            y+=m;
            delay(10);
        }
        cout<<"x:"<<x<<"y:"<<y;
    } else {
        float x = X0;
        float y = Y0;
        for(int i=0; i<=dy; i++) {
            putpixel(round(x),y,GREEN);
            y+=1;
            x+=1/m;
            delay(10);
        }
        cout<<"x:"<<x<<"y:"<<y;
    }
}

int main()
{
    int gd = DETECT, gm;
    initgraph (&gd, &gm, NULL);   
 
    int X0 = 2, Y0 = 2, X1 = 14, Y1 = 16;
    DDA(300,0,20,0);
    getch();
    return 0;
} 