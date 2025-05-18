#pragma once

#include "globals.hpp"
#include "utils/u_vec2.hpp"

#include <array>

class CCell
{
public:
	constexpr CCell(const uvec2& vecIndex, std::size_t quickIndex) : m_vecIndex(vecIndex), m_uQuickIndex(quickIndex){}
	constexpr virtual ~CCell() = default;

	constexpr void GiveNeighbor(const CCell* other, EDirection dir) noexcept {
		m_arrNeighbors[static_cast<std::underlying_type_t<EDirection>>(dir)] = other;
	}

	[[nodiscard]] virtual constexpr bool IsWall() const noexcept { return false; }

	uvec2 m_vecIndex;
	std::size_t m_uQuickIndex; //index on the grid, left to right, top to bottom order

	bool m_bVisited{};
	bool bBacktraced{}; //deadend
	bool bDeadend{}; //has only one corridor neighbor

protected:
	std::array<const CCell*, 4> m_arrNeighbors{};


};

class CCellWall final : public CCell
{
public:
	~CCellWall() = default;
	[[nodiscard]] virtual constexpr bool IsWall() const noexcept override { return true; }

private:
};

