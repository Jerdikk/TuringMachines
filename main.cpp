// Turnig.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
//#include <std
#include<string>
#include<iostream>
#include "turing.h"

const int MAXALPHABET = 128;
const int MAXSTATES = 255;

int TuringObject::gTuringObjectNum=0;


struct Rules {
	int nextstate;
	char currSymbol;
	TuringDirection currDirection;
	int isRule;
};

class tMachine
{
public:
	void SetAlphabet(char *str);
	void SetRibbon(char *str);
	void SetRules();
	void Solve();
	tMachine() {maxalphabet=0;maxstates=0;};
	~tMachine() {
	for (int count = 0; count < (maxalphabet+1); count++)
        delete [] currRules[count];
	};
private:
	int maxalphabet;
	int maxstates;
	char alphabet[MAXALPHABET];
	Rules **currRules;//[MAXALPHABET][MAXSTATES];
	Ribbon tmRibbon; //Объявляем переменную, тип которой есть список

};

void tMachine::SetAlphabet(char *str)
{
	int i;
	std::string currStr;
	currStr = str;

 maxalphabet = currStr.length();
 


 for ( i = 0; i < maxalphabet; i++ )
 {
	 alphabet[i] = currStr.at(i);
 }
}

void tMachine::SetRibbon(char *str)
{
	int i;
	std::string currRibbon;
	currRibbon = str;
	int ribbonlength = currRibbon.length();
	for ( i = 0; i < ribbonlength; i++ )
		tmRibbon.Add(currRibbon.at(i)); //Добавляем в список элементы
	tmRibbon.Show(); //Отображаем список на экране

}
void tMachine::SetRules()
{
	int i;
	maxstates = 9;

	currRules = new Rules*[(maxalphabet+1)];
	for (i=0; i<(maxalphabet+1); i++)
		currRules[i] = new Rules[(maxstates+1)];

currRules[0][0].nextstate = 0;
 currRules[0][0].currSymbol = '1';
 currRules[0][0].currDirection = TuringDirection::Right;
 currRules[0][0].isRule = 1;

 currRules[1][0].nextstate = 1;
 currRules[1][0].currSymbol = 'x';
 currRules[1][0].currDirection = TuringDirection::Right;
 currRules[1][0].isRule = 1;

 currRules[4][0].nextstate = 0;
 currRules[4][0].currSymbol = '*';
 currRules[4][0].currDirection = TuringDirection::Right;
 currRules[4][0].isRule = 1;

 currRules[0][1].nextstate = 2;
 currRules[0][1].currSymbol = 'a';
 currRules[0][1].currDirection = TuringDirection::Right;
 currRules[0][1].isRule = 1;

 currRules[0][2].nextstate = 2;
 currRules[0][2].currSymbol = '1';
 currRules[0][2].currDirection = TuringDirection::Left;
 currRules[0][2].isRule = 1;

 currRules[1][2].nextstate = 3;
 currRules[1][2].currSymbol = 'x';
 currRules[1][2].currDirection = TuringDirection::Left;
 currRules[1][2].isRule = 1;

 currRules[2][2].nextstate = 2;
 currRules[2][2].currSymbol = '=';
 currRules[2][2].currDirection = TuringDirection::Left;
 currRules[2][2].isRule = 1;

 currRules[3][2].nextstate = 2;
 currRules[3][2].currSymbol = 'a';
 currRules[3][2].currDirection = TuringDirection::Left;
 currRules[3][2].isRule = 1;

 currRules[0][3].nextstate = 4;
 currRules[0][3].currSymbol = 'a';
 currRules[0][3].currDirection = TuringDirection::Right;
 currRules[0][3].isRule = 1;

 currRules[3][3].nextstate = 3;
 currRules[3][3].currSymbol = 'a';
 currRules[3][3].currDirection = TuringDirection::Left;
 currRules[3][3].isRule = 1;

 currRules[4][3].nextstate = 6;
 currRules[4][3].currSymbol = '*';
 currRules[4][3].currDirection = TuringDirection::Right;
 currRules[4][3].isRule = 1;

 currRules[0][4].nextstate = 4;
 currRules[0][4].currSymbol = '1';
 currRules[0][4].currDirection = TuringDirection::Right;
 currRules[0][4].isRule = 1;

 currRules[1][4].nextstate = 4;
 currRules[1][4].currSymbol = 'x';
 currRules[1][4].currDirection = TuringDirection::Right;
 currRules[1][4].isRule = 1;

 currRules[2][4].nextstate = 4;
 currRules[2][4].currSymbol = '=';
 currRules[2][4].currDirection = TuringDirection::Right;
 currRules[2][4].isRule = 1;

 currRules[3][4].nextstate = 4;
 currRules[3][4].currSymbol = 'a';
 currRules[3][4].currDirection = TuringDirection::Right;
 currRules[3][4].isRule = 1;

 currRules[4][4].nextstate = 5;
 currRules[4][4].currSymbol = '1';
 currRules[4][4].currDirection = TuringDirection::Right;
 currRules[4][4].isRule = 1;

 currRules[5][5].nextstate = 2;
 currRules[5][5].currSymbol = '*';
 currRules[5][5].currDirection = TuringDirection::Left;
 currRules[5][5].isRule = 1;

 currRules[1][6].nextstate = 7;
 currRules[1][6].currSymbol = 'x';
 currRules[1][6].currDirection = TuringDirection::Right;
 currRules[1][6].isRule = 1;

 currRules[3][6].nextstate = 6;
 currRules[3][6].currSymbol = '1';
 currRules[3][6].currDirection = TuringDirection::Right;
 currRules[3][6].isRule = 1;

 currRules[0][7].nextstate = 2;
 currRules[0][7].currSymbol = 'a';
 currRules[0][7].currDirection = TuringDirection::Right;
 currRules[0][7].isRule = 1;

 currRules[2][7].nextstate = 8;
 currRules[2][7].currSymbol = '=';
 currRules[2][7].currDirection = TuringDirection::Left;
 currRules[2][7].isRule = 1;

 currRules[3][7].nextstate = 7;
 currRules[3][7].currSymbol = 'a';
 currRules[3][7].currDirection = TuringDirection::Right;
 currRules[3][7].isRule = 1;

 currRules[1][8].nextstate = 9;
 currRules[1][8].currSymbol = 'x';
 currRules[1][8].currDirection = TuringDirection::Stay;
 currRules[1][8].isRule = 1;

 currRules[3][8].nextstate = 8;
 currRules[3][8].currSymbol = '1';
 currRules[3][8].currDirection = TuringDirection::Left;
 currRules[3][8].isRule = 1;

}

