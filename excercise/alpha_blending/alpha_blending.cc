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
        bool render(int x, int y, SDL_Rect *clip = NULL);
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

bool LTexture:: render(int x, int y, SDL_Rect *clip)
{
    SDL_Rect render_quad = {x, y, mWidth, mHeight};

    if (clip != NULL)
    {
        render_quad.w = clip->w;
        render_quad.h = clip->h;
    }

    SDL_RenderCopy(mRenderer, mTexture, clip, &render_quad);
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

class ColorModulation: public ApplicationManageBase
{
    public:
        ColorModulation(): ApplicationManageBase() {};
        ~ColorModulation();
        int start_event_loop() override;
        bool load_media() override;
        bool init_resource_loading() override;
    private:
        LTexture mModulatedTexture;
        LTexture mBackgroundTexture;
};

ColorModulation:: ~ColorModulation()
{
    mModulatedTexture.~LTexture();
    mBackgroundTexture.~LTexture();
    close();
}

bool ColorModulation::init_resource_loading()
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

bool ColorModulation::load_media()
{
    if (mModulatedTexture.get_renderer() == NULL)
    {
        mModulatedTexture.set_renderer(mRenderer);
        mBackgroundTexture.set_renderer(mRenderer);
    }

    bool success = true;

    if (!mModulatedTexture.load_from_file("resources/fadeout.png"))
    {
        printf("Failed to load sprite front texture !\n");
        success = false;
    }
    else
    {
        mModulatedTexture.set_blend_mode(SDL_BLENDMODE_BLEND);
    }

    if (!mBackgroundTexture.load_from_file("resources/fadein.png"))
    {
        printf("Failed to load backround texture !\n");
        success = false;
    }

    return success;
}

int ColorModulation::start_event_loop()
{
    bool quit = false;
    SDL_Event e;
    uint8_t a = 255;

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
                //Increase alpha on w
                if( e.key.keysym.sym == SDLK_w )
                {
                    //Cap if over 255
                    if( a + 32 > 255 )
                    {
                        a = 255;
                    }
                    //Increment otherwise
                    else
                    {
                        a += 32;
                    }
                }
                //Decrease alpha on s
                else if( e.key.keysym.sym == SDLK_s )
                {
                    //Cap if below 0
                    if( a - 32 < 0 )
                    {
                        a = 0;
                    }
                    //Decrement otherwise
                    else
                    {
                        a -= 32;
                    }
                }
            }
        }

        SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(mRenderer);

        mBackgroundTexture.render(0, 0);
        
        mModulatedTexture.set_alpha(a);
        mModulatedTexture.render(0, 0);

        SDL_RenderPresent(mRenderer);
    }
    return 0;
}

int main(int argc, char *argv[])
{
    ApplicationManageBase *app_manage = new ColorModulation();
    app_manage->init("Color modulation");
    app_manage->load_media();
    return app_manage->start_event_loop();
}

