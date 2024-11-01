#include "../Headers/Scene.h"
#include "../RayCasting/Headers/GraphicObjects.h"
#include <cmath>

Molecule::Molecule(const Vect &DownLeftCorner, const Vect &UpRightCorner, const double weight):
weight  (weight),
radius  (5),
velocity(),
position()
{
    const Vect RectSize = UpRightCorner - DownLeftCorner;
    const Vect startPos = DownLeftCorner + Vect(radius, radius);
    const Vect Offset(
        rand() % (unsigned long long) (RectSize.x - radius + 1),
        rand() % (unsigned long long) (RectSize.y - radius + 1)
    );

    position = startPos + Offset;

    double v = (PISTON_VELOCITY + (rand() % MAX_START_VELOCITY));

    velocity.x = (((double) (1) / ((double) (rand() % 6 + 2))));
    velocity.y = (sqrt(1 - SQR(velocity.x)));

    velocity = velocity * v;

    if (rand() % 2) velocity = velocity * (-1);

    return;
}

//------------------------------------------------------------------------------------------------

int Molecule::draw(sf::Image *image, Light *light, Vision *vis) {
    catchNullptr(image, EXIT_FAILURE);
    catchNullptr(light, EXIT_FAILURE);
    catchNullptr( vis , EXIT_FAILURE);

    double x0 = getPosition().x, y0 = getPosition().y;
    double r = radius;

    Sphere curSphere(Vect3(x0, y0, 0), r, Vect3(0.3, 0.3, 0.3));
    

    for (double x = x0 - r; x <= x0 + r; x++)
        for (double y = y0 - r; y <= y0 + r; y++) {
            if (SQR(x - x0) + SQR(y - y0) <= SQR(r)) {
                double k = 1 - (SQR(x - x0) + SQR(y - y0)) / SQR(r);
                if (k > 1) k = 1;

                Vect3 curColor(0, 0, k);
                curSphere.setMaterial(curColor);

                double z = sqrt(SQR(r) - SQR(x - x0) - SQR(y - y0));

                image -> setPixel(x, y, getPixelColor(&curSphere, light, vis, Vect3(x - x0, y - y0, z)));
            }
        }

    return EXIT_SUCCESS;
}

//------------------------------------CRINGE_MOMENT--------------------------------------------------------------------------------------

void Gas::collideMolecules(Molecule &a, Molecule &b) {
    Vect distV = b.getPosition() - a.getPosition();

    double dist = sqrt(SQR(distV.x) + SQR(distV.y));

    if (dist < b.radius + a.radius) {

        Vect velocPrA = (distV, a.velocity) /  dist;
        Vect velocPrB = (distV, b.velocity) / -dist;

        if (velocPrA + velocPrB > 0) {
            
        }
    }

    return;
}

int Gas::collideWalls(Molecule &molecule) {
     if (molecule.position.x < LEFT_WALL + 5) {
        molecule.velocity.x *= -1;
        molecule.position.x = LEFT_WALL + 5;

        return 1;
    }

    if (molecule.position.x > RIGHT_WALL) {
        molecule.velocity.x *= -1;
        molecule.position.x = RIGHT_WALL - 3;

        return 1;
    }

    if (molecule.position.y > WINDOW_HEIGHT) {
        molecule.velocity.y *= -1;
        molecule.position.y = WINDOW_HEIGHT - 5;

        return 1;
    }

    if (molecule.position.y <= CEILING) {
        molecule.velocity.y *= -1;
        molecule.position.y = CEILING + 5;

        return 1;
    }

    return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------

int Gas::update(const double deltaTime) {
    for (auto curMolecule : molecules)
        curMolecule.move(deltaTime);
    
    // fprintf(logFile, "---------------------------------------\nSIZE:%d\n", this -> size);
    for (int firstPointer = 0; firstPointer < molecules.size(); firstPointer++) {
        for (int secondPointer = firstPointer + 1; secondPointer < molecules.size(); secondPointer++) {
            collideMolecules(molecules[firstPointer], molecules[secondPointer]);
        }
        collideWalls(molecules[firstPointer]);
    }
    // fprintf(logFile, "\nSIZE:%d\n===================================\n", this -> size);
    
    
    return EXIT_SUCCESS;
}

int Gas::draw(sf::Image *image, Light *light, Vision *vision) {
    for (auto curMolecule : molecules)
        curMolecule.draw(image, light, vision);

    return EXIT_SUCCESS;
}
