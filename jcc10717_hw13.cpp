
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;


class Organism {
public:
	//constructors
		//initializes an organism 
	Organism(int xLocationIn, int yLocationIn);

		//initializes the object with the symbol In
	Organism(char symbolIn);
		//no args.
	Organism();

	//accessor functs.
	char getSymbol() const;
	void getLocation(int &xLocationOut, int &yLocationOut) const ;
	bool getHasMoved();
	int getBreedTimer();

	//mutator functs.
	void setLocation(int xLocationIn, int yLocationIn);
	void setHasMoved(bool hasMovedIn);
	void setBreedTimer(int newBreedTimer);
	void incrementBreedTimer();

	//operator overload headers
	void operator =(const Organism& orgRHS);

	//functions
	virtual void move(Organism*** world, int& direction) =0;
	virtual void breed(Organism*** world, int& direction) = 0;
	virtual void starve(Organism*** world) = 0;
	//virtual bool checkMove(Organism*** world, const int direction) = 0;

private:
	int breedTimer;

	//position
	int xLocation;
	int yLocation;

	bool hasMoved;

	char symbol;
};

//organism contsructor defintions
Organism::Organism(int xLocationIn, int yLocationIn) {
	symbol = '-';
	breedTimer = 100;
	xLocation = xLocationIn;
	yLocation = yLocationIn;
	hasMoved = false;
}

Organism::Organism(char symbolIn) {
	symbol = symbolIn;
	breedTimer = 0;
	xLocation = 0;
	yLocation = 0;
	hasMoved = false;
}

//initializes an Organism with symbol - and x,y location of (0,0)
Organism::Organism() {
	symbol = '-';
	breedTimer = 0;
	xLocation = 0;
	yLocation = 0;
	hasMoved = false;

}

//accessor functs.
char Organism::getSymbol() const {
	return symbol;
}
void Organism::getLocation(int& xLocationOut, int& yLocationOut)const {
	xLocationOut = xLocation;
	yLocationOut = yLocation;
	
}
bool Organism::getHasMoved() {
	return hasMoved;
}
int Organism::getBreedTimer() {
	return breedTimer;
}

//mutator functs.

void Organism::setLocation(int xLocationIn, int yLocationIn) {
	xLocation = xLocationIn;
	yLocation = yLocationIn;
}
void Organism::setHasMoved(bool hasMovedIn) {
	hasMoved = hasMovedIn;
}
void Organism::setBreedTimer(int newBreedTimer) {
	breedTimer = newBreedTimer;
}
void Organism::incrementBreedTimer() {
	breedTimer += 1;
}


//operator definitions
void Organism::operator =(const Organism& orgRHS) {
	int xLoc,yLoc;

	symbol = orgRHS.symbol;
	this->setBreedTimer(orgRHS.breedTimer);
	orgRHS.getLocation(xLoc,yLoc);
	this->setLocation(xLoc,yLoc);



}

class Doodlebug: public Organism {

public:
	//constuctors
	Doodlebug();
	Doodlebug(int xLocationIn, int yLocationIn);
	Doodlebug( Doodlebug& bugIn);//copy constructor


	void move(Organism*** world, int& direction);
	void breed(Organism*** world, int& direction);
	void starve(Organism*** world);

	int getStarveTimer();
	void setStarveTimer(int newTime);


private:
	int starveTimer;
};

//doodlebug Constuctors
Doodlebug::Doodlebug():Organism('X') {
	starveTimer = 0;
}
Doodlebug::Doodlebug(int xLocationIn, int yLocationIn):Organism('X') {
	starveTimer = 0;
	setLocation(xLocationIn, yLocationIn);

}

//copy constructor
Doodlebug::Doodlebug( Doodlebug& bugIn) : Organism('X') {
	starveTimer = bugIn.starveTimer;
	
	int xTemp, yTemp;
	bugIn.getLocation(xTemp,yTemp);
	this->setLocation(xTemp,yTemp);

	int breedTimeTemp= bugIn.Organism::getBreedTimer();
	bugIn.Organism::setBreedTimer(breedTimeTemp);


	
}

