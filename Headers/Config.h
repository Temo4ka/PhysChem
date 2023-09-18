#pragma once

const signed WINDOW_WIDTH  = 1440;
const signed WINDOW_HEIGHT = 720;

const int MAX_START_VELOCITY  = 20;

const double REACTION_CONST  = 4;

const double  PISTON_WIDTH = WINDOW_WIDTH / 2 - 2;

const double    PISTON_X   = WINDOW_WIDTH / 2 + 3;

const double PISTON_HEIGHT = 30;

const double PISTON_VELOCITY = 80;

#define catchNullptr(POINTER, RETURN_IN_CASE_OF_FAILURE) {                                                         \
    if ((POINTER) == nullptr) {                                                                                     \
        fprintf(stderr, "%s pointer at %s at %s(%d) is NULL\n", #POINTER, __PRETTY_FUNCTION__, __FILE__, __LINE__);	 \
        return RETURN_IN_CASE_OF_FAILURE;                                                                             \
    }                                                                                                                  \
}

#define SQR(a) ((a) * (a))
