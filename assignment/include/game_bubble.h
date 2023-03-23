
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "game_object.h"
#include "game_event.h"
#include "game_object_factory.h"
#include "game_speech.h"
#include "animation.h"

enum eAnswerBubbleAnimationState
{
    eWATER_BUBBLE_SHOW_NORMAL = 0,
    eWATER_BUBBLE_SHOW_EXPLOSE,
    eWATER_BUBBLE_HIDE,
    eWATER_BUBBLE_READY_TO_SHOW,
};

enum eQuestionBubbleAnimationState
{
    eQUESTION_BUBBLE_HIDE = 0,
    eQUESTION_BUBBLE_SHOW,
    eQUESTION_BUBBLE_SHOW_ANSWER
};


enum eGameBubbleEventEnum {
    eBUBBLE_EVENT_CLICK_ON = eGAME_EVENT_MOUSE_DONW,
    eBUBBLE_EVENT_ENABLE,
    eBUBBLE_EVENT_SHOW,
    eBUBBLE_EVENT_HIDE
};

class AnswerBubbleAnimationPool: public AnimationPool
{
    public:
        AnswerBubbleAnimationPool(): AnimationPool(){load_animation();};
        ~AnswerBubbleAnimationPool(){};
        void load_animation() override;
    private:
        void load_bubble_normal_animation();
        void load_bubble_explose_animation();
};

class GameBubble: public GameObject
{
    public:
        GameBubble(enum eGameObjectType type);
        virtual ~GameBubble(){clean_up();};
        virtual void load_animation(){}; 
        void load(const LoaderParams* params) override;
        virtual void draw() override;
        void clean_up() override;

        void set_render_text(const wchar_t *text_to_show);
        virtual void set_render_text(GameCharacterSpeech *speech);
        void set_text_color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
        void set_text_color(SDL_Color color);
        virtual void get_position(int &x, int &y) const override;
        virtual void get_size(int &width, int &height) const override;
        virtual void handle_event(int event) = 0;
    protected:
        virtual void draw_background();
        virtual void draw_text();
        int mBackgroundX;
        int mBackgroundY;
        int mTextOffsetX;
        int mTextOffsetY;
        int mWidth;
        int mHeight;
        uint16_t *mText;
        SDL_Color mTextColor;
        eTextureType id;
        SDL_Texture *mTextTexture;
};

class GameAnswerBubble: public GameBubble 
{
    public:
        GameAnswerBubble();
        GameAnswerBubble(const GameAnswer &answer);
        ~GameAnswerBubble(){};
        void set_position(int x, int y);
        void set_answer(const GameAnswer &answer);
        void update() override;
        void draw() override;
        void load_animation() override;
        
        /* a alittle mapping here*/
        void handle_event(int event) override;
        bool is_user_answer(GameAnswer &answer) const;
        void clear_answer_flag() {mAnswerFlag = false;};
    protected:
        void draw_background() override;
    private:
        void animation_variable_reset();
        const AnimationFrame *mCurrentFrame;
        const AnimationPool *mAnimation;
        enum eAnswerBubbleAnimationState mState;
        int mFrameIdx;
        uint8_t mFrameCounter;
        GameAnswer mAnswer;
        bool mAnswerFlag;
};

class GameBubbleCreator: public BaseCreator
{
    GameObject *create_object() const override;
};

class GameQuestionBubble: public GameBubble 
{
    public:
        ~GameQuestionBubble(){};
        static GameQuestionBubble *Instance();
        // void set_state(enum )
        void update() override;
        /*TODO: handle answer if speech is a question*/
        void handle_event(int event) override;
        void set_render_text(GameCharacterSpeech *speech) override;
        void set_show_flag(bool flag) {mIsShow = flag;};
        void add_answer_bubble(GameAnswerBubble *other_bubble);
        bool get_user_answer(GameAnswer &answer) const;
        void clear_user_answer();
    
    private:
        void update_position_for_answer_bubble();
        void hide_all_answer_bubble();
        GameQuestionBubble();
        static GameQuestionBubble *mInstance;
        enum eQuestionBubbleAnimationState mState;
        std::vector<GameAnswerBubble*> mAnsBubbleList;
        bool mIsShow;
        bool isQuestion;
};