#ifndef GAME_CONSTANT_H
#define GAME_CONSTANT_H
#include <cmath>
    #define SCREEN_WIDTH (840)
    #define SCREEN_HEIGHT (480)
    #define GROUND_POSITION (SCREEN_HEIGHT - 100)
    #define MAX_CONTACT_HANDLER (20)
    #define MAX_ANSWER_BUBBLE (10)

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
    kGROUND = 0x0001 << 0,
    kFRUIT = 0x0001 << 1,
    kBIRD = 0x0001 << 2,
    kTREE = 0x0001 << 3,
    kSIGN = 0x0001 << 4
};
#endif /* GAME CONSTANT */