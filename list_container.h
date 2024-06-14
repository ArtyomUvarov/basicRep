#pragma once
#include <iostream>

template <typename T>
class ListContainer
{
public:
	struct Node {
		Node * next; // указатель на следующий элемент Node
		Node * prev; // указатель на предыдущий элемент Node
		T data; // пользовательские данные (хранимый объект)
	};

	ListContainer() : m_last{ nullptr }, m_first{ nullptr }, m_size{ 0 } {}
	 
	void push_back( const T & value ) {
 		Node * new_node = new Node{}; // создание нового узла
		new_node->prev = m_last; // предыдущим элементом станет последний
		new_node->next = nullptr; // следующего элемента пока нет
		new_node->data = value; // сохраняем пользовательские данные
		if ( m_last != nullptr )
		  m_last->next = new_node;
		else
			m_first = new_node;

		m_last = new_node; // обновляем указатель на последний
		m_size += 1; // обновляем размер
	}

	Node * Iterator( size_t ind ) {
		size_t count = m_size - 1;
		Node * current = m_last;

		if ( ind > count / 2 ) {
			while ( count > ind ) {
				if (current != nullptr) {
					current = current->prev;
				}
				else
					break;
				count--;
			}
		}
		else {
			current = m_first;
			count = 0;
			while ( count < ind ) {
				if ( current != nullptr ) {
					current = current->next;
				}
				else
					break;
				count++;
			}
		}
	
		return current;
	}

	 T & operator[] ( size_t ind )  {
		 Node * current = Iterator( ind );

		 if ( current != nullptr )
			 return current->data;
		else 
			return *new T();
	
	};


	bool erase( int pos )
	{
	
		if ( pos >= m_size || pos < 0 )
		{
			// invalid position
			std::cout << "out of range";
			return false;
		}
		
		Node * current = Iterator( pos );

 		if ( current != nullptr ) {
		  Node * prevNode = current->prev;
		  Node * nextNode = current->next;
			if ( prevNode != nullptr ) 
			  prevNode->next = nextNode;
			if ( nextNode != nullptr) {
			  nextNode->prev = prevNode;
				if ( pos == 0 )
					m_first = nextNode;
			}
      delete current;
			m_size -= 1;
		}

		return true;

	}

	bool insert( size_t pos, const T& value ) {
		if ( pos > m_size || pos < 0 ) {
			// invalid position
			std::cout << "out of range";
			return false;
		}
		
		if ( pos == m_size ) {
			push_back( value );
			return true;
		}
	
		Node * current = Iterator( pos );

		if ( current != nullptr ) {
			Node * prevNode = current->prev;
			Node * new_node = new Node{}; // создание нового узла
	    new_node->data = value; // сохраняем пользовательские данные
      new_node->next = current; // следующего элемента пока нет
      current->prev= new_node;
			new_node->prev = prevNode; // предыдущим элементом станет последний		
			if ( pos == 0 )
				m_first = new_node;
		  if ( prevNode != nullptr )
			  prevNode->next = new_node;	
			m_size += 1;	
		}

		return true;
	}

	size_t size() const { return m_size; }

private:
	Node * m_last;
	Node * m_first;
	size_t m_size;
};
