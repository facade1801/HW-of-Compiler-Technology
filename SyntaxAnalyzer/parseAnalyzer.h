#ifndef parseAnalyzer_h
#define parseAnalyzer_h

#include <string>
#include <iostream>
#include <fstream>
#include <assert.h>
using namespace std;

extern int getSym();

extern int lexClas;
extern std::string lexValue;
extern int lexNum;
extern std::string lexString;

extern void error(int errcode);

extern void unGetSym();

ofstream fout;


void Program();
void ConstExp();
void ConstDf();
void Int();
void Identifier();
void VariableExp();
void VariableDf();
void ConstValue();
void TypeIdentifier();
void NormalFuncDf();
void VoidFuncDf();
void CompoundSentence();
void Param();
void ParamList();
void MainFunc();
void Expression();
void Term();
void Factor();
void Sentence();
void AssignSentence();
void IfSentence();
void Condition();
void WhileSentence();
void SwitchSentence();
void CaseTable();
void CaseSentence();
void DefaultSentence();
void NormalFuncCall();
void VoidFuncCall();
void ValueParamList();
void Sentences();
void ScanfSentence();
void PrintfSentence();
void ReturnSentence();

void parse();

#endif /* parseAnalyzer_h */
