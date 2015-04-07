
class Rasterizer {
    
private:
    float* vertices_;
    GLuint shaderProgram_;
    
public:
    Rasterizer();
    
    ~Rasterizer();
    
    bool Init();
    
    bool Rasterize();
    
};