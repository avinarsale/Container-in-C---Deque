#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <math.h>
#include <initializer_list>
#include <memory.h>
#include <stdexcept>

#define DEPTH 200


namespace cs540 
{
template<typename Key_T,typename Mapped_T>
class Node;	
template<typename Key_T,typename Mapped_T>
class Map
{
	public:
		typedef std::pair<const Key_T, Mapped_T> ValueType;

	class Iterator{
		public: 
			Node<Key_T, Mapped_T> *activeNode;
		Iterator(const Iterator &it) : activeNode(it.getActiveNode()){}
		Iterator(Node<Key_T, Mapped_T>* node) : activeNode(node){}
		Node<Key_T, Mapped_T>* getActiveNode() const{return this->activeNode;}
		
		~Iterator(){
			activeNode=nullptr;
		}
		Iterator& operator=(const Iterator &it){
			activeNode=it.getActiveNode();
			return *this;
		}
		Iterator &operator++(){
			if(activeNode==nullptr){
				return *this;
			}
			activeNode=activeNode->next[0];
			return *this;
		}
		Iterator operator++(int){
			Map<Key_T,Mapped_T>::Iterator retIt=*this;
			if(activeNode==nullptr){
				return retIt;
			}
			activeNode=activeNode->next[0];
			return retIt;
		}
		Iterator &operator--(){
			if(activeNode==nullptr){
				return *this;
			}
			activeNode=activeNode->prev[0];
			return *this;
		}
		Iterator operator--(int){
			Map<Key_T,Mapped_T>::Iterator retIt=*this;
			if(activeNode==nullptr){
				return retIt;
			}
			activeNode=activeNode->prev[0];
			return retIt;
		}
		ValueType& operator*() const{
			return activeNode->value;
		}
		ValueType* operator->() const{
			return &activeNode->value;
		}
		
	};
	
	class ConstIterator{
		public:
			Node<Key_T, Mapped_T> *activeNode;
		ConstIterator(const ConstIterator &it) : activeNode(it.getActiveNode()){}
		ConstIterator(const Iterator &it) : activeNode(it.getActiveNode()){}
		ConstIterator(Node<Key_T, Mapped_T>* node) : activeNode(node){}
		Node<Key_T, Mapped_T>* getActiveNode() const{return activeNode;}

		~ConstIterator(){
			activeNode=nullptr;
		}
		ConstIterator& operator=(const ConstIterator &it){
			activeNode=it.getActiveNode();
			return *this;
		}
		ConstIterator &operator++(){
			if(activeNode==nullptr){
				return *this;
			}
			activeNode=activeNode->next[0];
			return *this;
		}
		ConstIterator operator++(int count){
			Map<Key_T,Mapped_T>::ConstIterator retIt=*this;
			if(activeNode==nullptr){
				return retIt;
			}
			activeNode=activeNode->next[0];
			return retIt;
		}
		ConstIterator &operator--(){
			if(activeNode==nullptr){
				return *this;
			}
			activeNode=activeNode->prev[0];
			return *this;
		}
		ConstIterator operator--(int count){
			Map<Key_T,Mapped_T>::ConstIterator retIt=*this;
			if(activeNode==nullptr){
				return retIt;
			}
			activeNode=activeNode->prev[0];
			return retIt;
		}
		const ValueType& operator*() const{
			return activeNode->value;
		}
		const ValueType* operator->() const{
			return &activeNode->value;
		}
		
	};
	
	class ReverseIterator{
		public:
			Node<Key_T, Mapped_T> *activeNode;
		ReverseIterator(const ReverseIterator &it) : activeNode(it.getActiveNode()){}
		ReverseIterator(Node<Key_T, Mapped_T>* node) : activeNode(node){}

		Node<Key_T, Mapped_T>* getActiveNode() const{return activeNode;}
		
		~ReverseIterator(){
			activeNode=nullptr;
		}
		ReverseIterator& operator=(const ReverseIterator &it){
			activeNode=it.getActiveNode();
			return *this;
		}
		ReverseIterator &operator++(){
			if(activeNode==nullptr){
				return *this;
			}
			activeNode=activeNode->prev[0];
			return *this;
		}
		ReverseIterator operator++(int){
			Map<Key_T,Mapped_T>::ReverseIterator retIt=*this;
			if(activeNode==nullptr){
				return retIt;
			}
			activeNode=activeNode->prev[0];
			return retIt;
		}
		ReverseIterator &operator--(){
			if(activeNode==nullptr){
				return *this;
			}
			activeNode=activeNode->next[0];
			return *this;
		}
		ReverseIterator operator--(int count){
			Map<Key_T,Mapped_T>::ReverseIterator retIt=*this;
			if(activeNode==nullptr){
				return retIt;
			}
			activeNode=activeNode->next[0];
			return retIt;
		}
		const ValueType &operator*() const{
			return activeNode->value;
		}
		const ValueType *operator->() const{
			return &activeNode->value;
		}
	};
	
