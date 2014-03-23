add_executable( benchmark_parse parse.cpp )
target_link_libraries( benchmark_parse ${Boost_PROGRAM_OPTIONS_LIBRARY_RELEASE} )
set_target_properties( benchmark_parse PROPERTIES OUTPUT_NAME "parse" )

