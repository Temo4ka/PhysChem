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

    Piston piston(Vect(PISTON_X, 0), PISTON_WIDTH, PISTON_HEIGHT, PISTON_VELOCITY);
    
    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        separateScreen(&window);
        piston.draw(&window);

        piston.move(clock.getElapsedTime().asSeconds());
        clock.restart();

        window.display();
    }


    return EXIT_SUCCESS;
}