#pragma once

#include "globals.hpp"
#include "utils/u_vec2.hpp"

#include <vector>
#include <memory>

class CCell;

class CMaze final
{
	NONCOPYABLE(CMaze);

public:

	constexpr CMaze(const ivec2& size) : m_vecGridSize(size){}

private:
	//used for populating the neighbors
	[[nodiscard]] CCell* GetCellNeighbor(const CCell* cell, EDirection dir) const noexcept;

	ivec2 m_vecGridSize;
	std::vector<std::unique_ptr<CCell>> m_oCells;
};

