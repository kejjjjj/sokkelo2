#pragma once

#include "dx/dx_imgui.hpp"

#include <cstdint>
#include <windows.h>

class CImguiWindow
{
public:
	CImguiWindow(std::int32_t _x, std::int32_t _y, std::int32_t _w, std::int32_t _h) :
		x(_x), y(_y), w(_w), h(_h){}

	[[nodiscard]] virtual bool Render() = 0;

	constexpr void SetPosition(std::int32_t _x, std::int32_t _y) noexcept { x = _x; y = _y; }
	constexpr void SetSize(std::int32_t _w, std::int32_t _h) noexcept { w = _w; h = _h; }

protected:
	std::int32_t x{}, y{};
	std::int32_t w{}, h{};
};

class CMainWindow : public CImGui, public CImguiWindow
{
public:
	CMainWindow(std::int32_t _x, std::int32_t _y, std::int32_t _w, std::int32_t _h)
		: CImguiWindow(_x, _y, _w, _h){}

	[[nodiscard]] bool Render() override;
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:

	void PreRender();
	void PostRender();
};

