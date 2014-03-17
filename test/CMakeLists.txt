add_executable( test_parse_uint parse_uint.cpp )
target_link_libraries( test_parse_uint ${Boost_LIBRARIES} )
set_target_properties( test_parse_uint PROPERTIES OUTPUT_NAME "parse_uint" )
add_test( test_parse_uint parse_uint )

add_executable( test_parse_int parse_int.cpp )
target_link_libraries( test_parse_int ${Boost_LIBRARIES} )
set_target_properties( test_parse_int PROPERTIES OUTPUT_NAME "parse_int" )
add_test( test_parse_int parse_int )

add_executable( test_parse_float parse_float.cpp )
target_link_libraries( test_parse_float ${Boost_LIBRARIES} )
set_target_properties( test_parse_float PROPERTIES OUTPUT_NAME "parse_float" )
add_test( test_parse_float parse_float )

add_executable( test_parse_none parse_none.cpp )
target_link_libraries( test_parse_none ${Boost_LIBRARIES} )
set_target_properties( test_parse_none PROPERTIES OUTPUT_NAME "parse_none" )
add_test( test_parse_none parse_none )

add_executable( test_parse_bool parse_bool.cpp )
target_link_libraries( test_parse_bool ${Boost_LIBRARIES} )
set_target_properties( test_parse_bool PROPERTIES OUTPUT_NAME "parse_bool" )
add_test( test_parse_bool parse_bool )

add_executable( test_parse_string parse_string.cpp )
target_link_libraries( test_parse_string ${Boost_LIBRARIES} )
set_target_properties( test_parse_string PROPERTIES OUTPUT_NAME "parse_string" )
add_test( test_parse_string parse_string )

add_executable( test_parse_binary parse_binary.cpp )
target_link_libraries( test_parse_binary ${Boost_LIBRARIES} )
set_target_properties( test_parse_binary PROPERTIES OUTPUT_NAME "parse_binary" )
add_test( test_parse_binary parse_binary )

add_executable( test_parse_extension parse_extension.cpp )
target_link_libraries( test_parse_extension ${Boost_LIBRARIES} )
set_target_properties( test_parse_extension PROPERTIES OUTPUT_NAME "parse_extension" )
add_test( test_parse_extension parse_extension )

add_executable( test_parse_array parse_array.cpp )
target_link_libraries( test_parse_array ${Boost_LIBRARIES} )
set_target_properties( test_parse_array PROPERTIES OUTPUT_NAME "parse_array" )
add_test( test_parse_array parse_array )

add_executable( test_parse_struct parse_struct.cpp )
target_link_libraries( test_parse_struct ${Boost_LIBRARIES} )
set_target_properties( test_parse_struct PROPERTIES OUTPUT_NAME "parse_struct" )
add_test( test_parse_struct parse_struct )

add_executable( test_generate_uint generate_uint.cpp )
target_link_libraries( test_generate_uint ${Boost_LIBRARIES} )
set_target_properties( test_generate_uint PROPERTIES OUTPUT_NAME "generate_uint" )
add_test( test_generate_uint generate_uint )

add_executable( test_generate_int generate_int.cpp )
target_link_libraries( test_generate_int ${Boost_LIBRARIES} )
set_target_properties( test_generate_int PROPERTIES OUTPUT_NAME "generate_int" )
add_test( test_generate_int generate_int )

add_executable( test_generate_float generate_float.cpp )
target_link_libraries( test_generate_float ${Boost_LIBRARIES} )
set_target_properties( test_generate_float PROPERTIES OUTPUT_NAME "generate_float" )
add_test( test_generate_float generate_float )

add_executable( test_generate_none generate_none.cpp )
target_link_libraries( test_generate_none ${Boost_LIBRARIES} )
set_target_properties( test_generate_none PROPERTIES OUTPUT_NAME "generate_none" )
add_test( test_generate_none generate_none )

add_executable( test_generate_bool generate_bool.cpp )
target_link_libraries( test_generate_bool ${Boost_LIBRARIES} )
set_target_properties( test_generate_bool PROPERTIES OUTPUT_NAME "generate_bool" )
add_test( test_generate_bool generate_bool )

add_executable( test_generate_string generate_string.cpp )
target_link_libraries( test_generate_string ${Boost_LIBRARIES} )
set_target_properties( test_generate_string PROPERTIES OUTPUT_NAME "generate_string" )
add_test( test_generate_string generate_string )

add_executable( test_generate_binary generate_binary.cpp )
target_link_libraries( test_generate_binary ${Boost_LIBRARIES} )
set_target_properties( test_generate_binary PROPERTIES OUTPUT_NAME "generate_binary" )
add_test( test_generate_binary generate_binary )

add_executable( test_generate_extension generate_extension.cpp )
target_link_libraries( test_generate_extension ${Boost_LIBRARIES} )
set_target_properties( test_generate_extension PROPERTIES OUTPUT_NAME "generate_extension" )
add_test( test_generate_extension generate_extension )

add_executable( test_generate_array generate_array.cpp )
target_link_libraries( test_generate_array ${Boost_LIBRARIES} )
set_target_properties( test_generate_array PROPERTIES OUTPUT_NAME "generate_array" )
add_test( test_generate_array generate_array )

add_executable( test_generate_struct generate_struct.cpp )
target_link_libraries( test_generate_struct ${Boost_LIBRARIES} )
set_target_properties( test_generate_struct PROPERTIES OUTPUT_NAME "generate_struct" )
add_test( test_generate_struct generate_struct )

