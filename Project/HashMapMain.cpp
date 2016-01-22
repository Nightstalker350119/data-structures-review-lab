// HashMapMain.cpp - the entry point of the hash map application
// Code by Cromwell D. Enage, December 2008
// Updated by Jeremiah Blanchard, January 2009
// Updated by Cromwell D. Enage, July 2009
#include <limits>
#include <string>
#include <complex>
#include <utility>
#include <iostream>
#include <cassert>
#include "Structures/HashMap.h"

using namespace std;

// Prototypes (allow implementation to follow main)
template <typename K, typename V>
void traverse(HashMap<K,V> const& hashMap);

typedef pair<pair<int,int>,pair<int,pair<int,int> > > KeyOfFiveInts;
KeyOfFiveInts createKeyOfFiveInts(int n1, int n2, int n3, int n4, int n5);
void testSearchAndRemove(HashMap<complex<int>,string>& complexMap, complex<int> const& key);
void testSearchAndRemove(HashMap<KeyOfFiveInts,char const*>& kfiMap, KeyOfFiveInts const& key);

int main()
{
	// Get ready.
	HashMap<complex<int>,string> complexMap(7);
	HashMap<KeyOfFiveInts,char const*> kfiMap(11);

	// Test insertion.
	unsigned int pairCount = 16;
	complex<int> complex9plus10i(9,10);
	KeyOfFiveInts key01234 = createKeyOfFiveInts(0, 1, 2, 3, 4);

	char const* testStrings[] =
	{
	    "kilo"
	  , "lima"
	  , "mike"
	  , "november"
	  , "oscar"
	  , "papa"
	  , "quebec"
	  , "romeo"
	  , "sierra"
	  , "tango"
	  , "uniform"
	  , "victor"
	  , "whiskey"
	  , "x-ray"
	  , "yankee"
	  , "zulu"
	};
	complex<int> complexKeys[] =
	{
	    complex<int>(0,3)
	  , complex<int>(6,0)
	  , complex<int>(9,9)
	  , complex<int>(2,1)
	  , complex<int>(4,2)
	  , complex<int>(7,4)
	  , complex<int>(2,3)
	  , complex<int>(1,4)
	  , complex<int>(3,2)
	  , complex<int>(6,4)
	  , complex<int>(5,4)
	  , complex<int>(4,1)
	  , complex<int>(7,3)
	  , complex<int>(10,8)
	  , complex<int>(7,6)
	  , complex<int>(10,9)
	};
	KeyOfFiveInts keysOfFiveInts[] =
	{
	    createKeyOfFiveInts(2, 3, 5, 7, 11)
	  , createKeyOfFiveInts(13, 17, 19, 23, 29)
	  , createKeyOfFiveInts(31, 37, 41, 43, 47)
	  , createKeyOfFiveInts(53, 59, 61, 67, 71)
	  , createKeyOfFiveInts(73, 79, 83, 89, 97)
	  , createKeyOfFiveInts(101, 103, 107, 109, 113)
	  , createKeyOfFiveInts(127, 131, 137, 139, 149)
	  , createKeyOfFiveInts(151, 157, 163, 167, 173)
	  , createKeyOfFiveInts(179, 181, 191, 193, 197)
	  , createKeyOfFiveInts(199, 211, 521, 607, 1279)
	  , createKeyOfFiveInts(1093, 2203, 2281, 3217, 3511)
	  , createKeyOfFiveInts(4253, 4423, 8191, 9689, 9941)
	  , createKeyOfFiveInts(11213, 19937, 21701, 23209, 44497)
	  , createKeyOfFiveInts(86243, 110503, 131071, 132049, 216091)
	  , createKeyOfFiveInts(524287, 756839, 859433, 1257787, 1398269)
	  , createKeyOfFiveInts(2976221, 3021377, 6972593, 13466917, 2147483647)
	};

	// Insert pairs into maps (including duplicates).
	for (unsigned int index = 0; index < pairCount; ++index)
	{
		complexMap[complexKeys[index]] = string(testStrings[index]);
		kfiMap[keysOfFiveInts[index]] = testStrings[index];
	}

	cout << "complexMap:" << endl;
	traverse(complexMap);
	cout << "kfiMap:" << endl;
	traverse(kfiMap);
	cout << endl << "Press ENTER to continue..." << endl << endl;
	cin.ignore((numeric_limits<streamsize>::max)(), '\n');

	// Test insertion with a NULL value.
	cout << "Testing insertion with a NULL value..." << endl;
	testSearchAndRemove(complexMap, complex9plus10i);
	cout << "complexMap:" << endl;
	traverse(complexMap);
	testSearchAndRemove(kfiMap, key01234);
	cout << "kfiMap:" << endl;
	traverse(kfiMap);
	cout << endl << "Press ENTER to continue..." << endl << endl;
	cin.ignore((numeric_limits<streamsize>::max)(), '\n');

	// Test insertion over an existing key.
	char const* replacement = "victoria";
	cout << "Testing replacement of value (victor -> victoria):" << endl;
	complexMap[complexKeys[11]] = string(replacement);
	cout << "complexMap:" << endl;
	traverse(complexMap);
	kfiMap[keysOfFiveInts[11]] = replacement;
	cout << "kfiMap:" << endl;
	traverse(kfiMap);
	cout << endl << "Press ENTER to continue..." << endl << endl;
	cin.ignore((numeric_limits<streamsize>::max)(), '\n');

	// Test search and removal of the only element in a bucket.
	cout << "Testing search and removal of the only element in a bucket..." << endl;
	testSearchAndRemove(complexMap, complexKeys[2]);
	cout << "complexMap:" << endl;
	traverse(complexMap);
	testSearchAndRemove(kfiMap, keysOfFiveInts[1]);
	cout << "kfiMap:" << endl;
	traverse(kfiMap);
	cout << endl << "Press ENTER to continue..." << endl << endl;
	cin.ignore((numeric_limits<streamsize>::max)(), '\n');

	// Test search and removal of the first element in a bucket.
	cout << "Testing search and removal of the first element in a bucket..." << endl;
	testSearchAndRemove(complexMap, complexKeys[0]);
	cout << "complexMap:" << endl;
	traverse(complexMap);
	testSearchAndRemove(kfiMap, keysOfFiveInts[5]);
	cout << "kfiMap:" << endl;
	traverse(kfiMap);
	cout << endl << "Press ENTER to continue..." << endl << endl;
	cin.ignore((numeric_limits<streamsize>::max)(), '\n');

	// Test search and removal of a middle element in a bucket.
	cout << "Testing search and removal of a middle element in a bucket..." << endl;
	testSearchAndRemove(complexMap, complexKeys[10]);
	cout << "complexMap:" << endl;
	traverse(complexMap);
	testSearchAndRemove(kfiMap, keysOfFiveInts[14]);
	cout << "kfiMap:" << endl;
	traverse(kfiMap);
	cout << endl << "Press ENTER to continue..." << endl << endl;
	cin.ignore((numeric_limits<streamsize>::max)(), '\n');

	// Test search and removal of the last element in a bucket.
	cout << "Testing search and removal of the last element in a bucket..." << endl;
	testSearchAndRemove(complexMap, complexKeys[14]);
	cout << "complexMap:" << endl;
	traverse(complexMap);
	testSearchAndRemove(kfiMap, keysOfFiveInts[12]);
	cout << "kfiMap:" << endl;
	traverse(kfiMap);
	cout << endl << "Press ENTER to continue..." << endl;
	cin.ignore((numeric_limits<streamsize>::max)(), '\n');

	return 0;
}

