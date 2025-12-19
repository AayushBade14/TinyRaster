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
#include "./Color.h"

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
    std::cout << "Framebuffer init via default constructor!" << std::endl;
  }

  //default constructor with fbo size as parameters
  Framebuffer(int width, int height) : m_pPixels(nullptr),
                                       m_iWidth(width),
                                       m_iHeight(height)
  {
    //Allocate memory to framebuffer
    m_pPixels = new Color[m_iWidth * m_iHeight];

    std::cout << "Framebuffer init via default constructor: " << m_iWidth << " * "
      << m_iHeight << std::endl;
  }

  //destructor for framebuffer
  ~Framebuffer()
  {
    delete[] m_pPixels;

    std::cout << "Framebuffer cleaned via destructor!" << std::endl;
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

    std::cout << "Framebuffer init via copy constructor: " << m_iWidth << " * " 
      << m_iHeight << std::endl;
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
    
    std::cout << "Framebuffer init via copy assignment overload: " << m_iWidth << " * "
      << m_iHeight << std::endl;

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
  
    std::cout << "Framebuffer init via move constructor: " << m_iWidth << " * "
      << m_iHeight << std::endl;
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

    std::cout << "Framebuffer init via move operator overload: " << m_iWidth << " * "
      << m_iHeight << std::endl;

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
  
    std::cout << "Memory allocated to the framebuffer: " << m_iWidth << " * "
      << m_iHeight << std::endl;
  }
  
  //methods for clearing the framebuffer using a color preset or explicit rgb value
  void ClearFramebuffer(CP color)
  {
    int res = m_iWidth * m_iHeight;
    for(int i = 0; i < res; i++)
    {
      m_pPixels[i].SetColor(color);
    }
    
    std::cout << "Framebuffer cleared to color: " << GetColorName(color) << std::endl;
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

    std::cout << "Framebuffer cleared to color: RGB(" << r << ", " << g << ", " << b << ")"
      << std::endl;
  }
  
  void PutPixel(int x, int y, CP color)
  {
    if(x < 0 || x >= m_iWidth || y < 0 || y >= m_iHeight) return;

    int index = y * m_iWidth + x;
    m_pPixels[index].SetColor(color);

    std::cout << "Pixel put into framebuffer at: (" << x << ", " << y << ")" << std::endl;
  }

  void PutPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b)
  {
    if(x < 0 || x >= m_iWidth || y < 0 || y >= m_iHeight) return;

    int index = y * m_iWidth + x;
    m_pPixels[index].SetColor(r, g, b);

    std::cout << "Pixel put into framebuffer at: (" << x << ", " << y << ")" << std::endl;
  }
  
  void PutLine(int x0, int y0, int x1, int y1, CP color)
  {
    int dx = x1 - x0;
    int dy = y1 - y0;

    if(abs(dx) > abs(dy))
    {
      float a = (float)dy/(float)dx;

      if(x0 > x1)
      {
        x0 ^= x1;
        x1 ^= x0;
        x0 ^= x1;
        y0 ^= y1;
        y1 ^= y0;
        y0 ^= y1;
      }

      float y = y0;
      for(int x = x0; x < x1; x++)
      {
        PutPixel(x, (int)y, color);
        y = y + a;
      }
    } 
    else
    {
      float a = (float)dx/(float)dy;

      if(y0 > y1)
      {
        //swap
        x0 ^= x1;
        x1 ^= x0;
        x0 ^= x1;
        y0 ^= y1;
        y1 ^= y0;
        y0 ^= y1;
      }

      float x = x0;
      for(int y = y0; y < y1; y++)
      {
        PutPixel((int)x, y, color);
        x = x + a;
      }
    }

    std::cout << "Rendered a line: (" << x0 << ", " << y0 << ") -> (" << x1 << ", " << y1 << ")"
      << std::endl;
  }

  void PutLine(int x0, int y0, int x1, int y1, uint8_t r, uint8_t g, uint8_t b)
  {
    
    int dx = x1 - x0;
    int dy = y1 - y0;

    if(abs(dx) > abs(dy))
    {
      float a = (float)dy/(float)dx;

      if(x0 > x1)
      {
        //swap
        x0 ^= x1;
        x1 ^= x0;
        x0 ^= x1;
        y0 ^= y1;
        y1 ^= y0;
        y0 ^= y1;
      }

      float y = y0;
      for(int x = x0; x < x1; x++)
      {
        PutPixel(x, (int)y, r, g, b);
        y = y + a;
      }
    } 
    else
    {
      float a = (float)dx/(float)dy;

      if(y0 > y1)
      {
        x0 ^= x1;
        x1 ^= x0;
        x0 ^= x1;
        y0 ^= y1;
        y1 ^= y0;
        y0 ^= y1;
      }

      float x = x0;
      for(int y = y0; y < y1; y++)
      {
        PutPixel((int)x, y, r, g, b);
        x = x + a;
      }
    }

    std::cout << "Rendered a line: (" << x0 << ", " << y0 << ") -> (" << x1 << ", " << y1 << ")"
      << std::endl;
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

