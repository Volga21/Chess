#include "../Header/Cell.h"
#include "../Header/IPiece.h"

#include "ox/Color.hpp"
#include "ox/Resources.hpp"
#include "ox/Stage.hpp"

namespace Game
{
    Cell::Cell(int row, int col, int cellSize)
        :oxygine::ColorRectSprite()
    {
        setSize(cellSize - 2, cellSize - 2); 
        setPosition(col * cellSize, row * cellSize);
        color_ = static_cast<GameColor>((col + row) % 2);

        if (color_ == GameColor::White)
            setColor(oxygine::Color(240, 217, 181, 255));
        else
            setColor(oxygine::Color(181, 136, 99, 255));
        oxygine::getStage()->addChild(this);
    }

    void Cell::setSelected(bool selected)
    {
        isSelected_ = selected;
        if (isSelected_)
        {
            setColor(oxygine::Color(255, 255, 0, 128));
        }
        else
        {
            if (color_ == GameColor::White)
                setColor(oxygine::Color(240, 217, 181, 255));
            else
                setColor(oxygine::Color(181, 136, 99, 255));
        }
    }

    bool Cell::isSelected() const
    {
        return isSelected_;
    }

    void Cell::setPiece(IPiece * piece)
    {
        if(piece_ != nullptr && piece != nullptr)
        {
            piece_->deletePiece();
        }
        piece_ = piece;
    }

    bool Cell::hasPiece() const
    {
        return piece_ != nullptr;
    }

    IPiece* Cell::getPiece() const
    {
        return piece_;
    }
 
}