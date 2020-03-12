//尖括号( < > )内包含的为必选项。
//方括号( [ ] )内包含的为可选项。
//大括号( { } )内包含的为可重复0至无数次的项。
#include "parseAnalyzer.h"

void match(int matchNum) {
	if (lexClas == matchNum) {
		getSym();
		return;
	} else {
		cout << "Expected:" << matchNum << "\tReal:" << lexClas << endl;
		//		exit(-1);
	}
}
void match(int mn1, int mn2) {
	if (lexClas == mn1 || lexClas == mn2) {
		getSym();
		return;
	} else {
		cout << "Expected:" << mn1 << "|" << mn2 << "\tReal:" << lexClas << endl;
		//		exit(-1);
	}
}
bool matchb(int matchNum) {
	if (lexClas == matchNum) {
		getSym();
		return true;
	} else {
		//		cout << "(b)Expected:" << matchNum << "Real:" << lexClas << endl;
		return false;
	}
}

bool matchb(int mn1, int mn2) {
	if (lexClas == mn1 || lexClas == mn2) {
		getSym();
		return true;
	} else {
		//		cout << "(b)Expected:" << mn1 << "|" << mn2 << "\tReal:" << lexClas << endl;
		return false;
	}
}

void Program() {//TODO:Many problems inside.
	fout << "== Program start ==\n" << endl;
	
	ConstExp();		//?
	
	VariableExp();	//?
	
	while(lexClas >= 2 && lexClas <= 4) {
		if (matchb(2)) {
			unGetSym();
			VoidFuncDf();
		}
		else {
			NormalFuncDf();
		}
	}
}

void ConstExp() {
	while (matchb(1)) {
		ConstDf();
		match(28);
		fout << "Constant declaration." << endl;
	}
}

