#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "application_manage.h"
#include "texture_wrapper.h"
#define WALKING_ANIMATION_FRAMES 4

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

class AnimateSprite: public ApplicationManageBase
{
    public:
        AnimateSprite(): ApplicationManageBase() {};
        ~AnimateSprite();
        int start_event_loop() override;
        bool load_media() override;
        bool init_resource_loading() override;
    private:
        SDL_Rect mSpriteClips[WALKING_ANIMATION_FRAMES];
        LTexture mModuleTexture;
};

AnimateSprite:: ~AnimateSprite()
{
    mModuleTexture.~LTexture();
    close();
}

bool AnimateSprite::init_resource_loading()
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

bool AnimateSprite::load_media()
{
    if (mModuleTexture.get_renderer() == NULL)
    {
        mModuleTexture.set_renderer(mRenderer);
    }

    bool success = true;

    if (!mModuleTexture.load_from_file("resources/foo.png"))
    {
        printf("Failed to load sprite sheet texture!\n");
        success = false;
    }
    else
    {
        //Set sprite clips
        mSpriteClips[ 0 ].x =   0;
        mSpriteClips[ 0 ].y =   0;
        mSpriteClips[ 0 ].w =  64;
        mSpriteClips[ 0 ].h = 205;

        mSpriteClips[ 1 ].x =  64;
        mSpriteClips[ 1 ].y =   0;
        mSpriteClips[ 1 ].w =  64;
        mSpriteClips[ 1 ].h = 205;
        
        mSpriteClips[ 2 ].x = 128;
        mSpriteClips[ 2 ].y =   0;
        mSpriteClips[ 2 ].w =  64;
        mSpriteClips[ 2 ].h = 205;

        mSpriteClips[ 3 ].x = 192;
        mSpriteClips[ 3 ].y =   0;
        mSpriteClips[ 3 ].w =  64;
        mSpriteClips[ 3 ].h = 205;
    }

    return success;
}

int AnimateSprite::start_event_loop()
{
    bool quit = false;
    SDL_Event e;
    int frame = 0;

    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
                continue;
            }
        }
        SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(mRenderer);

        SDL_Rect *current_frame = &mSpriteClips[frame/4];
        mModuleTexture.render((SCREEN_WIDTH - current_frame->w)/2, (SCREEN_HEIGHT - current_frame->h)/2, current_frame);
        
        SDL_RenderPresent(mRenderer);
        ++ frame;

        if (frame /4 >= WALKING_ANIMATION_FRAMES)
        {
            frame = 0;
        }
    }
    return 0;
}

int main(int argc, char *argv[])
{
    ApplicationManageBase *app_manage = new AnimateSprite();
    app_manage->init("Animate_Sprite", SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    app_manage->load_media();
    return app_manage->start_event_loop();
}

