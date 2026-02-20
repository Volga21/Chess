#pragma once

#include "../Header/Cell.h"
#include "../Header/IPiece.h"
#include "../Header/GameUtility.h"
#include "ox/Resources.hpp"


namespace Game
{
    using spCell = oxygine::intrusive_ptr<Cell>;
    using spPiece = oxygine::intrusive_ptr<IPiece>;

    class ChessModel
    {
    public:
        ChessModel(int cellSize);

        spCell data(int row, int column) const;
        void setData(int row, int column, ChessPieceType type);  
        
    private:   
        MoveType getMoveType(int row, int column);
        MoveType getMoveTypeForPawn(int row, int column);
        MoveType getMoveTypeForRook(int row, int column);
        MoveType getMoveTypeForBishop(int row, int column);
        MoveType getMoveTypeForQueen(int row, int column);
        MoveType getMoveTypeForKing(int row, int column);
        MoveType getMoveTypeForKnight(int row, int column);

        oxygine::Resources                      gameResources_;
        Game::GameColor                         gameMove_ = Game::GameColor::White;
        std::vector<std::vector<spCell>>        cells_;
        bool                                    isPieceSelected_ = false;
        int                                     selectedRow_;
        int                                     selectedCol_;
        int                                     cellSize_;
    };
}