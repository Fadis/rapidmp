add_executable( test_parse parse.cpp )
target_link_libraries( test_parse ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY_RELEASE} )
set_target_properties( test_parse PROPERTIES OUTPUT_NAME "parse" )
add_test( test_parse parse )

add_executable( test_sax sax.cpp )
target_link_libraries( test_sax ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY_RELEASE} )
set_target_properties( test_sax PROPERTIES OUTPUT_NAME "sax" )
add_test( test_sax sax )

add_executable( test_generate generate.cpp )
target_link_libraries( test_generate ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY_RELEASE} )
set_target_properties( test_generate PROPERTIES OUTPUT_NAME "generate" )
add_test( test_generate generate )

