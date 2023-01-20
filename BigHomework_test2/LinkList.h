#pragma once
#include"Node.h"

template<class Type>
class LinkList
{
public:
	Node<Type>* head;
	int num;
	Node<Type>* Getptr(int position) const;
//public:
	LinkList();
	virtual ~LinkList();
	bool Empty();
	int Length() const;
	void Clear();
	void Traverse(void (*visit)(const Type&));//��������ĳ������
	bool GetElem(int positon, Type& e) const;
	bool SetElem(int positon, const Type& e);
	bool Delete(int position, Type& e);//ɾ����position��Ԫ�أ�������e���ظýڵ��ֵ
	bool Insert(int position, const Type& e);
	LinkList(const LinkList<Type>& source);//���ƹ���
	void Copy(LinkList<Type>* source);
	//LinkList(Type& source);
	LinkList<Type>& operator = (LinkList<Type>& source);
	//LinkList<Type>& operator = (Type& source);
};

#define LINKLIST_HEAD
#include"LinkList.cpp"