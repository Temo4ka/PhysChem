#include "../Headers/Scene.h"
#include <cmath>

Molecule::Molecule (const Vect startPos, const double weight) {

    int r1 = rand() % RANGE_X;
    int r2 = rand() % RANGE_Y;

    this -> position = Vect(startPos.x + r1, startPos.y + r2);

    this -> velocity = PISTON_VELOCITY + (rand() % MAX_START_VELOCITY);
    this ->  weight  =            weight            ;

    this -> dir.x = ((double) (1) / ((double) (rand() % 6 + 2)));
    this -> dir.y = sqrt(1 - SQR(this -> dir.y));

    return;
}

int Molecule::setPosition(const Vect newPos) {
    this -> position.x = newPos.x;
    this -> position.y = newPos.y;

    return EXIT_SUCCESS;
}

int Molecule::move(double deltaTime, const double PistonY) {
    this -> position = this -> position + (this -> dir * (deltaTime * this -> velocity));

    if (this -> position.x < LEFT_WALL) {
        this -> dir.x *= -1;
        this -> position.x = LEFT_WALL;
    }

    if (this -> position.x > RIGHT_WALL) {
        this -> dir.x *= -1;
        this -> position.x = RIGHT_WALL;
    }

    if (this -> position.y > WINDOW_HEIGHT) {
        this -> dir.y *= -1;
        this -> position.y = WINDOW_HEIGHT - 5;
    }

    if (this -> position.y <= PistonY) {
        this -> dir.y *= -1;
        this -> position.y = PistonY + 5;
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

int TypeA::draw(sf::Image *image) {
    catchNullptr(image, EXIT_FAILURE);

    Vect curPos = this -> getPosition();

    double x0 = curPos.x, y0 = curPos.y;
    double r = this -> radius;
    

    for (double x = x0 - r; x <= x0 + r; x++)
        for (double y = y0 - r; y <= y0 + r; y++) {
            if (SQR(x - x0) + SQR(y - y0) <= SQR(r)) {
                double k = 1 -  (SQR(x - x0) + SQR(y - y0)) / SQR(r);
                if (k > 1) k = 1;

                image -> setPixel(x, y, sf::Color(k * 255, k * 255, k * 255));
            }  else 
                image -> setPixel(x, y, sf::Color::Black);
        }

    return EXIT_SUCCESS;
}

//------------------------------------------------------------------------------------------------

int TypeB::draw(sf::Image *image) {
    catchNullptr(image, EXIT_FAILURE);

    Vect curPos = this -> getPosition();

    double x0 = curPos.x, y0 = curPos.y;
    double a = this -> len / 2;

    for (double x = x0 - a; x <= x0 + a; x++)
        for (double y = y0 - a; y <= y0 + a; y++) {
            double k = 1 -  (SQR(x - x0) + SQR(y - y0)) / SQR(a) + 0.3;
            if (k > 1) k = 1;

            image -> setPixel(x, y, sf::Color(0, k * 255, k * 255));
        }

    return EXIT_SUCCESS;
}


//------------------------------------CRINGE_MOMENT--------------------------------------------------------------------------------------

int TypeA::collide(TypeA *a, MoleculeManager *manager) {
    catchNulptr(   a   , NO_COLLISION);
    catchNulptr(manager, NO_COLLISION);

    Vect distV = this -> position - a -> getPosition();

    int dist = sqrt(SQR(distV.x) - SQR(distV.y));

    if (SQR(this -> getVelocity()) * this -> getWeight + SQR(a -> getVelocity()) * a -> getWeight() > REACTION_CONST &&
                                                                                               dist < this -> radius + a -> getRadius())
    {

        TypeB res = new TypeB(Vect(0, 0), a -> getWeight() + this -> weight, 20);
        res.setPosition(a -> getPosition() + distV * 0.5);

        manager -> addMolecule(&res);

        return COLLISION;
    } else if (dist < this -> radius + a -> getRadius()) {
        this -> reverseDir();
           a -> reverseDir();
    }


    return NO_COLLISION;
}

int TypeA::collide(TypeB *b, MoleculeManager *manager) {
    catchNulptr(   b   , NO_COLLISION);
    catchNulptr(manager, NO_COLLISION);

    Vect distV = this -> position - b -> getPosition();

    int dist = sqrt(SQR(distV.x) - SQR(distV.y));

    if (SQR(this -> getVelocity()) * this -> getWeight + SQR(b -> getVelocity()) * b -> getWeight() > REACTION_CONST &&
                                                                                               dist < this -> radius + b -> getLen())
    {

        TypeB res = new TypeB(Vect(0, 0), b -> getWeight() + this -> weight, 20);
        res.setPosition(b -> getPosition());

        manager -> addMolecule(&res);

        return COLLISION;
    } else if (dist < this -> radius + b -> getLen()){
        this -> reverseDir();
           b -> reverseDir();
    }


    return NO_COLLISION;
}

int TypeB::collide(TypeA *a, MoleculeManager *manager) {
    catchNulptr(   a   , NO_COLLISION);

    return a.collide(this, manager);
}

int TypeB::collide(TypeB *b, MoleculeManager *manager) {
    catchNulptr(   b   , NO_COLLISION);
    catchNulptr(manager, NO_COLLISION);

    Vect distV = this -> position - b -> getPosition();

    int dist = (distV.x > distV.y) ? distV.y : disV.x;

    if (SQR(this -> getVelocity()) * this -> getWeight + SQR(b -> getVelocity()) * b -> getWeight() > REACTION_CONST &&
                                                                                               dist < this -> len + b -> getLen())
    {
        
        for (int curMolecule = 0; curMolecule < b -> getWeight() + this -> weight; curMolecule++) {
            TypeA newMolecule = new TypeA(b -> getPosition() + distV * 0.5, 1, 12);
            manager -> addMolecule(&newMolecule);
        }

        return COLLISION;
    } else if (dist < this -> len + b -> getLen()){
        this -> reverseDir();
           b -> reverseDir();
    }


    return NO_COLLISION;
}

//----------------------------------------------------------------------------------------------------------------------------------------

MoleculeManager::MoleculeManager() {
    this -> size = 0;
    this -> array = new Molecule*[MAX_MOLEC_NUM];

    return;
}

MoleculeManager::~MoleculeManager() {
    delete[] this -> array;
    this -> size = -1;

    return;
}

int MoleculeManager::addMolecule(const Molecule *molecule) {
    catchNullptr(molecule, EXIT_FAILURE);
    if (this -> size == MAX_MOLEC_NUM) return EXIT_SUCCESS;

    this -> array[this -> size] = molecule;
    this -> size++;

    return EXIT_SUCCESS;
}

int MoleculeManager::swap(Molecule *a, Molecule *b) {
    catchNullptr(a, EXIT_FAILURE);
    catchNullptr(b, EXIT_FAILURE);

    Molecule c = *a;
    *a = *b;
    *b =  c;

    return EXIT_SUCCESS;
}

int MoleculeManager::eraseMolecule(const int ind) {
    if (ind >= this -> size || this -> size == 0) return EXIT_FAILURE;

    this -> swap(this -> array[ind], this -> array[this -> size - 1]);
    this -> size--;

    return EXIT_SUCCESS;
}

int MoleculeManager::update() {
    for (int firstPointer = 0; firstPointer < this -> size; firstPointer++)
        for (int secondPointer = firstPointer + 1; secondPointer < this -> size; secondPointer++) {
            Molecule *a = this -> array[firstPointer];
            Molecule *b = this -> array[secondPointer];

            if (a->collide(b, this)) {
                this -> eraseMolecule(secondPointer);               //  The order of the pointers erased is
                this -> eraseMolecule(firstPointer);                //             ESSENTIAL
            }

        }
}