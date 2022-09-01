
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <string>
#include <iostream>
#include <time.h>

#include "DBoW2.h"

int main() {
    OrbVocabulary Voc;
    time_t start = clock();
    std::cout << "Start ORB Vocabulary loading!" << std::endl << std::endl;
    bool bVocLoad = Voc.loadFromTextFile("../test/files/ORBvoc.txt");
    if(!bVocLoad)
    {
        std::cerr << "Wrong path to vocabulary. " << std::endl;
    }
    std::cout << "ORB Vocabulary loaded!" << std::endl << std::endl;
    time_t end = clock();
    std::cout << "ORB Vocabulary Processing Time: " << (double)(end-start) / 1e6 << std::endl;
    Voc.saveToTextFile("../test/files/Test_ORBvoc.txt");


    OrbVocabulary2 Voc2;
    start = clock();
    std::cout << "Start ORB2 Vocabulary loading!" << std::endl << std::endl;
    bVocLoad = Voc2.loadFromBinaryFile2("../test/files/Input_ORBvoc.bin");
    if(!bVocLoad)
    {
        std::cerr << "Wrong path to vocabulary. " << std::endl;
    }
    std::cout << "ORB2 Vocabulary loaded!" << std::endl << std::endl;
    end = clock();
    std::cout << "ORB2 Vocabulary Processing Time: " << (double)(end-start) / 1e6 << std::endl;
    Voc2.saveToTextFile("../test/files/Test_ORBvoc2.txt");
    return 0;
}