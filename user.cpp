
class User
{
public:
    string name;
    int id;
    string password;
    int type;

    void showUser();
};

void User::showUser()
{
    cout << "\t\t Username : " << this->name << "\n";
    cout << "\t\t UserID : " << this->id << "\n";
}
class Professor : public User
{
private:
    vector<Book> myList;
    int fineAmount;
    int Calculate_fineAmount();
    void Clear_fineAmount();

public:
    friend int main();
    friend void postLogin(User *usr, Book_database &bd, UserDataBase &db);
};

class Student : public User
{
private:
    vector<Book> myList;
    int fineAmount;
    int Calculate_fineAmount();
    void Clear_fineAmount();

public:
    friend int main();
     friend void postLogin(User *usr, Book_database &bd, UserDataBase &db);
};


class UserDataBase
{
private:
    map<int, User> userList;
    // We will map id -> user
    map<int, Professor> profList;
    map<int, Student> stdList;
    map<int, Librarian> libList;

public:
    friend int main();
    friend void Registation(UserDataBase &db);
    friend User *Login(UserDataBase &db);
    friend void Logout();
     friend void postLogin(User *usr, Book_database &bd, UserDataBase &db);
    // friend class UserDataBase;
    friend class Librarian;
};

class Librarian : public User
{
private:
    // void AddUser();
    void DeleteUser(long long id, UserDataBase &db);
    void AddBook(Book_database &bd);
    void DeleteBook(long long int ISBN, Book_database &bd);

public:
    friend int main();
    friend void postLogin(User *usr, Book_database &bd, UserDataBase &db);
};

void Librarian::AddBook(Book_database &bd)
{
    bd.Add();
}

void Librarian::DeleteBook(long long int ISBN, Book_database &bd)
{
    bd.Delete(ISBN);
}

void Librarian::DeleteUser(long long id, UserDataBase &db)
{
    db.userList.erase(id);
    db.profList.erase(id);
    db.stdList.erase(id);
    db.libList.erase(id);
    db.profList.erase(id);
}

int Student::Calculate_fineAmount()
{
    cout << "\t Enter the DATE(dd/yy/mm) :";
    string date;
    getline(cin, date);
    Date today = Date(date);
    int fine = 0;
    for (Book book : this->myList)
    {
        int d = today.difference(book.dueDate);

        if (d > 30)
        {
            fine += 2 * (d - 30);
        }
    }
    return fine;
}

void Student::Clear_fineAmount()
{
    this->fineAmount = 0;

    // Update all issued book
}

int Professor::Calculate_fineAmount()
{
    cout << "\t Enter the DATE(dd/yy/mm) :";
    string date;
    getline(cin, date);
    Date today = Date(date);
    int fine = 0;
    for (Book book : this->myList)
    {
        int d = today.difference(book.dueDate);

        if (d > 60)
        {
            fine += 5 * (d - 60);
        }
    }
    return fine;
}

void Professor::Clear_fineAmount()
{
    this->fineAmount = 0;
    // Now return all the issued book
}
