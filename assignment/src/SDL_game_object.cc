#include "SDL_game_object.h"

void SDLGameObject:: load(const LoaderParams *pParams)
{
    mWidth = pParams->get_width();
    mHeight = pParams->get_height();
    x = pParams->get_x();
    y = pParams->get_y();
    id = pParams->get_type();
    mBody = Box2DPhysicalFacade::create_body(pParams);
    if (mBody != NULL)
    {
    }
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
        LogError("Error occur when get texture for id %d", id);
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

void SDLGameObject:: get_position(int &x, int &y) const
{
    x = this->x;
    y = this->y;
}


void SDLGameObject::update()
{
}