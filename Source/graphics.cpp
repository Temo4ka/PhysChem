#include "../Headers/Objects.h"

int Graph::drawBase(Vect &position, Vect &size, sf::Image *image, sf::Color color) {
    catchNullptr(image, EXIT_FAILURE);

    for (int x0 = 0; x0 < size.x; x0++)
        for (int y0 = 0; y0 < size.y; y0++)
            image->setPixel(position.x + x0, position.y + y0, color);
    
    int x0 = position.x + 30; 
    for (int y = 0; y < size.y; y++)
        image -> setPixel(x0, position.y + y, sf::Color::White);
    curX = x0;

    int y0 = position.y + 4 * size.y / 5;
    for (int x = 0; x < size.x; x++)
        image -> setPixel(x + position.x, y0, sf::Color::White);


    return EXIT_SUCCESS;
}

void Graph::update(double deltaTime, int value) {
    timer -= deltatime;
    valueY = value;
}

void Graph::draw(Vect &position, Vect &size, sf::Image *image, sf::Color color) {
    if (timer > 0) return;
    timer = GRAPHIC_TIMER;

    curX++;
    if (curX > position.x + size.x)
        curX = position.x + 30;

    for (int y = pos.y; y < pos.y + size.y; y++) {
        if (y < pos.y + size.y * 4 / 5 - 2 * valueY ||  y > pos.y + size.y * 4 / 5)
            image -> setPixel(curX, y, sf::Color(0, 80, 0));
        else if (y >= pos.y + size.y * 4 / 5 - 2 * valueY && y < pos.y + size.y * 4 / 5)
            image -> setPixel(curX, y, color);
        else
            image -> setPixel(curX, y, sf::Color::White);

    }
    for (int y = pos.y; y < pos.y + size.y; y++) 
            image -> setPixel(curX + 1, y, sf::Color::White);

    image -> setPixel(curX, this->getPosition().y + h * 4 / 5 - valueY * 2, sf::Color::White);

    return;
}

int Time_Molecules::update(double deltaTime, int molecules, sf::Image *image, sf::Color color) {
    catchNullptr(image, EXIT_FAILURE);

    this -> updTime -= deltaTime;
    if (this -> updTime > 0) return EXIT_SUCCESS;

    this -> updTime   = GRAPHIC_TIMER;
    this -> molecules =   molecules  ;

    if (this -> getCurX() == -1) this -> draw(image);
    if (this -> getCurX() >= this->getW() + this->getPosition().x)
        this -> setCurX(this ->getPosition().x + 30);
    this->incCurX();

    int   x  = this ->   getCurX  ();
    Vect pos = this -> getPosition();
    int   h  = this ->     getH   ();

    for (int y = pos.y; y < pos.y + h; y++) {
        if (y < pos.y + h * 4 / 5 - 2 * molecules ||  y > pos.y + h * 4 / 5)
            image -> setPixel(x, y, sf::Color(0, 80, 0));
        else if (y >= pos.y + h * 4 / 5 - 2 * molecules && y < pos.y + h * 4 / 5)
            image -> setPixel(x, y, color);
        else
            image -> setPixel(x, y, sf::Color::White);

    }
    for (int y = pos.y; y < pos.y + h; y++) 
            image -> setPixel(x + 1, y, sf::Color::White);

    image -> setPixel(x, this->getPosition().y + h * 4 / 5 - molecules * 2, sf::Color::White);

    return EXIT_SUCCESS;
}

int Graph::showAllText(Vect &position, Vect &size, sf::RenderWindow *window, sf::Font &font) {
    catchNullptr(window, EXIT_FAILURE);

    window->draw(getText(Vect(position.x + size.x - text.size * charSize, position.y + size.y - charSize), size, font, legendX, 10));
    window->draw(getText(Vect(0, 0), size, font, legendY, 10));
    window->draw(getText(Vect(position.x + size.x - text.size * charSize, position.y + size.y - charSize), size, font, legendX, 10));
    window->draw(getText(Vect(position.x + size.x - text.size * charSize, position.y + size.y - charSize), size, font, legendX, 10));
    window->draw(getText(Vect(position.x + size.x - text.size * charSize, position.y + size.y - charSize), size, font, legendX, 10));

    return EXIT_SUCCESS;
}

sf::Text Graph::getText(const Vect &position, const Vect &size, const sf::Font &font, const std::string text_, const size_t charSize) {
    sf::Text text = sf::Text(text_, font);
    time.setPosition(position.x, position.y);
    time.setCharacterSize(charSize);

    return text;
}

