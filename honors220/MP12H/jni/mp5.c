<<<<<<< .mine
/*									tab:8
 *
 * main.c - skeleton source file for ECE220 picture drawing program
 *
 * "Copyright (c) 2018 by Charles H. Zega, and Saransh Sinha."
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without written agreement is
 * hereby granted, provided that the above copyright notice and the following
 * two paragraphs appear in all copies of this software.
 *
 * IN NO EVENT SHALL THE AUTHOR OR THE UNIVERSITY OF ILLINOIS BE LIABLE TO
 * ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
 * DAMAGES ARISING OUT  OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION,
 * EVEN IF THE AUTHOR AND/OR THE UNIVERSITY OF ILLINOIS HAS BEEN ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * THE AUTHOR AND THE UNIVERSITY OF ILLINOIS SPECIFICALLY DISCLAIM ANY
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE
 * PROVIDED HEREUNDER IS ON AN "AS IS" BASIS, AND NEITHER THE AUTHOR NOR
 * THE UNIVERSITY OF ILLINOIS HAS ANY OBLIGATION TO PROVIDE MAINTENANCE,
 * SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS."
 *
 * Author:	    Charles Zega, Saransh Sinha
 * Version:	    1
 * Creation Date:   12 February 2018
 * Filename:	    mp5.h
 * History:
 *	CZ	1	12 February 2018
 *		First written.
 */
#include "mp5.h"
#include <stdlib.h>
#include <stdio.h>
=======
/*
ECE 220 Honors Spring 2018
>>>>>>> .r5416

<<<<<<< .mine
/*
	You must write all your code only in this file, for all the functions!
*/
=======
Machine Problem 5: Using functions to draw a picture
>>>>>>> .r5416

<<<<<<< .mine
/* Implemented functions near_horizontal, near_vertical, draw_line
 * draw_rect, draw_triangle, draw_circle, draw_parallelogram
 * based on the given specification. draw_picture generates a simple modulo
 * pattern, changing the functions can generate more patterns. eg - (x^2+y^2)
 * generates a grid of circles.
 */
=======
Steven S. Lumetta
Charles Zega
Saransh Sinha

*/




#include <stdio.h>
>>>>>>> .r5416

/*near_horizontal
 *
 *
 *
 * INPUTS: x_start,y_start -- the coordinates of the pixel at one end of the line
 * 	   x_end, y_end    -- the coordinates of the pixel at the other end
 * OUTPUTS: draws a pixel to all points in between the two given pixels including
 *          the end points
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */

<<<<<<< .mine

int32_t
point_color(int32_t x, int32_t y);


int32_t
near_horizontal(int32_t x_start, int32_t y_start, int32_t x_end, int32_t y_end){

    // draw line from larger point to smaller point
    if(x_start > x_end)
    {
        int32_t temp = x_start;                           //if the order is switched, swap start and end points
        x_start = x_end;
        x_end = temp;
        temp = y_start;
        y_start = y_end;
        y_end = temp;
    }

    //handles edge case
    if(x_start == x_end && y_start == y_end)
        return draw_dot(x_start, y_start);  //draw a single dot, and return the value draw_dot returns

    //Declare variables
    int32_t x_current = x_start;
    int32_t y_current = y_start;
    int32_t return_draw = 0;
    int32_t return_val = 1;

    //Draw dots from start to end with the given increment in y
    do
    {
        return_draw = draw_dot(x_current, y_current);
        if(return_draw == 0)
           return_val = 0;                 //return_val becomes 0 if one of the dots is out of bounds

        x_current += 1;
        y_current = ((2*(y_end-y_start)*(x_current - x_start)+1)/(2*(x_end-x_start))) + y_start;
    }
    while(x_current <= x_end);            //exit loop when all points are drawn

    return return_val;
}


/*
 *  near_vertical
 *
 *
 *
 *
 * INPUTS: x_start,y_start --#include <assert.h> the coordinates of the pixel at one end of the line
 * 	   x_end, y_end    -- the coordinates of the pixel at the other end
 * OUTPUTS: draws a pixel to all points in between the two given pixels including
 *          the end points
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */

