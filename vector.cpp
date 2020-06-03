#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>

using std::cout;
using std::endl;
using std::vector;
using std::string;

class String{
public:
	String(const char* str = "")
		:_str(new char[strlen(str) + 1]){
		strcpy(_str, str);
		cout << "String(const char*)" << endl;
	}

	~String(){
		if (_str){
			delete[] _str;
			_str = nullptr;
		}
		cout << "~String()" << endl;
	}
private:
	char* _str;
};

// vector是一个类模板
template<class T>
class Vector{
public:
	typedef T* iterator;
	typedef const T* const_iterator;

	Vector()
		:_start(nullptr)
		, _finish(nullptr)
		, _endOfStorage(nullptr){}
	size_t size(){
		return _finish - _start;
	}

	size_t capacity(){
		return _endOfStorage - _start;
	}

	// 尾插
	void pushBack(const T& val){
		//检查容量 (因为其本质为一个顺序表)
		//(size() == capacity())
		if (_finish == _endOfStorage){
			// 增容 reserve接口(传入要增容的大小)
			// 如果为0,增为1; 如果不为0,增到2倍
			size_t newC = capacity() == 0 ? 1 : 2 * capacity(); 
			reserve(newC);
		}
		// 尾插元素 在_finish位置插
		*_finish = val;
		++_finish;  // _finish 向后移动1, 意味size也+1
	}

	// reserve: 增容
	// 
	void reserve(size_t n){
		// 判断是否大于当前容量 
		if (n > capacity()){
			int sz = size(); // 记录当前的元素大小
			T* tmp = new T[n];
			// 空间开好后, 拷贝内容
			if (_start != nullptr){// (_start) 如果是空也不需要拷内容
				
				//拷贝内容:浅拷贝，会导致二次释放的问题
				//memcpy(tmp, _start, sizeof(T)* size());

				//深拷贝: 调用T类型的赋值运算符重载函数
				for (int i = 0; i < sz; ++i){
					tmp[i] = _start[i];
				}

				// 释放原有空间
				delete[]_start;// 会调析构,把资源释放了
			}
			// 更新指针
			_start = tmp;
			_finish = _start + sz;
			_endOfStorage = _start + n; // +偏移量
		}
	}

	void resize(size_t n, const T& val = T()){
		if (n > capacity()){
			reserve(n);
		}
		if (n > size()){
			while (_finish != _start + n){
				*_finish = val;
				++_finish;
			}
		}

		_finish = _start + n;
	}

	T& operator[](size_t pos){
		if (pos < size())
			return _start[pos];
	}

	iterator begin(){
		//第一个元素的位置
		return _start;
	}

	iterator end(){
		return _finish;
	}

	const_iterator begin() const{
		return _start;
	}

	const_iterator end() const{
		return _finish;
	}

private:
	T* _start; // 表示空间的首地址
	T* _finish; // 表示最后一个元素的结束位置
	T* _endOfStorage;// 表示空间的结束位置
};

void test(){
	Vector<int> v;
	int sz = v.size();
	int cap = v.capacity();

	v.pushBack(1);
	sz = v.size();
	cap = v.capacity();

	v.pushBack(2);
	sz = v.size();
	cap = v.capacity();

	for (int i = 0; i < 10000; ++i)
		v.pushBack(i);
}

void test2(){
	Vector<string> v;
	string str1 = "123";
	string str2 = "456";
	string str3 = "789";
	string str4 = "1011";
	string str5 = "1213";

	v.pushBack(str1);

	v.pushBack(str2);

	v.pushBack(str3);

	v.pushBack(str4);

	v.pushBack(str5);

	v.pushBack(str1);

	v.pushBack(str2);

	v.pushBack(str3);

	v.pushBack(str4);

	v.pushBack(str5);

	v.pushBack(str1);

	v.pushBack(str2);

	v.pushBack(str3);

	v.pushBack(str4);

	v.pushBack(str5);

	for (int i = 0; i < v.size(); ++i){
		cout << v[i] << endl;
		v[i] = "0";
	}

	for (int i = 0; i < v.size(); ++i){
		cout << v[i] << endl;
		v[i] = "0";
	}
}

template <class T>
void printVector(const Vector<T>& vec){
	Vector<T>::const_iterator it = vec.begin();
	while (it != vec.end()){
		cout << *it << " ";
		++it;
	}
	cout << endl;
}

void test3(){
	Vector<int> v;
	v.pushBack(1);
	v.pushBack(2);
	v.pushBack(3);
	v.pushBack(4);
	v.pushBack(5);
	v.pushBack(6);

	Vector<int>::iterator it = v.begin();
	while (it != v.end()){
		cout << *it << " ";
		*it = 100;
		++it;
	}
	cout << endl;

	printVector(v);

	for (const auto& e : v){
		cout << e << " ";
	}
	cout << endl;
}

void test4(){
	Vector<int> v;
	for (int i = 0; i < 10; ++i)
		v.pushBack(i);

	printVector(v);
	v.resize(5);
	printVector(v);
	v.resize(8);
	printVector(v);
	v.resize(20, 50);
	printVector(v);
}
int main(){
	test();

	system("pause");
	return 0;
}