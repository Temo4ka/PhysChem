#include "./Headers/Objects.h"

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

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.display();
    }

    return EXIT_SUCCESS;
}