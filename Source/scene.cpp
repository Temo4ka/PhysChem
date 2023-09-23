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

int organiseButtons(ButtonManager *buttonManager, MoleculeManager *manager, sf::Font *font) {
    catchNullptr(    manager  , EXIT_FAILURE);
    catchNullptr(buttonManager, EXIT_FAILURE);
    catchNullptr(     font    , EXIT_FAILURE);

    
    AddTypeA* addTypeA_button = new AddTypeA(Vect(121, 31), 240, 60, 0, 1, 0, manager);
    addTypeA_button -> setText("Type_A", 6, font);

    AddTypeB* addTypeB_button = new AddTypeB(Vect(121, 91), 240, 60, 1, 0, 0, manager);
    addTypeB_button -> setText("Type_B", 6, font);

    MoveUp* moveUp = new MoveUp(Vect(121, 151), 240, 60, 0, 0, 1, manager);
    moveUp -> setText("Up", 2, font);

    MoveDown* moveDown = new MoveDown(Vect(121, 211), 240, 60, 1, 1, 0, manager);
    moveDown -> setText("Down", 4, font);

    buttonManager->addButton(addTypeA_button);
    buttonManager->addButton(addTypeB_button);
    buttonManager->addButton(    moveDown   );
    buttonManager->addButton(     moveUp    );

    return EXIT_SUCCESS;
}
