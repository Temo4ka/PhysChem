const signed WIDTH  = 1080;
const signed HEIGHT =  640;

#define sqr(a) ((a) * (a))

const double    TEST_LIGHT_X    = 100;
const double    TEST_LIGHT_Y    = 100;
const double    TEST_LIGHT_Z    = 300;

const double   TEST_CAMERA_Z    = 400;

const double TEST_SPHERE_RADIUS = 300;

const double ROTATION_VELOCITY = 1;


#define catchNullptr(POINTER, RETURN_IN_CASE_OF_FAILURE) {                                                         \
    if ((POINTER) == nullptr) {                                                                                     \
        fprintf(stderr, "%s pointer at %s at %s(%d) is NULL\n", #POINTER, __PRETTY_FUNCTION__, __FILE__, __LINE__);	 \
        return EXIT_FAILURE;                                                                                          \
    }                                                                                                                  \
}

