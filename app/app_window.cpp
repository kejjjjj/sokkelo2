#include "app_window.hpp"

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_internal.h"

#include <d3d11.h>
#include <d3dx11.h>

bool CMainWindow::Render() {

    if (!ImGui::GetCurrentContext())
        return false;

    PreRender();

    ImGui::Begin("yo", 0, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_MenuBar);

    ImGui::Text("hiii");

    using T = decltype(ImVec2::x);

    ImGui::SetWindowPos({ static_cast<T>(CImguiWindow::x), static_cast<T>(CImguiWindow::y) });
    ImGui::SetWindowSize({ static_cast<T>(CImguiWindow::w), static_cast<T>(CImguiWindow::h) });

    ImGui::End();

    PostRender();

    return true;
}

void CMainWindow::PreRender()
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
}
void CMainWindow::PostRender()
{
    // Rendering
    ImGui::Render();
    static const ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
    g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
    g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    g_pSwapChain->Present(1, 0); // Present with vsync
}
