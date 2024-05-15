#include "arena.hpp"

Arena::Arena()
{
    Point2D prey_pos{ rand() % w, rand() % h };
    Point2D predator_pos{ rand() % w, rand() % h };
    while (prey_pos.isTouching(predator_pos)) {
        predator_pos = Point2D(rand() % w, rand() % h);
    }
    prey = std::make_unique<Prey>(prey_pos);
    predator = std::make_unique<Predator>(predator_pos);
}

bool Arena::isInBounds(const Point2D& point) const
{
    return point.X() >= 0 && point.X() < w && point.Y() >= 0 && point.Y() < h;
}

void Arena::play()
{
    prey_is_npc = askForSide();
    display();
    while (!prey->getPos().isTouching(predator->getPos())) {
        if (prey_is_npc) {
            const auto [dir_idx, len] = askForPredatorMove();
            predator->move(predator->getAvailableDirsMember()[dir_idx], len);
            prey->moveAsNpc(*this);
        }
        else {
            const int ans = askForPreyMove();
            prey->move(prey->getAvailableDirsMember()[ans]);
            predator->moveAsNpc(*this);
        }
        display();
    }
    std::cout << "Игра окончена! Жертва поймана!\n";
    std::cout << prey->getPos().X() << " " << prey->getPos().Y() << "\n";
    std::cout << predator->getPos().X() << " " << predator->getPos().Y();
}

bool Arena::askForSide() const
{
    std::cout << "Выбери сторону?\n1 - хищник, 2 - жертва\n";
    int ans = -1;
    std::cin >> ans;
    while (ans < 1 || ans > 2) {
        std::cout << "Некорректное значение, попробуй еще раз!\n";
        std::cin >> ans;
    }
    return ans == 1;
}

int Arena::askForPreyMove() const
{
    std::cout << "Куда убегаем?\n0 - вверх, 1 - вправо, 2 - вниз, 3 - влево,"
        "\n4 - вверх - влево, 5 - вверх - вправо, 6 - вниз - вправо, 7 - вниз - влево\n";
    int ans = -1;
    std::cin >> ans;
    while (ans < 0 || ans > 7 || !isInBounds(prey->getPos() + prey->getAvailableDirsMember()[ans])) {
        std::cout << "Некорректное значение, либо в этой стороне стена :)\nПопробуй еще раз!\n";
        std::cin >> ans;
    }
    return ans;
}

std::pair<int, int> Arena::askForPredatorMove() const
{
    std::cout << "Куда двигаемся?\n0 - вверх, 1 - вправо, 2 - вниз, 3 - влево\n";
    int ans_dir = -1;
    std::cin >> ans_dir;
    while (ans_dir < 0 || ans_dir > 3 || !isInBounds(predator->getPos() + predator->getAvailableDirsMember()[ans_dir])) {
        std::cout << "Некорректное значение, либо в этой стороне стена :)\nПопробуй еще раз!\n";
        std::cin >> ans_dir;
    }

    std::cout << "На сколько клеток двигаемся (от 1 до 3)?\n";
    int ans_len = -1;
    std::cin >> ans_len;
    Point2D predator_tmp_pos = predator->getPos();
    predator_tmp_pos.move(predator->getAvailableDirsMember()[ans_dir], std::min(std::max(ans_len, 0), 3));
    while (ans_len < 1 || ans_len > 3 || !isInBounds(predator_tmp_pos)) {
        std::cout << "Некорректное значение, либо на столько клеток нельзя переместиться из-за стены\nПопробуй еще раз!\n";
        std::cin >> ans_len;
        predator_tmp_pos = predator->getPos();
        predator_tmp_pos.move(predator->getAvailableDirsMember()[ans_dir], std::min(std::max(ans_len, 0), 3));
    }

    return { ans_dir, ans_len };
}

void Arena::display() const {
    // Clear screen and move cursor to home position
    system("cls");
    std::cout << " " << std::string(w * 2 + 3, '~') << std::endl;
    for (int y = h - 1; y >= 0; --y) {
        std::cout << std::setw(2) << y + 1 << "|";
        for (int x = 0; x < w; ++x) {
            if (prey->getPos() == Point2D(x, y)) {
                std::cout << "()";
            }
            else if (predator->getPos() == Point2D(x, y)) {
                std::cout << "**";
            }
            else {
                std::cout << "  ";
            }
        }
        std::cout << "|" << std::endl;
    }
    std::cout << " " << std::string(w * 2 + 3, '~') << std::endl;

    std::cout << "  ";
    for (int x = 1; x <= w; ++x) {
        std::cout << std::setw(2) << x;
    }
    std::cout << std::endl;
}
