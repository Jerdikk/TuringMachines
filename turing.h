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


#pragma once

#include "stdafx.h"




enum TuringDirection {Left, Right, Stay};

typedef char RibbonSymbol;

class TuringObject
{
private:
	int ID;
	static int gTuringObjectNum;
public:
	TuringObject() {ID=(++gTuringObjectNum);};
	int GetID() {return ID;};
};

class RibbonCell : TuringObject   /// структура €чейки ленты
	{
	private:
		RibbonSymbol CellValue;		
	public:
		RibbonCell() {Next=NULL;Prev=NULL;};
		RibbonSymbol GetCellValue() {return CellValue;};
		char GetCharCellValue() {return char(CellValue);};
		void SetCellValue(RibbonSymbol x) {CellValue = x;};		

		RibbonCell *Next, *Prev;
};

class Ribbon : TuringObject
	{         /// класс ленты дл€ машины “ьюринга
   RibbonCell *First, *Last; //”казатели на адреса начала списка и его конца
   RibbonCell *CurrentPosition;  //”казатели текущей €чейки над который расположен считыватель
   int ribbonLength;
 public:
     Ribbon():First(NULL),Last(NULL),CurrentPosition(NULL){ribbonLength=0;}; //»нициализируем адреса как пустые
     ~Ribbon(); //ƒеструктор
     void Show(); //‘ункци€ отображени€ списка на экране
	 int GetRibbonLength() {return ribbonLength;};
     void Add(RibbonSymbol x); //‘ункци€ добавлени€ элементов в список
	 int Left();
	 int Right();
	 void Top() {CurrentPosition = First;};
	 RibbonCell *ReadCellFromHeadPosition() {return CurrentPosition;};
	 int Move(TuringDirection temp) 
	 {
		 int result = -1;
		 if (temp == TuringDirection::Left)
		 {
			 result = Left();
		 }
		 if (temp == TuringDirection::Right)
		 {
			 result = Right();
		 }
		 return result;
	 };
};

/*

 class TuringState;

 class TuringTransitionRule : TuringObject
 {
 private:
	 char RuleString[6];	
	 int RuleID;
 public:
	 char *GetRuleString() {return RuleString;};
	 void SetRuleString(char str[6]) {memcpy(RuleString,str,6);};

	 TuringTransitionRule() {memset(RuleString,0,sizeof RuleString);RuleID = 0;};
	 void SetTransitionRule (char rulestr[6]);
	 void SetTransitionRule (RibbonSymbol BeforeTransValue, RibbonSymbol AfterTransValue, TuringDirection TransCommand);

	 RibbonSymbol BeforeTransValue;
	 RibbonSymbol AfterTransValue;
	 TuringDirection TransCommand;
	 TuringState *NextState;	 
 };

 class TuringTransitionListNode : TuringObject
 {
	int TuringTransitionRuleID;

	TuringTransitionListNode *Next;
 };

 class TuringTransitionList : TuringObject
 {
	TuringTransitionListNode *Head;

	void Add();
	void Remove(int ruleid);
	void ShowList();
 };


 class TuringState : TuringObject
 {
 private:
	 int statenum;
 public:
	 TuringState() {statenum = 0;};

	 int GetState() { return statenum; };
	 void SetState(int num) { statenum = num; };

	 TuringTransitionList *list;	 
 };

 class TuringMachine : TuringObject
 {
	 Ribbon *CurrentRibbon;
	 TuringState *CurrentState;
	 TuringMachine() {};
	 ~TuringMachine() {};
	 void SetRules() {};
	 void Process() {};
 };
 */
