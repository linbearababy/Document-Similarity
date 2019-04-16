#include<iostream>
using std::ostream; using std::cout; using std::cin;
#include<vector>
using std::vector;
#include<string>
using std::string; using std::to_string;
//using std::erase;
#include<sstream>
using std::ostringstream;
#include <stdlib.h>
//using namespace std;
#include <algorithm>
using std::sort;
#include <fstream>
using std::ifstream;
#include <map>
using std::map;
#include <set>
using std::set;
using std::set_intersection;
using std::inserter; //using std::insert;
#include <cmath>
#include <algorithm>
#include "proj07_functions.h"

ostream& print_vector (ostream &out, const vector<string> &v){
    for(int i=0 ;i<v.size();++i){
        if(i < v.size()-1){
            out << v[i]<<',' ;
        }
        else{
            out << v[i];
        }
    }
    return out;
}
//print vector
string clean_word(const string& abs){
    string word="";
    for (auto i : abs ){
        if (isalpha(i)){
            word += tolower(i);
        }
    }
    return word;
}
//remove the unalphabet and space

vector<string> split(const string &s, char delim) {
    vector<string> word;
    long current, previous = 0;
    current = s.find(delim);
    while (current != std::string::npos) {
        word.push_back(s.substr(previous, current - previous));
        previous = current + 1;
        current = s.find(delim, previous);
    }
    word.push_back(s.substr(previous, current - previous));
    return word;
}
//split the value by space

ostream& print_map(ostream& out, const map_type& m){
    string words="";
    string words1="", words2, words3;
    for (auto a :m){
        words1=a.first;
        words2=to_string(a.second);
        words += words1+":"+words2+",";
    }
    
    words=words.substr(0,words.size()-1);
    out<<words;
    return out;
   
}
// print key and value of the map

bool process_words(map_type&m, string fl){
    vector<string> words;
    ifstream file;
    file.open(fl);
    string sent;
    if(file.is_open()){
        while(getline(file, sent)){
            words = split(sent);
            for(int i = 0; i < words.size(); i++){
                string op;
                op= clean_word(words[i]);
                m[op] += 1;
            }
        }
    }
    else{
        return false;
    }
    return true;
}
//get the numbe tor count of the map's key


double jaccard_similarity(const map_type &m1, const map_type &m2){
    string words="", words2="";
    set<string>a;
    set<string>b;
    set<string>c;
    double  count2,count3, num;
    for(auto i : m1){
        a.insert(i.first);
        
    }
    for(auto i2 : m2){
        b.insert(i2.first);
    }
    set_intersection(a.begin(),a.end(),b.begin(),b.end(),inserter(c,c.begin()));
    count2=a.size();
    count3=b.size();
    num= c.size()/(count2+count3-c.size());
    return num;
}
//get the jaccard similarity

double calc_norm_factor(const map_type &m1){
    vector<long> words;
    for (auto e : m1){
        words.push_back(e.second);
    }
    double sum_num=0;
    for (auto h : words){
        sum_num+=pow(h,2);
    }
    double nor_num=0;
    nor_num=sqrt(sum_num);
    return nor_num;
}
//get the normal factor



double cosine_similarity_tf(const map_type &m1, const map_type &m2){
    double factor1, factor2;
    factor1=calc_norm_factor(m1);
    factor2=calc_norm_factor(m2);
    set<string>a;
    map<string,long>map3,map4;
    map<string,vector<long>>c;
    for (auto i:m2){
        a.insert(i.first);
        map4[i.first]=i.second;
    }
    for (auto i:m1){
        a.insert(i.first);
        map3[i.first]=i.second;
    }
    //set_intersection(a.begin(),a.end(),b.begin(),b.end(),inserter(c,c.end()));
    double num1=0, num2=0,num3=0;
    for (auto h: a){
        if (map4.end() == map4.find(h)){
            c[h].push_back(0);
            c[h].push_back(map3[h]);
            
        }
        if(map4.end()!=map4.find(h) &&map3.find(h)!=map3.end()){
            c[h].push_back(map3[h]);
            c[h].push_back(map4[h]);
        }
        else{
            c[h].push_back(0);
            c[h].push_back(map4[h]);
        }
    }
    for (auto i: c){
        num1+=(i.second[0]/factor1)*(i.second[1]/factor2);
    }
    return num1;
    
}
// get the cosine similarity
