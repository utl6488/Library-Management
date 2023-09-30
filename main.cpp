#include "headers.h"

#include "Date.cpp"
#include "book.cpp"
#include "BookDatabase.cpp"
#include "user.cpp"

void Registation(UserDataBase &db);
User *Login(UserDataBase &db);
void Logout(User *usr);
int PresentChoice();
int showOptionProf();
int showOptionForLib();
bool isConvertable(string s);

int main()
{ // Gloabal user database
    UserDataBase db;
    Book_database bd;
    int ch = PresentChoice();

    while (ch != -1)
    {

        if (ch == 0)
        {
            cout << "\t\tYou have entered the invalid choice.\n";
            system("sleep 1\n");
            system("clear\n");
            ch = PresentChoice();
        }

        else if (ch == -1)
        {
            cout << "\t\tExiting succesfully!\n";
            exit(0);
        }

        else if (ch == 1)
        {
            Registation(db);
            cout << "\n\n\n";
            system("sleep 2\n");
            system("clear\n");
            // User *u = Login(db);
            // if (u->id >= 1000)
            // {
            //     cout << "Redircting to Login ....\n";
            //     system("sleep 2\n");
            //     postLogin(u, bd, db);
            //     Logout(u);
            // }
        }
        else if (ch == 2)
        {
            User *usr = Login(db);
            if (usr->id == 0)
            {
                cout << "Type c to continue or q to quit\n";
                string choice;
                cin >> choice;
                cin.ignore();
                if (choice == "c")
                {
                    system("clear\n");
                    ch = PresentChoice();
                }
                else
                {
                    exit(0);
                }
            }
            else if (usr->type == 1)
            {
                // Professor
                cout << "\t\tWELCOME " << usr->name << " TO THE LIBRARY MANAGMENT SYSTEM\n";
                Professor *pf = &db.profList[usr->id];

                int pch = showOptionProf();

                if (pch == 1)
                {
                    vector<Book> listBook = bd.Search();
                    for (auto myissue : listBook)
                    {
                        if (myissue.isAvailable)
                        {
                            myissue.Book_Request(60);
                            pf->myList.push_back(myissue);
                            break;
                        }
                        else
                        {
                            cout << "The Book is not available\n";
                        }
                    }
                }
                else if (pch == 2)
                {
                    int cnt = 1;
                    for (auto it : pf->myList)
                    {
                        cout << cnt++ << "\n";
                        it.bookDetails();
                    }
                }
                else if (pch == 3)
                {
                    for (auto book : bd.bookList)
                    {
                        book.bookDetails();
                        cout << "\n";
                    }
                }
                else if (pch == 4)
                {
                    int x = pf->Calculate_fineAmount(); //<< "\n";
                    cout << "Fine Amount: " << x << "\n";
                }
                else if (pch == 5)
                {
                    int cnt = 1;
                    for (auto it : pf->myList)
                    {
                        cout << cnt++ << "\n";
                        it.bookDetails();
                    }

                    cout << "Now enter the serial no of the book you want to return ";
                    int sl;
                    cin >> sl;
                    if (sl >= pf->myList.size())
                        continue;
                    pf->myList[sl - 1].Book_return();
                    pf->myList.erase(pf->myList.begin() + sl - 1);
                }
                else
                {
                    cout << "Invalid choice!\n";
                    cout << "Press q to exit or any options ";
                    string mychoice;
                    cin >> mychoice;
                    cin.ignore();
                    if (mychoice == "q")
                    {
                        Logout(usr);
                        system("sleep 2\n");
                        system("clear");
                        // ch = PresentChoice();
                    }
                }
            }
            else if (usr->type == 2)
            {
                // Student
                cout << "\t\tWELCOME " << usr->name << " TO THE LIBRARY MANAGMENT SYSTEM\n";
                Student *pf = &db.stdList[usr->id];

                int pch = showOptionProf();

                if (pch == 1)
                {
                    // issue book
                    // cout << "Enter book name :";
                    // string bname;
                    // cin >> bname;
                    // cin.ignore();
                    // Book *myissue;

                    // for (auto pp : bd.bookList)
                    // {
                    //     if (pp.title == bname)
                    //     {
                    //         myissue = &pp;
                    //     }
                    // }

                    // if (myissue->isAvailable)
                    // {
                    //     myissue->Book_Request(60);
                    //     pf->myList.push_back(*myissue);
                    // }
                    // else
                    // {
                    //     cout << "The Book is not available\n";
                    // }

                    vector<Book> listBook = bd.Search();
                    for (auto myissue : listBook)
                    {
                        if (myissue.isAvailable)
                        {
                            myissue.Book_Request(60);
                            pf->myList.push_back(myissue);
                            break;
                        }
                        else
                        {
                            cout << "The Book is not available\n";
                        }
                    }
                }
                else if (pch == 2)
                {
                    int cnt = 1;
                    for (auto it : pf->myList)
                    {
                        cout << cnt++ << "\n";
                        it.bookDetails();
                    }
                }
                else if (pch == 3)
                {
                    for (auto book : bd.bookList)
                    {
                        book.bookDetails();
                        cout << "\n";
                    }
                }
                else if (pch == 4)
                {
                    cout << "Your fine amount is : = " << pf->Calculate_fineAmount() << "\n";
                }
                else if (pch == 5)
                {
                    int cnt = 1;
                    for (auto it : pf->myList)
                    {
                        cout << cnt++ << "\n";
                        it.bookDetails();
                    }

                    cout << "Now enter the serial no of the book you want to return ";
                    int sl;
                    cin >> sl;
                    if (sl >= pf->myList.size())
                        continue;
                    pf->myList[sl - 1].Book_return();
                    pf->myList.erase(pf->myList.begin() + sl - 1);
                }
                else
                {
                    cout << "Invalid choice!\n";
                    cout << "Press q to exit or any options ";
                    string mychoice;
                    cin >> mychoice;
                    cin.ignore();
                    if (mychoice == "q")
                    {
                        Logout(usr);
                        system("sleep 2\n");
                        system("clear");
                        // ch = PresentChoice();
                    }
                }
            }
            else if (usr->type == 3)
            {
                // Librarian
                cout << "\t\tWELCOME " << usr->name << " TO THE LIBRARY MANAGMENT SYSTEM\n";
                Librarian *lb = &db.libList[usr->id];
                int lch = showOptionForLib();
                if (lch == 1)
                {
                    // bd

                    lb->AddBook(bd);
                }
                else if (lch == 2)
                {
                    cout << "\t\t ENTER ISBN : ";
                    long long int isbn;
                    cin >> isbn;
                    lb->DeleteBook(isbn, bd);
                }
                else if (lch == 3)
                {
                    for (auto book : bd.bookList)
                    {
                        book.bookDetails();
                        cout << "\n";
                    }
                }
                else if (lch == 4)
                {
                    cout << "Enter the id to be deleted :";
                    int nid;
                    cin >> nid;
                    cin.ignore();
                    lb->DeleteUser(nid, db);
                }
                else if (lch == 5)
                {
                    int cnt = 1;
                    for (auto pp : db.userList)
                    {
                        cout << cnt++ << "\n";
                        pp.second.showUser();
                        cout << "\n";
                    }
                }

                else
                {
                    cout << "Invalid choice!\n";
                    cout << "Press q to exit or any options ";
                    string mychoice;
                    cin >> mychoice;
                    cin.ignore();
                    if (mychoice == "q")
                    {
                        Logout(usr);
                        system("sleep 2\n");
                        system("clear");
                        // ch = PresentChoice();
                    }
                }
            }
        }

        ch = PresentChoice();
    }

    return 0;
}

