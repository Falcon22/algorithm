Implement a data structure which implements vector semantics with O(log N) time for get(), set(), add(), remove()

You should implement the following methods:


/* Java example (method names and semantics came from java.util.List,
 you can use method names you like) */

add(Object obj)
add(int index, Object obj)
remove(int index)
set(int index, Object obj)
get(int index)

// C++ example (not really std::vector naming,
// but trying to express desired semantics
// you can use names from Java-example or whatever you like)

push_back(const T&)
insert(int index, const T&)
remove(int index)
set(int index, const T&)
T at(int index)
Every of these operations should have O(log N) complexity.
