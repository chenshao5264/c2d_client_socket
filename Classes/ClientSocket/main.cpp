#include <string>
#include <iostream>

#include "ByteBuffer.h"

#include "ProtocolStruct.h"

using namespace std;



int main()
{
    Player player;
    player.age = 10;
    player.name = "chenshao";

    player.day = 1;

    std::map<int, std::string> cards = { std::make_pair(1, "a"), std::make_pair(2, "b"), std::make_pair(3, "c") };
    player.mapCards = cards;

    std::vector<std::string> vecCards = { "aaa", "bbb", "ccc" };
    player.vecCards = vecCards;

    std::list<std::string> listCards = { "aaa", "bbb", "ccc" };
    player.listCards = listCards;

    std::deque<std::string> dequeCards = { "aaa", "bbb", "ccc" };
    player.dequeCards = dequeCards;

    std::set<std::string> setCards;
    setCards.insert("aaa");
    setCards.insert("bbb");
    setCards.insert("ccc");
    player.setCards = setCards;
     
    CBuffer buf;
    buf << player;


    Player p;
    buf >> p;

    system("pause");

    return 1;
}