int32_t
near_vertical(int32_t x_start, int32_t y_start, int32_t x_end, int32_t y_end){
    //code similar to near_horizontal, swap points if they are in reverse order
    if(y_start > y_end)
    {
        int32_t temp = y_start;
        y_start = y_end;
        y_end = temp;
        temp = x_start;
        x_start = x_end;
        x_end = temp;
    }
    //handle edge case of start and end point being the same
    if(x_start == x_end && y_start == y_end)
        return draw_dot(x_start, y_start);

    //Declare all required variables
    int32_t x_current = x_start;
    int32_t y_current = y_start;
    int32_t return_draw = 0;
    int32_t return_val = 1;

    //draw a dot between the start and end points using the given incement in x
    do
    {
        return_draw = draw_dot(x_current, y_current);
        if(return_draw == 0)
           return_val = 0;

        y_current += 1;
        x_current = ((2*(x_end-x_start)*(y_current - y_start)+1)/(2*(y_end-y_start))) + x_start;
    }
    while(y_current <= y_end); //end when end point is reached

    return return_val;
}

/*
 *  draw_line
 *
 *
 *
 *
 * INPUTS: x_start,y_start -- the coordinates of the pixel at one end of the line
 * 	   x_end, y_end    -- the coordinates of the pixel at the other end
 * OUTPUTS: draws a pixel to all points in between the two given pixels including
 *          the end points
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */

int32_t
draw_line(int32_t x_start, int32_t y_start, int32_t x_end, int32_t y_end){
	  //assign the absolute values of the numerator and denominator of the slope to variables
    int32_t slope_num = (y_end>y_start)?(y_end-y_start):(y_start-y_end);
    int32_t slope_denum = (x_end>x_start)?(x_end-x_start):(x_start-x_end);

    //if the absolute value of the slope is less than 1, call near_horizontal, else call near_vertical
    int32_t return_near = (slope_num<=slope_denum)?
    (near_horizontal(x_start, y_start, x_end, y_end)):(near_vertical(x_start, y_start, x_end, y_end));

    //return zero if a point was out of bounds
    if(return_near == 0)
       return 0;

    return 1;
}


/*
 *  draw_rect
 *
 *
 *
 *
 * INPUTS: x,y -- the coordinates of the of the top-left pixel of the rectangle
 *         w,h -- the width and height, respectively, of the rectangle
 * OUTPUTS: draws a pixel to every point of the edges of the rectangle
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */

int32_t
draw_rect(int32_t x, int32_t y, int32_t w, int32_t h){
	  //height and width less than zero is invalid input
    if(w < 0 || h < 0)
	    return 0;

    //if both h,w = 0, draw a point (draw line will do this)
    if(w == 0 && h == 0)
      return draw_line(x,y,x,y);

    //declare all necessary variables
    int32_t x_current = x;
    int32_t y_current = y;
    int32_t return_draw = 0;
    int32_t return_val = 1;

    //draw the width lines of the rectangle
    while(y_current <= y+h)
    {
        return_draw = (draw_line(x_current, y_current, (x_current+w), y_current));
        if(return_draw == 0)
            return_val = 0;

        y_current += h;

        //if height is zero, the loop will end in the first pass;
        if(h == 0)
          return return_val;
    }


    y_current = y;                  //reset the y_current

    //draw the height lines of the rectangle
    while(x_current <= x+w)
    {
        return_draw =  (draw_line(x_current, y_current, x_current, (y_current+h) ));
        if(return_draw == 0)
            return_val = 0;

        x_current += w;

        //if w = 0, the loop will end in the first pass (after drawing one near vertical line)
        if(w == 0)
          return return_val;
    }

    return return_val;
}


/*
 *  draw_triangle
 *
 *
 *
 *
 * INPUTS: x_A,y_A -- the coordinates of one of the vertices of the triangle
 *         x_B,y_B -- the coordinates of another of the vertices of the triangle
 *         x_C,y_C -- the coordinates of the final of the vertices of the triangle
 * OUTPUTS: draws a pixel to every point of the edges of the triangle
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */

int32_t
draw_triangle(int32_t x_A, int32_t y_A, int32_t x_B, int32_t y_B, int32_t x_C, int32_t y_C){

    //Draw three lines from one point to the other.
    int32_t rval_1, rval_2, rval_3 = 1;
    rval_1 = draw_line(x_A, y_A, x_B, y_B);
    rval_2 = draw_line(x_B, y_B, x_C, y_C);
    rval_3 = draw_line(x_A, y_A, x_C, y_C);

    return rval_1 && rval_2 && rval_3;
}

