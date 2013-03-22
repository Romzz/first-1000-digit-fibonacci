#include <iostream>
using namespace std;

struct bigNumber
{
    int digit;
    int count;
    bigNumber* next;
    bigNumber* prev;
};

class fibonacTerm : private bigNumber
{
private:
    bigNumber* firstDigit;
    bigNumber* lastDigit;
public:
    fibonacTerm()
    {
        firstDigit = NULL;
        lastDigit  = NULL;
    }
    fibonacTerm(int x);
    ~fibonacTerm();
    void addBack(int x);
    int addCount();
    void carryNum();
    int getCount();
    void operator += (fibonacTerm & f2);
    void print();
};

fibonacTerm::fibonacTerm(int x)
{
    bigNumber* newDigit  = new bigNumber;
    newDigit->digit      = x;
    newDigit->count      = 1;            //Establish first node with count one.
    newDigit->next       = NULL;
    firstDigit           = newDigit;
    firstDigit->prev     = NULL;
}

fibonacTerm::~fibonacTerm()
{
    bigNumber* temp;// = firstDigit->next;
    while(firstDigit != NULL)
    {
        temp = firstDigit;
        firstDigit = firstDigit->next;
//DEBUG        cout << "deleting count " << temp->count << endl;
        delete temp;
    }
}

void fibonacTerm::addBack(int x)
{
    if(firstDigit == NULL)
    {
        cout << "Sequence empty!\n";
        return;
    }
    bigNumber* newDigit = new bigNumber;
    newDigit->digit = x;
    newDigit->next = NULL;
    bigNumber* temp1 = firstDigit;
    bigNumber* temp2 = temp1->next;
    while(temp2 != NULL)
    {
        temp1 = temp2;
        temp2 = temp2->next;
    }
    temp1->next      = newDigit;
    newDigit->prev   = temp1;
    firstDigit->prev = newDigit;
    newDigit->count  = temp1->count+1;
}

void fibonacTerm::carryNum()
{
    int carry = 0;
    bigNumber* current = firstDigit;
    while (current != NULL)
    {
        if( 9 < current->digit )          //Need to carry
        {
            if( NULL == current->next )   //Last element, need to add a node
            {
               this->addBack(current->digit/10);
               current->digit = (current->digit) % 10;
           }
           else
           {
               int div        = current->digit;
               carry          = div/10;
               current->digit = (current->digit)%10;
               current->next->digit += carry;
           }
        }
    current = current->next;
    }
    delete current;                     //Delete temp pointer
}

int fibonacTerm::getCount()
{
    int count;
    bigNumber* current = firstDigit;
    while(current != NULL)
    {
        count   = current->count;
        current = current->next;
    }
    delete current;                    //Delete temp pointer
    return count;
}

void fibonacTerm::operator += (fibonacTerm & f2)
{
    bigNumber* current1 = this->firstDigit;
    bigNumber* current2 = f2.firstDigit;
    while( (current2 != NULL)  )
    {
        current1->digit += current2->digit;
        if (NULL == current1->next && NULL != current2->next)
            this->addBack(0);
        current1 = current1->next;
        current2 = current2->next;
    }
    delete current1;                    //Delete temp pointerss
    delete current2;
}

void fibonacTerm::print()
{
    bigNumber* current = firstDigit->prev;
    int tmpCount = current->count;
    do
    {
        cout << current->digit;
        current = current->prev;
    }  while(current->count != tmpCount);
    cout << endl;
}

int secondary()
{
    int numDigits = 1;
    fibonacTerm termOne(1);
    fibonacTerm termTwo(0);
    cout << "Generating Fibonacci sequence. Enter the number of digits desired to\n";
    cout << "get the first term with that many digits: ";
    cin >> numDigits;
    for(int i = 2; ; i++)     //Starting from the second term
    {
        termTwo += termOne;
        termTwo.carryNum();
        if(numDigits == termTwo.getCount() )
        {
            cout << "\nFirst term with " << numDigits << " terms is the " << i << "th term:\n\n";
            termTwo.print();
            cout << endl;
            break;
        }
        i++;                         // Need to increment the count
        termOne += termTwo;
        termOne.carryNum();
        if(numDigits == termOne.getCount() )
        {
            cout << "\nFirst term with " << numDigits << " terms is the " << i << "th term:\n\n";
            termOne.print();
            cout << endl;
            break;
        }
    }
        return 0;
}
