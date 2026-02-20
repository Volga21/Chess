#pragma once

#include "../Header/IPiece.h"

namespace oxygine
{
    class Resources;
}

namespace Game
{
    class Queen : public IPiece
    {
    public:
        Queen(GameColor color, int row, int col, const oxygine::Resources& res);

        ChessPieceType type() const final;
        GameColor color() const final;
        
        int row() const final;
        int col() const final;
        
        void setPieceRow(int row) final;
        void setPieceColumn(int col) final;

        void setPiecePosition(int row, int column, int cellSize) final;
    private:
        
        GameColor color_ = GameColor::None;
        int row_ = 0;
        int col_ = 0;
    };
}