/*
 *  draw_parallelogram
 *
 *
 *
 *
 * INPUTS: x_A,y_A -- the coordinates of one of the vertices of the parallelogram
 *         x_B,y_B -- the coordinates of another of the vertices of the parallelogram
 *         x_C,y_C -- the coordinates of another of the vertices of the parallelogram
 * OUTPUTS: draws a pixel to every point of the edges of the parallelogram
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */

int32_t
draw_parallelogram(int32_t x_A, int32_t y_A, int32_t x_B, int32_t y_B, int32_t x_C, int32_t y_C){
	  //calculate the last point of the parallelogram
    int32_t x_D = (x_A+x_C-x_B);
    int32_t y_D = (y_A+y_C-y_B);
    int32_t rval_1, rval_2, rval_3, rval_4 = 1;

    //connect the 4 points.
    rval_1 = draw_line(x_A, y_A, x_B, y_B);
    rval_2 = draw_line(x_B, y_B, x_C, y_C);
    rval_3 = draw_line(x_C, y_C, x_D, y_D);
    rval_4 = draw_line(x_A, y_A, x_D, y_D);

    return rval_1 && rval_2 && rval_3 && rval_4;
}


/*
 *  draw_circle
 *
 *
 *
 *
 * INPUTS: x,y -- the center of the circle
 *         inner_r,outer_r -- the inner and outer radius of the circle
 * OUTPUTS: draws a pixel to every point whose distance from the center is
 * 	    greater than or equal to inner_r and less than or equal to outer_r
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */

int32_t
draw_circle(int32_t x, int32_t y, int32_t inner_r, int32_t outer_r){

    //inner radius negative, or larger than outer radius is invalid
    if(inner_r < 0 || outer_r < inner_r)
	     return 0;

    //declare variables
    int32_t x_square_1 = x-outer_r-1;
    int32_t x_square_2 = x+outer_r+1;
    int32_t y_square_1 = y-outer_r-1;
    int32_t y_square_2 = y+outer_r+1;
    int32_t x_current, y_current, distance = 0;
    int32_t return_val = 1;
    int32_t return_draw = 1;

    //handle edge case where both radii are zero
    if(inner_r == 0 && outer_r == 0)
        return draw_dot(x,y);

    //explore the points inside the circumsquare of the circle
    for(x_current = x_square_1; x_current < x_square_2 ; x_current++)
    {
        for(y_current = y_square_1; y_current < y_square_2 ; y_current++)
        {
            //if distance between point and center lies between inner and outer radius
            distance = ((x_current-x)*(x_current-x) + (y_current-y)*(y_current-y));
            if( distance >= inner_r*inner_r  && outer_r*outer_r >= distance)
                return_draw = draw_dot(x_current, y_current);       //draw that point

            if(return_draw == 0)
                return_val = 0;
        }
    }
        return return_val;
}


/*
 *  rect_gradient
 *
 *
 *
 *
 * INPUTS: x,y -- the coordinates of the of the top-left pixel of the rectangle
 *         w,h -- the width and height, respectively, of the rectangle
 *         start_color -- the color of the far left side of the rectangle
 *         end_color -- the color of the far right side of the rectangle
 * OUTPUTS: fills every pixel within the bounds of the rectangle with a color
 *	    based on its position within the rectangle and the difference in
 *          color between start_color and end_color
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */

int32_t
rect_gradient(int32_t x, int32_t y, int32_t w, int32_t h, int32_t start_color, int32_t end_color){

    //handle invalid inputs
    if(h < 0 || w <= 0)
	    return 0;

    //declare required variables
    int32_t x_right = x+w;
    int32_t y_bottom = y+h;
    int32_t x_current = x;
    int32_t y_current = y;
    int32_t bitmask_red = 0xff0000;
    int32_t bitmask_green = 0x00ff00;
    int32_t bitmask_blue = 0x0000ff;
    int32_t i, return_draw = 0;
    int32_t return_val = 1;

    //array for storing r,g,b values for a particular dot
    int32_t level[3];
    int32_t color = 0;

    //array for storing start and end values for each of the three color channels
    int32_t levels_fixed[3][2] = {{(start_color&bitmask_red)>>16,  (end_color&bitmask_red)>>16}, {(start_color&bitmask_green)>>8,
      (end_color&bitmask_green)>>8},{start_color&bitmask_blue,  end_color&bitmask_blue}};

    for(x_current = x; x_current <= x_right ; x_current++)
    {
        for(y_current = y; y_current <= y_bottom; y_current++)
        {
            //increment channels based on given formula
            for(i = 0; i <= 2; i++)
                level[i] = ((((2*(x_current - x)*(levels_fixed[i][1]-levels_fixed[i][0])) + 1))/((2*(-x+x_right)))) + levels_fixed[i][0];

            //combine channels into color
            color = (level[0]<<16) | (level[1]<<8) | (level[2]) ;
            set_color(color);
            return_draw = draw_dot(x_current, y_current);

            if(return_draw == 0)
                return_val = 0;
        }
    }

    return return_val;
}

