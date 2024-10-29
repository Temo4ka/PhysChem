#include "../Headers/Scene.h"
#include "../RayCasting/Headers/GraphicObjects.h"
#include <cmath>

// #define DEBUG_
// #include "../Headers/Log.h"

Molecule::Molecule (const Vect &startPos, const double weight) {

    int r1 = rand() % RANGE_X - rand() % RANGE_X;
    int r2 = rand() % RANGE_Y - rand() % RANGE_Y;

    this -> position = Vect(startPos.x + r1, startPos.y + r2);

    double v = (PISTON_VELOCITY + (rand() % MAX_START_VELOCITY));

    this -> weight = weight;

    this -> velocity.x = (((double) (1) / ((double) (rand() % 6 + 2))));
    this -> velocity.y = (sqrt(1 - SQR(this -> velocity.x)));

    this -> velocity = this -> velocity * v;

    if (rand() % 2) this->velocity.x *= -1;
    if (rand() % 2) this->velocity.y *= -1;

    return;
}

int Molecule::setPosition(const Vect newPos) {
    this -> position.x = newPos.x;
    this -> position.y = newPos.y;

    return EXIT_SUCCESS;
}

int Molecule::move(double deltaTime, const double CEILING) {
    this -> position = this -> position + (this -> velocity * deltaTime);

    if (this -> position.x < LEFT_WALL + 5) {
        this -> velocity.x *= -1;
        this -> position.x = LEFT_WALL + 5;
    }

    if (this -> position.x > RIGHT_WALL) {
        this -> velocity.x *= -1;
        this -> position.x = RIGHT_WALL - 3;
    }

    if (this -> position.y > WINDOW_HEIGHT) {
        this -> velocity.y *= -1;
        this -> position.y = WINDOW_HEIGHT - 5;
    }

    if (this -> position.y <= CEILING) {
        this -> velocity.y *= -1;
        this -> position.y = CEILING + 5;
    }

    return EXIT_SUCCESS;
}

int Molecule::absorb(Molecule *molecule) {
    catchNullptr(molecule, EXIT_FAILURE);

    this -> weight += molecule->getWeight();

    delete molecule;

    return EXIT_SUCCESS;
}

//------------------------------------------------------------------------------------------------

int TypeA::draw(sf::Image *image, Light *light, Vision *vis) {
    catchNullptr(image, EXIT_FAILURE);

    Vect curPos = this -> getPosition();

    double x0 = curPos.x, y0 = curPos.y;
    double r = this -> radius;

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

//------------------------------------------------------------------------------------------------

int TypeB::draw(sf::Image *image, Light *light, Vision *vis) {
    catchNullptr(image, EXIT_FAILURE);

    Vect curPos = this -> getPosition();

    double x0 = curPos.x, y0 = curPos.y;
    double a = this -> len / 2;

    Sphere curSphere(Vect3(x0, y0, 0), a, Vect3(1, 1, 1));

    for (double x = x0 - a; x <= x0 + a; x++)
        for (double y = y0 - a; y <= y0 + a; y++) {
            if (SQR(x - x0) + SQR(y - y0) <= SQR(a)) {
                double k = 1 - (SQR(x - x0) + SQR(y - y0)) / SQR(a) + 0.3;
                if (k > 1) k = 1;

                Vect3 curColor(k, 0, k);
                curSphere.setMaterial(curColor);

                double z = sqrt(SQR(a) - SQR(x - x0) - SQR(y - y0));

                image -> setPixel(x, y, getPixelColor(&curSphere, light, vis, Vect3(x - x0, y - y0, z)));
            } else {
                double k = 1 - (SQR(x - x0) + SQR(y - y0)) / SQR(a) + 0.3;
                if (k > 1) k = 1;

                image -> setPixel(x, y, sf::Color(0, k * 255, k * 255));
            }
        }

    return EXIT_SUCCESS;
}


//------------------------------------CRINGE_MOMENT--------------------------------------------------------------------------------------

void Gas::collide(Molecule &a, Molecule &b) {
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
     if (molecule.getPosition().x < LEFT_WALL + 5) {
        molecule.velocity.x *= -1;
        molecule.getPosition().x = LEFT_WALL + 5;

        return 1;
    }

    if (molecule.getPosition().x > RIGHT_WALL) {
        molecule.velocity.x *= -1;
        molecule.getPosition().x = RIGHT_WALL - 3;

        return 1;
    }

    if (molecule.getPosition().y > WINDOW_HEIGHT) {
        molecule.velocity.y *= -1;
        molecule.getPosition().y = WINDOW_HEIGHT - 5;

        return 1;
    }

    if (molecule.getPosition().y <= CEILING) {
        molecule.velocity.y *= -1;
        molecule.getPosition().y = CEILING + 5;

        return 1;
    }

    return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------

ProgramManager::ProgramManager(Piston *piston, Light *light, Vision *vision) {
    this -> vision = vision;
    this -> light  =  light; 
    this -> piston = piston;

    return;
}

int ProgramManager::addMolecule(Molecule *molecule) {
    catchNullptr(molecule, EXIT_FAILURE);
    if (this -> size == MAX_MOLEC_NUM) return EXIT_SUCCESS;

    Vect pos = molecule->getPosition();

    if (pos.x <= LEFT_WALL + 20)  pos.x =  LEFT_WALL + 20;
    if (pos.x >= RIGHT_WALL) pos.x = RIGHT_WALL;

    if (pos.y >= WINDOW_HEIGHT - 20)    pos.y = WINDOW_HEIGHT - 20;
    if (pos.y <= piston->getPosition()) pos.y = piston->getPosition() + 20;

    molecule -> setPosition(pos);

    this -> array[this -> size] = molecule;
    this -> size++;

    return EXIT_SUCCESS;
}

int Gas::update(const double deltaTime) {
    for (auto curMolecule : molecules)
        curMolecule->move(deltaTime);
    
    // fprintf(logFile, "---------------------------------------\nSIZE:%d\n", this -> size);
    for (int firstPointer = 0; firstPointer < molecules.size; firstPointer++) {
        for (int secondPointer = firstPointer + 1; secondPointer < molecules.size; secondPointer++) {
            collide(molecules[firstPointer], molecules[secondPointer]);
        }
        collideWalls(molecules[firstPointer]);
    }
    // fprintf(logFile, "\nSIZE:%d\n===================================\n", this -> size);
    
    
    return EXIT_SUCCESS;
}

int ProgramManager::draw(sf::Image *image) {
    catchNullptr(image, EXIT_FAILURE);

    for (int curMolecule = 0; curMolecule < molucules.size(); curMolecule++)
        (this -> array[curMolecule]) -> draw(image, light, vision);

    return EXIT_SUCCESS;
}