void tMachine::Solve()
{
	int i;

  bool done = false;
  RibbonCell *temp;
  char tempChar;
  int currAlphabetNum;

  int currentTuringMachineState=0;

  tmRibbon.Top();
  do {
	  temp = tmRibbon.ReadCellFromHeadPosition();
	  tempChar = temp->GetCharCellValue();
	  currAlphabetNum = -1;
	  for ( i = 0; i < maxalphabet; i++ )	  
		  if (tempChar == alphabet[i])
		  {
			currAlphabetNum = i;
			i = maxalphabet;
		  }
	  if ((currAlphabetNum >= 0 ) && (currAlphabetNum < maxalphabet))
	  {
			  if (currRules[currAlphabetNum][currentTuringMachineState].isRule)
			  {
				  temp->SetCellValue( currRules[currAlphabetNum][currentTuringMachineState].currSymbol);				  
				  if (!tmRibbon.Move(currRules[currAlphabetNum][currentTuringMachineState].currDirection))
				  {
					  if (currRules[currAlphabetNum][currentTuringMachineState].currDirection == TuringDirection::Right)
					  {
						  tmRibbon.Add(' ');
						  if (!tmRibbon.Move(currRules[currAlphabetNum][currentTuringMachineState].currDirection))
						  {
							std::cout  << " Errorr !!!!";
						  }
					  }
				  }
				  currentTuringMachineState = currRules[currAlphabetNum][currentTuringMachineState].nextstate;
				  if ( currentTuringMachineState == maxstates)
					  done = true;
			  }
	  }
	  else
	  {
		  /// символ не найден в алфавите
		  if ((currAlphabetNum == -1) && (i == maxalphabet))
		  {
			  if (currRules[i][currentTuringMachineState].isRule)
			  {
				  temp->SetCellValue( currRules[i][currentTuringMachineState].currSymbol);				  
				  tmRibbon.Move(currRules[i][currentTuringMachineState].currDirection);
				  currentTuringMachineState = currRules[i][currentTuringMachineState].nextstate;
				  if ( currentTuringMachineState == maxstates)
					  done = true;
			  }
		  }
	  }

  } while (!done);

  tmRibbon.Show(); //Отображаем список на экране

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int _tmain(int argc, _TCHAR* argv[])
{
	int i;
	tMachine t1;
	//TuringState *CurrentState;
 system("CLS");

 // если хотим ввести алфовит вручную
 //std::cout << "Put in alphabet"; 
 //std::getline(std::cin, currStr);
 //

 t1.SetAlphabet("1x=a*");
 

 //// Set rules
 
 t1.SetRules(); 
 ////

 // если хотим ввести ленту вручную
 //std::cout << "Put in current problem: "; 
 //std::getline(std::cin, currRibbon);
 //
 //currRibbon = "*1111x11=*";
 t1.SetRibbon("*1111x11=*");
 t1.Solve();
 
 system("PAUSE");

	return 0;
}


