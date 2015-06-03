#include <array>

class Rasterizer {
    
public:
  Rasterizer();
  ~Rasterizer();
  
  /// Initialze the rasterizer
  bool Init();
  
  /// Start the rasterization
  bool Rasterize();
  
private:
  void CompileShaders();
  
  void CheckCompilation(GLuint shaderSource);
  
  void BindBuffers();
  
private:
  std::array<float, 6> vertices_;
  GLuint shaderProgram_;
  
};