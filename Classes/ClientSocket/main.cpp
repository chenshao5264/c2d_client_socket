#include <string>
#include <iostream>

#include "ByteConverter.h"

#include "ProtocolStruct.h"

using namespace std;



int main()
{
    Player player;
    player.age = 10;
    player.name = "chenshao";

    std::map<int, std::string> cards = { std::make_pair(1, "a"), std::make_pair(2, "b"), std::make_pair(3, "c") };
    player.cards = cards;

    ByteConvert buf;
    buf << player;

    Player p;
    buf >> p;

        /*
    ByteConvert buf;
    
    int a1 = 10;
    std::string a2 = "aabbcc";
    int a3 = 20;
    int a4[3] = { 1, 2, 3 };
    PackageArray<int> aa4((&a4[0]), 4);
    std::vector<std::string> a5 = { "a", "b", "c"};
    std::list<std::string> a6 = { "a", "b", "c" };
    std::deque<std::string> a7 = { "a", "b", "c" };
    std::map<int, std::string> a8 = { std::make_pair(1, "a"), std::make_pair(2, "b"), std::make_pair(3, "c") };
    std::set<std::string> a9 = { "a", "b", "c" };
    buf << a1 << a2 << a3 << aa4 << a5 << a6 << a7 << a8 << a9; 

    int b1 = 0;
    std::string b2 = "";
    int b3 = 0;
    int b4[4] = {};
    PackageArray<int> b44((&b4[0]), 4);
    std::vector<std::string> b5 = {};
    std::list<std::string> b6 = {};
    std::deque<std::string> b7 = {};
    std::map<int, std::string> b8 = {};
    std::set<std::string> b9 = {};
    buf >> b1 >> b2 >> b3 >> b44 >> b5 >> b6 >> b7 >> b8 >> a9;
     */
    
    system("pause");

    return 1;
}