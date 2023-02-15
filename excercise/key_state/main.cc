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

bool LTexture::render(int x, int y, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip)
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

class AppMange: public ApplicationManageBase
{
    public:
        AppMange():ApplicationManageBase(){};
        ~AppMange();
        int start_event_loop() override;
        bool load_media() override;
        void close() override;
        bool init_resource_loading() override;
    private:
        LTexture mUpTexture;
        LTexture mDownTexture;
        LTexture mLeftTexture;
        LTexture mRightTexture;
        LTexture mPressTexture;
};


AppMange:: ~AppMange()
{
    mUpTexture.~LTexture();
    mDownTexture.~LTexture();
    mLeftTexture.~LTexture();
    mRightTexture.~LTexture();
    mPressTexture.~LTexture();
    close();
}

bool AppMange::init_resource_loading()
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

void AppMange::close()
{
    ApplicationManageBase:: close();
    IMG_Quit();
}

bool AppMange::load_media()
{
    bool success = true;
    if (mUpTexture.get_renderer() == NULL)
    {
        mUpTexture.set_renderer(mRenderer);
        mDownTexture.set_renderer(mRenderer);
        mLeftTexture.set_renderer(mRenderer);
        mRightTexture.set_renderer(mRenderer);
        mPressTexture.set_renderer(mRenderer);
    }

    if (!mUpTexture.load_from_file("resources/up.png"))
    {
        printf("Unable to load up file, SDL error %s\n", SDL_GetError());
        success = false;
    }

    if (!mDownTexture.load_from_file("resources/down.png"))
    {
        printf("Unable to load down file, SDL error %s\n", SDL_GetError());
        success = false;
    }

    if (!mLeftTexture.load_from_file("resources/left.png"))
    {
        printf("Unable to load left file, SDL error %s\n", SDL_GetError());
        success = false;
    }

    if (!mRightTexture.load_from_file("resources/right.png"))
    {
        printf("Unable to load right file, SDL error %s\n", SDL_GetError()); 
        success = false;
    }

    if (!mPressTexture.load_from_file("resources/press.png"))
    {
        printf("Unable to load press file, SDL error %s\n", SDL_GetError());
        success = false;
    }

    return success;
}

int AppMange::start_event_loop()
{
    bool quit = false;
    SDL_Event e;
    LTexture *current_texture = NULL;

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

       const uint8_t * current_key_states = SDL_GetKeyboardState(NULL);
        if (current_key_states[SDL_SCANCODE_UP])
        {
            current_texture = &mUpTexture;
        }
        else if (current_key_states[SDL_SCANCODE_DOWN])
        {
            current_texture = &mDownTexture;
        }
        else if (current_key_states[SDL_SCANCODE_LEFT])
        {
            current_texture = &mLeftTexture;
        }
        else if (current_key_states[SDL_SCANCODE_RIGHT])
        {
            current_texture = &mRightTexture;
        }
        else
        {
            current_texture = &mPressTexture;
        }

        SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(mRenderer);

        current_texture->render(0, 0);

        SDL_RenderPresent(mRenderer);
    }
    return 0;
}

int main(int argc, char *argv[])
{
    ApplicationManageBase *app_manage = new AppMange();
    app_manage->init("Main");
    app_manage->load_media();
    return app_manage->start_event_loop();
}

