#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
//--------------------------------------------------------------------
//  
//  Name: Framebuffer.h
//
//  Desc: Defines a framebuffer class with capability to blit
//
//  Author: Aayush Bade 2025 (aayushbade14.github.io/Portfolio)
//  
//--------------------------------------------------------------------

#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
#include "./Color.h"
#include "./Math.h"

class Framebuffer
{

public:
  
  class Invalid{};
 
  //index for saving in a ppm file
  static int m_iBlitNum;

  //default constructor for framebuffer
  Framebuffer() : m_pPixels(nullptr),
                  m_iWidth(0),
                  m_iHeight(0)
  {
    #ifdef DEBUG
    std::cout << "Framebuffer init via default constructor!" << std::endl;
    #endif
  }

  //default constructor with fbo size as parameters
  Framebuffer(int width, int height) : m_pPixels(nullptr),
                                       m_iWidth(width),
                                       m_iHeight(height)
  {
    //Allocate memory to framebuffer
    m_pPixels = new Color[m_iWidth * m_iHeight];
    
    #ifdef DEBUG
    std::cout << "Framebuffer init via default constructor: " << m_iWidth << " * "
      << m_iHeight << std::endl;
    #endif
  }

  //destructor for framebuffer
  ~Framebuffer()
  {
    delete[] m_pPixels;
    
    #ifdef DEBUG
    std::cout << "Framebuffer cleaned via destructor!" << std::endl;
    #endif
  }
  
  //copy constructor and copy assignment for framebuffer
  Framebuffer(const Framebuffer& other) : m_pPixels(nullptr),
                                          m_iWidth(other.m_iWidth),
                                          m_iHeight(other.m_iHeight)
  {
    m_pPixels = new Color[m_iWidth * m_iHeight];
    
    int res = m_iWidth * m_iHeight;
    for(int i = 0; i < res; i++)
    {
      m_pPixels[i] = other.m_pPixels[i];
    }
    
    #ifdef DEBUG
    std::cout << "Framebuffer init via copy constructor: " << m_iWidth << " * " 
      << m_iHeight << std::endl;
    #endif
  }

  Framebuffer& operator=(const Framebuffer& other)
  {
    
    if(this == &other) return *this;
    
    delete[] m_pPixels;
    m_pPixels = nullptr;

    m_iWidth = other.m_iWidth;
    m_iHeight = other.m_iHeight;

    m_pPixels = new Color[m_iWidth * m_iHeight];
    
    int res = m_iWidth * m_iHeight;
    for(int i = 0; i < res; i++)
    {
      m_pPixels[i] = other.m_pPixels[i];
    }
    
    #ifdef DEBUG
    std::cout << "Framebuffer init via copy assignment overload: " << m_iWidth << " * "
      << m_iHeight << std::endl;
    #endif

    return *this;
  }
  
  //move assignment and move constructor for framebuffer
  Framebuffer(Framebuffer&& other) : m_pPixels(other.m_pPixels),
                                     m_iWidth(other.m_iWidth),
                                     m_iHeight(other.m_iHeight)
  {
    other.m_pPixels = nullptr;
    other.m_iWidth = 0;
    other.m_iHeight = 0;
    
    #ifdef DEBUG
    std::cout << "Framebuffer init via move constructor: " << m_iWidth << " * "
      << m_iHeight << std::endl;
    #endif  
  }
  
  Framebuffer& operator=(Framebuffer&& other)
  {
    
    if(this == &other) return *this;

    delete[] m_pPixels;
    m_pPixels = nullptr;

    m_iWidth = other.m_iWidth;
    m_iHeight = other.m_iHeight;
    m_pPixels = other.m_pPixels;

    other.m_pPixels = nullptr;
    other.m_iWidth = 0;
    other.m_iHeight = 0;

    #ifdef DEBUG
    std::cout << "Framebuffer init via move operator overload: " << m_iWidth << " * "
      << m_iHeight << std::endl;
    #endif

    return *this;
  }
  
  //operator overload for accessing pixel value
  Color& operator[](int index)
  {
    if(index < 0 || index >= m_iWidth * m_iHeight)
    {
      throw Invalid{};
    }

    return m_pPixels[index];
  }
  
  //getters
  Color* Data(){return m_pPixels;}
  int GetRes(){return m_iWidth * m_iHeight;}
  int Width(){return m_iWidth;}
  int Height(){return m_iHeight;}

