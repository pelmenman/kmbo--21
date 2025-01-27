﻿#include <iostream>
#include "memhacks.h"

using namespace std;

B::B() : b_s("It's b!") {
	for (auto i = 0; i < sizeof(data) / sizeof(data[0]); i++)
		data[i] = i * 2;
}

A::A() : a_s("It's a!") {}

/// <summary>
/// Выводит на экран адреса и размеры объекта типа <see cref="B"/> и его содержимого.
/// Можно модифицировать для собственных отладочных целей.
/// </summary>
/// <param name="b">Изучаемый объект</param>
void printInternals(const B& b) {
	const A* a = &b; // *a2 = a + 1;
	cout << "Address of b is 0x" << &b << ", address of b.a_s is 0x" << &b.a_s << ", address of b.b_s is 0x" << &b.b_s << endl;
	cout << "Size of A is " << sizeof(A) << ", size of B is " << sizeof(B) << endl;
	cout << "B string is '" << b.getBString() << "'" << endl;
	//cout << "B data: "; b.printData(cout); cout << endl;
}

/// <summary>
/// Извлекает значение <see cref="B::b_s"/> из текущего объекта.
/// Подразумевается, что текущий объект на самом деле представлено классом <see cref="B"/>.
/// </summary>
/// <returns>Значение B::b_s</returns>
std::string A::getBString() const { return *((std::string const*)(this + 1)); }


/// <summary>
/// Извлекает значения <see cref="A::a_s"/>, <see cref="B::b_s"/> и <see cref="B::data"/>
/// из текущего объекта и выводит их в текстовом виде в указанный выходной поток
/// с помощью адресной арифметики.
/// Подразумевается, что текущий объект на самом деле представлено классом <see cref="B"/>.
/// </summary>
/// 
void A::printData(std::ostream& os) {
	 os << "a_s: " << a_s << endl;
	 os << "b_s: " << getBString() << endl;
	 os << "b_data: ";
	 const float* bData = (const float*)( ((const string*)(this + 1)) + 1 );
	 for (auto i = 0; i < 7; i++) { os << *(bData + i) << " "; }
	 os << endl;
}

/// <summary>
/// Извлекает значения <see cref="A::a_s"/>, <see cref="B::b_s"/> и <see cref="B::data"/>
/// из текущего объекта и выводит их в текстовом виде в указанный выходной поток
/// с помощью виртуальных функций, предусмотренных в классе <see cref="A"/>.
/// </summary>
void A::printData2(std::ostream& os) {
	os << "a_s: " << a_s << endl;
	os << "b_s: " << getBstr() << endl;
	os << "b_data: ";
	for (auto i = 0; i < 7; i++)
	{
		os << *(getBData() + i)<< " ";
	}
	os << endl;
}

int main()
{
	B b;
	cout << "this is printData:" << endl;
	b.printData(cout);

	cout << endl;

	cout << "this is printData2:" << endl;
	b.printData2(cout);


	return 0;
}
