#include "app_maze.hpp"
#include "app_cell.hpp"

#include <cassert>

CCell* CMaze::GetCellNeighbor(const CCell* cell, EDirection dir) const noexcept
{
	assert(cell);
	if (!cell)
		return nullptr;

	switch (dir) {
	case EDirection::N:

		if (cell->m_uQuickIndex < m_vecGridSize.x)
			return nullptr;

		return m_oCells[cell->m_uQuickIndex - m_vecGridSize.x].get();

	case EDirection::E:

		if (cell->m_vecIndex.x == (m_vecGridSize.x - std::size_t(1)))
			return nullptr;

		return m_oCells[cell->m_uQuickIndex].get();

	case EDirection::S:

		if (cell->m_vecIndex.y == (m_vecGridSize.y - std::size_t(1)))
			return nullptr;

		return m_oCells[cell->m_uQuickIndex + m_vecGridSize.x].get();

	case EDirection::W:

		if (cell->m_vecIndex.x == 0)
			return nullptr;

		return m_oCells[cell->m_uQuickIndex - std::size_t(1)].get();

	default:
		return nullptr;
	}
}
