//
// Created by Tristan Zippert on 6/19/21.
//
#pragma once
#include "TabbyEngine/Renderer/Texture.h"
#include <glad/glad.h>

#ifndef TABBYENGINE_CLION_OPENGLTEXTURE_H
#define TABBYENGINE_CLION_OPENGLTEXTURE_H


namespace TabbyEngine{
    class OpenGLTexture2D: public Texture2D {
    public:
        OpenGLTexture2D(uint32_t width, uint32_t height);
        OpenGLTexture2D(const char* path);

        void CreateCubeMap(bool with_mipmap);

        virtual ~OpenGLTexture2D();

        virtual void SetData(void* data, uint32_t size, uint32_t slot =0) const override;

        virtual uint32_t  GetHeight() const override{return m_Height;}
        virtual uint32_t  GetWidth() const override{return m_Width;}
        virtual uint32_t GetRendererID() const override {return m_RendererID;}

        virtual void Bind(uint32_t slot = 0) const override;

        virtual bool operator==(const Texture& other) const override{
            return m_RendererID == ((OpenGLTexture2D&)other).m_RendererID;
        }
        virtual std::string getPath() const override{return m_Path;}

    private:
        std::string m_Path;
        uint32_t m_Width, m_Height;
        uint32_t m_RendererID;
        GLenum m_InternalFormat, m_DataFormat;
    };
}


#endif //TABBYENGINE_CLION_OPENGLTEXTURE_H
