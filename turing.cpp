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
