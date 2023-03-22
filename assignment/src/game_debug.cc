#include "game_debug.h"
#include "game_object.h"
#include "texture_manager.h"
#include "game_event.h"
#include "game_font_manage.h"

const char* DBG_TextureType(int id)
{
    switch ((eTextureType)id)
    {
    case eTEXTURE_BACKGROUND:
        return "BACKGROUND_TEXTURE";
    case eTEXTURE_APPLE:
        return "APPLE_TEXTURE";
    case eTEXTURE_BASKET:
        return "BASKET_TEXTURE";
    case eTEXTURE_BIRDS:
        return "BIRD_TEXTURE";
    case eTEXTURE_TREE_FORM_1:
        return "TREE_FORM_1_TEXTURE";
    case eTEXTURE_TREE_FORM_2:
        return "TREE_FORM_2_TEXTURE";
    case eTEXTURE_TREE_FORM_3:
        return "TREE_FORM_3_TEXTURE";
    case eTEXTURE_KIDS:
        return "KID_TEXTURE";
    case eTEXTURE_BUBBLE:
        return "BUBBLE_TEXTURE";
    case eTEXTURE_SIGN:
        return "SIGN_TEXTURE";
    case eTEXTURE_WATER_BUBBLE:
        return "WATER_BUBBLE_TEXTURE";

    default:
        return "UNREGISTERED_TEXTURE";
    }
}

const char* DBG_ObjectType(int obj_type)
{
    switch ((eGameObjectType) obj_type)
    {
    case eBACKGROUND_OBJECT:
        return "BACKGROUND_OBJECT";
    case eBASKET_OBJECT:
        return "BASKET_OBJECT";
    case eBIRD_OBJECT:
        return "BIRD_OBJECT";
    case eFRUIT_OBJECT:
        return "FRUIT_OBJECT";
    case eKID_OBJECT:
        return "KID_OBJECT";
    case eTREE_OBJECT:
        return "TREE_OBJECT";
    case eBUBBLE_OBJECT:
        return "BUBBLE_OBJECT";
    case eSIGN_OBJECT:
        return "SIGN_OBJECT";
    case eWATER_BUBBLE_OBJECT:
        return "WATER_BUBBLE_OBJECT";
    default:
        return "UNREGISTERED OBJECT";
    }
}

const char* DBG_EventType(int event)
{
    switch ((eGameEventEnum) event)
    {
    case eGAME_EVENT_UNSET:
        return "UNSET_EVENT";
    case eGAME_EVENT_MOUSE_DONW:
        return "MOUSE_DOWN_EVENT";
    case eGAME_EVENT_MOUSE_RELEASE:
        return "MOUSE_RELEASE_EVENT";
    case eGAME_EVENT_MOUSE_MOVE:
        return "MOUSE_MOVE_EVENT";
    case eGAME_EVENT_CONTACT_TARGET:
        return "CONTACT_TARGET_EVENT";
    case eGAME_EVENT_BIRD_FLY:
        return "BIRD_FLY_EVENT";
    case eGAME_EVENT_ALL_BIRD_OUT:
        return "ALL_BIRD_HAS_OUT";
    default:
        return "UNREGISTERED_MOUSE_EVENT";
    }
}

const char *DBG_FontType(int font)
{
    switch ((eGameFont) font)
    {
    case eDEFAULT_FONT:
        return "DEFAULT_FONT";
    case eDELUXE_FONT:
        return "DELUXE_FONT";
    default:
        return "UNREGISTERED FONT";
        break;
    }
}