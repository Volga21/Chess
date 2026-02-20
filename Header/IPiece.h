#pragma once

#include "../Header/GameUtility.h"
#include "ox/Sprite.hpp"

namespace Game
{
    class IPiece : public oxygine::Sprite
    {
    public:
        void move(int row, int column, int cellSize)
        {
            float targetX = ( column + 1) * cellSize + cellSize / 4;
            float targetY = (row + 1 )* cellSize + cellSize /4;
            
            oxygine::spTween tween = oxygine::createTween(
                oxygine::Actor::TweenPosition(oxygine::Vector2(targetX, targetY)),
                900, 
                1,
                false
            );

             tween->addDoneCallback([this, row, column](oxygine::Event*) {
                setPieceRow(row);
                setPieceColumn(column);
            });

            addTween(tween);
        }

        void deletePiece()
        {
            setTouchEnabled(false);
        
            oxygine::spTween fadeTween = addTween(Sprite::TweenAlpha(0), 500);
            
            fadeTween->addDoneCallback([this](oxygine::Event*) {
                detach(); 
            });
            
        }
        
        virtual void setPiecePosition(int row, int column, int cellSize) = 0;

        virtual ChessPieceType type() const = 0;
        virtual GameColor color() const = 0;

        virtual int row() const = 0;
        virtual int col() const = 0;
        
        virtual void setPieceRow(int row) = 0;
        virtual void setPieceColumn(int col) = 0;

        virtual ~IPiece() = default;
    };
}