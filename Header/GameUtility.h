#pragma once

#include <utility>
#include <string>

namespace Game
{
    enum class GameColor 
    { 
        White,
        Black,

        None
    };

    enum class ChessPieceType
    {
        King,
        Queen,
        Rook,
        Bishop,
        Knight,
        Pawn,
        None
    };

    enum class MoveType
    {
        Move,
        CantMove
    };

    inline std::pair<ChessPieceType, GameColor> getStartPosition(int row, int column)
    { 
        if(row == 1 || row == 6)
        {
            return {Game::ChessPieceType::Pawn, row == 1 ? Game::GameColor::Black : Game::GameColor::White};
        }
        else if(row == 0 || row == 7)
        {
            if(column == 0 || column ==7)
            {
                return {Game::ChessPieceType::Rook, row == 0 ? Game::GameColor::Black : Game::GameColor::White};
            }
            else if(column == 1 || column == 6)
            {
                return {Game::ChessPieceType::Knight, row == 0 ? Game::GameColor::Black : Game::GameColor::White};
            }
            else if(column == 2|| column == 5)
            {
                return {Game::ChessPieceType::Bishop, row == 0 ? Game::GameColor::Black : Game::GameColor::White};
            }
            else if(column == 3)
            {
                return {Game::ChessPieceType::Queen, row == 0 ? Game::GameColor::Black : Game::GameColor::White};
            }
            else if(column == 4)
            {
                return {Game::ChessPieceType::King, row == 0 ? Game::GameColor::Black : Game::GameColor::White};
            }
        }
        return {Game::ChessPieceType::None, Game::GameColor::None};
    }

    inline std::string getIconName(ChessPieceType type, GameColor color)
    {
        switch (type)
        {
            case ChessPieceType::King:
                return color == GameColor::White ? "white_king" : "black_king";

            case ChessPieceType::Knight:
                return color == GameColor::White ? "white_knight" : "black_knight";
            
            case ChessPieceType::Bishop:
                return color == GameColor::White ? "white_bishop" : "black_bishop";

            case ChessPieceType::Pawn:
                return color == GameColor::White ? "white_pawn" : "black_pawn";
            
            case ChessPieceType::Rook:
                return color == GameColor::White ? "white_rook" : "black_rook";

            case ChessPieceType::Queen:
                return color == GameColor::White ? "white_queen" : "black_queen";
               
            default:
                break;
        }
        return {};
    }
}