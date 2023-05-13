//
// Created by Tristan Zippert on 5/24/21.
//

#pragma once
#include "TabbyEngine/Core/Input.h"
namespace TabbyEngine{
    class MacInput: public Input{
    protected:
        virtual bool IsKeyPressedImpl(int keycode) override;


        virtual float GetMouseXImpl() override;
        virtual float GetMouseYImpl() override;
        virtual std::pair<float,float> GetMousePosImpl() override;

        virtual bool IsMouseButtonPressedImpl(int button) override;
    };
}