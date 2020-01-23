//: TMA4Question2.cpp

/**
 * Title: TMA4Question2.cpp
 * Description:
 *       An inheritance hierarchy of Rodents.
 * Date: January 20, 2020 
 * Author: Tommy Wu
 */

/**
 * DOCUMENTATION
 *
 * Program Purpose:
 *      1. Create 10 Rodents of either Mouse, Gerbil, Hamster type
 *      2. Call the overloaded functions
 *
 * Compile: clang++ TMA4Question2.cpp -o TMA4Question2
 * Execution : ./TMA4Question2
 */

/**
 * No test available for a fully static program.
 * 
 * The program should generate following output from stdout:
 * Created Mouse with name M0!
 * Created Gerbil with name G1!
 * Created Hamster with name H2!
 * Created Mouse with name M3!
 * Created Gerbil with name G4!
 * Created Hamster with name H5!
 * Created Mouse with name M6!
 * Created Gerbil with name G7!
 * Created Hamster with name H8!
 * Created Gerbil with name G9!
 * 
 * 
 * 
 * Hi! I'm Mouse M0!
 * Mouse M0 eat!
 * Hi! I'm Gerbil G1!
 * Gerbil G1 eat!
 * Hi! I'm Hamster H2!
 * Hamster H2 eat!
 * Hi! I'm Mouse M3!
 * Mouse M3 eat!
 * Hi! I'm Gerbil G4!
 * Gerbil G4 eat!
 * Hi! I'm Hamster H5!
 * Hamster H5 eat!
 * Hi! I'm Mouse M6!
 * Mouse M6 eat!
 * Hi! I'm Gerbil G7!
 * Gerbil G7 eat!
 * Hi! I'm Hamster H8!
 * Hamster H8 eat!
 * Hi! I'm Gerbil G9!
 * Gerbil G9 eat!
 * 
 * 
 * 
 * Destroyed Mouse with name M0!
 * Destroyed Gerbil with name G1!
 * Destroyed Hamster with name H2!
 * Destroyed Mouse with name M3!
 * Destroyed Gerbil with name G4!
 * Destroyed Hamster with name H5!
 * Destroyed Mouse with name M6!
 * Destroyed Gerbil with name G7!
 * Destroyed Hamster with name H8!
 * Destroyed Gerbil with name G9!
 */

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
} ///:~