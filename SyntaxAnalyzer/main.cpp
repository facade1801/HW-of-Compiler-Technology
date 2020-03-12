//1. 语法分析程序需按文法规则，用递归子程序法对每种语法成分进行分析，并在结束每种语法程序分析之前，在控制台输出当前所识别的语法成分的信息，例如“This is a read statement！”
//parse: 语法分析

#include "main.h"

int main() {
	tmpstrpointer = -1;
	
	fin.open("read.txt");
	fout.open("write1.txt");
	
	parse();
	return 0;
}
