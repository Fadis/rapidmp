RapidMP
=======

Yet anothoer MessagePack serializer/deserializer for C++

Parsed tree holds string, binary and extension in iterator_range, instead to copy them.

deserialization
---------------

tree = rapidmp::parse_object( &lt;input iterator begin&gt;, &lt;input iterator end&gt; )

Note that forward_traversal or successor is required for the input iterator

serialization
-------------

rapidmp::generate_object( &lt;output iterator&gt;, tree )

