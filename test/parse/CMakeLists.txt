add_executable( test_parse_event event.cpp )
target_link_libraries( test_parse_event ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY_RELEASE} )
set_target_properties( test_parse_event PROPERTIES OUTPUT_NAME "event" )
add_test( test_parse_event event )

add_executable( test_parse_tree tree.cpp )
target_link_libraries( test_parse_tree ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY_RELEASE} )
set_target_properties( test_parse_tree PROPERTIES OUTPUT_NAME "tree" )
add_test( test_parse_tree tree )

