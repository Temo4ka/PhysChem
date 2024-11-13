#include "./Headers/Scene.h"
#include <iostream>

//---------------------------------------------------------\\
//                      Screen Sheme                       \\
//---------------------------------------------------------\\
//                           \                             \\
//      Buttons HERE         \                             \\
//                           \                             \\
// --------------------------\          Reaction           \\
//                           \                             \\
//                           \                             \\
//       Graphics HERE       \                             \\
//                           \                             \\
//                           \                             \\
//---------------------------------------------------------\\

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Reaction");

	Light light(Vect3(700, WINDOW_HEIGHT / 2, 100), WHITE_LIGHT);

    Vision vision(Vect3(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 500));

    ProgramManager manager = ProgramManager(Vect(WINDOW_WIDTH / 2, 0), Vect(WINDOW_WIDTH, WINDOW_HEIGHT), &light, &vision);

    // for (int i = 0; i < 15; i++)
    //     manager.createTypeA(&piston);
    // for (int i = 0; i < 10; i++)
    //     manager.createTypeB(&piston);

    sf::Clock clock;

    sf::Image       canvas;
    sf::Texture canvasTexture2;
    sf::Texture canvasTexture;
    sf::Sprite   canvasSprite;
    sf::Sprite   canvasSprite2;

    sf::Font font;
    font.loadFromFile("./Fonts/newFont.ttf");

    ButtonManager buttonManager = ButtonManager();

    GraphManager graphManager = GraphManager(Vect(0, 0), Vect(WINDOW_WIDTH / 2, 2 * WINDOW_HEIGHT / 3));

    if (organiseButtons(&buttonManager, &manager, &font) == EXIT_FAILURE) return EXIT_FAILURE;

    sf::Image graphCanvas;
    graphCanvas.create(720, 500, sf::Color::Black);

    std::vector<sf::Text> textToDraw;
    graphManager.init(&graphCanvas, font, textToDraw);
    for (auto &text : textToDraw) {
        sf::Vector2f pos = text.getPosition();
        text.setPosition(pos.x, pos.y + WINDOW_HEIGHT / 3 + 2);
    }

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                buttonManager.checkPression(&window, BUTTON_PRESSED);
            }

            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
                buttonManager.checkPression(&window, BUTTON_NOT_PRESSED);            
        }

        canvas.create(2 * WINDOW_WIDTH, 2 * WINDOW_HEIGHT, sf::Color::Black);


        double time = clock.getElapsedTime().asSeconds();
        clock.restart();

        // piston.move(time);
        light.rotate(time, Vect3(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 100));
        manager.update(time);

        graphManager.update(GraphManager::GraphTypes::PRESSURE, time, (int) manager.gas.get_pressure().val_);
        graphManager.update(GraphManager::GraphTypes::H, time, (int) manager.gas.get_gas_group(Molecule::H).kinetic_energy.val_);
        graphManager.update(GraphManager::GraphTypes::N, time, (int) manager.gas.get_gas_group(Molecule::N).kinetic_energy.val_);
        graphManager.update(GraphManager::GraphTypes::F, time, (int) manager.gas.get_gas_group(Molecule::F).kinetic_energy.val_);

        graphManager.draw(&graphCanvas);
        buttonManager.draw(&canvas, &light, &vision);
            manager   .draw(&canvas);

        window.clear();

            canvasTexture.loadFromImage(canvas);
                canvasSprite.setTexture(canvasTexture);
            window.draw(canvasSprite);

            canvasTexture2.loadFromImage(graphCanvas);
                canvasSprite2.setTexture(canvasTexture2);
            canvasSprite2.setPosition(0, WINDOW_HEIGHT / 3 + 2);
            window.draw(canvasSprite2);

            separateScreen(&window);

            buttonManager.showText(&window);
            for (auto text : textToDraw)
                window.draw(text);

        window.display();
    }


    return EXIT_SUCCESS;
}