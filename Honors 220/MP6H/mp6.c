/*									tab:8
 *
 * mp6.c - implementation file for ECE220 "Blocky" game
 *
 * "Copyright (c) 2017-2018 by Steven S. Lumetta."
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
 * Author:	    Steve Lumetta
 * Version:	    5
 * Creation Date:   7 November 2017
 * Filename:	    mp2.c
 * History:
 *	SL	1	7 November 2017
 *		First written.
 *      JXG     2	8 November 2017
 *		Added ncurses support.
 *	SL	3	30 November 2017
 *		Polished for MP distribution.
 *	SL	4	18 February 2018
 *		Edited slightly for ECE220H S18 distribution.
 *	SL	5	18 February 2018
 *		Stripped down from gold version.
 */


#include <stdint.h>
#include <stdio.h>

#include "mp6.h"


/*
 * The maximum number of blocks in one piece.  Do not change for
 * this assignment (you can do as you like with the code afterward).
 */
#define MAX_PIECE_SIZE 4

/*
 * Pieces are defined by an array of offsets from the center point.
 * Each piece consists of a set of adjacent blocks that together form
 * the piece.  The first index of the array is the piece type, the
 * second is the orientation (0-3), the third is block index within
 * the piece (0 to MAX_PIECE_SIZE - 1), and the fourth gives the
 * x (0) and y (1) offsets of the block relative to the center point.
 * Note that the first block is always the center point of the piece.
 *
 * Offsets may be replicated if a piece contains fewer than MAX_PIECE_SIZE
 * blocks.
 *
 * Clockwise rotation changes the orientation in the positive (mod 4)
 * direction, and counter-clockwise rotation changes the orientation in
 * the negative (mod 4) direction.
 */
static const int32_t piece_def[NUM_PIECE_TYPES][4][MAX_PIECE_SIZE][2] = {
    {   /* PIECE_TYPE_ELL */
	{{0, 0}, { 1,  0}, { 2,  0}, { 0,  1}},
	{{0, 0}, { 0,  1}, { 0,  2}, {-1,  0}},
	{{0, 0}, {-1,  0}, {-2,  0}, { 0, -1}},
	{{0, 0}, { 0, -1}, { 0, -2}, { 1,  0}}
    },
    {   /* PIECE_TYPE_REV_ELL */
	{{0, 0}, { 1,  0}, { 2,  0}, { 0, -1}},
	{{0, 0}, { 0,  1}, { 0,  2}, { 1,  0}},
	{{0, 0}, {-1,  0}, {-2,  0}, { 0,  1}},
	{{0, 0}, { 0, -1}, { 0, -2}, {-1,  0}}
    },
    {   /* PIECE_TYPE_LINE */
	{{0, 0}, {-1,  0}, { 1,  0}, { 2,  0}},
	{{0, 0}, { 0, -1}, { 0,  1}, { 0,  2}},
	{{0, 0}, { 1,  0}, {-1,  0}, {-2,  0}},
	{{0, 0}, { 0,  1}, { 0, -1}, { 0, -2}}
    },
    {   /* PIECE_TYPE_TEE */
	{{0, 0}, {-1,  0}, { 0, -1}, { 1,  0}},
	{{0, 0}, { 0, -1}, { 1,  0}, { 0,  1}},
	{{0, 0}, { 1,  0}, { 0,  1}, {-1,  0}},
	{{0, 0}, { 0,  1}, {-1,  0}, { 0, -1}}
    },
    {   /* PIECE_TYPE_ESS */
	{{0, 0}, { 0, -1}, { 1,  0}, { 1,  1}},
	{{0, 0}, { 1,  0}, { 0,  1}, {-1,  1}},
	{{0, 0}, { 0,  1}, {-1,  0}, {-1, -1}},
	{{0, 0}, {-1,  0}, { 0, -1}, { 1, -1}}
    },
    {   /* PIECE_TYPE_REV_ESS */
	{{0, 0}, { 0, -1}, {-1,  0}, {-1,  1}},
	{{0, 0}, { 1,  0}, { 0, -1}, {-1, -1}},
	{{0, 0}, { 0,  1}, { 1,  0}, { 1, -1}},
	{{0, 0}, {-1,  0}, { 0,  1}, { 1,  1}}
    }
};


/*
 * empty_board -- fills a board b with empty spaces (SPACE_EMPTY)
 * INPUTS: b -- the board
 * OUTPUTS: b -- the board, filled with empty spaces
 * RETURN VALUE: none
 * SIDE EFFECTS: none
 */
