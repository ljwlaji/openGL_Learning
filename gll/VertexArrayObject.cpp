//
//  VertexArrayObject.cpp
//  gll
//
//  Created by lijingwei on 2021/12/4.
//

#include "VertexArrayObject.hpp"
#include "Renderer.hpp"

VertexArrayObject::VertexArrayObject()
{
    //glGenBuffers(1, &buffer); //number of buffers, return an id of buffer which written in the povide uint pointer
    //设置vertex array object
    //这个东西好像没有指定任何与之关联的数组或vertex 但是又不能不写 就离谱
    //难道这个是管理下面VBO和EBO的前提?
    glGenVertexArrays(1, &m_RendererID);
}

VertexArrayObject::~VertexArrayObject()
{
    GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArrayObject::Bind() const
{
    GLCall(glBindVertexArray(m_RendererID));
}

void VertexArrayObject::UnBind() const
{
    GLCall(glBindVertexArray(0));
}

void VertexArrayObject::AddBuffer(const VertexBuffer& buffer, const VertexBufferLayout& layout)
{
    Bind();
    buffer.Bind();
    const auto* elements = layout.GetElements();
    unsigned int offset = 0;
    //这个方法需要在生成VAO并且绑定之后调用(glGenVertexArrays, glBindVertexArray)
    //GL_INVALID_OPERATION is generated by glEnableVertexArrayAttrib and glDisableVertexArrayAttrib if vaobj(VAO) is not the name of an existing vertex array object.
    //size 每组vertex长度 这边位置信息始2个float组成一个vertex 所以是2
    //type 单个数据的类型
    //normal 是否需要让数据归一化 bool
    //stride 每组vertex数据的步长 bit为单位 这边为2个float的长度 8
    //pointer pos/tex_cord/color 指代起始位置
    //关于这两行的详细情况 https://www.youtube.com/watch?v=Bcs56Mm-FJY&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2&index=12 10:00
    for (unsigned int i = 0; i < elements->size(); i++) {
        const auto& element = elements->at(i);
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset);
        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }

    //https://www.youtube.com/watch?v=0p9VxImr7Y0&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2&index=4 18:00 glBindBuffer

}
