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
    
    for(int i = 0; i < 10; i++){
      int x0 = std::rand() % fbo.Width();
      int y0 = std::rand() % fbo.Height();
      int x1 = std::rand() % fbo.Width();
      int y1 = std::rand() % fbo.Height();
      int x2 = std::rand() % fbo.Width();
      int y2 = std::rand() % fbo.Height();
      
      auto area2 = x0 * (y1 - y2) +
                   x1 * (y2 - y0) +
                   x2 * (y0 - y1);

      if(std::abs(area2) < 10) continue;

      uint8_t r = std::rand() % 256;
      uint8_t g = std::rand() % 256;
      uint8_t b = std::rand() % 256;
      
      //fbo.PutLine(x0, y0, x1, y1, r, g, b); // rasterizes a line for specified two points and color
      fbo.PutFilledTriangle(x0, y0, x1, y1, x2, y2, r, g, b);
      fbo.PutWireframeTriangle(x0, y0, x1, y1, x2, y2, CP::BLACK);
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

