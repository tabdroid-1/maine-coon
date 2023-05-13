//
// Created by Tristan Zippert on 11/24/21.
//

#ifndef TABBYENGINE_VKUNIFORMBUFFER_H
#define TABBYENGINE_VKUNIFORMBUFFER_H

#include "TabbyEngine/Renderer/UniformBuffer.h"
#include <vulkan/vulkan_core.h>

namespace TabbyEngine{
    class VulkanUniformBuffer: public UniformBuffer{
        VulkanUniformBuffer(uint32_t size, uint32_t binding);
        virtual ~VulkanUniformBuffer();

        virtual void SetData(const void* data, uint32_t size, uint32_t offset =0) override;

    private:
        VkVertexInputBindingDescription bindingDescription;
    };
}
#endif //TABBYENGINE_VKUNIFORMBUFFER_H
