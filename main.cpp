#include "./Framebuffer.h"
#include <cstdlib>
#include <ctime>

const float N = 0.1f;
const float F = 1024.0f;

const float N_X = 1024.0f;
const float N_Y = 1024.0f;

const float CS = 500.0f;

const float PI = 3.141;
const float THETA = PI/12.0f;

int main(void)
{
  std::srand(std::time(nullptr));
 
  try
  {
    float fov = 45.0f * PI / 180.0f;
    float L = -tan(fov/2.0f)*N;
    float R = -L;
    float B = -tan(fov/2.0f)*N;
    float T = -B;

    Mat4 M_vp;
    M_vp.m_Mat[0][0] = N_X/2.0f;
    M_vp.m_Mat[1][1] = N_Y/2.0f;
    M_vp.m_Mat[0][3] = (N_X - 1)/2.0f;
    M_vp.m_Mat[1][3] = (N_Y - 1)/2.0f;
    
    Mat4 M_perspective;
    M_perspective.m_Mat[2][2] = -(F + N)/(F - N);
    M_perspective.m_Mat[2][3] = -(2.0f * F * N)/(F - N);
    M_perspective.m_Mat[3][2] = -1.0f;
    M_perspective.m_Mat[0][0] = N;
    M_perspective.m_Mat[1][1] = N;


    Mat4 M_ortho;
    M_ortho.m_Mat[0][0] = 2.0f/(R - L);
    M_ortho.m_Mat[1][1] = 2.0f/(T - B);
    M_ortho.m_Mat[2][2] = 2.0f/(F - N);
    M_ortho.m_Mat[0][3] = -(R + L)/(R - L);
    M_ortho.m_Mat[1][3] = -(T + B)/(T - B);
    M_ortho.m_Mat[2][3] = -(F + N)/(F - N);

    Mat4 M_proj = M_vp * M_ortho * M_perspective;
   
    for(int f = 0; f < 360; f++){
      Mat4 M_model_r;
      M_model_r.m_Mat[0][0] = cos(PI/60.0f*(float)f);
      M_model_r.m_Mat[0][2] = sin(PI/60.0f*(float)f);
      M_model_r.m_Mat[2][0] = -sin(PI/60.0f*(float)f);
      M_model_r.m_Mat[2][2] = cos(PI/60.0f*(float)f);
    
      float theta = PI/60.0f * (float)f;
      float invLen = 1.0f / sqrt(3.0f);
      float x = invLen;
      float y = invLen;
      float z = invLen;

      float c = cos(theta);
      float s = sin(theta);
      float t = 1.0f - c;
      
      Mat4 R1;
      R1.m_Mat[0][0] = t*x*x + c;
      R1.m_Mat[0][1] = t*x*y - s*z;
      R1.m_Mat[0][2] = t*x*z + s*y;

      R1.m_Mat[1][0] = t*x*y + s*z;
      R1.m_Mat[1][1] = t*y*y + c;
      R1.m_Mat[1][2] = t*y*z - s*x;

      R1.m_Mat[2][0] = t*x*z - s*y;
      R1.m_Mat[2][1] = t*y*z + s*x;
      R1.m_Mat[2][2] = t*z*z + c;

      Vec3 Pos(N_X/2.0f, N_Y/2.0f, -N_X/2.0f);
      
      Mat4 M_model_it;
      M_model_it.m_Mat[0][3] = -Pos.X();
      M_model_it.m_Mat[1][3] = -Pos.Y();
      M_model_it.m_Mat[2][3] = -Pos.Z();

      Mat4 M_model_t;
      M_model_t.m_Mat[0][3] = Pos.X();
      M_model_t.m_Mat[1][3] = Pos.Y();
      M_model_t.m_Mat[2][3] = Pos.Z();
  
      float radius = 1000.0f;
      float z1 = radius * cos((float)f * 0.02f) + radius + 500.0f;
      float y1 = 0.0f;
      float x1 = 0.0f;

      Vec3 campos(x1, y1, z1);
      Vec3 gaze = campos * -1.0f;

      Vec3 w = Normalize(gaze);
      Vec3 top = fabs(w.Y()) > 0.99f ? Vec3(1.0f, 0.0f, 0.0f) : Vec3(0.0f, 1.0f, 0.0f);

      Vec3 u = Normalize(top.Cross(w));
      Vec3 v = Normalize(w.Cross(u));
      
      Mat4 M_view;
      M_view.m_Mat[0][0] = u.X();
      M_view.m_Mat[1][0] = v.X();
      M_view.m_Mat[2][0] = w.X();
      
      M_view.m_Mat[0][1] = u.Y();
      M_view.m_Mat[1][1] = v.Y();
      M_view.m_Mat[2][1] = w.Y();

      M_view.m_Mat[0][2] = u.Z();
      M_view.m_Mat[1][2] = v.Z();
      M_view.m_Mat[2][2] = w.Z();

      M_view.m_Mat[0][3] = -u.Dot(campos);
      M_view.m_Mat[1][3] = -v.Dot(campos);
      M_view.m_Mat[2][3] = -w.Dot(campos);

      Mat4 M_model = R1;
      
      Mat4 M_transform = M_proj * M_view * M_model;

      std::vector<Vec4> vertices = {
        {-CS/2.0f, -CS/2.0f, -CS/2.0f, 1.0f},
        {CS/2.0f, -CS/2.0f, -CS/2.0f, 1.0f},
        {CS/2.0f, CS/2.0f, -CS/2.0f, 1.0f},
        {-CS/2.0f, CS/2.0f, -CS/2.0f, 1.0f},

        {-CS/2.0f, -CS/2.0f, CS/2.0f, 1.0f},
        {CS/2.0f, -CS/2.0f, CS/2.0f, 1.0f},
        {CS/2.0f, CS/2.0f, CS/2.0f, 1.0f},
        {-CS/2.0f, CS/2.0f, CS/2.0f, 1.0f}
      };
  
      for(int i = 0; i < 8; i++)
      {
        Vec4 clip = M_view * M_model * vertices[i];
        clip = M_perspective * clip;

        clip /= clip.W();
        
        vertices[i] = M_vp * M_ortho * clip;
      } 

      Framebuffer fbo(N_X, N_Y);
      fbo.ClearFramebuffer(CP::BLACK);
    
      //back
      fbo.PutWireframeTriangle(vertices[0].X(), vertices[0].Y(), vertices[1].X(), vertices[1].Y(), vertices[2].X(), vertices[2].Y(), CP::ORANGE);
      fbo.PutWireframeTriangle(vertices[0].X(), vertices[0].Y(), vertices[2].X(), vertices[2].Y(), vertices[3].X(), vertices[3].Y(), CP::ORANGE);
      //bottom
      fbo.PutWireframeTriangle(vertices[0].X(), vertices[0].Y(), vertices[4].X(), vertices[4].Y(), vertices[5].X(), vertices[5].Y(), CP::BLUE);
      fbo.PutWireframeTriangle(vertices[0].X(), vertices[0].Y(), vertices[5].X(), vertices[5].Y(), vertices[1].X(), vertices[1].Y(), CP::BLUE);
      //right
      fbo.PutWireframeTriangle(vertices[1].X(), vertices[1].Y(), vertices[5].X(), vertices[5].Y(), vertices[6].X(), vertices[6].Y(), CP::GREEN);
      fbo.PutWireframeTriangle(vertices[1].X(), vertices[1].Y(), vertices[6].X(), vertices[6].Y(), vertices[2].X(), vertices[2].Y(), CP::GREEN);
      //left
      fbo.PutWireframeTriangle(vertices[0].X(), vertices[0].Y(), vertices[4].X(), vertices[4].Y(), vertices[7].X(), vertices[7].Y(), CP::YELLOW);
      fbo.PutWireframeTriangle(vertices[0].X(), vertices[0].Y(), vertices[7].X(), vertices[7].Y(), vertices[3].X(), vertices[3].Y(), CP::YELLOW);
      //front
      fbo.PutWireframeTriangle(vertices[4].X(), vertices[4].Y(), vertices[5].X(), vertices[5].Y(), vertices[6].X(), vertices[6].Y(), CP::RED);
      fbo.PutWireframeTriangle(vertices[4].X(), vertices[4].Y(), vertices[6].X(), vertices[6].Y(), vertices[7].X(), vertices[7].Y(), CP::RED);
      //top
      fbo.PutWireframeTriangle(vertices[3].X(), vertices[3].Y(), vertices[7].X(), vertices[7].Y(), vertices[6].X(), vertices[6].Y(), CP::WHITE);
      fbo.PutWireframeTriangle(vertices[3].X(), vertices[3].Y(), vertices[6].X(), vertices[6].Y(), vertices[2].X(), vertices[2].Y(), CP::WHITE);

      fbo.BlitFramebuffer();
    }
  }
  catch(Color::Invalid)
  {
    std::cerr << "Error: Color::Invalid" << std::endl;
    exit(1);
  }

  return 0;
}

