#ifndef HUD_H
#define HUD_H

#include <Player.h>

class HUD
{
    public:
        HUD();
        void showHP(Player*);
        void showHeadIcon();
        virtual ~HUD();
        void Update();
    protected:

    private:
};

#endif // HUD_H