//doodlebug functions
int Doodlebug::getStarveTimer() {
	return starveTimer;
}

void Doodlebug::setStarveTimer(int newTime) {
	starveTimer = newTime;
}

void Doodlebug::breed(Organism*** world, int& direction) {
	if (this == nullptr) {//do nothing
	}
	else {

		int xLocationCurrent;
		int yLocationCurrent;
		this->getLocation(xLocationCurrent, yLocationCurrent);

		int newXLoc;
		int newYLoc;


		if (this->getBreedTimer() == 8) {//only breed if 8 time steps have passed for this bug.
			if (direction == 1) {//move North
				newXLoc = (xLocationCurrent - 1);
				newYLoc = yLocationCurrent;

				if ((newXLoc >= 0) && (world[newXLoc][newYLoc] == nullptr)) {//TODO need to bring in value of 20
					world[newXLoc][newYLoc] = new Doodlebug(newXLoc, newYLoc);
					world[newXLoc][newYLoc]->setHasMoved(true);//setting the new ant move flag to true so it wont start counting this time step as a breeding step
					//set breed counter to 0
					this->setBreedTimer(0);
				}
				else {}//will do nothing if the direction it is trying to move is occupied or the end of the world..proof the world is flat??


			}
			else if (direction == 2) {//Move East
				newXLoc = xLocationCurrent;
				newYLoc = (yLocationCurrent + 1);
				//newYLoc = (yLocationCurrent);

				if ((newYLoc < 20) && (world[newXLoc][newYLoc] == nullptr)) {//TODO need to bring in value of 20
					world[newXLoc][newYLoc] = new Doodlebug(newXLoc, newYLoc);
					world[newXLoc][newYLoc]->setHasMoved(true);//setting the new ant move flag to true so it wont start counting this time step as a breeding step

					//set breed counter to 0
					this->setBreedTimer(0);
				}
			}
			else if (direction == 3) {//Move South
				newXLoc = (xLocationCurrent)+1;
				newYLoc = yLocationCurrent;

				if ((newXLoc < 20) && (world[newXLoc][newYLoc] == nullptr)) {//TODO need to bring in value of 20
					world[newXLoc][newYLoc] = new Doodlebug(newXLoc, newYLoc);
					world[newXLoc][newYLoc]->setHasMoved(true);//setting the new ant move flag to true so it wont start counting this time step as a breeding step

					//set breed counter to 0
					this->setBreedTimer(0);
				}
			}

			else {//(direction == 4) //Move West
				newXLoc = xLocationCurrent;
				newYLoc = (yLocationCurrent - 1);

				if ((newYLoc) >= 0 && (world[newXLoc][newYLoc] == nullptr)) {//TODO need to bring in value of 20
					world[newXLoc][newYLoc] = new Doodlebug(newXLoc, newYLoc);
					world[newXLoc][newYLoc]->setHasMoved(true);//setting the new ant move flag to true so it wont start counting this time step as a breeding step

					//set breed counter to 0
					this->setBreedTimer(0);
				}
			}
		}
		else if (this->getHasMoved() == true) {
			//Newly bred bugs will have the breeding count as a movement so that they dont get a breed counter the day of their birth
			//they need to warm up to things a little bit.

		}
		else {
			this->incrementBreedTimer();
		}//if not ready to breed increment up timer
	}
}
void Doodlebug::move(Organism*** world, int& direction) {
	//curently eating the ant and leaving a copy of itself there.

	int xLocationCurrent;
	int yLocationCurrent;
	this->getLocation(xLocationCurrent, yLocationCurrent);

	//these represent the coordinates of the spots around the doodlebug
	int xNorth = xLocationCurrent - 1, yNorth = yLocationCurrent;
	int xEast = xLocationCurrent, yEast = yLocationCurrent + 1;
	int xSouth = xLocationCurrent + 1, ySouth = yLocationCurrent;
	int xWest = xLocationCurrent, yWest = yLocationCurrent - 1;

	int newXLoc;
	int newYLoc;

	//creates an doodlebug Pointer named temp which is set equal to the current Ant object
	Doodlebug* temp = this;

	//could figure out how to randomize this later
	if ((xNorth >= 0) && (world[xNorth][yNorth] != nullptr) && world[xNorth][yNorth]->getSymbol() == 'o') {//eats bug to north
		//this might fail on the edges but i think it will read the if statement left to right and jump out after it fails the boundry check
		//cout << "eat";

		//this solves the issue of leaving a copy
		//i think the problem is i need to create my copy constructor.

		//killing ant
		world[xNorth][yNorth] = nullptr;
		
		//moving bug to its spot
		newXLoc = (xLocationCurrent - 1);
		newYLoc = yLocationCurrent;
		this->setLocation(newXLoc, newYLoc);
		world[newXLoc][newYLoc] = temp;

		world[xLocationCurrent][yLocationCurrent] = nullptr;
		//set move flag up
		world[newXLoc][newYLoc]->setHasMoved(true);

		this->setStarveTimer(-1);
	}
	else if ((yEast < 20) && (world[xEast][yEast] != nullptr) && world[xEast][yEast]->getSymbol() == 'o') {//eats bug to east
		//killing ant
		world[xEast][yEast] = nullptr;

		//moving bug to its spot
		newXLoc = xLocationCurrent;
		newYLoc = (yLocationCurrent + 1);
		this->setLocation(newXLoc, newYLoc);
		world[newXLoc][newYLoc] = temp;

		world[xLocationCurrent][yLocationCurrent] = nullptr;
		//set move flag up
		world[newXLoc][newYLoc]->setHasMoved(true);

		this->setStarveTimer(-1);

		//this code wasnt working, i think i was creating 2 pointers to the same object, needed big 3 to resolve but couldnt get it.
		 /*	world[xEast][yEast] = temp;
		world[xEast][yEast]->setHasMoved(true);
		world[xLocationCurrent][yLocationCurrent] = nullptr;*/
	}
	else if ((xSouth < 20) && (world[xSouth][ySouth] != nullptr) && world[xSouth][ySouth]->getSymbol() == 'o') {//eats bug to south
		//killing ant
		world[xSouth][ySouth] = nullptr;
		
		//moving bug to its spot
		newXLoc = (xLocationCurrent)+1;
		newYLoc = yLocationCurrent;
		world[newXLoc][newYLoc] = temp;
		this->setLocation(newXLoc, newYLoc);
		world[xLocationCurrent][yLocationCurrent] = nullptr;
		//set move flag up
		world[newXLoc][newYLoc]->setHasMoved(true);

		this->setStarveTimer(-1);


		/*	world[xSouth][ySouth] = temp;
			world[xSouth][ySouth]->setHasMoved(true);
			world[xLocationCurrent][yLocationCurrent] = nullptr;*/
	}

	else if (yWest >= 0 && (world[xWest][yWest] != nullptr) && world[xWest][yWest]->getSymbol() == 'o') {//eats bug to west
		//killing ant
		world[xWest][yWest] = nullptr;
	
		//moving bug to its spot
		newXLoc = xLocationCurrent;
		newYLoc = (yLocationCurrent - 1);
		this->setLocation(newXLoc, newYLoc);
		world[newXLoc][newYLoc] = temp;
		world[xLocationCurrent][yLocationCurrent] = nullptr;
		//set move flag up
		world[newXLoc][newYLoc]->setHasMoved(true);




		this->setStarveTimer(-1);



		/*world[yWest][yWest] = temp;
			world[yWest][yWest]->setHasMoved(true);
			world[xLocationCurrent][yLocationCurrent] = nullptr;*/
	}





	else {
		//If there is nothing to eat it will act like an ant	
		//			V__Code below is from ant::move__

		if (direction == 1) {//move North
			newXLoc = (xLocationCurrent - 1);
			newYLoc = yLocationCurrent;

			if ((newXLoc >= 0) && (world[newXLoc][newYLoc] == nullptr)) {//TODO need to bring in value of 20
				this->setLocation(newXLoc, newYLoc);
				world[newXLoc][newYLoc] = temp;

				world[xLocationCurrent][yLocationCurrent] = nullptr;
				//set move flag up
				world[newXLoc][newYLoc]->setHasMoved(true);
			}
		}
		else if (direction == 2) {//Move East
			newXLoc = xLocationCurrent;
			newYLoc = (yLocationCurrent + 1);
			if ((newYLoc < 20) && (world[newXLoc][newYLoc] == nullptr)) {//TODO need to bring in value of 20
				this->setLocation(newXLoc, newYLoc);
				world[newXLoc][newYLoc] = temp;
				world[xLocationCurrent][yLocationCurrent] = nullptr;
				//set move flag up
				world[newXLoc][newYLoc]->setHasMoved(true);
			}
		}
		else if (direction == 3) {//Move South

			newXLoc = (xLocationCurrent)+1;
			newYLoc = yLocationCurrent;

			if ((newXLoc < 20) && (world[newXLoc][newYLoc] == nullptr)) {//TODO need to bring in value of 20
				world[newXLoc][newYLoc] = temp;
				this->setLocation(newXLoc, newYLoc);
				world[xLocationCurrent][yLocationCurrent] = nullptr;
				//set move flag up
				world[newXLoc][newYLoc]->setHasMoved(true);
			}
		}

		else {//(direction == 4) //Move West
			newXLoc = xLocationCurrent;
			newYLoc = (yLocationCurrent - 1);

			if ((newYLoc) >= 0 && (world[newXLoc][newYLoc] == nullptr)) {//TODO need to bring in value of 20
				this->setLocation(newXLoc, newYLoc);
				world[newXLoc][newYLoc] = temp;
				world[xLocationCurrent][yLocationCurrent] = nullptr;
				//set move flag up
				world[newXLoc][newYLoc]->setHasMoved(true);
			}
		}
	}
}//includes eat
void Doodlebug::starve(Organism*** world) {

		if (this == nullptr) {//do nothing
		}
		else {

			int xLocationCurrent;
			int yLocationCurrent;
			this->getLocation(xLocationCurrent, yLocationCurrent);

			if (this->getStarveTimer() == 3) {//only breed if 8 time steps have passed for this bug.
				world[xLocationCurrent][yLocationCurrent] = nullptr;
			}
			
			else {
				this->starveTimer+=1;
			}//if not ready to starve increment up timer
		}
	}



