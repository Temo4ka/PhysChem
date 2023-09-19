#include "../Headers/Scene.h"

// #define DEBUG_
// #include "../Headers/Log.h"

int separateScreen(sf::RenderWindow *window, sf::Color color) {
    catchNullptr(window, EXIT_FAILURE);

    sf::RectangleShape block;
    block.setPosition(WINDOW_WIDTH / 2 - 2, 0);
    block.setSize(sf::Vector2f(5, WINDOW_HEIGHT));
    block.setFillColor(color);

    window -> draw(block);

    block.setPosition(0, WINDOW_HEIGHT / 3 - 2);
    block.setSize(sf::Vector2f(WINDOW_WIDTH / 2, 5));
    block.setFillColor(color);

    window -> draw(block);

    return EXIT_SUCCESS;
}
