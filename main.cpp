#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>

using namespace std;


// Zaid Ajaj / s4807561 / Informatica & Wiskunde

// data structures
struct Gift { int Price; string Name; };
struct Wishlist { int Budget; vector<string> Wishes; };

// global data
vector<Gift> available_gifts;

// Reads the giftstore into memory
vector<Gift> read_giftstore(string filename)
{   
    // the output
    vector<Gift> results;
    // input file stream
    ifstream inputFile(filename);
    // foreach line you read -> parse it!
    for (string line; getline(inputFile, line);) {
        // split on first space to get price and name
        int firstSpaceIndex = line.find_first_of(' ');
        if (firstSpaceIndex != -1) {

            string giftPrice = line.substr(0, firstSpaceIndex);
            string giftName = line.substr(firstSpaceIndex + 1, line.length() - firstSpaceIndex - 1);
            
            Gift gift;
            gift.Price = stoi(giftPrice.c_str()),
            gift.Name = giftName;

            results.push_back(gift);
        }
        
    }  

    return results;
}

// Reads a file and turns it into a Wishlist
Wishlist read_wishlist_from(string filename)
{
    Wishlist result;
    vector<string> wishes;
    ifstream inputFile(filename);
    bool readFirstLine = false;
    for (string line; getline(inputFile, line);) {
        if (!readFirstLine) {
            // first line is the budget
            result.Budget = stoi(line.c_str());
            readFirstLine = true;
        } else {
            // other lines are the wishes
            wishes.push_back(line);
        }
        
    }

    result.Wishes = wishes;
    return result;
    assert(result.Budget > 0 && result.Wishes.size() > 0);
}

// Computes a subset of gifts for a given wishlist and a budget
vector<string> gifts(vector<string> wishlist, int budgetLeft, int wishIndex, int giftIndex, vector<string> result)
{
    assert (wishIndex > -1 && giftIndex > -1 && budgetLeft > 0);

    if (wishIndex == wishlist.size()) 
    {
        // finished searching
        return result;
    }

    if (giftIndex == available_gifts.size()) 
    {
        // start over
        return gifts(wishlist, budgetLeft, wishIndex + 1, 0, result);
    }


    string wish = wishlist[wishIndex];
    Gift gift = available_gifts[giftIndex];

    if (wish == gift.Name) 
    {
        if (budgetLeft > gift.Price) 
        {
            // found a wish we can afford
            // add it to result
            // move on to next wish
            result.push_back(wish);
            return gifts(wishlist, budgetLeft - gift.Price, wishIndex + 1, 0, result);
        } 
        else 
        {
            // We don't enough money for this wish, move on to next wish
            // starting the search of gifts from beginning
            return gifts(wishlist, budgetLeft, wishIndex + 1, 0, result);
        }
    }
    else
    {
        // not the one we are looking for, move one to next gift
        return gifts(wishlist, budgetLeft, wishIndex, giftIndex + 1, result);
    }
}

// Helper function to be called for each name
void make_wish_come_true_for(string name) {
    string filename = name + ".txt";
    Wishlist wishlist = read_wishlist_from(filename);
    vector<string> initial;
    vector<string> gifts_received = gifts(wishlist.Wishes, wishlist.Budget, 0, 0, initial);

    cout << name << " will receive: " << endl;
    for(int i = 0; i < gifts_received.size(); i++) {
        cout << gifts_received[i] << endl;
    }
}

//// Results:
//Andrew will receive:
//cd A Darker Shade Of White van Navarone
//spel Mens erger je niet!
//boek In de ban van de ring - reisgenoten van J.R.R. Tolkien
//boek In de ban van de ring - de twee torens van J.R.R. Tolkien

//Belle will receive:
//speelgoed klei
//speelgoed kleurpotloden
//speelgoed stiften

//Chris will receive:
//spel Mens erger je niet!
//cd Nothing but the beat van David Guetta
//cd Synthesized van Junkie XL

//Desiree will receive:
//boek Fiese Ferien van J. Till
//boek Fette Ferien van J. Till
//boek Bitterschokolade van M. Pressler
//boek Crazy van B. Lebert
//dvd Brave van Pixar
//dvd Wall-E van Pixar

//Fabienne will receive:
//sport langlaufski
//spel Mens erger je niet!
//spel De kolonisten van Catan
//cd Evenwicht van Marco Borsato


int main()
{
    available_gifts = read_giftstore("giftstore.txt");
    
    string names[] = { "Andrew", "Belle", "Chris", "Desiree", "Fabienne" };

    for(int i = 0; i < 5; i++) {
        string name = names[i];
        make_wish_come_true_for(name);
        cout << endl;
    }

    return 0;
}