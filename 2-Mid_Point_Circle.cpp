#include <iostream>
#include <stdio.h>
#include <graphics.h>
#include <cmath>

using namespace std;

int X, Y;
void put_pixel(int x, int y) {
    putpixel(X + x, Y - y, BLUE);
}

void circle(int R)
{
    int x, y;
    int count = 0;
    x = 0;
    y = R;
    int P0 = 1 - R;
    int pk = P0;
    putpixel(X, Y, RED);
    put_pixel(x, y);
    put_pixel(x, -y);
    put_pixel(y, x);
    put_pixel(-y, x);
    delay(10);
    count += 4;
    if(pk < 0) {
        ++x;
        pk += (2*x)+3;
    } else {
        ++x;--y;
        pk += (2*x) + 1 - (2*y);
    }
    while(x<y) {

        put_pixel(x, y);
        put_pixel(-x, y);
        put_pixel(x, -y);
        put_pixel(-x, -y);
        put_pixel(y, x);
        put_pixel(y, -x);
        put_pixel(-y, -x);
        put_pixel(-y, x);
        delay(10);
        count += 8;
        if(pk < 0) {
            ++x;
            pk += (2*x)+3;
        } else {
            ++x;--y;
            pk += (2*x) + 1 - (2*y);
        }
    }
    if(x == y+1) {
        put_pixel(x, y);
        put_pixel(-x, y);
        put_pixel(x, -y);
        put_pixel(-x, -y);
        put_pixel(y, x);
        put_pixel(y, -x);
        put_pixel(-y, -x);
        put_pixel(-y, x);
        delay(10);
        count += 8;
    } else if (x == y) {
        put_pixel(x, y);
        put_pixel(-x, y);
        put_pixel(x, -y);
        put_pixel(-x, -y);
        delay(10);
        count += 4;
    }
    cout<<"\n\nTotal pixels illuminated : "<< count<<endl;
}
 
int main()
{
    int gd = DETECT, gm, r;
    cout<<"\n\n Enter the center of the circle seperated by space : ";
    cin>>X>>Y;
    cout<<"\n Enter the radius of the circle : ";
    cin>>r;
    initgraph (&gd, &gm, NULL);   
    circle(r);
    getch();
    return 0;
}
