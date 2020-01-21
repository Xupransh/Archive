#include "Image.h"
#include "StickerSheet.h"

int main() {

  Image wuxi;
  wuxi.readFromFile("wuxi.png");
  Image heap;
  Image destructor;
  heap.readFromFile("Heap.png");
  destructor.readFromFile("Destructor.png");
  StickerSheet sheet(wuxi, 5);
  sheet.addSticker(heap, 340, 100);
  sheet.addSticker(destructor, 80, 350);
  Image result = sheet.render();
  result.writeToFile("myImage.png");

  return 0;
}
