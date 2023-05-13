//
// Created by Tristan Zippert on 5/29/21.
//
#pragma once
#include "TabbyEngine/Renderer/VertexArray.h"

#ifndef TABBYENGINE_CLION_OPENGLVERTEXARRAY_H
#define TABBYENGINE_CLION_OPENGLVERTEXARRAY_H

namespace TabbyEngine{
    class OpenGLVertexArray: public VertexArray{
    public:
        OpenGLVertexArray();
        virtual ~OpenGLVertexArray();

        virtual void Bind() const override;

        virtual void Unbind() const override;

        virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)override ;
        virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)override ;

        virtual const std::vector<Ref<VertexBuffer>> & GetVertexBuffers() const override{return m_VertexBuffers;};
        virtual const Ref<IndexBuffer> & GetIndexBuffer() const override{return m_IndexBuffer;};

    private:
        RendererID m_RendererID;
        uint32_t m_VertexBufferIndex = 0;
        std::vector<Ref<VertexBuffer>> m_VertexBuffers;
        std::shared_ptr<IndexBuffer> m_IndexBuffer;

    };
}


#endif //TABBYENGINE_CLION_OPENGLVERTEXARRAY_H
