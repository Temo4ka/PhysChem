#include "../Headers/Objects.h"

int Graphics::draw(sf::Image *image, sf::Color color) {
    catchNullptr(image, EXIT_FAILURE);

    Vect position = this->position;

    for (int x0 = 0; x0 < this->w; x0++)
        for (int y0 = 0; y0 < this->h; y0++)
            image->setPixel(x0, y0, color);
    
    int x0 = position.x + this->w / 5; 
    for (int y = 0; y < this->h; y++)
        image -> setPixel(x0, position.y + y, sf::Color::White);
    this -> curX = x0;

    int y0 = position.y + 4 * this->h / 5;
    for (int x = 0; x < this->w; x++)
        image -> setPixel(x + position.x, y0, sf::Color::White);


    return EXIT_SUCCESS;
}

int Time_Molecules::update(double deltaTime, int molecules, sf::Image *image, sf::Color color) {
    catchNullptr(image, EXIT_FAILURE);

    this -> updTime -= deltaTime;
    if (this -> updTime > 0) return EXIT_SUCCESS;

    this -> updTime   = GRAPHIC_TIMER;
    this -> molecules =   molecules  ;

    (this->curX)++;
    if (this -> curX >= this->getW() + this->getPosition().x) this -> draw(image);

    for (int y = this->getPosition().y + this->getH() * 4 / 5 - molecules; y++)
        image -> setPixel(x, y, color);

    return EXIT_SUCCESS;
}

