#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "application_manage.h"
#include "texture_wrapper.h"

class LTexture: public BaseTexture
{
    public:
        LTexture():BaseTexture(){};
        LTexture(SDL_Renderer *renderer): BaseTexture(renderer){};
        void render(int x, int y, SDL_Rect *clip = NULL);
        bool load_from_file(std:: string path) override;
};

void LTexture::render(int x, int y, SDL_Rect *clip)
{
    SDL_Rect render_quad = {x, y, mWidth, mHeight};

    if (clip != NULL)
    {
        render_quad.w = clip->w;
        render_quad.h = clip->h;
    }

    SDL_RenderCopy(mRenderer, mTexture, clip, &render_quad);
}

bool LTexture::load_from_file(std:: string path)
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

    return newTexture == NULL;
}


class ClipRendering: public ApplicationManageBase
{
    public:
        ClipRendering(): ApplicationManageBase() {};
        virtual ~ClipRendering();
        int start_event_loop() override;
        bool load_media() override;
        bool init_resource_loading() override;
    private:
        SDL_Rect mSpriteClips[4];
        LTexture mSpriteSheetTexture;
};

bool ClipRendering::load_media()
{
    if (mSpriteSheetTexture.get_renderer() == NULL)
    {
        mSpriteSheetTexture.set_renderer(mRenderer);
    }

    bool success = true;

    if (!mSpriteSheetTexture.load_from_file("resources/dots.png"))
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

ClipRendering::~ClipRendering()
{
    close();
    mSpriteSheetTexture.~LTexture();
}

bool ClipRendering:: init_resource_loading()
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

int ClipRendering:: start_event_loop()
{
    bool quit = false;
    SDL_Event e;
    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(mRenderer);

        mSpriteSheetTexture.render(0, 0, &mSpriteClips[0]);
        mSpriteSheetTexture.render(SCREEN_WIDTH - mSpriteClips[1].w, 0, &mSpriteClips[1]);
        mSpriteSheetTexture.render(0, SCREEN_HEIGHT - mSpriteClips[2].h, &mSpriteClips[2]);
        mSpriteSheetTexture.render(SCREEN_WIDTH - mSpriteClips[3].w, SCREEN_HEIGHT - mSpriteClips[3].h, &mSpriteClips[3]);
        SDL_RenderPresent(mRenderer);
    }
    close();
    return 0;
}

int main(int argc, char *argv[])
{
    ClipRendering *clip_rendering = new ClipRendering();
    clip_rendering->init("Clip rendering");
    clip_rendering->load_media();
    return clip_rendering->start_event_loop();
}