int32_t
empty_board (space_type_t b[BOARD_HEIGHT][BOARD_WIDTH])
{
    //Declare variables
    int x, y;

    //loop through the entire board and set each index to SPACE_EMPTY
    for(y = 0; y < BOARD_HEIGHT; y++)
    {
        for(x = 0; x < BOARD_WIDTH; x++)
        {
            b[y][x] = SPACE_EMPTY;
        }
    }
    //1 is returned always
    return 1;
}


/*
 * mark_piece -- forcibly writes a piece into a board, ignoring the
 *               board's current contents; you will need to understand
 *               the piece definition array (piece_def) in order to
 *               implement this function
 * INPUTS: b -- the board
 *         p -- the type of piece
 *         orient -- the orientation of the piece
 *         x -- horizontal coordinate of the piece's center point
 *         y -- vertical coordinate of the piece's center point
 *         v -- type of space to write (in the shape of the piece)
 * OUTPUTS: b -- the board, with the piece filled in with value v
 * RETURN VALUE: none
 * SIDE EFFECTS: none
 */
void
mark_piece (space_type_t b[BOARD_HEIGHT][BOARD_WIDTH],
            piece_type_t p, int32_t orient, int32_t x, int32_t y, space_type_t v)
{
    //declare variables, block_x,y are offsets, i is index for accessing blocks
    int32_t i = 0;
    int32_t block_x = 0, block_y = 0;

    //while all blocks are processed
    while(i < 4)
    {
        block_x = piece_def[p][orient][i][0]; //obtain offsets for given piece
        block_y = piece_def[p][orient][i][1];
        b[y+block_y][x+block_x] = v;          //mark block with given type
        i+=1;                                 //increment block index
    }
}


/*
 * test_piece_fit -- checks whether a piece fits into a board; you will
 *		     need to understand the piece definition array
 *		     (piece_def) in order to implement this function
 * INPUTS: b -- the board
 *         p -- the type of piece
 *         orient -- the orientation of the piece
 *         x -- horizontal coordinate of the piece's center point
 *         y -- vertical coordinate of the piece's center point
 * OUTPUTS: none
 * RETURN VALUE: if the piece does not fit within the board, returns
 *		 FIT_OUT_OF_BOARD; otherwise, if the piece would overwrite
 *		 non-empty board spaces, returns FIT_NO_ROOM_THERE;
 *		 otherwise, returns FIT_SUCCESS
 * SIDE EFFECTS: none
 */
fit_result_t
test_piece_fit (space_type_t b[BOARD_HEIGHT][BOARD_WIDTH],
                piece_type_t p, int32_t orient, int32_t x, int32_t y)
{
    //declare variables, i is block index, block_x,y are offsets
    int32_t i = 0;
    int32_t block_x, block_y = 0;

    //while all blocks are processed
    while(i < 4)
    {
        block_x = piece_def[p][orient][i][0];       //obtain offets for given piece
        block_y = piece_def[p][orient][i][1];

        //if certain conditions aren't satisfied, the block will not fit in the board, return fit out of board

        if((y+block_y >= BOARD_HEIGHT) || (x+block_x >= BOARD_WIDTH) || (x) >= BOARD_WIDTH || (y) >= BOARD_HEIGHT
            || (x+block_x < 0) || (y+block_y < 0) || (x < 0) || (y < 0))
            return FIT_OUT_OF_BOARD;

        //else, if there is a block in that place, return fit no room there.
        else if(b[y+block_y][x+block_x] != SPACE_EMPTY)
            return FIT_NO_ROOM_THERE;

        //increment index
        i+=1;
    }

    //success if condtions satisfied for all blocks
    return FIT_SUCCESS;
}


/*
 * print_board -- prints a board to the screen using period ('.') to
 *		  represent empty spaces, percent ('%') to represent
 *		  old blocks, and asterisk ('*') to represent the current
 *		  piece (SPACE_BLOCK); see specification for example
 * 		  of board appearance
 * INPUTS: b -- the board
 * OUTPUTS: none
 * RETURN VALUE: none
 * SIDE EFFECTS: prints to the monitor
 */
void
print_board (space_type_t b[BOARD_HEIGHT][BOARD_WIDTH])
{
    //variables for indexing into the board
    int y,x;

    //go through each index
    for(y = 0; y < BOARD_HEIGHT ; y++)
    {
        for(x = 0; x < BOARD_WIDTH; x++)
        {
            //print . if empty space
            if(b[y][x] == SPACE_EMPTY)
                printf(".");

            //* if there is an active block
            else if(b[y][x] == SPACE_BLOCK)
                printf("*");

            //else print %
            else
                printf("%%");
        }

        //print a new line after each row is done.
        printf("\n");
    }
}


