// C++ program for implementation of Aho Corasick algorithm
// for string matching
// Source: http://www.geeksforgeeks.org/how-to-prepare-for-acm-icpc/
using namespace std;
#include <iostream>
#include <string>
#include <queue>
#include <cstring>

/*
// Version 1: C style, with comments

// Max number of states in the matching machine.
// Should be equal to the sum of the length of all keywords.
const int MAXS = 500;

// Maximum number of characters in input alphabet
const int MAXC = 26;

// OUTPUT FUNCTION IS IMPLEMENTED USING out[]
// Bit i in this mask is one if the word with index i
// appears when the machine enters this state.
int out[MAXS];

// FAILURE FUNCTION IS IMPLEMENTED USING f[]
int f[MAXS];

// GOTO FUNCTION (OR TRIE) IS IMPLEMENTED USING g[][]
int g[MAXS][MAXC];

// Builds the string matching machine.
// arr -   array of words. The index of each keyword is important:
//         "out[state] & (1 << i)" is > 0 if we just found word[i]
//         in the text.
// Returns the number of states that the built machine has.
// States are numbered 0 up to the return value - 1, inclusive.
int buildMatchingMachine(string arr[], int k)
{
	// Initialize all values in output function as 0.
	memset(out, 0, sizeof out);

	// Initialize all values in goto function as -1.
	memset(g, -1, sizeof g);

	// Initially, we just have the 0 state
	int states = 1;

	// Construct values for goto function, i.e., fill g[][]
	// This is same as building a Trie for arr[]
	for (int i = 0; i < k; ++i)
	{
		const string &word = arr[i];
		int currentState = 0;

		// Insert all characters of current word in arr[]
		for (int j = 0; j < word.size(); ++j)
		{
			int ch = word[j] - 'a';

			// Allocate a new node (create a new state) if a
			// node for ch doesn't exist.
			if (g[currentState][ch] == -1)
				g[currentState][ch] = states++;

			currentState = g[currentState][ch];
		}

		// Add current word in output function
		out[currentState] |= (1 << i);
	}

	// For all characters which don't have an edge from
	// root (or state 0) in Trie, add a goto edge to state
	// 0 itself
	for (int ch = 0; ch < MAXC; ++ch)
		if (g[0][ch] == -1)
			g[0][ch] = 0;

	// Now, let's build the failure function

	// Initialize values in fail function
	memset(f, -1, sizeof f);

	// Failure function is computed in breadth first order
	// using a queue
	queue<int> q;

	// Iterate over every possible input
	for (int ch = 0; ch < MAXC; ++ch)
	{
		// All nodes of depth 1 have failure function value
		// as 0. For example, in above diagram we move to 0
		// from states 1 and 3.
		if (g[0][ch] != 0)
		{
			f[g[0][ch]] = 0;
			q.push(g[0][ch]);
		}
	}

	// Now queue has states 1 and 3
	while (q.size())
	{
		// Remove the front state from queue
		int state = q.front();
		q.pop();

		// For the removed state, find failure function for
		// all those characters for which goto function is
		// not defined.
		for (int ch = 0; ch <= MAXC; ++ch)
		{
			// If goto function is defined for character 'ch'
			// and 'state'
			if (g[state][ch] != -1)
			{
				// Find failure state of removed state
				int failure = f[state];

				// Find the deepest node labeled by proper
				// suffix of string from root to current
				// state.
				while (g[failure][ch] == -1)
					failure = f[failure];

				failure = g[failure][ch];
				f[g[state][ch]] = failure;

				// Merge output values
				out[g[state][ch]] |= out[failure];

				// Insert the next level node (of Trie) in Queue
				q.push(g[state][ch]);
			}
		}
	}

	return states;
}

// Returns the next state the machine will transition to using goto
// and failure functions.
// currentState - The current state of the machine. Must be between
//                0 and the number of states - 1, inclusive.
// nextInput - The next character that enters into the machine.
int findNextState(int currentState, char nextInput)
{
	int answer = currentState;
	int ch = nextInput - 'a';

	// If goto is not defined, use failure function
	while (g[answer][ch] == -1)
		answer = f[answer];

	return g[answer][ch];
}

// This function finds all occurrences of all array words
// in text.
void searchWords(string arr[], int k, string text)
{
	// Preprocess patterns.
	// Build machine with goto, failure and output functions
	buildMatchingMachine(arr, k);

	// Initialize current state
	int currentState = 0;

	// Traverse the text through the nuilt machine to find
	// all occurrences of words in arr[]
	for (int i = 0; i < text.size(); ++i)
	{
		currentState = findNextState(currentState, text[i]);

		// If match not found, move to next state
		if (out[currentState] == 0)
			continue;

		// Match found, print all matching words of arr[]
		// using output function.
		for (int j = 0; j < k; ++j)
		{
			if (out[currentState] & (1 << j))
			{
				cout << "Word " << arr[j] << " appears from "
					<< i - arr[j].size() + 1 << " to " << i << endl;
			}
		}
	}
}

// Driver program to test above
int main()
{
	string arr[] = { "he", "she", "hers", "his" };
	string text = "ahishers";
	int k = sizeof(arr) / sizeof(arr[0]);

	searchWords(arr, k, text);

	return 0;
}
*/

