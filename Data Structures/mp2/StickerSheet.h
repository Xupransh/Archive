/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

 #include "Image.h"
 #include <utility>
 #include <vector>

 class StickerSheet {

  private:

    //array that holds images
    std::vector<Image*> image_array;

    Image* base_image;

    //array that stores x,y locations as a pair, one to one correspondence
    std::vector<std::pair <unsigned int, unsigned int>> image_location;

    //max number of images
    unsigned int max_images;

    void copy (const StickerSheet &other);

    void renderHelper (Image &new_image) const;

    void clear();

  public:

    StickerSheet (const Image &picture, unsigned max);

    ~StickerSheet ();

    StickerSheet (const StickerSheet &other);

    const StickerSheet & 	operator= (const StickerSheet &other);

    void changeMaxStickers (unsigned max);

    int addSticker (Image &sticker, unsigned x, unsigned y);

    bool translate (unsigned index, unsigned x, unsigned y);

    void removeSticker (unsigned index);

    Image * getSticker (unsigned index) const;

    Image render () const;

 };
