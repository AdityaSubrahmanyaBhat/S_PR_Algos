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
public:
	int fault;
	int hit;
	//initialise hit and fault count to zero
	Process()
	{
		fault=0;
		hit=0;
	}
	void Process::CLOCK(Process proc,string ref,int len,int n);
};


void Process::CLOCK(Process proc,string ref, int len, int n)
{
	//to keep track of second chances
	map<char, int> bits; 
	//clock_hand
	int clock_hand = 0;
	//vector to keep track of which processes are currently in the frames
	vector<char> frames;
	int i = -1;
	int char_count = 0;
	//first character is put into the frame
	frames.push_back(ref[0]);
	while (++i < len)
	{
		//if a hit occurs
		if (find(frames.begin(), frames.end(), ref[char_count]) != frames.end())
		{
			proc.hit++;
			//if the rbit of the process is 0
			if (!bits[ref[char_count]])
			{
				frames[clock_hand] = ref[char_count];
				clock_hand = (clock_hand + 1) % n;
			}
			//if the rbit of the process is 1
			else
			{
				for (int i = 0; i < n; i++)
				{
					if (bits[ref[char_count]])
					{
						bits[ref[char_count]]=0;
						clock_hand=(clock_hand+1)%n;
						continue;
					}
					frames[clock_hand]=ref[char_count];
					break;
				}
			}
		}
		//if a page fault occurs
		else
		{
			proc.fault++;
			frames[clock_hand] = ref[char_count];
			clock_hand = (clock_hand + 1) % n;
		}
		char_count++;
	}
	return;
}

vector<string> getPages(string ref_str)
{
	istringstream ss(ref_str);
	string page;
	vector<string> ref_vector;
	while(ss>>page)
	{
		ref_vector.push_back(page);
	}
	return ref_vector;
}



int main()
{
	string ref_str;
	vector<string> ref_vector;
	Process process;
	int n;
	cout << "Enter reference string" << endl;
	cin >> ref_str;
	cout << "Enter the number of frames" << endl;
	cin >> n;
	
	ref_vector = getPages(ref_str);

	process.CLOCK(process,ref_str, ref_str.size(), n);
	
	cout << "Page faults : " << process.fault << "   Fault ratio : " << (float)process.fault/ref_vector.size()<<endl;
	cout << "Page hits : " << process.hit << "   Hit ratio : " << (float)process.hit/ref_vector.size()<<endl;
	
	return 0;
}