#include "../Headers/Scene.h"

// #define DEBUG_
// #include "../Headers/Log.h"

int Button::draw(sf:: Image *image) {
    double a = this -> width  / 2;
    double b = this -> height / 2;

    double x0 = this -> position.x;
    double y0 = this -> position.y;

    // this -> isPressed = 1;

    for (double x = x0 - a; x <= x0 + a; x++)
        for (double y = y0 - b; y <= y0 + b; y++) {
            double k = 1 - SQR(y - y0 + b) / SQR(2 * b);
            if (k <= 0) k = 0;
            if (this -> isPressed) k = 1 - k;

            image -> setPixel(x, y, sf::Color(this->r * k * 255, this->g * k * 255, this-> b * k * 255));
        }

    return EXIT_SUCCESS;
}

int Button::setText(const char *text, const signed textSize, sf::Font *font) {
    this -> text = sf::Text(text, *font);
    this -> text.setCharacterSize(15);
    this -> text.setPosition(this -> position.x - width / 3, this -> position.y - height / 3);

    return EXIT_SUCCESS;
}

int Button::showText(sf::RenderWindow *window) {
    if (this -> isPressed)
        this -> text.setColor(sf::Color::White);
    else
        this -> text.setColor(sf::Color::Black);

    window -> draw(text);
    
    return EXIT_SUCCESS;
}

int Button::checkIsPressed(const Vect mousePosition, int buttonStatus) {
    Vect dist = Vect(abs(mousePosition.x - this->position.x), abs(mousePosition.y - this->position.y));

    FILE* logFile = freopen("logFile", "w", stdout);

    fprintf(logFile, "%lg - %lg\n", mousePosition.x, mousePosition.y);
    
    if (dist.x <= this->width / 2 && dist.y <= this->height / 2)
        this->isPressed = buttonStatus;
    else
        this->isPressed = BUTTON_NOT_PRESSED;

    fclose(logFile);

    return EXIT_SUCCESS;
}

//--------------------------------------------------------------------------------------------------------------------

ButtonManager::ButtonManager() {
    this ->  size = 0;
    this -> array = new Button*[MAX_BUTTON_NUM];

    return;
}

ButtonManager::~ButtonManager() {
    for (int cur = 0; cur < MAX_BUTTON_NUM; cur++)
        delete this -> array[cur];

    delete[] this -> array;
    this -> size = -1;

    return;
}

int ButtonManager::addButton(Button *button) {
    if (this -> size == MAX_BUTTON_NUM) return EXIT_FAILURE;

    this -> array[this -> size] = button;
    this -> size++;

    return EXIT_SUCCESS;
}

int ButtonManager::draw(sf::Image *image) {
    catchNullptr(image, EXIT_FAILURE);

    for (int curButton = 0; curButton < this -> size; curButton++)
        ((this->array[curButton])->draw)(image);

    return EXIT_SUCCESS;
}

int ButtonManager::showText(sf::RenderWindow *window) {
    catchNullptr(window, EXIT_FAILURE);

    for (int curButton = 0; curButton < this -> size; curButton++)
        ((this->array[curButton])->showText)(window);

    return EXIT_SUCCESS;
}

int ButtonManager::checkPression(sf::RenderWindow *window, const int buttonStatus) {
    Vect mousePosition = Vect(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);

    for (int curButton = 0; curButton < this -> size; curButton++)
        ((this->array[curButton])->checkIsPressed)(mousePosition, buttonStatus);

    return EXIT_SUCCESS;
}

//--------------------------------------------------------------------------------------------------------------------

AddTypeA::AddTypeA() {

}