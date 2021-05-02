#ifndef RSA_H_
#define RSA_H

#include <iostream>
#include <string>
#include <vector>
#include <ctime>

#define ull unsigned long long
#define ll long long

using namespace std;

class rsa {
public:
	bool isPrime(int n);
	int gcd(int, int, int*, int*);
	int modInverse(int, int);
	int kthPrime(int);
	ull emod(ull, ull, ull);
	vector<ull> encrypt_decrypt(vector<ull> , ull, ull);

	void displayInt(vector<int>, int);
	void displayChar(vector<char>, int);
	void displayULL(vector<ull>, int);


};

#endif // !RSA_H_

