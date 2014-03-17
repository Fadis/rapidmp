RapidMP
=======

Yet anothoer MessagePack serializer/deserializer for C++
Parsed tree holds string, binary and extension in iterator_range, instead to copy them.

* deserialization

tree = rapidmp::parse_object( <input iterator begin>, <input iterator end> )

Note that forward_traversal or successor is required for the input iterator

* serialization

rapidmp::generate_object( <output iterator>, tree )

