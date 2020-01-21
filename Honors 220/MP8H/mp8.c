#include <stdlib.h>
#include <string.h>

#include "mp8.h"


/*
 * basicFlood -- wrapper for flood filling recursively from a point until
 *               reaching black or the image border
 * INPUTS: width -- width of the input image
 *         height -- height of the input image
 *         inRed -- pointer to the input red channel (1-D array)
 *         inGreen -- pointer to the input green channel (1-D array)
 *         inBlue -- pointer to the input blue channel (1-D array)
 *         startX -- starting x position of the flood
 *         startY -- starting y position of the flood
 *         floodR -- red component of the flood color
 *         floodG -- green component of the flood color
 *         floodB -- blue component of the flood color
 * OUTPUTS: outRed -- pointer to the output red channel (1-D array)
 *          outGreen -- pointer to the output green channel (1-D array)
 *          outBlue -- pointer to the output blue channel (1-D array)
 * RETURN VALUE: none
 * SIDE EFFECTS: none
 */
void
basicFlood (int32_t width, int32_t height,
	    const uint8_t* inRed, const uint8_t* inGreen,
	    const uint8_t* inBlue,
	    int32_t startX, int32_t startY,
	    uint8_t floodR, uint8_t floodG, uint8_t floodB,
	    uint8_t* outRed, uint8_t* outGreen,
	    uint8_t* outBlue)
{
		//set marking array (outRed) to all zeroes
		memset(outRed, 0, height*width*sizeof(outRed[0]));

		//call basicRecurse with given parameters, declare variables
		basicRecurse(width, height, inRed, inGreen, inBlue, startX, startY, outRed);
		int32_t x,y, index = 0;

		//for each pixel in the marking array, check if it is marked
		for(x = 0; x < width; x++)
		{
			for(y = 0; y < height; y++)
			{
				index = x+y*width;
				//if marked, then flood it, else, copy original values
				if(outRed[index] == 2)
				{
					outRed[index] = floodR;
					outBlue[index] = floodB;
					outGreen[index] = floodG;
				}
				else
				{
					outRed[index] = inRed[index];
					outBlue[index] = inBlue[index];
					outGreen[index] = inGreen[index];
				}
			}
		}
}


/*
 * colorsWithinDistSq -- returns 1 iff two colors are within Euclidean
 *                       distance squared of one another in RGB space
 * INPUTS: r1 -- red component of color 1
 *         g1 -- green component of color 1
 *         b1 -- blue component of color 1
 *         r2 -- red component of color 2
 *         g2 -- green component of color 2
 *         b2 -- blue component of color 2
 *         distSq -- maximum distance squared for the check
 * RETURN VALUE: 1 if the sum of the squares of the differences in the
 *               three components is less or equal to distSq; 0 otherwise
 * SIDE EFFECTS: none
 */
int32_t
colorsWithinDistSq (uint8_t r1, uint8_t g1, uint8_t b1,
                    uint8_t r2, uint8_t g2, uint8_t b2, uint32_t distSq)
{
		//declare variables, set each variable to square of difference of color values
		uint32_t diff_r = (r1-r2)*(r1-r2);
		uint32_t diff_g = (g1-g2)*(g1-g2);
		uint32_t diff_b = (b1-b2)*(b1-b2);

		//if sum of squares of difference of color values if more than allowed, return 0
		if((diff_r+diff_b+diff_g) <= distSq)
    	return 1;
		else
			return 0;
}


/*
 * greyFlood -- wrapper for flood filling recursively from a point until
 *              reaching near-black pixels or the image border
 * INPUTS: width -- width of the input image
 *         height -- height of the input image
 *         inRed -- pointer to the input red channel (1-D array)
 *         inGreen -- pointer to the input green channel (1-D array)
 *         inBlue -- pointer to the input blue channel (1-D array)
 *         startX -- starting x position of the flood
 *         startY -- starting y position of the flood
 *         floodR -- red component of the flood color
 *         floodG -- green component of the flood color
 *         floodB -- blue component of the flood color
 *         distSq -- maximum distance squared between black and boundary
 *                   pixel color
 * OUTPUTS: outRed -- pointer to the output red channel (1-D array)
 *          outGreen -- pointer to the output green channel (1-D array)
 *          outBlue -- pointer to the output blue channel (1-D array)
 * RETURN VALUE: none
 * SIDE EFFECTS: none
 */
