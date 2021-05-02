#include "rsa.h"

int main() {

	srand(time(NULL));

	//initialize variables for message, ASCII representation of the message, int representation of the message
	string message;
	vector<int> messageVector1;
	vector<char> messageVector2;
	vector<ull> messageBlks;
	vector<int> recoverMessage;

	//Initialize the rsa class as encryption1
	rsa encryption1;

	cout << "Enter message: ";
	getline(cin, message);

	//Fill vectors messageVector1 and messageVector2 with the correct values
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

	//Display the vectors
	std::cout << "Message:              ";
	encryption1.displayChar(messageVector2, 1);                                                                   
	std::cout << std::endl;

	std::cout << "Number values:         ";                                                             
	encryption1.displayInt(messageVector1, 1);
	std::cout << std::endl;

	//Converts the values of the int vector to message blocks
	if (messageVector1.size() % 2 == 0) {
		for (std::vector<int>::iterator it = messageVector1.begin(); it != messageVector1.end(); it = it + 2)  
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

	//Displays the message blocks
	cout << "Message Blocks:        ";                                                            
	encryption1.displayULL(messageBlks, 1);
	cout << std::endl;

	//Calculates a random number between 500 and 3000
	ul p1 = (rand() % 2500 + 500);                            
	ul p2 = (rand() % 2500 + 500);                            

	//Calculate the p1-th and p2-th prime numbers for the encryption
	//Prime numbers are generated randomly
	ul p = encryption1.calculatePrime(p1);                                                         
	ul q = encryption1.calculatePrime(p2);                                                         

	//Display prime numbers
	cout << "p (a random prime):    " << p << std::endl;                                          
	cout << "q (a random prime):    " << q << std::endl;                                          

	//Calculates n based of the values of p and q
	ull n = p * q;                                                                      

	//Calculating phi basede off the values of p and q
	ull phi = (p - 1) * (q - 1);                                                      

	//Calculation e by generating a random number between 1 and phi
	ull e = encryption1.calculatePrime(rand() % phi);                                    

	//D is calculated by finding the mod inverse of e and phi
	ull d = encryption1.modInverse(e, phi);                                             

	//Displaying the public and private key generated from the calculations above
	cout << "Public Key  (e , n):   (" << e << " , " << n << " )" << endl;          
	cout << "Private Key (d , n):   (" << d << " , " << n << " ) " << endl;

	//Encyrpts the message based on the values of n and e as well as the content of the message blocks vector
	vector<ull> encryptedMsg = encryption1.encrypt_decrypt(messageBlks, n, e);           

	//Displays the encrpyted vector
	cout << "Encrypted Message:     ";                                                            
	encryption1.displayULL(encryptedMsg, 1);
	cout << std::endl;

	//Send the encrpyted message along with the values n and d for it to be decrypted 
	vector<ull> decryptedMsg = encryption1.encrypt_decrypt(encryptedMsg, n, d);              

	//Displaying the decrypted message
	cout << "Decrypted Message:     ";                                                           
	encryption1.displayULL(decryptedMsg, 1);
	cout << std::endl;

	// Alters the values back to smaller values that can be convert to chars

	if (messageVector1.size() % 2 == 0) {                                                                
		for (vector<ull>::iterator it = decryptedMsg.begin(); it != decryptedMsg.end(); it = it + 1)
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
		vector<ull>::iterator it = decryptedMsg.begin();
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

	//Display the recovered message from the decryption
	cout << "Number values:         ";                                                            
	encryption1.displayInt(recoverMessage, 1);
	cout << std::endl;

	//Converts the recovered message back to chars
	cout << "Message:               ";
	for (vector<int>::iterator it = recoverMessage.begin(); it != recoverMessage.end(); ++it)
	{
		if (char(*it + 65) != '[') {
			cout << "'" << char(*it + 65) << "'" << " ";
		}
		else {
			cout << "'" << " " << "'" << " ";
		}
	}
	cout << endl;

	return 0;
}