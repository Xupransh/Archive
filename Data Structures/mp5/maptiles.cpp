/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    int rows = theSource.getRows();
    int columns = theSource.getColumns();
    MosaicCanvas * canvas = new MosaicCanvas(rows, columns);
    vector< Point<3> > tilePixels;
    map <Point<3>, int> m;
    for (unsigned long i = 0; i < theTiles.size(); i++) {
        Point<3> average_pixel = convertToXYZ(theTiles[i].getAverageColor());
        m.insert(make_pair(average_pixel, i));
        tilePixels.push_back(average_pixel);
    }
    KDTree<3> tree(tilePixels);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            Point <3> nearest_pixel = tree.findNearestNeighbor(convertToXYZ(theSource.getRegionColor(i, j)));
            canvas->setTile(i, j, &theTiles[m.find(nearest_pixel)->second]);
        }
    }
    return canvas;
}

