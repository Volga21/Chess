#include "../Header/ChessModel.h"

#include "../Header/Pawn.h"
#include "../Header/Bishop.h"
#include "../Header/King.h"
#include "../Header/Knight.h"
#include "../Header/Queen.h"
#include "../Header/Rook.h"

namespace
{
    Game::spPiece getPiece(Game::ChessPieceType type, Game::GameColor color, int row, int col, const oxygine::Resources& res)
    {
        switch (type)
        {
        case Game::ChessPieceType::Pawn:
            return new Game::Pawn(color, row, col, res); 
            break;
        case Game::ChessPieceType::King:
            return new Game::King(color, row, col, res); 
            break;
        case Game::ChessPieceType::Knight:
            return new Game::Knight(color, row, col, res); 
            break;
        case Game::ChessPieceType::Bishop:
            return new Game::Bishop(color, row, col, res); 
            break;
        case Game::ChessPieceType::Queen:
            return new Game::Queen(color, row, col, res); 
            break;
        case Game::ChessPieceType::Rook:
            return new Game::Rook(color, row, col, res); 
            break;
        default:
            break;
        }
    }

    bool isValid(int row, int col)
    {
        if(row < 0 || col < 0 || row > 7 || col > 7)
            return false;
        return true;
    }
}

namespace Game
{
    ChessModel::ChessModel(int cellSize)
    :cellSize_(cellSize)
    {
        gameResources_.loadXML("../data/res.xml");
        cells_.resize(8);

        for(auto i = 0; i < 8; ++i)
        {
            for(auto j = 0; j < 8; ++j)
            {
                cells_[i].emplace_back(new Cell(i, j, cellSize));
                cells_[i][j]->addEventListener(oxygine::TouchEvent::CLICK, [this, i, j](oxygine::Event* ev) {
                        if(auto moveType = getMoveType(i, j); isPieceSelected_ && moveType != MoveType::CantMove )
                        {
                            cells_[selectedRow_][selectedCol_]->setSelected(false);
                            cells_[selectedRow_][selectedCol_]->getPiece()->move( i, j, cellSize_);
                            
                            cells_[i][j]->setPiece(cells_[selectedRow_][selectedCol_]->getPiece());
                            cells_[selectedRow_][selectedCol_]->setPiece(nullptr);
                            isPieceSelected_ = false;    
                            gameMove_ = gameMove_ == GameColor::White ? GameColor::Black : GameColor::White;                       
                        }                          
                        else
                            return;
                    });
                auto [pieceType, pieceColor] = getStartPosition(i, j);
                if(pieceType != ChessPieceType::None)
                {
                    auto pPiece = getPiece(pieceType, pieceColor, i, j, gameResources_);
                    pPiece->setPiecePosition(i, j, cellSize);
                    cells_[i][j]->setPiece(pPiece.get());
                    pPiece->addEventListener(oxygine::TouchEvent::CLICK, [this, piece = pPiece.get()](oxygine::Event* ev) {
                        if(isPieceSelected_ )
                        {
                            if(selectedRow_ == piece->row() && selectedCol_ == piece->col())
                            {
                                cells_[selectedRow_][selectedCol_]->setSelected(false);  
                                isPieceSelected_ = false;
                                return;
                            }
                            auto moveType = getMoveType(piece->row(), piece->col());
                            if(moveType == MoveType::CantMove)
                                return;
                            cells_[selectedRow_][selectedCol_]->setSelected(false);
                            cells_[selectedRow_][selectedCol_]->getPiece()->move(piece->row(), piece->col(), cellSize_);    
                            
                            cells_[piece->row()][piece->col()]->setPiece(cells_[selectedRow_][selectedCol_]->getPiece());
                            cells_[selectedRow_][selectedCol_]->setPiece(nullptr);                            
                            isPieceSelected_ = false;

                            gameMove_ = gameMove_ == GameColor::White ? GameColor::Black : GameColor::White;
                        }
                        else if(gameMove_ == piece->color())
                        {
                            selectedRow_ = piece->row();
                            selectedCol_ = piece->col();
                        
                            isPieceSelected_ = true;    
                            cells_[selectedRow_][selectedCol_]->setSelected(true);
                        }
                        });
                }
            }
        }
    }

    spCell ChessModel::data(int row, int column) const
    {
        if(!isValid(row, column))
            assert(false);

        return cells_[row][column];
    }

    void ChessModel::setData(int row, int column, ChessPieceType type)
    {
        if(!isValid(row, column))
            assert(false);
    }  

    MoveType ChessModel::getMoveType(int row, int column)
    {
        if(row == selectedRow_ && column == selectedCol_)
            return MoveType::CantMove;

        if(!cells_[selectedRow_][selectedCol_]->hasPiece())
            return MoveType::CantMove;

        if(cells_[row][column]->hasPiece() && cells_[selectedRow_][selectedCol_]->getPiece()->color() == cells_[row][column]->getPiece()->color())
            return MoveType::CantMove;

        switch (cells_[selectedRow_][selectedCol_]->getPiece()->type())
        {
            case Game::ChessPieceType::Pawn:
                return getMoveTypeForPawn(row, column);
                break;
            case Game::ChessPieceType::Rook:
                return getMoveTypeForRook(row, column);
                break;
            case Game::ChessPieceType::Knight:
                return getMoveTypeForKnight(row, column);
                break;
            case Game::ChessPieceType::King:
                return getMoveTypeForKing(row, column);
                break;
            case Game::ChessPieceType::Queen:
                return getMoveTypeForQueen(row, column);
                break;
            case Game::ChessPieceType::Bishop:
                return getMoveTypeForBishop(row, column);
                break;
        }
         return MoveType::CantMove;
    }

