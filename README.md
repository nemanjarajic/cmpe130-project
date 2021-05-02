# Advanced Algorithm Design CMPE 130 Project

To solve the problem of breach of data privacy and insecure communication between two parties,
the RSA(Rivest-Shamir-Aldeman) algorithm will be used, a public key cryptosystem which can
be used to generate public and private keys, digital signatures as well as for encryption,
decryption, and digital signature verification. Encryption and decryption will help provide secure
communication and privacy while digital signatures will help with secure authentication.

### Important values to calculate

Two random prime number p and q, n, phi, e (public key), and d (private key)

p and q are found by generating random numbers p1 & p2 between 500-3000 then the two value are run through the calculatePrime() function to get p1-th and p2-th prime numbers

n is calculated by multiplying p and q

phi is calculated by multiplying (p-1) and (q-1)

e is calculated by generating a random number between 1 - phi then it passed through the calculatePrime() function to get the kth prime number

d is calculated by passing e and phi values through the modeInverse() function

### Important Functions

```
//Fucntion for the extended Euclidean Algorithm to calculate for the greatest common denominator
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

//Modular Exponent
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
```

### Sample of encryption and decryption
![alt_text]('') 
