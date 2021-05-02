#include "rsa.h"

int main() {
	srand(time(NULL));
	string message;
	vector<int> messageVector1;
	vector<char> messageVector2;
	vector<ull> messageBlks;
	vector<int> recoverMessage;

	rsa encryption1;

	cout << "Enter message: ";
	getline(cin, message);

	for (int i = 0; i < message.length(); i++)       
	{
		messageVector2.push_back((message[i]));
		if (message[i] != ' ') {
			messageVector1.push_back(int(message[i] - 65));
		}
		else {
			messageVector1.push_back(26);
		}
	}

	std::cout << "Message:              ";
	encryption1.displayChar(messageVector2, 1);                                                                   
	std::cout << std::endl;

	std::cout << "Number values:         ";                                                             
	encryption1.displayInt(messageVector1, 1);
	std::cout << std::endl;

	if (messageVector1.size() % 2 == 0) {
		for (std::vector<int>::iterator it = messageVector1.begin(); it != messageVector1.end(); it = it + 2)  // converting numbers into message blocks
		{
			messageBlks.push_back(*it * 100 + (*(it + 1)));
		}
	}
	else {
		std::vector<int>::iterator it = messageVector1.begin();
		for (it; it != messageVector1.end() - 1; it = it + 2)
		{
			messageBlks.push_back(*it * 100 + (*(it + 1)));
		}
		messageBlks.push_back(*it * 100);
	}

	cout << "Message Blocks:        ";                                                            // displaying message blocks
	encryption1.displayULL(messageBlks, 1);
	std::cout << std::endl;

	unsigned long nthRandPrime1 = 1000 + (std::rand() % (2000 - 1000 + 1));                            // a random number between 1000 and 2000
	unsigned long nthRandPrime2 = 1000 + (std::rand() % (2000 - 1000 + 1));                            // a random number between 1000 and 2000

	unsigned long p = encryption1.kthPrime(nthRandPrime1);                                                         // using the random number to get the nth prime
	unsigned long q = encryption1.kthPrime(nthRandPrime2);                                                         // using the random number to get the nth prime

	std::cout << "p (a random prime):    " << p << std::endl;                                          // printing the nth prime p
	std::cout << "q (a random prime):    " << q << std::endl;                                          // printing the nth prime q

	unsigned long long n = p * q;                                                                      // calculating n = p * q

	unsigned long long totient = (p - 1) * (q - 1);                                                      // calculating phi = (p - 1) * (q - 1)

	unsigned long long e_coPrime = encryption1.kthPrime(std::rand() % totient);                                    // calculating e which is a prime between 1 and phi

	unsigned long long d = encryption1.modInverse(e_coPrime, totient);                                             // calculating modular multiplicative inverse using e and phi

	std::cout << "Public Key  (e , n):   (" << e_coPrime << " , " << n << " )" << std::endl;           // printing public key generated
	std::cout << "Private Key (d , n):   (" << d << " , " << n << " ) " << std::endl;                  // printing private key generated

	std::vector<unsigned long long> encryptedMsg = encryption1.encrypt_decrypt(messageBlks, n, e_coPrime);           // encrypting the message using message blocks, n and e

	std::cout << "Encrypted Message:     ";                                                            // displaying the encrypted message
	encryption1.displayULL(encryptedMsg, 1);
	std::cout << std::endl;

	std::vector<unsigned long long> decryptedMsg = encryption1.encrypt_decrypt(encryptedMsg, n, d);               // decrypting the message using the encrypted numbers, n and d

	std::cout << "Decrypted Message:     ";                                                           // displaying the decrypted message
	encryption1.displayULL(decryptedMsg, 1);
	std::cout << std::endl;

	if (messageVector1.size() % 2 == 0) {                                                                // breaking message blocks into smaller number values to be converted into characters
		for (std::vector<unsigned long long>::iterator it = decryptedMsg.begin(); it != decryptedMsg.end(); it = it + 1)
		{
			if (*it > 99)
			{
				recoverMessage.push_back(*it / 100);
				recoverMessage.push_back(*it % 100);
			}

			else if (*it < 99 && *it % 100 != 0)
			{
				recoverMessage.push_back(0);
				recoverMessage.push_back(*it % 100);
			}

			else {
				recoverMessage.push_back(*it);
			}
		}
	}

	else {
		std::vector<unsigned long long>::iterator it = decryptedMsg.begin();
		for (it; it != decryptedMsg.end() - 1; it = it + 1)
		{
			if (*it > 99)
			{
				recoverMessage.push_back(*it / 100);
				recoverMessage.push_back(*it % 100);
			}

			else if (*it < 99 && *it % 100 != 0)
			{
				recoverMessage.push_back(0);
				recoverMessage.push_back(*it % 100);
			}

			else {
				recoverMessage.push_back(*it);
			}
		}

		recoverMessage.push_back(*it / 100);
	}

	std::cout << "Number values:         ";                                                            // displaying the number values
	encryption1.displayInt(recoverMessage, 1);
	std::cout << std::endl;

	std::cout << "Message:               ";
	for (std::vector<int>::iterator it = recoverMessage.begin(); it != recoverMessage.end(); ++it)
	{
		if (char(*it + 65) != '[') {
			std::cout << "'" << char(*it + 65) << "'" << " ";
		}
		else {
			std::cout << "'" << " " << "'" << " ";
		}
	}
	std::cout << std::endl;

	return 0;
}