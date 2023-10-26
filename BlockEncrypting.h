#pragma once
#include <iostream>
#include <vector>
#include <cassert>
#include <map>
#include <iomanip>

using namespace std;

#define ENCRYPTED 1
#define DECRYPTED 0

class BlockEncryptingText
{
private:
    string text;
    int k;
    vector<int>alpha;
    bool flag;
    static map<char, double> expectedProbabilities;
    bool state;

public:
    
    BlockEncryptingText() : text(""), k(3), alpha((1, 2, 3)), flag(false), state(false)
    {

    }
    BlockEncryptingText(string text, int k, vector<int>&alpha, bool flag, bool state) 
        : text(text), k(k), alpha(alpha), flag(flag), state(state)
    {

    }
    
    string getText()
    {
        return text;
    }

    void setText(string text)
    {
        this->text = text;
    }

    int getK()
    {
        return k;
    }

    void setK(int k)
    {
        this->k = k;
    }

    vector<int> getAlpha()
    {
        return alpha;
    }

    void setAlpha(vector<int> alpha)
    {
        this->alpha = alpha;
    }

    bool getFlag()
    {
        return flag;
    }

    void setFlag(bool flag)
    {
        this->flag = flag;
    }
    static map<char, double> getExpectedProbabilities()
    {
        return expectedProbabilities;
    }

    void blockEncrypt()
    {
        assert(k == alpha.size() && "Size of block isn't equal to 'alpha'\n");
        assert(state == DECRYPTED && "Text is already encrypted!\n");
        string encryptedText;
        size_t point = 0;

        for (size_t i = 0; i < text.length(); i++)
        {
            if (isalpha(text[i]))
            {
                char base = (isupper(text[i])) ? 'A' : 'a';
                encryptedText += static_cast<char>((text[i] - base + alpha[point % k]) % 26 + base);
                point++;
            }
            else if (text[i] == ' ')
            {
                encryptedText += text[i];
            }
            else
            {
                if (flag)
                {
                    encryptedText += text[i];
                }
                else continue;
            }
        }
        state = ENCRYPTED;
        text = encryptedText;
    }

    void blockDecrypt()
    {
        assert(k == alpha.size() && "Size of block isn't equal to 'alpha'\n");
        assert(state == ENCRYPTED && "Text is already decrypted!\n");

        string decryptedText;
        size_t point = 0;

        for (size_t i = 0; i < text.length(); i++)
        {
            if (isalpha(text[i]))
            {
                char base = (isupper(text[i])) ? 'A' : 'a';
                int shiftedValue = (text[i] - base - alpha[point % k] + 26) % 26;
                decryptedText += static_cast<char>(shiftedValue + base);
                point++;
            }
            else
            {
                decryptedText += text[i];
            }
        }
        state = DECRYPTED;
        text = decryptedText;
    }

    void letterProbability()
    {
        map<char, int> letterCount;
        int totalLetters = 0;

        for (char c : text)
        {
            if (isalpha(c))
            {
                letterCount[tolower(c)]++;
                totalLetters++;
            }
        }

        cout << "Letter |   Probability  |   Expected probability\n";
        cout << "-----------------------------------------------------------\n";
        for (char letter = 'a'; letter <= 'z'; letter++)
        {
            int count = letterCount[letter];
            double probability = static_cast<double>(count) / totalLetters;
            double expectedProbability = expectedProbabilities.at(letter);
            cout << "   " << letter << "    |   " << fixed << setprecision(4) << probability << "%   |   " << expectedProbability << "%\n";
        }
    }
    void splitText(char separator)
    {
        string result;
        int charCount = 0;

        for (char c : text)
        {
            if (isalpha(c))
            {
                result += c;
                charCount++;
                if (charCount == k)
                {
                    result += " ";
                    charCount = 0;
                }
            }
            else if (c == ' ')
            {
                result += "*";
            }
            else
            {
                result += c;
            }
        }
        text = result;
    }

    void splitText()
    {
        string result;
        int charCount = 0;

        for (char c : text)
        {
            if (isalpha(c))
            {
                result += c;
                charCount++;
                if (charCount == k)
                {
                    result += " ";
                    charCount = 0;
                }
            }
            else
            {
                continue;
            }
        }
        text = result;
    }

    void combineText(char separator)
    {
        string result;

        for (char c : text)
        {
            if (c == separator)
            {
                result += " ";
            }
            else if (c == ' ')
            {
                continue;
            }
            else
            {
                result += c;
            }
        }
        text = result;
    }

    void combineText()
    {
        string result;

        for (char c : text)
        {
            if (isalpha(c))
            {
                result += c;
            }
            else
            {
                continue;
            }
        }
        text = result;
    }
};

map<char, double> BlockEncryptingText::expectedProbabilities = 
{
    {'a', 0.0817},
    { 'b', 0.0150 },
    { 'c', 0.0278 },
    { 'd', 0.0425 },
    { 'e', 0.1270 },
    { 'f', 0.0223 },
    { 'g', 0.0202 },
    { 'h', 0.0609 },
    { 'i', 0.0697 },
    { 'j', 0.0015 },
    { 'k', 0.0077 },
    { 'l', 0.0403 },
    { 'm', 0.0241 },
    { 'n', 0.0675 },
    { 'o', 0.0751 },
    { 'p', 0.0193 },
    { 'q', 0.0010 },
    { 'r', 0.0599 },
    { 's', 0.0633 },
    { 't', 0.0906 },
    { 'u', 0.0276 },
    { 'v', 0.0098 },
    { 'w', 0.0236 },
    { 'x', 0.0015 },
    { 'y', 0.0197 },
    { 'z', 0.0007 }
};

