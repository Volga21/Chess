#include "../Header/Rook.h"

#include "../Header/GameUtility.h"

#include "ox/Resources.hpp"
#include "ox/Stage.hpp"

namespace Game
{

    Rook::Rook(GameColor color,int row, int col, const oxygine::Resources& res)
        :IPiece(),color_(color), row_(row), col_(col)
    {
        oxygine::getStage()->addChild(this);
        if(auto iconName = getIconName(ChessPieceType::Rook, color_); !iconName.empty())
        {
            setResAnim(res.getResAnim(iconName));
            setSize(100/2, 100 /2);
        }
    }

    ChessPieceType Rook::type() const
    {
        return ChessPieceType::Rook;
    }

    GameColor Rook::color() const
    {
        return color_;
    }

    int Rook::row() const
    {
        return row_;
    }

    int Rook::col() const
    {
        return col_;
    }
        
    void Rook::setPieceRow(int row)
    {
        row_ = row;
    }

    void Rook::setPieceColumn(int col) 
    {
        col_ = col;
    }

    void Rook::setPiecePosition(int row, int column, int cellSize)
    {
        row_ = row;
        col_ = column;
        setPosition((column + 1) * cellSize + cellSize / 4, (row + 1) * cellSize + cellSize / 4 );
    }

}
