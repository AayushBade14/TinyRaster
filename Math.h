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
#include <vector>

class Vec2
{
  
public:
  //empty invalid class for error handling 
  class Invalid{};

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
  float X()const{ return m_fX; }
  float Y()const{ return m_fY; }
  
  //getters for returning truncated x and y values
  int iX()const{return (int)m_fX; }
  int iY()const{return (int)m_fY; }

  void X(float x){ m_fX = x; }
  void Y(float y){ m_fY = y; }

  //arithmetic operations
  
  //addition operations
  Vec2 operator+(const Vec2& other)const{ return Vec2(m_fX + other.m_fX, m_fY + other.m_fY); }
  Vec2& operator+=(const Vec2& other){ m_fX += other.m_fX; m_fY += other.m_fY; return *this;}

  //subtraction operations
  Vec2 operator-(const Vec2& other)const{ return Vec2(m_fX - other.m_fX, m_fY - other.m_fY); }
  Vec2& operator-=(const Vec2& other){ m_fX -= other.m_fX; m_fY -= other.m_fY; return *this;}

  //scalar multiplications
  Vec2 operator*(float val)const{ return Vec2(m_fX * val, m_fY * val); }
  Vec2 operator*=(float val){ m_fX *= val; m_fY *= val; return *this;}

  //vector-vector multiplications
  Vec2 operator*(const Vec2& other)const{ return Vec2(m_fX * other.m_fX, m_fY * other.m_fY); }
  Vec2& operator*=(const Vec2& other){ m_fX *= other.m_fX; m_fY *= other.m_fY; return *this; }

  //scalar division operations
  Vec2 operator/(float val)const{ return Vec2(m_fX / val, m_fY / val); }
  Vec2& operator/=(float val){ m_fX /= val; m_fY /= val; return *this; }

  //vector-vector divisions
  Vec2 operator/(const Vec2& other)const{ return Vec2(m_fX / other.m_fX, m_fY / other.m_fY); }
  Vec2& operator/=(const Vec2& other){ m_fX /= other.m_fX; m_fY /= other.m_fY; return *this; }

  //dot-product method
  float Dot(const Vec2& other)const { return ((m_fX * other.m_fX) + (m_fY * other.m_fY)); }
  
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
  return (pow(v.X(), 2) + pow(v.Y(), 2));
}

//method to get norm of vec2 : |V| = '/<V,V>
inline float Norm(const Vec2& v)
{
  float norm2 = Norm2(v);
  return pow(norm2, 2);
}

//method for swapping two vec2's
inline void Swap(Vec2& v1, Vec2& v2)
{
  float tmp = v1.X();
  v1.X(v2.X());
  v2.X(tmp);

  tmp = v1.Y();
  v1.Y(v2.Y());
  v2.Y(tmp);
}

//method for printing vec2 for debugging
inline std::ostream& operator<<(std::ostream& os, const Vec2& v)
{
  os << "(" << v.X() << ", " << v.Y() << ")";
  return os;
}

//---------------------------------Interpolation methods-------------------------------------

inline std::vector<float> Interpolate(float i0, float d0, float i1, float d1)
{
  float epsilon = 0.0001f;

  if(abs(i0 - i1) <= epsilon)
  {
    return {d0};
  }
    
  std::vector<float> values;

  float a = (d1 - d0)/(i1 - i0);

  float d = d0;

  for(int i = (int)i0; i <= (int)i1; i++)
  {
    values.push_back(d);
    d = d + a;
  }

  return values;
}

inline std::vector<float> Interpolate(const Vec2& v1, const Vec2& v2)
{
  return Interpolate(v1.X(), v1.Y(), v2.X(), v2.Y());
}

inline std::vector<float> Interpolate_(const Vec2& v1, const Vec2& v2)
{
  return Interpolate(v1.Y(), v1.X(), v2.Y(), v2.X());
}

#endif