	friend bool operator==(const Iterator &it1, const Iterator &it2){
		if(it1.activeNode==it2.activeNode){
			return true;
		}
		return false;
	}

	friend bool operator==(const ConstIterator &it1, const ConstIterator &it2){
		if(it1.activeNode==it2.activeNode){
			return true;
		}
		return false;
	}

	friend bool operator==(const Iterator &it1, const ConstIterator &it2){
	if(it1.activeNode==it2.activeNode){
			return true;
		}
		return false;
	}

	friend bool operator==(const ConstIterator &it1, const  Iterator &it2){
	if(it1.activeNode==it2.activeNode){
			return true;
		}
		return false;
	}

	friend bool operator!=(const Iterator &it1, const Iterator &it2){
	if(it1.activeNode==it2.activeNode){
			return false;
		}
		return true;
	}

	friend bool operator!=(const ConstIterator &it1, const ConstIterator &it2){
	if(it1.activeNode!=it2.activeNode){
			return true;
		}
		return false;
	}

	friend bool operator!=(const Iterator &it1, const ConstIterator &it2){
	if(it1.activeNode!=it2.activeNode){
			return true;
		}
		return false;
	}

	friend bool operator!=(const ConstIterator &it1, const Iterator &it2){
	if(it1.activeNode!=it2.activeNode){
			return true;
		}
		return false;
	}

	friend bool operator==(const ReverseIterator &it1, const ReverseIterator &it2){
	if(it1.activeNode==it2.activeNode){
			return true;
		}
		return false;
	}

	friend bool operator!=(const ReverseIterator &it1, const ReverseIterator &it2){
	if(it1.activeNode!=it2.activeNode){
			return true;
		}
		return false;
	}

	Node<Key_T,Mapped_T> *header;
	Node<Key_T,Mapped_T> *sentinel;
	int currentLevel;
	int listCount;
	void initialize_map(const ValueType &value){
		currentLevel = 0;
		listCount=0;
		header = new Node<Key_T,Mapped_T>(DEPTH,value); 
		sentinel = new Node<Key_T,Mapped_T>(DEPTH,value);
		for (int i = DEPTH;i >= 0;i--) 
		{
			header->next[i]=sentinel;
			sentinel->prev[i]=header;
			header->prev[i]=nullptr;
			sentinel->next[i]= nullptr;
		}
	}

	Map(){
		header=nullptr;
		sentinel=nullptr;
	}
	
	Map(const Map &map){
		bool firstInit=true;
		Node<Key_T, Mapped_T> *tNode;
			for(tNode = map.header->next[0];tNode!=map.sentinel;tNode=tNode->next[0]){
				if(firstInit){
					initialize_map(tNode->value);
					firstInit=false;
				}
				insert(tNode->value);
			}
	}
	
	Map &operator=(const Map& map){
		Node<Key_T, Mapped_T> *tNode = map.header->next[0];
		if(tNode == map.sentinel) return *this;
		while(tNode != map.sentinel){
			insert(tNode->value);
			tNode = tNode->next[0];
		}
		return *this;
	}

	Map(std::initializer_list<ValueType> initializer_list){
		bool firstInit=true;
		for(auto itList = initializer_list.begin();itList != initializer_list.end();itList++){
			if(firstInit){
				initialize_map(*itList);
				firstInit=false;
			}
			insert(*itList);
		}
	}

	size_t size() const{
		return listCount;
	}
	bool empty() const{
		if(listCount==0){
			return true;
		}
		return false;
	}
	Iterator begin() {
		if(header!=nullptr){
			return header->next[0];
		}
		return nullptr;
	}
	Iterator end() {
		return sentinel;
	}
	ConstIterator begin() const{
		if(header!=nullptr){
			return header->next[0];
		}
		return nullptr;
	}
	ConstIterator end() const{
		return sentinel;
	}
	
	ReverseIterator rbegin(){
		if(sentinel!=nullptr){
			return sentinel->prev[0];
		}
		return nullptr;
	}
	ReverseIterator rend(){
		if(header!=nullptr){
			return header;
		}
		return nullptr;
	}

	void clear(){
		if(header!=nullptr && sentinel!=nullptr){
			Node<Key_T, Mapped_T> *tNode;
			for(tNode = header->next[0];tNode!=sentinel;tNode=header->next[0])
			{
				erase(find(tNode->value.first));
			}
		}
	}
	~Map(){
		clear();
		delete header;
		delete sentinel;
	}
	
