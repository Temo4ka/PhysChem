#include "../Headers/Scene.h"
#include "../RayCasting/Headers/GraphicObjects.h"
#include <cmath>

// #define DEBUG_
// #include "../Headers/Log.h"

Molecule::Molecule (const Vect startPos, const double weight) {

    int r1 = rand() % RANGE_X - rand() % RANGE_X;
    int r2 = rand() % RANGE_Y - rand() % RANGE_Y;

    this -> position = Vect(startPos.x + r1, startPos.y + r2);

    double v = (PISTON_VELOCITY + (rand() % MAX_START_VELOCITY));

    this ->  weight  =            weight            ;

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

int Molecule::move(double deltaTime, const double PistonY) {
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

    if (this -> position.y <= PistonY) {
        this -> velocity.y *= -1;
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

int TypeA::collide(Molecule *m, MoleculeManager *manager) {
    catchNullptr(m, NO_COLLISION);

    // fprintf(logFile, "HERE1!\n");

    return (m->collide2)(this, manager);
}

int TypeB::collide(Molecule *m, MoleculeManager *manager) {
    catchNullptr(m, NO_COLLISION);

    // fprintf(logFile, "HERE2!\n");

    return (m->collide2)(this, manager);
}

int TypeA::collide2(TypeA *a, MoleculeManager *manager) {
    catchNullptr(   a   , NO_COLLISION);
    catchNullptr(manager, NO_COLLISION);

    Vect distV = this -> getPosition() - a -> getPosition();

    int dist = sqrt(SQR(distV.x) + SQR(distV.y));

    if ((this->getVelocity(), this->getVelocity()) * this->getWeight() + (a->getVelocity(), a->getVelocity()) * a->getWeight()
                                                                                                 > REACTION_CONST && dist < this->radius + a->getRadius())
    {

        TypeB *res = new TypeB(Vect(0, 0), a->getWeight() + this->getWeight(), BASE_TYPEB_RADIUS);
        res -> setPosition(a->getPosition() + distV * 0.5);
        res -> setVelocity(this->getVelocity() + a->getVelocity());

        manager -> addMolecule(res);

        return COLLISION;
    } else if (dist < this->radius + a->getRadius()) {
        this -> reverseDir();
           a -> reverseDir();
    }


    return NO_COLLISION;
}

int TypeA::collide2(TypeB *b, MoleculeManager *manager) {
    catchNullptr(   b   , NO_COLLISION);
    catchNullptr(manager, NO_COLLISION);

    Vect distV = this->getPosition() - b->getPosition();

    int dist = sqrt(SQR(distV.x) + SQR(distV.y));

    if ((this->getVelocity(), this->getVelocity()) * this->getWeight() + (b->getVelocity(), b->getVelocity()) * b->getWeight() &&
                                                                                         dist < this->radius + b->getLen())
    {

        TypeB *res = new TypeB(Vect(0, 0), b -> getWeight() + this->getWeight(), BASE_TYPEB_RADIUS);
        res -> setPosition(b -> getPosition());
        res -> setVelocity(this->getVelocity() + b->getVelocity());

        manager -> addMolecule(res);

        return COLLISION;
    } else if (dist < this->radius + b->getLen()){
        this -> reverseDir();
           b -> reverseDir();
    }


    return NO_COLLISION;
}

int TypeB::collide2(TypeA *a, MoleculeManager *manager) {
    catchNullptr(   a   , NO_COLLISION);

    return a->collide2(this, manager);
}

int TypeB::collide2(TypeB *b, MoleculeManager *manager) {
    catchNullptr(   b   , NO_COLLISION);
    catchNullptr(manager, NO_COLLISION);

    Vect distV = this->getPosition() - b->getPosition();

    int dist = sqrt(SQR(distV.x) + SQR(distV.y));

    if ((this->getVelocity(), this->getVelocity()) * this->getWeight() + (b->getVelocity(), b->getVelocity()) * b->getWeight() &&
                                                                                         dist < this->getLen() + b->getLen())
    {
        
        for (int curMolecule = 0; curMolecule < b -> getWeight() + this->getWeight(); curMolecule++) {
            TypeA *newMolecule = new TypeA(b -> getPosition() + distV * 0.5, 1, BASE_TYPEA_RADIUS);
            
            manager -> addMolecule(newMolecule);
        }

        return COLLISION;
    } else if (dist < this->getLen() + b->getLen()){
        this -> reverseDir();
           b -> reverseDir();
    }


    return NO_COLLISION;
}

//----------------------------------------------------------------------------------------------------------------------------------------

MoleculeManager::MoleculeManager(Piston *piston, Light *light, Vision *vision) {
    this -> vision = vision;
    this -> light  =  light; 
    this -> piston = piston;

    this -> size = 0;
    this -> array = new Molecule*[MAX_MOLEC_NUM];

    return;
}

MoleculeManager::~MoleculeManager() {
    for (int cur = 0; cur < MAX_MOLEC_NUM; cur++)
        delete this -> array[cur];

    delete[] this -> array;
    this -> size = -1;

    return;
}

int MoleculeManager::createTypeA(Piston *piston) {
    catchNullptr(piston, EXIT_FAILURE);
    
    TypeA *newMolecule = new TypeA(Vect(LEFT_WALL, piston->getPosition()), 1, BASE_TYPEA_RADIUS);

    this -> addMolecule(newMolecule);

    return EXIT_SUCCESS;
}

int MoleculeManager::createTypeB(Piston *piston) {
    catchNullptr(piston, EXIT_FAILURE);
    
    TypeB *newMolecule = new TypeB(Vect(LEFT_WALL, piston -> getPosition()), 1, BASE_TYPEB_RADIUS);
    this -> addMolecule(newMolecule);

    return EXIT_SUCCESS;
}

int MoleculeManager::addMolecule(Molecule *molecule) {
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

int MoleculeManager::swap(Molecule **a, Molecule **b) {
    catchNullptr(a, EXIT_FAILURE);
    catchNullptr(b, EXIT_FAILURE);

    Molecule *c = *a;
    *a = *b;
    *b =  c;

    return EXIT_SUCCESS;
}

int MoleculeManager::eraseMolecule(const int ind) {
    if (ind >= this -> size || this -> size <= 1) return EXIT_FAILURE;

    this -> swap(this->array + ind, this -> array + this->size - 1);
    this -> size--;

    return EXIT_SUCCESS;
}

int MoleculeManager::update(const double deltaTime) {
    double pistonY = (this->piston)->getPosition();

    for (int curMolecule = 0; curMolecule < this -> size; curMolecule++)
        (this -> array[curMolecule]) -> move(deltaTime, pistonY);
    
    // fprintf(logFile, "---------------------------------------\nSIZE:%d\n", this -> size);
    for (int firstPointer = 0; firstPointer < this -> size; firstPointer++)
        for (int secondPointer = firstPointer + 1; secondPointer < this -> size; secondPointer++) {
            Molecule *a = this -> array[firstPointer];
            Molecule *b = this -> array[secondPointer];


            if ((a->collide)(b, this) == COLLISION) {
                // fprintf(logFile, "\nSIZE:%d\n", this -> size);
                this -> eraseMolecule(secondPointer);               //  The order of the pointers erased is
                this -> eraseMolecule(firstPointer);                //             ESSENTIAL
                break;
            }

        }
    // fprintf(logFile, "\nSIZE:%d\n===================================\n", this -> size);
    
    
    return EXIT_SUCCESS;
}

int MoleculeManager::draw(sf::Image *image) {
    catchNullptr(image, EXIT_FAILURE);

    for (int curMolecule = 0; curMolecule < this -> size; curMolecule++)
        (this -> array[curMolecule]) -> draw(image, this -> light, this -> vision);

    return EXIT_SUCCESS;
}
