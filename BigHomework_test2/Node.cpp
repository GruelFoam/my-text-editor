#ifdef NODE_HEAD
template<class Type>
Node<Type>::Node() {
	data = '\0';
	next = nullptr;
}

template<class Type>
Node<Type>::Node(const Type& e, Node<Type>* ptr) {
	data = e;
	next = ptr;
}
#endif