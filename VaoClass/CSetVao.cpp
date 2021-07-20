#include "CSetVao.h"

CSetVao::CSetVao(float* vertexs, int vertexs_sz, int* indicies, int indicies_sz) : vao(0), vbo(0), ebo(0)
{
    if (vertexs == nullptr) return;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    setVbo(vertexs, vertexs_sz);
    setEbo(indicies, indicies_sz);
}

void CSetVao::setVbo(float* vertexs, int vertexs_sz, int layout = 0, int gap = 3)
{
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertexs_sz, vertexs, GL_STATIC_DRAW);
    glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, gap * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(layout);
}

void CSetVao::setEbo(int* indicies, int indicies_sz)
{

}

void CSetVao::setBuffer(int* data, int sz)
{
}

CSetVao::~CSetVao()
{
    if (!vao) glDeleteVertexArrays(1, &vao);
    if (!vbo) glDeleteBuffers(1, &vbo);
    if (!ebo) glDeleteBuffers(1, &ebo);
}

