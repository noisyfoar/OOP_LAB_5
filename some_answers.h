#pragma once
#include<iostream>
#include<memory>

using namespace std;

class Msg {
protected:
	string msg = "";
public:
	virtual string print_hello() {
		cout << "virtual method of base class\n";
		return "hello!";
	}
	void setMsg(string new_msg) {
		cout << "default method of base class\n";
		msg = new_msg;
	}
	virtual ~Msg() {
		cout << typeid(this).name() << " : destructor\n";
	}
};

class BracketsMsg : public Msg {
public:
	string print_hello() override{
		cout << "overrided method of child class\n";
		return "(" + Msg::print_hello() + ")";
	}
	void setMsg(string new_msg) {
		cout << "inherited method of child class\n";
		msg = "(" + new_msg + ")";
	}
	~BracketsMsg() {
		cout << typeid(this).name() << " : destructor\n";
	}
};


void unq(unique_ptr<int> p) {
	cout << "unq()\n";
}

shared_ptr<int> shrd(shared_ptr<int> p) {
	cout << "shrd()\n";
	return p;
}

void overrided_and_inherited() {
	BracketsMsg br_msg;
	br_msg.Msg::print_hello();
	br_msg.print_hello();
	br_msg.Msg::setMsg("1");
	br_msg.setMsg("1");
}

void definition_virtual() {
	{
		BracketsMsg msg;
		msg.setMsg("1");
	}
	cout << "------------\n";
	{
		Msg* msg_p = new BracketsMsg();
		//убрать virtual в msg для примера
		delete msg_p;
	}
}

void smart_pointers() {
	unique_ptr<int> unqObj = make_unique<int>();
	unq(move(unqObj));  //передать в функцию можно только с помощью (move)
	unique_ptr<int> unqObj2(new int());
	//нельзя записать один unique_ptr в другой

	cout << '\n';

	shared_ptr<int> shrdObj(new int());
	shrdObj = shrd(shrdObj);
	//при передаче счетчик ссылок увеличится, но адрес будет один и тот же
	shared_ptr<int> shrdObj2 = shrdObj;
	shrdObj2 = shrd(shrdObj2);
}