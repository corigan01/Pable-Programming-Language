
#include "TokenHandler.h"



int main(int argc, char** argv) {

    std::string WorkingFileName = "";

    for (int i = 0; i < argc; i ++) {
        std::string InputArgs = std::string(argv[i]);
        dis.out(D_INFO, InputArgs);

        if (InputArgs == "--DEBUG_INFO") {
            dis.__DEBUG_ON = true;
        }

        else if (InputArgs == "--help") {
            std::cout << R"(
----------------------------------------------------------------------------------------------

--help          :   Brings up the Help menu for the compiler
--DEBUG_INFO    :   Gives all parsing and compile operations going on inside of the compiler
"Filename"      :   Gives a file for the compiler to compile

----------------------------------------------------------------------------------------------

Example on basic use -------------

./Compiler "main.pable"

            )" << std::endl;
        }


        else if (InputArgs[0] != '-' && InputArgs.find("./") == std::string::npos) {
            WorkingFileName = InputArgs;
        }

        else if (InputArgs.find("./") != std::string::npos) {
            ;
        }

        else {
            std::cout << "Input " << InputArgs << " is not a vailid input" << std::endl;
        }
        


    }

    if (WorkingFileName == "") {
        std::cout << "You must enter a file name to compile!" << std::endl;
        exit(1);
    }


    
    

    FileIO file;
    file.ReadFile(WorkingFileName);
    
    FileIO Token_file;
    
    Token_file.FileContent = {
        "help",
        "out $VAR_STRING",
        "in",
        "string",
        "int",
        "bool"};

    std::vector<std::string> VarTypesInToken = {"string", "int"};
    std::vector<Token> Tokens;

    std::vector<Var> Pable_vars; // This is a globles


    for (auto i : Token_file.FileContent) {
        auto output = split(i, " ");

        if (output.size() > 1) {
            Token token;
            token.token = output[0];
            output.erase(output.begin());
            token.TokenContent = output;
            token.NumArg = output.size();
            
            for (auto i : output) {
                if (i == "$VAR_STRING") {
                    token.VartypeInArg.push_back(VAR_STRING);
                }
                else if (i == "$VAR_INT") {
                    token.VartypeInArg.push_back(VAR_INT);
                }
                else {
                    dis.out(D_ERROR, "Arg type with name --> " + i + " can not be found in the list of args!");
                    usleep(1000);
                    exit(1);
                }
            }


            Tokens.push_back(token);
        }
        else if (output.size() == 1) {
            Token token;
            token.token = output[0];
            token.NumArg = 0;

            Tokens.push_back(token);
        }
        else {
            continue;
        }


    }





    auto PableFileContent = file.FileContent;

    for (auto i : PableFileContent) {
    WorkingLine ++;
        //std::cout << __LINE__ << std::endl;
        
        //i = RemoveWhiteSpace(i);

        
        
        dis.out(D_INFO, i);

        int commentfound = i.find("#");
        int eb = i.size();
        if (commentfound != -1) {
            for (int e = 0; e < (eb - commentfound); e++ ) {
                i.erase(i.begin() + commentfound);
            }
        }


        int found_input = i.find("in(");
        eb = i.size();
        if (found_input != -1) {
            std::string pableInput;

            std::cout << "Pable Program input: ";
            std::getline (std::cin, pableInput);
            
            dis.out(D_FILE, "Got input with content of --> " + pableInput);

            pableInput.insert(0, "\"");
            pableInput.push_back('\"');

            for (int e = 0; e < 4; e ++) {
                i.erase(i.begin() + found_input);
            }

            i.insert(found_input, pableInput);
        }



        RemoveWhiteSpace(i);

        //

        if (FoundStringDef(i)) {
            dis.out(D_INFO, "Found useless var");
            continue; 
        }


        

        if (i.size() > 0) {
            size_t found = i.find_first_of(" (=");

            std::string FoundToken = i;
            std::string args = "";

            if (found != std::string::npos) {
                dis.out(D_FILE, "Found out command at a pos : " + std::to_string(found));

                
                for (int e = found; e < i.size(); e++) {
                    args.push_back(FoundToken[found]);
                    FoundToken.erase(FoundToken.begin() + found);
                }

                RemoveWhiteSpace(args);

                dis.out(D_FILE, "Found token --> \'" + FoundToken + "\' with args --> \'" + args + "\'");
            }
            bool FoundInArray = 0;
            bool FoundComment = 0;
            for (auto e : Tokens) {
                if (FoundToken == e.token) {
                    FoundInArray = 1;
                }
            }

            if (!FoundInArray) {
                Pable_ERROR( "Token with name --> \'" + FoundToken + "\' was not found in the list of tokens!\n\tOf command --> " + i);
            }

            // This needs to be fixed
            if (FoundToken == "out") {
                if (args.size() > 0) {
                    if (args[0] == '(') {
                        args.erase(args.begin());

                        RemoveWhiteSpace(args);


                        if (FoundStringDef(args)) {

                            std::cout << ExtractStringDef(args) << std::endl;

                        }
                        else {
                                
                            if (!IsfoundinVar(Pable_vars, args)) {
                                Pable_ERROR("Need '\"' to begin a string def because var with name could not be found in the list of defined vars!");
                            }
                        }
                    }
                    else {
                        Pable_ERROR("Need '(' to begin a function call!");
                    }
                }
            }
            else if (FoundToken == "string") {
                StringSplit splite = SplitString(args, " (");

                std::string VarName = splite.BeforeChar;
                std::string LatArg = splite.AfterChar;
                

                RemoveWhiteSpace(LatArg);

                if (CheckIfEqual(LatArg)) {
                    LatArg.erase(LatArg.begin());
                }
                else {
                    Pable_ERROR("You need to have a = to define a var");
                }

                RemoveWhiteSpace(LatArg);

                Var TempVar;

                if (VAR_STRING != DetectVarType(LatArg)) {
                    Pable_ERROR("A string def needs to have a string as a definer!");
                }


                if (FoundStringDef(LatArg)) {
                    
                    std::string VarContent = ExtractStringDef(LatArg);
                
                    dis.out(D_INFO, "Found Var with name of \'" + VarName + "\' and content of --> \'" + VarContent + "\'");

                    TempVar.StoreVar(VAR_STRING, VarContent, VarName);

                    Pable_vars.push_back(TempVar);
                }
                else {
                    Pable_ERROR("Unknown char --> " + LatArg[0]);
                }


            }
            else if (FoundToken == "int") {
                StringSplit splite = SplitString(args, " (");

                std::string VarName = splite.BeforeChar;
                std::string LatArg = splite.AfterChar;

                RemoveWhiteSpace(LatArg);

                if (CheckIfEqual(LatArg)) {
                    LatArg.erase(LatArg.begin());
                }
                else {
                    Pable_ERROR("You need to have a = to define a var");
                }

                RemoveWhiteSpace(LatArg);

                Var TempVar;

                if (VAR_INT != DetectVarType(LatArg)) {
                    Pable_ERROR("A int def needs to have a int as a definer!");
                }

                std::string FirstChar = std::to_string(LatArg[0]);
                if (FirstChar.find_first_of("0123456789") != std::string::npos) {
                    
                    std::string VarContent = std::to_string(ExtractIntDef(LatArg));

                
                    dis.out(D_INFO, "Found Var with name of \'" + VarName + "\' and content of --> \'" + VarContent + "\'");

                    TempVar.StoreVar(VAR_INT, VarContent, VarName);

                    Pable_vars.push_back(TempVar);
                }
                else {
                    Pable_ERROR("Unknown char --> " + LatArg[0]);
                }

            }

            else if (FoundToken == "help") {
                std::cout << D_COLOR::greenM << R"(
Help with the Pable Programming language
-------------------------------

Built-ins: in(), out()
Variable Types: string, int
--------------------------------

Getting started program:
--------------------------------
string MyStr = in() # this will set the string \'MyStr\' to whatever you input
out(MyStr) # this will output the content of \'MyStr\'
--------------------------------)" << D_COLOR::defM << std::endl;


            }


            
            else {
                Pable_ERROR("Command not supported yet, we are working on it!");
            }
        
            


        }            
        
        
        else {
            dis.out(D_WARNING, "Null line");
        }

        //std::cout << __LINE__ << std::endl;


    }
 
    


    return 0;
}

