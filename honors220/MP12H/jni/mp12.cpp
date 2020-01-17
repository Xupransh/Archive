//									tab:8
//
// mp12.cpp - source file for Spring 2018 MP12 student code
//
// "Copyright (c) 2018 by Steven S. Lumetta."
//
// Permission to use, copy, modify, and distribute this software and its
// documentation for any purpose, without fee, and without written agreement is
// hereby granted, provided that the above copyright notice and the following
// two paragraphs appear in all copies of this software.
//
// IN NO EVENT SHALL THE AUTHOR OR THE UNIVERSITY OF ILLINOIS BE LIABLE TO
// ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION,
// EVEN IF THE AUTHOR AND/OR THE UNIVERSITY OF ILLINOIS HAS BEEN ADVISED
// OF THE POSSIBILITY OF SUCH DAMAGE.
//
// THE AUTHOR AND THE UNIVERSITY OF ILLINOIS SPECIFICALLY DISCLAIM ANY
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE
// PROVIDED HEREUNDER IS ON AN "AS IS" BASIS, AND NEITHER THE AUTHOR NOR
// THE UNIVERSITY OF ILLINOIS HAS ANY OBLIGATION TO PROVIDE MAINTENANCE,
// SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS."
//
// Author:	    Steve Lumetta
// Version:	    1.00
// Creation Date:   20 April 2018
// Filename:	    mp12.cpp
// History:
//	SL	1.00	20 April 2018
//		First written.
//

#include <iostream>
#include <list>

#include <math.h>
#include <stdio.h>
#include <string.h>
#include "WALYmain.h"

#include "TurtleScreen.h"

#include "mp5.h"
#include "mp12.h"

using namespace std;
using namespace WALY;

#define PI 3.14159265

// THESE ARE GLOBAL VARIABLES IN THE INTEREST OF TESTING.  THEY SHOULD
// BE FILE-SCOPE OR LOCAL TO frameUpdate.
FILE*           input = NULL;		// input stream
list<segment_t> lines;			// list of lines drawn
command_t       cmd = {CMD_NONE};	// current command
int32_t	        moveColor = 0xFFFFFF;	// current movement drawing color

/* Helper function used to calculate the end point of a move */
void calculateEnd(TurtleScreen *ts, int32_t dist) {

    /* Dist is the hypotenuse, the change is x is calculated as the
     * product of the hypotenuse and the sin of the angle, and
     * the change in y is the cosine
     */
    double x_change = -dist*sin(ts->getDirection()*(PI)/18);
    double y_change = -dist*cos(ts->getDirection()*(PI)/18);
    cmd.endX = cmd.startX + int32_t(round(x_change));
    cmd.endY = cmd.startY + int32_t(round(y_change));
}

/* Function used to turn the turtle (also used to wait, since a wait is a 0
 * degree turn)
 */
void add_turn(TurtleScreen *ts) {
    //frame update calls this framesLeft times
    if(cmd.framesLeft-- > 0) {
        //turn based on cmd.dir
        if(cmd.dir == 1) ts->turnLeft();
        else if (cmd.dir == -1) ts->turnRight();
        ts->makeVisibleChange();
    }
    //change type to cmd_none
    else {
      cmd.type = CMD_NONE;
    }
}

/*Function used to move the turtle*/
void addMove(TurtleScreen *ts) {
    //frame update calls this framesLeft times
    if(cmd.framesLeft-- == 0 || cmd.framesLeft < 0) {
      cmd.type = CMD_NONE;
      return;
    }
    //add a new line with the correct attributes
    segment_t element;
    element.color = moveColor;
    element.x1 = ts->getX();
    element.y1 = ts->getY();

    //calculate x2 and y2 using linear approximation
    element.x2 = cmd.startX+
    int32_t(round((double(cmd.endX-cmd.startX)*double(cmd.cmdFrames-cmd.framesLeft))/double(cmd.cmdFrames)));
    element.y2 = cmd.startY+
    int32_t(round((double(cmd.endY-cmd.startY)*double(cmd.cmdFrames-cmd.framesLeft))/double(cmd.cmdFrames)));

    //change the turtle's positions, draw the line, and make the change Visible
    ts->setX(element.x2);
    ts->setY(element.y2);
    lines.push_back(element);
    drawEverything();
    ts->makeVisibleChange();
}

/*Check if the command is valid, return an int indicating it's type*/
int32_t isValidToken(char *ptr) {
    if(!strcasecmp(ptr,"color")) {
        return 1;
    } else if(!strcasecmp(ptr,"turn")) {
        return 2;
    } else if(!strcasecmp(ptr,"wait")) {
        return 3;
    } else if(!strcasecmp(ptr,"restart")) {
        return 4;
    } else if(!strcasecmp(ptr,"move")) {
        return 5;
    } else {
        return -1;
    }
}

