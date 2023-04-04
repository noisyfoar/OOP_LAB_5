#pragma once
#include <iostream>
#include <typeinfo>

using namespace std;


class Base {
public:
	Base() {
		cout << typeid(this).name() << " : default constuctor \n";
	};
	Base(Base* obj) {
		cout << typeid(this).name() << " : copy constuctor * \n";
	};
	Base(Base& obj) {
		cout << typeid(this).name() << " : copy constuctor & \n";
	};
	~Base() {
		cout << typeid(this).name() << " : destructor" << '\n';
	};
};

class Desc : public Base {
public:
	Desc() {
		cout << typeid(this).name() << " : default constuctor \n";
	};
	Desc(Base* obj) {
		cout << typeid(this).name() << " : copy constuctor * \n";
	};
	Desc(Base& obj) {
		cout << typeid(this).name() << " : copy constuctor & \n";
	};
	~Desc() {
		cout << typeid(this).name() << " : destructor" << '\n';
	};
};

void func1(Base obj) {

	cout << "func1(Base obj)\n";
}

void func2(Base* obj) {
	cout << "func2(Base* obj)\n";
}

void func3(Base& obj) {
	cout << "func3(Base& obj)\n";
}

Base func1() {
	cout << "Base func1()\n";
	Base obj;
	return obj;
}

Base* func2() {
	cout << "Base* func2()\n";
	Base obj;
	return &obj;
}

Base& func3() {
	cout << "Base& func3()\n";
	Base obj;
	return obj;
}

Base func4() {
	cout << "Base func4()\n";
	Base* obj = new Base();
	return *obj;
}

Base* func5() {
	cout << "Base* func5()\n";
	Base* obj = new Base();
	return obj;
}

Base& func6() {
	cout << "Base& func6\n";
	Base* obj = new Base();
	return *obj;
}

void base() {
	Base obj = NULL;
	Base* obj_p = new Base();
	cout << '\n';
	func1(obj);  //компилятор создаёт копию исходного объекта с помощью конструктора копирования, а потом его удаляет 
	func2(&obj);  //функция работает с исходным объектом
	func3(obj);   //функция работает с исходным объектом
	cout << '\n';

	func1(*obj_p); //компилятор создаёт копию исходного объекта с помощью конструктора копирования
	func2(obj_p);
	func3(*obj_p);
	cout << '\n';

	delete obj_p;

	cout << "\n\n---------------------\n\n";

	Base obj1;
	cout << '\n';

	obj1 = func1();  //внутри ф-ции создается объект obj копируется в obj1, затем удаляется
	cout << '\n';
	obj1 = func2();  //в переменную складывается адрес локального объекта, который уже уничтожен
	cout << '\n';
	obj1 = func3();  //в переменную складывается имя объекта, который уже уничтожен
	cout << '\n';
	obj1 = func4();  //создается объект obj, туда копируется созданный "на куче" объект, копируется в obj1, но не удаляется созданный "на куче" объект
	cout << '\n';
	obj1 = func5();  //создаётся динамический объект и его адрес из функции возвращается и помещается в переменную. Не забыть вовремя удалить obj1
	cout << '\n';
	obj1 = func6();  //создаётся динамический объект и его имя назначается ссылке o6 после выхода из функции . Не забыть вовремя удалить obj1
	cout << '\n';
}