void Registation(UserDataBase &db)
{
    cout << "\t\t REGISTATION PORTAL\n";
    cout << "\t Enter Your Name : ";
    string name;
    getline(cin, name);
    cout << "\t Enter Your ID(4 digit Number): ";
    int id;
    cin >> id;
    string password;
    bool isNewEntty = true;

    while (id < 1000 or id > 9999)
    {
        cout << "Please Enter a valid id or q to quit...\n";
        cout << "\t New ID:";
        string ch;
        cin >> ch;
        cin.ignore();
        if (ch == "q")
        {
            isNewEntty = false;
            break;
        }

        id = stoi(ch);
    }

    while (db.userList.find(id) != db.userList.end())
    {

        cout << "\t\tThis USERID has been taken\n";
        cout << "\tRe-Enter a new id or q to quit:";
        string choice;
        cin >> choice;
        cin.ignore();
        if (choice == "q")
        {
            isNewEntty = false;
            break;
        }
        id = stoi(choice);
        isNewEntty = true;
    }

    if (isNewEntty)
    {
        cout << "\t Now set the Password(min of 6 charecters) :";
        cin.ignore();
        getline(cin, password);
        while (password.size() < 6)
        {
            cout << "Re-Enter the password or q to quit :";
            cin >> password;
            cin.ignore();
            if (password == "q")
            {
                isNewEntty = false;
                break;
            }
        }
    }

    if (isNewEntty)
    {
        cout << "You want to register as : (1-Profesor, 2-Student, 3-Librarian)"
             << "\n";
        int a;
        cin >> a;
        cin.ignore();
        if (a == 1)
        {
            Professor pf;
            pf.id = id;
            pf.name = name;
            pf.password = password;
            pf.type = 1;

            db.userList[id] = pf;
            db.profList[id] = pf;
            cout << "Congratulation " << pf.name << "! You have succesfully registered to our system.\n";
        }
        else if (a == 2)
        {
            Student st;
            st.id = id;
            st.name = name;
            st.password = password;
            st.type = 2;

            db.userList[id] = st;
            db.stdList[id] = st;
            cout << "Congratulation " << st.name << "! You have succesfully registered to our system.\n";
        }
        else if (a == 3)
        {
            Librarian lb;
            lb.id = id;
            lb.password = password;
            lb.type = 3;
            lb.name = name;

            db.userList[id] = lb;
            db.libList[id] = lb;
            cout << "Congratulation " << lb.name << "! You have succesfully registered to our system.\n";
        }
    }
}

