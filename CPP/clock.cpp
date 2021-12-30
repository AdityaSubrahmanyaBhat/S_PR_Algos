#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

class Process
{
public:
    int fault;
    int hit;
    //initialise hit and fault count to zero
    Process(){
        fault=0;
        hit=0;
    }
};


Process CLOCK(Process proc,string ref, int len, int n)
{
    //to keep track of second chances
    map<char, int> bits; 
    //clock pointer
    int pointer = 0;
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
                frames[pointer] = ref[char_count];
                pointer = (pointer + 1) % n;
            }
            //if the rbit of the process is 1
            else
            {
                for (int i = 0; i < n; i++)
                {
                    if (bits[ref[char_count]]){
                        bits[ref[char_count]]=0;
                        pointer=(pointer+1)%n;
                        continue;
                    }
                    frames[pointer]=ref[char_count];
                    break;
                }
            }
        }
        //if a page fault occurs
        else
        {
            proc.fault++;
            frames[pointer] = ref[char_count];
            pointer = (pointer + 1) % n;
        }
        char_count++;
    }
    return proc;
}

int main()
{
    string str;
    Process process;
    int n;
    cout << "Enter reference string" << endl;
    cin >> str;
    cout << "Enter the number of frames" << endl;
    cin >> n;
    process=CLOCK(process,str, str.size(), n);
    cout<<"Page faults : "<<process.fault<<"   Fault ratio : "<<(float)process.fault/str.size()<<endl;
    cout<<"Page hits : "<<process.hit<<"   Hit ratio : "<<(float)process.hit/str.size()<<endl;
    return 0;
}