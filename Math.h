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


class Vec3
{
  
public:
  //empty invalid class for error handling 
  class Invalid{};

  //constructors for the vec3 class
  Vec3() : m_fX(0.0f),
           m_fY(0.0f),
           m_fZ(0.0f)
  {}

  Vec3(float x, float y, float z) : m_fX(x),
                           m_fY(y),
                           m_fZ(z)
  {}

  //destructor for the vec3 class
  ~Vec3()=default;

  //copy constructor and assignment for vec3 class
  Vec3(const Vec3& other) : m_fX(other.m_fX),
                            m_fY(other.m_fY),
                            m_fZ(other.m_fZ)
  {}
  
  Vec3& operator=(const Vec3& other)
  {
    if(this == &other)
    {
      return *this;
    }

    m_fX = other.m_fX;
    m_fY = other.m_fY;
    m_fZ = other.m_fZ;

    return *this;
  }
  
  //move constructor and assignment operator not required as we are not allocating anything
  //on the heap memory.
  
  //getters and setters
  float X()const{ return m_fX; }
  float Y()const{ return m_fY; }
  float Z()const{ return m_fZ; }
  
  Vec2 XY()const{ return Vec2(m_fX, m_fY); }
  Vec2 YX()const{ return Vec2(m_fY, m_fX); }
  Vec2 YZ()const{ return Vec2(m_fY, m_fZ); }
  Vec2 ZY()const{ return Vec2(m_fZ, m_fY); }
  Vec2 XZ()const{ return Vec2(m_fX, m_fZ); }
  Vec2 ZX()const{ return Vec2(m_fZ, m_fX); }

  //getters for returning truncated x, y and z values
  int iX()const{ return (int)m_fX; }
  int iY()const{ return (int)m_fY; }
  int iZ()const{ return (int)m_fZ; }

  void X(float x){ m_fX = x; }
  void Y(float y){ m_fY = y; }
  void Z(float z){ m_fZ = z; }

  //arithmetic operations
  
  //addition operations
  Vec3 operator+(const Vec3& other)const{ return Vec3(m_fX + other.m_fX, m_fY + other.m_fY, m_fZ + other.m_fZ); }
  Vec3& operator+=(const Vec3& other){ m_fX += other.m_fX; m_fY += other.m_fY; m_fZ += other.m_fZ; return *this;}

  //subtraction operations
  Vec3 operator-(const Vec3& other)const{ return Vec3(m_fX - other.m_fX, m_fY - other.m_fY, m_fZ - other.m_fZ); }
  Vec3& operator-=(const Vec3& other){ m_fX -= other.m_fX; m_fY -= other.m_fY; m_fZ -= other.m_fZ; return *this;}
  
  //scalar multiplications
  Vec3 operator*(float val)const{ return Vec3(m_fX * val, m_fY * val, m_fZ * val); }
  Vec3 operator*=(float val){ m_fX *= val; m_fY *= val; m_fZ *= val; return *this;}

  //vector-vector multiplications
  Vec3 operator*(const Vec3& other)const{ return Vec3(m_fX * other.m_fX, m_fY * other.m_fY, m_fZ * other.m_fZ); }
  Vec3& operator*=(const Vec3& other){ m_fX *= other.m_fX; m_fY *= other.m_fY; m_fZ *= other.m_fZ; return *this; }

  //scalar division operations
  Vec3 operator/(float val)const{ return Vec3(m_fX / val, m_fY / val, m_fZ / val); }
  Vec3& operator/=(float val){ m_fX /= val; m_fY /= val; m_fZ /= val; return *this; }

  //vector-vector divisions
  Vec3 operator/(const Vec3& other)const{ return Vec3(m_fX / other.m_fX, m_fY / other.m_fY, m_fZ / other.m_fZ); }
  Vec3& operator/=(const Vec3& other){ m_fX /= other.m_fX; m_fY /= other.m_fY; m_fZ /= other.m_fZ; return *this; }

