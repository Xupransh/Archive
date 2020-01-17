#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "mp5.h"

int main()
{
set_color (0x00000000);
    draw_circle (50, 75, 45, 46);
    draw_circle (140, 75, 45, 46);

    int i = 0;
    for (i = 0; i < 50; i++) {
        int32_t x_temp = rand() % 90 + 5;
        int32_t y_temp = rand() % 90 + 30;
        draw_line (x_temp, y_temp, x_temp + (22 - rand() % 45), y_temp + (22 - rand() % 45));
    }

    for (i = 0; i < 50; i++) {
        int32_t x_temp = rand() % 90 + 94;
        int32_t y_temp = rand() % 90 + 30;
        draw_line (x_temp, y_temp, x_temp + (22 - rand() % 45), y_temp + (22 - rand() % 45));
    }

    int32_t start_y = 75 + 45 * sin(270 + 45);
    int32_t x_left = 50 + 15 * cos(270+45);
    int32_t x_right = 140 - 15 * cos(270+45);

    draw_line (x_left, start_y, x_left, 125 + start_y);
    draw_line (x_right, start_y, x_right, 125 + start_y);

    draw_circle ((x_left+x_right)/2,start_y+125,((x_right-x_left)/2), ((x_right-x_left)/2)+1);
    
    int32_t head_x = (x_right+x_left)/2;
    int32_t head_y = start_y+125+((x_right-x_left)/2)+1;

    draw_line (head_x, head_y, head_x, head_y - 25);

    draw_line (head_x + 35, head_y + 25, head_x + 55, head_y + 40);
    draw_line (head_x, head_y + 25, head_x, head_y + 40);
    draw_line (head_x - 35, head_y + 25, head_x - 55, head_y + 40);

    int32_t offset = 425;
    draw_circle (50 + offset, 75, 45, 46);
    draw_circle (140 + offset, 75, 45, 46);

    i = 0;
    for (i = 0; i < 50; i++) {
        int32_t x_temp = rand() % 90 + 5 + offset;
        int32_t y_temp = rand() % 90 + 30;
        draw_line (x_temp, y_temp, x_temp + (22 - rand() % 45), y_temp + (22 - rand() % 45));
    }

    for (i = 0; i < 50; i++) {
        int32_t x_temp = rand() % 90 + 94 + offset;
        int32_t y_temp = rand() % 90 + 30;
        draw_line (x_temp, y_temp, x_temp + (22 - rand() % 45), y_temp + (22 - rand() % 45));
    }

    start_y = 75 + 45 * sin(270 + 45);
    x_left = 50 + 15 * cos(270+45) + offset;
    x_right = 140 - 15 * cos(270+45) + offset;

    draw_line (x_left, start_y, x_left, 125 + start_y);
    draw_line (x_right, start_y, x_right, 125 + start_y);

    draw_circle ((x_left+x_right)/2,start_y+125,((x_right-x_left)/2), ((x_right-x_left)/2)+1);

    head_x = (x_right+x_left)/2;
    head_y = start_y+125+((x_right-x_left)/2)+1;

    draw_line (head_x, head_y, head_x, head_y - 25);

    draw_line (head_x + 35, head_y + 25, head_x + 55, head_y + 40);
    draw_line (head_x, head_y + 25, head_x, head_y + 40);
    draw_line (head_x - 35, head_y + 25, head_x - 55, head_y + 40);

    return 0;
}
