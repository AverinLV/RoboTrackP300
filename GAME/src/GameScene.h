#pragma once
#include "TmxLevel.h"

/// Предварительное объявление (pre-declaration) структуры
///  позволит передавать и хранить указатели и ссылки на неё,
///  но не позволит пользоваться или создавать,
///  поскольку мы ещё не знаем ни размер в байтах, ни свойства структуры.
struct GameView;

/// Структура, абстрагирующая игровую сцену.
struct GameScene
{
    TmxLevel level;
    TmxObject player;
    std::vector<TmxObject> enemies;
    std::vector<TmxObject> coins;
	std::vector<TmxObject> blocks;
};

GameScene* NewGameScene(const char* file);
void UpdateGameScene(void *pData, GameView &view, float deltaSec);
void DrawGameScene(void *pData, GameView &view);
void DestroyGameScene(GameScene *&pScene);
