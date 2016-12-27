// Turnig.cpp: определяет точку входа для консольного приложения.
//
/*
Original code by Marat Fazylyanov 

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any
damages arising from the use of this software.

Permission is granted to anyone to use this software for any
purpose, including commercial applications, and to alter it and
redistribute it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must
not claim that you wrote the original software. If you use this
software in a product, an acknowledgment in the product documentation
would be appreciated but is not required.

2. Altered source versions must be plainly marked as such, and
must not be misrepresented as being the original software.

3. This notice may not be removed or altered from any source
distribution.
*/

#include "stdafx.h"
//#include <std
#include<string>
#include<iostream>
#include "turing.h"
#include "tinyxml.h"


const int MAXALPHABET = 128;
const int MAXSTATES = 255;
const int MAXRIBBON = 4096;

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
	bool SetAlphabet(char *str);
	bool SetAlphabetFromXML(char *str);
	bool SetRibbon(char *str);
	char *GetRibbonFromXML(char *filename);
	void WriteRibbonToXML(char *filename);
	void SetRules();
	void SetXMLRules(char *str);
	void Solve();
	void SaveXML();
	tMachine() {maxalphabet=0;maxstates=0;};
	~tMachine() {
	for (int count = 0; count < (maxalphabet+1); count++)
        delete [] currRules[count];
	};
private:
	int positionOnRibbon;
	int maxPositionOnRibbon;
	int maxalphabet;
	int maxstates;
	char alphabet[MAXALPHABET];
	Rules **currRules;//[MAXALPHABET][MAXSTATES];
	Ribbon tmRibbon; //Объявляем переменную, тип которой есть список

};

void OnErrorWrite(char *str)
{
	printf( "Suddenly App raise Error='%s'. Exiting.\n", str );
	system("PAUSE");
	exit( 1 );
}


char * tMachine::GetRibbonFromXML(char *filename)
{
	
	TiXmlDocument doc( filename );
	bool loadOkay = doc.LoadFile();
	if ( !loadOkay )
	{		
		char *errstr=new char[255];
		sprintf( errstr,"Could not load test file '%s'. Error='%s'.", filename, doc.ErrorDesc() );
		OnErrorWrite(errstr);
	}
	TiXmlNode* node = 0;
	TiXmlNode* node1 = 0;
	TiXmlElement* RibbonElement = 0;
	TiXmlElement* itemElement = 0;

	node = doc.FirstChild("Ribbon");
	assert(node);
	RibbonElement = node->ToElement();
	assert( RibbonElement  );
	node = RibbonElement->FirstChildElement("In");	
	std::string ttt = node->ValueTStr().c_str();
	assert( node );
	node = node->FirstChild();
	ttt = node->Value();
	if (ttt.empty()) OnErrorWrite("String with Ribbon in XML is empty!");
	
	maxPositionOnRibbon = ttt.length();
	if (maxPositionOnRibbon>=MAXRIBBON) OnErrorWrite("String with Ribbon is too long!");
	positionOnRibbon=0;
	char *result = new char[maxPositionOnRibbon+1];
	strcpy(result,ttt.c_str());

	return result;
}

void tMachine::WriteRibbonToXML(char *filename)
{
	int i;
	TiXmlDocument doc( filename );
	bool loadOkay = doc.LoadFile();
	bool isnewfile = false;
	if ( !loadOkay ) isnewfile = true;	
	TiXmlNode* node = 0;
	TiXmlNode* node1 = 0;
	TiXmlElement* RibbonElement = 0;
	TiXmlElement* itemElement = 0;
	TiXmlText* textik = 0;
	if (!isnewfile)
	{
		node = doc.FirstChild( "Ribbon" );
		assert( node );
		RibbonElement = node->ToElement();
		assert( RibbonElement  );
		node = RibbonElement->FirstChildElement("Out");	
		std::string ttt = node->ValueTStr().c_str();
		assert( node );
		node1 = node->FirstChild();		
		if (tmRibbon.GetRibbonLength()>=MAXRIBBON) OnErrorWrite("String with Ribbon is too long to write!");
		char tempRibbon[MAXRIBBON];		
		tmRibbon.Top();
		for ( i = 0; i < tmRibbon.GetRibbonLength(); i++ )
		{
			tempRibbon[i]=tmRibbon.ReadCellFromHeadPosition()->GetCellValue();
			tmRibbon.Right();
		}
		tempRibbon[tmRibbon.GetRibbonLength()]=0;
		if (!node1)
		{
			textik = new TiXmlText( tempRibbon );
			node->LinkEndChild( textik );
		}
		else
		 node1->SetValue(tempRibbon);
		
	}
	else
	{
	}
	doc.SaveFile( filename );
}

