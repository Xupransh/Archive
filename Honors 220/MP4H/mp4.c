#include "mp4.h"
#include <stdio.h>

/*Program to determine the regions that are filled in all configurations
 *of a nonogram row. The boxes to be filled are determined by first solving
 *the basic case, then depending on how much more width there is, a certain 
 *number of boxes are made blank (this number is exactly the difference). 
 *Instead of doing this in 2 steps, it's done using one do-while loop. 
 *First the size of the basic case is calculated, then the difference is  
 *calculated. If this difference is negative, then the row cannot be solved.
 *Else, based on some conditions, the regions are printed.
 *Would need to replace all 4s with region_array size for more regions
 */


int32_t print_row (int32_t r1, int32_t r2, int32_t r3, int32_t r4, int32_t width)
{
    //Declaration of all required variables.   
    int difference, i, j, region_left = 0;
    int region_array[4] = {r1,r2,r3,r4};
    int basic_array_size = -1;

    //calculate size of base case (minimum width for a solution)
    for(i = 0; i < 4 ; i++)
    {   
        if(region_array[i] != 0)
            basic_array_size += region_array[i]+1; //extra space needed for non zero regions
    }

    difference = width - basic_array_size;         //difference between given case and base case

    //quit if difference is negative
    if(difference < 0)
        return 0;

    i = 0;

    do
    {   
        region_left = 0;                          //set region left to false 
        for(j = i+1; j < 4 ; j++)
        {
            if(region_array[j] !=0)               //if a non zero region is left, it's true
                region_left = 1;
        }  
        if(region_array[i] - difference > 0)      //if there's a positive number of Xs
        {
            for(j = 0; j < difference ; j++)      //print difference .s
                printf(".");

            for(j = 0; j < region_array[i]-difference; j++) //print Xs
                printf("X");
        }   
        else if(region_array[i] == 0)             //if region is zero in length
        {
            i+=1;
            continue;                             //move to next region
        }
        else
        {
            for(j = 0; j < region_array[i]; j++)  //for zero or negative values,
                printf(".");                      //the entire region is dots
        }
        if(i < 3 && region_left == 1)             //if more regions left, and not the last region
            printf(".");                          //print a dot to separate the regions  
        
        i+=1;                                     //increment region
    }
    while(i < 4);                                 //till you hit the last one
   
    //print "difference" dots at the end of the row 
    for(i = 0; i < difference; i++)
        printf(".");
        
    printf("\n");
    return 1;                      //print a newline, return 1 indicating sucess
}