  //method for allocating memory to the framebuffer if not already
  void MemAlloc(int width, int height)
  {
    if(m_pPixels) return;
    
    m_iWidth = width;
    m_iHeight = height;
    m_pPixels = new Color[m_iWidth * m_iHeight];
    
    #ifdef DEBUG
    std::cout << "Memory allocated to the framebuffer: " << m_iWidth << " * "
      << m_iHeight << std::endl;
    #endif
  }
  
  //methods for clearing the framebuffer using a color preset or explicit rgb value
  void ClearFramebuffer(CP color)
  {
    int res = m_iWidth * m_iHeight;
    for(int i = 0; i < res; i++)
    {
      m_pPixels[i].SetColor(color);
    }
    
    #ifdef DEBUG
    std::cout << "Framebuffer cleared to color: " << GetColorName(color) << std::endl;
    #endif
  }

  void ClearFramebuffer(uint8_t r, uint8_t g, uint8_t b)
  {

    if(!IS_VALID(r) || !IS_VALID(g) || !IS_VALID(b))
    {
      throw Invalid{};
    }
    
    int res = m_iWidth * m_iHeight;
    for(int i = 0; i < res; i++)
    {
      m_pPixels[i].SetColor(r, g, b);
    }
    
    #ifdef DEBUG
    std::cout << "Framebuffer cleared to color: RGB(" << r << ", " << g << ", " << b << ")"
      << std::endl;
    #endif  
  }
  
  void PutPixel(int x, int y, CP color)
  {
    if(x < 0 || x >= m_iWidth || y < 0 || y >= m_iHeight) return;

    int index = y * m_iWidth + x;
    m_pPixels[index].SetColor(color);
    
    #ifdef DEBUG
    std::cout << "Pixel put into framebuffer at: (" << x << ", " << y << ")" << std::endl;
    #endif
  }

  void PutPixel(const Vec2& v, CP color)
  {
    if(v.iX() < 0 || v.iX() >= m_iWidth || v.iY() < 0 || v.iY() >= m_iHeight) return;

    int index = v.iY() * m_iWidth + v.iX();
    m_pPixels[index].SetColor(color);
    
    #ifdef DEBUG
    std::cout << "Pixel put into framebuffer at: (" << v.iX() << ", " << v.iY() << ")" << std::endl;
    #endif
  }

  void PutPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b)
  {
    if(x < 0 || x >= m_iWidth || y < 0 || y >= m_iHeight) return;

    int index = y * m_iWidth + x;
    m_pPixels[index].SetColor(r, g, b);
    
    #ifdef DEBUG
    std::cout << "Pixel put into framebuffer at: (" << x << ", " << y << ")" << std::endl;
    #endif  
  }
 
  void PutPixel(const Vec2& v, uint8_t r, uint8_t g, uint8_t b)
  {
    if(v.iX() < 0 || v.iX() >= m_iWidth || v.iY() < 0 || v.iY() >= m_iHeight) return;

    int index = v.iY() * m_iWidth + v.iX();
    m_pPixels[index].SetColor(r, g, b);
    
    #ifdef DEBUG
    std::cout << "Pixel put into framebuffer at: (" << v.iX() << ", " << v.iY() << ")" << std::endl;
    #endif
  }

  void PutLine(float x0, float y0, float x1, float y1, CP color)
  {
    
    if(std::fabs(x1 - x0) > std::abs(y1 - y0))
    {
      //line is horizontal-ish
      //making sure x0 < x1
      if(x0 > x1)
      {
        float tmp = x0;
        x0 = x1;
        x1 = tmp;

        tmp = y0;
        y0 = y1;
        y1 = tmp;

      }

      std::vector<float> ys = Interpolate(x0, y0, x1, y1);

      for(int x = (int)x0; x < (int)x1; x++)
      {
        PutPixel(x, (int)ys[(int)(x - x0)], color);
      }
    }
    else
    {
      //line is vertical-ish
      //making sure y0 < y1
      if(y0 > y1)
      {
        float tmp = x0;
        x0 = x1;
        x1 = tmp;

        tmp = y0;
        y0 = y1;
        y1 = tmp;

      }

      std::vector<float> xs = Interpolate(y0, x0, y1, x1);

      for(int y = (int)y0; y < (int)y1; y++)
      {
        PutPixel((int)xs[(int)(y - y0)], (int)y, color);
      }
    }
    
    #ifdef DEBUG
    std::cout << "Rendered a line: (" << x0 << ", " << y0 << ") -> (" << x1 << ", " << y1 << ")"
      << std::endl;
    #endif
  }

  void PutLine(const Vec2& p0, const Vec2& p1, CP color)
  {
    PutLine(p0.X(), p0.Y(), p1.X(), p1.Y(), color); 
  }

  void PutLine(int x0, int y0, int x1, int y1, uint8_t r, uint8_t g, uint8_t b)
  {
       if(std::fabs(x1 - x0) > std::fabs(y1 - y0))
    {
      //line is horizontal-ish
      //making sure x0 < x1
      if(x0 > x1)
      {
        float tmp = x0;
        x0 = x1;
        x1 = tmp;

        tmp = y0;
        y0 = y1;
        y1 = tmp;
      }

      std::vector<float> ys = Interpolate(x0, y0, x1, y1);

      for(int x = (int)x0; x < (int)x1; x++)
      {
        PutPixel(x, (int)ys[(int)(x - x0)], r, g, b);
      }
    }
    else
    {
      //line is vertical-ish
      //making sure y0 < y1
      if(y0 > y1)
      {
       float tmp = x0;
        x0 = x1;
        x1 = tmp;

        tmp = y0;
        y0 = y1;
        y1 = tmp;
      }

      std::vector<float> xs = Interpolate(y0, x0, y1, x1);

      for(int y = (int)y0; y < (int)y1; y++)
      {
        PutPixel((int)xs[(int)(y - y0)], (int)y, r, g, b);
      }
    }

    #ifdef DEBUG
    std::cout << "Rendered a line: " << p0 << " -> " << p1 << std::endl;
    #endif
  }
 
