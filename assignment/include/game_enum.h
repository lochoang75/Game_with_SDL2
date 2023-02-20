#ifndef GAME_ENUM_H
#define GAME_ENUM_H

enum eTextureTypeList {
    eTEXTURE_BACKGROUND = 0,
    eTEXTURE_TREE_FORM_1 = 1,
    eTEXTURE_TREE_FORM_2 = 2,
    eTEXTURE_TREE_FORM_3 = 3,
    eTEXTURE_APPLE = 4,
    eTEXTURE_BASKET = 5,
    eTEXTURE_TOTAL = 6
};

enum eGameObjectType {
    eFRUIT_OBJECT = 0,
    eTREE_OBJECT = 1,
    eBASKET_OBJECT = 2,
    eBACKGROUND_OBJECT = 3,
    eTOTAL_OBJECT = 4
};

enum eGameEventEnum {
    eGAME_EVENT_UNSET = 0,
    eGAME_EVENT_MOUSE_DONW,
    eGAME_EVENT_MOUSE_RELEASE,
    eGAME_EVENT_MOUSE_MOVE,
};

#endif /* GAME_ENUM_H*/