#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <stack>
#include <queue>
#include <tuple>
#include <set>
#include <array>
#include <sstream>


using namespace std;


class Process
{
private:
	int faults;
	int hits;
	int frames;
	void initFrames();
	void initFrameVector();

public:
	Process();
	
	int clock_hand;
	int ref_ptr;
	
	vector<tuple<string,int>> frame_vector;
	vector<string> ref_vector;
	
	int getFaults();
	int getHits();
	int getFrames();
	
	void incrementFaults();
	void incrementHits();

	void initStuctures();
	void getPages(string);
	void CPR_Algo();
	void moveClockHand();
	void caseFault();
	void toggleChance(int);
	void printTable();
};


Process::Process()
{
	faults=0;
	hits=0;
	clock_hand = 0;
	ref_ptr = -1;
}

void Process::initFrames()
{
	cout << "Enter the number of frames" << endl;
	cin >> this->frames;
}

void Process::initFrameVector()
{
	for(int i=0;i<this->getFrames();i++)
	{
		this->frame_vector.emplace_back("_",0);
	}
}


void Process::initStuctures()
{
	this->initFrames();
	this->initFrameVector();
}

int Process::getFaults()
{
	return this->faults;
}

int Process::getHits()
{
	return this->hits;
}

int Process::getFrames()
{
	return this->frames;
}

void Process::incrementFaults()
{
	this->faults++;
}

void Process::incrementHits()
{
	this->hits++;
}

void Process::moveClockHand()
{
	this->clock_hand = (this->clock_hand+1) % this->frames;
}

void Process::toggleChance(int index = -1)
{
	if(index==-1) index = this->clock_hand;
	get<1>(this->frame_vector[index]) = 1 - get<1>(this->frame_vector[index]);
}

void Process::caseFault()
{
	this->incrementFaults();
	while(get<1>(this->frame_vector[this->clock_hand]))
	{
		this->toggleChance();
		this->moveClockHand();
	}
	get<0>(this->frame_vector[this->clock_hand]) = this->ref_vector[this->ref_ptr];
	this->moveClockHand();
}

void Process::CPR_Algo()
{
	while( ++(this->ref_ptr) < this->ref_vector.size() )
	{
		vector<tuple<string,int>>::iterator it = find(this->frame_vector.begin(),this->frame_vector.end(),make_tuple(this->ref_vector[this->ref_ptr],0));
		if(it != this->frame_vector.end())
		{
			this->incrementHits();
			this->toggleChance(distance(this->frame_vector.begin(),it));
		}
		else if(find(this->frame_vector.begin(),this->frame_vector.end(),make_tuple(this->ref_vector[this->ref_ptr],1)) != this->frame_vector.end())
		{
			this->incrementHits();
		}
		else
		{
			this->caseFault();
		}

		this->printTable();
	}
}

void Process::getPages(string ref_str)
{
	istringstream ss(ref_str);
	string page;
	while(ss>>page)
	{
		this->ref_vector.push_back(page);
	}
}

void Process::printTable()
{
	for(int i=0;i<this->getFrames();i++)
		cout << get<0>(this->frame_vector[i]) << "-" << get<1>(this->frame_vector[i]) << "\t\t";
	cout << this->clock_hand << endl;
}


int main()
{
	string ref_str;
	Process process;
	cout << "Enter reference string" << endl;
	getline(cin,ref_str);
	process.getPages(ref_str);
	process.initStuctures();

	process.CPR_Algo();
	
	cout << "Page faults : " << process.getFaults() << "\t Fault ratio : " << (float)process.getFaults() / process.ref_vector.size() << endl;
	cout << "Page hits : " << process.getHits() << "\t Hit ratio : " << (float)process.getHits() / process.ref_vector.size() << endl;
	
	return 0;
}