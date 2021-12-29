#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <string.h>
using namespace std;

class Process
{
public:
    int fault;
    int hit;

    Process(){
        fault=hit=0;
    }
};

Process CLOCK(Process proc,string ref, int len, int n)
{
    map<char, int> bits;
    int pointer = 0;
    vector<char> frames;
    int i = -1;
    int char_count = 0;
    frames.push_back(ref[0]);
    while (++i < len)
    {
        if (find(frames.begin(), frames.end(), ref[char_count]) != frames.end())
        {
            proc.hit++;
            if (!bits[ref[char_count]])
            {
                frames[pointer] = ref[char_count];
                pointer = (pointer + 1) % n;
            }
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