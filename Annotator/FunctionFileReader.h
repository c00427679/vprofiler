#ifndef FUNCTIONFILEREADER_H
#define FUNCTIONFILEREADER_H

// VProf libs
#include "Utils.h"
#include "../ExecutionTimeTracer/C++/OperationLog.h"

// STL libs
#include <memory>
#include <unordered_map>
#include <string>
#include <vector>
#include <set>
#include <fstream>
#include <stdexcept>
#include <algorithm>

struct LogInformation {
    unsigned int functionID;
    Operation op;
};

class FunctionFileReader {
    public:
        FunctionFileReader(const std::string _filename): 
        filename(_filename),
        funcMap(std::make_shared<std::unordered_map<std::string, std::string>>()), 
        opMap(std::make_shared<std::unordered_map<std::string, std::string>>()), 
        unqualifiedNames(std::make_shared<std::vector<std::string>>()), 
        qualifiedNames(std::make_shared<std::vector<std::string>>()),
        operationStrings({ "MUTEX_LOCK", "MUTEX_UNLOCK", "CV_WAIT",
                           "CV_BROADCAST", "CV_SIGNAL", "QUEUE_ENQUEUE",
                           "QUEUE_DEQUEUE", "MESSAGE_SEND", "MESSAGE_RECEIVE" }),
        beenParsed(false) {}
        
        // Parse the file
        void Parse();

        // Returns the function map generated by parse.
        // Parse must be called prior to this.
        std::shared_ptr<std::unordered_map<std::string, std::string>> GetFunctionMap();

        // Returns a map of qualified function name to log info struct
        std::shared_ptr<std::unordered_map<std::string, std::string>> GetOperationMap();

        // Returns a vector of all the qualified function names.
        // Parse must be called prior to this.
        std::shared_ptr<std::vector<std::string>> GetQualifiedFunctionNames();

        // Returns a vector of all the unqualified function names.
        // Parse must be called prior to this.
        std::shared_ptr<std::vector<std::string>> GetUnqualifiedFunctionNames();

    private:
        const std::string filename;
        std::shared_ptr<std::unordered_map<std::string, std::string>> funcMap;
        std::shared_ptr<std::unordered_map<std::string, std::string>> opMap;
        std::shared_ptr<std::vector<std::string>> unqualifiedNames;
        std::shared_ptr<std::vector<std::string>> qualifiedNames;

        std::set<std::string> operationStrings;

        bool beenParsed;
};

#endif