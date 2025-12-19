#include "./Framebuffer.h"
#include <cstdlib>
#include <ctime>

int main(void)
{
  std::srand(std::time(nullptr));
 
  try
  {
    Framebuffer fbo(1024, 1024); // initalizing a framebuffer of width and height 1024px
    fbo.ClearFramebuffer(CP::WHITE); // clearning the framebuffer with white color

    for(int i = 0; i < 1000; i++){
      int x0 = std::rand() % fbo.Width();
      int y0 = std::rand() % fbo.Height();
      int x1 = std::rand() % fbo.Width();
      int y1 = std::rand() % fbo.Height();

      uint8_t r = std::rand() % 256;
      uint8_t g = std::rand() % 256;
      uint8_t b = std::rand() % 256;
      
      fbo.PutLine(x0, y0, x1, y1, r, g, b); // rasterizes a line for specified two points and color
    }
    fbo.BlitFramebuffer(); // blits the framebuffer to a .ppm file and stores it in the same directory 
  }
  catch(Color::Invalid)
  {
    std::cerr << "Error: Color::Invalid" << std::endl;
    exit(1);
  }

  return 0;
}