class Ant : public Organism {

public:
	Ant();
	Ant(int xLocationIn, int yLocationIn);

	void move(Organism*** world, int& direction);
	void breed(Organism*** world, int& direction);
	void starve(Organism*** world) {};
	//bool checkMove(const Organism*** world, const int direction);


private:
};

//Ant constructor defs
Ant::Ant() :Organism('o') {
	setBreedTimer(0);
}
Ant::Ant(int xLocationIn, int yLocationIn) :Organism('o') {
	this->setLocation(xLocationIn, yLocationIn);
	
	setBreedTimer(0);
}

//bool Ant::checkMove(const Organism*** world, const int direction) {
//	//might not need this... overcomplicating??
//}

void Ant::move(Organism*** world, int& direction) {

	int xLocationCurrent;
	int yLocationCurrent;
	this->getLocation(xLocationCurrent, yLocationCurrent);

	int newXLoc;
	int newYLoc;

	//creates an Ant Pointer named temp which is set equal to the current Ant object
	Ant* temp = this;

	if (direction == 1) {//move North
		newXLoc=(xLocationCurrent - 1);
		newYLoc = yLocationCurrent;

		if ((newXLoc >= 0)&& (world[newXLoc][newYLoc]==nullptr)) {//TODO need to bring in value of 20
			this->setLocation(newXLoc, newYLoc);
			world[newXLoc][newYLoc] = temp;
			world[xLocationCurrent][yLocationCurrent] = nullptr;
			//set move flag up
			world[newXLoc][newYLoc]->setHasMoved(true);
		}
	}
	else if (direction == 2){//Move East
		newXLoc = xLocationCurrent;
		newYLoc = (yLocationCurrent+1);
		//newYLoc = (yLocationCurrent);


		if ((newYLoc < 20) && (world[newXLoc][newYLoc] == nullptr)) {//TODO need to bring in value of 20
			this->setLocation(newXLoc, newYLoc);
			world[newXLoc][newYLoc] = temp;
			world[xLocationCurrent][yLocationCurrent] = nullptr;
			//set move flag up
			world[newXLoc][newYLoc]->setHasMoved(true);
		}
	}
	else if (direction == 3) {//Move South
		   newXLoc = (xLocationCurrent)+1;
		   newYLoc = yLocationCurrent;

		if ((newXLoc < 20) && (world[newXLoc][newYLoc] == nullptr)) {//TODO need to bring in value of 20
			world[newXLoc][newYLoc] = temp;
			this->setLocation(newXLoc, newYLoc);
			world[xLocationCurrent][yLocationCurrent] = nullptr;
			//set move flag up
			world[newXLoc][newYLoc]->setHasMoved(true);
		}
	}

	else{//(direction == 4) //Move West
		newXLoc = xLocationCurrent;
		newYLoc = (yLocationCurrent-1);

		if ((newYLoc) >= 0 && (world[newXLoc][newYLoc] == nullptr)) {//TODO need to bring in value of 20
			this->setLocation(newXLoc, newYLoc);
			world[newXLoc][newYLoc] = temp;
			world[xLocationCurrent][yLocationCurrent] = nullptr;
			//set move flag up
			world[newXLoc][newYLoc]->setHasMoved(true);
		}
	}
}
void Ant::breed(Organism*** world, int& direction) {
	if (this == nullptr) {//do nothing
	}
	else{

		int xLocationCurrent;
		int yLocationCurrent;
		this->getLocation(xLocationCurrent, yLocationCurrent);

		int newXLoc;
		int newYLoc;


		if (this->getBreedTimer() == 3) {//only breed if 3 time steps have passed for this ant.
			if (direction == 1) {//move North
				newXLoc = (xLocationCurrent - 1);
				newYLoc = yLocationCurrent;

				if ((newXLoc >= 0) && (world[newXLoc][newYLoc] == nullptr)) {//TODO need to bring in value of 20
					world[newXLoc][newYLoc] = new Ant(newXLoc, newYLoc);
					world[newXLoc][newYLoc]->setHasMoved(true);//setting the new ant move flag to true so it wont start counting this time step as a breeding step
					//set breed counter to 0
					this->setBreedTimer(0);
				}
				else {}//will do nothing if the direction it is trying to move is occupied or the end of the world..proof the world is flat??


			}
			else if (direction == 2) {//Move East
				newXLoc = xLocationCurrent;
				newYLoc = (yLocationCurrent + 1);
				//newYLoc = (yLocationCurrent);

				if ((newYLoc < 20) && (world[newXLoc][newYLoc] == nullptr)) {//TODO need to bring in value of 20
					world[newXLoc][newYLoc] = new Ant(newXLoc, newYLoc);
					world[newXLoc][newYLoc]->setHasMoved(true);//setting the new ant move flag to true so it wont start counting this time step as a breeding step

					//set breed counter to 0
					this->setBreedTimer(0);
				}
			}
			else if (direction == 3) {//Move South
				newXLoc = (xLocationCurrent)+1;
				newYLoc = yLocationCurrent;

				if ((newXLoc < 20) && (world[newXLoc][newYLoc] == nullptr)) {//TODO need to bring in value of 20
					world[newXLoc][newYLoc]= new Ant(newXLoc, newYLoc);
					world[newXLoc][newYLoc]->setHasMoved(true);//setting the new ant move flag to true so it wont start counting this time step as a breeding step

					//set breed counter to 0
					this->setBreedTimer(0);
				}
			}

			else {//(direction == 4) //Move West
				newXLoc = xLocationCurrent;
				newYLoc = (yLocationCurrent - 1);

				if ((newYLoc) >= 0 && (world[newXLoc][newYLoc] == nullptr)) {//TODO need to bring in value of 20
					world[newXLoc][newYLoc] = new Ant(newXLoc, newYLoc);
					world[newXLoc][newYLoc]->setHasMoved(true);//setting the new ant move flag to true so it wont start counting this time step as a breeding step

					//set breed counter to 0
					this->setBreedTimer(0);
				}
			}
		}
		else if (this->getHasMoved() == true) {
			//Newly bred ants will have the breeding count as a movement so that they dont get a breed counter the day of their birth
			//they need to warm up to things a little bit.

		}
		else{
			this->incrementBreedTimer();
		}//if not ready to breed increment up timer
	}
}

