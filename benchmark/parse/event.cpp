#include <iterator>
#include <fstream>
#include <chrono>
#include <iostream>
#include <boost/program_options.hpp>
#include <rapidmp/parser/event.hpp>
#include <rapidmp/null_receiver.hpp>

int main( int argc, char *argv[] ) {
  namespace po = boost::program_options;
  po::options_description options("option");
  options.add_options()
    ( "help,h", "show this message" )
    ( "input,i", po::value<std::string>(), "MessagePack file to parse" )
    ( "repeat,n", po::value<size_t>(),  "number of times to parse" );
  po::variables_map args;
  po::store(
    po::parse_command_line( argc, argv, options ),
    args
  );
  po::notify( args );
  if( args.count("help") || !args.count("input") || !args.count("repeat") )
    std::cerr << options << std::endl;
  else {
    std::fstream  file( args[ "input" ].as< std::string >(), std::ios::in|std::ios::binary );
    const std::vector< char > serialized( std::istreambuf_iterator< char >( file.rdbuf() ), std::istreambuf_iterator< char >() );
    const size_t repeat = args[ "repeat" ].as<size_t>();
    rapidmp::null_receiver< std::vector< char >::const_iterator > receiver;
    const auto begin_time = std::chrono::high_resolution_clock::now();
    for( size_t count = 0; count != repeat; ++count ) {
      auto iter = serialized.begin();
      rapidmp::parse_object< rapidmp::version_1_1 >( iter, serialized.end(), receiver );
    }
    const auto end_time = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>( end_time - begin_time ).count() << "msec" << std::endl;
  }
}
