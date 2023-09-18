#include "../Headers/Scene.h"

// #define DEBUG_
// #include "../Headers/Log.h"

Molecule::Molecule (const Vect startPos, const int rangeX, const int rangeY, const double weight) {

    int r1 = rand() % rangeX;
    int r2 = rand() % rangeY;

    this -> position = Vect(startPos.x + r1, startPos.y + r2);

    this -> velocity = (rand() % MAX_START_VELOCITY);
    this ->  weight  =            weight            ;

    this -> dir.x = ((double) (rand() % 2 - 1))  /  (double) (rand());
    this -> dir.y = sqrt(1 - SQR(this -> dir.x));

    return;
}

Piston::Piston (const Vect &startPos, const double w, const double h, const double velocity, const sf::Color color) {
    this -> pistonShape.setSize(sf::Vector2f(w, h));
    this -> pistonShape.setPosition(startPos.x, startPos.y);
    this -> pistonShape.setFillColor(color);

    this -> velocity = velocity;

    return;
}

int Piston::move (const double deltaTime) {
    catchNullptr(this, EXIT_FAILURE);


    sf::Vector2f pos = this -> pistonShape.getPosition();
    pos.y += this -> velocity * deltaTime;

    this -> pistonShape.setPosition(pos.x, pos.y);

    return EXIT_SUCCESS;
}

// int TypeA::collide(TypeA *a) {
//     catchNulptr(a, EXIT_FAILURE);

//     if (SQR(this -> getVelocity()) * this -> getWeight + SQR(a -> getVelocity()) * a -> getWeight() > REACTION_CONST)
//         this -> absorb(a);

//     return EXIT_SUCCESS;
// }

// int TypeB::collide(TypeA *a) {
//     catchNulptr(a, EXIT_FAILURE);

//     if (SQR(this -> getVelocity()) * this -> getWeight + SQR(a -> getVelocity()) * a -> getWeight() > REACTION_CONST)
//         this -> absorb(a);

//     return EXIT_SUCCESS;
// }

// int TypeB::collide(TypeB *b) {
//     catchNulptr(a, EXIT_FAILURE);

//     if (SQR(this -> getVelocity()) * this -> getWeight + SQR(a -> getVelocity()) * a -> getWeight() > REACTION_CONST)
//         this -> absorb(a);

//     return EXIT_SUCCESS;
// }


int Molecule::absorb(Molecule *molecule) {
    catchNullptr(molecule, EXIT_FAILURE);

    this -> weight += molecule->getWeight();

    delete molecule;

    return EXIT_SUCCESS;
}

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

int Piston::draw(sf::RenderWindow *window) {
    catchNullptr(window, EXIT_FAILURE);

    window -> draw(this -> pistonShape);

    return EXIT_SUCCESS;
}