Organism*** createWorld(int xSize, int ySize);

//general funct. defs.
void printWorld(Organism*** world, const int xSize, const int ySize);
void simulateWorld(Organism*** world, const int xSize, const int ySize);
//ants
void moveAllAnts(Organism*** world, const int xSize, const int ySize,int& direction);
void breedAllAnts(Organism*** world, const int xSize, const int ySize, int& direction);

//doodlebugs
void moveAllDoodlebugs(Organism*** world, const int xSize, const int ySize, int& direction);
void breedAllDoodlebugs(Organism*** world, const int xSize, const int ySize, int& direction);
void starveAllDoodlebugs(Organism*** world, const int xSize, const int ySize);

int main()
{
	Organism*** world = createWorld(20, 20);
	int direction;
	int xSize = 20, ySize = 20;
	int randX,randY;//will give a random number between 1 and 3

	srand(time(0));  // Initialize random number generator.
	int doodlebugCount = 0, antCount = 0;

	while (doodlebugCount<5) {//randomly places 5 doodlebugs into the world
		randX = (rand() % 20);//gives from 0 to 19
		randY = (rand() % 20);//gives from 0 to 19

		if (world[randX][randY] == nullptr) {
			world[randX][randY] = new Doodlebug(randX, randY);
			doodlebugCount += 1;
		}
		else {}//do nothing
	}

	while (antCount < 100) {//randomly places 100 Ants into the world
		randX = (rand() % 20);//gives from 0 to 19
		randY = (rand() % 20);//gives from 0 to 19

		if (world[randX][randY] == nullptr) {
			world[randX][randY] = new Ant(randX, randY);
			antCount += 1;
		}
		else {}//do nothing
	}

	printWorld(world, xSize, ySize);
	simulateWorld(world, xSize, ySize);

		
	}





	//// _________TESTING SImulate__________
	///*world[10][10] = new Ant(10, 10);
	//world[9][10] = new Ant(9, 10);
	//world[9][11] = new Ant(9, 11);*/
	//world[11][10] = new Doodlebug(11, 10);
	//world[11][12] = new Ant(11, 12);
	//world[10][9] = new Ant(10, 9);
	//printWorld(world, xSize, ySize);
	//simulateWorld(world, xSize, ySize);

	//this is basically saying the organism pointer at [0][0] should be set to a new organism object
  //	world[0][0] = new Organism();

	//cout << temp.getSymbol();
	//cout<<(world[0][0]->getSymbol());