bool tMachine::SetAlphabetFromXML(char *str)
{

	if (str==0)	return false;
	TiXmlDocument doc( str );
	bool loadOkay = doc.LoadFile();
	if ( !loadOkay )
	{
		printf( "Could not load test file 'turing1.xml'. Error='%s'. Exiting.\n", doc.ErrorDesc() );
		return false;
	}

	TiXmlNode* node = 0;
	TiXmlNode* node1 = 0;
	TiXmlElement* TuringMachineElement = 0;
	TiXmlElement* itemElement = 0;

	node = doc.FirstChild( "TuringMachine" );
	assert( node );
	TuringMachineElement = node->ToElement();
	assert( TuringMachineElement  );
	node = TuringMachineElement->FirstChildElement("Alphabet");	
	std::string ttt = node->ValueTStr().c_str();
	assert( node );
	itemElement = node->FirstChildElement();
	ttt = itemElement->Value();
	assert( itemElement  );
	int count=0;
	int i;
	for( node1 = node->FirstChild( "Symbol" ),i=0;
			 node1;
			 node1 = node1->NextSibling( "Symbol" ),i++ )
		{
			ttt = node1->Value();
			ttt= node1->FirstChild()->Value();
			alphabet[i] = ttt.at(0);
			count++;
		}

	maxalphabet = count;
	return true;

}


void tMachine::SaveXML()
{
	int i,j;
	TiXmlDocument doc;
	TiXmlElement * xmlroot;
	TiXmlElement * xmlAlphabet;	
	TiXmlElement * xmlSymbol;
	TiXmlElement * xmlRules;
	TiXmlElement * xmlRule;
	//TiXmlElement * xmlElem;
	char tempCStr[2];	

	doc.LinkEndChild( new TiXmlDeclaration( "1.0", "", "" ) );
	/// Create root element
	xmlroot = new TiXmlElement( "TuringMachine" );
	doc.LinkEndChild( xmlroot );
	/// Create first child element Alphabet
	xmlAlphabet = new TiXmlElement( "Alphabet" );
	xmlroot->LinkEndChild( xmlAlphabet );
	
	/// Create child nodes Symbol in Alphabet
	for ( i = 0; i < maxalphabet; i++ )
	{
		xmlSymbol = new TiXmlElement( "Symbol" );		
		tempCStr[0] = alphabet[i];
		tempCStr[1] = 0;
		xmlSymbol->LinkEndChild( new TiXmlText( tempCStr ) );
		xmlAlphabet->LinkEndChild( xmlSymbol );
	}

	xmlRules = new TiXmlElement( "Rules" );
	xmlRules->SetAttribute("MaxStates", maxstates);
	xmlroot->LinkEndChild( xmlRules );
	
	for ( i = 0; i < (maxstates+1); i++)
		for ( j = 0; j < (maxalphabet+1); j++ )
			if (currRules[j][i].isRule)
			{
				xmlRule = new TiXmlElement( "Rule" );
				xmlRules->LinkEndChild( xmlRule );

				//xmlElem = new TiXmlElement( "CurentSymbol" );
				tempCStr[0] = alphabet[j];
				tempCStr[1] = 0;
				//xmlElem->LinkEndChild( new TiXmlText( tempCStr ) );
				xmlRule->SetAttribute("CurentSymbol", tempCStr);
				xmlRule->SetAttribute("CurrentState", i);
				tempCStr[0] = currRules[j][i].currSymbol;
				tempCStr[1] = 0;			
				xmlRule->SetAttribute("SymbolToWrite", tempCStr);
				xmlRule->SetAttribute("NextState", currRules[j][i].nextstate);
				xmlRule->SetAttribute("IsRule", currRules[j][i].isRule);

				switch (currRules[j][i].currDirection)
				{
				case TuringDirection::Left:
					tempCStr[0] = 'L';
					break;
				case TuringDirection::Right:
					tempCStr[0] = 'R';
					break;
				case TuringDirection::Stay:
					tempCStr[0] = 'N';
					break;
				default:
					tempCStr[0] = 0;
					break;
				}

				xmlRule->SetAttribute("Direction", tempCStr);
				//CurentSymbol
				//CurrentState
				//SymbolToWrite
				//NextState
				//Direction
				//IsRule
			}


	doc.SaveFile( "turing1.xml" );

}

