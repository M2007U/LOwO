//version 2024.1030.0712

#pragma once

#include <iostream>
#include <iomanip>

#include <cstdlib>

#include <fstream>
#include <sstream>

#include <string>
#include <vector>
#include <cstring>
#include <cctype>

#include <cmath>
#include <math.h>

#include <typeinfo>
#include <sys/types.h>
#include <unistd.h>

#include "FOwOFunctions_2024.cpp"

using namespace std;

class LOwO
{
    public :

    FOwO fowo;

    vector<string> List_Constant; //{Name, Value"}
    vector<string> List_Variable; //{Name, Value"}
    vector<vector<string>> List_Function; //{Name, Input, Input, Input, Open, Output, Output, Output, Close}

    LOwO()
    {
        fowo.vectOwOr.PushBackMultiple<string>(List_Constant,
        {
            "PI",
            fowo.strOwOng.cOwOnvert.AnythingToString(fowo.mOwOth.Konst("PI")),
            "e",
            fowo.strOwOng.cOwOnvert.AnythingToString(fowo.mOwOth.Konst("e")),
            "gold",
            fowo.strOwOng.cOwOnvert.AnythingToString(fowo.mOwOth.Konst("gold"))
        });
    }


    string StatementEvaluate (string InString, char InSeparateChar, bool DebugMode)
    {
        if (InString.length() == 0){return"";}

        vector<string> StringSegments = fowo.strOwOng.mOwOnip.SeparateByChar(InString,InSeparateChar);
        vector<string> StringSegmentsNew = {};//this is needed for plate manipulation

        bool SafetySwitch = false;
        while( StringSegments.size() > 0 && !SafetySwitch) //when the expression is not in its simplest form
        {

            //sometimes, the string segments may contain tokens that should be ignored
            //like empty strings, or "#ignore" at the front
            StringSegmentsNew = {};
            for(int i = 0 ; i < StringSegments.size() ; i++)
            {
                if ( fowo.vectOwOr.FindObjPos({"","#ignore"},StringSegments[i],'l') == -1 )
                {
                    StringSegmentsNew.push_back( StringSegments[i] );
                }
            }
            StringSegments = StringSegmentsNew;
            StringSegmentsNew = {};
            

            //decide what is the attention area
            //in other words, focus on an un-nested paranthesis
            //Pin_Attention_S will be the starting position of the unested paranthesis
            //Pin_Attention_E will be the ending position of it.

            cout << fowo.strOwOng.shOwOrthand.ColorText("b") << fowo.cOwOut.ForcePrintVector(StringSegments,"bef : ",""," ","",0,'r'," ") << fowo.strOwOng.shOwOrthand.ColorText("d") << endl;
            
            int Pin_Attention_S = 0;
            int Pin_Attention_E = 0;

            Pin_Attention_E = fowo.vectOwOr.FindObjPos<string>(StringSegments,{")",";"},0,'r',StringSegments.size()-1);
            if (Pin_Attention_E == -1)
            {
                //if there are no  paranthesis at all
                //then the whole expression is the attention span
                Pin_Attention_S = 0;
                Pin_Attention_E = StringSegments.size() - 1;
            }
            else
            {
                Pin_Attention_S = fowo.vectOwOr.FindObjPos<string>(StringSegments,{"("},Pin_Attention_E,'l',0); //when Endding Position is -1 (which is given by the param), then halt
                if (Pin_Attention_S == -1){Pin_Attention_S = 0;}
            }
            

            
        
            //decide where is Pin0, Pin1 and Pin2
            int Pin0 = -1;
            int Pin1 = -1;
            int Pin2 = -1;



            
            //look for the operators
            int OprPos_Group0 = fowo.vectOwOr.FindObjPos<string>(StringSegments, {"RefKon","RefVar", "RefFunction"                        }, Pin_Attention_S, 'r', Pin_Attention_E);


            int OprPos_Group1 = fowo.vectOwOr.FindObjPos<string>(StringSegments, {"^","!"                                                 }, Pin_Attention_E, 'l', Pin_Attention_S);
            int OprPos_Group2 = fowo.vectOwOr.FindObjPos<string>(StringSegments, {"*","/","%"                                             }, Pin_Attention_S, 'r', Pin_Attention_E);
            int OprPos_Group3 = fowo.vectOwOr.FindObjPos<string>(StringSegments, {"+","-"                                                 }, Pin_Attention_S, 'r', Pin_Attention_E);
            int OprPos_Group4 = fowo.vectOwOr.FindObjPos<string>(StringSegments, {"neg","sin","cos","tan","asin","acos","atan","P","C"    }, Pin_Attention_S, 'r', Pin_Attention_E);

            //look for the actions
            int ActPos_Group0 = fowo.vectOwOr.FindObjPos<string>(StringSegments, {"var", "function", "print", "="                         }, Pin_Attention_S, 'r', Pin_Attention_E);

            //look for statementEnd
            int SemiPos = fowo.vectOwOr.FindObjPos<string>(StringSegments, {";"}, Pin_Attention_S, 'l', Pin_Attention_E);
            
            
            if (DebugMode)
            {
                cout << fowo.strOwOng.shOwOrthand.ColorText("g");
                cout << "PinAttS   : " << Pin_Attention_S << endl;
                cout << "PinAttE   : " << Pin_Attention_E << endl;
                cout << "OprPos_G1 : " << OprPos_Group1 << endl;
                cout << "OprPos_G2 : " << OprPos_Group2 << endl;
                cout << "OprPos_G3 : " << OprPos_Group3 << endl;
                cout << "OprPos_G4 : " << OprPos_Group4 << endl;
                cout << "ActPos_G0 : " << ActPos_Group0 << endl;
                cout << "SemiPos   : " << SemiPos << endl;
                cout << fowo.strOwOng.shOwOrthand.ColorText("d");
            }
            
            

            //know which small part to deal with
            if (OprPos_Group0 > -1)
            {
                Pin0 = OprPos_Group0;
                Pin1 = Pin0;
                Pin2 = Pin0;
            }
            else if (OprPos_Group1 > -1)
            {
                Pin0 = OprPos_Group1;
                Pin1 = Pin0;
                Pin2 = Pin0;
            }
            else if (OprPos_Group2 > -1)
            {
                Pin0 = OprPos_Group2;
                Pin1 = Pin0;
                Pin2 = Pin0;
            }
            else if (OprPos_Group3 > -1)
            {
                Pin0 = OprPos_Group3;
                Pin1 = Pin0;
                Pin2 = Pin0;
            }
            else if (OprPos_Group4 > -1)
            {
                Pin0 = OprPos_Group4;
                Pin1 = Pin0;
                Pin2 = Pin0;
            }
            else if (ActPos_Group0 > -1)
            {
                Pin0 = ActPos_Group0;
                Pin1 = Pin0;
                Pin2 = Pin0;
            }
            else
            {
                //there are no more operations inside the unested paranthesis
                //now focus on the whole attention span
                Pin0 = Pin_Attention_S;
                Pin2 = Pin_Attention_E;
                Pin1 = Pin0;
            }

            //are things are still in range ?
            if
            (
                Pin0 < 0 || Pin1 < 0 || Pin2 < 0 ||
                StringSegments.size() <= Pin0 ||
                StringSegments.size() <= Pin1 ||
                StringSegments.size() <= Pin2
            )
            {
                if (StringSegments.size() == 0)
                {
                    //run successfully, end
                    return "done";
                }

                SafetySwitch = true;
                cout << fowo.strOwOng.shOwOrthand.ColorText("r");
                cout << "Pin0 or Pin1 or Pin2 is out of range, brake safety switch" << endl;
                cout << "Pin0 : " << Pin0 << endl;
                cout << "Pin1 : " << Pin1 << endl;
                cout << "Pin2 : " << Pin2 << endl;
                cout << fowo.strOwOng.shOwOrthand.ColorText("d");

                
                return "err";
            }

            //now start calculating
            string CalRes_String = "";
            double CalRes_Double = 0;
            stringstream buffer;


            if (StringSegments[Pin0] == "RefKon")
            {
                // RefKON  name
                // Pin0 Pin1

                Pin1 = Pin0 + 1;
                Pin2 = Pin1;

                int FoundIndex = fowo.vectOwOr.FindObjPos(List_Constant,StringSegments[Pin1],'l');

                if(FoundIndex == -1)
                {
                    cout << fowo.cOwOut.ConsoleQuick("error","unable to find constant : " + StringSegments[Pin1]) << endl;
                    return "constant error";
                }
                else
                {
                    CalRes_String = List_Constant[FoundIndex+1];
                }
            }
            else if (StringSegments[Pin0] == "RefVar")
            {
                // RefVAR  name
                // Pin0 Pin1

                Pin1 = Pin0 + 1;
                Pin2 = Pin1;

                int FoundIndex = fowo.vectOwOr.FindObjPos(List_Variable,StringSegments[Pin1],'l');

                if(FoundIndex == -1)
                {
                    cout << fowo.cOwOut.ConsoleQuick("error","unable to find variable : " + StringSegments[Pin1]) << endl;
                    return "variable error";
                }
                else
                {
                    CalRes_String = List_Variable[FoundIndex+1];
                }
            }
            else if (StringSegments[Pin1] == "!")
            {
                //expecting #### !!!!
                //          Pin0 Pin1

                Pin0 = Pin1 - 1;
                Pin2 = Pin1;

                if(fowo.strOwOng.mOwOth.isNumber_BuiltInDouble(StringSegments[Pin0]) == false)
                {
                    return "syntax error";
                }
                else
                {
                    double OperandA = stod(StringSegments[Pin0]);
                    CalRes_Double = fowo.mOwOth.Factorial(OperandA);
                    CalRes_String = fowo.strOwOng.cOwOnvert.AnythingToString<double>(CalRes_Double);
                }
            }
            else if (StringSegments[Pin1] == "^")
            {
                //expecting #### ^    ####
                //          Pin0 Pin1 Pin2

                Pin0 = Pin1 - 1;
                Pin2 = Pin1 + 1;

                if(fowo.strOwOng.mOwOth.isNumber_BuiltInDouble(StringSegments[Pin0]) == false || fowo.strOwOng.mOwOth.isNumber_BuiltInDouble(StringSegments[Pin2]) == false)
                {
                    return "syntax error";
                }
                else
                {
                    double OperandA = stod(StringSegments[Pin0]);
                    double OperandB = stod(StringSegments[Pin2]);
                    CalRes_Double = pow(OperandA, OperandB);
                    CalRes_String = fowo.strOwOng.cOwOnvert.AnythingToString<double>(CalRes_Double);
                }
            }
            else if (StringSegments[Pin1] == "*" || StringSegments[Pin1] == "/")
            {
                //expecting #### *    ####
                //          Pin0 Pin1 Pin2

                Pin0 = Pin1 - 1;
                Pin2 = Pin1 + 1;

                if(fowo.strOwOng.mOwOth.isNumber_BuiltInDouble(StringSegments[Pin0]) == false || fowo.strOwOng.mOwOth.isNumber_BuiltInDouble(StringSegments[Pin2]) == false)
                {
                    return "syntax error";
                }
                else
                {
                    float OperandA = stod(StringSegments[Pin0]);
                    float OperandB = stod(StringSegments[Pin2]);

                    if      (StringSegments[Pin1] == "*"){CalRes_Double = OperandA * OperandB;}
                    else if (StringSegments[Pin1] == "/"){CalRes_Double = OperandA / OperandB;}
                    
                    CalRes_String = fowo.strOwOng.cOwOnvert.AnythingToString<double>(CalRes_Double);
                }
            }
            else if (StringSegments[Pin1] == "%")
            {
                //expecting #### *    ####
                //          Pin0 Pin1 Pin2

                Pin0 = Pin1 - 1;
                Pin2 = Pin1 + 1;

                if(!fowo.strOwOng.mOwOth.isNumber_BuiltInDouble(StringSegments[Pin0]) || !fowo.strOwOng.mOwOth.isNumber_BuiltInDouble(StringSegments[Pin2]))
                {
                    return "syntax error";
                }
                else
                {
                    int OperandA = (int)stod(StringSegments[Pin0]);
                    int OperandB = (int)stod(StringSegments[Pin2]);
                    CalRes_Double = (double)(OperandA % OperandB);
                    CalRes_String = fowo.strOwOng.cOwOnvert.AnythingToString<double>(CalRes_Double);
                }
            }
            else if (StringSegments[Pin1] == "+" || StringSegments[Pin1] == "-")
            {
                //expecting #### +    ####
                //          Pin0 Pin1 Pin2

                Pin0 = Pin1 - 1;
                Pin2 = Pin1 + 1;

                if(fowo.strOwOng.mOwOth.isNumber_BuiltInDouble(StringSegments[Pin0]) == false || fowo.strOwOng.mOwOth.isNumber_BuiltInDouble(StringSegments[Pin2]) == false)
                {
                    return "syntax error";
                }
                else
                {
                    float OperandA = stod(StringSegments[Pin0]);
                    float OperandB = stod(StringSegments[Pin2]);

                    if      (StringSegments[Pin1] == "+"){CalRes_Double = OperandA + OperandB;}
                    else if (StringSegments[Pin1] == "-"){CalRes_Double = OperandA - OperandB;}
                    
                    CalRes_String = fowo.strOwOng.cOwOnvert.AnythingToString<double>(CalRes_Double);
                }
            }
            else if (StringSegments[Pin0] == "neg")
            {
                //expecting neg  ####
                //          Pin0 Pin1

                //need to move Pin1 to the right
                Pin1 = Pin0 + 1;
                Pin2 = Pin1;

                if(fowo.strOwOng.mOwOth.isNumber_Simple(StringSegments[Pin1]) <= 0)
                {
                    return "syntax error";
                }
                else
                {
                    float OperandA = stod(StringSegments[Pin1]);
                    CalRes_Double = OperandA * -1;
                    CalRes_String = fowo.strOwOng.cOwOnvert.AnythingToString<double>(CalRes_Double);
                }
            }
            else if (StringSegments[Pin0] == "sin" || StringSegments[Pin0] == "cos" || StringSegments[Pin0] == "tan")
            {
                //expecting neg  #### ####
                //          Pin0 Pin1 Pin2

                //need to move pin around
                Pin1 = Pin0 + 1;
                Pin2 = Pin0 + 2;

                string ErrorMessage = fowo.strOwOng.shOwOrthand.ColorText("r") + "expected syntax : \"sin\"/\"cos\"/tan\" \"deg\"/\"rad\" <angle>" + fowo.strOwOng.shOwOrthand.ColorText("d");
                if (StringSegments[Pin1] != "deg" && StringSegments[Pin1] != "rad")
                {
                    cout << ErrorMessage << endl;
                    return "syntax error";
                }
                else if (fowo.strOwOng.mOwOth.isNumber_Simple(StringSegments[Pin2]) <= 0)
                {
                    cout << ErrorMessage << endl;
                    return "syntax error";
                }
                else
                {
                    string OperandA = StringSegments[Pin1];
                    double OperandB = stod(StringSegments[Pin2]);

                    if (OperandA == "deg")
                    {
                        OperandB = (double)fowo.mOwOth.Trig_DegToRad((float)OperandB);
                    }

                    if      (StringSegments[Pin0] == "sin"){CalRes_Double = sin(OperandB);}
                    else if (StringSegments[Pin0] == "cos"){CalRes_Double = cos(OperandB);}
                    else if (StringSegments[Pin0] == "tan"){CalRes_Double = tan(OperandB);}
                    CalRes_String = fowo.strOwOng.cOwOnvert.AnythingToString<double>(CalRes_Double);
                }
            }
            else if (StringSegments[Pin0] == "asin" || StringSegments[Pin0] == "acos" || StringSegments[Pin0] == "atan")
            {
                //expecting trig #### ####
                //          Pin0 Pin1 Pin2

                //need to move pin around
                Pin1 = Pin0 + 1;
                Pin2 = Pin0 + 2;

                string ErrorMessage = fowo.strOwOng.shOwOrthand.ColorText("r") + "expected syntax : \"sin\"/\"cos\"/tan\" \"deg\"/\"rad\" <angle>" + fowo.strOwOng.shOwOrthand.ColorText("d");
                if (StringSegments[Pin1] != "deg" && StringSegments[Pin1] != "rad")
                {
                    cout << ErrorMessage << endl;
                    return "syntax error";
                }
                else if (fowo.strOwOng.mOwOth.isNumber_Simple(StringSegments[Pin2]) <= 0)
                {
                    cout << ErrorMessage << endl;
                    return "syntax error";
                }
                else
                {
                    string OperandA = StringSegments[Pin1];
                    double OperandB = stod(StringSegments[Pin2]);

                    if      (StringSegments[Pin0] == "asin"){CalRes_Double = asin(OperandB);}
                    else if (StringSegments[Pin0] == "acos"){CalRes_Double = acos(OperandB);}
                    else if (StringSegments[Pin0] == "atan"){CalRes_Double = atan(OperandB);}

                    if (OperandA == "deg")
                    {
                        CalRes_Double = (double)fowo.mOwOth.Trig_RadToDeg((float)CalRes_Double);
                    }

                    CalRes_String = fowo.strOwOng.cOwOnvert.AnythingToString<double>(CalRes_Double);
                }
            }
            else if (StringSegments[Pin0] == "P" || StringSegments[Pin0] == "C")
            {
                //expecting P/C  n    r
                //          Pin0 Pin1 Pin2

                //need to move pin around
                Pin1 = Pin0 + 1;
                Pin2 = Pin0 + 2;

                string ErrorMessage = fowo.strOwOng.shOwOrthand.ColorText("r") + "expected syntax : \"P\"/\"C\" <n> <r>" + fowo.strOwOng.shOwOrthand.ColorText("d");
                if(fowo.strOwOng.mOwOth.isNumber_BuiltInDouble(StringSegments[Pin1]) == false || fowo.strOwOng.mOwOth.isNumber_BuiltInDouble(StringSegments[Pin2]) == false)
                {
                    cout << ErrorMessage << endl;
                    return "syntax error";
                }
                else
                {
                    float OperandA = stod(StringSegments[Pin1]);
                    float OperandB = stod(StringSegments[Pin2]);

                    if      (StringSegments[Pin0] == "P"){CalRes_Double = fowo.mOwOth.Permutation(OperandA, OperandB);}
                    else if (StringSegments[Pin0] == "C"){CalRes_Double = fowo.mOwOth.Combination(OperandA,OperandB);}
                    
                    CalRes_String = fowo.strOwOng.cOwOnvert.AnythingToString<double>(CalRes_Double);
                }


            }
            else if (Pin0 + 2 == Pin2 && StringSegments[Pin0] == "(" && StringSegments[Pin2] == ")")
            {
                //if the paranthesis only contain one number
                CalRes_String = StringSegments[Pin0+1];
            }
            else if (StringSegments[Pin0] == "var")
            {
                //declaring a variable

                //expecting
                //var <name> <initValue> <;>

                Pin1 = Pin0 + 1;
                Pin2 = Pin0 + 2;

                List_Variable.push_back(StringSegments[Pin0 + 1]);
                List_Variable.push_back(StringSegments[Pin0 + 2]);

                CalRes_String = "#ignore";

            }
            else if (StringSegments[Pin0] == "function")
            {
                //declaring a function
                //expecting
                //function <name> <inputs> ... <inputs> functionOpen <outputs> ... <outputs> functionClose ;
                //AttS                                                                                     AttE
                //Pin0
                
                //function tripMul inA inB inC functionOpen inA * inB * inC function Close ;

                Pin2 = Pin0 + 1;

                vector<string> FunctionStripNew = {};
                while(Pin2 < Pin_Attention_E)
                {
                    FunctionStripNew.push_back(StringSegments[Pin2]);
                    Pin2++;
                }

                Pin2--;
                List_Function.push_back( FunctionStripNew );

                CalRes_String = "#ignore";
            }
            else if (StringSegments[Pin0] == "=")
            {
                //expecting
                //<name> = <value>

                Pin0 = Pin1 - 1;
                Pin2 = Pin1 + 1;

                int FoundIndex = fowo.vectOwOr.FindObjPos(List_Variable,StringSegments[Pin0],'l');

                if(FoundIndex == -1)
                {
                    cout << fowo.cOwOut.ConsoleQuick("error","unable to find variable : " + StringSegments[Pin0]) << endl;
                    return "variable error";
                }
                else
                {
                    List_Variable[FoundIndex + 1] = StringSegments[Pin2];
                    CalRes_String = "#ignore";
                }
            }
            else if (StringSegments[Pin0] == "print")
            {
                Pin1 = Pin0 + 1;
                Pin2 = Pin0 + 1;

                cout << fowo.strOwOng.shOwOrthand.ColorText("b") << "LOwO : " << fowo.strOwOng.shOwOrthand.ColorText("d") << StringSegments[Pin1] << endl;
                CalRes_String = "#ignore";
            }
            else if (StringSegments[Pin0] == ";")
            {
                CalRes_String = "#ignore";
            }
            else
            {
                return "emergency halt";
            }

            //now start replacing string

            //### ### ### ### ((( 003 +++ 004 --- 005 ))) ### ###
            //                S   P0  P1  P2          E
            //                                ^
            //### ### ### ### ((( 007

            int CurrentIndex = 0;
            while(CurrentIndex < StringSegments.size())
            {
                if (CurrentIndex < Pin0 || Pin2 < CurrentIndex)
                {
                    StringSegmentsNew.push_back(StringSegments[CurrentIndex]);
                    CurrentIndex++;
                }
                else if (CurrentIndex == Pin0)
                {
                    StringSegmentsNew.push_back(CalRes_String);
                    CurrentIndex = Pin2 + 1;
                }
            }

            
            cout << fowo.strOwOng.shOwOrthand.ColorText("b") << fowo.cOwOut.ForcePrintVector(StringSegmentsNew,"aft : ",""," ","",0,'r'," ") << fowo.strOwOng.shOwOrthand.ColorText("d") << endl;
            cout << endl << "---- ---- ---- ----" << endl;
            string EnterStepBuffer;
            getline(cin,EnterStepBuffer);

            StringSegments = StringSegmentsNew;

        }

        return StringSegments[0];
    }





};

/*

var <name> <value>
function <name> <inputs> functionOpen <expressions> functionClose


*/