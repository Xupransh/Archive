#include "StickerSheet.h"
#include <iostream>

static const int no_space = -1;

void StickerSheet::copy (const StickerSheet & other) {
  max_images = other.max_images;
  for (auto i : other.image_location) {
    image_location.push_back(i);
  } for (auto i : other.image_array) {
    Image* new_sticker = new Image(*i);
    image_array.push_back(new_sticker);
  }
  base_image = new Image(*(other.base_image));
}

void stickerAttacher(Image &sticker, Image &new_image, unsigned int sticker_x,
  unsigned int sticker_y) {
  for (unsigned int x = 0; x < sticker.width(); x++) {
    for (unsigned int y = 0; y < sticker.height(); y++) {
      while ( x + sticker_x >= new_image.width() || y + sticker_y >= new_image.height()) {
        new_image.scale(2.0);
      }
      cs225::HSLAPixel &pixel = new_image.getPixel(x+sticker_x, y+sticker_y);
      cs225::HSLAPixel &sticker_pixel = sticker.getPixel(x,y);
      pixel = (sticker_pixel.a != 0) ? sticker_pixel : pixel;
    }
  }
}

void StickerSheet::renderHelper (Image &new_image) const {
  unsigned int index = 0;
  while (index < image_array.size()) {
    unsigned int sticker_x = image_location[index].first;
    unsigned int sticker_y = image_location[index].second;
    stickerAttacher(*image_array[index], new_image, sticker_x, sticker_y);
    index++;
  }
}

StickerSheet::StickerSheet (const Image & picture, unsigned int max )	{
  base_image = new Image(picture);
  max_images = max;
}

StickerSheet::StickerSheet (const StickerSheet & other)	{
  copy(other);
}

void StickerSheet::clear() {
  if (base_image) {
    delete base_image;
  } for(auto i : image_array) {
    if (i) {
      delete i;
    }
  }
  image_array.clear();
  image_location.clear();
}

StickerSheet::~StickerSheet () {
  clear();
}

void StickerSheet::changeMaxStickers (unsigned int max)	{
  max_images = max;
  if (image_array.size() > max_images) {
    unsigned int index = max_images;
    while(index < image_array.size()) {
        removeSticker(index);
    }
  }
}

const StickerSheet & StickerSheet::operator= (const StickerSheet & other) {
  if (this != &other) {
    clear();
    copy(other);
  }
  return *this;
}

int StickerSheet::addSticker (Image & sticker, unsigned int	x, unsigned int	y )	{
  if (image_array.size() == max_images) {
    return no_space;
  }
  std::pair<unsigned int, unsigned int> location = std::make_pair(x,y);
  image_location.push_back(location);
  Image* new_sticker = new Image(sticker);
  image_array.push_back(new_sticker);
  return image_array.size()-1;
}

bool 	StickerSheet::translate (unsigned index, unsigned x, unsigned y) {
  if (index < image_location.size()) {
    image_location[index].first = x;
    image_location[index].second = y;
    return true;
  }
  return false;
}

void StickerSheet::removeSticker (unsigned 	index) {
  if (index < image_array.size()) {
    delete image_array[index];
    image_array.erase(image_array.begin() + index);
    image_location.erase(image_location.begin() + index);
  }
}

Image * StickerSheet::getSticker (unsigned index) const {
  if (index < image_array.size()) {
    return image_array[index];
  }
    return NULL;
}

Image StickerSheet::render() const {
  Image result;
  if (!base_image) {
    return result;
  }
  result = *base_image;
  renderHelper(result);
  return result;
}
