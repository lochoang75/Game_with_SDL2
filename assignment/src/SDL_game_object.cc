#include "SDL_game_object.h"

void SDLGameObject:: load(const LoaderParams *pParams)
{
    mWidth = pParams->get_width();
    mHeight = pParams->get_height();
    id = pParams->get_type();
    b2World *world_instnace = Game::Instance()->get_world();
    b2BodyDef object_def;
    if (pParams->get_physical_object_type() == ePHYSIC_DYNAMIC)
    {
        object_def.type = b2_dynamicBody;
    }
    object_def.position.Set(pParams->get_x(), pParams->get_y());
    mBody = world_instnace->CreateBody(&object_def);
    physic_paramter_load(pParams->get_physical_shape(), pParams->get_physical_density(),
                        pParams->get_physical_friction(), pParams->get_physical_restitution());
}

void SDLGameObject::draw()
{
    double angle = SDLGameObject::get_angle();
    int pos_x, pos_y;
    SDLGameObject::get_current_position(pos_x, pos_y);
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
        LogError("Error occur when get texture for id %d", id);
    }
    else
    {
        texture->draw(pos_x, pos_y, &src_rect, angle, p_renderer, flip);
    }
    return;
}

void SDLGameObject:: clean_up()
{
    b2World *world_instance = Game::Instance()->get_world();
    world_instance->DestroyBody(mBody);
}

void SDLGameObject::physic_paramter_load(enum ePhysicalShape shape, float density, float friction, float restitution)
{
    if (shape == ePOLYGON_SHAPE)
    {
        b2PolygonShape object_shape;
        float w_plat = mWidth / MET2PIX;
        float h_plat = mHeight / MET2PIX;
        object_shape.SetAsBox((w_plat / 2.0f) - object_shape.m_radius, (h_plat / 2.0f) - object_shape.m_radius);
        b2FixtureDef fixture;
        fixture.shape = &object_shape;
        fixture.density = density;
        fixture.friction = friction;
        fixture.restitution = restitution;
        mBody->CreateFixture(&fixture);
    }
    else
    {
        LogError("Object has shape %d is not implment", shape);
    }
}

void SDLGameObject::set_velocity(float x_vel, float y_vel)
{
    b2Vec2 vel(0.0f, 0.2f);
    mBody->SetLinearVelocity(vel);
}

void SDLGameObject::get_current_position(int &pos_x, int &pos_y) const
{
    b2Vec2 position = mBody->GetPosition();
    pos_x = ((SCALED_WIDTH / 2.0f) + position.x) * MET2PIX - mWidth / 2;
    pos_y = ((SCALED_HEIGH / 2.0f) + position.y) * MET2PIX - mHeight / 2;
}

double SDLGameObject::get_angle() const
{
    return mBody->GetAngle() * RAD2DEG;
}


void SDLGameObject::update()
{
}