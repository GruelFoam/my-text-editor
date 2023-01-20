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
	void Traverse(void (*visit)(const Type&));//遍历调用某个函数
	bool GetElem(int positon, Type& e) const;
	bool SetElem(int positon, const Type& e);
	bool Delete(int position, Type& e);//删除第position个元素，并利用e返回该节点的值
	bool Insert(int position, const Type& e);
	LinkList(const LinkList<Type>& source);//复制构造
	void Copy(LinkList<Type>* source);
	//LinkList(Type& source);
	LinkList<Type>& operator = (LinkList<Type>& source);
	//LinkList<Type>& operator = (Type& source);
};

#define LINKLIST_HEAD
#include"LinkList.cpp"