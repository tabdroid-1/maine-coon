//
// Created by Tristan Zippert on 8/2/21.
//
#pragma once

#include "TabbyEngine/Renderer/UniformBuffer.h"

#ifndef TABBYENGINE_OPENGLUNIFORMBUFFER_H
#define TABBYENGINE_OPENGLUNIFORMBUFFER_H
namespace TabbyEngine{
    class OpenGlUniformBuffer: public UniformBuffer{
    public:
        OpenGlUniformBuffer(uint32_t size, uint32_t binding);
        virtual ~OpenGlUniformBuffer();

        virtual void SetData(const void* data, uint32_t size, uint32_t offset =0) override;
    private:
        uint32_t m_RendererID =0;
    };
}
#endif //TABBYENGINE_OPENGLUNIFORMBUFFER_H