/*set command based on the type of command, return 1 if successful*/
int32_t setCommand (TurtleScreen *ts, char* buf, int32_t type) {
    //set required variables
    int32_t frames = 0,dist = 0;
    char trailing[2];
    //change color
    if(1 == type) {
        //set color if the argument is correctly formatted
        if(1 == sscanf(buf,"%*s%*[ ]%X%1s",&moveColor,trailing)) {
          //Screen::debug ()<< "argument: " << moveColor << endl;
          set_color(moveColor);
          cmd.type = CMD_NONE;
          return 1;
        }
    }
    //turn, wait - the same function handle turns and waits
    else if(2 == type || 3 == type) {

        if(1 == sscanf(buf,"%*s%*[ ]%d%1s",&frames,trailing)) {
            //set the commands based on the type
            cmd.type = CMD_WAIT;
            cmd.cmdFrames = cmd.framesLeft = (frames>0)?(frames):(-frames);

            //if type is turn, set direction and type
            if(type == 2) {
              cmd.type = CMD_TURN;
              cmd.dir = (frames > 0)?(1):(-1);
            } else {
              cmd.dir = 0;
            }

            //set X and Y values
            cmd.startX = cmd.endX = ts->getX();
            cmd.startY = cmd.endY = ts->getY();
            return 1;
        }
    }

    //handle restart
    else if(4 == type) {
        //rewind the input buffer if the format is valid
        if(!sscanf(buf,"%*[\n]%*[ ]%1s",trailing)) {
          rewind(input);
          return 1;
        }
    }

    //handle movement
    else if(5 == type) {
        //if the format is correct, set up the command, and return 1
        if(2 == sscanf(buf,"%*s%*[ ]%d%*[ ]%d%1s", &dist, &frames, trailing)){
            //Screen::debug () << "Dist: " << dist << " frames:" << frames << endl;
            cmd.type = CMD_MOVE;
            cmd.cmdFrames = cmd.framesLeft = (dist>=0)?(frames):(-1);
            cmd.startX = ts->getX();
            cmd.startY = ts->getY();
            //calculate the end point for the move
            calculateEnd(ts,dist);
            return 1;
        }
    }
    //return 0 on failure
    return 0;
}

//function used to open the command file
int32_t openInputStream (const char* fname) {
    return (NULL != (input= fopen(fname, "r")));
}

//function used to close the command file
void closeInputStream (void) {
    fclose(input);
}

void showLines (void) {
    // you can use 'call showLines ()' in GDB to look at the
    // list of segments.  Don't forget to call makeVisibleChange
    // when you change this list, since the background won't be
    // redrawn unless you call that function (so changes will not
    // show up.
   for (list<segment_t>::iterator it = lines.begin ();
	 lines.end () != it; it++) {
  Screen::debug () << it->color << " " << it->x1 << "," << it->y1 << "  " << it->x2 << "," << it->y2 << endl;
    }
}

//draw a list of lines
void drawEverything (void) {
    //set the color, draw the line for each line in linked list
    for (list<segment_t>::iterator it = lines.begin (); lines.end () != it; it++) {
     set_color(it->color);
     draw_line(it->x1,it->y1,it->x2,it->y2);
    }
}

//function used to read through the commands file
void readNewCommand (TurtleScreen* ts) {
    //declare variables
    char buf[201];
    char token[100];
    int32_t token_type;
    //while end of files isn't reached
    while (!feof(input)) {
        //if there's a line
        if(fgets(buf,201,input)) {
              //if the format is correct
              if(1 == sscanf(buf, "%s", token)) {
                  //and the command is correct, and the arguments are formatted correctly
                  if(-1 != (token_type = isValidToken(token)) && setCommand(ts,buf,token_type)) {
                      //call the required function for the current frame
                      if (token_type == 2 || token_type == 3) {
                        add_turn(ts);
                      } else if(token_type == 5) {
                        addMove(ts);
                      } else if(token_type == 4 || token_type == 1) {
                        readNewCommand(ts);
                      }
                      return;
                  }
                  //print error messages
                  else {
                     fprintf(stderr, "This was a bad command: %s\n", buf);
                  }
              }
              //print error messages
              else {
                  fprintf(stderr, "This was a bad command: %s\n", buf);
              }
          }
     }
     //set command to none, clear up all lines
     cmd.type = CMD_NONE;
     while(!lines.empty()) {
       lines.pop_back();
     }
}

void frameUpdate (TurtleScreen* ts) {
    //switch based on currect command
    switch (cmd.type) {
      case CMD_NONE:   readNewCommand(ts); break;
      case CMD_MOVE:   addMove(ts); break;
      case CMD_TURN:   add_turn(ts); break;
      case CMD_WAIT:   add_turn(ts); break;
      default: Screen::debug () << "Something's wrong!" << endl;
    }
}
