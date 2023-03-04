#ifndef GAME_CONSTANT_H
#define GAME_CONSTANT_H
#include <cmath>
    #define SCREEN_WIDTH (840)
    #define SCREEN_HEIGHT (480)
    #define GROUND_POSITION (SCREEN_HEIGHT - 100)
    #define MAX_CONTACT_HANDLER (20)

    const int MET2PIX = (60);
    const int SCALED_WIDTH = (SCREEN_WIDTH/ MET2PIX);
    const int SCALED_HEIGHT = (SCREEN_HEIGHT/ MET2PIX);
    const float RAD2DEG = 180/M_PI;

typedef enum kErrorCode {
    kSUCCESS = 0,
    kFAILED = -1,
    kTRY_AGAIN = -2,
    kNO_MEM = -3,
    kINVALID = -4,
    kUNKNOWN = -5
} ErrorCode_t;

enum _ObjectPhysicCategoryEnum {
    kGROUND = 0x0001,
    kFRUIT = 0x0002,
    kBIRD = 0x0004,
    kTREE = 0x0008,
};
#endif /* GAME CONSTANT */