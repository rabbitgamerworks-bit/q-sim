#ifndef __QSimGameState_H__
#define __QSimGameState_H__

namespace QSim
{
    enum GAME_STATE
    {
        G_EXIT,
        G_GAME
    };

    extern GAME_STATE g_ApplicationState;
}

#endif // __QSimGameState_H__