KeyOfFiveInts createKeyOfFiveInts(int n1, int n2, int n3, int n4, int n5)
{
	return make_pair(make_pair(n1, n2), make_pair(n3, make_pair(n4, n5)));
}

void printKeyValuePair(KeyOfFiveInts const& key, char const* value)
{
	cout << "\tkey = (" << key.first.first << ", " << key.first.second << ", " << key.second.first;
	cout << ", " << key.second.second.first << ", " << key.second.second.second << "); value = ";
	cout << (value ? value : "NULL") << endl;
}

void printKeyValuePair(complex<int> const& key, string const& value)
{
	cout << "\tkey = (" << key.real() << ", " << key.imag() << "); value = ";
	cout << (value.empty() ? "{0}" : value) << endl;
}

template <typename K, typename V>
void traverse(HashMap<K,V> const& hashMap)
{
	unsigned int current_bucket = (numeric_limits<unsigned int>::max)();
	typename HashMap<K,V>::Iterator itr = hashMap.begin();
	typename HashMap<K,V>::Iterator itr_end = hashMap.end();

	if (itr != itr_end)
	{
		// Test iterator pre-increment operator return value.
		assert((&(++itr) == &itr) && "Your iterator\'s pre-increment operator is not returning the right object!");
	}

	for (itr = hashMap.begin(); itr != itr_end; ++itr)
	{
		if (itr.getCurrentBucket() != current_bucket)
		{
			cout << "    bucket " << (current_bucket = itr.getCurrentBucket()) << ':' << endl;
		}

		printKeyValuePair((*itr).key, itr->value);
	}
}

void testSearchAndRemove(HashMap<complex<int>,string>& complexMap, complex<int> const& key)
{
	cout << "Testing search and remove:";

	string const& value = complexMap[key];

	if (value.empty())
	{
		cout << "\tkey not found.  Inserting with default value..." << endl;
	}
	else
	{
		printKeyValuePair(key, value);
		complexMap.remove(key);
		complexMap.remove(key);
	}
}

void testSearchAndRemove(HashMap<KeyOfFiveInts,char const*>& kfiMap, KeyOfFiveInts const& key)
{
	cout << "Testing search and remove:";

	char const* value = kfiMap[key];

	if (value)
	{
		printKeyValuePair(key, value);
		kfiMap.remove(key);
		kfiMap.remove(key);
	}
	else
	{
		cout << "\tkey not found.  Inserting with default value..." << endl;
	}
}

