#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "application_manage.h"
#include "texture_wrapper.h"

class LTexture: public BaseTexture
{
    public:
        LTexture(): BaseTexture() {};
        LTexture(SDL_Renderer *render): BaseTexture(render) {};
        ~LTexture();
        bool load_from_file(std:: string path) override;
        bool render(int x, int y, SDL_Rect *clip = NULL, double angle = 0.0, SDL_Point *center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void set_color(uint8_t red, uint8_t green, uint8_t blue);
        void set_alpha(uint8_t alpha);
        void set_blend_mode(SDL_BlendMode blending);
};

bool LTexture:: load_from_file(std::string path)
{
    SDL_Texture *newTexture = NULL;

    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load the image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

        newTexture = SDL_CreateTextureFromSurface(mRenderer, loadedSurface);
        if (newTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        } 
        else
        {
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        SDL_FreeSurface(loadedSurface);
        mTexture = newTexture;
    }

    return newTexture;
}

LTexture:: ~LTexture()
{
    free();
}

bool LTexture:: render(int x, int y, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip)
{
    SDL_Rect render_quad = {x, y, mWidth, mHeight};

    if (clip != NULL)
    {
        render_quad.w = clip->w;
        render_quad.h = clip->h;
    }

    SDL_RenderCopyEx(mRenderer, mTexture, clip, &render_quad, angle, center, flip);
    return true;
}

void LTexture::set_color(uint8_t red, uint8_t green, uint8_t blue)
{
    SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::set_alpha(uint8_t alpha)
{
    SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::set_blend_mode(SDL_BlendMode blending)
{
    SDL_SetTextureBlendMode(mTexture, blending);
}

class RotationFlipping: public ApplicationManageBase
{
    public:
        RotationFlipping(): ApplicationManageBase() {};
        ~RotationFlipping();
        int start_event_loop() override;
        bool load_media() override;
        bool init_resource_loading() override;
    private:
        LTexture mArrowTexture;
};

RotationFlipping:: ~RotationFlipping()
{
    mArrowTexture.~LTexture();
    close();
}

bool RotationFlipping::init_resource_loading()
{
    bool success = true;
    SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    int img_flag = IMG_INIT_PNG;
    if (!(IMG_Init(img_flag) & img_flag))
    {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", SDL_GetError());
        success = false;
    }
    return success;
}

bool RotationFlipping::load_media()
{
    if (mArrowTexture.get_renderer() == NULL)
    {
        mArrowTexture.set_renderer(mRenderer);
    }

    bool success = true;

    if (!mArrowTexture.load_from_file("resources/arrow.png"))
    {
        printf("Failed to load sprite front texture !\n");
        success = false;
    }

    return success;
}

int RotationFlipping::start_event_loop()
{
    bool quit = false;
    SDL_Event e;
    double degrees = 0.0f;
    SDL_RendererFlip flip_type = SDL_FLIP_NONE;

    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
                continue;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {
                    case SDLK_a:
                    degrees -= 60;
                    break;
                
                    case SDLK_d:
                    degrees += 60;
                    break;

                    case SDLK_q:
                    flip_type = SDL_FLIP_HORIZONTAL;
                    break;

                    case SDLK_w:
                    flip_type = SDL_FLIP_NONE;
                    break;

                    case SDLK_e:
                    flip_type = SDL_FLIP_VERTICAL;
                    break;
                }
            }
        }

        SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(mRenderer);

        mArrowTexture.render( ( SCREEN_WIDTH - mArrowTexture.get_width() ) / 2, ( SCREEN_HEIGHT - mArrowTexture.get_height() ) / 2, NULL, degrees, NULL, flip_type );

        SDL_RenderPresent(mRenderer);
    }
    return 0;
}

int main(int argc, char *argv[])
{
    ApplicationManageBase *app_manage = new RotationFlipping();
    app_manage->init("Rotation Flipping");
    app_manage->load_media();
    return app_manage->start_event_loop();
}