/*
 * try_to_move_down -- tries to move the current piece down one space in
 *                     the board; assumes that the piece is in the board
 *		       and must thus be removed before it can be put into
 *                     its new position (or back into its old position
 *                     on failure)
 * INPUTS: b -- the board
 *         p -- the type of piece
 *         orient -- the current orientation of the piece
 *         x -- current horizontal coordinate of the piece's center point
 *         y -- current vertical coordinate of the piece's center point
 * OUTPUTS: b -- the board, with the piece moved down (on success), or
 *               unchanged on failure
 * RETURN VALUE: 1 on success, 0 on failure
 * SIDE EFFECTS: none
 */
int32_t
try_to_move_down (space_type_t b[BOARD_HEIGHT][BOARD_WIDTH],
                  piece_type_t p, int32_t orient, int32_t x, int32_t y)
{
    //return_val is the value returned by the function
    int32_t return_val = 1;

    //remove piece from the board
    remove_piece (b, p, orient, x, y);

    //increase row number
    y++;

    //test if the block fits there
    if(FIT_SUCCESS != test_piece_fit (b, p, orient, x, y))
    {
        //if it doesn't, move back to the original row, set return value to zero
        y = y-1;
        return_val = 0;
    }

    //add the piece, return the return value
    add_piece (b, p, orient, x, y);
    return return_val;
}


/*
 * try_to_move_left -- tries to move the current piece one space left in
 *                     the board; assumes that the piece is in the board
 *		       and must thus be removed before it can be put into
 *                     its new position (or back into its old position
 *                     on failure)
 * INPUTS: b -- the board
 *         p -- the type of piece
 *         orient -- the current orientation of the piece
 *         x -- current horizontal coordinate of the piece's center point
 *         y -- current vertical coordinate of the piece's center point
 * OUTPUTS: b -- the board, with the piece moved left (on success), or
 *               unchanged on failure
 * RETURN VALUE: 1 on success, 0 on failure
 * SIDE EFFECTS: none
 */
int32_t
try_to_move_left (space_type_t b[BOARD_HEIGHT][BOARD_WIDTH],
                  piece_type_t p, int32_t orient, int32_t x, int32_t y)
{
  //return_val is the value returned by the function
  int32_t return_val = 1;

  //remove piece from the board, decrease the column number
  remove_piece (b, p, orient, x, y);
  x--;

  //test if the block fits there
  if(FIT_SUCCESS != test_piece_fit (b, p, orient, x, y))
  {
      //if it doesn't, move back to the original column, set return value to zero
      x++;
      return_val = 0;
  }

  //add the piece to the board, return the return value
  add_piece (b, p, orient, x, y);
  return return_val;
}


/*
 * try_to_move_right -- tries to move the current piece one space right in
 *                     the board; assumes that the piece is in the board
 *		       and must thus be removed before it can be put into
 *                     its new position (or back into its old position
 *                     on failure)
 * INPUTS: b -- the board
 *         p -- the type of piece
 *         orient -- the current orientation of the piece
 *         x -- current horizontal coordinate of the piece's center point
 *         y -- current vertical coordinate of the piece's center point
 * OUTPUTS: b -- the board, with the piece moved right (on success), or
 *               unchanged on failure
 * RETURN VALUE: 1 on success, 0 on failure
 * SIDE EFFECTS: none
 */
int32_t
try_to_move_right (space_type_t b[BOARD_HEIGHT][BOARD_WIDTH],
                   piece_type_t p, int32_t orient, int32_t x, int32_t y)
{
  //return_val is the return value, remove the piece from the board, incease column number
  int32_t return_val = 1;
  remove_piece (b, p, orient, x, y);
  x++;
  if(FIT_SUCCESS != test_piece_fit (b, p, orient, x, y))
  {
    //if it doesn't, move back to the original column, set return value to zero
      x--;
      return_val = 0;
  }
  //add the piece into the board, return the return value
  add_piece (b, p, orient, x, y);
  return return_val;
}


/*
 * try_to_rotate_clockwise --
 *	tries to rotate the current piece clockwise in the board; assumes
 *	that the piece is in the board and must thus be removed before it
 *	can be put into its new position (or back into its old position on
 *	failure)
 * INPUTS: b -- the board
 *         p -- the type of piece
 *         orient -- the current orientation of the piece
 *         x -- current horizontal coordinate of the piece's center point
 *         y -- current vertical coordinate of the piece's center point
 * OUTPUTS: b -- the board, with the piece rotated clockwise (on success),
 *		 or unchanged on failure
 * RETURN VALUE: 1 on success, 0 on failure
 * SIDE EFFECTS: none
 */
