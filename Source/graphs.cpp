#include "../Headers/Objects.h"
#include "../Headers/GraphConfig.h"

void Graph::drawBase(const Vect &position, const Vect &size, sf::Image *image, const sf::Font &font, std::vector<sf::Text> &textToDraw) {
    for (int x0 = 0; x0 < size.x; x0++)
        for (int y0 = 0; y0 < size.y; y0++)
            image->setPixel(position.x + x0, position.y + y0, colorScheme.GRAPH_BACKGROUND_COLOR);
    
    int x0 = position.x + size.x / 5; 
    for (int y = 0; y < size.y; y++)
        image -> setPixel(x0, position.y + y, colorScheme.GRAPH_LEGEND_COLOR);
    curX = x0;

    int y0 = position.y + 4 * size.y / 5;
    for (int x = 0; x < size.x; x++)
        image -> setPixel(x + position.x, y0, colorScheme.GRAPH_LEGEND_COLOR);

    Vect offside = Vect(4 * size.x / (5 * GRAPH_PARTS), 4 * size.y / (5 * GRAPH_PARTS));
    
    int charSize = std::min(size.y, size.x) / CHAR_COEFF;
    for (int curPart = 1; curPart < GRAPH_PARTS; curPart++) {
        textToDraw.push_back(getText(Vect(x0 + curPart * offside.x, position.y + size.y * 4 / 5 + 2), font,
                                                           std::to_string(MAX_X * curPart / GRAPH_PARTS), charSize));
    }
    for (int curPart = 1; curPart < GRAPH_PARTS; curPart++) {
        textToDraw.push_back(getText(Vect(position.x + size.x / 5 - std::to_string(MAX_Y).size() * charSize - 1, position.y + 4 * size.y / 5 - curPart * offside.y), font,
                                                           std::to_string(MAX_Y * curPart / GRAPH_PARTS), charSize));
    }

    showAllText(position, size, textToDraw, font);
}

void Graph::update(const double deltaTime, const int value) {
    timer -= deltaTime;
    curY = value;
}

void Graph::draw(const Vect &position, const Vect &size, sf::Image *image) {
    if (timer > 0) return;
    timer = GRAPHIC_TIMER;

    curX++;
    if (curX > position.x + size.x)
        curX = position.x + size.x / 5 + 1;

    for (int y = position.y; y < position.y + 4 * size.y / 5; y++) {
        if (y < position.y + size.y * 4 / 5 - curY * 4 * size.y / (5 * MAX_Y))
            image -> setPixel(curX, y, colorScheme.GRAPH_BACKGROUND_COLOR);
        else if (y >= position.y)
            image -> setPixel(curX, y,colorScheme.GRAPH_DIAGRAM_COLOR);

    }
    for (int x = position.x; x < position.x + size.x; x++)
        image -> setPixel(x, position.y, colorScheme.GRAPH_LEGEND_COLOR);

    for (int y = position.y; y < position.y + 4 * size.y / 5; y++) 
        image -> setPixel(curX + 1, y, colorScheme.GRAPH_LEGEND_COLOR);

    if (position.y + size.y * 4 / 5 - curY * 4 * size.y / (5 * MAX_Y) > 0 && position.y + size.y * 4 / 5 - curY * 4 * size.y / (5 * MAX_Y) > position.y)
        image -> setPixel(curX, position.y + size.y * 4 / 5 - curY * 4 * size.y / (5 * MAX_Y), colorScheme.GRAPH_LEGEND_COLOR);
}


void Graph::showAllText(const Vect &position, const Vect &size, std::vector<sf::Text> &textToDraw, const sf::Font &font) {
    int charSize = std::min(size.y, size.x) / CHAR_COEFF;

    textToDraw.push_back(getText(Vect(position.x + size.x - legendX.size() * charSize, position.y + size.y - charSize), font, legendX, charSize));
    textToDraw.push_back(getText(Vect(charSize, position.y + charSize), font, legendY, charSize));
    textToDraw.push_back(getText(Vect(charSize, position.y + size.y * 4 / 5 + charSize), font, name, std::min(charSize, charSize)));
}

sf::Text Graph::getText(const Vect &position, const sf::Font &font, const std::string text_, const size_t charSize) {
    sf::Text text = sf::Text(text_, font);
    text.setColor(GRAPH_LEGEND_COLOR);
    text.setPosition(position.x, position.y);
    text.setCharacterSize(charSize);

    return text;
}

