#include "../Headers/Scene.h"

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
    if (pos.y < PISTON_Y || pos.y > PISTON_LIMIT) 
        this -> velocity *= -1;

    pos.y += this -> velocity * deltaTime;

    this -> pistonShape.setPosition(pos.x, pos.y);

    return EXIT_SUCCESS;
}

int Piston::draw(sf::RenderWindow *window) {
    catchNullptr(window, EXIT_FAILURE);

    window -> draw(this -> pistonShape);

    return EXIT_SUCCESS;
}

double Piston::getPosition() {
    sf::Vector2f pos = this -> pistonShape.getPosition();

    return pos.y + PISTON_HEIGHT;
}