#pragma once

#include "globals.hpp"

class CDirectX
{
    NONCOPYABLE(CDirectX);
public:

    CDirectX() = default;
    ~CDirectX() { Cleanup(); }

    [[nodiscard]] Status Initialize(void* hwnd);
    void Cleanup();

protected:
    struct ID3D11Device* g_pd3dDevice = 0;
    struct ID3D11DeviceContext* g_pd3dDeviceContext = 0;
    struct IDXGISwapChain* g_pSwapChain = 0;
    struct ID3D11RenderTargetView* g_mainRenderTargetView = 0;

//private:

    void CleanupRenderTarget();
    void CreateRenderTarget();
};