Organism*** createWorld(int xSize, int ySize) {
	Organism*** world = new Organism** [xSize];
	for (int i = 0; i < xSize; i += 1) {
		world[i] = new Organism * [ySize];
		for (int j = 0; j < ySize; j += 1) {
			world[i][j] = nullptr;
			
		}
	}
	
	return world;
}
void printWorld(Organism*** world,const int xSize,const int ySize) {

	int bugCount = 0, antCount = 0;

	for (int i = 0; i < xSize; i += 1) {
		for (int j = 0; j < ySize; j += 1) {
			if (world[i][j] == nullptr){
				cout << " - ";
			}

			//will be where we check if its an ant or doodle
			else {
				if ((world[i][j])->getSymbol() == 'X') {
					cout << " X ";
					bugCount += 1;
				}
				else {
					cout << " o ";
					antCount += 1;
				}
			}
		}
		cout << endl;
	}
}
void simulateWorld(Organism*** world, const int xSize, const int ySize) {

	char userInput;
	int direction=1;

	cin.get(userInput);
	while (userInput == '\n') {
		
		moveAllDoodlebugs(world, xSize, ySize, direction);
		breedAllDoodlebugs(world, xSize, ySize, direction);
		starveAllDoodlebugs(world, xSize, ySize);
		
		moveAllAnts(world, xSize, ySize, direction);//after this point all ants will have moved and hasMoved is setback to false
		breedAllAnts(world, xSize, ySize, direction);
		printWorld(world, xSize, ySize);

		cin.get(userInput);
	}

}

