#pragma once

#include "Class/Core/Framework.h"

/* Test Framework realization */
class MyFramework : public Framework
{

private:
    int mouseX = 0;
    int screenWidth = 800;
    int screenHeight = 600;
    bool isFullscreen = false;

public:
    
    void PreInit(int& width, int& height, bool& fullscreen) override;
    bool Init() override;
    void Close() override;
    bool Tick() override;
    void onMouseMove(int x, int y, int xrelative, int yrelative) override;
    void onMouseButtonClick(FRMouseButton button, bool isReleased) override;
    void onKeyPressed(FRKey k) override;
    void onKeyReleased(FRKey k) override;
    const char* GetTitle() override;
    void setWindowParameters(int width, int height, bool fullscreen);

    static void getSpriteSizeInFramework(Sprite* sprite, int& width, int& height);
    static void setSpriteSizeInFramework(Sprite* sprite, int width, int height);
    static void destroySpriteInFramework(Sprite* sprite);
    static void getScreenSizeFromFramework(int& w, int& h);
    static void drawSpriteInFramework(Sprite* sprite, int x_axis, int y_axis);
    static Sprite* createSpriteInFramework(const char* path);
};