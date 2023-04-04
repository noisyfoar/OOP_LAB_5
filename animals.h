#pragma once
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
	Animal(const Animal& new_animal) {
		cout << typeid(this).name() << " : copy constuctor\n";
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

	string classname() override{
		return name;
	}

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
	string classname() override {
		return name;
	}
	void move() {
		cout << name << " teleported somewhere\n";
	}

	void makeSound() override {
		cout << name << " said " << sound;
	}

	bool isA(string classname) override {
		return classname == name || Cat::isA(classname);
	}
};

class Dog : public Animal {
public:
	void hideBone() {
		cout << name << " hid the bone\n";
	}
	Dog() {
		cout << typeid(this).name() << " : constuctor\n";
		name = "Dog";
	}

	string classname() override {
		return name;
	}
	bool isA(string classname) override {
		return classname == name || Animal::isA(classname);
	}
	void makeSound() {
		cout << name << " said " << " bow\n";
	}
};

void safely_type_conversion() {
	srand(time(NULL));
	Cat c;
	CheshireCat cc;
	if (cc.isA("Cat")) {
		c = cc;
	}

	const int zooSize = 30;
	Animal* zoo[zooSize];
	for (int i = 0; i < zooSize; ++i) {
		if (rand() % 2) {
			zoo[i] = new Cat();
		}
		else {
			zoo[i] = new Dog();
		}
	}

	for (int i = 0; i < zooSize; ++i) {
		Cat* c = dynamic_cast<Cat*>(zoo[i]);
		if (c != nullptr) {
			c->getAnnoyed();
			continue;
		}
		Dog* d = dynamic_cast<Dog*>(zoo[i]);
		if (d != nullptr) {
			d->hideBone();
		}
	}
}

void examples() {

	{
		/*
		1
		base class - cat
		child - cheshirecat
		method1 - getannoyed
		method2 - catchmouse

		в методе1 базового класса вызывается метод2,
		который определен в этом же классе как невиртуальный,
		у класса-потомка метод2 переопределен:
		что происходит при вызове метода1 у класса-потомка?
		*/
		cout << "1:\n";
		CheshireCat cc;
		cc.getAnnoyed();
	}

	{
		/*
		 2
		base class - cat
		child - cheshirecat
		method1 - getbored
		method2 - move

		в методе1 базового класса вызывается метод2,
		который определен в этом же классе как виртуальный,
		у класса-потомка метод2 переопределен:
		что происходит при вызове метода1 у класса-потомка?
		*/
		cout << "2:\n";
		CheshireCat cc;
		cc.getBored();
	}

	{
		/*
		3
		base class - cat
		child - cheshirecat
		method1 - getbored

		в базовом классе объявить метод невиртуальный,
		а в классе-потомке объявить метод с таким же именем:
		какой метод будет вызываться при обращении к объекту
		через указатель на базовый класс,
		через указатель на класс-потомок?
		*/
		cout << "3:\n";

		Cat* c;
		c->getBored();
		delete c;

		CheshireCat* c;
		c->getBored();
		delete c;
	}

	{
		/*
		4
		base class - cat
		child - cheshirecat
		method1 - move

		в базовом классе объявить метод виртуальный,
		а в классе-потомке объявить метод с таким же именем:
		какой метод будет вызываться при обращении к объекту 
		через указатель на базовый класс,
		через указатель на класс-потомок?
		*/
		cout << "4:\n";

		Cat* c;
		c->move();
		delete c;

		CheshireCat* c;
		c->move();
		delete c;
	}

}

void classnames() {
	Cat c;
	CheshireCat cc;
	if (c.classname() == cc.classname()) {//условие никогда не выполнится
		c = cc;
	}
}
void isInstances() {
	Cat c;
	CheshireCat cc;
	if (c.classname() == cc.classname()) {//условие никогда не выполнится
		c = cc;
	}
	if (cc.isA("Cat")) { //условие выполнятся
		c = cc;
	}
}

void not_safe_type_conversion() {
	Cat c;
	CheshireCat cc;
	c = static_cast<Cat>(cc);
	
}