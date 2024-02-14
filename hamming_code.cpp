#include <iostream>
#include <vector>
#include <chrono>

// Function prototypes
std::vector<int> encodeHamming(const std::vector<int>& dataBits);
int checkError(const std::vector<int>& hammingCode);
std::vector<int> checkAndCorrectError(std::vector<int>& hammingCode);

// Function to generate the Hamming code for a 4-bit input
std::vector<int> encodeHamming(const std::vector<int>& dataBits) {
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
int checkError(const std::vector<int>& hammingCode) {
    // Error position calculation
    int errorPos = 0;
    errorPos += (hammingCode[0] ^ hammingCode[2] ^ hammingCode[4] ^ hammingCode[6]) * 1;
    errorPos += (hammingCode[1] ^ hammingCode[2] ^ hammingCode[5] ^ hammingCode[6]) * 2;
    errorPos += (hammingCode[3] ^ hammingCode[4] ^ hammingCode[5] ^ hammingCode[6]) * 4;
    return errorPos; // Returns 0 if no error, or the position (1-7) of the single-bit error
}

// Function to check and correct errors in the received Hamming code
std::vector<int> checkAndCorrectError(std::vector<int>& hammingCode) {
    int errorPos = checkError(hammingCode);
    if (errorPos != 0) {
        // Correct the error. Note that position is 1-based index in the errorPos calculation
        hammingCode[errorPos - 1] ^= 1;
    }
    return hammingCode; // Returns the corrected Hamming code
}

int main() {
    // Example data bits
    std::vector<int> dataBits = {1, 0, 1, 1}; // The original 4 bits of data to encode

    auto start = std::chrono::high_resolution_clock::now();

    // Benchmarking the encoding process
    for (int i = 0; i < 1000000; ++i) {
        std::vector<int> hammingCode = encodeHamming(dataBits);
        hammingCode[2] = !hammingCode[2]; // Introducing an error for correction
        hammingCode = checkAndCorrectError(hammingCode); // Correcting the error
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    std::cout << "Time taken for 1,000,000 encodings and corrections: " << elapsed.count() << " ms\n";

    // Single test for demonstration purposes
    std::vector<int> hammingCode = encodeHamming(dataBits);
    std::cout << "Original Encoded Hamming code: ";
    for (int bit : hammingCode) std::cout << bit;
    std::cout << std::endl;

    // Introduce an error in the Hamming code for demonstration
    hammingCode[2] = !hammingCode[2]; // Introducing an error
    std::cout << "Hamming code with error: ";
    for (int bit : hammingCode) std::cout << bit;
    std::cout << std::endl;

    // Error correction
    std::vector<int> correctedCode = checkAndCorrectError(hammingCode);
    std::cout << "Corrected Hamming code: ";
    for (int bit : correctedCode) std::cout << bit;
    std::cout << std::endl;

    return 0;
}
