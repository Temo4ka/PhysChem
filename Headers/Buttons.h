#pragma once

#include "Objects.h"

class Button {
    Vect   position;
    
    double    width;
    double   height;

    double r;
    double g;
    double b;

    int isPressed;

    sf::Text text;

    public:
        Button(const Vect pos, const double w, const double h, const double r, const double g, const double b) :
                position (pos),
                                     width (w),
                                                    height (h),
                                                                         r (r),
                                                                                         g (g),
                                                                                                         b (b),
        isPressed (0)
        {}

        int draw(sf::Image *image);

        int setText(const char *text, const signed textSize, sf::Font *font);

        int showText(sf::RenderWindow *window);

        int checkIsPressed(const Vect mousePosition, const int buttonStatus);

        int getPression() { return this->isPressed; }

        virtual int run() { return EXIT_FAILURE; };

        ~Button() {}

};

class ManagerButton : public Button {
    MoleculeManager *manager;

    public:
        ManagerButton(const Vect pos, const double w, const double h, const double r, const double g, const double b,
                                                                                                                MoleculeManager *manager):
        Button(pos, w, h, r, g, b),
        manager (manager)
        {}
        
        ~ManagerButton() {}

        MoleculeManager* getManager() { return this->manager; }

        int run() { return EXIT_FAILURE; }
};

class AddTypeA : public ManagerButton {

    public:
        AddTypeA(const Vect pos, const double w, const double h, const double r, const double g, const double b,
                                                                                                                MoleculeManager *manager):
        ManagerButton(pos, w, h, r, g, b, manager)
        {}
        
        ~AddTypeA() {}

        int run();
};

class AddTypeB : public ManagerButton {

    public:
        AddTypeB(const Vect pos, const double w, const double h, const double r, const double g, const double b,
                                                                                                                MoleculeManager *manager):
        ManagerButton(pos, w, h, r, g, b, manager)
        {}
        
        ~AddTypeB() {}

        int run();
};


class MoveUp : public ManagerButton {

    public:
        MoveUp(const Vect pos, const double w, const double h, const double r, const double g, const double b,
                                                                                                                MoleculeManager *manager):
        ManagerButton(pos, w, h, r, g, b, manager)
        {}
        
        ~MoveUp() {}

        int run();
};

class MoveDown : public ManagerButton {

    public:
        MoveDown(const Vect pos, const double w, const double h, const double r, const double g, const double b, 
                                                                                                            MoleculeManager *manager):
        ManagerButton(pos, w, h, r, g, b, manager)
        {}
        
        ~MoveDown() {}

        int run();
};

class ButtonManager {
    signed size;

    Button **array;

    public:
        ButtonManager();
        ~ButtonManager();

        int addButton(Button *button);

        int showText(sf::RenderWindow *window);

        int draw(sf::Image *image);

        int checkPression(sf::RenderWindow *window, const int buttonStatus);
};