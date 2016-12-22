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
#include "turing.h"




Ribbon::~Ribbon() //����������
 {   
     while (First) //���� �� ������ �� ������ ������ ���-�� ����
     {
         Last=First->Next; //��������� ����� ������ ���������� ����� ������
         delete First; //������� ������ �� ������� �����
         First=Last; //����� ������ ������ �� ����� ���������� ��������
     }
	 CurrentPosition = NULL;
 }
 
 void Ribbon::Add(RibbonSymbol x)
 {
   RibbonCell *temp=new RibbonCell; //��������� ������ ��� ����� ������� ���������
   temp->Next=NULL;  //���������, ��� ���������� �� ���������� ������ �����
   temp->SetCellValue(x);//���������� �������� � ���������
	ribbonLength++;
   if (First!=NULL) //���� ������ �� ����
   {
       temp->Prev=Last; //��������� ����� �� ���������� ������� � �����. ����
       Last->Next=temp; //��������� ����� ���������� �� ������� ��������
       Last=temp; //������ ����� ������
   }
   else //���� ������ ������
   {
       temp->Prev=NULL; //���������� ������� ��������� � �������
       First=Last=temp; //������=�����=��� �������, ��� ������ ��������
	   CurrentPosition = First;
   }
   //CurrentPosition = temp;
 }
 
 void Ribbon::Show()
 {
/*//������� ������ � �����
     RibbonCell *temp=Last;
      //��������� ��������� �� ����� ���������� ��������
     while (temp!=NULL) //���� �� ���������� ������ ��������
     {
		 std::cout<<temp->GetCharCellValue()<<" "; //�������� �������� �� �����
	 temp=temp->Prev; //���������, ��� ����� ����� ����������� ��������
     }
     std::cout<<"\n";
 */
 //������� ������ � ������
    
	 Top();
	RibbonCell *temp=ReadCellFromHeadPosition();
    while (temp!=NULL) //���� �� �������� ������ ��������
     {
	 std::cout<<temp->GetCharCellValue()<<" "; //������� ������ ��������� �������� �� �����
	 temp=temp->Next; //����� ������ �� ����� ���������� ��������
     }
     std::cout<<"\n";
 }
 
 int Ribbon::Left()
 {
	 if (CurrentPosition->Prev != NULL)
	 {
		 CurrentPosition = CurrentPosition->Prev;
		 return 1;
	 }
	 else
		return 0;
 }

 int Ribbon::Right()
 {
	 if (CurrentPosition->Next != NULL)
	 {
		 CurrentPosition = CurrentPosition->Next;
		 return 1;
	 }
	 else
		return 0;
 }