	//element access 
	Iterator find(const Key_T &);
	ConstIterator find(const Key_T &) const;
	Mapped_T &at(const Key_T &);
	const Mapped_T &at(const Key_T &) const;
	Mapped_T &operator[](const Key_T &); 

	// modifiers
	std::pair<Iterator, bool> insert(const ValueType &);

	template<typename IT_T>
	void insert(IT_T range_beg, IT_T range_end); 
	void erase(Iterator pos);
	void erase(const Key_T &); 

	Node<Key_T, Mapped_T>* lookupKey(const Key_T &key) const;
	
	// comparisons 
	friend bool operator==(const Map<Key_T, Mapped_T> &map1, const Map<Key_T, Mapped_T> &map2){
		Node<Key_T, Mapped_T> *nodePtr1 = map1.header->next[0];
		Node<Key_T, Mapped_T> *nodePtr2 = map2.header->next[0];

		while(nodePtr1 != map1.sentinel && nodePtr2 != map2.sentinel){
			if(nodePtr1->value != nodePtr2->value){
				return false;
			}
			nodePtr1=nodePtr1->next[0];
			nodePtr2=nodePtr2->next[0];
		}
		if(nodePtr1==map1.sentinel && nodePtr2==map2.sentinel){
			return true;
		}
		return false;
	}

	friend  bool operator!=(const Map<Key_T,Mapped_T> &map1, const Map<Key_T,Mapped_T> &map2){
		if(map1==map2){
			return false;
		}
		return true;
	}

