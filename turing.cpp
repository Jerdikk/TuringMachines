#include "stdafx.h"
#include "turing.h"




Ribbon::~Ribbon() //Деструктор
 {   
     while (First) //Пока по адресу на начало списка что-то есть
     {
         Last=First->Next; //Резервная копия адреса следующего звена списка
         delete First; //Очистка памяти от первого звена
         First=Last; //Смена адреса начала на адрес следующего элемента
     }
	 CurrentPosition = NULL;
 }
 
 void Ribbon::Add(RibbonSymbol x)
 {
   RibbonCell *temp=new RibbonCell; //Выделение памяти под новый элемент структуры
   temp->Next=NULL;  //Указываем, что изначально по следующему адресу пусто
   temp->SetCellValue(x);//Записываем значение в структуру
 
   if (First!=NULL) //Если список не пуст
   {
       temp->Prev=Last; //Указываем адрес на предыдущий элемент в соотв. поле
       Last->Next=temp; //Указываем адрес следующего за хвостом элемента
       Last=temp; //Меняем адрес хвоста
   }
   else //Если список пустой
   {
       temp->Prev=NULL; //Предыдущий элемент указывает в пустоту
       First=Last=temp; //Голова=Хвост=тот элемент, что сейчас добавили
	   CurrentPosition = First;
   }
   //CurrentPosition = temp;
 }
 
 void Ribbon::Show()
 {
/*//ВЫВОДИМ СПИСОК С КОНЦА
     RibbonCell *temp=Last;
      //Временный указатель на адрес последнего элемента
     while (temp!=NULL) //Пока не встретится пустое значение
     {
		 std::cout<<temp->GetCharCellValue()<<" "; //Выводить значение на экран
	 temp=temp->Prev; //Указываем, что нужен адрес предыдущего элемента
     }
     std::cout<<"\n";
 */
 //ВЫВОДИМ СПИСОК С НАЧАЛА
    
	 Top();
	RibbonCell *temp=ReadCellFromHeadPosition();
    while (temp!=NULL) //Пока не встретим пустое значение
     {
	 std::cout<<temp->GetCharCellValue()<<" "; //Выводим каждое считанное значение на экран
	 temp=temp->Next; //Смена адреса на адрес следующего элемента
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
