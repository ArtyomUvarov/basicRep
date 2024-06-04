#pragma once
#include <iostream>

template <typename T>
class ListContainer
{
public:
	struct Node {
		Node * next; // ��������� �� ��������� ������� Node
		Node * prev; // ��������� �� ���������� ������� Node
		T data; // ���������������� ������ (�������� ������)
	};

	ListContainer() : m_last{ nullptr }, m_size{ 0 } {}
	 
	void push_back( const T & value ) {
 		Node * new_node = new Node{}; // �������� ������ ����
		new_node->prev = m_last; // ���������� ��������� ������ ���������
		new_node->next = nullptr; // ���������� �������� ���� ���
		new_node->data = value; // ��������� ���������������� ������
		if ( m_last != nullptr )
		  m_last->next = new_node;
		m_last = new_node; // ��������� ��������� �� ���������
		m_size += 1; // ��������� ������
	}

	 T & operator[] ( size_t ind )  {
		size_t count = m_size-1;
		T * currentData = nullptr;
		Node * current_last = m_last;

		while( count >= ind ) {
			if ( current_last != nullptr ) {
				currentData = &current_last->data;
				current_last = current_last->prev;
			}
			else
				break;
			count--;
		}

		if ( currentData != nullptr )
  	  return *currentData;
		else 
			return *new T();
	
	};


	bool erase( int pos )
	{
		int arrayInd = pos - 1;

		if ( arrayInd >= m_size || arrayInd < 0 )
		{
			// invalid position
			return false;
		}

		size_t count = m_size - 1;
		T currentData;
		Node * current_last = m_last;

		while ( count > arrayInd )
		{
			if ( current_last != nullptr ) {
				currentData = current_last->data;
				current_last = current_last->prev;
			}
			else 
				break;
			count--;
		}

 		if ( current_last != nullptr ) {
		  Node * prevNode = current_last->prev;
		  Node * nextNode = current_last->next;
			if ( prevNode != nullptr && nextNode != nullptr ) {
			prevNode->next = nextNode;
			nextNode->prev = prevNode;
			delete current_last;
			m_size -= 1;
			}
		}
		return true;

	}

	bool insert( size_t pos, const T& value ) {
		if ( pos > m_size || pos < 0 )
			// invalid position
			return false;
		
		if ( pos == m_size ) {
			push_back( value );
			return true;
		}

		size_t count = m_size - 1;
		T currentData;
		Node * current_last = m_last;

		while ( count > pos )
		{
			if (current_last != nullptr) {
				currentData = current_last->data;
				current_last = current_last->prev;
			}
			else
				break;
			count--;
		}

		if ( current_last != nullptr ) {
			Node * prevNode = current_last->prev;
			Node * new_node = new Node{}; // �������� ������ ����
	    new_node->data = value; // ��������� ���������������� ������
      new_node->next = current_last; // ���������� �������� ���� ���
      current_last->prev= new_node;
			new_node->prev = prevNode; // ���������� ��������� ������ ���������		
		  if ( prevNode != nullptr )
			  prevNode->next = new_node;	
			m_size += 1;	
		}

		return true;
	}

	size_t size() const { return m_size; }

private:
	Node * m_last;
	size_t m_size;
};
