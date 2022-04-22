/*
 SHA1_Demo.cpp - demo program of
 
 ============
 SHA-1 in C++
 ============
 
 100% Public Domain.
 
 Original C Code
 -- Steve Reid <steve@edmweb.com>
 Small changes to fit into bglibs
 -- Bruce Guenter <bruce@untroubled.org>
 Translation to simpler C++ Code
 -- Volker Grabsch <vog@notjusthosting.com>
 */

#include <string>
#include <iostream>

#include "SHA1.hpp"
#include "SHA1.hpp"

using namespace std;

//int main() {
//
//	char s[] = "Testing SHA-1";
//	string input(s);
//
//	SHA1 checksum;
//	checksum.update(input);
//	char hash[41];
//	strcpy(hash, checksum.final().c_str());
//
//	cout << "The SHA-1 of \"" << input << "\" is: " << hash << endl;
//
//	return 0;
//}
