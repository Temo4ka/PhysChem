#include "../Headers/Objects.h"

Molecule::Molecule (const Vect& startPos, const int rangeX, const int rangeY, const double weight) {

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

int Piston::Move (const double deltaTime) {
    catchNullptr(this, EXIT_FAILURE);

    sf::Vector2f pos = this -> pistonShape.getPosition();
    pos.y += this -> velocity * deltaTime;

    this -> pistonShape.setPosition(pos.x, pos.y);

    return EXIT_SUCCESS;
}