  //dot-product method
  float Dot(const Vec3& other)const { return ((m_fX * other.m_fX) + (m_fY * other.m_fY) + (m_fZ * other.m_fZ)); }
  
  //cross-product method
  Vec3 Cross(const Vec3& other)const { return Vec3(((m_fY * other.m_fZ) - (m_fZ * other.m_fY)), ((m_fZ * other.m_fX) - (m_fX * other.m_fZ)), ((m_fX * other.m_fY) - (m_fY * other.m_fX))); }
  //operator overloading for indexing vec2
  float operator[](int index)
  {
    switch(index)
    {
      case 0:
        return m_fX;
      case 1:
        return m_fY;
      case 2:
        return m_fZ;
      default:
        throw Invalid{};
    }
    
  }

  
private:

  float m_fX;
  float m_fY;
  float m_fZ;
};

class Vec4{
  
public:
  //empty invalid class for error handling 
  class Invalid{};

  //constructors for the vec3 class
  Vec4() : m_fX(0.0f),
           m_fY(0.0f),
           m_fZ(0.0f),
           m_fW(1.0f)
  {}

  Vec4(float x, float y, float z, float w) : m_fX(x),
                           m_fY(y),
                           m_fZ(z),
                           m_fW(w)
  {}
  
  Vec4(const Vec3& v, float w) : m_fX(v.X()),
                                 m_fY(v.Y()),
                                 m_fZ(v.Z()),
                                 m_fW(w)
  {}

  //destructor for the vec3 class
  ~Vec4()=default;

  //copy constructor and assignment for vec3 class
  Vec4(const Vec4& other) : m_fX(other.m_fX),
                            m_fY(other.m_fY),
                            m_fZ(other.m_fZ),
                            m_fW(other.m_fW)
  {}
  
  Vec4& operator=(const Vec4& other)
  {
    if(this == &other)
    {
      return *this;
    }

    m_fX = other.m_fX;
    m_fY = other.m_fY;
    m_fZ = other.m_fZ;
    m_fW = other.m_fW;

    return *this;
  }
  
  //move constructor and assignment operator not required as we are not allocating anything
  //on the heap memory.
  
  //getters and setters
  float X()const{ return m_fX; }
  float Y()const{ return m_fY; }
  float Z()const{ return m_fZ; }
  float W()const{ return m_fW; }
  
  Vec2 XY()const{ return Vec2(m_fX, m_fY); }
  Vec2 YX()const{ return Vec2(m_fY, m_fX); }
  Vec2 YZ()const{ return Vec2(m_fY, m_fZ); }
  Vec2 ZY()const{ return Vec2(m_fZ, m_fY); }
  Vec2 XZ()const{ return Vec2(m_fX, m_fZ); }
  Vec2 ZX()const{ return Vec2(m_fZ, m_fX); }
  Vec2 XW()const{ return Vec2(m_fX, m_fW); }
  Vec2 WX()const{ return Vec2(m_fW, m_fX); }
  Vec2 YW()const{ return Vec2(m_fY, m_fW); }
  Vec2 WY()const{ return Vec2(m_fW, m_fY); }
  Vec2 ZW()const{ return Vec2(m_fZ, m_fW); }
  Vec2 WZ()const{ return Vec2(m_fW, m_fZ); }

  Vec3 XYZ()const{ return Vec3(m_fX, m_fY, m_fZ); }
  Vec3 XZY()const{ return Vec3(m_fX, m_fZ, m_fY); }
  Vec3 YXZ()const{ return Vec3(m_fY, m_fX, m_fZ); }
  Vec3 YZX()const{ return Vec3(m_fY, m_fZ, m_fX); }
  Vec3 ZXY()const{ return Vec3(m_fZ, m_fX, m_fY); }
  Vec3 ZYX()const{ return Vec3(m_fZ, m_fY, m_fX); }
  
  //getters for returning truncated x, y and z values
  int iX()const{ return (int)m_fX; }
  int iY()const{ return (int)m_fY; }
  int iZ()const{ return (int)m_fZ; }
  int iW()const{ return (int)m_fW; }

