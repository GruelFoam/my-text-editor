#ifdef LINKLIST_HEAD

template<class Type>
Node<Type>* LinkList<Type>::Getptr(int position) const {
	Node<Type>* temp = head;
	int i = 0;
	while (temp != nullptr && i < position) {
		i++;
		temp = temp->next;
	}
	if (i == position) {
		return temp;
	}
	else {
		return nullptr;
	}
}

template<class Type>
LinkList<Type>::LinkList() {

	head = new Node<Type>;
	num = 0;
}

template<class Type>
LinkList<Type>::LinkList(const LinkList<Type>& source) {
	this->head = new Node<Type>;
	int i = 1;
	Type temp = 0;
	while (i <= source.Length()) {
		source.GetElem(i, temp);
		this->Insert(i, temp);
		i++;
	}
	return;
}

template<class Type>
LinkList<Type>& LinkList<Type>::operator=(LinkList<Type>& source) {
	if (&source != this) {
		if (source.Empty()) {
			Clear();
		}
		else {
			Clear();
			int i = 1;
			Type temp = 0;
			while (i <= source.Length()) {
				source.GetElem(i, temp);
				this->Insert(i, temp);
				i++;
			}
		}
	}
	return *this;
}

template<class Type>
void LinkList<Type>::Copy(LinkList<Type>* source) {
	if (source != this) {
		if (source->Empty()) {
			Clear();
		}
		else {
			Clear();
			int i = 1;
			Type temp = 0;
			while (i <= source->Length()) {
				source->GetElem(i, temp);
				this->Insert(i, temp);
				i++;
			}
		}
	}
}

template<class Type>
LinkList<Type>::~LinkList() {
	Clear();
	delete head;
}

template<class Type>
int LinkList<Type>::Length() const{
	return num;
}

template<class Type>
bool LinkList<Type>::Empty() {
	return (head->next == nullptr);
}

template<class Type>
void LinkList<Type>::Clear() {
	while (num != 0) {
		num--;
		Type e;
		Delete(1, e);
	}
}

template<class Type>
bool LinkList<Type>::GetElem(int position, Type& e) const {
	if (position < 1 || position > num) {
		return false;
	}
	Node<Type>* temp = Getptr(position);
	e = temp->data;
	return true;
}

template<class Type>
bool LinkList<Type>::SetElem(int position, const Type& e) {
	if (position < 1 || position > num) {
		return false;
	}
	Node<Type>* temp = Getptr(position);
	temp->data = e;
	return true;
}

template<class Type>
bool LinkList<Type>::Insert(int position, const Type& e) {
	if (position < 1 || position > num + 1) {
		return false;
	}
	Node<Type>* newnode = new Node<Type>(e);
	Node<Type>* prenode = Getptr(position - 1);
	newnode->next = prenode->next;
	prenode->next = newnode;
	num++;
	return true;
}

template<class Type>
bool LinkList<Type>::Delete(int position, Type& e) {
	if (position < 1 || position > num) {
		return false;
	}
	Node<Type>* prenode = Getptr(position - 1);
	Node<Type>* temp = prenode->next;
	e = temp->data;
	prenode->next = temp->next;
	delete temp;
	num--;
	return true;
}

template<class Type>
void LinkList<Type>::Traverse(void (*visit)(const Type&)) {
	Node<Type>* temp = head->next;
	for (; temp != nullptr; temp = temp->next) {
		(*visit)(temp->data);
	}
}

#endif