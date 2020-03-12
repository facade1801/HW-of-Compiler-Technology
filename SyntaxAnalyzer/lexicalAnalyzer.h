#ifndef lexicalAnalyzer_h
#define lexicalAnalyzer_h
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const std::string keyword[] = {"const", "int", "char", "void", "main", "if", "else", "while", "switch", "case", "default", "scanf", "printf", "return", "do"};
const int keywordlength = 14;

enum lexClassEnum
{
	ERROR = 0,
	CONSTTYPE=1, NOTYPE, INTTYPE, CHARTYPE, MAINSY,	//5
	IFSY, ELSESY, WHILESY, SWITCHSY, CASESY,		//10
	DEFAULTSY, SCANFSY, PRINTFSY, RETURNSY, DOSY,	//15
	VARIABLE, INTSY, LESY, LTSY, GESY,				//20
	GTSY, NESY, EQSY, EQUALSY, CHARACTER,			//25
	STRING, COLONSY, SEMISY, COMMASY, PLUSSY,		//30
	MINUSSY, MULTISY, DIVISY, LPARSY, RPARSY,		//35
	LBRACKSY, RBRACKSY, LBRACESY, RBRACESY			//39
} ;
lexClassEnum lexClass;//class number(0~ )

int lexClas;
std::string lexValue;	//class(
int lexNum;				//for int
std::string lexString;		//for String

ifstream fin;



string tmpstr[100];
int tmpstrpointer;

int getSym();


#endif /* lexicalAnalyzer_h */