  void X(float x){ m_fX = x; }
  void Y(float y){ m_fY = y; }
  void Z(float z){ m_fZ = z; }
  void W(float w){ m_fW = w; }

  //arithmetic operations
  
  //addition operations
  Vec4 operator+(const Vec4& other)const{ return Vec4(m_fX + other.m_fX, m_fY + other.m_fY, m_fZ + other.m_fZ, m_fW + other.m_fW); }
  Vec4& operator+=(const Vec4& other){ m_fX += other.m_fX; m_fY += other.m_fY; m_fZ += other.m_fZ; m_fW += other.m_fW; return *this;}

  //subtraction operations
  Vec4 operator-(const Vec4& other)const{ return Vec4(m_fX - other.m_fX, m_fY - other.m_fY, m_fZ - other.m_fZ, m_fW - other.m_fW); }
  Vec4& operator-=(const Vec4& other){ m_fX -= other.m_fX; m_fY -= other.m_fY; m_fZ -= other.m_fZ; m_fW -= other.m_fW; return *this;}
  
  //scalar multiplications
  Vec4 operator*(float val)const{ return Vec4(m_fX * val, m_fY * val, m_fZ * val, m_fW * val); }
  Vec4 operator*=(float val){ m_fX *= val; m_fY *= val; m_fZ *= val; m_fW *= val; return *this;}

  //vector-vector multiplications
  Vec4 operator*(const Vec4& other)const{ return Vec4(m_fX * other.m_fX, m_fY * other.m_fY, m_fZ * other.m_fZ, m_fW * other.m_fW); }
  Vec4& operator*=(const Vec4& other){ m_fX *= other.m_fX; m_fY *= other.m_fY; m_fZ *= other.m_fZ; m_fW *= other.m_fW; return *this; }

  //scalar division operations
  Vec4 operator/(float val)const{ return Vec4(m_fX / val, m_fY / val, m_fZ / val, m_fW / val); }
  Vec4& operator/=(float val){ m_fX /= val; m_fY /= val; m_fZ /= val; m_fW /= val; return *this; }

  //vector-vector divisions
  Vec4 operator/(const Vec4& other)const{ return Vec4(m_fX / other.m_fX, m_fY / other.m_fY, m_fZ / other.m_fZ, m_fW / other.m_fW); }
  Vec4& operator/=(const Vec4& other){ m_fX /= other.m_fX; m_fY /= other.m_fY; m_fZ /= other.m_fZ; m_fW /= other.m_fW; return *this; }

  //dot-product method
  float Dot(const Vec4& other)const { return ((m_fX * other.m_fX) + (m_fY * other.m_fY) + (m_fZ * other.m_fZ) + (m_fW * other.m_fW)); }
  
  //operator overloading for indexing vec2
  float operator[](int index)
  {
    switch(index)
    {
      case 0:
        return m_fX;
      case 1:
        return m_fY;
      case 2:
        return m_fZ;
      case 3:
        return m_fW;
      default:
        throw Invalid{};
    }
    
  }

  
private:

  float m_fX;
  float m_fY;
  float m_fZ;
  float m_fW;
};

class Mat4
{

public:
  
  class Invalid{};

  float m_Mat[4][4];
  
  Mat4()
  {
    for(int i = 0; i < 4; i++)
    {
      for(int j = 0; j < 4; j++)
      {
        if(i == j) m_Mat[i][j] = 1.0f;
        else m_Mat[i][j] = 0.0f;
      }
    }
  }
 
  Mat4(float t)
  {
    for(int i = 0; i < 4; i++)
    {
      for(int j = 0; j < 4; j++)
      {
        if(i == j) m_Mat[i][j] = t;
        else m_Mat[i][j] = 0.0f;
      }
    }
  }

  ~Mat4() = default;
  
