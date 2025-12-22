#ifndef TINYRASTER_VERTEX_H
#define TINYRASTER_VERTEX_H
//----------------------------------------------------------------------
//  
//  Name: Vertex.h
//
//  Desc: Vertex class for storing vertex data for rasterizing geometry
//  and passing other attributes to the vertex
//
//  Author: Aayush Bade 2025 (aayushbade14.github.io/Portfolio)
//
//----------------------------------------------------------------------

#include "./Math.h"

struct Vertex
{
  Vec3 m_Position;
  Vec3 m_Color;
  Vec3 m_Normal;
  Vec2 m_TextureCoords;
};

#endif
