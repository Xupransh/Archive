/* Your code here! */
#include "maze.h"
#include "dsets.h"
#include <cstdlib>
#include <algorithm>
#include <queue>

using namespace cs225;

SquareMaze::SquareMaze() {}

void SquareMaze::makeMaze(int width, int height)
{
    width_ = width;
    height_ = height;

    DisjointSets s;
    s.addelements(width*height);

    wall blocked = {true, true};
    maze.clear();
    maze.resize(width, std::vector<wall>(height, blocked));

    int rand_x, rand_y, dir, rand_disjoint,
        root, edges = 0;

    while (edges != width*height - 1) {

        rand_x = rand()%(width);
        rand_y = rand()%(height);
        dir = rand()%2;

        rand_disjoint = rand_x + rand_y*width;
        root = s.find(rand_disjoint);

        if (dir == RIGHT && rand_x != width - 1) {
            if (s.find(rand_disjoint + 1) != root) {
                s.setunion(rand_disjoint + 1, rand_disjoint);
                setWall(rand_x, rand_y, RIGHT, false);
                edges++;
            }
        } else if (dir == DOWN && rand_y != height - 1) {
            if (s.find(rand_disjoint + width) != root) {
                s.setunion(rand_disjoint + width, rand_disjoint);
                setWall(rand_x, rand_y, DOWN, false);
                edges++;
            }
        }
    }
}

void SquareMaze::setWall(int x, int y, int dir, bool exists)
{
    if(dir == DOWN) {
        maze[x][y].down = exists;
    } else {
        maze[x][y].right = exists;
    }
}

bool SquareMaze::canTravel(int x, int y, int dir) const
{
    if (dir == RIGHT) {
        if (x == width_ - 1 || maze[x][y].right) {
            return false;
        }
    } else if (dir == DOWN) {
        if (y == height_ - 1 || maze[x][y].down) {
            return false;
        }
    } else if (dir == LEFT) {
        if (x == 0 || maze[x-1][y].right) {
            return false;
        }
    } else if (dir == UP) {
        if (y == 0 || maze[x][y-1].down) {
            return false;
        }
    }
    return true;
}

int SquareMaze::increment(int dir) const
{
    if (dir == RIGHT) {
        return 1;
    } else if (dir == DOWN) {
        return width_;
    } else if (dir == LEFT) {
        return -1;
    }
    return -1*width_;
}

int SquareMaze::incrementX(int dir) const
{
    if (dir == RIGHT) {
        return 1;
    } else if (dir == LEFT) {
        return -1;
    }
    return 0;
}

int SquareMaze::incrementY(int dir) const
{
    if (dir == DOWN) {
        return 1;
    } else if (dir == UP) {
        return -1;
    }
    return 0;
}

std::vector<int> SquareMaze::solveMaze ()
{
    std::vector<int> distance(width_*height_, INT_MAX);
    std::vector<int> path(width_*height_);
    std::vector<int> parent(width_*height_);
    std::vector<int> directions = {RIGHT, DOWN, LEFT, UP};
    std::vector<int> result;
    std::queue<point> maze_queue;

    point start = {0,0};
    maze_queue.push(start);
    distance[0] = 0;
    point curr, temp;
    int index, incr;

    while (!maze_queue.empty()) {

        curr = maze_queue.front();
        maze_queue.pop();
        index = curr.x + curr.y*width_;

        for (auto & d : directions) {
            if (canTravel(curr.x, curr.y, d)) {
                int incr = increment(d);
                if (distance[index + incr] == INT_MAX) {
                    distance[index + incr] = distance[index] + 1;
                    path[index + incr] = d;
                    parent[index + incr] = index;
                    temp.x = curr.x + incrementX(d);
                    temp.y = curr.y + incrementY(d);
                    maze_queue.push(temp);
                }
            }
        }
    }

    auto max_dist_it =
        std::max_element(distance.begin() + width_*(height_- 1),
                         distance.end());

    int max_index = std::distance(distance.begin(), max_dist_it);

    while (max_index > 0) {
        result.push_back(path[max_index]);
        max_index = parent[max_index];
    }

    std::reverse(result.begin(), result.end());
    return result;
}


PNG * SquareMaze::drawMaze() const
{
    int img_width = width_*10 + 1;
    int img_height = height_*10 + 1;
    PNG * maze = new PNG(img_width, img_height);
    std::vector<int> directions = {DOWN, RIGHT};
    HSLAPixel black(0,0,0);
    int incr_x, incr_y;

    for (int i = 10; i < img_width; i++) {
        HSLAPixel & p = maze->getPixel(i, 0);
        p = black;
    } for (int j = 0; j < img_height; j++) {
        HSLAPixel & p = maze->getPixel(0, j);
        p = black;
    } for (int i = 0; i < width_; i++) {
        for (int j = 0; j < height_; j++) {

            for (auto & d : directions) {
                incr_x = incrementX(d);
                incr_y = incrementY(d);

                if (!canTravel(i, j, d)) {
                    for(int k = 0; k <= 10; k++) {
                        HSLAPixel & p =
                            maze->getPixel((i + incr_x)*10 + (1 - incr_x)*k,
                                           (j + incr_y)*10 + (1 - incr_y)*k);
                        p = black;
                    }
                }
            }
        }
    }
    return maze;
}

PNG * SquareMaze::drawMazeWithSolution()
{
    PNG * solution_maze = drawMaze();
    std::vector<int> solution_path = solveMaze();
    std::vector<int> directions = {RIGHT, DOWN, LEFT, UP};
    int x = 5;
    int y = 5;
    int incr_x, incr_y;
    HSLAPixel red(0,1,0.5,1);
    HSLAPixel white;

    for (size_t i = 0; i < solution_path.size(); i++) {
        for (auto & d : directions) {
            incr_x = incrementX(d);
            incr_y = incrementY(d);
            if (solution_path[i] == d) {
                for (int j = 0; j < 11; j++) {
                    HSLAPixel & p =
                        solution_maze->getPixel(x + j*incr_x,
                                                y + j*incr_y);
                    p = red;
                }
                x = x + incr_x*10;
                y = y + incr_y*10;
            }
        }
    }

    x -= 5;
    y += 5;
    for (int i = 1; i <= 9; i++) {
        HSLAPixel & p = solution_maze->getPixel(x+i, y);
        p = white;
    }
    return solution_maze;
}