User *Login(UserDataBase &db)
{
    system("clear");
    cout << "\t\t LOGIN PORTAL :\n";
    cout << "\tEnter ID :";
    string ids;
    cin >> ids;
    cin.ignore();
    int id = 0;
    if (isConvertable(ids))
    {
        id = stoi(ids);
    }
    cout << "\tPassword : ";
    string password;
    getline(cin, password);
    // cin.ignore();
    //  cout << id << " " << password << "\n";

    while (db.userList.find(id) != db.userList.end())
    {

        if (db.userList[id].password == password)
        {
            cout << "\tLogin Succesfully!\n";
            return &db.userList[id];
        }
        else
        {
            cout << "Wrong Password or UserID enter q to quit\n";
            system("clear");
            cout << "\t\tLOGIN PORTAL\n";
            cout << "\tEnter ID :";
            // int id;
            string choice;
            cin >> choice;
            cin.ignore();

            if (choice == "q")
            {
                User *usr = new User;
                usr->id = -1; // Choosen quit
            }
            id = stoi(choice);
            cout << "\tPassword : ";
            // string password;
            getline(cin, password);
            cin.ignore();
        }
    }

    // if (db.userList.find(id) == db.userList.end())
    // {
    //     //
    //     cout << "\n\t\tNo user exsist with the above id\n";
    //     cout << "\t\tPress c to continue with login system q to quit\n";
    //     string c;
    //     cin >> c;
    //     cin.ignore();
    //     if (c == "c")
    //         Login(db);
    // }

    return new User;
}

void Logout(User *usr)
{
    cout << "Dear " << usr->name << "! You have Logout succesfully from our system!"
         << "\n";
}

int PresentChoice()
{ // system("echo Redirecting....");
    system("sleep 1");
    //  system("clear");
    cout << "\t\tDASHBOARD PORTAL : \n";
    cout << "Press 1 for Registation\n";
    cout << "Press 2 for Login\n";
    cout << "Press q to quit\n";
    string choice;
    cin >> choice;
    cin.ignore();
    if (choice == "q")
        return -1;

    if (choice == "1")
        return 1;
    else if (choice == "2")
        return 2;
    else
    {
        return 0;
    }
}

int showOptionProf()
{
    cout << "\t\t Press 1 to ISSUE BOOK \n";
    cout << "\t\t Press 2 to SHOW BOOK YOU HAVE ISSUED\n";
    cout << "\t\t Press 3 to SEE ALL THE BOOK IN THE LIBRARY\n";
    cout << "\t\t Press 4 to SEE THE FINE\n";
    cout << "\t\t Press 5 to RETURN BOOK\n";
    cout << "\t\t Press q to to quit\n";

    string choice;
    cin >> choice;
    cin.ignore();

    if (choice == "q")
        return -1;

    return choice[0] - '0';
}

int showOptionForLib()
{
    cout << "\t\t Press 1 to ADD BOOK \n";
    cout << "\t\t Press 2 to DELETE BOOK\n";
    cout << "\t\t Press 3 to SEE ALL THE BOOK IN THE LIBRARY\n";
    cout << "\t\t Press 4 to DELETE USER\n";
    cout << "\t\t Press 5 to SEE ALL THE USER\n";
    cout << "\t\t Press q to to quit\n";

    string choice;
    cin >> choice;
    cin.ignore();

    if (choice == "q")
        return -1;

    return choice[0] - '0';
}

bool isConvertable(string s)
{
    bool ans = true;
    for (char ch : s)
    {
        ans = ans and (ch >= '0' and ch <= '9');
    }
    return ans;
}