    MoveType ChessModel::getMoveTypeForPawn(int row, int column)
    {

        auto pieceColor = cells_[selectedRow_][selectedCol_]->getPiece()->color(); 
        
        if(pieceColor == Game::GameColor::White)  
        {
            if(selectedRow_ == 0 || selectedRow_ - 1 != row)
                return MoveType::CantMove;
        }
        else if(pieceColor == Game::GameColor::Black)  
        {
             if(selectedRow_ == 7 || selectedRow_ + 1 != row)
                return MoveType::CantMove;
        }  
        
         if (selectedRow_ + 1 == row || selectedRow_ - 1 == row)
            {
                if((column + 1 == selectedCol_ || column - 1 == selectedCol_) && cells_[row][column]->hasPiece() && cells_[row][column]->getPiece()->color() != pieceColor)
                    return MoveType::Move;
                if(column == selectedCol_ && !cells_[row][column]->hasPiece())
                    return MoveType::Move;
            }

        return MoveType::CantMove;
    }

    MoveType ChessModel::getMoveTypeForRook(int row, int column)
    {
        auto pieceColor = cells_[selectedRow_][selectedCol_]->getPiece()->color(); 

        if(row == selectedRow_)
        {
            for(auto i = selectedCol_ > column ? selectedCol_ - 1 : selectedCol_ + 1; i != column; selectedCol_ > column ? --i : ++i)
            {
                if(cells_[row][i]->hasPiece())
                    return MoveType::CantMove;
            }
           
        }
        else if(column == selectedCol_)
        {
            for(auto i = selectedRow_ > row ? selectedRow_- 1 : 1 + selectedRow_; i != row; selectedRow_ > row ? --i : ++i)
            {
                if(cells_[i][column]->hasPiece())
                    return MoveType::CantMove;
            }                
        }
        else
            return MoveType::CantMove;

         if(!cells_[row][column]->hasPiece())
            return MoveType::Move;
        else if(cells_[row][column]->getPiece()->color() != pieceColor)
            return MoveType::Move;

        return MoveType::CantMove;
    }

    MoveType ChessModel::getMoveTypeForBishop(int row, int column)
    {
        auto pieceColor = cells_[selectedRow_][selectedCol_]->getPiece()->color(); 

        const int directions[4][2] = {{-1,-1}, {-1,1}, {1,-1}, {1,1}};
        std::vector<std::pair<int,int>> moves;

        for (auto& dir : directions) 
        {
            for (int step = 1; step < 8; ++step)
            {
                auto newRow = selectedRow_ + dir[0] * step;
                auto newCol = selectedCol_ + dir[1] * step;
                
                if (!isValid(newRow, newCol))
                    break;
                
                if (cells_[newRow][newCol]->hasPiece())
                {
                    if(cells_[newRow][newCol]->getPiece()->color() == pieceColor)
                        break;

                    moves.emplace_back(newRow, newCol);
                    break;
                } 
                moves.emplace_back(newRow, newCol);
            }
        }

        for(const auto& info : moves)
        {
            if(info.first == row && info.second == column)
                return MoveType::Move;
        }

        return MoveType::CantMove;

    }

    MoveType ChessModel::getMoveTypeForQueen(int row, int column)
    {
        if(getMoveTypeForRook(row, column) != MoveType::CantMove)
            return MoveType::Move;
        if(getMoveTypeForBishop(row, column) != MoveType::CantMove)
            return MoveType::Move;

        return MoveType::CantMove;
    }

    MoveType ChessModel::getMoveTypeForKing(int row, int column)
    {
        auto pieceColor = cells_[selectedRow_][selectedCol_]->getPiece()->color(); 
        std::vector<std::pair<int,int>> moves;

        for (int i = -1; i <= 1; ++i)
        {
            for (int j = -1; j <= 1; ++j) 
            {
                if (i == 0 && j == 0)
                    continue;
                
                auto newRow = selectedRow_ + i;
                auto newCol = selectedCol_ + j;
                
                if (!isValid(newRow, newCol))
                    continue;
                
                if (cells_[newRow][newCol]->hasPiece())
                {
                    if(cells_[newRow][newCol]->getPiece()->color() == pieceColor)
                        continue;

                    moves.emplace_back(newRow, newCol);
                    continue;
                } 
                moves.emplace_back(newRow, newCol);
            }
        }

        for(const auto& info : moves)
        {
            if(info.first == row && info.second == column)
                return MoveType::Move;
        }

        return MoveType::CantMove;

    }

    MoveType ChessModel::getMoveTypeForKnight(int row, int column)
    {
        auto pieceColor = cells_[selectedRow_][selectedCol_]->getPiece()->color(); 

        const int jumps[8][2] = {
        {-2,-1}, {-2,1}, {-1,-2}, {-1,2},
        {1,-2}, {1,2}, {2,-1}, {2,1}
        };
    
        for (auto& jump : jumps) 
        {
            auto newRow = selectedRow_ + jump[0];
            auto newCol = selectedCol_ + jump[1];
            
            if (!isValid(newRow, newCol))
                continue;
            
            if (newRow == row && newCol == column) 
            {
                if(cells_[newRow][newCol]->hasPiece())
                {
                    if(cells_[newRow][newCol]->getPiece()->color() != pieceColor)
                    {
                        return MoveType::Move;
                    }
                    else
                        return MoveType::CantMove;
                }
                else
                    return MoveType::Move;
            }
        }
        return MoveType::CantMove;
    }

}