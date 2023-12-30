#include <vector>
#include <iostream>
#include <time.h>
#include <map>
#include <algorithm>
#include <string>
#include <cstring>
using namespace std;
int main()
{
    //map <string, int> m;
    //map <type, type> name;
    //set<pair<string, int>> m;
    //m["privet"] = 5;

    // int n;
    //cin >> n;
    // map< string, int> people;
    // for (int i = 0; i < n ; ++i){
    // pair<strig,int> temp;
    // cin >> temp.first >>  temp.second;
    // people.insert(temp); или лучше использовать people.emplace(temp); или map[temp.first] = temp.second; а если people[temp.first] = temp.second; то будет перезапись
    
    
    // people ["word"] = "word2"



    int n;
    cin >> n;
    vector<pair<string, int>> people(n);
    for (int i = 0; i < n; ++i) {
        cin >> people[i].first >> people[i].second;
    }
   sort(people.begin(), people.end());
    for (auto& i : people) {
        cout << i.first << " " << i.second << endl;
    }
}
