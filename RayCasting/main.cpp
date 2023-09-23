#include <SFML/Graphics.hpp>
#include <cmath>
#include "headers/Config.h"
#include "headers/GraphicObjects.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "The way to ray tracing");

	Sphere sphere(Vect(WIDTH / 2, HEIGHT / 2, 0), TEST_SPHERE_RADIUS, TEST_MATERIAL);

	Light light(Vect(TEST_LIGHT_X, TEST_LIGHT_Y, TEST_LIGHT_Z), WHITE_LIGHT);

	Vision vision(Vect(WIDTH / 2, HEIGHT / 2, TEST_CAMERA_Z));

	sf::Image canvas;
	canvas.create(WIDTH, HEIGHT);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

		scanForSphere(&canvas, &sphere, &light, &vision);

		sf::Texture texture;
		texture.loadFromImage(canvas);

		sf::Sprite sprite;
		sprite.setTexture(texture);

        window.clear();
		window.draw(sprite);
        window.display();
    }

    return 0;
}