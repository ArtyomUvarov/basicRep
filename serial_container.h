#pragma once
#include <iostream>

template <typename T>
class SerialContainer
{
public:
	SerialContainer() : m_region{nullptr},m_size{0}, m_capacity{0}{}

	void push_back( const T & value ) {

 		if ( m_capacity == 0) 
		{
			m_capacity= m_size / 2 + 1;
			T * new_region = new T[m_size  + m_capacity]; // ����� ������� ������
			for ( size_t i = 0; i < m_size; ++i ) 
				new_region[i] = m_region[i]; // ����������� ���������
   		delete[] m_region; // �������� ������ �������
		  new_region[m_size] = value; // ���������� ������ ��������
		  m_region = new_region; // ���������� ����� � ������
		}
		else 
			m_region[m_size] = value;	
					
		m_size += 1; // ���������� ���������� � �������

		if ( m_capacity > 0 )
		  m_capacity -= 1;
	}

	const T & operator[] ( size_t ind )  const {
	  return m_region[ind];
	};

	bool erase( int pos )
	{
		
		if ( pos >= m_size || pos < 0 )
		{
			// invalid position
			std::cout<<"out of range";
			return false;
		}
		
		for (size_t i = pos; i < m_size - 1; ++i)
			m_region[i]= m_region[i+1];
		
		m_size -= 1; // ���������� ���������� � �������
		m_capacity += 1;
		return true;
	}


	bool insert( size_t pos, const T& value )
	{

		if ( pos > m_size || pos < 0 )
		{
			// invalid position
			std::cout << "out of range";
			return false;
		}
		if ( m_capacity == 0 ) 
		{
			T* new_region = new T[m_size + 1]; // ����� ������� ������
			size_t k = 0;
 		
			for ( size_t i = 0; i < pos; ++i )  		
				new_region[k++] = m_region[i]; // ����������� ���������

			new_region[k++] = value;

			for ( size_t i = pos; i < m_size; ++i )
				new_region[k++] = m_region[i]; // ����������� ���������

			delete[] m_region; // �������� ������ �������
			m_region = new_region; // ���������� ����� � ������
		}
		else {	
			for ( size_t i = m_size; i > pos; --i ){
				m_region[i] = m_region[i-1];
			}
			m_region[pos] = value;
			m_capacity -= 1;
		}
		
		m_size += 1; // ���������� ���������� � �������
		
		return true;
	}

	size_t size() const { return m_size; }

private:
	T * m_region;
	size_t m_size;
	size_t m_capacity;
};