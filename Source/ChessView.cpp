#include "../Header/ChessView.h"
#include "../Header/ChessModel.h"

#include "ox/ColorRectSprite.hpp"


namespace Game
{
    ChessView::ChessView(float x, float y, int cellSize)
        :Actor()
    {
        setPosition(x, y);
        createBoard(cellSize);
    }

    ChessView::~ChessView(){};

    void ChessView::createBoard(int cellSize)
    {
        oxygine::spColorRectSprite background = new oxygine::ColorRectSprite();
        background->setSize(cellSize * 8 + 20, cellSize * 8 + 20);
        background->setColor(oxygine::Color(139, 69, 19, 255));
        background->setPosition(-10, -10);
        addChild(background);
    }

    void ChessView::setModel(std::unique_ptr<Game::ChessModel> model)
    {
        model_ = std::move(model);
        for(auto i = 0; i < 8; ++i)
        {
            for(auto j = 0; j < 8; ++j)
                addChild(model_->data(i,j));
        }
    }
}