#pragma once

const signed WINDOW_WIDTH  = 1440;
const signed WINDOW_HEIGHT = 720;

const int MAX_START_VELOCITY  = 500;

const double REACTION_CONST  =  1000;

const double  PISTON_WIDTH = WINDOW_WIDTH / 2 - 2;

const double    PISTON_X   = WINDOW_WIDTH / 2 + 3;

const double    PISTON_Y   =          20         ;

const double PISTON_HEIGHT = 30;

const double PISTON_VELOCITY = 30;

const double PISTON_LIMIT = WINDOW_HEIGHT - 120;

const double LEFT_WALL = WINDOW_WIDTH / 2 + 10;

const double RIGHT_WALL = WINDOW_WIDTH - 5;

const signed RANGE_X = 50;
const signed RANGE_Y = 50;

const double DELTA_PISTON = 12;

const signed  MAX_MOLEC_NUM = 120;
const signed MAX_BUTTON_NUM =  40;

const signed BASE_TYPEA_RADIUS = 12;
const signed BASE_TYPEB_RADIUS = 24;

const double GRAPHIC_TIMER = 1;

const int GRAPHIC_WIDTH  = 700;
const int GRAPHIC_HEIGHT = 100;

#define catchNullptr(POINTER, RETURN_IN_CASE_OF_FAILURE) {                                                         \
    if ((POINTER) == nullptr) {                                                                                     \
        fprintf(stderr, "%s pointer at %s at %s(%d) is NULL\n", #POINTER, __PRETTY_FUNCTION__, __FILE__, __LINE__);	 \
        return RETURN_IN_CASE_OF_FAILURE;                                                                             \
    }                                                                                                                  \
}

#define SQR(a) ((a) * (a))