/*
 *  draw_picture
 *
 *
 *
 *
 * INPUTS: none
 * OUTPUTS: draws modulo patterns based on given input functions
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */


int32_t
draw_picture()
{
	  //assign a value to each pixel based on value returned by point_color
    int32_t max_x = 624;
    int32_t max_y = 320;
    int32_t x, y , color = 0;
    for(x = 0; x < max_x ; x++)
    {
        for(y = 0; y < max_y ; y++)
        {
            color = point_color(x,y);
            set_color(color);
            draw_dot(x,y);
        }
    }
    return 1;
}

int32_t
point_color(int32_t x, int32_t y)
{
    //declare variables
    int32_t r, g, b = 0;
    /*control which pattern to create, patterns can be changed
     *by changing the functions inside the modulo
     *(could try using sin^2, cos^2 etc to bound values)
     *changing the modulo results in different shades (as in case 3)
     */
    int i = 4;
    if(x == 0 || y == 0)
        return 0;

    switch (i) {
      case 1:
          r = (x*x + y*y)%255;
          g = (x*x + y*y)%255;
          b = (x*x + y*y)%255;
          break;
      case 2:
          r = (3*x + 3*y)%255;
          g = (3*x)%255;
          b = (3*y)%255;
          break;
      case 3:
          r = (x + y*y*y)%225;
          g = (x + y*y*y)%255;
          b = (x + y*y*y)%255;
          break;
      case 4:
          r = (2*x*x)%255;
          g = (2*x*x)%255;
          b = (2*x*x)%255;
          break;
    }

    return ((r)<<16 | (g) <<8 | (b));
}
=======
/*
	You must write all your code only in this file, for all the functions!
*/




int32_t near_horizontal(int32_t x_start, int32_t y_start, int32_t x_end, int32_t y_end){
/* Your code goes here!*/
	int32_t dx, dy, x_1, y_1, x_A, x_B, x, y, retval = 1;

	if(x_start == x_end) return draw_dot(x_start, y_start);
	if (y_start < y_end) {
		dx = x_end - x_start;
		dy = y_end - y_start;
		x_1 = x_start;
		y_1 = y_start;
	} else {
		dx = x_start - x_end;
		dy = y_start - y_end;
		x_1 = x_end;
		y_1 = y_end;
	}
	if(x_start < x_end){
		x_A = x_start;
		x_B = x_end;
	}
	else{
		x_B = x_start;
		x_A = x_end;
	}
	for(x = x_B; x >= x_A; x--){
		y = (2 * dy * (x - x_1) + dx) / (2 * dx) + y_1;
		retval &= draw_dot(x, y);
	}
	return retval;
}

int32_t near_vertical(int32_t x_start, int32_t y_start, int32_t x_end, int32_t y_end){
/* Your code goes here!*/
	int32_t dx, dy, x_1, y_1, y_A, y_B, x, y, retval = 1;

	if(y_start == y_end) return draw_dot(x_start, y_start);
	if (x_start < x_end) {
		dx = x_end - x_start;
		dy = y_end - y_start;
		x_1 = x_start;
		y_1 = y_start;
	} else {
		dx = x_start - x_end;
		dy = y_start - y_end;
		x_1 = x_end;
		y_1 = y_end;
	}
	if(y_start < y_end){
		y_A = y_start;
		y_B = y_end;
	}
	else{
		y_B = y_start;
		y_A = y_end;
	}
	for(y = y_A; y <= y_B; y++){
		x = (2 * dx * (y - y_1) + dy) / (2 * dy) + x_1;
		retval &= draw_dot(x, y);
	}
	return retval;
}

int32_t draw_line(int32_t x_start, int32_t y_start, int32_t x_end, int32_t y_end){
/* Your code goes here!*/
	int32_t delta_x, delta_y;
	delta_x = x_end - x_start;
	delta_y = y_end - y_start;
	if(delta_x < 0) delta_x = -delta_x;
	if(delta_y < 0) delta_y = -delta_y;
	if(delta_y > delta_x){
		return near_vertical(x_start, y_start, x_end, y_end);
	}
	else{
		return near_horizontal(x_start, y_start, x_end, y_end);
	}
}

