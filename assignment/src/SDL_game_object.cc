#include "SDL_game_object.h"
#include "vec2.h"

void SDLGameObject:: load(const LoaderParams *pParams)
{
    mWidth = pParams->get_width();
    mHeight = pParams->get_height();
    x = pParams->get_x();
    y = pParams->get_y();
    id = pParams->get_type();
    ErrorCode_t ret = create_object_body();
    if (ret != kSUCCESS)
    {
        LogError("Unable to create body for object type %s", DBG_ObjectType(mType));
    }

    if (pParams->is_create_fixture())
    {
        ret = create_object_fixture();
        if (ret != kSUCCESS)
        {
            LogError("Unable to create fixture for object type %s", DBG_ObjectType(mType));
        }
    }
    mMass = mBody->GetMass();
    // LogDebug("Loaded successful object mass is: %0.4f", mMass);
}

void SDLGameObject::draw()
{
    double angle = Box2DPhysicalFacade::get_angle(mBody);
    float pos_x, pos_y;
    Box2DPhysicalFacade::get_current_position(mBody, pos_x, pos_y);
    Box2DPhysicalFacade::compute_pixel_postion(pos_x, pos_y, mWidth, mHeight, x, y);
    SDL_Rect src_rect;
    src_rect.x = 0;
    src_rect.y = 0;
    src_rect.w = mWidth;
    src_rect.h = mHeight;
    SDL_Renderer *p_renderer = Game::Instance()->get_renderer();
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    GameTexture *texture = TextureManager::Instance()->get_texture(id);
    if (texture == NULL)
    {
        LogError("Error occur when get texture for id %s", DBG_TextureType(id));
    }
    else
    {
        // LogDebug("Draw object %d at x: %0.4f, y: %0.4f, w: %d, height: %d", id, pos_x, pos_y, mWidth, mHeight);
        texture->draw(x, y, &src_rect, angle, p_renderer, flip);
    }
    return;
}

void SDLGameObject:: clean_up()
{
    Box2DPhysicalFacade::destroy_body(mBody);
}

ErrorCode_t SDLGameObject::create_object_body()
{
    LogDebug("Create body for object %s", DBG_ObjectType(mType));
    b2BodyDef body_def;
    float body_x, body_y;
    Box2DPhysicalFacade::compute_cartesian_origin(x, y, mWidth, mHeight, body_x, body_y);

    body_def.type = b2_staticBody;
    body_def.position.Set(body_x, body_y);
    body_def.userData.pointer = reinterpret_cast<uintptr_t> (this);
    mBody = Box2DPhysicalFacade::create_body(body_def);
    if (mBody == NULL)
    {
        return kNO_MEM;
    }

    return kSUCCESS;
}

ErrorCode_t SDLGameObject::create_object_fixture()
{
    LogDebug("Get fixture definition for object %s", DBG_ObjectType(mType));
    b2FixtureDef fixture_def;
    b2PolygonShape shape;
    fixture_def.shape = &shape;
    fixture_def.density = 1.0;
    Box2DPhysicalFacade::create_fixture(mBody, fixture_def);
    return kSUCCESS;
}

void SDLGameObject:: get_position(int &x, int &y) const
{
    x = this->x;
    y = this->y;
}

void SDLGameObject:: get_size(int &width, int &height) const
{
    width = mWidth;
    height = mHeight;
}


void SDLGameObject::update()
{
}