#include "./Headers/Scene.h"

// #define DEBUG_
// #include "./Headers/Log.h"

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

    // TypeA  FirstMolecule(Vect(LEFT_WALL, piston.getPosition() + 100), 1, 12);
    // TypeB SecondMolecule(Vect(LEFT_WALL, piston.getPosition() + 100), 1, 24);

    MoleculeManager manager = MoleculeManager();

    for (int i = 0; i < 15; i++)
        manager.createTypeA(&piston);
    for (int i = 0; i < 10; i++)
        manager.createTypeB(&piston);

    sf::Clock clock;

    sf::Image       canvas;
    sf::Texture canvasTexture;
    sf::Sprite   canvasSprite;

    sf::Font font;
    font.loadFromFile("./Fonts/newFont.ttf");

    ButtonManager buttonManager = ButtonManager();

    Button addTypeA_button(Vect(121, 31), 240, 60, 0, 1, 0);
    addTypeA_button.setText("Type_A", 6, &font);

    Button addTypeB_button(Vect(121, 91), 240, 60, 1, 0, 0);
    addTypeB_button.setText("Type_B", 6, &font);

    buttonManager.addButton(&addTypeA_button);
    buttonManager.addButton(&addTypeB_button);

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

        piston.move(time);
        manager.update(time, piston.getPosition());

        window.clear();

            manager.draw(&canvas);
            
            buttonManager.draw(&canvas);
            addTypeA_button.draw(&canvas);

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