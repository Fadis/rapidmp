RapidMP
=======

Yet anothoer MessagePack serializer/deserializer for C++

Parsed tree holds string, binary and extension in iterator_range, instead to copy them.

deserialization
---------------

tree = rapidmp::parse_object&lt; &lt;version&gt; &gt;( &lt;input iterator begin&gt;, &lt;input iterator end&gt; )

Note that forward_traversal or successor is required for the input iterator

### available versions

| Version                   | Description                                                                                        |
|---------------------------|:--------------------------------------------------------------------------------------------------:|
| version_1_0               | Assume input is MessagePack 1.0(aka. pre-str MessagePack ). Raw will be mapped to rapidmp::string. |
| version_1_0_raw_as_string | Same as version_1_0                                                                                |
| version_1_0_raw_as_binary | Almost same as version_1_0 but, Raw will be mapped to rapidmp::binary instead to rapidmp::string.                                                                              |
| version_1_1               | Assume input is MessagePack 1.1(aka. post-str MessagePack).                                        |

serialization
-------------

rapidmp::generate_object&lt; &lt;version&gt; &gt;( &lt;output iterator&gt;, tree )

### available versions

| Version                   | Description                                                                                                     |
|---------------------------|:---------------------------------------------------------------------------------------------------------------:|
| version_1_0               | Serialize into MessagePack 1.0(aka. pre-str MessagePack). Both string and binary will be mapped to raw.         |
| version_1_0_raw_as_string | Same as version_1_0                                                                                             |
| version_1_0_raw_as_binary | Same as version_1_0                                                                                             |
| version_1_1               | Serialize using MessagePack 1.1(aka. post-str MessagePack). String and binary will be mapped to different type. |
