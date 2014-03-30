add_executable( benchmark_parse_event event.cpp )
target_link_libraries( benchmark_parse_event ${Boost_PROGRAM_OPTIONS_LIBRARY_RELEASE} )
set_target_properties( benchmark_parse_event PROPERTIES OUTPUT_NAME "event" )
add_executable( benchmark_parse_tree tree.cpp )
target_link_libraries( benchmark_parse_tree ${Boost_PROGRAM_OPTIONS_LIBRARY_RELEASE} )
set_target_properties( benchmark_parse_tree PROPERTIES OUTPUT_NAME "tree" )
if ( PYTHONLIBS_FOUND )
  add_executable( benchmark_parse_python python.cpp )
  target_link_libraries( benchmark_parse_python
	  ${Boost_PROGRAM_OPTIONS_LIBRARY_RELEASE}
	  ${Boost_PYTHON_LIBRARY_RELEASE} ${PYTHON_LIBRARIES} )
  set_target_properties( benchmark_parse_python PROPERTIES OUTPUT_NAME "python" )
endif()