void ConstDf() {//TODO!!!
	if(matchb(3)) {
		do {
			match(16);
			match(24);
			match(17);
		} while (matchb(29));
	}
	else if (matchb(4)) {
		do {
			match(16);
			match(24);
			match(25);
		} while (matchb(29));
	}
	else exit(1);
}
	
	
	void Int() {
		if (matchb(30, 31)) {
			match(17);
		} else {
			match(17);
		}
	}
	
	void UnsignedInt() {
		match(17);//TODO
	}
	
	void Identifier() {
		match(16);
	}
	
	void VariableExp() {
		while (matchb(3, 4)) {
			unGetSym();
			VariableDf();
			if (matchb(28))
				fout << "Variable declaration." << endl;
			else {
				unGetSym();
				unGetSym();
				return;
			}
		}
	}
	
	void VariableDf() {
		TypeIdentifier();
		do {
			Identifier();
			if (matchb(36)) {
				UnsignedInt();
				match(37);
			}
		} while (matchb(29));
	}
	
	void ConstValue() {
		if (matchb(30, 31)) {
			match(17);
		} else if (matchb(17)) {
			;
		} else {
			match(25);
		}
	}
	
	void TypeIdentifier() {
		match(3, 4);
	}
	
	void NormalFuncDf() {
		match(3, 4);
		Identifier();
		if (matchb(34)) {
			Param();
			match(35);
		}
		match(38);
		CompoundSentence();
		match(39);
		fout << "Return function declaration." << endl;
		
	}
	
	void VoidFuncDf() {
		match(2);
		if (matchb(16)) {
			unGetSym();
			Identifier();
		}
		else if (matchb(5)){
			unGetSym();
			unGetSym();
			MainFunc();
			return;
		}
		else {
			error(4);	//void后面接了函数，但是并不是标识符也不是main的一个奇妙的错误……
		}
		if (matchb(34)) {
			Param();
			match(35);
		}
		match(38);
		CompoundSentence();
		match(39);
		fout << "Void function declaration." << endl;
		
	}
	
	void CompoundSentence() {
		if (matchb(1)) {
			unGetSym();
			ConstExp();
		}
		if (matchb(3, 4)) {
			unGetSym();
			VariableExp();
		}
		Sentences();
	}
	
	void Param() {
		ParamList();
	}
	void ParamList() {
		do {
			match(3, 4);
			Identifier();
		} while (matchb(29));
	}
	
	void MainFunc() {
		fout << "Start Main function." << endl;
		
		match(2);
		match(5);
		match(34);
		match(35);
		match(38);
		
		CompoundSentence();
		//思路：compoundSentence在遇到花括号的时候终止。也就是说，花括号可以标志着一个语句段的开始和结束！！！
		
		if (lexClas == 39) {
			fout << "End of main function. The compiling program will end." << endl;
			fout << "\n== Program End ====" << endl;
			exit(0);//end in peace.
		}
		else
			exit(1);
	}
	
	void Expression() {	//表达式
		if (matchb(30, 31)) {
			unGetSym();
			Term();
		}
		else
			Term();
		while (matchb(30, 31)) {
			unGetSym();
			Term();
		}
	}
	
	void Term() {
		Factor();
		while (matchb(32, 33)) {
			unGetSym();
			Factor();
		}
	}
	
	void Factor() {
		if (matchb(16)) {
			if (matchb(36)) {
				Expression();
				match(37);
			}
		}
		else {
			if (matchb(34)) {
				Expression();
				matchb(35);
			}
			else {
				if (matchb(17))
					;
				else {
					if (matchb(25))
						;
					else {
						NormalFuncCall();
					}
				}
			}
		}
	}
	
	void Sentence() {
		switch (lexClas) {
			case 6:		IfSentence();					break;
			case 8:		WhileSentence();				break;
			case 38: 	getSym();		Sentences();	break;
			case 16:	{
				getSym();
				if (matchb(34)) {
					unGetSym();
					unGetSym();
					NormalFuncCall();
					match(28);
				}
				else if (matchb(28)){
					unGetSym();
					unGetSym();
					VoidFuncCall();
					match(28);
				}
				else {
					unGetSym();
					AssignSentence();
					match(28);
				}
				break;
			}
			case 12: 	ScanfSentence();	match(28);	break;
			case 13: 	PrintfSentence();	match(28);	break;
			case 18: 	match(28);						break;
			case 9: 	SwitchSentence();				break;
			case 14: 	ReturnSentence();	match(28);	break;
			default: 	error(3);						break;
		}
	}
	
	void AssignSentence() {
		fout << "Assigning Sentence." << endl;

		Identifier();
		if (matchb(24))
			Expression();
		else {
			match(36);
			Expression();
			match(37);
			match(24);
			Expression();
		}
	}
	void IfSentence() {
		fout << "If Sentence." << endl;

		match(6);
		match(34);
		Condition();
		match(35);
		Sentence();
		match(7);
		Sentence();
	}
	
	void Condition() {
		fout << "<Condition>" << endl;

		Expression();
		if (lexClas >= 18 && lexClas <= 23) {
			getSym();
			Expression();
		}
		else
			unGetSym();
	}
	
	void WhileSentence() {
		fout << "While Sentence." << endl;

		match(8);
		match(34);
		Condition();
		match(35);
		Sentence();
	}
	
	void SwitchSentence() {
		fout << "Switch Sentence." << endl;

		match(9);
		match(34);
		Expression();
		match(35);
		match(38);
		CaseTable();
		if (matchb(11)) {
			unGetSym();
			DefaultSentence();
		}
		match(39);
	}
	
	void CaseTable() {
		while (matchb(10))
			CaseSentence();
		getSym();
	}
	
	void CaseSentence() {
		fout << "\tA case" << endl;

		ConstValue();
		match(27);
		Sentence();
	}
	
	void DefaultSentence() {
		fout << "Default" << endl;

		match(11);
		match(27);
		Sentence();
	}
	void NormalFuncCall() {
		fout << "Function Call." << endl;

		Identifier();
		if (matchb(34)) {
			ValueParamList();
			match(35);
		}
		else
			;
	}
	void VoidFuncCall() {
		fout << "Void Function Call." << endl;
		Identifier();
		if (matchb(34)) {
			ValueParamList();
			match(35);
		}
		else
			;
	}
	void ValueParamList() {
		do {
			Expression();
		} while (matchb(29));
	}
	void Sentences() {
		Sentence();
		while (lexClas != 39){
			Sentence();
		}
		//	unGetSym();
	}
	void ScanfSentence() {
		fout << "Scanf Sentence." << endl;

		match(12);
		match(34);
		do {
			Identifier();
		} while (matchb(29));
		match(35);
	}
	void PrintfSentence() {
		fout << "Printf Sentence." << endl;

		match(13);
		match(34);
		if (matchb(26)) {
			if (matchb(29))
				Expression();
			else
				;
		}
		else
			Expression();
		match(35);
	}
	void ReturnSentence() {
		fout << "Return Sentence." << endl;

		match(14);
		if (matchb(34)) {
			Expression();
			matchb(35);
		}
	}
	
	void parse() {
		lexClas = getSym();
		Program();
		
		//test now. delete later.
	}
	
