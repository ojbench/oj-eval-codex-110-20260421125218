// Problem 110 - 小恶魔的生日
// Implements a Date class with required operations and a test harness per README

#include <bits/stdc++.h>
using namespace std;

class Date {
private:
    int _year{1900};
    int _month{1};
    int _day{1};

    static bool isLeap(int y) {
        if (y % 400 == 0) return true;
        if (y % 100 == 0) return false;
        return y % 4 == 0;
    }

    static int daysInMonth(int y, int m) {
        static const int mdays[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
        if (m == 2) return mdays[m] + (isLeap(y) ? 1 : 0);
        if (m >= 1 && m <= 12) return mdays[m];
        return 0;
    }

    static bool isValidDate(int y, int m, int d) {
        if (m < 1 || m > 12) return false;
        int dim = daysInMonth(y, m);
        if (d < 1 || d > dim) return false;
        return true;
    }

    static long long leapsBeforeYear(int y) {
        // Count leap years from year 0 to y-1 inclusive
        long long n = y - 1;
        return n/4 - n/100 + n/400;
    }

    static long long daysBeforeYear(int y) {
        // Days from 1900-01-01 up to y-01-01
        long long years = (long long)y - 1900LL;
        return years * 365LL + (leapsBeforeYear(y) - leapsBeforeYear(1900));
    }

    static int daysBeforeMonth(int y, int m) {
        int days = 0;
        for (int i = 1; i < m; ++i) days += daysInMonth(y, i);
        return days;
    }

    long long toOrdinal() const {
        // 1900-01-01 -> 0
        return daysBeforeYear(_year) + daysBeforeMonth(_year, _month) + (_day - 1);
    }

    static Date fromOrdinal(long long ord) {
        // Build date from days since 1900-01-01
        Date d;
        long long remaining = ord;
        int y = 1900;
        // advance years
        while (true) {
            int ydays = isLeap(y) ? 366 : 365;
            if (remaining >= ydays) {
                remaining -= ydays;
                ++y;
            } else break;
        }
        d._year = y;
        int m = 1;
        while (true) {
            int md = daysInMonth(y, m);
            if (remaining >= md) {
                remaining -= md;
                ++m;
            } else break;
        }
        d._month = m;
        d._day = (int)remaining + 1;
        return d;
    }

public:
    Date() = default;
    Date(int yy, int mm, int dd) {
        if (isValidDate(yy, mm, dd)) {
            _year = yy; _month = mm; _day = dd;
        } else {
            _year = 1900; _month = 1; _day = 1;
        }
    }

    // out() helper with newline
    void out() const {
        cout << _year << '-' << _month << '-' << _day << '\n';
    }

    // Arithmetic with integers
    Date operator+(long long days) const {
        long long ord = toOrdinal();
        long long nord = ord + days;
        if (nord < 0) nord = 0; // clamp to base if ever underflows
        return fromOrdinal(nord);
    }
    Date operator-(long long days) const {
        long long ord = toOrdinal();
        long long nord = ord - days;
        if (nord < 0) nord = 0; // clamp
        return fromOrdinal(nord);
    }

    // Difference between dates (absolute days)
    long long operator-(const Date& other) const {
        long long a = toOrdinal();
        long long b = other.toOrdinal();
        return llabs(a - b);
    }

    // Comparisons
    bool operator<(const Date& other) const {
        if (_year != other._year) return _year < other._year;
        if (_month != other._month) return _month < other._month;
        return _day < other._day;
    }

    // Pre-increment (next day)
    Date& operator++() {
        *this = *this + 1;
        return *this;
    }
    // Post-increment
    Date operator++(int) {
        Date tmp = *this;
        *this = *this + 1;
        return tmp;
    }
    // Pre-decrement (previous day)
    Date& operator--() {
        *this = *this - 1;
        return *this;
    }
    // Post-decrement
    Date operator--(int) {
        Date tmp = *this;
        *this = *this - 1;
        return tmp;
    }

    friend ostream& operator<<(ostream& os, const Date& d) {
        os << d._year << '-' << d._month << '-' << d._day;
        return os;
    }
};

static void Test() {
    int op;
    if (!(cin >> op)) return;
    int yy, mm, dd;
    if (op == 1 || op == 0)
    {
        Date d0;
        Date d1(2000, 2, 29);
        Date d2(1900, 2, 29);
        cout << d0 << endl;
        cout << d1 << endl;
        cout << d2 << endl;
        // d0.out(); d1.out(); d2.out();
    }
    if (op == 2 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        for (int i=0;i<5;++i) cout << ++d0 << endl; //(++d0).out();
        for (int i=0;i<5;++i) cout << d0++ << endl; //(d0++).out();
        for (int i=0;i<5;++i) cout << d0-- << endl; //(d0--).out();
        for (int i=0;i<2;++i) cout << --d0 << endl; //(--d0).out();
        cout << d0 << endl;
        // d0.out();
    }
    if (op == 3 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        cout << d0 + 100 << endl;
        // (d0+100).out();
        cout << d0 - 1000 << endl;
        // (d0-1000).out();
    }
    if (op == 4 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        Date d1(2020, 12, 21);
        cout << (d0 < d1) << endl;
    }
    if (op == 5 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        Date d1(1912, 6, 23);
        cout << (d0 - d1) << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    Test();
    return 0;
}

