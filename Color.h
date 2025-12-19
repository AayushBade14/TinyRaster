#ifndef COLOR_H
#define COLOR_H
//----------------------------------------------------------
//  
//  Name: Color.h
//
//  Desc: Defines 24-bit color data-structure (rgb)
//
//  Author: Aayush Bade 2025 (aayushbade14.github.io/Portfolio)
//
//----------------------------------------------------------

#include <string>
#include <cstdint>

#define IS_VALID(x) (x <= 255)

#define COLOR_MAX 255
#define COLOR_MIN 0

// CP - color presets
enum class CP
{
  RED,
  BLUE,
  GREEN,
  YELLOW,
  WHITE,
  BLACK,
  ORANGE
};

inline std::string GetColorName(CP color)
{
  switch(color)
  {
    case CP::RED:
      return "RED";
    case CP::BLUE:
      return "BLUE";
    case CP::GREEN:
      return "GREEN";
    case CP::YELLOW:
      return "YELLOW";
    case CP::WHITE:
      return "WHITE";
    case CP::BLACK:
      return "BLACK";
    case CP::ORANGE:
      return "ORANGE";

    default:
      return "UNKNOWN!";
  }
}

struct Color
{
  uint8_t r;
  uint8_t g;
  uint8_t b;
  
  class Invalid{};

  //default constructor for color
  Color() : r(0),
            g(0),
            b(0)
  {}

  //default constructor with color paramaters
  Color(uint8_t rr, uint8_t gg, uint8_t bb) : r(rr),
                                  g(gg),
                                  b(bb)
  {
    if(!IS_VALID(r) || !IS_VALID(g) || !IS_VALID(b))
    {
      throw Invalid{};
    }
  }

  //destructor
  ~Color()=default;

  //copy constructor and copy assignment for color
  Color(const Color& other) : r(other.r),
                              g(other.g),
                              b(other.b)
  {}

  Color& operator=(const Color& other)
  {

    if(this == &other) return *this;

    r = other.r;
    g = other.g;
    b = other.b;
    
    return *this;
  }

  //move constructor and move assignment
  Color(Color&& other) : r(other.r),
                         g(other.g),
                         b(other.b)
  {
    other.r = 0;
    other.g = 0;
    other.b = 0;
  }

  Color& operator=(Color&& other)
  {

    if(this == &other) return *this;
    
    r = other.r;
    g = other.g;
    b = other.b;

    other.r = 0;
    other.g = 0;
    other.b = 0;

    return *this;
  }

  //operator overload for indexing rgb values
  uint8_t& operator[](int index)
  {
    switch (index) {
      case 0:
        return r;
      case 1:
        return g;
      case 2:
        return b;

      default:
        throw Invalid{};
        break;
    }
  }

  //method for setting a color
  void SetColor(CP color)
  {
    switch (color) {
      
      case CP::RED:
        r = 255;
        g = 0;
        b = 0;
        break;
      
      case CP::BLUE:
        r = 0;
        g = 0;
        b = 255;
        break;
      
      case CP::GREEN:
        r = 0;
        g = 255;
        b = 0;
        break;
      
      case CP::YELLOW:
        r = 255;
        g = 255;
        b = 0;
        break;
      
      case CP::WHITE:
        r = 255;
        g = 255;
        b = 255;
        break;
      
      case CP::BLACK:
        r = 0;
        g = 0;
        b = 0;
        break;
      
      case CP::ORANGE:
        r = 255;
        g = 125;
        b = 0;
        break;

      default:
        r = 0;
        g = 0;
        b = 0;
        break;
    }
  }

  void SetColor(uint8_t r, uint8_t g, uint8_t b)
  {
    if(!IS_VALID(r) || !IS_VALID(g) || !IS_VALID(b))
    {
      throw Invalid{};
    }
    
    this->r = r;
    this->g = g;
    this->b = b;
  }

};

#endif
