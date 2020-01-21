#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    // Write your own main here
    PNG maize;
    maize.readFromFile("maize.png");
    SquareMaze maze;
    HSLAPixel white;
    maze.makeMaze(218, 300);
    PNG * maze_image = maze.drawMazeWithSolution();

    for (int i = 0; i < 2180; i++) {
        for (int j = 0; j < 3000; j++) {
            HSLAPixel & p = maze_image->getPixel(i, j);
            HSLAPixel & maize_p = maize.getPixel(i, j);
            //std::cout << maize_p << std::endl;
            if (maize_p == white) {
                maize_p = p;
            }
        }
    }
    maize.writeToFile("creative.png");
    delete(maze_image);
    return 0;
}
