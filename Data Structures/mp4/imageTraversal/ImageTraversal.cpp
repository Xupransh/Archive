#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"


static const std::vector< std::vector<int> > directions =
  { {1,0}, {0,1}, {-1,0}, {0,-1} };

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 * 
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );    
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() : traversal(NULL) {
  /** @todo [Part 1] */
}

ImageTraversal::Iterator::Iterator(ImageTraversal & img_traversal, Point & start,
                                   PNG & t_png, double t_tolerance) :
  traversal(&img_traversal) {
  /** @todo [Part 1] */
  png = t_png;
  int width = png.width();
  int height = png.height();
  std::vector < std::vector<int> > temp(width, std::vector<int> (height, 0));
  visited = temp;
  current = start;
  start_point = start;
  tolerance = t_tolerance;
  last.x = width-1;
  last.y = height-1;
}

bool ImageTraversal::Iterator::isValid (const Point & current) {
  if ((current < zero) || (last < current)) {
    return false;
  }
  const HSLAPixel curr_pixel = png.getPixel(current.x, current.y);
  const HSLAPixel start_pixel = png.getPixel(start_point.x, start_point.y);
  if (calculateDelta(curr_pixel, start_pixel) > tolerance ||
      visited[current.x][current.y]) {
    return false;
  }
  return true;
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  for (auto i : directions) {
    Point neighbor;
    neighbor.x = current.x + i[0];
    neighbor.y = current.y + i[1];
    if (isValid(neighbor)) {
      traversal->add(neighbor);
    }
  }
  visited[current.x][current.y] = 1;
  while (visited[current.x][current.y]) {
    if(!traversal->empty()) { current = traversal->pop(); }
    else { return *this; }
  }
  return *this;
}

/**
 * Iterator accessor opreator.
 * 
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return current;
}

/**
 * Iterator inequality operator.
 * 
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  bool thisEmpty;
  bool otherEmpty;
  thisEmpty = (traversal == NULL)? true : traversal->empty();
  otherEmpty = (other.traversal == NULL)? true : other.traversal->empty();
  if (thisEmpty && otherEmpty) {
    return false;
  } else if (!thisEmpty && !otherEmpty) {
    return traversal != other.traversal;
  }
  return true;
}

