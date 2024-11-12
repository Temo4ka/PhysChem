#include "../Headers/Objects.h"
#include "../Headers/GraphConfig.h"

void Graph::drawBase(Vect &position, Vect &size, sf::Image *image, sf::Font &font, sf::RenderWindow *window) {
    for (int x0 = 0; x0 < size.x; x0++)
        for (int y0 = 0; y0 < size.y; y0++)
            image->setPixel(position.x + x0, position.y + y0, GRAPH_BACK_GROUND_COLOR);
    
    int x0 = position.x + size.x / 5; 
    for (int y = 0; y < size.y; y++)
        image -> setPixel(x0, position.y + y, GRAPH_BACKGROUND_COLOR);
    curX = x0;

    int y0 = position.y + 4 * size.y / 5;
    for (int x = 0; x < size.x; x++)
        image -> setPixel(x + position.x, y0, GRAPH_LEGEND_COLOR);

    Vect offside = Vect(4 * size.x / (5 * GRAPH_PARTS), 4 * size.y / (5 * GRAPH_PARTS));
    
    int charSize = size.y / 12;
    for (int curPart = 1; curPart < GRAPH_PARTS; curPart++) {
        window->draw(getText(Vect(x0 + curPart * offside.x, position.y + size.y - charSize - 1),
                                                           std::to_string(MAX_X * curPart / GRAPH_PARTS), charSize));
    }

    charSize = size.x / 12;
    for (int curPart = 1; curPart < GRAPH_PARTS; curPart++) {
        window->draw(getText(Vect(position.x, position.y + 4 * size.y / 5 - curPart * offside.y),
                                                           std::to_string(MAX_Y * curPart / GRAPH_PARTS), charSize));
    }

    showAllText(position, size, window, font);
}

void Graph::update(double deltaTime, int value) {
    timer -= deltatime;
    curY = value;
}

void Graph::draw(Vect &position, Vect &size, sf::Image *image) {
    if (timer > 0) return;
    timer = GRAPHIC_TIMER;

    curX++;
    if (curX > position.x + size.x)
        curX = position.x + size.x / 5;

    for (int y = position.y; y < position.y + 4 * size.y / 5; y++) {
        if (y < position.y + size.y * 4 / 5 - curY * 4 * size.y / (5 * MAX_Y))
            image -> setPixel(curX, y, GRAPH_DIAGRAM_COLOR);
        else 
            image -> setPixel(curX, y, GRAPH_BACKGROUND_COLOR);

    }
    for (int y = position.y; y < position.y + 4 * size.y / 5; y++) 
            image -> setPixel(curX + 1, y, GRAPH_LEGEND_COLOR);

    image -> setPixel(curX, position.y + size.y * 4 / 5 - curY * 4 * size.y / (5 * MAX_Y), GRAPH_LEGEND_COLOR);
}


void Graph::showAllText(Vect &position, Vect &size, sf::RenderWindow *window, sf::Font &font) {
    catchNullptr(window, EXIT_FAILURE);

    int charSizeX = size.y / 12;
    int charSizeY = size.x / 12;

    window->draw(getText(Vect(position.x + size.x - text.size * charSizeX, position.y + size.y - charSizeX), size, font, legendX, charSizeX));
    window->draw(getText(Vect(charSizeX, charSizeY), font, legendY, charSizeY));
    window->draw(getText(Vect(charSizeX, position.y + size.y - charSizeY), font, name, std::min(charSizeX, charSizeY));
}

sf::Text Graph::getText(const Vect &position, const sf::Font &font, const std::string text_, const size_t charSize) {
    sf::Text text = sf::Text(text_, font);
    time.setPosition(position.x, position.y);
    time.setCharacterSize(charSize);

    return text;
}

