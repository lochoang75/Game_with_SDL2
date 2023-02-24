#include "SDL_game_object.h"

void SDLGameObject:: load(const LoaderParams *pParams)
{
    mWidth = pParams->get_width();
    mHeight = pParams->get_height();
    id = pParams->get_type();
    b2World *world_instnace = Game::Instance()->get_world();
    b2BodyDef object_def;
    if (pParams->get_physic() == ePHYSIC_DYNAMIC)
    {
        object_def.type = b2_dynamicBody;
    }
    object_def.position.Set(pParams->get_x(), pParams->get_y());
    mBody = world_instnace->CreateBody(&object_def);
}

void SDLGameObject::draw()
{
    SDL_Renderer *p_renderer = Game::Instance()->get_renderer();
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    GameTexture *texture = TextureManager::Instance()->get_texture(id);
    if (texture == NULL)
    {
        LogError("Error occur when get texture for id %d", id);
    }
    else
    {
        texture->draw(x, y, mWidth, mHeight, p_renderer, flip);
    }
    return;
}

void SDLGameObject:: clean_up()
{
    b2World *world_instance = Game::Instance()->get_world();
    world_instance->DestroyBody(mBody);
}

void SDLGameObject::update()
{
}