int32_t draw_rect(int32_t x, int32_t y, int32_t w, int32_t h){
/* Your code goes here!*/
	int32_t retval = 1;
	if(h < 0 || w < 0) return 0;
	retval &= draw_line(x, y, x+w, y);
	retval &= draw_line(x, y, x, y+h);
	retval &= draw_line(x, y+h, x+w, y+h);
	retval &= draw_line(x+w, y, x+w, y+h);
	return retval;
}

int32_t draw_triangle(int32_t x_A, int32_t y_A, int32_t x_B, int32_t y_B, int32_t x_C, int32_t y_C){
/* Your code goes here!*/
	int32_t retval = 1;
	retval &= draw_line(x_A, y_A, x_B, y_B);
	retval &= draw_line(x_B, y_B, x_C, y_C);
	retval &= draw_line(x_C, y_C, x_A, y_A);
	return retval;
}

int32_t draw_parallelogram(int32_t x_A, int32_t y_A, int32_t x_B, int32_t y_B, int32_t x_C, int32_t y_C){
/* Your code goes here!*/
	int32_t delta_x, delta_y, x_D, y_D, retval = 1;
	delta_x = x_B - x_A;
	delta_y = y_B - y_A;
	x_D = x_C - delta_x;
	y_D = y_C - delta_y;
	retval &= draw_line(x_A, y_A, x_B, y_B);
	retval &= draw_line(x_B, y_B, x_C, y_C);
	retval &= draw_line(x_C, y_C, x_D, y_D);
	retval &= draw_line(x_D, y_D, x_A, y_A);
	return retval;
}

int32_t draw_circle(int32_t x, int32_t y, int32_t inner_r, int32_t outer_r){
/* Your code goes here!*/
	int32_t i, j, d, retval = 1;
	if((inner_r < 0) || (outer_r < 0) || (inner_r > outer_r)) return 0;
	for(i = x - outer_r; i <= x + outer_r; i++){
		for(j = y - outer_r; j <= y + outer_r; j++){
			d = (i - x)*(i - x) + (j - y)*(j - y);
			if((d >= inner_r*inner_r) && (d <= outer_r*outer_r)){
				retval &= draw_dot(i,j);
			}
		}
	}
	return retval;
}

int32_t rect_gradient(int32_t x, int32_t y, int32_t w, int32_t h, int32_t start_color, int32_t end_color){
	/* Your code goes here!*/
	int32_t i, j, start_red, start_green, start_blue, end_red, end_green, end_blue, red, green, blue, delta_red, delta_green, delta_blue, new_color, retval = 1;
	int32_t r_adj, g_adj, b_adj;
	if(w <= 0 || h < 0) return 0;
	start_red = (start_color >> 16) & 0x000000FF;
	start_green = (start_color >> 8) & 0x000000FF;
	start_blue = start_color & 0x000000FF;
	end_red = (end_color >> 16) & 0x000000FF;
	end_green = (end_color >> 8) & 0x000000FF;
	end_blue = end_color & 0x000000FF;
	delta_red = end_red - start_red;
	delta_green = end_green - start_green;
	delta_blue = end_blue - start_blue;
	r_adj = w * (delta_red > 0 ? 1 : (delta_red < 0 ? -1 : 0));
	g_adj = w * (delta_green > 0 ? 1 : (delta_green < 0 ? -1 : 0));
	b_adj = w * (delta_blue > 0 ? 1 : (delta_blue < 0 ? -1 : 0));
	for(i = x; i <= x + w; i++){
		red = ((i - x) * delta_red * 2 + r_adj) / (2 * w) + start_red;
		green = ((i - x) * delta_green * 2 + g_adj) / (2 * w) + start_green;
		blue = ((i - x) * delta_blue * 2  + b_adj) / (2 * w) + start_blue;
		new_color = (red << 16) + (green << 8) + blue;
		set_color(new_color);
		for(j = y; j <= y + h; j++){
			retval &= draw_dot(i,j);
		}
	}
	return retval;
}



int32_t draw_picture(){
	set_color(0);
	if(rect_gradient(150,150,410,100,60,10600) == 0) printf("asfd\n");
	return 1;
}
>>>>>>> .r5416
