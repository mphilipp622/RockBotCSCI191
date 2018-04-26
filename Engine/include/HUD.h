#ifndef HUD_H
#define HUD_H

#include <Player.h>
#include <TextureLoader.h>

class HUD
{
    public:
        HUD();
        void showHP(Player*);
        void showHeadIcon();
        virtual ~HUD();
        void Update();
        void loadIcons();
        TextureLoader* headIcon;
    protected:

    private:
        TextureLoader iconImage[2];
};

#endif // HUD_H
