#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// auxiliary string to count letters in a given string
const std::string alphabet = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};

// node that contains a value and maybe a letter
struct node {
    int value;
    char letter;
    struct node *left;
    struct node *right;
    
    // constructor
    node(int value, char letter='\0') {
        this->value = value;
        this->letter = letter;
        left = nullptr;
        right = nullptr;
    }
    
    // operator< to sort nodes
    bool operator<(node const& that) const {
        return this->value < that.value;
    }
};

// custom comp function to compare dereferenced nodes
bool comp(node* node1, node* node2) {return node1->value < node2->value;}

std::vector<int> schedulingAlg(std::vector<int> start, std::vector<int> end, int n);
std::vector<std::pair<int, char>> countLetters(const std::string& str);
void huffmanCoding(node* root, std::vector<char>& code);

int main() {
    
    int option;
    
    // declaration of scheduling algorithm variables
    int n;
    std::vector<int> start;
    std::vector<int> end;
    std::vector<int> answer;
    
    // declaration of huffman coding variables
    std::string str;
    std::vector<std::pair<int, char>> n_letters;
    std::vector<node *> nodes;
    std::vector<char> code;
    
    do {
        std::cout << "Choose an option from the menu below:\n"
                     "0) Exit.\n"
                     "1) Scheduling algorithm.\n"
                     "2) Huffman coding.\n";
        
        std::cin >> option;
        
        switch (option) {
    
            // exit
            case 0:
                break;
        
                // scheduling algorithm
            case 1:
                std::cout << "Please enter:\n"
                             "1) The number of events;\n"
                             "2) The start and ending times for each event.\n";
        
                std::cin >> n;
        
                for (int x, y, i = 0; i < n; i++) {
                    std::cin >> x >> y;
                    start.push_back(x);
                    end.push_back(y);
                }
        
                answer = schedulingAlg(start, end, n);
        
                std::cout << "The events chosen are:\n";
                for (int x: answer) {
                    std::cout << x << " ";
                }
                std::cout << std::endl;
        
                // clear everything before next case
                start.clear();
                end.clear();
                answer.clear();
        
                break;
        
            // huffman coding
            case 2:
                std::cin >> str;
        
                n_letters = countLetters(str);
        
                // construct a node for each letter, save reference to each in a vector
                for (auto x: n_letters) {
                    node *new_node = new node(x.first, x.second);
                    nodes.push_back(new_node);
                }
        
                // construct tree
                // iteratively pop the two smaller nodes, make a new node with sum of
                // their values and insert new node in the vector
                while (nodes.size() > 1) {
            
                    node *node1 = nodes.back();
                    nodes.pop_back();
                    node *node2 = nodes.back();
                    nodes.pop_back();
            
                    node *new_node = new node(node1->value + node2->value);
                    new_node->left = node1;
                    new_node->right = node2;
                    nodes.push_back(new_node);
            
                    // sort the vector, so we always get the nodes with the smaller values
                    std::sort(nodes.rbegin(), nodes.rend(), comp);
            
                }
                
                // traverse tree to get the codes
                huffmanCoding(nodes[0], code);
                std::cout << std::endl;
        
                break;
    
            default:
                std::cout << "Invalid option.\n";
        }
    } while (option != 0);
}

// function that receives two vectors representing the starting and ending times
// for a given number of events (n) and returns the greatest possible vector with
// the indexes of events that don't overlap
std::vector<int> schedulingAlg(std::vector<int> start, std::vector<int> end, int n) {
    
    std::vector<int> res;
    
    // get hold of first event index and it's ending time
    int currIndex = 0;
    int currEnd = end[0];
    
    // loop through every other event
    for (int i = 1; i < n; i++) {
        
        // if the next event starts after the current event finishes, save
        // current event and start tracking the next
        if (currEnd <= start[i]) {
            res.push_back(currIndex);
            currIndex = i;
            currEnd = end[i];
        }
        
        // if the next event finishes before current event, then it's best to
        // choose next event instead
        if (end[i] < currEnd) {
            currIndex = i;
            currEnd = end[i];
        }
    }
    res.push_back(currIndex);
    
    return res;
}

// auxiliary function to count the occurrences of letters in a string
// returns a vector with a pair (count, letter) for each letter that appears on the string
std::vector<std::pair<int, char>> countLetters(const std::string& str) {
    
    std::vector<std::pair<int, char>> res;

    for (char a : alphabet) {
        int count = 0;
        for (char l : str) {
            if (toupper(l) == a) {
                count++;
            }
        }
        if (count) {
            res.emplace_back(count, a); // save (count, letter) if it appears on the string
        }
    }
    
    return res;
}

// function that prints the huffman coding for any given string by post order traversal
// must be given a tree built by a specific algorithm
void huffmanCoding(node* root, std::vector<char>& code) {
    
    if (root->letter) {
        std::cout << root->letter << ": ";
        for (char c : code) {
            std::cout << c;
        } std::cout << std::endl;
        return;
    }
    code.push_back('0');
    huffmanCoding(root->left, code);
    code.pop_back();
    code.push_back('1');
    huffmanCoding(root->right, code);
    code.pop_back();
}

/*
scheduling algorithm test cases:

in:
4
1 3
2 5
3 9
6 8

4
1 2
2 3
3 4
4 5

4
1 5
2 3
3 4
4 6


out:
0 3
0 1 2 3
1 2 3

-------------------------
huffman coding test cases:

in:
ab
gabs
gabriel
gabrielcarvalhobergoc
thefiveboxingwizardsjumpquickly
Thispangramlistsfoura's,oneb,onec,twod's,twenty-ninee's,eightf's,threeg's,fiveh's,eleveni's,onej,onek,threel's,twom's,twenty-twon's,fifteeno's,onep,oneq,sevenr's,twenty-sixs's,nineteent's,fouru's,fivev's,ninew's,twox's,foury's,andonez.

out:
B: 0
A: 1

B: 00
A: 01
S: 10
G: 11

A: 00
E: 010
B: 011
I: 100
G: 101
R: 110
L: 111

E: 000
C: 001
L: 010
G: 011
B: 100
A: 101
I: 11000
H: 11001
O: 1101
V: 1110
R: 1111

Q: 0000
O: 00010
P: 00011
U: 0010
T: 00110
F: 00111
L: 01000
N: 01001
E: 0101
I: 011
D: 10000
V: 10001
W: 10010
C: 10011
G: 10100
S: 10101
R: 10110
H: 10111
Z: 11000
Y: 11001
J: 11010
K: 11011
B: 11100
X: 11101
M: 11110
A: 11111

T: 000
R: 0010
K: 001100
M: 001101
A: 00111
N: 010
H: 0110
L: 01110
G: 01111
S: 100
F: 10100
Y: 101010
W: 101011
O: 1011
I: 1100
C: 1101000
D: 1101001
J: 1101010
P: 1101011
V: 110110
B: 1101110
U: 1101111
E: 111
O: 000
Y: 00100
X: 00101
I: 0011
T: 010
F: 0110
U: 01110
R: 01111
M: 100000
Q: 1000010
P: 1000011
V: 10001
W: 1001
N: 101
S: 110
E: 111

*/