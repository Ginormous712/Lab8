#include <iostream>
#include "BlockEncrypting.h"
#include <vector>
#include <cassert>
#include <map>
#include <iomanip>

//#define 

using namespace std;
int main()
{
    
    string text = ("Block encryption algorithm using the substitution technique. encryption of the word n in the alphabet with the usual order of letters is performed as follows:");
    vector<int > alpha = { 1,2,3,4 };
    int k = 4;
    
    BlockEncryptingText Example(text, k, alpha, false, false);
    cout << "*********************************************\n";
    cout << "Original text:\n" << text << endl;
    cout << "*********************************************\n";
    cout << "Spliting text into blocks:\n";
    Example.splitText();
    cout << Example.getText() << endl;
    cout << "*********************************************\n";
    cout << "Encrypting text:\n";
    Example.blockEncrypt();
    cout << Example.getText() << endl;
    cout << "*********************************************\n";
    cout << "Decrypting text:\n";
    Example.blockDecrypt();
    cout << Example.getText() << endl;
    cout << "*********************************************\n";
    cout << "Combining text from blocks:\n";
    Example.combineText();
    cout << Example.getText() << endl;
    

}