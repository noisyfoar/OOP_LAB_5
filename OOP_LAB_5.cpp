#include <iostream>
#include <typeinfo>
#include <memory>

using namespace std;

class Animal {
protected:
	string name = "Animal";
	string sound = "";
public:
	Animal() {
		cout << typeid(this).name() << " : constuctor\n";
	}

	virtual string classname() {
		return name;
	}

	virtual bool isA(string classname) {
		return classname == name;
	}

	virtual void makeSound() = 0;

	virtual ~Animal() {
		cout << typeid(this).name() << " : destructor\n";
	}
};


class Cat : public Animal {
	
protected:
	int lives = 9;
	void catchMouse() {
		cout << name << " went to catch a mouse\n";
	}

public:
	Cat() {
		name = "Cat";
		sound = "meow";
		cout << typeid(this).name() << " : constuctor\n";
	}

	virtual void move() {
		cout << name << " went somewhere\n";
	};

	int getLives() {
		return lives;
	}

	bool isA(string classname) override {
		return classname == name || Animal::isA(classname);
	}

	void getAnnoyed() {
		cout << name << " get annoyed by mouse\n";
		catchMouse();
	}

	void getBored() {
		cout << name << " get bored\n";
		move();
	}

	void makeSound() override {
		cout << name << " said " << sound << '\n';
	}
};

class CheshireCat : public Cat {
protected:
	void catchMouse() {
		cout << name << " went with a beautiful gait to catch a mouse\n";
	}
public:
	CheshireCat() {
		name = "Chechire Cat";
		lives = 8;
		cout << typeid(this).name() << " : constuctor\n";
	}

	void move() override {
		cout << name << " teleported somewhere\n";
	}

	void makeSound() override {
		cout << name << " said " << sound;
	}

	bool isA(string classname) override {
		return classname == name || Cat :: isA(classname);
	}
};

class Dog : public Animal {

};


int main() {
	/*
	1 - ok

	2 - base class - cat
		child - cheshirecat
		method1 - getannoyed
		method2 - catchmouse

	3 - base class - cat
		child - cheshirecat
		method1 - getbored
		method2 - move

	4 - base class - cat
		child - cheshirecat
		method1 - getbored

	*/
}