#ifndef GAME_CONSTANT_H
#define GAME_CONSTANT_H
    #define SCREEN_WIDTH (480)
    #define SCREEEN_HEIGHT (854)
    #define GROUND_POSITION (SCREEN_WIDTH - 100)

typedef enum kErrorCode {
    kSUCCESS = 0,
    kFAILED = -1,
    kTRY_AGAIN = -2,
    kNO_MEM = -3,
    kINVALID = -4,
    kUNKNOWN = -5
} ErrorCode_t;
#endif /* GAME CONSTANT */