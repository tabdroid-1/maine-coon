//
// Created by Tristan Zippert on 8/11/21.
//
#pragma once
#ifndef TABBYENGINE_PROCESSORDETECTION_H
#define TABBYENGINE_PROCESSORDETECTION_H

#include "tbpch.h"

namespace TabbyEngine{
    class ProcessorDetectionBase{
    public:
         static std::string getCPUString();
         static int32_t getCPUMaxFreq() ;
    };
}
#endif //TABBYENGINE_PROCESSORDETECTION_H
