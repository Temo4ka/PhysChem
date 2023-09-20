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

    // TypeA  FirstMolecule(Vect(LEFT_WALL, piston.getPosition() + 100), 1, 12);
    // TypeB SecondMolecule(Vect(LEFT_WALL, piston.getPosition() + 100), 1, 24);

    MoleculeManager manager = MoleculeManager();

    manager.createTypeA(&piston);
    manager.createTypeA(&piston);
    manager.createTypeB(&piston);
    manager.createTypeA(&piston);
    manager.createTypeA(&piston);
    manager.createTypeA(&piston);
    manager.createTypeA(&piston);
    manager.createTypeA(&piston);
    manager.createTypeA(&piston);
    manager.createTypeA(&piston);
    manager.createTypeA(&piston);
    manager.createTypeA(&piston);
    manager.createTypeA(&piston);
    manager.createTypeA(&piston);
    manager.createTypeA(&piston);
    manager.createTypeA(&piston);
    manager.createTypeA(&piston);
    manager.createTypeA(&piston);
    manager.createTypeA(&piston);
    manager.createTypeA(&piston);
    manager.createTypeA(&piston);
    manager.createTypeA(&piston);
    manager.createTypeB(&piston);
    manager.createTypeB(&piston);
    manager.createTypeB(&piston);
    manager.createTypeB(&piston);
    manager.createTypeB(&piston);
    manager.createTypeB(&piston);
    manager.createTypeB(&piston);
    manager.createTypeB(&piston);

    sf::Clock clock;

    sf::Image       canvas;
    sf::Texture canvasTexture;
    sf::Sprite   canvasSprite;
    

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        canvas.create(2 * WINDOW_WIDTH, 2 * WINDOW_HEIGHT, sf::Color::Black);


        double time = clock.getElapsedTime().asSeconds();
        clock.restart();

        piston.move(time);
        manager.update(time, piston.getPosition());

        window.clear();

            manager.draw(&canvas);

            canvasTexture.loadFromImage(canvas);
             canvasSprite.setTexture(canvasTexture);

            window.draw(canvasSprite);

            piston.draw(&window); 
            separateScreen(&window);

        window.display();
    }


    return EXIT_SUCCESS;
}