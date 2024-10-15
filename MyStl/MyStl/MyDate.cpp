#include <iostream>
#include <vector>
using std::cout;
using std::endl;

int GetMonthDay(int year, int month) {
	int MonthDay[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)) {
		return 29; // 年份如果能被400整除即为闰年， 能被4整除但不能被100整除也为闰年
	}
	else {
		return MonthDay[month];
	}	
}

class Date {
public:
	Date(int year = 0, int month = 1, int day = 1)
		:_year(year), _month(month), _day(day)
	{
		if (_year < 0 || _month < 1 || _month > 12 || _day < 1 || _day > GetMonthDay(_year, _month)) {
			cout << "输入未通过校验" << endl;
			return;
		}
	}

	Date(const Date& date) {
		_year = date._year;
		_month = date. _month;
		_day = date._day;
	}

	bool operator > (const Date& date) {
		if (_year > date._year) {
			return true;
		}
		else if (_year == date._year && _month > date._month){
			return true;
		}
		else if (_year == date._year && _month == date._month && _day > date._day) {
			return true;
		}
		else {
			return false;
		}
	}

	bool operator < (const Date& date) {
		return !(*this > date);
	}

	bool operator >= (const Date& date) {
		return (*this > date) || (*this == date);
	}

	bool operator <= (const Date & date) {
		return (*this < date) || (*this == date);
	}

	bool operator == (const Date& date) {
		return _year == date._year && _month == date._month && _day == date._day;
	}

	bool operator != (const Date& date) {
		return !(*this == date);
	}

	bool operator += (const int days) {
		int MutiDays = _day + days;
		if (MutiDays > GetMonthDay(_year, _month)) { // 如果日期和大于当前月的最大值
			_month += 1;
			if (_month == 13) {
				_month = 1;
				_year += 1;
			}
			_day = MutiDays - GetMonthDay(_year, _month); // 日期和减去下个月的最大值就是下个月剩余天数
		}
		else {
			_day += days;
		}
		return true;
	}

	bool operator -= (const int days) {
		int GapDays = _day - days;
		if (GapDays <= 0) {
			if (_month == 1) {
				_year--;
				_month = 12;
				_day = GetMonthDay(_year, _month) - GapDays;
			}
			else {
				_month--;
				_day = GetMonthDay(_year, _month) - GapDays;
			}
		}
		else {
			_day = GapDays;
		}
		return true;
	}

	Date& operator + (const int& days) {
		int MonthNow = GetMonthDay(_year, _month);
		if (_day + days > MonthNow) {
			_day = days + (MonthNow - _day);
			_month += 1;
			if (_month == 13) {
				_month = 1;
				_year += 1;
			}
		}
		else {
			_day += days;
		}
		return *this;
	}

	Date& operator - (const int& days) {
		int GapDays = _day - days;
		if (GapDays <= 0) { // 这时Gapdays是负数， 所以后面要加
			if (_month == 1) {
				_year--;
				_month = 12;
				_day = GetMonthDay(_year, _month) + GapDays;
			}
			else {
				_month--;
				_day = GetMonthDay(_year, _month) + GapDays;
			}
		}
		else {
			_day = GapDays;
		}
		return *this;
	}

	int operator - (const Date& date) {
		if (_day - date._day < 0) {
			return GetMonthDay(_year, _month - 1) + _day - date._day;
		}
		else {
			return _day - date._day;
		}
	}

	int CodeTest(int a) {
		if (a - 10 < 0 || a % 10 == 0) {
			return a + 10;
		}
	}

	~Date() {
		
	}

private:
	int _year;
	int _month;
	int _day;
};

int main() {
	Date d1(1999, 12, 30);
	Date d2(d1);
	d1 += 10;
	d2 -= 1;
	Date d3(d2 - 10);
	d2 - 20;
	cout << (d2 - d1) << '\n';
	cout << (d1 > d2) << '\n';
	cout << (d1 < d2) << '\n';
}
