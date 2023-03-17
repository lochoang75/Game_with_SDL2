#ifndef APPLICATION_MANAGE_H
#define APPLICATION_MANAGE_H
#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include "game_constant.h"
#include "game_object.h"
#include "game_contact_listener.h"
#include "box2d.h"

class Game
{
    public:
        static Game* Instance();
        SDL_Renderer* get_renderer();
        ErrorCode_t init(const char *title);

        ErrorCode_t load_media();
        ErrorCode_t load_animation();
        ErrorCode_t load_font();
        ErrorCode_t create_object();
        void set_touch_position(int &x, int &y);
        int get_number_fruit_on_the_tree();
        void update();
        void clean_up();
        void render();
        void handle_event(enum eGameEventEnum);
        void close();
    
    private:
        friend Uint32 periodict_timer_callback(Uint32 interval, void* name);
        Game();
        ~Game(){};
        void creator_register();
        ErrorCode_t sdl_component_init(const char *title, int xpos, int ypos, int flags);
        void timer_init();
        void physics_init();
        SDL_Window *mWindow;
        SDL_Renderer *mRenderer;
        static Game *mInstance;
        int touch_x;
        int touch_y;
        b2Body *mGroundBody;
        GameContactListener mContactListener;
        std::vector<GameObject*> mGameObjectVector;
        SDL_TimerID mTimerID;

        ErrorCode_t _create_background_object();
        ErrorCode_t _create_tree_object(GameObject *&tree);
        ErrorCode_t _create_bird_object(GameObject *roadSign);
        ErrorCode_t _create_fruit_object(GameObject *tree);
        ErrorCode_t _create_kid_object();
        ErrorCode_t _create_road_sign(GameObject *&sign);
        ErrorCode_t _create_chat_box(GameObject *&chatBox);
        ErrorCode_t _create_answer_bubble(GameObject *pParent); 
};

#endif /* APPLICATION_MANAGE_H */