#include "../Headers/Objects.h"

int Graphics::draw(sf::Image *image, sf::Color color) {
    catchNullptr(image, EXIT_FAILURE);

    Vect position = this->getPosition();

    for (int x0 = 0; x0 < this->getW(); x0++)
        for (int y0 = 0; y0 < this->getH(); y0++)
            image->setPixel(x0, y0, color);
    
    int x0 = position.x + this->getW() / 5; 
    for (int y = 0; y < this->getH(); y++)
        image -> setPixel(x0, position.y + y, sf::Color::White);

    int y0 = position.y + this->getH() / 5;
    for (int x = 0; x < this->getW(); x++)
        image -> setPixel(x + position.x, y0, sf::Color::White);

    return EXIT_SUCCESS;
}

