#ifndef TINYRASTER_MATH_H
#define TINYRASTER_MATH_H
//--------------------------------------------------------------------
//  
//  Name: Math.h
//
//  Desc: Header only math library for TinyRaster. Includes vec2, vec3,
//  vec4 and mat4 classes and implementation.
//
//  Author: Aayush Bade 2025 (aayushbade14.github.io/Portfolio)
//
//--------------------------------------------------------------------
#include <cmath>
#include <iostream>

class Vec2
{
  
public:

  //constructors for the vec2 class
  Vec2() : m_fX(0.0f),
           m_fY(0.0f)
  {}

  Vec2(float x, float y) : m_fX(x),
                           m_fY(y)
  {}

  //destructor for the vec2 class
  ~Vec2()=default;

  //copy constructor and assignment for vec2 class
  Vec2(const Vec2& other) : m_fX(other.m_fX),
                            m_fY(other.m_fY)
  {}
  
  Vec2& operator=(const Vec2& other)
  {
    if(this == &other)
    {
      return *this;
    }

    m_fX = other.m_fX;
    m_fY = other.m_fY;

    return *this;
  }
  
  //move constructor and assignment operator not required as we are not allocating anything
  //on the heap memory.
  
  //getters and setters
  float X(){ return m_fX; }
  float Y(){ return m_fY; }

  void X(float x){ m_fX = x; }
  void Y(float y){ m_fY = y; }

  //arithmetic operations
  
  //addition operations
  Vec2 operator+(const Vec2& other){ return Vec2(m_fX + other.m_fX, m_fY + other.m_fY); }
  Vec2& operator+=(const Vec2& other){ m_fX += other.m_fX; m_fY += other.m_fY; return *this;}

  //subtraction operations
  Vec2 operator-(const Vec2& other){ return Vec2(m_fX - other.m_fX, m_fY - other.m_fY); }
  Vec2& operator-=(const Vec2& other){ m_fX -= other.m_fX; m_fY -= other.m_fY; return *this;}

  //scalar multiplications
  Vec2 operator*(float val){ return Vec2(m_fX * val, m_fY * val); }
  Vec2 operator*=(float val){ m_fX *= val; m_fY *= val; return *this;}

  //vector-vector multiplications
  Vec2 operator*(const Vec2& other){ return Vec2(m_fX * other.m_fX, m_fY * other.m_fY); }
  Vec2& operator*=(const Vec2& other){ m_fX *= other.m_fX; m_fY *= other.m_fY; return *this; }

  //scalar division operations
  Vec2 operator/(float val){ return Vec2(m_fX / val, m_fY / val); }
  Vec2& operator/=(float val){ m_fX /= val; m_fY /= val; return *this; }

  //vector-vector divisions
  Vec2 operator/(const Vec2& other){ return Vec2(m_fX / other.m_fX, m_fY / other.m_fY); }
  Vec2& operator/=(const Vec2& other){ m_fX /= other.m_fX; m_fY /= other.m_fY; return *this; }

  //dot-product method
  float Dot(const Vec2& other) { return ((m_fX * other.m_fX) + (m_fY * other.m_fY)); }
  
  //operator overloading for indexing vec2
  float operator[](int index)
  {
    switch(index)
    {
      case 0:
        return m_fX;
      case 1:
        return m_fY;
      default:
        throw Invalid{};
    }
    
  }
  
private:

  float m_fX;
  float m_fY;
};

//operator overloading for bi-directional operations
inline Vec2 operator*(float val, const Vec2& v) { return Vec2(v.X() * val, v.Y() * val); }

//method to get a normalized vec2
inline Vec2 Normalize(const Vec2& v)
{
  float mag = sqrt(pow(v.X(), 2) + pow(v.Y(), 2));
  return Vec2(v.X()/mag, v.Y()/mag);
}

//method to get squared-norm of vec2 : |V|^2 = <V,V>
inline float Norm2(const Vec2& v)
{
  return (pow(v.X(), 2) + pow(v.Y()));
}

//method to get norm of vec2 : |V| = '/<V,V>
inline float Norm(const Vec2& v)
{
  float norm2 = Norm2(v);
  return pow(norm2, 2);
}

#endif
