#ifndef CELL_H
#define CELL_H
#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
using namespace std;
class Gene{
private:
    string RNA;
    string DNA[2];
public:
    friend class Cell;

    void setRNA(string s);
    void setDNA(string s1,string s2);

    void make_DNA();

    void small_mutation_RNA(char a,char b,int n);
    void small_mutation_DNA(char a,char b,int n);

    void big_mutation_RNA(string s1,string s2);
    void big_mutation_DNA(string s1,string s2);

    void reverse_mutation_RNA(string s);
    void reverse_mutation_DNA(string s);
};
class Cell:public Gene{
public:
    vector<Gene>chro;

    void show();

    void receive_chro(int n);
    void die();
    void small_mutation(char a,char b,int n,int m);
    void big_mutation(string s1,int n,string s2,int m);
    void reverse_mutation(string s,int n);
    void palindrome(int n);
};
#endif