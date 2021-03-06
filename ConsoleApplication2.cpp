﻿// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <numeric>
#include <map>
#include <set>
#include <string>
#include <iterator>
#include <mutex>
#include"windows.h"

using namespace std;
mutex mMutex;

void callBackF(int val)
{
	cout << "val = " << val << endl;
}

typedef void(*pFunc)(int);

void myFunc(pFunc p)
{
	p(111);
}

void func(vector<string> vec)
{
	vector<string>::iterator iter = vec.begin();
	while (iter != vec.end())
	{
		cout << *iter << endl;
		++iter;
	}
}

void printVal(int cnt, string str)
{
	mMutex.lock();
	for (int i = 0; i < cnt; ++i)
	{
		cout << str << ", ";
		Sleep(1000);
	}
	cout << endl;
	mMutex.unlock();
}

string callBackFuncStr(string str, string(*pFunc)(string))
{
	return pFunc(str);
}

string NewString(string str)
{
	size_t i{0};
	while (i < str.length())
	{
		if (str[i] >= 'a'&&str[i] < 'z' || str[i] >= 'A'&&str[i] < 'Z')
			++str[i];
		++i;
	}
	return str;
}

class A
{
private:
	int iVal;
	int mArray[5];
public:
	A()
	{
		for (int i = 0; i < 5; ++i)
			mArray[i] = i + 5;
		cout << "Def constructor." << endl; 
	}
	A(int n) :iVal(n) {}
	bool operator==(const A& obj)
	{
		return this->iVal == obj.iVal;
	}
	A(const A& obj)	//copy constructor
	{
		this->iVal = obj.iVal;
	}
	
	A operator=(const A& obj)	//operator assignment
	{
		if (*this == obj)
			return obj;
		this->iVal = obj.iVal;
		return *this;
	}

	int operator[](int k)
	{
		return mArray[k];
	}

	int getVal()
	{
		return iVal;
	}
};

template<typename T>
class C
{
private:
	T m_Val;
public:
	C(T a) :m_Val(a) 
	{
		cout << "Template" << endl;
	}
	T getVal() { return m_Val; }
};

void FuncForEach(int a)
{
	cout << "arr[i] = " << a << ", " << endl;
}

int main()
{

	vector<int> iVec(5);
	vector<int> iVec2;
	iota(iVec.begin(), iVec.end(), 1);
	for (auto& x : iVec)
	{
		cout << x << endl;
	}
	cout << "size of int vector is: " << iVec.size() << endl;
	

	list<double> dList(5);
	iota(dList.begin(), dList.end(), 1.1);
	for (auto& x : dList)
	{
		cout << x << endl;
	}
	cout << endl;

	using iter = list<double>::iterator;
	iter ii = dList.begin();
	++ii;
	dList.insert(ii, 5.5);
	for (auto& x : dList)
	{
		cout << x << endl;
	}

	map<int, const char> mMap;
	mMap.insert(pair<int, const char>(10, 'a'));
	mMap.insert(pair<int, const char>(15, 'b'));
	mMap.insert(pair<int, const char>(35, 'c'));
	mMap.insert(pair<int, const char>(5, 'd'));

	map<int, const char>::iterator iMap = mMap.find(45);
	if (iMap != mMap.end())
		cout << (*iMap).second << endl;
	else
		cout << "the value not found" << endl;
	iMap = mMap.begin();
	for (auto& x : mMap)
		cout << x.first << "  " << x.second << endl;

	iMap = mMap.begin();
	while (iMap != mMap.end())
	{
		if ((*iMap).second == 'd')
			cout << (*iMap).first << endl;
		++iMap;
	}

	/*{
		string strArr[]{ "abcd", "asd", "asdf", "erte" };
		vector<string> v1(strArr, strArr + sizeof(strArr) / sizeof(string));

		vector<string> v2;
		v2.push_back("qwer");
		v2.push_back("sgfdfg");
		v2.push_back("tyutyu");
		v2.push_back("xdfgnb");
		v2.push_back("uykl");
		vector<string> v3(v2.begin(), v2.end());
	
		vector<vector<string>> v4;
		v4.push_back(v2);
		v4.push_back(v1);
		v4.push_back(v3);

		vector<vector<string>>::iterator iVec2 = v4.begin();
		while (iVec2 != v4.end())
		{
			func(*iVec2);
			cout << endl;
			++iVec2;
		}
	}

	{
		set<int> iSet;
		iSet.insert(15);
		iSet.insert(2);
		iSet.insert(10);
		iSet.insert(4);
		iSet.insert(10);
		cout << "set size is: " << iSet.size() << endl;
		copy(iSet.begin(), iSet.end(), ostream_iterator<int>(cout, " "));
	}

	{
		cout << endl;
		map<int, string> map1;
		map1[1] = "one";
		map1[2] = "two";
		map1[2] = "three";

		map1.insert(pair<int, string>(4, "four"));
		map1.insert(pair<int, string>(4, "five"));

		map<int, string>::iterator mapIter = map1.begin();
		while (mapIter != map1.end())
		{
			cout << mapIter->first << " " << mapIter->second << endl;
			++mapIter;
		}
	}
	
	{
		cout << "Multithreading example" << endl;
		thread th1(printVal, 5, "TH1");
		thread th2(printVal, 9, "TH2");
		th1.join();
		th2.join();
	}

	{
		string str{ "New String is z" };
		cout << "The original string is: " << str << endl;
		str = callBackFuncStr(str, &NewString);
		cout << "The modified string is: " << str << endl;

		unique_ptr<int> ptrI(new int(25));
		cout << *ptrI << endl;
	}

	{
		cout << "A class with copy copy constructor" << endl;
		A ob1(125);
		cout << "A class value is: " << ob1.getVal() << endl;
		A ob2 = ob1;
		cout << "A class value for ob2 is: " << ob2.getVal() << endl;
		A ob3(130);
		cout << "befor assigment ob3 is: " << ob3.getVal() << endl;
		ob3 = ob2;
		cout << "after assigment ob3 is: " << ob3.getVal() << endl;
		ob3 = ob3;
		cout << "after assigment ob3 is: " << ob3.getVal() << endl;
	}

	{
		C<int> ob1(25);
		cout << ob1.getVal() << endl;

		C<double> ob2(25.5);
		cout << ob2.getVal() << endl;

		C<string> ob3("String");
		cout << ob3.getVal() << endl;
	}

	{
		int arr[]{ 1,2,6,7,5,9,4,1,6 };
		int i{ 0 };
		for_each(arr, arr + sizeof(arr) / sizeof(int), [&](int x)
		{
			cout << "arr[" << i << "] = " << x << ", " << endl;
			++i;
		});
		cout << endl;

		for_each(arr, arr + sizeof(arr) / sizeof(int), (&FuncForEach));
	}

	{
		vector<int> iVect(10);
		iota(iVect.begin(), iVect.end(), 2);
		//copy(iVect.begin(), iVect.end(), ostream_iterator<int>(cout, ", "));
		//vector<int>::const_iterator iter = iVect.cbegin();
		const vector<int>::iterator iter = iVect.begin();
		cout << *iter << endl;
		*iter = 12;
		cout << *iter << endl;
		cout << endl;
	}*/

	{
		A ob;
		int k = ob[2];
		for (int i = 0; i < 5; ++i)
			cout << ob[i] << ", ";
		cout << endl;
	}

	cout << endl;
	cout << "C++ 11" << endl;
	cout << "C++ interview" << endl;
    return 0;
}
