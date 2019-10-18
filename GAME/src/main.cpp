#include <iostream>
#include "GameView.h"
#include "GameScene.h"

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    try
    {
        // NOTE: Если при загрузке карты будет выброшено исключение,
        //  то память утечёт. НАДО ЮЗАТЬ БУСТ УКАЗАТЕЛИ!!!
        GameView *pGameView = NewGameView({800, 600});
        GameScene *pGameScene = NewGameScene("res/platformer.tmx");

        // Аргумент типа `GameLogic*` будет преобразован в `void*`.
        EnterGameLoop(*pGameView, UpdateGameScene, DrawGameScene, pGameScene);
    }
    catch (const std::exception &ex)
    {
        std::cerr << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