void breedAllAnts(Organism*** world, const int xSize, const int ySize, int& direction) {
	srand(time(0));  // Initialize random number generator.

	for (int i = 0; i < xSize; i += 1) {
		for (int j = 0; j < ySize; j += 1) {
			direction = (rand() % 4) + 1;//will give a random number between 1 and 4
			if (world[i][j] == nullptr) {}//do nothing if NULL

			else if ((world[i][j]->getSymbol()) == 'o') {//if its an ant
				world[i][j]->breed(world, direction);	
			}
		}
	}
}
void moveAllAnts(Organism*** world, const int xSize, const int ySize, int& direction) {
	srand(time(0));  // Initialize random number generator.
	
	for (int i = 0; i < xSize; i += 1) {
		for (int j = 0; j < ySize; j += 1) {
			direction = (rand() % 4) + 1;//will give a random number between 1 and 4

			if (world[i][j] == nullptr) {}//do nothing if NULL

			else if ((world[i][j]->getSymbol()) =='o' && world[i][j]->getHasMoved() == false) {
				//if its an ant  
				world[i][j]->move(world, direction);
			}
		}
	}
	//reset the has moved flag
	for (int i = 0; i < xSize; i += 1) {
		for (int j = 0; j < ySize; j += 1) {
			if (world[i][j] != nullptr) {
				world[i][j]->setHasMoved(false);
			}
		}
	}
}

