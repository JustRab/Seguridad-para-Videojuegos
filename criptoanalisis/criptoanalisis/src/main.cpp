#include "Prerequisites.h"
#include "AsciiBinary.h"
int main()
{
	AsciiBinary aB;

	std::string input = "Hello, World!";
	std::string binaryOutput = aB.stringToBinary(input);
	std::cout << "Binary representation of \"" << input << "\": " << binaryOutput << std::endl;
	std::string message = aB.binaryToString(binaryOutput);
	std::cout << "Converted back to string: \"" << message << "\"" << std::endl;



	return 0;
}