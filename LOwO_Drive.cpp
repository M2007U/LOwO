//version 2024.1022.0544

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#include <unistd.h>
#include <thread>
#include <atomic>

#include "FOwOFunctions_2024.cpp"
#include "LOwO_2024.cpp"



using namespace std;



int main ()
{
    
    FOwO fowo;
    LOwO lowo;

    string UserInput = "";
    bool UserDebug = false;
    vector<string> UserInputVector = {};

    cout << fowo.strOwOng.shOwOrthand.ColorText("y") << endl;
    cout << "/h ?" << endl;
    cout << fowo.strOwOng.shOwOrthand.ColorText("d") << endl;

    while(UserInput != "/e")
    {
        getline(cin, UserInput);

        if (UserInput.length() > 0)
        {
            UserInputVector = fowo.strOwOng.mOwOnip.SeparateByChar(UserInput,' ');

            if (UserInputVector[0] == "/h")
            {
                cout << fowo.strOwOng.shOwOrthand.ColorText("y") << endl;
                cout << "Step 0 Operations , L to R : KON" << endl;
                cout << "Step 1 Operations , R to L : ^    !" << endl;
                cout << "Step 2 Operations , L to R : *    /    %" << endl;
                cout << "Step 3 Operations , L to R : +    -" << endl;
                cout << "Step 4 Operations , L to R : neg  sin  cos  tan  asin acos atan Pnr  Cnr" << endl;
                cout << "/d                         : toggle debug mode" << endl;
                cout << "/c                         : clear the screen" << endl;
                cout << "/k print                   : print the constant list" << endl;
                cout << "/k def <name> <value>      : define a constant" << endl;
                cout << "/k undef <name>            : undefine a constant" << endl;
                cout << "/k clear                   : clear the constant" << endl;
                cout << "/e                         : exit calculator" << endl;
                cout << fowo.strOwOng.shOwOrthand.ColorText("d") << endl;
            }
            else if (UserInputVector[0] == "/d")
            {
                UserDebug = !UserDebug;
                cout << fowo.strOwOng.shOwOrthand.ColorText("y") << endl;
                cout << "DebugMode set to : " << UserDebug << endl;
                cout << fowo.strOwOng.shOwOrthand.ColorText("d") << endl;
            }
            else if (UserInputVector[0] == "/c")
            {
                #ifdef _WIN32
                    system("cls");
                #else
                    system("clear");
                #endif
            }
            else if (UserInputVector[0] == "/k")
            {
                if (UserInputVector.size() == 2)
                {
                    if (UserInputVector[1] == "print")
                    {
                        cout << fowo.cOwOut.ForcePrintVector(lowo.List_Constant,"ConstantList",""," , ","",0,'l'," ") << endl;
                    }  
                    else if (UserInputVector[1] == "clear")
                    {
                        lowo.List_Constant = {};
                        cout << fowo.cOwOut.ConsoleQuick("success", "constant list cleared") << endl;
                    }
                }
                else if (UserInputVector.size() == 3)
                {
                    if (UserInputVector[1] == "undef")
                    {
                        // /k undef name
                        int FoundIndex = fowo.vectOwOr.FindObjPos(lowo.List_Constant,UserInputVector[2],'l');

                        if (FoundIndex > -1)
                        {
                            lowo.List_Constant = fowo.vectOwOr.remove_byIndex(lowo.List_Constant,FoundIndex);
                            lowo.List_Constant = fowo.vectOwOr.remove_byIndex(lowo.List_Constant,FoundIndex);
                            cout << fowo.cOwOut.ConsoleQuick("success", "removed constant") << endl;
                        }
                        else
                        {
                            cout << fowo.cOwOut.ConsoleQuick("error", "no such constant") << endl;
                        }
                    }
                }
                else if (UserInputVector.size() == 4)
                {
                    if (UserInputVector[1] == "def")
                    {
                        // /k def name value
                        if ( fowo.strOwOng.mOwOth.isNumber_Simple(UserInputVector[2]))
                        {
                            cout << fowo.cOwOut.ConsoleQuick("error", "provided name can be interpreted as a number") << endl;
                        }
                        else if (fowo.strOwOng.mOwOth.isNumber_BuiltInDouble(UserInputVector[3]) == false)
                        {
                            cout << fowo.cOwOut.ConsoleQuick("error", "provided value cannot be interpreted as a number") << endl;
                        }
                        else
                        {
                            lowo.List_Constant.push_back(UserInputVector[2]);
                            lowo.List_Constant.push_back(UserInputVector[3]);
                            cout << fowo.cOwOut.ConsoleQuick("success", "added constant") << endl;
                        }
                    }
                }
                
                
                
                
            }
            else if (UserInputVector[0] == "/e")
            {
                //do nothing, then go out
            }
            else if (UserInputVector[0] == "/printMemory")
            {
                cout << fowo.cOwOut.ForcePrintVector(lowo.List_Constant,"constants:",""," , ","",0,'l'," ") << endl;
                cout << fowo.cOwOut.ForcePrintVector(lowo.List_Variable,"variables:",""," , ","",0,'l'," ") << endl;
                for(int i = 0 ; i < lowo.List_Function.size() ; i++)
                {
                    cout << fowo.cOwOut.ForcePrintVector(lowo.List_Function[i],"function:",""," , ","",0,'l'," ") << endl;
                }
            }
            else
            {
                cout << lowo.StatementEvaluate(UserInput,' ',UserDebug) << endl;
            } 
        }
          
    }

    
    


} 

/*

( ( 3 ^ 2 ^ 2 - 2 ^ 2 ^ 2 - 60 ) ^ ( 20 + 8 ^ ( 0.5 - ( ( 18 - 0.333 ^ 3 ) / ( 5 % 2 ) ) ) - 60 ) ) / ( 2 ^ ( 2 + 19 % 3 ) )
( ( neg 8 ) + ( 8 ^ 2 - 4 * 2 * 3 ) ^ 0.5 ) / ( 2 * 2 )
acos deg ( cos deg 30 )
( sin deg 30 ) ^ 2 + ( cos deg 30 ) ^ 2

*/