// Turnig.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
//#include <std
#include<string>
#include<iostream>
#include "turing.h"

const int MAXALPHABET = 255;
const int MAXSTATES = 255;

int TuringObject::gTuringObjectNum=0;


char alphabet[MAXALPHABET];
int maxalphabet;
int maxstates;
std::string currStr;
std::string currRibbon;


struct Rules {
	int nextstate;
	char currSymbol;
	TuringDirection currDirection;
	int isRule;
};



Rules currRules[MAXALPHABET][MAXSTATES];

void GetRules()
{
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

void Solve()
{
int i;
Ribbon lst; //Объявляем переменную, тип которой есть список

 int ribbonlength = currRibbon.length();

 for ( i = 0; i < ribbonlength; i++ )
	 lst.Add(currRibbon.at(i)); //Добавляем в список элементы
  lst.Show(); //Отображаем список на экране


  bool done = false;
  RibbonCell *temp;
  char tempChar;
  int currAlphabetNum;

  int currentTuringMachineState=0;

  lst.Top();
  do {
	  temp = lst.ReadCellFromHeadPosition();
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
				  if (!lst.Move(currRules[currAlphabetNum][currentTuringMachineState].currDirection))
				  {
					  if (currRules[currAlphabetNum][currentTuringMachineState].currDirection == TuringDirection::Right)
					  {
						  lst.Add(' ');
						  if (!lst.Move(currRules[currAlphabetNum][currentTuringMachineState].currDirection))
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
				  lst.Move(currRules[i][currentTuringMachineState].currDirection);
				  currentTuringMachineState = currRules[i][currentTuringMachineState].nextstate;
				  if ( currentTuringMachineState == maxstates)
					  done = true;
			  }
		  }
	  }

  } while (!done);

  lst.Show(); //Отображаем список на экране

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int _tmain(int argc, _TCHAR* argv[])
{
	int i;
	//TuringState *CurrentState;
 system("CLS");

 // если хотим ввести алфовит вручную
 //std::cout << "Put in alphabet"; 
 //std::getline(std::cin, currStr);
 //
 currStr = "1x=a*";

 maxalphabet = currStr.length();
 maxstates = 9;


 for ( i = 0; i < maxalphabet; i++ )
 {
	 alphabet[i] = currStr.at(i);
 }

 //// Set rules
 
GetRules(); 
 ////

 // если хотим ввести ленту вручную
 //std::cout << "Put in current problem: "; 
 //std::getline(std::cin, currRibbon);
 //
 currRibbon = "*1111x11=*";

 Solve();
 
 system("PAUSE");

	return 0;
}


