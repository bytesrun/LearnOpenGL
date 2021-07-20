#include "glad/glad.h"
class CSetVao
{
public:
    CSetVao(float* vertexs, int vertexs_sz, int* indicies, int indicies_sz);
    ~CSetVao();
    void setVbo(float* vertexs, int vertexs_sz, int layout = 0, int gap = 3);
    void setEbo(int* indicies, int indicies_sz);
private:
    void setBuffer(int* data, int sz);
public:
    unsigned int vao;
private:
    unsigned int vbo;
    unsigned int ebo;
};