bool tMachine::SetAlphabet(char *str)
{
	int i;
	std::string currStr;
	if (str==0) return false;
	currStr = str;
	maxalphabet = currStr.length();
	for ( i = 0; i < maxalphabet; i++ )
	{
		alphabet[i] = currStr.at(i);
	}
	return true;	
}

bool tMachine::SetRibbon(char *str)
{
	int i;
	std::string currRibbon;
	if (str==0) return false;
	currRibbon = str;
	maxPositionOnRibbon = currRibbon.length();
	if (maxPositionOnRibbon>=MAXRIBBON) return false;
	positionOnRibbon=0;
	for ( i = 0; i < maxPositionOnRibbon; i++ )
		tmRibbon.Add(currRibbon.at(i)); //Добавляем в список элементы
	tmRibbon.Show(); //Отображаем список на экране
	return true;		
}
void tMachine::SetXMLRules(char *str)
{
	int count=0;
	char tempChar;
	int i,j, iCurrState,iNextState,iRes,iIsRule,currAlphabetNum;
	maxstates = 9;

	currRules = new Rules*[(maxalphabet+1)];


	TiXmlDocument doc( str );
	bool loadOkay = doc.LoadFile();
	if ( !loadOkay )
	{
		printf( "Could not load test file 'turing1.xml'. Error='%s'. Exiting.\n", doc.ErrorDesc() );
		system("PAUSE");
		exit( 1 );
	}

	TiXmlNode* node = 0;
	TiXmlNode* root = 0;
	TiXmlNode* node1 = 0;
	TiXmlElement* TuringMachineElement = 0;
	TiXmlElement* itemElement = 0;

	root = doc.FirstChild( "TuringMachine" );
	assert( root );
	TuringMachineElement = root->ToElement();
	assert( TuringMachineElement  );
	node = TuringMachineElement->FirstChildElement("Rules");	
	itemElement = node->ToElement();
	iRes = itemElement->QueryIntAttribute("MaxStates",&maxstates);			
	if ( iRes == TIXML_NO_ATTRIBUTE )
	{
		printf( "Could not get maxtstates from XML. Exiting.\n");
		system("PAUSE");
		exit( 1 );
	}

	std::string ttt = node->ValueTStr().c_str();
	assert( node );

	for (i=0; i<(maxalphabet+1); i++)
		currRules[i] = new Rules[(maxstates+1)];
	/// Init rules
	for (i=0; i<(maxstates+1); i++)
		for (j=0; j<(maxalphabet+1); j++)
		{
			currRules[j][i].currDirection = TuringDirection::Stay;
			currRules[j][i].currSymbol = 0;
			currRules[j][i].isRule = 0;
			currRules[j][i].nextstate = -1;
		}


	itemElement = node->FirstChildElement("Rule");
	ttt = itemElement->Value();
	assert( itemElement  );
	
	for( node1 = node->FirstChild( "Rule" ),i=0;
			 node1;
			 node1 = node1->NextSibling( "Rule" ),i++ )
		{
			ttt = node1->Value();
			itemElement = node1->ToElement();
			iRes = itemElement->QueryIntAttribute("NextState",&iNextState);
			if ( iRes == TIXML_NO_ATTRIBUTE )
			{
				printf( "Could not get NextState from XML. Exiting.\n");
				system("PAUSE");
				exit( 1 );
			}

			if (iNextState>=0)
			{
				iRes = itemElement->QueryIntAttribute("CurrentState",&iCurrState);			
				if ( iRes == TIXML_NO_ATTRIBUTE )
				{
					printf( "Could not get CurrentState from XML. Exiting.\n");
					system("PAUSE");
					exit( 1 );
				}

				iRes = itemElement->QueryIntAttribute("IsRule",&iIsRule);	
				if ( iRes == TIXML_NO_ATTRIBUTE )
				{
					printf( "Could not get IsRule from XML. Exiting.\n");
					system("PAUSE");
					exit( 1 );
				}

				ttt = itemElement->Attribute("CurentSymbol");
				tempChar = ttt.at(0);
				currAlphabetNum = -1;
				for ( j = 0; j < maxalphabet; j++ )	  
					if (tempChar == alphabet[j])
					{
						currAlphabetNum = j;
						j = maxalphabet;
					};
				if ((currAlphabetNum == -1) && (j == maxalphabet) && (iIsRule))
				{
					currAlphabetNum = j;
				}
				ttt = itemElement->Attribute("SymbolToWrite");
				tempChar = ttt.at(0);
				currRules[currAlphabetNum][iCurrState].currSymbol = tempChar;
				ttt = itemElement->Attribute("Direction");
				tempChar = ttt.at(0);
				switch(tempChar)
				{
				case 'L':
					currRules[currAlphabetNum][iCurrState].currDirection = TuringDirection::Left;
					break;
				case 'R':
					currRules[currAlphabetNum][iCurrState].currDirection = TuringDirection::Right;
					break;
				case 'N':
					currRules[currAlphabetNum][iCurrState].currDirection = TuringDirection::Stay;
					break;
				default:
					break;
				};
				currRules[currAlphabetNum][iCurrState].nextstate = iNextState;
				currRules[currAlphabetNum][iCurrState].isRule = iIsRule;
				//alphabet[i] = ttt.at(0);
			}
			count++;
		}

 //maxalphabet = count;

}
void tMachine::SetRules()
{
	int i,j;
	maxstates = 9;

	currRules = new Rules*[(maxalphabet+1)];
	for (i=0; i<(maxalphabet+1); i++)
		currRules[i] = new Rules[(maxstates+1)];
	for (i=0; i<(maxstates+1); i++)
		for (j=0; j<(maxalphabet+1); j++)
		{
			currRules[j][i].currDirection = TuringDirection::Stay;
			currRules[j][i].currSymbol = 0;
			currRules[j][i].isRule = 0;
			currRules[j][i].nextstate = -1;
		}
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
							system("PAUSE");
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

 if (!t1.SetAlphabetFromXML("turing1.xml"))
	 OnErrorWrite("Can't set alphabet from XML!"); 

 //// Set rules
 
 //t1.SetRules(); 
 t1.SetXMLRules("turing1.xml");
 ////

 // если хотим ввести ленту вручную
 //std::cout << "Put in current problem: "; 
 //std::getline(std::cin, currRibbon);
 //
 //currRibbon = "*1111x11=*";
 
 char *tempStrRibbon = t1.GetRibbonFromXML("ribbon.xml");

 if (tempStrRibbon==0) 
	 OnErrorWrite("Can't read ribbon from XML!");
 if (!t1.SetRibbon(t1.GetRibbonFromXML("ribbon.xml")))
	 OnErrorWrite("Can't read and set ribbon from XML!");
 //t1.SetRibbon("*1111x111=*");
 t1.Solve();
 t1.WriteRibbonToXML("ribbon.xml");
 //t1.SaveXML();
 

 system("PAUSE");

	return 0;
}


