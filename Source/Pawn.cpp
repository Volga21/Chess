#include "../Header/Pawn.h"

#include "../Header/GameUtility.h"

#include "ox/Resources.hpp"
#include "ox/Stage.hpp"

namespace Game
{

    Pawn::Pawn(GameColor color,int row, int col, const oxygine::Resources& res)
        :IPiece(),color_(color), row_(row), col_(col)
    {
        oxygine::getStage()->addChild(this);
        if(auto iconName = getIconName(ChessPieceType::Pawn, color_); !iconName.empty())
        {
            setResAnim(res.getResAnim(iconName));
            setSize(100/2, 100 /2);
        }
    }

    ChessPieceType Pawn::type() const
    {
        return ChessPieceType::Pawn;
    }

    GameColor Pawn::color() const
    {
        return color_;
    }
    
    int Pawn::row() const
    {
        return row_;
    }

    int Pawn::col() const
    {
        return col_;
    }

    void Pawn::setPieceRow(int row)
    {
        row_ = row;
    }

    void Pawn::setPieceColumn(int col) 
    {
        col_ = col;
    }

    void Pawn::setPiecePosition(int row, int column, int cellSize)
    {
        row_ = row;
        col_ = column;
        setPosition((column + 1) * cellSize + cellSize / 4, (row + 1) * cellSize + cellSize / 4 );
    }

}
