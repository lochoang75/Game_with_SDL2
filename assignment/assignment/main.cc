#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "application_manage.h"
#include "texture_wrapper.h"
#include "base_button.h"
#define MAX_FRUIT (10)
#define NUM_TREES (3)

class GameTexture: public BaseTexture
{
    public:
        GameTexture(): BaseTexture(){};
        GameTexture(SDL_Renderer *renderer): BaseTexture(renderer){};
        ~GameTexture();
        bool load_from_file(std:: string path) override;
        bool render(int x, int y, SDL_Rect *clip = NULL);

};

GameTexture:: ~GameTexture()
{
    BaseTexture::~BaseTexture();
}

bool GameTexture::render(int x, int y, SDL_Rect* clip)
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

bool GameTexture::load_from_file(std::string path)
{
    SDL_Surface *loaded_surface = IMG_Load(path.c_str());
    if (loaded_surface == NULL)
    {
        printf("SDL image error on load image %s, IMG error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {        
        mTexture = SDL_CreateTextureFromSurface(mRenderer, loaded_surface);
        if (mTexture == NULL)
        {
            printf("SDL texture create failed, SDL error %s\n", SDL_GetError());
        }
        else
        {
            mWidth = (loaded_surface->w > SCREEN_WIDTH) ? SCREEN_WIDTH: loaded_surface->w;
            mHeight = (loaded_surface->h > SCREEN_HEIGHT) ? SCREEN_HEIGHT: loaded_surface->h;
        }

        SDL_FreeSurface(loaded_surface);
    }

    return mTexture == NULL;
}

class FruitObject: public BaseButton
{
    FruitObject(): BaseButton(){};
    ~FruitObject();
    void handle_event(SDL_Event *event);
};

class AppManage: public ApplicationManageBase
{
    public:
        AppManage(): ApplicationManageBase(){};
        ~AppManage();
        static const int floor_line = SCREEN_HEIGHT - 125;
        void close() override;
        int start_event_loop();
        bool load_media();
        bool init_resource_loading();
    private:
        GameTexture mBackground;
        GameTexture mFruit;
        GameTexture mTree[NUM_TREES];
        SDL_Rect mFruitSprites[MAX_FRUIT];
        GameTexture mBasket;
};

AppManage::~AppManage()
{
    ApplicationManageBase::~ApplicationManageBase();
}

bool AppManage::init_resource_loading()
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

void AppManage::close()
{
    IMG_Quit();
    ApplicationManageBase::close();
}

bool AppManage::load_media()
{
    bool success = true;
    if (mBackground.get_renderer() == NULL)
    {
        mBackground.set_renderer(mRenderer);
        mFruit.set_renderer(mRenderer);
        mBasket.set_renderer(mRenderer);
        for (int i = 0; i < NUM_TREES; i++)
        {
            mTree[i].set_renderer(mRenderer);
        }
    }

    if (mBackground.load_from_file("resources/background.png"))
    {
        printf("Unable to load background image");
        success = false;
    }

    if (mFruit.load_from_file("resources/apple.png"))
    {
        printf("Unable to load fruit image");
        success = false;
    }

    if (mBasket.load_from_file("resources/basket.png"))
    {
        printf("Unable to load basket image");
        success = false;
    }

    if (mTree[0].load_from_file("resources/tree_1.png"))
    {
        printf("Unable to load image tree 1");
        success = false;
    }

    if (mTree[1].load_from_file("resources/tree_2.png"))
    {
        printf("Unable to load image tree 2");
        success = false;
    }

    if (mTree[2].load_from_file("resources/tree_3.png"))
    {
        printf("Unable to load image tree 3");
        success = false;
    }
    return success;
}

int AppManage::start_event_loop()
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
        }

        SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(mRenderer);
        mBackground.render(0, 0);
        mFruit.render(0, 10);
        mBasket.render(0, floor_line - mBasket.get_height());
        for (int i = 0; i < NUM_TREES; i++)
        {
            mTree[i].render(i* mTree[i].get_width(), floor_line - mTree[i].get_height());
        }

        SDL_RenderPresent(mRenderer);
    }

    return 0;
}


int main(int argc, char *argv[])
{
    ApplicationManageBase *main_app = new AppManage();
    main_app->init("Fruit picking", SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    main_app->load_media();
    return main_app->start_event_loop();
}