// Read files and prints top k word by frequency

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>
#include <mutex>
#include <thread>
#include <future>
#include <utility>
#include <random>
#include <chrono>


const size_t TOPK = 10;
using Counter = std::map<std::string, std::size_t>;
std::string tolower( const std::string & str );
void count_words( const std::string & filepath, Counter & );
void print_topk( std::ostream & stream, const Counter &, const size_t k );


int main( int argc, char *argv[] ) {
  if ( argc < 2 ) {
    std::cerr << "Usage: topk_words [FILES...]\n";
    return EXIT_FAILURE;
  }
  auto start = std::chrono::high_resolution_clock::now();
  std::vector<Counter> freq_dicts;
  std::vector<std::thread> threads;
  
  for (int i = 1; i < argc; ++i)
    freq_dicts.emplace_back( Counter() );
    
  for (size_t i = 1; i < argc; ++i)
    threads.emplace_back( count_words, argv[i], std::ref(freq_dicts[i-1]) ) ;
            
  bool success = true;

  for ( auto & thread : threads ) {
    try {
      thread.join();
    }
    catch (std::exception & e) {
      std::cerr << "Error: " << e.what() << std::endl;
      success = false;
    }
  }
  
  if ( success ) {
    for ( size_t g = 1; g< freq_dicts.size(); ++g ) 
      for ( auto it = std::cbegin(freq_dicts[g]); it != std::cend(freq_dicts[g]); ++it )
        ++freq_dicts[0][it->first];      
    print_topk( std::cout, freq_dicts[0], TOPK );
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>( end - start );
    std::cout << "Elapsed time is " << elapsed_ms.count() << " us\n";
  }   
}

std::string tolower( const std::string & str ) {
    std::string lower_str;
    std::transform( std::cbegin(str), std::cend(str),
                   std::back_inserter(lower_str),
                   [](unsigned char ch) { return std::tolower(ch);} );
    return lower_str;
};

void count_words( const std::string & filepath, Counter & counter ) {
  std::ifstream stream{ filepath };

  if ( !stream.is_open() ) 
    throw std::runtime_error{ "Failed to open '" + filepath + "'" };
  
  std::for_each( std::istream_iterator<std::string>(stream),
              std::istream_iterator<std::string>(),
              [&counter](const std::string & s) {++counter[tolower(s)];} );
  
}

void print_topk( std::ostream & stream, const Counter & counter, const size_t k ) {
    std::vector<Counter::const_iterator> words;
    words.reserve( counter.size() );

    for ( auto it = std::cbegin(counter); it != std::cend(counter); ++it ) 
        words.push_back( it );

    std::partial_sort(
        std::begin(words), std::begin(words) + k, std::end(words),
        [](auto lhs, auto &rhs) { return lhs->second > rhs->second; });

    std::for_each(
        std::begin(words), std::begin(words) + k,
        [&stream](const Counter::const_iterator &pair) {
            stream << std::setw(4) << pair->second << " " << pair->first
                      << '\n';
        });
}
