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
	void initPageChance();

public:
	Process();
	
	int clock_hand = 0;
	int ref_ptr = 0;
	
	vector<string> frame_vector;
	vector<string> ref_vector;
	map<string,int> pageChance;
	
	int getFaults();
	int getHits();
	int getFrames();
	
	void incrementFaults();
	void incrementHits();

	void initStuctures();
	void getPages(string ref_str);
	void CPR_Algo();
	void caseFault();
	void caseHit();
	void toggleChance();
	void moveClockHand();
};


Process::Process()
{
	faults=0;
	hits=0;
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
		this->frame_vector.push_back("");
	}
}

void Process::initPageChance()
{
	vector<string>::iterator it;
	for(it=this->frame_vector.begin();it!=this->frame_vector.end();it++)
	{
		this->pageChance.insert(pair<string,int>(*it,0));
	}
}

void Process::initStuctures()
{
	this->initFrames();
	this->initFrameVector();
	this->initPageChance();
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

void Process::toggleChance()
{
	this->pageChance.at(this->frame_vector[this->ref_ptr]) = 1 - this->pageChance.at(this->frame_vector[this->ref_ptr]);
}

void Process::caseFault()
{
	this->incrementFaults();
	while(this->pageChance.at(this->frame_vector[this->clock_hand]))
	{
		this->toggleChance();
		this->moveClockHand();
	}
	this->frame_vector[this->clock_hand] = this->ref_vector[this->ref_ptr];
	this->moveClockHand();
}

void Process::caseHit()
{
	this->incrementHits();
	if(!this->pageChance.at(this->frame_vector[this->ref_ptr]))
	{
		this->toggleChance();
	}
}

void Process::CPR_Algo()
{
	while( (this->ref_ptr)++ < this->ref_vector.size() )
	{
		if(find(this->frame_vector.begin(),this->frame_vector.end(),this->ref_vector[this->ref_ptr]) != this->frame_vector.end())
		{
			this->caseHit();
		}
		else
		{
			this->caseFault();
		}
	}
}

// void Process::CLOCK(Process proc,string ref, int len, int n)
// {
// 	while (++i < len)
// 	{
// 		//if a hit occurs
// 		if (find(frames.begin(), frames.end(), ref[i]) != frames.end())
// 		{
// 			proc.hit++;
// 			//if the rbit of the process is 0
// 			if (!bits[ref[i]])
// 			{
// 				frames[clock_hand] = ref[i];
// 				clock_hand = (clock_hand + 1) % n;
// 			}
// 			//if the rbit of the process is 1
// 			else
// 			{
// 				for (int i = 0; i < n; i++)
// 				{
// 					if (bits[ref[i]])
// 					{
// 						bits[ref[i]]=0;
// 						clock_hand=(clock_hand+1)%n;
// 						continue;
// 					}
// 					frames[clock_hand]=ref[i];
// 					break;
// 				}
// 			}
// 		}
// 	}
// 	return;
// }

void Process::getPages(string ref_str)
{
	istringstream ss(ref_str);
	string page;
	while(ss>>page)
	{
		this->ref_vector.push_back(page);
	}
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
	
	cout << "Page faults : " << process.getFaults() << "\t Fault ratio : " << (float) (process.getFaults() / process.ref_vector.size()) << endl;
	cout << "Page hits : " << process.getFaults() << "\t Hit ratio : " << (float) (process.getHits() / process.ref_vector.size()) << endl;
	
	return 0;
}