add_executable( benchmark_generate_tree tree.cpp )
target_link_libraries( benchmark_generate_tree ${Boost_PROGRAM_OPTIONS_LIBRARY_RELEASE} )
set_target_properties( benchmark_generate_tree PROPERTIES OUTPUT_NAME "tree" )

add_executable( benchmark_generate_event event.cpp )
target_link_libraries( benchmark_generate_event ${Boost_PROGRAM_OPTIONS_LIBRARY_RELEASE} )
set_target_properties( benchmark_generate_event PROPERTIES OUTPUT_NAME "event" )
