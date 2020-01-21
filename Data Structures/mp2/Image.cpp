#include "Image.h"
#include <math.h>

using namespace cs225;

static const double change = 0.1;
static const int ill_orange = 11;
static const int ill_blue = 216;

void copyImage(PNG &old_image, Image &new_image) {
  unsigned int old_width = old_image.width();
  unsigned int old_height = old_image.height();
  for (unsigned int i = 0; i < old_width; i++) {
    for(unsigned int j = 0; j < old_height; j++) {
      HSLAPixel & pixel = new_image.getPixel(i,j);
      HSLAPixel & pixel_2 = old_image.getPixel(i,j);
      pixel_2 = pixel;
    }
  }
}

void Image::lighten() {
  for(unsigned int x = 0; x < width(); x++) {
    for(unsigned int y = 0; y < height(); y++) {
      HSLAPixel &pixel = getPixel(x,y);
      pixel.l += change;
      if(pixel.l > 1.0) {
        pixel.l = 1.0;
      }
    }
  }
}

void Image::lighten(double amount) {
  for(unsigned int x = 0; x < width() ; x++) {
    for(unsigned int y = 0; y < height(); y++) {
      HSLAPixel &pixel = getPixel(x,y);
      pixel.l += amount;
      if (pixel.l > 1.0) {
        pixel.l = 1.0;
      }
    }
  }
}

void Image::darken() {
  for(unsigned int x = 0; x < width() ; x++) {
    for(unsigned int y = 0; y < height(); y++) {
      HSLAPixel &pixel = getPixel(x,y);
      pixel.l -= change;
      if (pixel.l < 0) {
        pixel.l = 0;
      }
    }
  }
}

void Image::darken(double amount) {
  for(unsigned int x = 0; x < width() ; x++) {
    for(unsigned int y = 0; y < height(); y++) {
      HSLAPixel &pixel = getPixel(x,y);
      pixel.l -= amount;
      if (pixel.l < 0) {
        pixel.l = 0;
      }
    }
  }
}

void Image::saturate() {
  for(unsigned int x = 0; x < width() ; x++) {
    for(unsigned int y = 0; y < height(); y++) {
      HSLAPixel &pixel = getPixel(x,y);
      pixel.s += change;
      if (pixel.s > 1.0) {
        pixel.s = 1.0;
      }
    }
  }
}

void Image::saturate(double amount) {
  for(unsigned int x = 0; x < width() ; x++) {
    for(unsigned int y = 0; y < height(); y++) {
      HSLAPixel &pixel = getPixel(x,y);
      pixel.s += amount;
      if(pixel.s > 1.0) {
        pixel.s = 1.0;
      }
    }
  }
}

void Image::desaturate() {
  for(unsigned int x = 0; x < width() ; x++) {
    for(unsigned int y = 0; y < height(); y++) {
      HSLAPixel &pixel = getPixel(x,y);
      pixel.s -= change;
      if (pixel.s < 0) {
        pixel.s = 0;
      }
    }
  }
}

void Image::desaturate(double amount) {
  for(unsigned int x = 0; x < width() ; x++) {
    for(unsigned int y = 0; y < height(); y++) {
      HSLAPixel &pixel = getPixel(x,y);
      pixel.s -= amount;
      if (pixel.s < 0) {
        pixel.s = 0;
      }
    }
  }
}

void Image::grayscale() {
  for(unsigned int x = 0; x < width() ; x++) {
    for(unsigned int y = 0; y < height(); y++) {
      HSLAPixel &pixel = getPixel(x,y);
      pixel.s = 0;
    }
  }
}

void Image::rotateColor(double degrees) {
  while(degrees < 0) {
    degrees = 360+degrees;
  }
  for (unsigned int x = 0; x < width(); x++) {
    for(unsigned int y = 0; y < height(); y++) {
      HSLAPixel &pixel = getPixel(x,y);
      pixel.h = fmod(pixel.h+degrees, 360);
    }
  }
}

void Image::illinify() {
  for (unsigned int x = 0; x < width(); x++) {
    for(unsigned int y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x,y);
      if(pixel.h < ill_orange) {
        pixel.h = ill_orange;
      } else if(pixel.h > ill_orange && pixel.h < ill_blue) {
        if(pixel.h <= (ill_blue+ill_orange)/2) {
            pixel.h = ill_orange;
        } else {
            pixel.h = ill_blue;
        }
      } else if (pixel.h > ill_blue){
        if(pixel.h <= (ill_blue+ill_orange+360)/2) {
          pixel.h = ill_blue;
        } else {
          pixel.h = ill_orange;
        }
      }
    }
  }
}

void Image::scale(double factor) {
  unsigned int old_width = width();
  unsigned int old_height = height();
  PNG old_image(old_width, old_height);
  copyImage(old_image, *this);
  unsigned int new_width = factor*old_width;
  unsigned int new_height = factor*old_height;
  resize(new_width, new_height);
  unsigned int x,y;
  for (unsigned int i = 0; i < new_width ; i++) {
    for(unsigned int j = 0; j < new_height ; j++) {
      x = double(i)/factor;
      y = double(j)/factor;
      HSLAPixel & pixel_old = old_image.getPixel(x,y);
      HSLAPixel & pixel_new = this->getPixel(i,j);
      pixel_new = pixel_old;
    }
  }
}

void Image::scale(unsigned int w, unsigned int h) {
  unsigned int old_width = width();
  unsigned int old_height = height();
  PNG old_image(old_width, old_height);
  copyImage(old_image, *this);
  resize(w,h);
  double x_ratio = old_width/w;
  double y_ratio = old_height/h;
  unsigned int x,y;
  for (unsigned int i = 0; i < w; i++) {
    for(unsigned int j = 0; j < h; j++) {
      x = double(i)/x_ratio;
      y = double(j)/y_ratio;
      HSLAPixel & p_old = old_image.getPixel(x,y);
      HSLAPixel & p_new = this->getPixel(i,j);
      p_new = p_old;
    }
  }
}
