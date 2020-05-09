#include <iostream>
// to disable the RTTI -fno-rtti
// g++ -fno-rtti RTTI.cpp -o RTTI
class Animal{
	//virtual void dummy(){}
	};

class StrayCat : public Animal
{
	public:
		void meow(){std::cout<<"meoww"<<std::endl;}
};

class Lion : public Animal {};

void speak(Animal* animalPtr)
{
	StrayCat* catPtr = (StrayCat*)animalPtr;
	//StrayCat* catPtr = dynamic_cast<StrayCat*>(animalPtr);
	//if(catPtr) 
	catPtr->meow();
	//else{std::cout<<"Related instance "<<
	//       "has no meow"<<std::endl;}
}

int main()
{
	Animal* animalPtr = new Animal;
	StrayCat* catPtr = new StrayCat;
	Lion* lionPtr = new Lion;
	std::cout<<"for animal ptr"<<std::endl;
	speak(animalPtr);
	std::cout<<"for straycat ptr"<<std::endl;
	speak(catPtr);
	std::cout<<"for lionPtr"<<std::endl;
	speak(lionPtr);

	return 0;
}
