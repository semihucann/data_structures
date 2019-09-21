/*
Ön kabuller
1- Boþluk girdisi tam belirtilmediði için böyle kabul ettim
./lm english-input.txt u " "
Üstteki kodun çýktýsý u harfinden sonra gelen boþluklarýn toplam u sayýsýna oraný

2- Output örneði olmadýðý için þu þekilde kabul ettim
./lm english-input.txt a b
Output: a-b: "ab/a"

*/
/* @Author
* Student Name	: <Ahmet Semih Uçan>
* Student ID	: <150160014>
* Date			: <1.11.2018> */

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

struct occur_node {
    char character;
    occur_node* next;
    int occurence;
};

struct vocab_node {
    char character;
    vocab_node* next;
    occur_node* list;
};

struct vocab_list {
    int node_number;
    vocab_node* head;
    void create();
    void print();
    void add_char(char x);
    void add_occurence(char a, char b);
    int get_occurence(char c);
    int get_union_occurence(char d, char e);
};

struct language_model {
    vocab_list* vocabularylist;
    void readData(const char*);
    double calculateProbability(char first, char second);
};

void vocab_list::create()
{
    head = NULL;
    node_number = 0;
}

void vocab_list::print()
{

    vocab_node* traverse;
    traverse = head;

    occur_node* listTraverse;

    while (traverse) {
        if (traverse->character == ' ') {
            cout << "<SP>"
                 << ":\n";
        } else {
            cout << traverse->character << ":\n";
        }

        listTraverse = traverse->list;

        while (listTraverse) {
            if (listTraverse->character == ' ') {
                cout << "    <"
                     << "<SP>"
                     << "," << listTraverse->occurence << ">" << endl;
            } else {
                cout << "    <" << listTraverse->character << "," << listTraverse->occurence << ">" << endl;
            }
            listTraverse = listTraverse->next;
        }

        traverse = traverse->next;
    }
}

void vocab_list::add_char(char newChar)
{
    //All chars are lowed
    newChar = tolower(newChar);
    vocab_node* newNode;
    newNode = new vocab_node;
    vocab_node* traverse;
    //NULL is assigned for newnode
    newNode->list = NULL;
    newNode->character = newChar;
    traverse = head;
    if (head == NULL) {
        newNode->next = NULL;
        head = newNode;
    } else {
        //if newchar is letter, newchar will order
        if (newChar < 123 && newChar > 96) {
            if (newChar < traverse->character) {
                newNode->next = head;
                head = newNode;
            } else if (newChar == traverse->character) {
                return;
            } else {
                while (traverse->next && newChar > traverse->next->character && traverse->next->character > 96 && traverse->next->character < 123) {
                    traverse = traverse->next;
                }
                if (traverse->next && newChar == traverse->next->character) {
                    return;
                } else {
                    if (traverse->next) {
                        //Middle of list
                        newNode->next = traverse->next;
                        traverse->next = newNode;
                    } else {
                        //End of list
                        traverse->next = newNode;
                        newNode->next = NULL;
                    }
                }
            }
        } else {
            //newchar is punction
            if (traverse->character == newChar) {
                return;
            }
            while (traverse->next) {
                traverse = traverse->next;
                if (traverse->character == newChar) {
                    return;
                }
            }
            traverse->next = newNode;
            newNode->next = NULL;
        }
    }
    node_number++;
}

void vocab_list::add_occurence(char first, char second)
{
    vocab_node* traverse;
    traverse = head;

    first = tolower(first);
    second = tolower(second);

    occur_node* newOccur;
    newOccur = new occur_node;
    newOccur->character = second;

    occur_node* listTraverse;

    while (traverse) {
        if (first == traverse->character) {
            //Found and search occur node
            listTraverse = traverse->list;

            if (listTraverse == NULL) {
                newOccur->occurence = 1;
                newOccur->next = NULL;
                listTraverse = newOccur;
                traverse->list = newOccur;
            } else {
                //Travel at occur_list
                while (listTraverse->next) {
                    if (listTraverse->character == second) {
                        listTraverse->occurence++;
                        return;
                    }
                    listTraverse = listTraverse->next;
                }
                //Control end of list
                if (listTraverse->next == NULL) {
                    if (listTraverse->character == second) {
                        listTraverse->occurence++;
                        return;
                    } else {
                        listTraverse->next = newOccur;
                        newOccur->occurence = 1;
                        newOccur->next = NULL;
                    }
                }
            }
        }
        traverse = traverse->next;
    }
}

int vocab_list::get_occurence(char myChar)
{
    int total = 0;

    vocab_node* traverse;
    traverse = head;

    occur_node* listTraverse;

    while (traverse) {
        if (myChar == traverse->character) {
            //Found. Add all occurences
            listTraverse = traverse->list;
            while (listTraverse) {
                total += listTraverse->occurence;
                listTraverse = listTraverse->next;
            }
            break;
        } else {
            traverse = traverse->next;
        }
    }

    return total;
}

int vocab_list::get_union_occurence(char first, char second)
{
    int total = 0;

    vocab_node* traverse;
    traverse = head;

    occur_node* listTraverse;

    while (traverse) {
        if (first == traverse->character) {
            //Found.
            listTraverse = traverse->list;
            while (listTraverse) {
                if (listTraverse->character == second) {
                    total = listTraverse->occurence;
                    break;
                }
                listTraverse = listTraverse->next;
            }
            break;
        } else {
            traverse = traverse->next;
        }
    }

    return total;
}

double language_model::calculateProbability(char first, char second)
{
    double result = 0;

    first = tolower(first);
    second = tolower(second);

    result = (double)vocabularylist->get_union_occurence(first, second) / (double)vocabularylist->get_occurence(first);

    return result;
}

void language_model::readData(const char* input_name)
{
    ifstream input;
    input.open(input_name);

    string line;

    //Will fill model
    while (!input.eof()) {
        getline(input, line);

        //Filled vocab_list
        for (int i = 0; i < line.length(); i++) {
            vocabularylist->add_char(line[i]);
        }

        //Filled  occur nodes
        for (int i = 0; i < line.length() - 1; i++) {
            vocabularylist->add_occurence(line[i], line[i + 1]);
        }
        //assume that there is a empty character at end of line 
        char empt=' ';
        vocabularylist->add_occurence(line[line.length()-1],empt);
    }
}

int main(int argc, char* argv[])
{

    language_model myModel;

    vocab_list myList;
    myList.create();

    myModel.vocabularylist = &myList;

    const char* name = argv[1];
    myModel.readData(name);

    //Control parameter
    if (argc == 4) {
        //There are parameter

        cout << setprecision(2) << myModel.calculateProbability(argv[2][0], argv[3][0]);
    } else {
        //There is not parameter
        myList.print();
    }

    return 0;
}
