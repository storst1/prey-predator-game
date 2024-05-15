#include <limits>

#include "predator.hpp"
#include "arena.hpp"

void Predator::move(const Dir& dir, const std::size_t length)
{
	pos.move(dir, length);
}

void Predator::moveAsNpc(const Arena& arena)
{
	float best_dist = std::numeric_limits<float>::max();
	Dir best_dir{};
	std::size_t best_move_len = 0;
	for (const auto& cur_dir : available_dirs) {
		for (std::size_t cur_len = 1; cur_len <= 3; ++cur_len) {
			Point2D cur_new_pos{ pos };
			cur_new_pos.move(cur_dir, cur_len);
			if (!arena.isInBounds(cur_new_pos)) {
				continue;
			}

			const float cur_dist = cur_new_pos.distanceReal(arena.getPreyPos());
			if (cur_dist < best_dist) {
				best_dist = cur_dist;
				best_dir = cur_dir;
				best_move_len = cur_len;
			}
		}
	}
	pos.move(best_dir, best_move_len);
}