int32_t
try_to_rotate_clockwise (space_type_t b[BOARD_HEIGHT][BOARD_WIDTH],
                         piece_type_t p, int32_t orient, int32_t x, int32_t y)
{

  //remove the piece from the board, increment orient, and mod with 4
  int32_t return_val = 1;
  remove_piece (b, p, orient, x, y);
  int32_t orient_copy = (orient+1)%4;
  if(FIT_SUCCESS != test_piece_fit (b, p, orient_copy, x, y))
  {
      //if fit test is not successful, make orient_copy orient again, return val zero
      orient_copy = orient;
      return_val = 0;
  }

  //add the piece back, return the return value
  add_piece (b, p, orient_copy, x, y);
  return return_val;
}


/*
 * try_to_rotate_cc --
 *	tries to rotate the current piece counter-clockwise in the board;
 *	assumes that the piece is in the board and must thus be removed
 *	before it can be put into its new position (or back into its old
 *	position on failure)
 * INPUTS: b -- the board
 *         p -- the type of piece
 *         orient -- the current orientation of the piece
 *         x -- current horizontal coordinate of the piece's center point
 *         y -- current vertical coordinate of the piece's center point
 * OUTPUTS: b -- the board, with the piece rotated counter-clockwise (on
 *		 success), or unchanged on failure
 * RETURN VALUE: 1 on success, 0 on failure
 * SIDE EFFECTS: none
 */
int32_t
try_to_rotate_cc (space_type_t b[BOARD_HEIGHT][BOARD_WIDTH],
                  piece_type_t p, int32_t orient, int32_t x, int32_t y)
{
  //remove the piece from the board, set the orient value to orient+3 modulo 4
  int32_t return_val = 1;
  remove_piece (b, p, orient, x, y);
  int32_t orient_copy = (orient+3)%4;
  if(FIT_SUCCESS != test_piece_fit (b, p, orient_copy, x, y))
  {
      //if the fit test is not successful, move orient into orient_copy, return val = 0
      orient_copy = orient;
      return_val = 0;
  }

  //add back the piece in its place
  add_piece (b, p, orient_copy, x, y);
  return return_val;
}


/*
 * remove_row -- removes a single row from a board, moving rows above
 *		 it downward and adding a new empty row at the top of
 *		 the board; this function should be called by your
 *		 remove_full_rows function
 * INPUTS: b -- the board
 *	   row -- which row to remove
 * OUTPUTS: b -- the board, with the specified row removed
 * RETURN VALUE: none
 * SIDE EFFECTS: none
 */
void
remove_row (space_type_t b[BOARD_HEIGHT][BOARD_WIDTH], int row)
{
    //x is the column number, row_copy holds the row number
    int32_t x;
    int32_t row_copy = row;

    //for each column
    for(x = 0; x < BOARD_WIDTH; x++)
    {
        //copy element from the previous row into current row till row_copy is 0
        while(row_copy > 0)
        {
            b[row_copy][x] = b[row_copy-1][x];
            row_copy--;
        }
        //reset row copy to row, and set the first row entry to 0 (empty the first row)
        row_copy = row;
        b[0][x] = SPACE_EMPTY;
    }
}

/*
 * remove_full_rows -- removes all rows filled with SPACE_FULL from a
 * 		       board, moving rows above them downward and adding
 *		       new empty rows at the top of the board
 * INPUTS: b -- the board
 * OUTPUTS: b -- the board, with full rows removed
 * RETURN VALUE: none
 * SIDE EFFECTS: none
 */
void
remove_full_rows (space_type_t b[BOARD_HEIGHT][BOARD_WIDTH])
{
    //is_full used to check if row is full (1 if full, 0 if not)
    int32_t is_full = 1;
    //row is row number, x is column number
    int32_t row = 0;
    int32_t x;
    while(row < BOARD_HEIGHT)
    {
        for(x = 0; x < BOARD_WIDTH ; x++)
        {
            //if even a single block is empty, the whole row isn't full
            if(b[row][x] != SPACE_FULL)
                is_full = 0;
        }

        //if the row is full, remove it
        if(is_full == 1)
            remove_row(b, row);

        //reset is_full to 1, check for next row till all rows are done
        is_full = 1;
        row++;
    }
}
