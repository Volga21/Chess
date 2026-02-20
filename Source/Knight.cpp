#include "../Header/Knight.h"

#include "../Header/GameUtility.h"

#include "ox/Resources.hpp"
#include "ox/Stage.hpp"

namespace Game
{

    Knight::Knight(GameColor color,int row, int col, const oxygine::Resources& res)
        :IPiece(),color_(color), row_(row), col_(col)
    {
        oxygine::getStage()->addChild(this);
        if(auto iconName = getIconName(ChessPieceType::Knight, color_); !iconName.empty())
        {
            setResAnim(res.getResAnim(iconName));
            setSize(100/2, 100 /2);
        }
    }

    ChessPieceType Knight::type() const
    {
        return ChessPieceType::Knight;
    }

    GameColor Knight::color() const
    {
        return color_;
    }

    int Knight::row() const
    {
        return row_;
    }

    int Knight::col() const
    {
        return col_;
    }
        
    void Knight::setPieceRow(int row)
    {
        row_ = row;
    }

    void Knight::setPieceColumn(int col) 
    {
        col_ = col;
    }

    void Knight::setPiecePosition(int row, int column, int cellSize)
    {
        row_ = row;
        col_ = column;
        setPosition((column + 1) * cellSize + cellSize / 4, (row + 1) * cellSize + cellSize / 4 );
    }

}
