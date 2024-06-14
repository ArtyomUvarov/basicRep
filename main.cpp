#include "serial_container.h"
#include"list_container.h"
template <typename T>
void print_container( T& container )
{
	for ( size_t i = 0; i < container.size(); ++i )
	{
		if ( i != 0 )
			std::cout << ' ';
		std::cout << container[i];
	}
}


template <typename T>
void test_conteiner( T& int_container ){
	for (int i = 0; i < 10; ++i)
	int_container.push_back( i );
	print_container( int_container );
	std::cout << std::endl;
	std::cout << int_container.size() << std::endl;
	int_container.erase( 2 );
  int_container.erase( 3 );
  int_container.erase( 4 );
 	print_container( int_container );
	std::cout << std::endl;
	
	int_container.insert( 0, 10 );
	print_container(int_container);
	std::cout << std::endl;
	
	int_container.insert( 4, 20 );
	print_container( int_container );
	std::cout << std::endl;

	int_container.insert( int_container.size(), 30 );
	print_container( int_container );
	std::cout << std::endl;
	
}

int main()
{
	ListContainer<int> int_container;
	//SerialContainer<int> int_container;
	test_conteiner( int_container );

	return 0;
}