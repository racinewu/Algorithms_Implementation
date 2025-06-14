#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Huffman Tree Node
struct Node
{
    char ch;
    int freq;
    int order;
    Node *left;
    Node *right;

    Node(char character, int frequency, int order)
        : ch(character), freq(frequency), order(order), left(nullptr), right(nullptr) {}

    Node(int frequency)
        : ch(0), freq(frequency), order(-1), left(nullptr), right(nullptr) {}
};

// Comparator for priority queue
struct Compare
{
    bool operator()(Node *a, Node *b)
    {
        if (a->freq == b->freq)
        {
            return a->order > b->order;
        }
        return a->freq > b->freq;
    }
};

class HuffmanCoder
{
private:
    unordered_map<char, string> huffmanTable;
    unordered_map<string, char> reverseTable;
    Node *root;

    unordered_map<char, int> calculateFrequency(const string &text, unordered_map<char, int> &order)
    {
        unordered_map<char, int> freq;
        for (int i = 0; i < text.size(); ++i)
        {
            char ch = text[i];
            freq[ch]++;
            if (order.find(ch) == order.end())
            {
                order[ch] = i;
            }
        }
        return freq;
    }

    // Build Huffman Tree
    Node *buildHuffmanTree(const unordered_map<char, int> &freq, const unordered_map<char, int> &order)
    {
        priority_queue<Node *, vector<Node *>, Compare> pq;

        for (auto &pair : freq)
        {
            char ch = pair.first;
            int f = pair.second;
            int ord = order.at(ch);
            pq.push(new Node(ch, f, ord));
        }

        while (pq.size() > 1)
        {
            Node *right = pq.top();
            pq.pop();
            Node *left = pq.top();
            pq.pop();

            Node *merged = new Node(left->freq + right->freq);
            merged->left = left;
            merged->right = right;

            pq.push(merged);
        }

        return pq.top();
    }

    void generateCodes(Node *node, string code)
    {
        if (!node)
            return;

        if (node->ch != 0)
        {
            huffmanTable[node->ch] = code.empty() ? "0" : code;
            reverseTable[code.empty() ? "0" : code] = node->ch;
            return;
        }

        generateCodes(node->left, code + "0");
        generateCodes(node->right, code + "1");
    }

    string readFile(const string &filename)
    {
        ifstream file(filename);
        if (!file.is_open())
        {
            cerr << "Error: Cannot open file " << filename << endl;
            return "";
        }

        string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        file.close();
        return content;
    }

    void writeFile(const string &filename, const string &content)
    {
        ofstream file(filename);
        if (!file.is_open())
        {
            cerr << "Error: Cannot create file " << filename << endl;
            return;
        }
        file << content;
        file.close();
    }

public:
    HuffmanCoder() : root(nullptr) {}

    // Encoding mode
    void encode(const string &decodedFile, const string &huffTableFile, const string &encodedFile)
    {
        string text = readFile(decodedFile);
        if (text.empty())
        {
            cerr << "Error: Empty or invalid input file" << endl;
            return;
        }

        unordered_map<char, int> order;
        auto freq = calculateFrequency(text, order);
        root = buildHuffmanTree(freq, order);

        huffmanTable.clear();
        reverseTable.clear();
        generateCodes(root, "");

        // Write into Huffman Table
        string tableContent;
        for (auto &pair : huffmanTable)
        {
            string charStr;
            char ch = pair.first;

            switch (ch)
            {
            case '\n':
                charStr = "\\n";
                break;
            case '\t':
                charStr = "\\t";
                break;
            case '\r':
                charStr = "\\r";
                break;
            case '\\':
                charStr = "\\\\";
                break;
            case '\"':
                charStr = "\\\"";
                break;
            case ' ':
                charStr = "SPACE";
                break;
            default:
                if (ch >= 32 && ch <= 126)
                    charStr = string(1, ch);
                else
                    charStr = "ASCII_" + to_string((int)(unsigned char)ch);
                break;
            }

            tableContent += "\"" + charStr + "\" : " + pair.second + "\n";
        }
        writeFile(huffTableFile, tableContent);

        string encodedText;
        for (char ch : text)
        {
            encodedText += huffmanTable[ch];
        }
        writeFile(encodedFile, encodedText);

        cout << "Encoding completed successfully!" << endl;
        cout << "Original size: " << text.length() * 8 << " bits" << endl;
        cout << "Encoded size: " << encodedText.length() << " bits" << endl;
        cout << "Compression ratio: " << (double)encodedText.length() / (text.length() * 8) << endl;
    }

    // Decoding mode
    void decode(const string &huffTableFile, const string &encodedFile, const string &decodedFile)
    {
        ifstream tableFile(huffTableFile);
        if (!tableFile.is_open())
        {
            cerr << "Error: Cannot open huffman table file" << endl;
            return;
        }

        reverseTable.clear();
        string line;
        while (getline(tableFile, line))
        {
            if (line.empty())
                continue;

            // format: "string" : code
            size_t colonPos = line.find(" : ");
            if (colonPos != string::npos)
            {
                string charPart = line.substr(1, colonPos - 2);
                string codePart = line.substr(colonPos + 3);

                char actualChar;
                if (charPart == "\\n")
                {
                    actualChar = '\n';
                }
                else if (charPart == "\\t")
                {
                    actualChar = '\t';
                }
                else if (charPart == "\\r")
                {
                    actualChar = '\r';
                }
                else if (charPart == "\\\\")
                {
                    actualChar = '\\';
                }
                else if (charPart == "\\\"")
                {
                    actualChar = '\"';
                }
                else if (charPart == "SPACE")
                {
                    actualChar = ' ';
                }
                else if (charPart.substr(0, 6) == "ASCII_")
                {
                    int ascii = stoi(charPart.substr(6));
                    actualChar = (char)ascii;
                }
                else if (charPart.length() == 1)
                {
                    actualChar = charPart[0];
                }
                else
                {
                    continue;
                }

                reverseTable[codePart] = actualChar;
            }
        }
        tableFile.close();

        string encodedText = readFile(encodedFile);
        if (encodedText.empty())
        {
            cerr << "Error: Empty or invalid encoded file" << endl;
            return;
        }

        string decodedText;
        string currentCode;

        for (char bit : encodedText)
        {
            currentCode += bit;
            if (reverseTable.find(currentCode) != reverseTable.end())
            {
                decodedText += reverseTable[currentCode];
                currentCode.clear();
            }
        }

        writeFile(decodedFile, decodedText);

        cout << "Decoding completed successfully!" << endl;
        cout << "Decoded text length: " << decodedText.length() << " characters" << endl;
    }
};

int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        cout << "Usage: ./Huffman <mode> <hufftable.txt> <encoded.txt> <decoded.txt>" << endl;
        cout << "Modes:" << endl;
        cout << "  -e : Encode mode (read decoded.txt, write hufftable.txt and encoded.txt)" << endl;
        cout << "  -d : Decode mode (read hufftable.txt and encoded.txt, write decoded.txt)" << endl;
        return 1;
    }

    string mode = argv[1];
    string huffTableFile = argv[2];
    string encodedFile = argv[3];
    string decodedFile = argv[4];

    HuffmanCoder coder;

    if (mode == "-e")
    {
        cout << "Starting encoding process..." << endl;
        coder.encode(decodedFile, huffTableFile, encodedFile);
    }
    else if (mode == "-d")
    {
        cout << "Starting decoding process..." << endl;
        coder.decode(huffTableFile, encodedFile, decodedFile);
    }
    else
    {
        cerr << "Error: Invalid mode. Use -e for encode or -d for decode." << endl;
        return 1;
    }

    return 0;
}