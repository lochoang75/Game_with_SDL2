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

class ColorModulation: public ApplicationManageBase
{
    public:
        ColorModulation(): ApplicationManageBase() {};
        ~ColorModulation();
        int start_event_loop() override;
        bool load_media() override;
        bool init_resource_loading() override;
    private:
        SDL_Rect mSpriteClips[4];
        LTexture mModuleTexture;
};

ColorModulation:: ~ColorModulation()
{
    mModuleTexture.~LTexture();
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
    if (mModuleTexture.get_renderer() == NULL)
    {
        mModuleTexture.set_renderer(mRenderer);
    }

    bool success = true;

    if (!mModuleTexture.load_from_file("resources/colors.png"))
    {
        printf("Failed to load sprite sheet texture!\n");
        success = false;
    }
    else
    {
        //Set top left sprite
        mSpriteClips[ 0 ].x =   0;
        mSpriteClips[ 0 ].y =   0;
        mSpriteClips[ 0 ].w = 100;
        mSpriteClips[ 0 ].h = 100;

        //Set top right sprite
        mSpriteClips[ 1 ].x = 100;
        mSpriteClips[ 1 ].y =   0;
        mSpriteClips[ 1 ].w = 100;
        mSpriteClips[ 1 ].h = 100;
        
        //Set bottom left sprite
        mSpriteClips[ 2 ].x =   0;
        mSpriteClips[ 2 ].y = 100;
        mSpriteClips[ 2 ].w = 100;
        mSpriteClips[ 2 ].h = 100;

        //Set bottom right sprite
        mSpriteClips[ 3 ].x = 100;
        mSpriteClips[ 3 ].y = 100;
        mSpriteClips[ 3 ].w = 100;
        mSpriteClips[ 3 ].h = 100;
    }

    return success;
}

int ColorModulation::start_event_loop()
{
    bool quit = false;
    SDL_Event e;
    uint8_t r = 255;
    uint8_t g = 255;
    uint8_t b = 255;

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
                switch(e.key.keysym.sym)
                {
                    //Increase red
                    case SDLK_q:
                    r += 32;
                    break;
                            
                    //Increase green
                    case SDLK_w:
                    g += 32;
                    break;
                            
                    //Increase blue
                    case SDLK_e:
                    b += 32;
                    break;
                            
                    //Decrease red
                    case SDLK_a:
                    r -= 32;
                    break;
                            
                    //Decrease green
                    case SDLK_s:
                    g -= 32;
                    break;
                            
                    //Decrease blue
                    case SDLK_d:
                    b -= 32;
                    break;
                }
            }
        }

        SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(mRenderer);
        
        mModuleTexture.set_color(r, g, b);
        mModuleTexture.render(0, 0);

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

