#include "./Headers/Scene.h"

//-----------------------------------------------------------
//                      Screen Sheme                        
//----------------------------------------------------------\
//                           \        Free                 \    
//      Buttons HERE         \             Space           \     
//                           \=============================\     
// --------------------------\=============================\ 
//                           \                             \             
//                           \                             \ 
//       Graphics HERE       \       Reaction HERE         \ 
//                           \                             \ 
//                           \                             \
//----------------------------------------------------------\

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Reaction");

    Piston piston(Vect(PISTON_X, PISTON_Y), PISTON_WIDTH, PISTON_HEIGHT, PISTON_VELOCITY);

    MoleculeManager manager = MoleculeManager(&piston);

    // for (int i = 0; i < 15; i++)
    //     manager.createTypeA(&piston);
    // for (int i = 0; i < 10; i++)
    //     manager.createTypeB(&piston);

    sf::Clock clock;

    sf::Image       canvas;
    sf::Texture canvasTexture;
    sf::Sprite   canvasSprite;

    sf::Font font;
    font.loadFromFile("./Fonts/newFont.ttf");

    ButtonManager buttonManager = ButtonManager();

    if (organiseButtons(&buttonManager, &manager, &font) == EXIT_FAILURE) return EXIT_FAILURE;

    while (window.isOpen()) {
        FILE* logFile = freopen("logFile", "w", stdout);
        fprintf(logFile, "%d active Molecules\n", manager.getSize());
        fclose(logFile);

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

        piston.move(time);
        manager.update(time);

        window.clear();

            manager.draw(&canvas);
            
            buttonManager.draw(&canvas);

            canvasTexture.loadFromImage(canvas);
             canvasSprite.setTexture(canvasTexture);

            window.draw(canvasSprite);

            piston.draw(&window); 
            buttonManager.showText(&window);
            separateScreen(&window);

        window.display();
    }


    return EXIT_SUCCESS;
}