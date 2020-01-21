#include <stdlib.h>
#include <string.h>

#include "mp8.h"


/*
 * basicRecurse -- flood fill recursively from a point until reaching
 *                 black or the image border
 * INPUTS: width -- width of the input image
 *         height -- height of the input image
 *         inRed -- pointer to the input red channel (1-D array)
 *         inGreen -- pointer to the input green channel (1-D array)
 *         inBlue -- pointer to the input blue channel (1-D array)
 *         x -- current x position of the flood
 *         y -- current y position of the flood
 *         marking -- array used to mark seen positions (indexed
 *                    in the same way as the RGB input arrays)
 * OUTPUTS: marking -- marked with flooded pixels
 * RETURN VALUE: none
 * SIDE EFFECTS: none
 */
void
basicRecurse (int32_t width, int32_t height,
	      const uint8_t* inRed, const uint8_t* inGreen,
	      const uint8_t* inBlue,
	      int32_t x, int32_t y,
	      uint8_t* marking)
{
	//declare variables
	int32_t is_black = 0;
	int32_t size = (width)*height;
	int32_t index = x + y*width;

	//check if x, y exceed their bounds, if pixel is already marked, or if the index is too high
	if(index > size || marking[index] == 2 || x >= width || y >= height || x < 0 || y < 0)
		return;

	//mark pixel as found
	marking[index] = 2;

	//go up if possible
	index = x+((y-1)*width);
	if(index >= 0 && index < size)
	{
		//check if pixel is black, if not, go in the specified direction
		is_black = ((inRed[index] == 0) && (inBlue[index] == 0) && (inGreen[index] == 0)) ? (1) : (0);
		if(!is_black)
			basicRecurse(width, height, inRed, inGreen, inBlue, x, y-1, marking);
	}

	//go right if possible
	index = x+1+(y*width);
	if(index >= 0 && index < size)
	{
		is_black = ((inRed[index] == 0) && (inBlue[index] == 0) && (inGreen[index] == 0)) ? (1) : (0);
		if(!is_black)
			basicRecurse(width, height, inRed, inGreen, inBlue, x+1, y, marking);

	}

	//go down if possible
	index = x+((y+1)*width);
	if(index >= 0 && index < size)
	{
		is_black = 	((inRed[index] == 0) && (inBlue[index] == 0) && (inGreen[index] == 0)) ? (1) : (0);
		if(!is_black)
			basicRecurse(width, height, inRed, inGreen, inBlue, x, y+1, marking);

	}

	//go left if possible (index is within bounds)
	index = x-1+(y*width);
	if(index >= 0 && index < size)
	{
		is_black = 	((inRed[index] == 0) && (inBlue[index] == 0) && (inGreen[index] == 0)) ? (1) : (0);
		if(!is_black)
			basicRecurse(width, height, inRed, inGreen, inBlue, x-1, y, marking);
	}

}


/*
 * greyRecurse -- flood fill recursively from a point until reaching
 *                near-black pixels or the image border
 * INPUTS: width -- width of the input image
 *         height -- height of the input image
 *         inRed -- pointer to the input red channel (1-D array)
 *         inGreen -- pointer to the input green channel (1-D array)
 *         inBlue -- pointer to the input blue channel (1-D array)
 *         x -- current x position of the flood
 *         y -- current y position of the flood
 *         distSq -- maximum distance squared between black and boundary
 *                   pixel color
 *         marking -- array used to mark seen positions (indexed
 *                    in the same way as the RGB input arrays)
 * OUTPUTS: marking -- marked with flooded pixels
 * RETURN VALUE: none
 * SIDE EFFECTS: none
 */
void
greyRecurse (int32_t width, int32_t height,
	     const uint8_t* inRed, const uint8_t* inGreen,
	     const uint8_t* inBlue,
	     int32_t x, int32_t y, uint32_t distSq,
	     uint8_t* marking)
{
	//declare variables, check bounds for x,y, check if pixel is marked
	int32_t near_black = 0;
	int32_t index = x+y*width;
	int32_t size = width*height;
	//if pixel is marked or bounds are exceeded, return
	if(index > size || marking[index] == 3 || x >= width || y >= height || x < 0 || y < 0 )
		return;

	//mark pixel as found
	marking[index] = 3;

	//go up if index is within bounds and the pixel at that location is not near black
	index = x+(y-1)*width;
	if(index >= 0 && index < size)
	{
		//if pixel is near black, don't go there
		near_black = colorsWithinDistSq(inRed[index], inGreen[index], inBlue[index], 0,0,0, distSq);
		if(!near_black)
			greyRecurse(width,height,inRed,inGreen,inBlue,x,y-1,distSq,marking);
	}

	//go right if possible
	index = x+1+(y*width);
	if(index >= 0 && index < size)
	{
		near_black = colorsWithinDistSq(inRed[index], inGreen[index], inBlue[index], 0,0,0, distSq);
		if(!near_black)
			greyRecurse(width,height,inRed,inGreen,inBlue,x+1,y,distSq,marking);
	}

	//go down if possible
	index = x+((y+1)*width);
	if(index >= 0 && index < size)
	{
		near_black = colorsWithinDistSq(inRed[index], inGreen[index], inBlue[index], 0,0,0, distSq);
		if(!near_black)
			greyRecurse(width,height,inRed,inGreen,inBlue,x,y+1,distSq,marking);
	}

	//go left if possible
	index = x-1+(y)*width;
	if(index >= 0 && index < size)
	{
		near_black = colorsWithinDistSq(inRed[index], inGreen[index], inBlue[index], 0,0,0, distSq);
		if(!near_black)
			greyRecurse(width,height,inRed,inGreen,inBlue,x-1,y,distSq,marking);
	}
}


