#include "displayout.h"
#include "Base.h"
#include "TokenFunctions.h"




int main() {

    //dis.out(D_INFO, "Starting Main");

    FileIO file;
    file.ReadFile("../Pable Source/Program.pable");
    
    FileIO Token_file;
    Token_file.ReadFile("Pable Tokens/Tokens.txt");

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


        int found_input = i.find("in()");
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

        if (i[0] == '\"') {
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
                dis.out(D_ERROR, "Token with name --> \'" + FoundToken + "\' was not found in the list of tokens!\n\tOf command --> " + i); // token not found ERROR
                break;
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
                                dis.out(D_ERROR, "Need '\"' to begin a string def because var with name could not be found in the list of defined vars!");
                                break;
                            }
                        }
                    }
                    else {
                        dis.out(D_ERROR, "Need '(' to begin a function call!");
                        break;
                    }
                }
            }
            else if (FoundToken == "string") {
                int clipoff = args.find_first_of(" =");

                std::string VarName = "";
                std::string LatArg = args;
                for (int e = 0; e < clipoff; e++) {
                    VarName.push_back(args[e]);
                    LatArg.erase(LatArg.begin());
                }

                RemoveWhiteSpace(LatArg);

                if (!FoundStringDef(LatArg)) {
                    LatArg.erase(LatArg.begin());
                }
                else {
                    dis.out(D_ERROR, "You need to have a = to define a var");
                    break;
                }

                RemoveWhiteSpace(LatArg);

                dis.out(D_INFO, LatArg);
                dis.out(D_INFO, VarName);

                Var TempVar;

                if (VAR_STRING != DetectVarType(LatArg)) {
                    dis.out(D_ERROR, "A string def needs to have a string as a definer!");
                    usleep(1000);
                    exit(1);
                }


                if (LatArg[0] == '\"') {
                    
                    std::string VarContent = ExtractStringDef(LatArg);

                
                    dis.out(D_INFO, "Found Var with name of \'" + VarName + "\' and content of --> \'" + VarContent + "\'");

                    TempVar.StoreVar(VAR_STRING, VarContent, VarName);

                    Pable_vars.push_back(TempVar);
                }
                else {
                    dis.out(D_ERROR, "Unknown char --> " + LatArg[0]);
                    usleep(1000);
                    exit(1);
                }


            }
            else if (FoundToken == "int") {
                int clipoff = args.find_first_of(" =");

                std::string VarName = "";
                std::string LatArg = args;
                for (int e = 0; e < clipoff; e++) {
                    VarName.push_back(args[e]);
                    LatArg.erase(LatArg.begin());
                }

                RemoveWhiteSpace(LatArg);

                if (!FoundStringDef(LatArg)) {
                    LatArg.erase(LatArg.begin());
                }
                else {
                    dis.out(D_ERROR, "You need to have a = to define a var");
                    break;
                }

                RemoveWhiteSpace(LatArg);

                dis.out(D_INFO, LatArg);
                dis.out(D_INFO, VarName);

                Var TempVar;

                if (VAR_INT != DetectVarType(LatArg)) {
                    dis.out(D_ERROR, "A int def needs to have a int as a definer!");
                    usleep(1000);
                    exit(1);
                }

                std::string FirstChar = std::to_string(LatArg[0]);
                if (FirstChar.find_first_of("0123456789") != std::string::npos) {
                    
                    std::string VarContent = std::to_string(ExtractIntDef(LatArg));

                
                    dis.out(D_INFO, "Found Var with name of \'" + VarName + "\' and content of --> \'" + VarContent + "\'");

                    TempVar.StoreVar(VAR_INT, VarContent, VarName);

                    Pable_vars.push_back(TempVar);
                }
                else {
                    dis.out(D_ERROR, "Unknown char --> " + LatArg[0]);
                    usleep(1000);
                    exit(1);
                }

            }

            else if (FoundToken == "help") {
                std::cout << R"(
                Help with the Pable Programming language
                -------------------------------
    
                Built-ins: in(), out()
                Variable Types: string, int
                --------------------------------
                
                Getting started program:
                --------------------------------
                string MyStr = in() # this will set the string \'MyStr\' to whatever you input
                out(MyStr) # this will output the content of \'MyStr\'
                --------------------------------

                )" << std::endl;


            }


            
            else {
                dis.out(D_ERROR, "Command not supported!");
                continue;
            }
        
            


        }            
        
        
        else {
            dis.out(D_WARNING, "Null line");
        }

        //std::cout << __LINE__ << std::endl;


    }
 
	usleep(1000);

    return 0;
}

