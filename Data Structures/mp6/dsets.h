/* Your code here! */
#pragma once

#include <vector>

class DisjointSets {

public: void addelements(int num);
public: int find(int elem);
public: void setunion(int a, int b);
public: int size(int elem);

private: std::vector<int> disjoint_set;

};
