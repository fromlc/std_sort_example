//------------------------------------------------------------------------------
// std_sort_example.cpp
// 
// -demos call to std::sort() with array and vector
//------------------------------------------------------------------------------

#include <algorithm>		// std::sort
#include <iostream>			// std::cout
#include <vector>			// std::vector

using namespace std;

//------------------------------------------------------------------------------
// local functions
//------------------------------------------------------------------------------
// With an array parameter, caller must also pass the number of elements.
void sort_int_array(int ia[], int num_elements);

// With a vector parameter, caller only needs to pass the vector by reference.
// If the vector is passed by value, changes (like a sort) will not survive
// the function call.

void sort_char_vector(vector<char>& vc);

//------------------------------------------------------------------------------
// entry point
//------------------------------------------------------------------------------
int main() {

	int intArray[] = { 10, 35, 85, 93, 62, 77, 345, 43, 2, 10 };

	// pass starting array address in memory and how many elements
	sort_int_array(intArray, sizeof(intArray) / sizeof(intArray[0]));

	vector<char> charVector = { 't', 'o', 'y', ' ', 'b', 'o', 'a', 't' };
	sort_char_vector(charVector);

	cout << "Type any key to close this window...";

	cin.get();
}

//------------------------------------------------------------------------------
// sort passed array of ints
//------------------------------------------------------------------------------
void sort_int_array(int ia[], int num_elements) {

	// Get number of elements in intArray[], because
	// we need it to call std::sort().
	// 
	// But in this function scope sizeof() won't work!
	// 
	// Inside this function, we're in a different scope than the one
	// where the array was declared. 
	// 
	// In this function's scope:
	//	- we know the type of its elements, and
	//	- we know where it starts in memory (in C++ the value of an array
	//		 parameter is the memory address of the first element)
	//	- BUT we don't know how many bytes were allocated for this array.
	// 
	// The punchline:
	// 
	// On a 64-bit machine sizeof(ia) will always return 8 here,
	// because the int ia[] parameter is a memory address 8 bytes long.
	// We divide that 8 by sizeof(int), so bad_array_size will always be 2.
	// 
	// Notice the compiler warning trying to help us.
	// 
	// #TODO sizeof() for demo only
	int bad_array_size = sizeof(ia) / sizeof(ia[0]);

	cout << "integer array before sorting: ";
	for (int i = 0; i < num_elements; i++)
		cout << ia[i] << " ";

	cout << '\n';

	// Here, std::sort() needs to know at least 2 things:
	// std::sort() needs to know at least 2 things:
	//		1) the starting memory address of the first element 
	//		2) the ending address of the last element plus one
	//		3) 
	sort(ia, ia + num_elements);

	cout << "integer array after sorting:  ";
	for (int i = 0; i < num_elements; i++)
		cout << ia[i] << " ";

	cout << '\n' << '\n';
}

//------------------------------------------------------------------------------
// sort passed vector of chars
//------------------------------------------------------------------------------
void sort_char_vector(vector<char>& vc) {

	// We know the passed vector's size inside this function,
	// and much more, because a vector carries its own information with it.

	cout << "character vector before sorting: ";
	
	// C++ knows how many elements in the passed vector, so 
	// we can use an easy range-based for loop.

	for (char ch : vc)
		cout << ch;

	cout << '\n';

	// sort() needs to know where the first element and last elements are
	// in memory. Easy - just use the vector's begin() and end().

	sort(vc.begin(), vc.end());

	cout << "character vector after sorting:  ";
	for (char ch : vc)
		cout << ch;

	cout << '\n' << '\n';
}