#include <iostream>
#include <stdio.h>
#include <graphics.h>
#include <cmath>

using namespace std;

int X, Y;
void put_pixel(int x, int y) {
    putpixel(X + x, Y - y, RED);
}

void Bresenham(int X1, int Y1, int X2, int Y2) {

    int DX = X2 - X1;
    int DY = Y2 - Y1;
    int _2DY = 2 * DY;
    int _2DX = 2 * DX;
    int pk;
    int x = X1;
    int y = Y1;
    float m = float(DY)/float(DX);

    put_pixel(x, y);
    delay(10);
    cout<<"M : "<<m<<endl;
    if(m<=1 && m>=0) {
        cout<<"x,y"<<X2<<","<<Y2<<endl;
        
        int P0 = _2DY - DX;
        pk = P0;
cout<<"dx,dy"<<DX<<","<<DY;
        if(DX<0 || DY<0) {
            cout<<"pk : "<<pk<<endl;
            pk = - pk;
            _2DX = - _2DX;
            _2DY = - _2DY;
            for(int i=0; i>DX; i--) {
                x -= 1;
                if(pk < 0) {
                    put_pixel(x, y);
                    cout<<"("<<x<<","<<y<<"),";
                    delay(10);
                    pk += _2DY;
                } else {
                    y -= 1;
                    put_pixel(x, y);
                    cout<<"("<<x<<","<<y<<"),";
                    delay(10);
                    pk += _2DY - _2DX;
                }
            }
        } else {

            for(int i=1; i<=DX; i++) {
                x += 1;
                if(pk < 0) {
                    put_pixel(x, y);
                    delay(10);
                    pk += _2DY;
                } else {
                    y += 1;
                    put_pixel(x, y);
                    delay(10);
                    pk += _2DY - _2DX;
                }
            }
        }
    } else if(m>1) {

        int P0 = _2DX - DY;
        pk = P0;
        for(int i=1; i<=DY; i++) {
            y += 1;
            if(pk < 0) {
                put_pixel(x, y);
                delay(10);
                pk += _2DX;
            } else {
                x += 1;
                put_pixel(x, y);
                delay(10);
                pk += _2DX - _2DY;
            }
        }
    }
    
}
int xmin, ymin, xmax, ymax;

void DrawRectangle() {
    for(int i=xmin; i<=xmax; i++) {
        putpixel(i, ymin, BLUE);
        putpixel(i, ymax, BLUE);
    }
    for(int i=ymin; i<=ymax; i++) {
        putpixel(xmin, i, BLUE);
        putpixel(xmax, i, BLUE);
    }

}

int main() {
    int gd = DETECT, gm;
    initgraph (&gd, &gm, NULL);
    xmin = 100;
    ymin = 100;
    xmax = 300;
    ymax = 300;
    X = 200;
    Y = 200;
    int X1 = 0, Y1 = 0, X2 = 100, Y2 = 100;
    DrawRectangle();
    Bresenham(X1, Y1, X2, Y2);
     Bresenham(X1, Y1, -X2, -Y2);
    getch();
} 