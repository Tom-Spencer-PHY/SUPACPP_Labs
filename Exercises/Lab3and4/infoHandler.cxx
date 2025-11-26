#include "infoHandler.h"

infoHandler::infoHandler(){
    this->setPrintLevel("info");
}

infoHandler::infoHandler(std::string level){
    this->setPrintLevel(level);
}

void infoHandler::print(printLevels lvl, std::string message){
    if (m_verbosity >= lvl){
        std::cout << m_warnMap[lvl] << message << std::endl;
    }
}

void infoHandler::setPrintLevel(std::string lvl){
    m_level = lvl;
    m_verbosity = m_lvlMap[m_level];
}