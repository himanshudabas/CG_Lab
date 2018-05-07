#include <iostream>
#include <stdio.h>
#include <graphics.h>
#include <cmath>

using namespace std;


typedef int OutCode;

const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000

const int xmin = 50;
const int ymin = 50;
const int xmax = 400;
const int ymax = 400;

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

void Bresenham(int X1, int Y1, int X2, int Y2, int color) {

    int DX = X2 - X1;
    int DY = Y2 - Y1;
    int _2DY = 2 * DY;
    int _2DX = 2 * DX;
    int P0 = _2DY - DX;
    int pk = P0;
    int x = X1;
    int y = Y1;
    float m = float(DY)/float(DX);

    putpixel(x, y, color);
    delay(10);

    if(m<=1 && m>=0) {
        for(int i=1; i<=DX; i++) {
            x += 1;
            if(pk < 0) {
                putpixel(x, y, color);
                // delay(10);
                pk += _2DY;
            } else {
                y += 1;
                putpixel(x, y, color);
                // delay(10);
                pk += _2DY - _2DX;
            }
            // cout<<"("<<x<<","<<y<<"),";
        }
    } else {
        for(int i=1; i<=DY; i++) {
            y += 1;
            if(pk < 0) {
                putpixel(x, y, color);
                // delay(10);
                pk += _2DX;
            } else {
                x += 1;
                putpixel(x, y, color);
                // delay(10);
                pk += _2DX - _2DY;
            }
            // cout<<"("<<x<<","<<y<<"),";
        }
    }
    
}

OutCode ComputeOutCode(double x, double y) {

	OutCode code;

	code = INSIDE;          // initialised as being inside of [[clip window]]

	if (x < xmin)           // to the left of clip window
		code |= LEFT;
	else if (x > xmax)      // to the right of clip window
		code |= RIGHT;
	if (y < ymin)           // below the clip window
		code |= BOTTOM;
	else if (y > ymax)      // above the clip window
		code |= TOP;

	return code;
}

void CohenSutherlandLineClipAndDraw(double x0, double y0, double x1, double y1) {

	// compute outcodes for P0, P1, and whatever point lies outside the clip rectangle
	OutCode outcode0 = ComputeOutCode(x0, y0);
	OutCode outcode1 = ComputeOutCode(x1, y1);
	bool accept = false;

	while (true) {
		if (!(outcode0 | outcode1)) {
			// bitwise OR is 0: both points inside window; trivially accept and exit loop
			accept = true;
			break;
		} else if (outcode0 & outcode1) {
			// bitwise AND is not 0: both points share an outside zone (LEFT, RIGHT, TOP,
			// or BOTTOM), so both must be outside window; exit loop (accept is false)
			break;
		} else {
			// failed both tests, so calculate the line segment to clip
			// from an outside point to an intersection with clip edge
			int x, y;

			// At least one endpoint is outside the clip rectangle; pick it.
			OutCode outcodeOut = outcode0 ? outcode0 : outcode1;

			// Now find the intersection point;
			// use formulas:
			//   slope = (y1 - y0) / (x1 - x0)
			//   x = x0 + (1 / slope) * (ym - y0), where ym is ymin or ymax
			//   y = y0 + slope * (xm - x0), where xm is xmin or xmax
			// No need to worry about divide-by-zero because, in each case, the
			// outcode bit being tested guarantees the denominator is non-zero
			if (outcodeOut & TOP) {           // point is above the clip window
				x = x0 + (x1 - x0) * (ymax - y0) / (y1 - y0);
				y = ymax;
			} else if (outcodeOut & BOTTOM) { // point is below the clip window
				x = x0 + (x1 - x0) * (ymin - y0) / (y1 - y0);
				y = ymin;
			} else if (outcodeOut & RIGHT) {  // point is to the right of clip window
				y = y0 + (y1 - y0) * (xmax - x0) / (x1 - x0);
				x = xmax;
			} else if (outcodeOut & LEFT) {   // point is to the left of clip window
				y = y0 + (y1 - y0) * (xmin - x0) / (x1 - x0);
				x = xmin;
			}

			// Now we move outside point to intersection point to clip
			// and get ready for next pass.
			if (outcodeOut == outcode0) {
				x0 = x;
				y0 = y;
				outcode0 = ComputeOutCode(x0, y0);
			} else {
				x1 = x;
				y1 = y;
				outcode1 = ComputeOutCode(x1, y1);
			}
		}
	}
	if (accept) {
		// Following functions are left for implementation by user based on
		// their platform (OpenGL/graphics.h etc.)
		Bresenham(x0, y0, x1, y1, 2);
        // cout<<"points after clipping (x0,y0),(x1,y1) : "<<"("<<x0<<","<<y0<<")"<<",("<<x1<<","<<y1<<")";
	}
}



int main()
{
    int gd = DETECT, gm, r;
    
    double x0, x1, y0, y1, x2, y2, x3, y3;
    x0 = 0;y0 = 5;
    x1 = 405;y1 = 100;
	x2 = 200;y2 = 450;
	x3 = 5;y3 = 200;
    // cout<<"\n\n Enter x0,y0,x1,y1 (seperated by space) : ";
    // cin>>x0>>y0>>x1>>y1;
    initgraph (&gd, &gm, NULL);
    DrawRectangle();
    // CohenSutherlandLineClipAndDraw(x0,y0,x1,y1);
	// CohenSutherlandLineClipAndDraw(x1,y1,x2,y2);
	DDA(50,50,40,40);
	// CohenSutherlandLineClipAndDraw(x2,y2,x3,y3);
	// CohenSutherlandLineClipAndDraw(x3,y3,x0,0);


    getch();
    return 0;
}
