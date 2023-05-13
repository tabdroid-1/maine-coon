//
// Created by Tristan Zippert on 5/27/21.
//
#include "OpenGLBuffer.h"
#include "tbpch.h"

#include <glad/glad.h>

namespace TabbyEngine{
    OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t count) {
        TABBY_PROFILE_FUNCTION();
        glShadeModel(GL_FLAT);
        glGenBuffers(1, &m_RendererID);
        glBindBuffer(GL_ARRAY_BUFFER,m_RendererID);
        glBufferData(GL_ARRAY_BUFFER, count, nullptr, GL_DYNAMIC_DRAW);
    }
    OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
    {
        TABBY_PROFILE_FUNCTION();
        glGenBuffers(1, &m_RendererID);
        glBindBuffer(GL_ARRAY_BUFFER,m_RendererID);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

    }
    OpenGLVertexBuffer::~OpenGLVertexBuffer(){
        TABBY_PROFILE_FUNCTION();
        glDeleteBuffers(1, &m_RendererID);
    }
    void OpenGLVertexBuffer::SetData(const void *data, uint32_t size) {
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferSubData(GL_ARRAY_BUFFER,0, size ,data);
    }
    void OpenGLVertexBuffer::Bind() const {
        TABBY_PROFILE_FUNCTION();
        glBindBuffer(GL_ARRAY_BUFFER,m_RendererID);
    }
    void OpenGLVertexBuffer::Unbind() const {
        TABBY_PROFILE_FUNCTION();
        glBindBuffer(GL_ARRAY_BUFFER,0);
    }

    //-----------------------------------------------------------------------------------
    //Index Buffer-----------------------------------------------------------------------
    //-----------------------------------------------------------------------------------

    OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t *indices, uint32_t count)
    :m_Count(count){
        TABBY_PROFILE_FUNCTION();
        glGenBuffers(1, &m_RendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_RendererID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    }
    OpenGLIndexBuffer::~OpenGLIndexBuffer() {
        TABBY_PROFILE_FUNCTION();
        glDeleteBuffers(1, &m_RendererID);
    }
    void OpenGLIndexBuffer::Bind() const {
        TABBY_PROFILE_FUNCTION();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    }
    void OpenGLIndexBuffer::Unbind() const {
        TABBY_PROFILE_FUNCTION();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    }
}