void
greyFlood (int32_t width, int32_t height,
	   const uint8_t* inRed, const uint8_t* inGreen,
	   const uint8_t* inBlue,
	   int32_t startX, int32_t startY,
	   uint8_t floodR, uint8_t floodG, uint8_t floodB, uint32_t distSq,
	   uint8_t* outRed, uint8_t* outGreen,
	   uint8_t* outBlue)
{
	//set marking array to all zeroes
	memset(outRed, 0, width*height*sizeof(outRed[0]));
	//call grey recurse with given parameters, declare variables
	greyRecurse(width, height, inRed, inGreen, inBlue, startX, startY, distSq, outRed);
	int32_t x,y,index = 0;
	//for each pixel in the marking array
	for(x = 0; x < width ; x++)
	{
		for(y = 0; y < height ; y++)
		{
			//if pixel is marked, flood it with the given color
			index = x+y*width;
			if(outRed[index] == 3)
			{
				outRed[index] = floodR;
				outGreen[index] = floodG;
				outBlue[index] = floodB;
			}
			//else, copy original values
			else
			{
				outRed[index] = inRed[index];
				outGreen[index] = inGreen[index];
				outBlue[index] = inBlue[index];
			}
		}
	}
}


/*
 * limitedFlood -- wrapper for flood filling recursively from a point until
 *                 reaching pixels too different (in RGB color) from the
 *                 color at the flood start point, too far away
 *                 (> 40 pixels), or beyond the image border
 * INPUTS: width -- width of the input image
 *         height -- height of the input image
 *         inRed -- pointer to the input red channel (1-D array)
 *         inGreen -- pointer to the input green channel (1-D array)
 *         inBlue -- pointer to the input blue channel (1-D array)
 *         startX -- starting x position of the flood
 *         startY -- starting y position of the flood
 *         floodR -- red component of the flood color
 *         floodG -- green component of the flood color
 *         floodB -- blue component of the flood color
 *         distSq -- maximum distance squared between pixel at origin
 *                   and boundary pixel color
 * OUTPUTS: outRed -- pointer to the output red channel (1-D array)
 *          outGreen -- pointer to the output green channel (1-D array)
 *          outBlue -- pointer to the output blue channel (1-D array)
 * RETURN VALUE: none
 * SIDE EFFECTS: none
 */
void
limitedFlood (int32_t width, int32_t height,
	      const uint8_t* inRed, const uint8_t* inGreen,
	      const uint8_t* inBlue,
	      int32_t startX, int32_t startY,
	      uint8_t floodR, uint8_t floodG, uint8_t floodB, uint32_t distSq,
	      uint8_t* outRed, uint8_t* outGreen,
	      uint8_t* outBlue)
{
	//set marking array to all zeroes
	memset(outRed, 0, width*height*sizeof(outRed[0]));
	//declare variables, call limited recurse with given parameters
	limitedRecurse(width, height, inRed, inGreen, inBlue, startX, startY, startX, startY, distSq, outRed);
	int32_t x,y,index = 0;
	//for each value in the marking array
	for(x = 0; x < width ; x++)
	{
		for(y = 0; y < height ; y++)
		{
			//check if pixel is marked. If it is, flood it with the flood colors
			index = x+y*width;
			if(outRed[index] == 4)
			{
				outRed[index] = floodR;
				outGreen[index] = floodG;
				outBlue[index] = floodB;
			}
			//else, copy original pixel values
			else
			{
				outRed[index] = inRed[index];
				outGreen[index] = inGreen[index];
				outBlue[index] = inBlue[index];
			}
		}
	}
}
