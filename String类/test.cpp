#include<iostream>
#include<assert.h>
using namespace std;
#define DEFAULT_GAP 3
 class String
{
public:
	String(char* str = "")
	{	
		_size = strlen(str);
		_capacity = _size + 1;
		_str = (char*)malloc(sizeof(char)*_capacity);
		strcpy(_str, str);
	}
	String(const String &s)
		:_str(NULL)
	{
		String tem(s._str);
		swap(_str, tem._str);
		swap(_size, tem._size);
		swap(_capacity, tem._capacity);
	}
	String& operator=(String s)
	{
		swap(_str, s._str);
		swap(_size, s._size);
		swap(_capacity, s._capacity);
		return *this;
	}
	~String()
	{
		if (_str)
		{
			//delete[] _str;
			free(_str);
		} 
	}
public:
	void _CheackCapacity(size_t capacity)
	{
		if (capacity > _capacity)
		{
			_capacity = capacity + DEFAULT_GAP;
			_str=(char*)realloc(_str, _capacity);
			assert(_str);
		}
	}
	void PushBack(char ch)
	{
		_CheackCapacity(_size+2);
		_str[_size++] = ch;
		_str[_size] = '\0';
//		Insert(_size, ch);
	}
	void Insert(size_t pos, char ch)
	{
		_CheackCapacity(_size + 2);
		//memmove
		for (int begin = _size; begin >= pos; --begin)
		{
			_str[begin + 1] = _str[begin]; //???
		}
		_str[pos] = ch;
		++_size;
	}
	void Insert(size_t pos, const char* str)
	{
		int newCapacity = _size + strlen(str) + 1;
		_CheackCapacity(newCapacity);
		//int strSize=strlen(str);
		int end = strlen(str) + _size;
		for (int begin = _size; begin >= pos; --begin)
		{
			_str[end] = _str[begin];
			--end;
		}
		strncpy(_str + pos, str, strlen(str));
		_size += strlen(str);
	}
	char& operator[](size_t index)
	{
		assert(index < _size);
		return _str[index];
	}
	bool operator<(const String &s)
	{
		char* begin1 = _str;
		char* begin2 = s._str;
		while (*begin1 && *begin2)
		{
			if (*begin1 > *begin2)
			{
				return false;
			}
			else if (*begin1 < *begin2)
			{
				return true;
			}
			else
			{
				++begin1;
				++begin2;
			}
		}
		return *begin1 < *begin2;
	}
	/*
	*/
	bool operator==(const String &s)
	{
		char* begin1 = _str;
		char* begin2 = s._str;
		if (_size != s._size)
		{
			return false;
		}

		while (*begin1 && *begin2)
		{
			if (*begin1 != *begin2)
			{
				return false;
			}
			else
			{
				++begin1;
				++begin2;
			}
		}
		return true;
	}
	/*
	*/
	int Find(const String &s)
	{
		if (_size < s._size)
		{
			return -1;
		}
		int srcIndex = 0;
		int dstIndex = 0;
		int old;
		const char* src = _str;
		const char* dst = s._str;
		while (srcIndex < _size )
		{		old = srcIndex;
			while (dstIndex < s._size && srcIndex<_size)
			{				
				if (src[srcIndex] == dst[dstIndex])
				{
					++srcIndex;
					++dstIndex;
				}
				else
				{
					dstIndex = 0;
					srcIndex = old + 1;
					break;
				}
			}	
			if (dstIndex == s._size)
			{
				return old;
			}	
		}	
		return -1;
	}
	void PopBack()
	{
		--_size;
	}
	 
	char* Getstr()
	{
		return _str;
	}

private:
	char* _str;
	int _size;
	int _capacity;
};
 void test()
 {
	 char* p1 = "abcd";
	 String s1(p1);
	 cout<<s1.Getstr()<<endl;
 }
 void test1()
 {
	 String s1("hello");
	 cout << s1.Getstr() << endl;
	 s1.PushBack('d');
	 s1.PopBack();
	 s1.PushBack('d');
	 cout << s1.Getstr() << endl;

	 s1.Insert(5, " worl");
	 cout << s1.Getstr() << endl;

 }
 void test2()
 {
	 //String s1("ab");
	 //String s2("abc");
	 //cout << (s1 < s2) << endl;
	 //cout << (s1 == s2) << endl;
	 String s3("abcdabcdefg");
	int ret= s3.Find("cde");
	cout<< ret << endl;
 }
 int main(void)
 {
	 test1();
 }