/*
// Version 2
// Shorter

const int MAXS = 500; // Max number of states: sum of lengths of patterns
const int MAXC = 26; // Maximum number of characters in input alphabet
int out[MAXS]; // output function. i-th bit of out[j] on => i-th pattern found at index j
int f[MAXS], g[MAXS][MAXC]; // Failure and goto functions

int buildMatchingMachine(vector<string> arr){ // arr -> patterns
	int k = arr.size(), states = 1; // Only state 0
	memset(out, 0, sizeof out);	memset(g, -1, sizeof g);
	for (int i = 0; i < k; ++i)	{ // Fill g, o , ie, build trie
		const string &word = arr[i];
		int currentState = 0;
		for (int j = 0; j < word.size(); ++j) {
			int ch = word[j] - 'a'; // Change if not only chars in [a,...,z]
			if (g[currentState][ch] == -1)
				g[currentState][ch] = states++;
			currentState = g[currentState][ch];
		}
		out[currentState] |= (1 << i); // Add word in output function
	}
	for (int ch = 0; ch < MAXC; ++ch) { // Special case with initial state
		if (g[0][ch] == -1)
			g[0][ch] = 0;
	}
	memset(f, -1, sizeof f);
	queue<int> q; // We fill failure function with a BFS
	for (int ch = 0; ch < MAXC; ++ch) { // Consider every possible input
		if (g[0][ch] != 0) { // depth = 1 => failure = 0
			f[g[0][ch]] = 0;
			q.push(g[0][ch]);
		}
	}
	while (q.size()) {
		int state = q.front(); q.pop();
		for (int ch = 0; ch <= MAXC; ++ch) {
			if (g[state][ch] != -1)	{
				int failure = f[state];
				while (g[failure][ch] == -1)
					failure = f[failure];
				failure = g[failure][ch];
				f[g[state][ch]] = failure;
				out[g[state][ch]] |= out[failure]; // Merge output values
				q.push(g[state][ch]);
			}
		}
	}
	return states; // Number of states in the automaton
}

int findNextState(int currentState, char nextInput){ // Transitions in automaton
	int answer = currentState;
	int ch = nextInput - 'a';
	while (g[answer][ch] == -1)
		answer = f[answer];
	return g[answer][ch];
}

// Find patterns (arr) in a line (text)
void searchWords(vector<string> arr, string text){
	buildMatchingMachine(arr); // Preprocess
	int currentState = 0;
	for (int i = 0; i < text.size(); ++i){
		currentState = findNextState(currentState, text[i]);		
		if (out[currentState] == 0) // If match not found, move to next state
			continue;
		for (int j = 0; j < arr.size(); ++j){ // Match found
			if (out[currentState] & (1 << j)) // i-th bit on => i-th word match
				cout << "Word " << arr[j] << " appears from " << i - arr[j].size() + 1 << " to " << i << endl;
		}
	}
}

// Driver program to test above
int main()
{
	vector<string> arr = { "he", "she", "hers", "his" };
	string text = "ahishers";
	int k = sizeof(arr) / sizeof(arr[0]);

	searchWords(arr, text);

	return 0;
}
*/


// Version 3
// without C arrays
#include <unordered_map>
//#include <boost/functional/hash.hpp>
typedef pair<int, int> ii;

const int MAXC = 26; // Size of input alphabet
unordered_map<int, int> out, f; // i-th bit of out[j] on => i-th pattern found at index j
struct myhash {
	template <typename T, typename U>
	size_t operator()(const std::pair<T, U> &x) const	{
		return hash<T>()(x.first) ^ hash<U>()(x.second); // xor, for instance
	} };
unordered_map<ii, int, myhash> g;

int buildMatchingMachine(vector<string> const & arr){//patterns
	int k = arr.size(), states = 1; // Only state 0
	for (int i = 0; i < k; ++i) { // Fill g, o , i.e., build trie
		const string &word = arr[i];
		int currentState = 0;
		for (int j = 0; j < word.size(); ++j) {
			int ch = word[j] - 'a';//Change if not only chars in [a, ,z]
			if (g.find(ii(currentState, ch)) == g.end())
				g[ii(currentState,ch)] = states++;
			currentState = g[ii(currentState, ch)];
		}
		if (out.find(currentState) == out.end()) out[currentState] = 0;
		out[currentState] |= (1 << i); // Add to output
	}
	queue<int> q; // We fill failure function with a BFS
	for (int ch = 0; ch < MAXC; ++ch) { 
		if (g.find(ii(0, ch)) == g.end()) // Initial state: special
			g[ii(0, ch)] = 0;
		else { // depth = 1 => failure = 0
			f[g[ii(0, ch)]] = 0;
			q.push(g[ii(0, ch)]);
		}
	}
	while (q.size()) {
		int state = q.front(); q.pop();
		for (int ch = 0; ch <= MAXC; ++ch) {
			if (g.find(ii(state,ch)) != g.end()) {
				int failure = f[state];
				while (g.find(ii(failure,ch)) == g.end())
					failure = f[failure];
				failure = g[ii(failure, ch)];
				f[g[ii(state,ch)]] = failure;
				out[g[ii(state, ch)]] |= out[failure]; // Merge outputs
				q.push(g[ii(state, ch)]);
			}
		}
	}
	return states; // Number of states in the automaton
}

int findNextState(int currentState, char nextInput) { 
	int answer = currentState;
	int ch = nextInput - 'a';
	while (g.find(ii(answer, ch)) == g.end())
		answer = f[answer];
	return g[ii(answer,ch)];
}

// Find patterns (arr) in a line (text)
void searchWords(vector<string> arr, string text) {
	buildMatchingMachine(arr); // Preprocess
	int currentState = 0;
	for (int i = 0; i < text.size(); ++i) {
		currentState = findNextState(currentState, text[i]);
		if (out[currentState] != 0) // Match found
			for (int j = 0; j < arr.size(); ++j) 
				if (out[currentState] & (1 << j)) {
					//Word arr[j] appears from i - arr[j].size() + 1 to i
				}
	}
}

// Driver program to test above
int main()
{
	vector<string> arr = { "he", "she", "hers", "his" };
	string text = "ahishers";
	int k = sizeof(arr) / sizeof(arr[0]);

	searchWords(arr, text);

	return 0;
}
