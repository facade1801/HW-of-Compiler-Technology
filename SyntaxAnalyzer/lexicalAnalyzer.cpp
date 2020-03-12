#include "lexicalAnalyzer.h"

bool iskeyword(string s) {
	int i;
	for (i = 0; i < keywordlength; i ++) {
		if (s == keyword[i])
			return true;
	}
	return false;
}

bool isSpace(char c) {
	return (c == ' ' || c == '\t' || c == '\n');
}

bool isLetter(char c) {
	return ((c > 64 && c < 91) || c == 95 || (c > 96 && c < 123));
}

bool isChar(char c) {
	return (c == 32 || c == 33 || (c > 34 && c < 127));
}

void error(char c) {
	cout << "******** Error: " << c << " is not valid ********" << endl;
}

int getSym() {
	char a = fin.get();
	string token = "";	//字符串、标识符
	/* char a 和 token 其实是一样的，都是表示要被输出的东西本身 */

	/*  initializing  */
	lexClass = ERROR;	/* enum class	*/
	lexNum = NULL;		/* for int		*/
	lexString = "";		/* for string	*/
	lexValue = "";		/**exact input***/
	/* 对于int,是int的值；对于字符串,是字符串本身；对于标识符,是标识符本身；其他是null */

	while (isSpace(a) || a == EOF)
		a = fin.get();

	//	if (a == EOF) {
	//		cout << "EOF. Program ended Normally." << endl;
	//		exit(0);
	//	}

	if (isLetter(a)) {
		while (isLetter(a) || isdigit(a)) {
			token = token + a;
			a = fin.get();
		}
		fin.unget();
		lexValue = token;
		if (token == "int")
			lexClass = INTTYPE;
		else if (token == "const")
			lexClass = CONSTTYPE;
		else if (token == "void")
			lexClass = NOTYPE;
		else if (token == "char")
			lexClass = CHARTYPE;
		else if (token == "main")
			lexClass = MAINSY;
		else if (token == "if")
			lexClass = IFSY;
		else if (token == "else")
			lexClass = ELSESY;
		else if (token == "while")
			lexClass = WHILESY;
		else if (token == "switch")
			lexClass = SWITCHSY;
		else if (token == "case")
			lexClass = CASESY;
		else if (token == "default")
			lexClass = DEFAULTSY;
		else if (token == "scanf")
			lexClass = SCANFSY;
		else if (token == "printf")
			lexClass = PRINTFSY;
		else if (token == "return")
			lexClass = RETURNSY;
		//		else if (token == "do")
		//			lexClass = DOSY;
		else
			lexClass = VARIABLE;
	}

	else if (isdigit(a)) {
		while (isdigit(a)) {
			token = token + a;
			a = fin.get();
		}
		fin.unget();
		lexNum = 0;//stoi(token);
		lexClass = INTSY;
		lexValue = token;
	}

	// < LT｜<= LE｜> GT｜>= GE｜!= NE｜== EQ
	else if (a == '<') {
		a = fin.get();
		if (a == '=') {
			lexClass = LESY;
			lexValue = "<=";
		}
		else {
			lexClass = LTSY;
			lexValue = "<";
			fin.unget();
		}
	}
	else if (a == '>') {
		a = fin.get();
		if (a == '=') {
			lexClass = GESY;
			lexValue = ">=";
		}
		else {
			lexClass = GTSY;
			lexValue = ">";
			fin.unget();
		}
	}
	else if (a == '!') {
		a = fin.get();
		if (a == '=') {
			lexClass = NESY;
			lexValue = "!=";
		}
		else {
			error('!');
			fin.unget();
		}
	}

	else if (a == '=') {
		a = fin.get();
		if (a == '=') {
			lexClass = EQSY;
			lexValue = "==";
		}
		else {
			lexClass = EQUALSY;
			lexValue = "=";
			fin.unget();
		}
	}

	else if (a == '\'') {
		a = fin.get();
		if (isdigit(a) || isLetter(a)
			|| a == '+' || a == '-' || a == '*' || a == '/') {
			char t = fin.get();
			if (t == '\'') {
				lexClass = CHARACTER;
				lexValue = t + a + t;
				//lexString = a;
			}
			else {
				fin.unget();
				error('\'');
			}
		}
	}

	else if (a == '\"') {
		do {
			token += a;
			a = fin.get();
		} while (a != '\"');
		token = token + "\"";
		string tok1 = token;
		tok1 = tok1.erase(0,1);
		tok1 = tok1.erase(tok1.length()-1, 1);
		lexClass = STRING;
		lexValue = token;
		lexString = tok1;
	}

	else {
		lexValue = a;
		switch (a) {
			case ':':lexClass = COLONSY;	break;
			case ';':lexClass = SEMISY;		break;
			case ',':lexClass = COMMASY;	break;
			case '+':lexClass = PLUSSY;		break;
			case '-':lexClass = MINUSSY;	break;
			case '*':lexClass = MULTISY;	break;
			case '/':lexClass = DIVISY;		break;
			case '(':lexClass = LPARSY;		break;
			case ')':lexClass = RPARSY;		break;
			case '[':lexClass = LBRACKSY;	break;
			case ']':lexClass = RBRACKSY;	break;
			case '{':lexClass = LBRACESY;	break;
			case '}':lexClass = RBRACESY;	break;
			default:	error(a);	break;
		}
	}
	cout << "GetSym: " << lexClass << "\t" << lexValue << endl;
	lexClas = (int)lexClass;
	tmpstrpointer = (tmpstrpointer >= 99) ? 0 : (tmpstrpointer+1);
	tmpstr[tmpstrpointer] = lexValue;
	return lexClas;

}

void unGetSym() {//已经能成功回退！真棒！

	string str1 = tmpstr[tmpstrpointer];
	int i = (int) str1.length() - 1;
	for (; i >= 0; i --) {
		fin.unget();
	}
	fin.unget();
	while (fin.peek() == ' ' || fin.peek() == '\t' || fin.peek() == '\n')
		fin.unget();
	fin.get();

	if (tmpstrpointer == 0) {//如果第一个词就出现了问题的话（比如说
		str1 = tmpstr[tmpstrpointer + 99];
		if (str1 == "") {
			lexClas = 0;
			lexNum = 0;
			lexString = "";
			lexValue = "";
			return;
		}
	}
	else
		str1 = tmpstr[tmpstrpointer - 1];
	i = (int) str1.length() - 1;
	for (; i >= 0; i --) {
		fin.unget();
	}

	cout << "REGET1_" ;///////////
	tmpstrpointer = tmpstrpointer - 2;
	getSym();
	cout << "REGET2_" ;///////////
}