	friend bool operator<(const Map<Key_T,Mapped_T> &map1, const Map<Key_T,Mapped_T> &map2){
		if(map1.size()==map2.size()){
			return false;
		}
		if(map1.size()<map2.size()){
			return true;
		}
		for(auto it1=map1.begin(),it2=map2.begin();it2!=map2.end() && it1!=map1.end();++it2,++it1){
			if(it1.activeNode->value.first<it2.activeNode->value.first && 
				it1.activeNode->value.second<it2.activeNode->value.second){
				continue;
			}
			else{
				return false;
			}
		}
		return true;
	}

}; // Map

template<typename Key_T,typename Mapped_T>
class Node{
	public:
		typedef std::pair<const Key_T, Mapped_T> ValueType;
	ValueType value;
	int levelCurr;
	Node<Key_T,Mapped_T> **next;
	Node<Key_T,Mapped_T> **prev;
	Node(int randomLevel, const ValueType &val):value(val),levelCurr(randomLevel)
	{
		next=new Node*[DEPTH+1];
		prev=new Node*[DEPTH+1];
	}
	~Node()
	{
		delete [] prev;
		delete [] next;
	} 
};

int getRandomLevel()  
{
	int newLevel = (int)(log((float) rand() / RAND_MAX) / log(0.5));
    if(newLevel<DEPTH){
		return newLevel;
    }
	return DEPTH;
} 
template<typename Key_T,typename Mapped_T>
Node<Key_T,Mapped_T>* Map<Key_T,Mapped_T>::lookupKey(const Key_T& key) const{
	if(header!=nullptr){
		Node<Key_T,Mapped_T> *leftn = header;
		
		for (int i = currentLevel;i >= 0;i--) 
		{
			while (leftn->next[i] != sentinel && leftn->next[i]->value.first < key)
				leftn = leftn->next[i];
		}
		leftn = leftn->next[0];
		if(leftn->value.first==key && leftn!=sentinel){
			return leftn;
		}
    }
   	return nullptr;
}

template<typename Key_T,typename Mapped_T>
typename Map<Key_T,Mapped_T>::Iterator Map<Key_T,Mapped_T>::find(const Key_T& key){
	Node<Key_T, Mapped_T> *leftn = lookupKey(key);
	if(leftn == nullptr){
		return Map<Key_T, Mapped_T>::Iterator(sentinel);
	}
	return Map<Key_T, Mapped_T>::Iterator(leftn);
}
template<typename Key_T,typename Mapped_T>
typename Map<Key_T,Mapped_T>::ConstIterator Map<Key_T,Mapped_T>::find(const Key_T& key) const{
	Node<Key_T, Mapped_T> *leftn = lookupKey(key);
	if(leftn == nullptr){
		return Map<Key_T, Mapped_T>::ConstIterator(sentinel);
	}
	return Map<Key_T, Mapped_T>::ConstIterator(leftn);
}

template<typename Key_T,typename Mapped_T>
Mapped_T& Map<Key_T,Mapped_T>::at(const Key_T &key){
	Node<Key_T,Mapped_T> *leftn=lookupKey(key);
	if(leftn==nullptr){
		throw std::out_of_range("Key not present!");
	}
	return leftn->value.second;
}
template<typename Key_T,typename Mapped_T>
const Mapped_T& Map<Key_T,Mapped_T>::at(const Key_T &key) const{
	Node<Key_T,Mapped_T> *leftn=lookupKey(key);
	if(leftn==nullptr){
		throw std::out_of_range("Key not present!");
	}
	return leftn->value.second;
}	

template<typename Key_T,typename Mapped_T>
Mapped_T& Map<Key_T, Mapped_T>::operator[](const Key_T& key){
	Node<Key_T, Mapped_T> *tNode = lookupKey(key);
	if(tNode == nullptr){
		Map<Key_T, Mapped_T>::Iterator itr = insert(std::make_pair(key,Mapped_T{ })).first;
		return itr.activeNode->value.second;
	}
	return tNode->value.second;
}

template<typename Key_T,typename Mapped_T>
std::pair<typename Map<Key_T, Mapped_T>::Iterator, bool> Map<Key_T,Mapped_T>::insert(const ValueType &value){

	if(header==nullptr){
		initialize_map(value);
	}
    Node<Key_T,Mapped_T> *leftn = header;   
    Node<Key_T,Mapped_T> *holder[DEPTH + 1];
	
    for (int i = currentLevel;i >= 0;i--){
        while (leftn->next[i]->value.first < value.first && leftn->next[i] != sentinel) 
            leftn = leftn->next[i];
        holder[i] = leftn; 
    }
    
	if(leftn->next[0]->value.first == value.first && leftn->next[0]!=sentinel){
		auto returnValue=std::make_pair(Map<Key_T, Mapped_T>::Iterator(leftn->next[0]), true);
		return returnValue;
	}
	else
	{ 
		if (!(leftn->next[0]->value.first == value.first) || leftn->next[0] == sentinel )
		{
			int newLevel = getRandomLevel();
			if(newLevel==0){newLevel++;}
			Node<Key_T,Mapped_T> *newNode = new Node<Key_T,Mapped_T>(newLevel, value);

			if (newLevel > currentLevel) 
			{
				for (int i = newLevel + 1;i >= currentLevel;i--){  
					header->next[i]=newNode;
					newNode->next[i]=sentinel;
					sentinel->prev[i]=newNode;
					newNode->prev[i]=header;
					holder[i]=nullptr;
				}
				currentLevel = newLevel;
			}
			for (int i = 0;i <= newLevel;i++){  
				if(holder[i]!=nullptr){
					newNode->next[i]=holder[i]->next[i];
					holder[i]->next[i]->prev[i]=newNode;
					holder[i]->next[i]=newNode;
					newNode->prev[i]=holder[i];
				}
			}
			
			listCount=listCount+1;
			auto returnValue=std::make_pair(Map<Key_T, Mapped_T>::Iterator(newNode), true);
			return returnValue;
		}
	}
}

template<typename Key_T,typename Mapped_T>
template<typename IT_T>
void Map<Key_T,Mapped_T>::insert(IT_T range_beg, IT_T range_end){
	for(auto it=range_beg;it!=range_end;it++){
		insert(*it);
	}
}

template<typename Key_T,typename Mapped_T>
void Map<Key_T,Mapped_T>::erase(Map<Key_T,Mapped_T>::Iterator pos){
	const Key_T& keyValue=pos.getActiveNode()->value.first;
	erase(keyValue);
}

template<typename Key_T,typename Mapped_T>
void Map<Key_T,Mapped_T>::erase(const Key_T &value){

	Node<Key_T,Mapped_T> *leftn = header;   
    Node<Key_T,Mapped_T> *holder[DEPTH + 1];
    for (int i = currentLevel;i >= 0;i--){
        while (leftn->next[i] != sentinel && leftn->next[i]->value.first < value)
            leftn = leftn->next[i];
        holder[i] = leftn; 
    }
    leftn = leftn->next[0];
    if (leftn!=sentinel && leftn->value.first == value) 
    {
        for (int i = 0;i <= currentLevel;i++){
            if (holder[i]->next[i] == leftn)
            {
				holder[i]->next[i] = leftn->next[i];
				leftn->next[i]->prev[i]=holder[i];
            }
			else{
           		break;
        	}
        }
        listCount=listCount-1;
        delete leftn;
        while (currentLevel > 0 && header->next[currentLevel] == sentinel) 
            currentLevel--;
    }
}

} // namespace 
