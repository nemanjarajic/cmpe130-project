#include "rsa.h"

//StackOverflow help to determine whether a number is prime

bool rsa::isPrime(int val) {
	if (val % 2 == 0) return val == 2;
	if (val % 3 == 0) return val == 3;
	int step = 4;
	int m = (int)pow(val, .5) + 1;

	for (int i = 5; i < m; step = 6 - step, i += step) {
		if (val % i == 0) {
			return false;
		}
	}
	return true;
}

int rsa::gcd(int a, int b, int* x, int* y) {
	if (a == 0) {
		*x = 0, * y = 1;
		return b;
	}

	int x1, y1;

	int g = gcd(b%a,a,&x1,&y1);

	*x = y1 - (b / a) * x1;
	*y = x1;

	return g;
}

int rsa::modInverse(int a, int b) {
	int x, y;
	int g = gcd(a, b, &x, &y);

	if (g != 1) {
		return -1;
	}
	else {
		int res = (x % b + b) % b;
		return res;
	}
}

int rsa::kthPrime(int val) {
	int x, count;
	for (x = 2, count = 0; count < val; x++) {
		if (isPrime(x)) {
			count++;
		}
	}

	return x - 1;
}

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

vector<ull> rsa::encrypt_decrypt(vector<ull> message, ull nd, ull e) {
	vector<ull> c;

	for (vector<unsigned long long>::iterator it = message.begin(); it != message.end(); ++it) {
		ull v = emod(*it,e,nd);
		c.push_back(v);
	}

	return c;
}


void rsa::displayInt(vector<int> v, int inc) {
	for (vector<int>::iterator it = v.begin(); it != v.end(); it += inc)
	{
		std::cout << "'" << *it << "'" << " ";
	}
}

void rsa::displayChar(vector<char> v, int inc) {
	for (vector<char>::iterator it = v.begin(); it != v.end(); it += inc)
	{
		std::cout << "'" << *it << "'" << " ";
	}
}

void rsa::displayULL(vector<ull> v, int inc) {
	for (vector<ull>::iterator it = v.begin(); it != v.end(); it += inc)
	{
		std::cout << "'" << *it << "'" << " ";
	}
}