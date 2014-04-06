add_executable( test_generate_tree tree.cpp )
target_link_libraries( test_generate_tree ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY_RELEASE} )
set_target_properties( test_generate_tree PROPERTIES OUTPUT_NAME "tree" )
add_test( test_generate_tree tree )

add_executable( test_generate_event event.cpp )
target_link_libraries( test_generate_event ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY_RELEASE} )
set_target_properties( test_generate_event PROPERTIES OUTPUT_NAME "event" )
add_test( test_generate_event event )

