#include "SDL_game_object.h"

void SDLGameObject:: load(const LoaderParams *pParams)
{
    mPosition = Vector2D(pParams->get_x(), pParams->get_y());
    mVelocity = Vector2D(0,0);
    mAcceleration = Vector2D(0,0);
    mWidth = pParams->get_width();
    mHeight = pParams->get_height();
    id = pParams->get_type();
}

void SDLGameObject::draw()
{
    SDL_Renderer *p_renderer = Game::get_instance()->get_renderer();
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    GameTexture *texture = TextureManager::Instance()->get_texture(id);
    if (texture == NULL)
    {
        LogError("Error occur when get texture for id %d", id);
    }
    else
    {
        texture->draw(mPosition.getX(), mPosition.getY(), mWidth, mHeight, p_renderer, flip);
    }
    return;
}

void SDLGameObject:: clean_up()
{

}

void SDLGameObject::update()
{
    mVelocity += mAcceleration;
    mPosition += mVelocity;
}