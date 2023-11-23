//------------------------------------------------------------------------------
// std_sort_example.cpp
// 
// -demos call to std::sort() with array and vector
//------------------------------------------------------------------------------

#include <algorithm>		// std::sort
#include <iostream>			// std::cout
#include <vector>			// std::vector

// C++ provides a function name macro, with different names on Windows and *nix
#ifndef __FUNCTION_NAME__
	#ifdef _WIN32   //WINDOWS
		#define __FUNCTION_NAME__   __FUNCTION__  
	#else          //*NIX
		#define __FUNCTION_NAME__   __func__ 
	#endif
#endif

using namespace std;

//------------------------------------------------------------------------------
// local functions
//------------------------------------------------------------------------------
// With an array parameter, caller must also pass the number of elements.
void sort_int_array(int ia[], int num_elements);

// With a vector parameter, caller only needs to pass the vector by reference.
// If the vector is passed by value, changes (like a sort) will not survive
// the function call.

void sort_char_vector(vector<char> vc);
void display_array_elements(int ia[], int num_elements, const char*, const string&);
void display_vector_elements(vector<char>& vc, const char*, const string&);

//------------------------------------------------------------------------------
// entry point
//------------------------------------------------------------------------------
int main() {

	// array sort demo

	int intArray[] = { 35, 10, 93, 85, 62, 77, 345, 43, 2, 10 };
	int num_elements = sizeof(intArray) / sizeof(intArray[0]);

	display_array_elements(intArray, num_elements, __FUNCTION_NAME__, "(): array before sort");
	
	// pass starting array address in memory and how many elements
	sort_int_array(intArray, num_elements);

	display_array_elements(intArray, num_elements, __FUNCTION_NAME__, "(): array after sort");

	// vector sort demo

	vector<char> charVector = { 't', 'o', 'y', ' ', 'b', 'o', 'a', 't' };

	display_vector_elements(charVector, __FUNCTION_NAME__, "(): vector before sort");
	sort_char_vector(charVector);
	display_vector_elements(charVector, __FUNCTION_NAME__, "(): vector after sort");

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

	// Here, std::sort() needs to know 2 things:
	//		1) the starting memory address of the first element 
	//		2) the ending address of the last element plus one

	display_array_elements(ia, num_elements,
		__FUNCTION_NAME__, "(): array before sort");

	sort(ia, ia + num_elements);

	display_array_elements(ia, num_elements, 
		__FUNCTION_NAME__, "(): array after sort");
}

//------------------------------------------------------------------------------
// sort passed vector of chars
//------------------------------------------------------------------------------
void sort_char_vector(vector<char> vc) {

	// We know the passed vector's size inside this function,
	// and much more, because a vector carries its own information with it.

	display_vector_elements(vc, __FUNCTION_NAME__, "(): vector before sort");
	
	// sort() needs to know where the first element and last elements are
	// in memory. Easy - just use the vector's begin() and end().

	sort(vc.begin(), vc.end());

	display_vector_elements(vc, __FUNCTION_NAME__, "(): vector after sort");
}

//------------------------------------------------------------------------------
// display elements of passed array of int
//------------------------------------------------------------------------------
void display_array_elements(int ia[], int num_elements, 
	const char* func_name, const string& debug_msg) {

	cout << func_name << debug_msg << "\n\n";

	for (int i = 0; i < num_elements; i++)
		cout << ia[i] << " ";

	cout << '\n';
}

//------------------------------------------------------------------------------
// display elements of passed vector of chars
//------------------------------------------------------------------------------
void display_vector_elements(vector<char>& vc, 
	const char* func_name, const string& debug_msg) {

	cout << func_name << debug_msg << "\n\n";

	for (char ch : vc)
		cout << ch;

	cout << '\n' << '\n';
}