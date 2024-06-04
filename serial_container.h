#pragma once
#include <iostream>

template <typename T>
class SerialContainer
{
public:
	SerialContainer() : m_region{nullptr},m_size{ 0 } {}

	void push_back( const T & value ) {
		T * new_region = new T[m_size + 1]; // новая область памяти
		for ( size_t i = 0; i < m_size; ++i ) {
			new_region[i] = m_region[i]; // копирование элементов
		}
		new_region[m_size] = value; // добавление нового элемента
		delete[] m_region; // удаление старой области
		m_region = new_region; // сохранение новой в мембер
		m_size += 1; // обновление информации о размере
	}

	const T & operator[] ( size_t ind )  const {
	  return m_region[ind];
	};

	bool erase( int pos )
	{
		
		int arrayInd = pos - 1;
		if ( arrayInd >= m_size || arrayInd < 0 )
		{
			// invalid position
			return false;
		}
		T * new_region = new T[m_size - 1]; // новая область памяти
		size_t k = 0;
		for ( size_t i = 0; i < m_size; ++i ) {
			if ( i != arrayInd )
			new_region[k++] = m_region[i]; // копирование элементов
		}
		delete[] m_region; // удаление старой области
		m_region = new_region; // сохранение новой в мембер
		m_size -= 1; // обновление информации о размере
		return true;
	}


	bool insert( size_t pos, const T& value )
	{

		if ( pos > m_size || pos < 0 )
		{
			// invalid position
			return false;
		}
		T* new_region = new T[m_size + 1]; // новая область памяти
		size_t k = 0;
 		
		for ( size_t i = 0; i < pos; ++i )  		
		  new_region[k++] = m_region[i]; // копирование элементов

		new_region[k++] = value;

		for ( size_t i = pos; i < m_size; ++i )
			new_region[k++] = m_region[i]; // копирование элементов

		delete[] m_region; // удаление старой области
		m_region = new_region; // сохранение новой в мембер
		m_size += 1; // обновление информации о размере
		return true;
	}

	size_t size() const { return m_size; }

private:
	T * m_region;
	size_t m_size;
};