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

        int draw(sf::Image *image, Light *light, Vision *vision);

        int setText(const char *text, const signed textSize, sf::Font *font);

        int showText(sf::RenderWindow *window);

        int checkIsPressed(const Vect mousePosition, const int buttonStatus);

        int getPression() { return isPressed; }

        virtual int run() { return EXIT_FAILURE; };

        ~Button() {}

};

class ManagerButton : public Button {
    ProgramManager *manager;

    public:
        ManagerButton(const Vect pos, const double w, const double h, const double r, const double g, const double b,
                                                                                                                ProgramManager *manager):
        Button(pos, w, h, r, g, b),
        manager (manager)
        {}
        
        ~ManagerButton() {}

        ProgramManager* getManager() { return this->manager; }

        int run() { return EXIT_FAILURE; }
};

class AddMolecule : public ManagerButton {

    public:
        AddMolecule(const Vect pos, const double w, const double h, const double r, const double g, const double b,
                                                                                                                ProgramManager *manager):
        ManagerButton(pos, w, h, r, g, b, manager)
        {}
        
        ~AddMolecule() {}

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

        int draw(sf::Image *image, Light *light, Vision *vision);

        int checkPression(sf::RenderWindow *window, const int buttonStatus);
};