#include "rsa.h"


//Checks to see whether the given value is prime
//Code retrived from geeksforgeeks.com
bool rsa::isPrime(int val) {

	// Corner cases
	if (val <= 1)
		return false;
	if (val <= 3)
		return true;

	// This is checked so that we can skip
	// middle five numbers in below loop
	if (val % 2 == 0 || val % 3 == 0)
		return false;

	for (int i = 5; i * i <= val; i = i + 6)
		if (val % i == 0 || val % (i + 2) == 0)
			return false;

	return true;
}

//Fucntion for the extended Euclidean Algorithm to calculate for the greatest common denominator
//Code retrived from geeksforgeeks.com
int rsa::gcd(int a, int b, int* x, int* y) {
	
	//Base case
	if (a == 0) {
		*x = 0, * y = 1;
		return b;
	}

	//Stores values of recursive call
	int x1, y1;
	//Recurive call of algorithm
	int g = gcd(b%a,a,&x1,&y1);

	//Update values of x and y with the results of the recursive call
	*x = y1 - (b / a) * x1;
	*y = x1;

	return g;
}

//Modulo Inverse of values a and b
//Code retrived from geeksforgeeks.com
int rsa::modInverse(int a, int b) {
	int x, y;
	int g = gcd(a, b, &x, &y);

	if (g != 1) {
		return -1;
	}
	else {
		//B is added to handle negative x values
		int res = (x % b + b) % b;
		return res;
	}
}

//Determines the kth prime number
int rsa::calculatePrime(int val) {
	int x, count;
	//Loops until the kth prime number is reached
	for (x = 2, count = 0; count < val; x++) {
		if (isPrime(x)) {
			count++;
		}
	}

	return x - 1;
}

//Calculates the modular exponent
//Code retrived from geeksforgeeks.com
ull rsa::emod(ull a, ull b, ull c) {
	if (b == 0) {
		return 1;
	}
	else if (b % 2 == 0) {
		ull d = emod(a, b / 2, c);
		return (d * d) % c;
	}
	else {
		return ((a % c) * emod(a, b - 1, c)) % c;
	}
}

//This function encrypts and decrypts the message vector based on the values inputed to the emod function
vector<ull> rsa::encrypt_decrypt(vector<ull> message, ull nd, ull e) {
	vector<ull> c;

	for (vector<ull>::iterator it = message.begin(); it != message.end(); ++it) {
		ull v = emod(*it,e,nd);
		c.push_back(v);
	}

	return c;
}

//Display vectors holding int values
void rsa::displayInt(vector<int> v, int inc) {
	for (vector<int>::iterator it = v.begin(); it != v.end(); it += inc)
	{
		std::cout << "'" << *it << "'" << " ";
	}
}
//Display vectors holding char values
void rsa::displayChar(vector<char> v, int inc) {
	for (vector<char>::iterator it = v.begin(); it != v.end(); it += inc)
	{
		std::cout << "'" << *it << "'" << " ";
	}
}
//Display vectors holding unsigned long long values
void rsa::displayULL(vector<ull> v, int inc) {
	for (vector<ull>::iterator it = v.begin(); it != v.end(); it += inc)
	{
		std::cout << "'" << *it << "'" << " ";
	}
}