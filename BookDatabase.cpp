
bool isValidISBN(string ISBN)
{

    if (ISBN.length() != 13)
    {
        return false;
    }

    for (int i = 0; i < 13; i++)
    {
        int x = ISBN[i] - '0';
        if (x >= 0 and x <= 9)
            continue;
        else
            return false;
    }

    return true;
}

class Book_database
{
public:
    set<Book> bookList;
    void Add();
    void Delete(long long int);
    void Update();
    vector<Book> Search();

    void showDataBase();

    Book showOptions(string msg); // My function to show option
    friend int main();
    friend void postLogin();
};

Book Book_database::showOptions(string msg)
{
    cout << "\tLeave empty if you don't want to enter any feild (simply press ENTER):\n";
    cout << "\t" << msg << endl;
    cout << "\n Title :\t";
    string title;
    getline(cin, title);

    cout << "\n Author :\t";
    string author;
    getline(cin, author);

    cout << "\n ISBN :\t";
    string ISBN;
    getline(cin, ISBN);

    while (!(ISBN.size() == 0 || isValidISBN(ISBN)))
    {
        cout << "\t\t Please enter the valid ISBN\n";
        cout << "\t\t ISBN : ";
        getline(cin, ISBN);
    }

    cout << "\n Publication :\t";
    string publication;
    getline(cin, publication);

    cout << "\n\t----------- Completed ---------------\n\n\n";
    cout << "This is for the conformation that you are using following feild to perform the operation \n";
    cout << "......................................................................................\n";
    cout << "\t\tTitle : " << title << "\n";
    cout << "\t\tAuthor : " << author << "\n";
    cout << "\t\tISBN : " << ISBN << "\n";

    cout << "\t\tPublication :" << publication << "\n";

    Book book;
    book.title = title;
    book.author = author;
    book.publication = publication;
    if (ISBN.size())
        book.ISBN = stoll(ISBN);
    else
        book.ISBN = -1; // FOR SEARCHING PURPOSES

    return book;
}

void Book_database::Update()
{
    cout << "\t\t TO UPDATE DATABASE\n ";

    cout << "\tFor Search (Press 1)\n";
    cout << "\tFor Add (Press 2)\n";
    cout << "\tFor Delete (Press 3)\n";
    cout << "\tFor Database (Press 4)\n";

    int ch;
    cin >> ch;
    cin.ignore();
    if (ch == 1)
        Search();
    else if (ch == 2)
        Add();
    else if (ch == 3)
    {

        string ISBN;
        cout << "Enter the ISBN you want to delete : ";
        getline(cin, ISBN);

        while (!isValidISBN(ISBN))
        {
            cout << "You have enter ISBN in wrong format it must be a 13 digit number.\n";
            cout << "Kindky RE-ENTER ISBN or simply press 'q' to quit\n";
            getline(cin, ISBN);
            if (ISBN == "q" || ISBN == "q")
                return;
        }
    }
    else if (ch == 4)
    {
        showDataBase();
        cout << "\n";
    }
    else
    {
        cout << "\t\tInvalid choice\n";
        cout << "Reenter the choice or enter zero for quit.\n";
        cin >> ch;
        if (ch)
            Update();
        else
            return;
    }

    char ch1;
    cout << "Press c to continue any other to quit.\n";
    cin >> ch1;
    if (ch1 == 'c')
        Update();
    return;
}

void Book_database::showDataBase()
{
    int cnt = 1;
    for (Book book : bookList)
    {
        cout << " " << cnt++ << ".\n";
        book.bookDetails();
        cout << "\n";
    }

    if (bookList.empty())
    {
        cout << "\tYou don't have any book record in your database.\n";
    }
}

void Book_database::Add()
{
    Book book = showOptions("Make all the entry filled. Note ISBN is of 13 length digit.");
    if (book.author.empty() || book.publication.empty() || book.title.empty())
    {
        cout << "YOU CAN'T LEAVE ANY FEILD EMPTY\n";
        cout << "\t\t ....KINDLY ADD THE DETAILS TO ADD AGAIN.....\n";
        Add();
    }
    while (book.ISBN == -1)
    {
        cout << "\t\t PLEASE ENTER THE VALID ISBN :";
        string isbn;
        getline(cin, isbn);
        if (isValidISBN(isbn))
        {
            book.ISBN = stoll(isbn);
        }
        cout << "If you want to quit (Press q)";
        string choice;
        getline(cin, choice);
        if (choice == "q" || choice == "Q")
            return;
    }

    bookList.insert(book);

    int cont;
    cout << "If you want to continue with the operation ADD, SEARCH, DELETE (Enter any digit other than 0)\n";
    cin >> cont;
    if (cont)
        Update();
}

void Book_database::Delete(long long int ISBN)
{
    for (auto book : bookList)
    {
        if (book.ISBN == ISBN)
        {
            bookList.erase(book);
        }
    }
}

vector<Book> Book_database::Search()
{
    Book book = showOptions("Kindly leave a feild empty if you want to search upon only certain feilds but you can't leave all as empty.");
    if (book.author.empty() and book.publication.empty() and book.title.empty() and book.ISBN == -1)
    {
        cout << "YOU CAN'T LEAVE ALL FEILD EMPTY\n";
        cout << "\t\t Kindly enter the details again for search \n";
        Search();
    }
    vector<Book> result;
    for (Book obj : bookList)
    {
        if ((book.title.empty() || book.title == obj.title) and (book.author.empty() || book.author == obj.author) and (book.ISBN == -1 || book.ISBN == obj.ISBN) and (book.publication.empty() || book.publication == obj.publication))
            result.push_back(obj);
    }
    cout << "\t\t Your Search Result :\n"; // I can return the list if nessesary
    for (auto book : result)
    {
        book.bookDetails();
    }

    return result;
}
