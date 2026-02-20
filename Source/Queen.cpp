#include "../Header/Queen.h"

#include "../Header/GameUtility.h"

#include "ox/Resources.hpp"
#include "ox/Stage.hpp"

namespace Game
{

    Queen::Queen(GameColor color,int row, int col, const oxygine::Resources& res)
        :IPiece(),color_(color), row_(row), col_(col)
    {
        oxygine::getStage()->addChild(this);
        if(auto iconName = getIconName(ChessPieceType::Queen, color_); !iconName.empty())
        {
            setResAnim(res.getResAnim(iconName));
            setSize(100/2, 100 /2);
        }
    }

    ChessPieceType Queen::type() const
    {
        return ChessPieceType::Queen;
    }

    GameColor Queen::color() const
    {
        return color_;
    }

    int Queen::row() const
    {
        return row_;
    }

    int Queen::col() const
    {
        return col_;
    }
        
    void Queen::setPieceRow(int row)
    {
        row_ = row;
    }

    void Queen::setPieceColumn(int col) 
    {
        col_ = col;
    }

    void Queen::setPiecePosition(int row, int column, int cellSize)
    {
        row_ = row;
        col_ = column;
        setPosition((column + 1) * cellSize + cellSize / 4, (row + 1) * cellSize + cellSize / 4 );
    }

}
