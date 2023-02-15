#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "application_manage.h"
#include "texture_wrapper.h"
#include "base_button.h"

//Button constants
const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;
const int TOTAL_BUTTONS = 4;

enum LButtonSprite
{
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    BUTTON_SPRITE_MOUSE_DOWN = 2,
    BUTTON_SPRITE_MOUSE_UP = 3,
    BUTTON_SPRITE_TOTAL = 4
};

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

class MouseButton: public BaseButton
{
    public:
        MouseButton(): BaseButton() {};
        ~MouseButton();
        void handle_event(SDL_Event *event) override;
};

MouseButton:: ~MouseButton()
{
    BaseButton::~BaseButton();
}

void MouseButton:: handle_event(SDL_Event *event)
{
    if (event->type == SDL_MOUSEMOTION || event->type == SDL_MOUSEBUTTONDOWN ||
    event->type == SDL_MOUSEBUTTONUP)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);

        bool inside = true;

        if (x < mPosition.x)
        {
            inside = false;
        }
        else if (x > mPosition.x + BUTTON_WIDTH)
        {
            inside = false;
        }
        else if (y < mPosition.y)
        {
            inside = false;
        }
        else if (y > mPosition.y + BUTTON_HEIGHT)
        {
            inside = false;
        }

        if (!inside)
        {
            mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
        }
        else
        {
            switch (event->type)
            {
            case SDL_MOUSEMOTION:
                mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                break;
            
            case SDL_MOUSEBUTTONDOWN:
                mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
                break;
            
            case SDL_MOUSEBUTTONUP:
                mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
                break;
            
            default:
                break;
            }
        }

    }
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
        LTexture mMouseTexture;
        SDL_Rect mSpriteClips[BUTTON_SPRITE_TOTAL];
        MouseButton mButton[BUTTON_SPRITE_TOTAL];
};


AppMange:: ~AppMange()
{
    mMouseTexture.~LTexture();
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
    if (mMouseTexture.get_renderer() == NULL)
    {
        mMouseTexture.set_renderer(mRenderer);
    }

    if (!mMouseTexture.load_from_file("resources/button.png"))
    {
        printf("Unable to load button file, SDL error %s\n", SDL_GetError());
        success = false;
    }
    else
    {
  		for( int i = 0; i < BUTTON_SPRITE_TOTAL; ++i )
		{
			mSpriteClips[ i ].x = 0;
			mSpriteClips[ i ].y = i * 200;
			mSpriteClips[ i ].w = BUTTON_WIDTH;
			mSpriteClips[ i ].h = BUTTON_HEIGHT;
		}

		mButton[ 0 ].set_position( 0, 0 );
		mButton[ 1 ].set_position( SCREEN_WIDTH - BUTTON_WIDTH, 0 );
		mButton[ 2 ].set_position( 0, SCREEN_HEIGHT - BUTTON_HEIGHT );
		mButton[ 3 ].set_position( SCREEN_WIDTH - BUTTON_WIDTH, SCREEN_HEIGHT - BUTTON_HEIGHT );
    }

    return success;
}

int AppMange::start_event_loop()
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
                continue;
            }

            for (int i = 0; i < BUTTON_SPRITE_TOTAL; i++)
            {
                mButton[i].handle_event(&e);
            }
        }

        SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(mRenderer);

        for (int i = 0; i < BUTTON_SPRITE_TOTAL; i++)
        {
            const SDL_Point *point = mButton[i].get_position();
            enum LButtonSprite idx = (enum LButtonSprite)mButton[i].get_current_sprite();
            mMouseTexture.render(point->x, point->y, &mSpriteClips[idx]);
        }

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

