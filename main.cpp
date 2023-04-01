#include <iostream>
#include "src/GameController.h"
#include "src/InputController.h"
#include <memory>


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    InputController In_con;

    std::unique_ptr<GameController> game = std::make_unique<GameController>();

    In_con.start_cli(game.get());

    return 0;
}




