#ifndef TOKENIZER_H__
#define TOKENIZER_H__

#include "Base.h"

// This is the types of vars we can handle
enum VarTypes {
    VAR_STRING = 0,
    VAR_INT,
    VAR_NULL,
};


// This will hold vars, can be used in a vector for use when parsing
// NOTE: Vars with NULL as the name are passed as typed at the spot (eg: out("Hello world!") "Hello world!" <-- is the var, but it has not been defined, but still needs to be passed)
class Var {
    public:
        VarTypes VarType; 
        std::string VarContent;

        VarTypes DetectVarType(std::string Content) {
            std::string StringChars = "\"\'";
            std::string IntChars = "0123456789";

            

            for (auto i : Content) {
                for (auto str : StringChars) {
                    if (i == str) {
                        return VAR_STRING;
                    }
                }

                for (auto num : IntChars) {
                    if (i == num) {
                        return VAR_INT;
                    }
                }
            }

            return VAR_NULL;
        }

        void StoreVar(VarTypes type, std::string Content) {
            VarType = type;
            VarContent = Content;
        }

        

};



// This will hold the info for each token and its commands for running it later
// NOTE: This does not do the tokenizing, it just holds the tokens
class Token {
    public:
        int LineInFile = 0;
        int NumArg = 0;

        std::string token;
        std::vector<std::string> TokenContent; 
        std::vector<VarTypes> VartypeInArg;
        

};


std::vector<std::string> split(std::string str, std::string token){
    std::vector<std::string>result;

    while(str.size()){
        int index = str.find(token);

        if (index != std::string::npos) {
            result.push_back(str.substr(0,index));
            str = str.substr(index+token.size());

            if(str.size() == 0) result.push_back(str);
        }
        else {
            result.push_back(str);
            str = "";
        }
    }
    return result;
}

#endif