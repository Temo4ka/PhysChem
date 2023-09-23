#include "./Headers/Scene.h"

//----------------------------------------------------------\\
//                      Screen Sheme                       \\
//---------------------------------------------------------\\
//                           \        Free                 \\   
//      Buttons HERE         \             Space           \\    
//                           \=============================\\    
// --------------------------\=============================\\
//                           \                             \\             
//                           \                             \\
//       Graphics HERE       \       Reaction HERE         \\
//                           \                             \\
//                           \                             \\
//----------------------------------------------------------\\

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Reaction");

    Piston piston(Vect(PISTON_X, PISTON_Y), PISTON_WIDTH, PISTON_HEIGHT, PISTON_VELOCITY);

	Light light(Vect3(700, WINDOW_HEIGHT / 2, 100), WHITE_LIGHT);

    Vision vision(Vect3(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 500));

    MoleculeManager manager = MoleculeManager(&piston, &light, &vision);

    Time_Molecules graph1(Vect(0, 0), GRAPHIC_HEIGHT, GRAPHIC_WIDTH);

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

    if (organiseButtons(&buttonManager, &manager, &font) == EXIT_FAILURE) return EXIT_FAILURE;

    sf::Image graphCanvas;
    graphCanvas.create(720, 500, sf::Color::Black);

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

        graph1.update(time, manager.getSize(), &graphCanvas);

        window.clear();

            buttonManager.draw(&canvas, &light, &vision);
               manager   .draw(&canvas);

            canvasTexture.loadFromImage(canvas);
             canvasSprite.setTexture(canvasTexture);
            window.draw(canvasSprite);

            canvasTexture2.loadFromImage(graphCanvas);
             canvasSprite2.setTexture(canvasTexture2);
            canvasSprite2.setPosition(0, WINDOW_HEIGHT / 3 + 2);
            window.draw(canvasSprite2);

            piston.draw(&window); 
            buttonManager.showText(&window);
            graph1.showText(&window, &font);

            separateScreen(&window);

        window.display();
    }


    return EXIT_SUCCESS;
}