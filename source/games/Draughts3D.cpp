
#include <string>
#include <irrlicht.h>
#include <Piece.h>
#include <Game3D.h>
#include <games/Draughts3D.h>

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


BoardConfig Draughts3D::configBoard(std::string variant){
    BoardConfig config;
    if(variant == "INTERNATIONAL_DRAUGHTS"){
            config.rowCount = 10;
            config.pieceCount = 40;
            config.inverseBoard = false;
    }else if(variant == "ENGLISH_DRAUGHTS"){
            config.rowCount = 8;
            config.pieceCount = 24;
            config.inverseBoard = false;
    }else if(variant == "AMERICAN_DRAUGHTS"){
            config.rowCount = 8;
            config.pieceCount = 24;
            config.inverseBoard = false;
    }if(variant == "GHANIAN_DRAUGHTS"){
            config.rowCount = 10;
            config.pieceCount = 40;
            config.inverseBoard = true;
    }


    return config;
};

Square* Draughts3D::createBoardContent(std::string board_position){

    //TODO

    return this->squareList;
}

//white pieces captured
std::vector<Piece*> Draughts3D::offBoardWhitePieces(std::string board_position){
    std::vector<Piece*> pce_list;
    //TODO
    return pce_list;
};

//black pieces captured
std::vector<Piece*> Draughts3D::offBoardBlackPieces(std::string board_position){
    std::vector<Piece*> pce_list;
    //TODO
    return pce_list;
};

void Draughts3D::createPieceModel(Piece* p){

};

bool Draughts3D::isWhitePieceModel(){
    return false; // NOT YET IMPLEMENTED
};

std::string Draughts3D::getPieceName(){
    return "";
};

float Draughts3D::getModelBottom(Piece* pce){
    return pce->bottom;
};

Piece* Draughts3D::getInternalPiece(std::string sqn){
    //TODO - Call external method from here
    return 0;
};


/**
Calls the external method - e.g node, android, iOS etc
*/
MoveResult Draughts3D::makeMove(std::string from, std::string to){

    MoveResult meve_result;


    return meve_result;
};


float Draughts3D::getFlyHeight(Piece* pce, float to){
    if(to == this->OFF_BOARD){
        return 2.5f;
    }else{
        return 0.7f;
    }

};
