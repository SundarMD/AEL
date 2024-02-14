#include <iostream>
#include <vector>

// Function to generate the Hamming code for a 4-bit input
std::vector<int> encodeHamming(std::vector<int>& dataBits) {
    std::vector<int> hammingCode(7);
    // Parity bits calculation
    hammingCode[0] = dataBits[0] ^ dataBits[1] ^ dataBits[3];
    hammingCode[1] = dataBits[0] ^ dataBits[2] ^ dataBits[3];
    hammingCode[2] = dataBits[0];
    hammingCode[3] = dataBits[1] ^ dataBits[2] ^ dataBits[3];
    hammingCode[4] = dataBits[1];
    hammingCode[5] = dataBits[2];
    hammingCode[6] = dataBits[3];

    return hammingCode;
}

// Function to check for errors in the received Hamming code
int checkError(std::vector<int>& hammingCode) {
    // Error position calculation
    int errorPos = 0;
    errorPos += (hammingCode[0] ^ hammingCode[2] ^ hammingCode[4] ^ hammingCode[6]) * 1;
    errorPos += (hammingCode[1] ^ hammingCode[2] ^ hammingCode[5] ^ hammingCode[6]) * 2;
    errorPos += (hammingCode[3] ^ hammingCode[4] ^ hammingCode[5] ^ hammingCode[6]) * 4;

    return errorPos; // Returns 0 if no error, or the position (1-7) of the single-bit error
}

int main() {
    // Example data bits
    std::vector<int> dataBits = {1, 0, 1, 1}; // The original 4 bits of data to encode

    std::vector<int> hammingCode = encodeHamming(dataBits);
    std::cout << "Encoded Hamming code: ";
    for (int bit : hammingCode) std::cout << bit;
    std::cout << std::endl;

    // Introduce an error in the Hamming code for demonstration
    hammingCode[2] = !hammingCode[2]; // Introducing an error

    int errorPos = checkError(hammingCode);
    if (errorPos == 0) {
        std::cout << "No error detected." << std::endl;
    } else {
        std::cout << "Error detected at position: " << errorPos << std::endl;
    }

    return 0;
}