  //copy constructor and copy assignment
  Mat4(const Mat4& other)
  {
    for(int i = 0; i < 4; i++)
    {
      for(int j = 0; j < 4; j++)
      {
        m_Mat[i][j] = other.m_Mat[i][j];
      }
    }
  }
  
  Mat4 operator=(const Mat4& other)
  {
    if(this == &other) return *this;

    for(int i = 0; i < 4; i++)
    {
      for(int j = 0; j < 4; j++)
      {
        m_Mat[i][j] = other.m_Mat[i][j];
      }
    }

    return *this;
  }

  Vec4 GetRow(int index)
  {
    if(index > 3) throw Invalid{};

    return Vec4(m_Mat[index][0], m_Mat[index][1], m_Mat[index][2], m_Mat[index][3]);
  }
  
  Vec4 GetColumn(int index)
  {
    if(index > 3) throw Invalid{};

    return Vec4(m_Mat[0][index], m_Mat[1][index], m_Mat[2][index], m_Mat[3][index]);
  }
  
  Vec4 operator*(const Vec4& other)
  {
    return Vec4(GetRow(0).Dot(other), GetRow(1).Dot(other), GetRow(2).Dot(other), GetRow(3).Dot(other));
  }
  
  Mat4 operator*(Mat4& other)
  {
    Mat4 result(0.0f); // initialize all to 0

    for(int i = 0; i < 4; i++)
    {
      for(int j = 0; j < 4; j++)
      {
        result.m_Mat[i][j] =
        GetRow(i).Dot(other.GetColumn(j));
      }
    }

    return result;
  }
  
  static Mat4 Identity()
  {
    Mat4 r = {};
    
    r.m_Mat[0][0] = 1.0f;
    r.m_Mat[1][1] = 1.0f;
    r.m_Mat[2][2] = 1.0f;
    r.m_Mat[3][3] = 1.0f;
    
    return r;
  }  
};

//--------------------------------------vec2 methods------------------------------------------

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

//----------------------------------methods for vec3--------------------------------------------

//operator overloading for bi-directional operations
inline Vec3 operator*(float val, const Vec3& v) { return Vec3(v.X() * val, v.Y() * val, v.Z() * val); }

//method to get a normalized vec3
inline Vec3 Normalize(const Vec3& v)
{
  float mag = sqrt(pow(v.X(), 2) + pow(v.Y(), 2) + pow(v.Z(), 2));
  return Vec3(v.X()/mag, v.Y()/mag, v.Z()/mag);
}

//method to get squared-norm of vec3 : |V|^2 = <V,V>
inline float Norm2(const Vec3& v)
{
  return (pow(v.X(), 2) + pow(v.Y(), 2) + pow(v.Z(), 2));
}

//method to get norm of vec3 : |V| = '/<V,V>
inline float Norm(const Vec3& v)
{
  float norm2 = Norm2(v);
  return pow(norm2, 2);
}

//method for swapping two vec3's
inline void Swap(Vec3& v1, Vec3& v2)
{
  float tmp = v1.X();
  v1.X(v2.X());
  v2.X(tmp);

  tmp = v1.Y();
  v1.Y(v2.Y());
  v2.Y(tmp);

  tmp = v1.Z();
  v1.Z(v2.Z());
  v2.Z(tmp);
}

//method for printing vec3 for debugging
inline std::ostream& operator<<(std::ostream& os, const Vec3& v)
{
  os << "(" << v.X() << ", " << v.Y() << ", " << v.Z() << ")";
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

inline Vec3 Lerp(const Vec3& a, const Vec3& b, float t)
{
  return a + (b - a) * t;
}

inline std::vector<Vec3> InterpolateVec3(float y0, const Vec3& c0, float y1, const Vec3& c1)
{
  std::vector<Vec3> result;

  int dy = (int)std::ceil(y1) - (int)std::ceil(y0);
  if(dy <= 0) return result;

  for(int i = 0; i <= dy; i++)
  {
    float t = (float)i / (float)dy;
    result.push_back(Lerp(c0, c1, t));
  }

  return result;
}

#endif
