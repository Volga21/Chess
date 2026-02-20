#include "../Header/Bishop.h"

#include "../Header/GameUtility.h"

#include "ox/Resources.hpp"
#include "ox/Stage.hpp"

namespace Game
{

    Bishop::Bishop(GameColor color,int row, int col, const oxygine::Resources& res)
        :IPiece(),color_(color), row_(row), col_(col)
    {
        oxygine::getStage()->addChild(this);
        if(auto iconName = getIconName(ChessPieceType::Bishop, color_); !iconName.empty())
        {
            setResAnim(res.getResAnim(iconName));
            setSize(100/2, 100 /2);
        }
    }

    ChessPieceType Bishop::type() const
    {
        return ChessPieceType::Bishop;
    }

    GameColor Bishop::color() const
    {
        return color_;
    }

    int Bishop::row() const
    {
        return row_;
    }

    int Bishop::col() const
    {
        return col_;
    }
        
    void Bishop::setPieceRow(int row)
    {
        row_ = row;
    }

    void Bishop::setPieceColumn(int col) 
    {
        col_ = col;
    }

    void Bishop::setPiecePosition(int row, int column, int cellSize)
    {
        row_ = row;
        col_ = column;
        setPosition((column + 1) * cellSize + cellSize / 4, (row + 1) * cellSize + cellSize / 4 );
    }

}
