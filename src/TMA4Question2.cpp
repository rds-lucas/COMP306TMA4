#include <iostream>
#include <string>

using namespace std;

class Rodent
{
private:
	Rodent (const Rodent& noCopy) {}



protected:
	string name;



public:
	Rodent() : name("default") {}
	explicit Rodent(string& newName) : name(newName) {}  // explicit to avoid implicit conversion
	virtual ~Rodent() = default;

	virtual void eat() = 0;
	virtual void showName() = 0;
};

class Mouse : public Rodent
{
public:
	Mouse() : Rodent()
	{
		cout << "Created Mouse with name \"default!\"" << endl;
	}

	explicit Mouse(string newName) : Rodent(newName)
	{
		cout << "Created Mouse with name " << newName << "!" << endl;
	}

	~Mouse() override
	{
		cout << "Destroyed Mouse with name " << name << "!" << endl;
	}



	void eat() override
	{
		cout << "Mouse " << name << " eat!" << endl;
	}

	void showName() override
	{
		cout << "Hi! I'm Mouse " << name << "!" << endl;
	}
};

class Gerbil : public Rodent
{
public:
	Gerbil() : Rodent()
	{
		cout << "Created Gerbil with name \"default!\"" << endl;
	}

	explicit Gerbil(string newName) : Rodent(newName)
		{
			cout << "Created Gerbil with name " << newName << "!" << endl;
		}

	~Gerbil() override
	{
		cout << "Destroyed Gerbil with name " << name << "!" << endl;
	}



	void eat() override
	{
		cout << "Gerbil " << name << " eat!" << endl;
	}

	void showName() override
	{
		cout << "Hi! I'm Gerbil " << name << "!" << endl;
	}
};

class Hamster : public Rodent
{
public:
	Hamster() : Rodent()
	{
		cout << "Created Hamster with name \"default!\"" << endl;
	}

	explicit Hamster(string newName) : Rodent(newName)
		{
			cout << "Created Hamster with name " << newName << "!" << endl;
		}

	~Hamster() override
	{
		cout << "Destroyed Hamster with name " << name << "!" << endl;
	}



	void eat() override
	{
		cout << "Hamster " << name << " eat!" << endl;
	}

	void showName() override
	{
		cout << "Hi! I'm Hamster " << name << "!" << endl;
	}
};


int main()
{
	Rodent * rodents[10];
	rodents[0] = new Mouse("M0");
	rodents[1] = new Gerbil("G1");
	rodents[2] = new Hamster("H2");
	rodents[3] = new Mouse("M3");
	rodents[4] = new Gerbil("G4");
	rodents[5] = new Hamster("H5");
	rodents[6] = new Mouse("M6");
	rodents[7] = new Gerbil("G7");
	rodents[8] = new Hamster("H8");
	rodents[9] = new Gerbil("G9");

	cout << endl << endl << endl;

	for (auto & rodent : rodents)
	{
		rodent->showName();
		rodent->eat();
	}

	cout << endl << endl << endl;

	for (auto & rodent : rodents)
	{
		delete rodent;
	}

	return 0;
}