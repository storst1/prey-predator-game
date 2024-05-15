#include "arena.hpp"

int main() {
    srand(static_cast<unsigned int>(time(0)));
    setlocale(LC_ALL, "Russian");
    Arena arena;
    arena.play();
    return 0;
}
