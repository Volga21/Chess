cmake_minimum_required (VERSION 3.1)
project (MyChess)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(../oxygine-framework/ oxygine-framework)
add_definitions(${OXYGINE_DEFINITIONS})
include_directories(${OXYGINE_INCLUDE_DIRS})
link_directories(${OXYGINE_LIBRARY_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OXYGINE_CXX_FLAGS}")

add_executable(MyChess
	Header/ChessView.h
	Source/ChessView.cpp
	Header/ChessModel.h
	Source/ChessModel.cpp
	Header/Cell.h
	Source/Cell.cpp
    Source/main.cpp
	Header/GameUtility.h
	Header/IPiece.h
	Header/Pawn.h
	Source/Pawn.cpp
	Header/Bishop.h
	Source/Bishop.cpp
	Header/King.h
	Source/King.cpp
	Header/Knight.h
	Source/Knight.cpp
	Header/Rook.h
	Source/Rook.cpp
	Header/Queen.h
	Source/Queen.cpp
)
target_link_libraries(MyChess ${OXYGINE_CORE_LIBS})


