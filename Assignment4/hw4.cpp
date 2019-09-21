/* @Author
Student Name: Ahmet Semih Uçan
Student ID	: 150160014
Date		: 8.12.2018 */

#include <fstream>
#include <iostream>

using namespace std;

struct Node_ant {
    int ant_num;
    Node_ant* next;
};

struct queueAnt {
    Node_ant* front;
    Node_ant* back;
    void create();
    void enqueue(int);
    int dequeue();
    bool isempty();
};

struct stackAnt {
    Node_ant* head;
    void create();
    void push(int);
    int pop();
    bool isempty();
};

struct Ants {
    queueAnt ants;
    queueAnt holeDepths;
    stackAnt hole;
    void ReadFile(char*);
    void ShowContents(bool dec);
    void CrossRoad();
};

void queueAnt::create()
{
    front = NULL;
    back = NULL;
}

void queueAnt::enqueue(int ant)
{
    Node_ant* add_ant = new Node_ant;
    add_ant->ant_num = ant;
    add_ant->next = NULL;

    if (isempty()) {
        front = add_ant;
        back = add_ant;
    } else {
        back->next = add_ant;
        back = add_ant;
    }
}

int queueAnt::dequeue()
{
    Node_ant* tmp = new Node_ant;
    int ant;

    tmp = front;
    ant = tmp->ant_num;
    front = front->next;
    delete tmp;

    return ant;
}

bool queueAnt::isempty()
{
    return front == NULL;
}

void stackAnt::create()
{
    head = NULL;
}

void stackAnt::push(int ant)
{
    Node_ant* newant = new Node_ant;
    newant->ant_num = ant;

    if (isempty()) {
        head = newant;
        newant->next = NULL;
    } else {
        newant->next = head;
        head = newant;
    }
}

int stackAnt::pop()
{
    int ant;
    Node_ant* top = new Node_ant;
    top = head;
    head = head->next;
    ant = top->ant_num;
    delete top;

    return ant;
}

bool stackAnt::isempty()
{
    return head == NULL;
}

void Ants::ReadFile(char* file_name)
{
    ifstream input_file;
    input_file.open(file_name);

    int ant;

    input_file >> ant;

    ants.create();
    for (int i = 1; i <= ant; i++) {
        ants.enqueue(i);
    }

    int hole;

    holeDepths.create();

    while (input_file >> hole) {
        holeDepths.enqueue(hole);
    }
}

void Ants::ShowContents(bool decision)
{
    Node_ant* tmp;

    if (decision) { 	//decision 1 gelince
        tmp = ants.front;
    } else { 			//decision 0 gelince holedepths printle
        tmp = holeDepths.front;
    }

    while (tmp != NULL) {
        cout << tmp->ant_num << " ";

        tmp = tmp->next;
    }

    cout << endl;
}

void Ants::CrossRoad()
{
    int currentHole;

    while (holeDepths.front != NULL) {
        currentHole = holeDepths.dequeue();

        for (int i = 0; i < currentHole; i++) {
            hole.push(ants.dequeue());
        }
        for (int i = 0; i < currentHole; i++) {
            ants.enqueue(hole.pop());
        }
    }
}

int main(int argc, char** argv)
{
    Ants a;
    a.ReadFile(argv[1]); // store the number of ants and depths of holes
    cout << "The initial Ant sequence is: ";
    a.ShowContents(1); // list ant sequence ( initially : 1, 2, ... , N)

    cout << "The depth of holes are: ";
    a.ShowContents(0); // list depth of holes

    a.CrossRoad();
    cout << "The final Ant sequence is: ";
    a.ShowContents(1);

    return 0;
}
