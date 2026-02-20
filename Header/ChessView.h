#pragma once

#include "ox/Actor.hpp"
#include "../Header/ChessModel.h"

#include <memory>

namespace Game
{

    class ChessView : public oxygine::Actor
    {   
    public:
        ChessView(float x, float y, int cellSize);
        ~ChessView();
        void setModel(std::unique_ptr<ChessModel> model);

    private:
        void createBoard(int cellSize);

        std::unique_ptr<ChessModel> model_;        
    };
}
// Определение статических констант для событий