#include "prey.hpp"
#include "arena.hpp"

void Prey::move(const Dir& dir)
{
	pos.move(dir);
}

void Prey::moveAsNpc(const Arena& arena)
{
	int rand_dir_idx = rand() % available_dirs.size();
	while (!arena.isInBounds(pos + available_dirs[rand_dir_idx])) {
		rand_dir_idx = rand() % available_dirs.size();
	}
	pos.move(available_dirs[rand_dir_idx]);
}
