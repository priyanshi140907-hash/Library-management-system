#include<iostream>
#include<stack>
#include<queue>
using namespace std;

struct Book
{
    int id;
    string title;
    bool issued;
    Book* next;
};

Book* head = NULL;

queue<int> waitingList;
stack<int> returnedBooks;

// Add Book
void addBook()
{
    Book* newBook = new Book;

    cout<<"Enter Book ID: ";
    cin>>newBook->id;

    cout<<"Enter Book Title: ";
    cin.ignore();   // clear buffer
    getline(cin, newBook->title);

    newBook->issued = false;
    newBook->next = NULL;

    if(head == NULL)
        head = newBook;
    else
    {
        Book* temp = head;
        while(temp->next != NULL)
            temp = temp->next;

        temp->next = newBook;
    }

    cout<<"Book Added Successfully\n";
}

// Display Books
void displayBooks()
{
    Book* temp = head;

    if(temp == NULL)
    {
        cout<<"No books in library\n";
        return;
    }

    while(temp != NULL)
    {
        cout<<"ID: "<<temp->id<<" | Title: "<<temp->title;

        if(temp->issued)
            cout<<" | Issued";
        else
            cout<<" | Available";

        cout<<endl;
        temp = temp->next;
    }
}

// Search Book
void searchBook()
{
    int id;
    cout<<"Enter Book ID: ";
    cin>>id;

    Book* temp = head;

    while(temp != NULL)
    {
        if(temp->id == id)
        {
            cout<<"Book Found: "<<temp->title<<endl;
            return;
        }
        temp = temp->next;
    }

    cout<<"Book Not Found\n";
}

// Issue Book
void issueBook()
{
    int id;
    cout<<"Enter Book ID: ";
    cin>>id;

    Book* temp = head;

    while(temp != NULL)
    {
        if(temp->id == id)
        {
            if(!temp->issued)
            {
                temp->issued = true;
                cout<<"Book Issued Successfully\n";
            }
            else
            {
                cout<<"Already Issued! Added to waiting list\n";
                waitingList.push(id);
            }
            return;
        }
        temp = temp->next;
    }

    cout<<"Book Not Found\n";
}

// Return Book
void returnBook()
{
    int id;
    cout<<"Enter Book ID: ";
    cin>>id;

    Book* temp = head;

    while(temp != NULL)
    {
        if(temp->id == id)
        {
            if(temp->issued)
            {
                temp->issued = false;
                returnedBooks.push(id);

                cout<<"Book Returned Successfully\n";

                if(!waitingList.empty())
                {
                    int next = waitingList.front();
                    waitingList.pop();
                    cout<<"Book issued to next user (ID: "<<next<<")\n";
                }
            }
            else
            {
                cout<<"Book was not issued\n";
            }
            return;
        }
        temp = temp->next;
    }

    cout<<"Book Not Found\n";
}

int main()
{
    int choice;

    do
    {
        cout<<"\n--- Library Management System ---\n";
        cout<<"1. Add Book\n";
        cout<<"2. Issue Book\n";
        cout<<"3. Return Book\n";
        cout<<"4. Search Book\n";
        cout<<"5. Display Books\n";
        cout<<"6. Exit\n";

        cout<<"Enter choice: ";
        cin>>choice;

        switch(choice)
        {
            case 1: addBook(); break;
            case 2: issueBook(); break;
            case 3: returnBook(); break;
            case 4: searchBook(); break;
            case 5: displayBooks(); break;
            case 6: cout<<"Exit\n"; break;
            default: cout<<"Invalid choice\n";
        }

    }while(choice != 6);

    return 0;
}
