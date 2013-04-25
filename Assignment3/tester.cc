/*
 * This is a tester similar to the tester written in class.  It reads
 * words from a text file, then adds the words to two sets: A built-in
 * set class, and our utah_set class.  After reading the file, it
 * prints out all the words stored in the STL set object.  At the end
 * of the test, it prints out the sizes of both sets to see that they
 * are the same.
 *
 * After the test completes, I make sure the local variabls are properly
 * cleaned up.
 *
 * If the comments wrap lines, widen your emacs window.
 *
 * Peter Jensen
 * January 17, 2013
 */

#include <iostream>
#include <fstream>
#include <set>
#include <iterator>
#include "utah_set.h"
#include "node.h"

using namespace std;

int main ()
{
  // Open up another block.  This way, when the block ends,
  // variables local to the block will be destroyed, but main
  // will still be running.  (Did you know that you can open
  // up a block at any time to control local variable scope and
  // lifetime?)

  cout << "Get Elements Tests" << endl;
  cout << "-----------------------------------" << endl;
  {
    string testName = "Get Elements 1";
    cs3505::utah_set words(1); 
    words.add("this");
    words.add("is");
    words.add("a");
    words.add("test");
    string *e = new string[words.size()]; 
    words.get_elements(e, words.size());
    string s = "";

    for(int i = 0; i < 4; i++)
    {
      s += e[i];
    }

    if(s != "thisisatest")
      cout << testName << " failed" << "expected: thisisatest actual: " << s << endl;
    else
      cout << testName << " passed" << endl;
  }

  {
    string testName = "Get Elements 2";
    cs3505::utah_set words(1); 
    words.add("this");
    words.add("is");
    words.add("a");
    words.add("test");
    string *e = new string[words.size()]; 
    words.get_elements(e, 2);

    string s = "";
    for(int i = 0; i < 4; i++)
    {
      s += e[i];
    }

    if(s != "thisis")
      cout << testName << " failed" << "expected: thisis actual: " << s << endl;
    else
      cout << testName << " passed" << endl;
  }

  {
    string testName = "Get Elements 3";
    cs3505::utah_set words(1); 
    words.add("this");
    words.add("is");
    words.add("a");
    words.add("test");
    string *e = new string[9]; 
    words.get_elements(e, 9);

    string s = "";
    for(int i = 0; i < 9; i++)
    {
      s += e[i];
    }

    if(s != "thisisatest")
      cout << testName << " failed" << "expected: thisisatest actual: " << s << endl;
    else
      cout << testName << " passed" << endl;
  }

  cout << "" << endl;
  cout << "Remove Tests" << endl;
  cout << "-----------------------------------" << endl;
  {
    string testName = "Remove 1";
    cs3505::utah_set words(1); 
    words.add("this");
    words.add("is");
    words.add("a");
    words.add("test"); 
    words.remove("this");
    if(words.size() != 3)
      cout << testName << " failed" << endl;
    else
      cout << testName << " passed" << endl;
  }

  {
    string testName = "Remove 2";
    cs3505::utah_set words(1);
    words.add("this");
    words.add("is");
    words.add("a");
    words.add("test"); 
    words.remove("test");
    if(words.contains("test"))
      cout << testName << " failed" << endl;
    else
      cout << testName << " passed" << endl;
  }

  {
    string testName = "Remove 3";
    cs3505::utah_set words(1);  // Our set class, with a hashtable of 1000 slots.
    words.add("this");
    words.add("is");
    words.add("a");
    words.add("test");
    words.add("here");
    words.add("are");
    words.add("more");
    words.add("words"); 
    words.remove("this");
    words.remove("words");
    words.remove("test");
    string *e = new string[words.size()]; 
    words.get_elements(e, words.size());

    string s = "";
    for(int i = 0; i < 5; i++)
    {
      s += e[i];
    }

    if(s != "isaherearemore")
      cout << testName << " failed" << "expected: isaherearemore actual: " << s << endl;
    else
      cout << testName << " passed" << endl;
  }

  {
    string testName = "Remove 4";
    cs3505::utah_set words(1); 
    words.add("this");
    words.add("is");
    words.add("a");
    words.add("test");
    words.remove("happy");

    if(words.size() != 4)
      cout << testName << " failed" << endl;
    else
      cout << testName << " passed" << endl;
  }  

  cout << "" << endl;
  cout << "Operator = Tests" << endl;
  cout << "-----------------------------------" << endl;
  {
    string testName = "Operator = 1";
    cs3505::utah_set words(1);
    cs3505::utah_set copied(1);
    words.add("this");   
    copied = words;
    words.remove("this");  

    if(copied.size() != 1)
      cout << testName << " failed" << endl;
    else
      cout << testName << " passed" << endl;
  }

  {
    string testName = "Operator = 2";
    cs3505::utah_set words(1);
    cs3505::utah_set copied(1);
    words.add("this");   
    copied = words;
    words.remove("this"); 
    string *e = new string[copied.size()];
    copied.get_elements(e, copied.size()); 

    if(e[0] != "this")
      cout << testName << " failed" << endl;
    else
      cout << testName << " passed" << endl;
  }

  cout << "" << endl;
  cout << "Peter's Tests";
  
  {
    // Create the two sets.  Declaring the local variables constructs the objects.
  
    set<string>      stl_set_of_words;  // The built-in set class - no constructor parameters.

    cs3505::utah_set our_set_of_words(1000);  // Our set class, with a hashtable of 1000 slots.
  
    // Open the file stream for reading.  (We'll be able to use it just like
    //   the keyboard stream 'cin'.)

    ifstream in("Yankee.txt");

    // Loop for reading the file.  Note that it is controlled
    //   from within the loop (see the 'break').
    
    while (true)
    {
      // Read a word (don't worry about punctuation)
      
      string word;
      in >> word;

      // If the read failed, we're probably at end of file
      //   (or else the disk went bad).  Exit the loop.
      
      if (in.fail())
	break;

      // Word successfully read.  Add it to both sets.
      
      stl_set_of_words.insert(word);
      our_set_of_words.add(word);
    }

    // Close the file.

    in.close();

    // Print out the words found in the STL set.  I do this to show
    //   students how to get at the entries in an STL object.  For
    //   more examples, look up 'STL iterator examples'.
    // Notice that the iterator object 'it' acts like a pointer, but
    //   it is not a pointer.  (Bad, bad, bad design choice, but not mine!)
    // Feel free to comment this out.
  
    for (set<string>::iterator it = stl_set_of_words.begin(); it != stl_set_of_words.end(); it++)
    {
      string s = *it;
      //cout << s << endl;
    }

    // Print out the number of words found in each set.

    cout << endl;
    cout << "STL set contains " << stl_set_of_words.size() << " unique words.\n";
    cout << "Our set contains " << our_set_of_words.size() << " unique words.\n";
    cout << endl;

    // Done.  Notice that this code block ends below.  Any local
    // variables declared within this block will be automatically
    // destroyed.  Local objects will have their destructors
    // called.

  }

  // Now that the objects have been destroyed, I will simply call my auditing
  // code to print out how many times constructors have been called, and
  // how many times destructors have been called.  They should exactly match.
  // If not, we have a memory problem.

  cout << "Class cs3505::utah_set:" << endl;
  cout << "    Objects created:  " << cs3505::utah_set::constructor_count() << endl;
  cout << "    Objects deleted:  " << cs3505::utah_set::destructor_count() << endl;
  cout << endl;

  cout << "Class cs3505::node:" << endl;
  cout << "    Objects created:  " << cs3505::node::constructor_count() << endl;
  cout << "    Objects deleted:  " << cs3505::node::destructor_count() << endl;
  cout << endl;

  // Now we're really done.  End main.
  
  return 0;
}
