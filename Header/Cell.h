#pragma once

#include "ox/ColorRectSprite.hpp"
#include "../Header/GameUtility.h"
#include "ox/Sprite.hpp"

namespace oxygine
{
    class Resources;
} 

namespace Game
{   
    class IPiece;

    class Cell : public oxygine::ColorRectSprite
    {
    public:
        
        Cell(int row, int col, int cellSize);
        
        void setSelected(bool selected);
        bool isSelected() const;

        void setPiece(IPiece * piece);
        bool hasPiece() const;

        IPiece* getPiece() const;
 
    private:
        
        GameColor color_;
        IPiece * piece_ = nullptr;
        bool isSelected_ = false;
    };
}