/*
 * limitedRecurse -- flood fill recursively from a point until reaching
 *                   pixels too different (in RGB color) from the color at
 *                   the flood start point, too far away (> 40 pixels), or
 *                   beyond the image border
 * INPUTS: width -- width of the input image
 *         height -- height of the input image
 *         inRed -- pointer to the input red channel (1-D array)
 *         inGreen -- pointer to the input green channel (1-D array)
 *         inBlue -- pointer to the input blue channel (1-D array)
 *         origX -- starting x position of the flood
 *         origY -- starting y position of the flood
 *         x -- current x position of the flood
 *         y -- current y position of the flood
 *         distSq -- maximum distance squared between pixel at origin
 *                   and boundary pixel color
 *         marking -- array used to mark seen positions (indexed
 *                    in the same way as the RGB input arrays)
 * OUTPUTS: marking -- marked with flooded pixels
 * RETURN VALUE: none
 * SIDE EFFECTS: none
 */
void
limitedRecurse (int32_t width, int32_t height,
	        const uint8_t* inRed, const uint8_t* inGreen,
	        const uint8_t* inBlue,
	        int32_t origX, int32_t origY, int32_t x, int32_t y,
		uint32_t distSq, uint8_t* marking)
{
	//declare variables
	int32_t not_far_color = 0;
	//take absolute values of x,y distance
	int32_t far_x = ((x-origX) > 0 )? (x-origX) : (origX-x);
	int32_t far_y = ((y-origY) > 0 )? (y-origY) : (origY-y);
	//square x,y distances
	far_x *= far_x;
	far_y *= far_y;
	int32_t far = far_x + far_y;
	int32_t index = x+y*width;
	int32_t index_orig = origX + origY*width;
	//compute rgb values at the original index
	uint8_t r1 = inRed[index_orig];
	uint8_t g1 = inGreen[index_orig];
	uint8_t b1 = inBlue[index_orig];
	int32_t size = width*height;

	//if indices are out of bounds or pixel has been marked, return
	if(index > size || marking[index] == 4 || far > 1600 || x >= width || y >= height || x < 0 || y < 0)
		return;

	//mark pixel
	marking[index] = 4;

	//go up if pixel color is not too different from original and index is in bounds
	index = x+(y-1)*width;
	if(index >= 0 && index < size)
	{
		//call colors within dist sq to check if color is too far
		not_far_color = colorsWithinDistSq(inRed[index], inGreen[index], inBlue[index], r1,g1,b1, distSq);
		if(not_far_color)
			limitedRecurse(width,height,inRed,inGreen,inBlue,origX,origY,x,y-1,distSq,marking);
	}

	//go right if possible
	index = x+1+(y*width);
	if(index >= 0 && index < size)
	{
		not_far_color = colorsWithinDistSq(inRed[index], inGreen[index], inBlue[index], r1,g1,b1, distSq);
		if(not_far_color)
			limitedRecurse(width,height,inRed,inGreen,inBlue,origX, origY, x+1,y,distSq,marking);
	}

	//go down if possible
	index = x+((y+1)*width);
	if(index >= 0 && index < size)
	{
		not_far_color = colorsWithinDistSq(inRed[index], inGreen[index], inBlue[index], r1,g1,b1, distSq);
		if(not_far_color)
			limitedRecurse(width,height,inRed,inGreen,inBlue,origX, origY, x,y+1,distSq,marking);
	}

	//go left if possible
	index = x-1+(y)*width;
	if(index >= 0 && index < size)
	{
		not_far_color = colorsWithinDistSq(inRed[index], inGreen[index], inBlue[index], r1,g1,b1, distSq);
		if(not_far_color)
			limitedRecurse(width,height,inRed,inGreen,inBlue,origX,origY,x-1,y,distSq,marking);
	}

}
