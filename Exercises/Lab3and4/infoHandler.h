#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>

#pragma once

enum printLevels {FATAL=0, WARNING=1, INFO=2, VERBOSE=3};

class infoHandler{
    public: 
        infoHandler();
        infoHandler(std::string level);
        void print(printLevels lvl, std::string message);
        void setPrintLevel(std::string lvl);

    private:
        std::string m_level;
        unsigned int m_verbosity;
        std::unordered_map<std::string, unsigned int> m_lvlMap = {{"silent", 0}, {"warning", 1}, {"info", 2}, {"verbose", 3}};
        std::unordered_map<printLevels, std::string> m_warnMap = {{FATAL, "Fatal: "}, {WARNING, "Warning: "}, {INFO, "Info: "}, {VERBOSE, "Verbose: "}};
};