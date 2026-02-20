#include "../Header/King.h"

#include "../Header/GameUtility.h"

#include "ox/Resources.hpp"
#include "ox/Stage.hpp"

namespace Game
{

    King::King(GameColor color,int row, int col, const oxygine::Resources& res)
        :IPiece(),color_(color), row_(row), col_(col)
    {
        oxygine::getStage()->addChild(this);
        if(auto iconName = getIconName(ChessPieceType::King, color_); !iconName.empty())
        {
            setResAnim(res.getResAnim(iconName));
            setSize(100/2, 100 /2);
        }
    }

    ChessPieceType King::type() const
    {
        return ChessPieceType::King;
    }

    GameColor King::color() const
    {
        return color_;
    }

    int King::row() const
    {
        return row_;
    }

    int King::col() const
    {
        return col_;
    }
        
    void King::setPieceRow(int row)
    {
        row_ = row;
    }

    void King::setPieceColumn(int col) 
    {
        col_ = col;
    }

    void King::setPiecePosition(int row, int column, int cellSize)
    {
        row_ = row;
        col_ = column;
        setPosition((column + 1) * cellSize + cellSize / 4, (row + 1) * cellSize + cellSize / 4 );
    }

}