void postLogin(User *usr, Book_database &bd, UserDataBase &db)
{
    if (usr->id == 0)
    {
        return;
    }
    else if (usr->type == 1)
    {
        // Professor
        cout << "\t\tWELCOME " << usr->name << " TO THE LIBRARY MANAGMENT SYSTEM\n";
        Professor *pf = &db.profList[usr->id];

        int pch = showOptionProf();

        if (pch == 1)
        {
            vector<Book> listBook = bd.Search();
            for (auto myissue : listBook)
            {
                if (myissue.isAvailable)
                {
                    myissue.Book_Request(60);
                    pf->myList.push_back(myissue);
                    break;
                }
                else
                {
                    cout << "The Book is not available\n";
                }
            }
        }
        else if (pch == 2)
        {
            int cnt = 1;
            for (auto it : pf->myList)
            {
                cout << cnt++ << "\n";
                it.bookDetails();
            }
        }
        else if (pch == 3)
        {
            for (auto book : bd.bookList)
            {
                book.bookDetails();
                cout << "\n";
            }
        }
        else if (pch == 4)
        {
            int x = pf->Calculate_fineAmount(); //<< "\n";
            cout << "Fine Amoutn : " << x << "\n";
        }
        else
        {
            cout << "Invalid choice!\n";
            cout << "Press q to exit or any options ";
            string mychoice;
            cin >> mychoice;
            cin.ignore();
            if (mychoice == "q")
            {
                Logout(usr);
                system("sleep 2\n");
                system("clear");
                // ch = PresentChoice();
            }
        }
    }
    else if (usr->type == 2)
    {
        // Student
        cout << "\t\tWELCOME " << usr->name << " TO THE LIBRARY MANAGMENT SYSTEM\n";
        Student *pf = &db.stdList[usr->id];

        int pch = showOptionProf();

        if (pch == 1)
        {
            // issue book
            // cout << "Enter book name :";
            // string bname;
            // cin >> bname;
            // cin.ignore();

            vector<Book> listBook = bd.Search();
            for (auto myissue : listBook)
            {
                if (myissue.isAvailable)
                {
                    myissue.Book_Request(60);
                    pf->myList.push_back(myissue);
                    break;
                }
                else
                {
                    cout << "The Book is not available\n";
                }
            }
        }
        else if (pch == 2)
        {
            int cnt = 1;
            for (auto it : pf->myList)
            {
                cout << cnt++ << "\n";
                it.bookDetails();
            }
        }
        else if (pch == 3)
        {
            for (auto book : bd.bookList)
            {
                book.bookDetails();
                cout << "\n";
            }
        }
        else if (pch == 4)
        {
            cout << "Your fine amount is : = " << pf->Calculate_fineAmount() << "\n";
        }
        else
        {
            cout << "Invalid choice!\n";
            cout << "Press q to exit or any options ";
            string mychoice;
            cin >> mychoice;
            cin.ignore();
            if (mychoice == "q")
            {
                Logout(usr);
                system("sleep 2\n");
                system("clear");
                // ch = PresentChoice();
            }
        }
    }
    else if (usr->type == 3)
    {
        // Librarian
        cout << "\t\tWELCOME " << usr->name << " TO THE LIBRARY MANAGMENT SYSTEM\n";
        Librarian *lb = &db.libList[usr->id];
        int lch = showOptionForLib();
        if (lch == 1)
        {
            // bd

            lb->AddBook(bd);
        }
        else if (lch == 2)
        {
            cout << "\t\t ENTER ISBN : ";
            long long int isbn;
            cin >> isbn;
            lb->DeleteBook(isbn, bd);
        }
        else if (lch == 3)
        {
            for (auto book : bd.bookList)
            {
                book.bookDetails();
                cout << "\n";
            }
            // system("sleep 4\n");
        }
        else if (lch == 4)
        {
            cout << "Enter the id to be deleted :";
            int nid;
            cin >> nid;
            cin.ignore();
            lb->DeleteUser(nid, db);
        }
        else if (lch == 5)
        {
            int cnt = 1;
            for (auto pp : db.userList)
            {
                cout << cnt++ << "\n";
                pp.second.showUser();
                cout << "\n";
            }
        }

        else
        {
            cout << "Invalid choice!\n";
            cout << "Press q to exit or any options ";
            string mychoice;
            cin >> mychoice;
            cin.ignore();
            if (mychoice == "q")
            {
                Logout(usr);
                system("sleep 2\n");
                system("clear");
                // ch = PresentChoice();
            }
        }
    }
}