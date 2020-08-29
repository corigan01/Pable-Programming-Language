
#include "TokenHandler.h"



int main(int argc, char** argv) {
    auto start = std::chrono::high_resolution_clock::now();
    std::ios_base::sync_with_stdio(false); 
    
    std::string WorkingFileName = "";

    for (int i = 0; i < argc; i ++) {
        std::string InputArgs = std::string(argv[i]);
        dis.out(D_INFO, InputArgs);

        if (InputArgs == "--DEBUG_INFO") {
            dis.__DEBUG_ON = true;
        }

        else if (InputArgs == "--help") {
            std::cout << R"(
   ___       __   __      _____                _ __       
  / _ \___ _/ /  / /__   / ___/__  __ _  ___  (_) /__ ____
 / ___/ _ `/ _ \/ / -_) / /__/ _ \/  ' \/ _ \/ / / -_) __/
/_/   \_,_/_.__/_/\__/  \___/\___/_/_/_/ .__/_/_/\__/_/   
 _____________________________________/_/________________ 
/___/___/___/___/___/___/___/___/___/___/___/___/___/___/ 

CopyRight (C) 2020 Team @Hexcode - Repl.it : Github - Corigan01

----------------------------------------------------------------------------------------------
Compiler Options:

--help          :   Brings up the Help menu for the compiler
--DEBUG_INFO    :   Gives all parsing and compile operations going on inside of the compiler
"Filename"      :   Gives a file for the compiler to compile

----------------------------------------------------------------------------------------------

Example on basic use 

./Compiler "main.pable"

----------------------------------------------------------------------------------------------
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
        "bool",
        "color_out",
        "if"};

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

//Pabble_in()
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
//Pabble_Randomizer
        int foundRand_input = i.find("rand(");
        eb = i.size();
        if (found_input != -1) {
            
        }
            

/* 
------------------------------------------------ OPERATORS SEGMENT ------------------------------------------------
*/

    BeginAgain:

    found_input = i.find_first_of("*/+-");
    eb = i.size();
    if (found_input != -1) {
        int InsertSizeB = 0, InsertSizeE = 0;
        StringSplit splite = SplitString(i, "*/+-");
        
        RemoveWhiteSpace(splite.AfterChar);
        RemoveWhiteSpaceBack(splite.BeforeChar);

        // before char operations first check


        std::string FinalS1 = "";
        std::string FinalS2 = "";

        std::string FinalS2Pre = splite.AfterChar;

        int FoundPos1 = 0;

        int found_S1_back = splite.BeforeChar.find_last_of("= (");
        FoundPos1 = found_S1_back;
        for (int e = 0; e < found_S1_back + 1; e++) {
            InsertSizeB++;
            splite.BeforeChar.erase(splite.BeforeChar.begin());
        }

        FinalS1 = splite.BeforeChar;
        bool FirstCharNeg = 0;
        
        if (!(FinalS1.size() > 0)) {

            FirstCharNeg = 1;
            
            splite.AfterChar.erase(splite.AfterChar.begin());

            std::cout << "why!!!!" << std::endl;
            StringSplit FinalSpliteDiff = SplitString(splite.AfterChar, "*/+-");

            if (FinalSpliteDiff.BeforeChar.size() == 0) {
                goto FinalAfterCal;
            }
        
            RemoveWhiteSpace(FinalSpliteDiff.AfterChar);
            RemoveWhiteSpaceBack(FinalSpliteDiff.BeforeChar);

            // after check but still before char

            found_S1_back = FinalSpliteDiff.BeforeChar.find_last_of("= (");
            FoundPos1 = found_input;
            std::cout << FinalSpliteDiff.BeforeChar << std::endl;
            if (found_S1_back != -1)  {
                for (int e = 0; e < found_S1_back + 1; e++) {
                    InsertSizeB++;
                    FinalSpliteDiff.BeforeChar.erase(FinalSpliteDiff.BeforeChar.begin());
                }
            }
            

            FinalS2Pre = FinalSpliteDiff.AfterChar;

            FinalS1 = FinalSpliteDiff.BeforeChar;
        }
        
        InsertSizeE = FinalS1.size() + FinalS2Pre.size();

        RemoveWhiteSpace(FinalS2Pre);

        std::cout << "FinalS2Pre: " << FinalS2Pre << std::endl;

        std::string FinalS2Pre_Load = FinalS2Pre;

        FinalS2Pre_Load.erase(FinalS2Pre_Load.begin());

        int RemoveAccum = 0;
        for (int e = 0; e < FinalS2Pre_Load.size(); e++) {
            if (FinalS2Pre_Load[e - RemoveAccum] == ' ') {
                FinalS2Pre_Load.erase(FinalS2Pre_Load.begin() + e - RemoveAccum);
                RemoveAccum ++;
            }
        }

        if (FirstCharNeg)
            FinalS1.insert(FinalS1.begin(), '-');

        std::cout << "FinalS2Pre: " << FinalS2Pre_Load << std::endl;

        bool NegFlag = 0;
        if (FinalS2Pre_Load[0] == '-') {
            FinalS2Pre_Load.erase(FinalS2Pre_Load.begin());
            NegFlag =1;
        }

        std::cout << "FinalS2Pre: " << FinalS2Pre_Load << std::endl;

        int FoundSecond = FinalS2Pre_Load.find_first_of("+-*/");

        std::string AppendAfter = "";
        std::cout << ">" << FinalS2Pre_Load << std::endl;
        if (FoundSecond != -1) {
            for (int e = 0; e < FoundSecond; e ++) {
                FinalS2 += FinalS2Pre_Load[e];
                //InsertSizeE++;
            }
            for (int e = FoundSecond; e < FinalS2Pre_Load.size(); e++) {
                AppendAfter += FinalS2Pre_Load[e];
            }
        }
        else {
            FinalS2 = FinalS2Pre_Load;
            //InsertSizeE = FinalS2.size();
        }
        
        std::cout << "Append After " << AppendAfter << std::endl;

        if (NegFlag)
            FinalS2.insert(FinalS2.begin(), '-');

        dis.out(D_DEBUG, "FINALS2 = " + FinalS2);

        char FirstCharInFinal = FinalS2Pre[0];

        int FinalOutput = 0;

        dis.out(D_FILE, "Got " + FinalS1 + " and " + FinalS2 + " for calculation!");

        for (auto e : Pable_vars) {
            if (e.VarName == FinalS1) {
                FinalS1 = e.VarContent;
            }
            if (e.VarName == FinalS2) {
                FinalS2 = e.VarContent;
            }
        }
        
        try
        {
            switch (FirstCharInFinal) {
                case '-':
                    FinalOutput = std::stoi(FinalS1) - std::stoi(FinalS2);    
                    break;
                    
                case '+':
                    FinalOutput = std::stoi(FinalS1) + std::stoi(FinalS2);    
                    break;

                case '/':
                    FinalOutput = std::stoi(FinalS1) / std::stoi(FinalS2);    
                    break;

                case '*':
                    FinalOutput = std::stoi(FinalS1) * std::stoi(FinalS2);    
                    break;    
                    
                default:
                    Pable_ERROR("Unsupported Token");
                    break;
            }
        }
        catch(const std::exception& e)
        {
            Pable_ERROR("Unstable Operators - Convert to int failed or a illegal operation was found!");
        }
        
       

        // int i = 4 + 3


        dis.out(D_FILE, "Got Calculation Output of " + std::to_string(FinalOutput));
        
        int FoundPos2 = FinalS2.size();

        dis.out(D_DEBUG, "Got Pos 1: " + std::to_string(InsertSizeB) + " and Pos2: " + std::to_string(InsertSizeE + InsertSizeB));


        int Accum = i.size();
        for (int e = InsertSizeB; e < Accum; e++) {
            i.erase(i.begin() + InsertSizeB );
            //Accum++;
            std::cout << i << std::endl;
        }



        i.insert( InsertSizeB , std::to_string(FinalOutput) + AppendAfter);

        dis.out(D_INFO, "GOTL: " + i);

        goto BeginAgain;
        

    }

    FinalAfterCal:


        RemoveWhiteSpace(i);
        RemoveWhiteSpaceBack(i);

        std::string FoundPosUss = std::to_string(i[0]);

        if (FoundStringDef(i)) {
            dis.out(D_INFO, "Found useless var");
            continue; 
        }
        else if (FoundPosUss.find_first_of("-01234567890") == std::string::npos) {
            continue;
        }




        
/*
------------------------------------------------ built-ins ------------------------------------------------
*/
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

            // Pabble_out()
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
            //Pable_if():
            else if(FoundToken == "if"){
                if (args.size() > 0) {
                    if (args[0] == '(') {
                        args.erase(args.begin());

                        RemoveWhiteSpace(args);

                        if (FoundStringDef(args)) {
                            
                            RemoveWhiteSpace(args);
                            
                            std::string FoundIf = ExtractStringDef(args);
                            
                            StringSplit splite = SplitString(args, "==");
                            
                            RemoveWhiteSpace(splite.BeforeChar);
                            RemoveWhiteSpace(splite.AfterChar);

                            std::string FirstClause = ExtractStringDef(args);
                            std::string SecondClause = splite.AfterChar;
                            
                            dis.out(D_DEBUG, FirstClause);
                            dis.out(D_DEBUG, SecondClause);
                            
                            RemoveWhiteSpace(splite.AfterChar);
                            RemoveWhiteSpaceBack(splite.AfterChar);

                            splite.AfterChar.erase(splite.AfterChar.begin());
                            splite.AfterChar.erase(splite.AfterChar.begin());
                            splite.AfterChar.erase(splite.AfterChar.begin() + splite.AfterChar.size() - 1);
                            
                            RemoveWhiteSpace(splite.AfterChar);
                            RemoveWhiteSpaceBack(splite.AfterChar);
                            RemoveWhiteSpace(splite.AfterChar);
                            
                            FirstClause = ExtractStringDef(args);
                            SecondClause = ExtractStringDef(splite.AfterChar);                       
                            dis.out(D_DEBUG, FirstClause);
                            dis.out(D_DEBUG, SecondClause);                      


                            if (FirstClause == SecondClause){
                                return true;
                            }
                            else
                            {
                                return false;
                            }
                            
                         }
                    }
                }
            }
            //Pable_while()
            
            //color_out()
            else if (FoundToken == "color_out"){
                if(args.size() > 0){
                    if(args[0] == '('){
                        args.erase(args.begin());
                        RemoveWhiteSpace(args);
                        if(FoundStringDef(args)){
                          
                            StringSplit splite = SplitString(args, ",");
                            
                            RemoveWhiteSpace(splite.BeforeChar);
                            RemoveWhiteSpace(splite.AfterChar);

                            std::string Output = ExtractStringDef(args);
                            std::string Color = splite.AfterChar;

                

                            RemoveWhiteSpace(splite.AfterChar);
                            RemoveWhiteSpaceBack(splite.AfterChar);

                            splite.AfterChar.erase(splite.AfterChar.begin());
                            splite.AfterChar.erase(splite.AfterChar.begin() + splite.AfterChar.size() - 1);

                            RemoveWhiteSpace(splite.AfterChar);
                            RemoveWhiteSpaceBack(splite.AfterChar);
                            
                            Color = splite.AfterChar;
                            dis.out(D_INFO, "Found Output:" + Output);
                            dis.out(D_INFO, "Found Color:" + Color);
                            
                            
                            if(Color == "GREEN"){
                                std::cout << D_COLOR::greenM << Output << D_COLOR::defM << std::endl;
                            }
                            else if(Color == "BLUE"){
                                std::cout << D_COLOR::blueM << Output << D_COLOR::defM << std::endl;
                            }
                            else if(Color == "RED"){
                                std::cout << D_COLOR::redM << Output << D_COLOR::defM << std::endl;
                            }
                            else if(Color == "YELLOW"){
                                std::cout << D_COLOR::yellowM << Output << D_COLOR::defM << std::endl;
                            }
                            else if(Color == "MAGENTA"){
                                std::cout << D_COLOR::magentaM << Output << D_COLOR::defM << std::endl;
                            }
                            else {
                                Pable_ERROR("We do not support that color yet!");
                            }
                            
                        }
                    }
    
                    
                }
            }
            
            
            //Pabble_string
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
            //Pabble_int
            else if (FoundToken == "int") {
                StringSplit splite = SplitString(args, " (=");

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
                if (FirstChar.find_first_of("-0123456789") != std::string::npos) {
                    
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
                Pable_ERROR("Command not supported yet, we are working on it!\n\t--> " + i);
            }
        
            


        }            
        
        
        else {
            dis.out(D_WARNING, "Null line");
        }

        //std::cout << __LINE__ << std::endl;


    }
 
     auto end = std::chrono::high_resolution_clock::now(); 
     double time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count(); 
  
     time_taken *= 1e-9; 
  
    std::cout << std::endl << "Pabble compiled in: " << std::fixed  
         << time_taken << std::setprecision(9); 
    std::cout << " seconds" << std::endl;  
    return 0;
}