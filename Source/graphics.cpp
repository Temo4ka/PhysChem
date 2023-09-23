#include "../Headers/Objects.h"

int Graphics::draw(sf::Image *image, sf::Color color) {
    catchNullptr(image, EXIT_FAILURE);

    FILE* logFile = freopen("logFile", "w", stdout);
    fprintf(logFile, "Here\n");
    fclose(logFile);

    Vect position = this->position;

    for (int x0 = 0; x0 < this->w; x0++)
        for (int y0 = 0; y0 < this->h; y0++)
            image->setPixel(position.x + x0, position.y + y0, color);
    
    int x0 = position.x + 30; 
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

    if (this -> getCurX() == -1) this -> draw(image);
    if (this -> getCurX() >= this->getW() + this->getPosition().x)
        this -> setCurX(this ->getPosition().x + 30);
    this->incCurX();

    for (int y = 1; y < molecules * 2; y++)
        image -> setPixel(this->getCurX(), this->getPosition().y + this->getH() * 4 / 5 - y, color);
    image -> setPixel(this->getCurX(), this->getPosition().y + this->getH() * 4 / 5 - molecules * 2, sf::Color::Yellow);

    return EXIT_SUCCESS;
}

int Time_Molecules::showText(sf::RenderWindow *window, sf::Font *font) {
    catchNullptr(window, EXIT_FAILURE);

    sf::Text time = sf::Text("time", *font);
    time.setPosition(680, 330);
    time.setCharacterSize(10);

    sf::Text molecules = sf::Text("mol", *font);
    molecules.setPosition(2, 245);
    molecules.setCharacterSize(8);

    window -> draw(time);
    window -> draw(molecules);

    return EXIT_SUCCESS;
}

