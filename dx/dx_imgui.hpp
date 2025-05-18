#pragma once

#include "globals.hpp"
#include "dx_context.hpp"

class CImGui : public CDirectX
{
    NONCOPYABLE(CImGui);
public:

    CImGui() = default;
    ~CImGui() { Cleanup(); }

    [[nodiscard]] Status Initialize(void* hwnd);
    void Cleanup();

private:

};
