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

// vector��һ����ģ��
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

	// β��
	void pushBack(const T& val){
		//������� (��Ϊ�䱾��Ϊһ��˳���)
		//(size() == capacity())
		if (_finish == _endOfStorage){
			// ���� reserve�ӿ�(����Ҫ���ݵĴ�С)
			// ���Ϊ0,��Ϊ1; �����Ϊ0,����2��
			size_t newC = capacity() == 0 ? 1 : 2 * capacity(); 
			reserve(newC);
		}
		// β��Ԫ�� ��_finishλ�ò�
		*_finish = val;
		++_finish;  // _finish ����ƶ�1, ��ζsizeҲ+1
	}

	// reserve: ����
	// 
	void reserve(size_t n){
		// �ж��Ƿ���ڵ�ǰ���� 
		if (n > capacity()){
			int sz = size(); // ��¼��ǰ��Ԫ�ش�С
			T* tmp = new T[n];
			// �ռ俪�ú�, ��������
			if (_start != nullptr){// (_start) ����ǿ�Ҳ����Ҫ������
				
				//��������:ǳ�������ᵼ�¶����ͷŵ�����
				//memcpy(tmp, _start, sizeof(T)* size());

				//���: ����T���͵ĸ�ֵ��������غ���
				for (int i = 0; i < sz; ++i){
					tmp[i] = _start[i];
				}

				// �ͷ�ԭ�пռ�
				delete[]_start;// �������,����Դ�ͷ���
			}
			// ����ָ��
			_start = tmp;
			_finish = _start + sz;
			_endOfStorage = _start + n; // +ƫ����
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
		//��һ��Ԫ�ص�λ��
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
	T* _start; // ��ʾ�ռ���׵�ַ
	T* _finish; // ��ʾ���һ��Ԫ�صĽ���λ��
	T* _endOfStorage;// ��ʾ�ռ�Ľ���λ��
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