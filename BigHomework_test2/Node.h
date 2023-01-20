#pragma once

template<class Type>
struct Node
{
	Node<Type>* next;
	Type data;
	Node();
	Node(const Type& e, Node<Type>* ptr = nullptr);
};
#define NODE_HEAD
#include"Node.cpp"
