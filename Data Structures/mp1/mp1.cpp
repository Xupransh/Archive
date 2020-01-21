#include "cs225/PNG.h"
using cs225::PNG;

#include "cs225/HSLAPixel.h"
using cs225::HSLAPixel;

#include <string>
#include <cmath>
#include <complex>

static const double PI = 3.1415;

static const double PI_degrees = 180.0;

using std::complex;

//solution to part 2
void rotate(std::string inputFile, std::string outputFile) {
  PNG input;
  if(!input.readFromFile(inputFile)) {
    return;
  }
  PNG output(input.width(), input.height());
  unsigned int new_x, new_y;
  for(unsigned int x = 0; x < input.width(); x++) {
    for(unsigned int y = 0; y < input.height(); y++) {
      HSLAPixel & pixel = input.getPixel(x,y);
      new_x = -x+input.width()-1;
      new_y = -y+input.height()-1;
      HSLAPixel & output_pixel  = output.getPixel(new_x, new_y);
      output_pixel.h = pixel.h;
      output_pixel.s = pixel.s;
      output_pixel.l = pixel.l;
      output_pixel.a = pixel.a;
    }
  }
  if(!output.writeToFile(outputFile)) {
    return;
  }
}


//The function to be plotted, you could technically
//replace this with a function that parses a function
//string. Default function is sin(z)
complex<double> function(double x, double y, unsigned int width) {

  //domain
  x = 6*x/double(width);
  y = 6*y/double(width);

  // complex<double> a(x,y);
  // a = pow(a, 2);
  // complex<double> b(x - 2, y - 1);
  // b = pow(b,2);
  // complex<double> c(2,2);
  // return (a-1.0)*(b)/(a+c);

  // complex<double> a(x,y);
  // complex<double> b(x+2,y-1);
  // b = pow(b,2);
  // complex<double> d(2,-2);
  // d = pow(d,2);
  // return ((a*a-1.0)*b)/(a*a+d);

  // complex<double> a(x,y);
  // return a*sin(10.0/a);

  // complex <double> a(x,y);
  // return a;

  // complex <double> a(x,y);
  // return 1.0/a;

  // complex <double> a(x,y);
  // return pow(a,3) - 1.0;

  complex<double> a(x, y);
  return sin(a);

  // complex<double> a(x,y);
  // return pow(a,5) - 1.0;

}


/*
Color function, can be modified
*/
void colorFunction(HSLAPixel &pixel, complex<double> number) {

  double degrees, log_mag;
  double epsilon = 0.7;
  degrees = arg(number);
  if(degrees < 0) {
    degrees += 2*PI;
  }
  pixel.h = degrees*PI_degrees/PI;
  pixel.s = 1;
  log_mag = log(abs(number))/log(2);
  pixel.a = log_mag-floor(log_mag);
  if(pixel.a <= epsilon) {
    pixel.a = epsilon;
  }
  pixel.l = 0.5;

}

/*
K. Poelke and K. Polthier,
"Domain Coloring of Complex Functions:
An Implementation-Oriented Introduction," in IEEE Computer Graphics and Applications,
vol. 32, no. 5, pp. 90-97, Sept.-Oct. 2012.
doi: 10.1109/MCG.2012.100

Phase Plots of Complex
Functions:
A Journey in Illustration
Elias Wegert and Gunter Semmler

github.com/empet

*/

PNG myArt(unsigned int width, unsigned int height) {
  PNG png(width, height);
  double x,y;

  //for each pixel
  for (unsigned int i = 0 ; i < width ; i++) {
    for (unsigned int j = 0 ; j < height ; j++) {

      //re evaulate position in coordinate system
      x = (int(2*i)-int(width));
      y = -(int(2*j)-int(height));
      x = x/2;
      y = y/2;

      //apply function
      complex<double> number = function(x,y,width);
      HSLAPixel &pixel = png.getPixel(i,j);

      //apply colorFunction
      colorFunction(pixel, number);
    }
  }
  return png;
}
