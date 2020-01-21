/* Your code here! */
#pragma once

#include <vector>
#include "cs225/PNG.h"

using namespace cs225;

class SquareMaze {

public :  SquareMaze ();

public :  void makeMaze(int width, int height);

public :  bool canTravel(int x, int y, int dir) const;

public :  void setWall(int x, int y, int dir, bool exists);

public :  std::vector<int> solveMaze ();

public :  PNG * drawMaze () const;

public :  PNG * drawMazeWithSolution ();

private :
    enum { RIGHT = 0, DOWN = 1, LEFT = 2, UP = 3 };

private :
    struct wall {
        bool down;
        bool right;
    };

    struct point {
        int x;
        int y;
    };

private : std::vector< std::vector <wall> > maze;

private : int width_, height_;

private:
    int increment (int dir) const;
    int incrementX (int dir) const;
    int incrementY (int dir) const;

};
