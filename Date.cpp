#include <bits/stdc++.h>
using namespace std;
class Date
{
public:
    int dd;
    int mm;
    int yyyy;

    bool isValid();
    bool isLeapYear();
    int difference(Date newDate);
    Date add(int x);
    void showDate();
    explicit Date();
    Date(string s);
};
Date::Date()
{
    // This is the default constructor
    //  I will  use this as per my need later
    this->dd = 0;
    this->yyyy = 0;
    this->mm = 0;

    // This mean no issue date have been found till
}
Date::Date(string s)
{

    int dateEndAt;
    if (s[1] == '/')
    {
        this->dd = s[0] - '0';
        dateEndAt = 1;
    }
    else
    {
        this->dd = 10 * (s[0] - '0') + (s[1] - '0');
        dateEndAt = 2;
    }
    dateEndAt++;
    if (s[dateEndAt + 1] == '/')
    {
        this->mm = s[dateEndAt] - '0';
    }
    else
    {
        this->mm = 10 * (s[0 + dateEndAt] - '0') + (s[1 + dateEndAt] - '0');
    }

    string year = "";
    int endPoint = s.length() - 1;
    while (s[endPoint] != '/')
    {
        year += s[endPoint];
        endPoint--;
    }
    reverse(year.begin(), year.end());
    this->yyyy = stoi(year);
}

Date Date::add(int x)
{
    if (x == 0)
        return *this;
    set<int> ThirtyOneDaysMonth = {1,
                                   3,
                                   5,
                                   7,
                                   8,
                                   10,
                                   12};

    int used = 0;

    if (this->mm == 2)
    {
        if (this->isLeapYear())
        {
            // upto 29
            while (x)
            {
                if (this->dd < 29)
                {
                    x--;
                    this->dd++;
                }
                else
                {
                    break;
                }
            }
        }
        else
        {

            while (x)
            {
                if (this->dd < 28)
                {
                    x--;
                    this->dd++;
                }
                else
                {
                    break;
                }
            }
        }
    }
    else
    {
        if (ThirtyOneDaysMonth.find(this->mm) != ThirtyOneDaysMonth.end())
        {
             while (x)
            {
                if(this->dd < 31)
                 {
                     x--;
                     this->dd++;
                 }
                 else{
                     break;
                 }
            }
        }
        else
        {
            while (x)
            {
                if(this->dd < 30)
                 {
                     x--;
                     this->dd++;
                 }
                 else{
                     break;
                 }
            }
        }
    }

    x = x - used;
    if (x)
    {
        if (this->mm == 12)
        {
            this->mm = 1;
            this->yyyy = this->yyyy + 1;
            this->dd = 1;
            x--;
            if (x)
                return this->add(x);
            else
                return *this;
        }
        else
        {
            if (!x)
                return this->add(x);
            this->dd = 1;
            this->mm += 1;
            x--;
            return this->add(x);
        }
    }
    else
    {
        return *this;
    }
}
bool Date::isLeapYear()
{
    if (this->yyyy % 400 == 0)
        return true;
    else if (this->yyyy % 100 == 0)
        return false;
    else if (this->yyyy % 4 == 0)
        return true;
    else
        return false;
}

bool Date::isValid()
{
    set<int> ThirtyOneDaysMonth = {1,
                                   3,
                                   5,
                                   7,
                                   8,
                                   10,
                                   12};

    if (this->mm > 12 || this->mm < 1)
        return false;

    if (this->dd < 1 || this->dd > 31)
        return false;

    if (this->mm == 2)
    {
        if (this->isLeapYear())
            return this->dd <= 29;
        else
            return this->dd <= 28;
    }
    else if (ThirtyOneDaysMonth.find(this->mm) != ThirtyOneDaysMonth.end())
    {
        return this->dd <= 31;
    }
    else
    {
        return this->dd <= 30;
    }
    return false;
}

int Date::difference(Date pastDate)
{
    if (pastDate.yyyy > this->yyyy || (pastDate.yyyy == this->yyyy and (pastDate.mm > this->mm || (pastDate.mm == this->mm and pastDate.dd > this->dd))))
    {
        return -1 * pastDate.difference(*this);
    }
    set<int> ThirtyOneDaysMonth = {1,
                                   3,
                                   5,
                                   7,
                                   8,
                                   10,
                                   12};
    if (this->yyyy == pastDate.yyyy)
    {
        // This upto the end of the month
        if (this->mm == pastDate.mm)
        {
            return this->dd - pastDate.dd + 1;
        }

        int ans = 0;
        if (pastDate.mm == 2)
        {
            if (pastDate.isLeapYear())
                ans += (29 - pastDate.dd + 1);
            else
                ans += (28 - pastDate.dd + 1);
        }
        else if (ThirtyOneDaysMonth.find(pastDate.mm) != ThirtyOneDaysMonth.end())
        {
            ans += (31 - pastDate.dd + 1);
        }
        else
        {
            ans += (30 - pastDate.dd + 1);
        }
        // end of pastMonth date
        // begin pastMonths
        for (int month = pastDate.mm + 1; month < this->mm; month++)
        {
            if (month == 2)
            {
                if (pastDate.isLeapYear())
                    ans += 29;
                else
                    ans += 28;
            }
            else if (ThirtyOneDaysMonth.find(month) != ThirtyOneDaysMonth.end())
            {
                ans += 31;
            }
            else
            {
                ans += 30;
            }
        }
        // endofPast month

        ans += this->dd;
        return ans;
    }
    else
    {
        int ans = 0;
        if (pastDate.mm == 2)
        {
            if (pastDate.isLeapYear())
                ans += (29 - pastDate.dd + 1);
            else
                ans += (28 - pastDate.dd + 1);
        }
        else if (ThirtyOneDaysMonth.find(pastDate.mm) != ThirtyOneDaysMonth.end())
        {
            ans += (31 - pastDate.dd + 1);
        }
        else
        {
            ans += (30 - pastDate.dd + 1);
        }

        for (int month = pastDate.mm + 1; month <= 12; month++)
        {
            if (month == 2)
            {
                if (pastDate.isLeapYear())
                    ans += 29;
                else
                    ans += 28;
            }
            else if (ThirtyOneDaysMonth.find(month) != ThirtyOneDaysMonth.end())
            {
                ans += 31;
            }
            else
            {
                ans += 30;
            }
        }

        for (int years = pastDate.yyyy + 1; years < this->yyyy; years++)
        {
            if (years % 400 == 0)
                ans += 366;
            else if (years % 100 == 0)
                ans += 365;
            else if (years % 4 == 0)
                ans += 366;
            else
                ans += 365;
        }

        for (int month = 1; month < this->mm; month++)
        {
            if (month == 2)
            {
                if (this->isLeapYear())
                    ans += 29;
                else
                    ans += 28;
            }
            else if (ThirtyOneDaysMonth.find(month) != ThirtyOneDaysMonth.end())
            {
                ans += 31;
            }
            else
            {
                ans += 30;
            }
        }
        ans += this->dd;
        return ans;
    }

    return -1;
}

void Date::showDate()
{
    cout << this->dd << "/" << this->mm << "/" << this->yyyy << endl;
}

