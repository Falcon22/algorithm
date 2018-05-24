Implement a data structure which implements vector semantics with O(log N) time for get(), set(), add(), remove()

You should implement the following methods:


<div>/* Java example (method names and semantics came from java.util.List,
 you can use method names you like) */
</div>

<div>add(Object obj)</div>
<div>add(int index, Object obj)</div>
<div>remove(int index)</div>
<div>set(int index, Object obj)</div>
<div>get(int index)</div>

</div>// C++ example (not really std::vector naming,
// but trying to express desired semantics
// you can use names from Java-example or whatever you like)
</div>
<div>push_back(const T&)</div>
<div>insert(int index, const T&)</div>
<div>remove(int index)</div>
<div>set(int index, const T&)</div>
<div>T at(int index)</div>
<div>Every of these operations should have O(log N) complexity.</div>