void PutLine(const Vec2& p0, const Vec2& p1, uint8_t r, uint8_t g, uint8_t b)
  {
    PutLine(p0.X(), p0.Y(), p1.X(), p1.Y(), r, g, b);
  }

  void PutWireframeTriangle(float x0, float y0, float x1, float y1, float x2, float y2, CP color)
  {
    PutLine(x0, y0, x1, y1, color);
    PutLine(x1, y1, x2, y2, color);
    PutLine(x0, y0, x2, y2, color);

    #ifdef DEBUG
    std::cout << "Rendered a wireframe-triangle: " << Vec2(x0, y0) << ", " << Vec2(x1, y1) <<
    ", " << Vec2(x2, y2) << std::endl;
    #endif
  }
 
  void PutWireframeTriangle(const Vec2& p0, const Vec2& p1, const Vec2& p2, CP color)
  {
    PutWireframeTriangle(p0.X(), p0.Y(), p1.X(), p1.Y(), p2.X(), p2.Y(), color);
  }

  void PutWireframeTriangle(float x0, float y0, float x1, float y1, float x2, float y2, uint8_t r, uint8_t g, uint8_t b)
  {
    PutLine(x0, y0, x1, y1, r, g, b);
    PutLine(x1, y1, x2, y2, r, g, b);
    PutLine(x0, y0, x2, y2, r, g, b);
    
    #ifdef DEBUG
    std::cout << "Rendered a wireframe-triangle: " << Vec2(x0, y0) << ", " << Vec2(x1, y1) <<
    ", " << Vec2(x2, y2) << std::endl;
    #endif
  }
  
  void PutWireframeTriangle(const Vec2& p0, const Vec2& p1, const Vec2& p2, uint8_t r, uint8_t g, uint8_t b)
  {
    PutWireframeTriangle(p0.X(), p0.Y(), p1.X(), p1.Y(), p2.X(), p2.Y(), r, g, b);
  }

  void PutFilledTriangle(float x0, float y0, float x1, float y1, float x2, float y2, CP color)
  {
    if(y1 < y0)
    {
      float tmp = x0;
      x0 = x1;
      x1 = tmp;

      tmp = y0;
      y0 = y1;
      y1 = tmp;
    }

    if(y2 < y0)
    {
      float tmp = y0;
      y0 = y2;
      y2 = tmp;

      tmp = x0;
      x0 = x2;
      x2 = tmp;
    }

    if(y2 < y1)
    {
      float tmp = y1;
      y1 = y2;
      y2 = tmp;

      tmp = x1;
      x1 = x2;
      x2 = tmp;
    }

    std::vector<float> x01 = Interpolate(y0, x0, y1, x1);
    std::vector<float> x12 = Interpolate(y1, x1, y2, x2);
    std::vector<float> x02 = Interpolate(y0, x0, y2, x2);
    
    x01.pop_back();
    x01.insert(x01.end(), x12.begin(), x12.end());
    std::vector<float> x012 = x01;

    std::vector<float> x_left;
    std::vector<float> x_right;
    int m = std::floor(x012.size()/2);
    if(x02[m] < x012[m])
    {
      x_left = x02;
      x_right = x012;
    }
    else
    {
      x_left = x012;
      x_right = x02;
    }

    for(int y = (int)std::ceil(y0); y < (int)std::ceil(y2); y++)
    {
      for(int x = (int)x_left[y - y0]; x < (int)x_right[y - y0]; x++)
      {
        PutPixel(x, y, color);
      }
    }

    #ifdef DEBUG
    std::cout << "Rendered a filled-triangle: " << Vec2(x0, y0) << ", " << Vec2(x1, y1) <<
    ", " << Vec2(x2, y2) << std::endl;
    #endif
  }

  void PutFilledTriangle(const Vec2& p0, const Vec2& p1, const Vec2& p2, CP color)
  {
    PutFilledTriangle(p0.X(), p0.Y(), p1.X(), p1.Y(), p2.X(), p2.Y(), color);
  }

  void PutFilledTriangle(float x0, float y0, float x1, float y1, float x2, float y2, uint8_t r, uint8_t g, uint8_t b)
  {
    if(y1 < y0)
    {
      float tmp = x0;
      x0 = x1;
      x1 = tmp;

      tmp = y0;
      y0 = y1;
      y1 = tmp;
    }

    if(y2 < y0)
    {
      float tmp = y0;
      y0 = y2;
      y2 = tmp;

      tmp = x0;
      x0 = x2;
      x2 = tmp;
    }

    if(y2 < y1)
    {
      float tmp = y1;
      y1 = y2;
      y2 = tmp;

      tmp = x1;
      x1 = x2;
      x2 = tmp;
    }

    std::vector<float> x01 = Interpolate(y0, x0, y1, x1);
    std::vector<float> x12 = Interpolate(y1, x1, y2, x2);
    std::vector<float> x02 = Interpolate(y0, x0, y2, x2);
    
    x01.pop_back();
    x01.insert(x01.end(), x12.begin(), x12.end());
    std::vector<float> x012 = x01;

    std::vector<float> x_left;
    std::vector<float> x_right;
    int m = std::floor(x012.size()/2);
    if(x02[m] < x012[m])
    {
      x_left = x02;
      x_right = x012;
    }
    else
    {
      x_left = x012;
      x_right = x02;
    }

    for(int y = (int)std::ceil(y0); y < (int)std::ceil(y2); y++)
    {
      for(int x = (int)x_left[y - y0]; x < (int)x_right[y - y0]; x++)
      {
        PutPixel(x, y, r, g, b);
      }
    }
    
    #ifdef DEBUG
    std::cout << "Rendered a filled-triangle: " << Vec2(x0, y0) << ", " << Vec2(x1, y1) << ", "
    << Vec2(x2, y2) << std::endl;
    #endif
  }

  void PutFilledTriangle(const Vec2& p0, const Vec2& p1, const Vec2& p2, uint8_t r, uint8_t g, uint8_t b)
  {
    PutFilledTriangle(p0.X(), p0.Y(), p1.X(), p1.Y(), p2.X(), p2.Y(), r, g, b);
  }

  void BlitFramebuffer()
  {
    std::string name = "../frame_" + std::to_string(m_iBlitNum++) + ".ppm";
    std::ofstream file(name, std::ios::binary);

    if(!file) throw Invalid{};

    //PPM Header
    file << "P6\n";
    file << m_iWidth << " " << m_iHeight << "\n";
    file << "255\n";

    file.write(
      reinterpret_cast<const char*>(m_pPixels),
      m_iWidth * m_iHeight * sizeof(Color)
    );
    
    file.close();
    
    std::cout << "Framebuffer successfully blitted to: " << name << std::endl;
  }
  
private:
  
  int m_iWidth;
  int m_iHeight;
  
  Color* m_pPixels;

};

#endif

