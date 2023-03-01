#ifndef GAME_ENUM_H
#define GAME_ENUM_H

enum eTextureTypeList {
    eTEXTURE_BACKGROUND = 0,
    eTEXTURE_TREE_FORM_1 = 1,
    eTEXTURE_TREE_FORM_2 = 2,
    eTEXTURE_TREE_FORM_3 = 3,
    eTEXTURE_APPLE = 4,
    eTEXTURE_BASKET = 5,
    eTEXTURE_BIRDS = 6,
    eTEXTURE_KIDS = 7,
    eTEXTURE_TOTAL
};

enum eGameObjectType {
    eFRUIT_OBJECT = 0,
    eTREE_OBJECT = 1,
    eBASKET_OBJECT = 2,
    eBACKGROUND_OBJECT = 3,
    eBIRD_OBJECT = 4,
    eKID_OBJECT = 5,
    eTOTAL_OBJECT
};


enum eGameEventEnum {
    eGAME_EVENT_UNSET = 0,
    eGAME_EVENT_MOUSE_DONW,
    eGAME_EVENT_MOUSE_RELEASE,
    eGAME_EVENT_MOUSE_MOVE,
};

enum eGameObjectPhysic {
    ePHYSIC_STATIC = 0,
    ePHYSIC_DYNAMIC
};

enum ePhysicalShape {
    eCHAIN_SHAPE = 0,
    eCIRCEL_SHAPE,
    eEDGE_SHAPE,
    ePOLYGON_SHAPE
};

#endif /* GAME_ENUM_H*/