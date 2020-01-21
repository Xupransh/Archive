#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "ParrotPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */

HSLAPixel ParrotPicker::getColor(unsigned int x, unsigned int y) {
  double h = 150;
  double s = 1;
  double l = 0.5;
  return HSLAPixel(h,s,l);
}