void moveAllDoodlebugs(Organism*** world, const int xSize, const int ySize, int& direction) {
	srand(time(0));  // Initialize random number generator.

	for (int i = 0; i < xSize; i += 1) {
		for (int j = 0; j < ySize; j += 1) {
			direction = (rand() % 4) + 1;//will give a random number between 1 and 4
			if (world[i][j] == nullptr) {}//do nothing if NULL

			else if ((world[i][j]->getSymbol()) == 'X' && world[i][j]->getHasMoved() == false) {
				//if its a Doodlebug
				world[i][j]->move(world, direction);
			}
			else {}
		}
	}
	//reset the has moved flag
	for (int i = 0; i < xSize; i += 1) {
		for (int j = 0; j < ySize; j += 1) {
			if (world[i][j] != nullptr) {
				world[i][j]->setHasMoved(false);
			}
		}
	}
}
void breedAllDoodlebugs(Organism*** world, const int xSize, const int ySize, int& direction) {
	srand(time(0));  // Initialize random number generator.

	for (int i = 0; i < xSize; i += 1) {
		for (int j = 0; j < ySize; j += 1) {
			direction = (rand() % 4) + 1;//will give a random number between 1 and 4
			if (world[i][j] == nullptr) {}//do nothing if NULL

			else if ((world[i][j]->getSymbol()) == 'X') {//if its an ant
				world[i][j]->breed(world, direction);	
			}
		}
	}
}
void starveAllDoodlebugs(Organism*** world, const int xSize, const int ySize) {

	for (int i = 0; i < xSize; i += 1) {
		for (int j = 0; j < ySize; j += 1) {

			if (world[i][j] == nullptr) {}//do nothing if NULL

			else if ((world[i][j]->getSymbol()) == 'X') {//if its an ant
				//starve here
				world[i][j]->starve(world);
			}
		}
	}
}





//create organism class
//create data structure
	//this will prob be ***pointers to pointers to pointers of my organisms
	//create check if end of board function

//create grid


//print grid
