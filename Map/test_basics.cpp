#include "Map.hpp"

#include <iostream>
#include <string>
#include <assert.h>


// test initializer_list
cs540::Map<int, std::string> num {
	{10, "ten"},
	{20, "twenty"},
	{30, "thirty"},
	{40, "forty"},
	{50, "fifty"},
	{60, "sixty"},
	{70, "seventy"},
	{80, "eighty"},
};

int test_basics()
{
	// lookup by key
	assert(num.at(10) == "ten");
	assert(num.at(80) == "eighty");
	
	// check out_of_range 
	bool out_of_rg = false;
    try {
        num.at(10000);
    } catch (std::out_of_range) {
        out_of_rg = true;
    }
    assert(out_of_rg);
	
	// find key 
	auto it1 = num.find(30);
    assert((*it1).second == "thirty");
	
	// erase
	num.erase(70);
	assert(num.size()==7);
	
	auto it2 = num.find(80);
	num.erase(it2);
	assert(num.size()==6);
	
	// copy and assignment 
    cs540::Map<int, std::string> copy_num{num};
	assert(copy_num.size()==6);

    cs540::Map<int, std::string> assign_num;
    assign_num = num;
	assert(assign_num.size()==6);
	
	
	// insert
 	num.insert({90, "ninety"});
	assert(num.at(90) == "ninety");

	num[100] = "hundred";
	assert(num.at(100) == "hundred");
	
	assert (num.empty()==false);
	
	// comparing operators
	assert(assign_num==copy_num);
	
	copy_num.erase(10);
	
	assert(copy_num<assign_num);
	assert(copy_num!=assign_num);
	
	// clear
	copy_num.clear();
	assert (copy_num.empty()==true);
	
	// Iterators
	int revCount=0,count=0;
	for (auto It = num.begin();It != num.end();++It) {
		count++;
    }
	assert (count==8);

	for (auto revIt = num.rbegin();revIt != num.rend();++revIt) {
		revCount++;
    }
	assert (revCount==8);

	cs540::Map<int, std::string> check_num_itr{num};
	for (auto It1 = check_num_itr.begin(),It2 = check_num_itr.begin();
		It1 != check_num_itr.end()&&It2 != check_num_itr.end();++It1,++It2) {
		assert(It1==It2);
		assert(((*It1).second!=(*It2).second)==false);
    }
	return 1;
}

int test_reverse()
{
	cs540::Map<int, int> map1;
	for(int i = 0; i <= 100; i++) {
		map1.insert(std::pair<int, int>(i,i));
	}
	
	cs540::Map<int, int> map2;
	for(int i = 100; i >= 0; i--) {
		map2.insert(std::pair<int, int>(i,i));
	}
	
	assert(map1==map2);
	return 1;
}

int test_multiple()
{
	cs540::Map<int, std::string> map3;
	map3.insert({1,"A"});
	map3.insert({2,"B"});
	map3.insert({4,"C"});
	map3.insert({2,"D"});
	map3.insert({1,"E"});
	assert(map3.size()==3);
	return 1;
}

int test_range()
{
	typedef std::pair<std::string, std::string> myPair;
	myPair data[] =
	{
		myPair("Tom", "Jerry"),
		myPair("Harry", "Potter"),
		myPair("Mr", "Bean"),
	};
	cs540::Map<std::string, std::string> map4;
	map4.insert(std::begin(data), std::end(data));
	auto i = map4.find("Tom");
	assert(i->first == "Tom");
	assert(i->second == "Jerry");
	i = map4.find("Gun");
	assert(i == map4.end());
	return 1;
}

int main() {

	test_basics();
	test_reverse();
	test_multiple();
	test_range();
	
	std::cout << "Completed successfully!" << std::endl;
	return 0;
}
