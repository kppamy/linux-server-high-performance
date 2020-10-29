#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;

// 1472. Design Browser History
// 196 ms, faster than 65.57% o
class BrowserHistory
{
public:
    BrowserHistory(string homepage)
    {
        visit(homepage);
    }

    void visit(string url)
    {
        if (cursor > -1)
            cout << "you are in:  " << history[cursor];
        auto itr = map.find(url);
        if (itr == map.end())
        {
            if (cursor == size - 1)
            {
                history.push_back(url);
                map[url] = size;
                cursor = size;
                cout << " visit " << url << " at: " << cursor << endl;
                size++;
                return;
            }
            else
            {
                cursor++;
                history[cursor] = url;
            }
        }
        else
            cursor = itr->second;
        for (int i = cursor + 1; i < size; i++)
        {
            map.erase(history[i]);
        }
        size = cursor + 1;
        cout << " visit " << url << " at: " << cursor << endl;
        history.resize(size);
    }

    string back(int steps)
    {
        cout << "you are in:  " << history[cursor];
        int target = cursor - steps;
        target = (target >= 0) ? target : 0;
        cursor = target;
        cout << ", moving back" << steps << " steps to " << history[cursor] << endl;
        return history[cursor];
    }

    string forward(int steps)
    {
        cout << "you are in:  " << history[cursor];
        int target = cursor + steps;
        target = (target + 1 > size) ? size - 1 : target;
        cursor = target;
        cout << ", moving forward  " << steps << " steps to :  " << history[cursor] << endl;
        return history[cursor];
    }

private:
    unordered_map<string, int> map;
    vector<string> history;
    int cursor = -1;
    int size = 0;
};

int main(int argc, char const *argv[])
{

    BrowserHistory *browserHistory = new BrowserHistory("leetcode.com");
    browserHistory->visit("google.com");   // You are in "leetcode.com". Visit "google.com"
    browserHistory->visit("facebook.com"); // You are in "google.com". Visit "facebook.com"
    browserHistory->visit("youtube.com");  // You are in "facebook.com". Visit "youtube.com"
    browserHistory->back(1);               // You are in "youtube.com", move back to "facebook.com" return "facebook.com"
    browserHistory->back(1);               // You are in "facebook.com", move back to "google.com" return "google.com"
    browserHistory->forward(1);            // You are in "google.com", move forward to "facebook.com" return "facebook.com"
    browserHistory->visit("linkedin.com"); // You are in "facebook.com". Visit "linkedin.com"
    browserHistory->forward(2);            // You are in "linkedin.com", you cannot move forward any steps.
    browserHistory->back(2);               // You are in "linkedin.com", move back two steps to "facebook.com" then to "google.com". return "google.com"
    browserHistory->back(7);               // You are in "google.com", you can move back only one step to "leetcode.com". return "leetcode.com"

    browserHistory->visit("google.com");   // You are in "leetcode.com". Visit "google.com"
    browserHistory->visit("facebook.com"); // You are in "google.com". Visit "facebook.com"
    browserHistory->visit("youtube.com");  // You are in "facebook.com". Visit "youtube.com"
    browserHistory->back(1);               // You are in "youtube.com", move back to "facebook.com" return "facebook.com"
    browserHistory->visit("google.com");   // You are in "leetcode.com". Visit "google.com"
    browserHistory->forward(1);            // You are in "youtube.com", move back to "facebook.com" return "facebook.com"
    browserHistory->back(3);               // You are in "youtube.com", move back to "facebook.com" return "facebook.com"

    browserHistory->visit("google.com");   // You are in "leetcode.com". Visit "google.com"
    browserHistory->visit("facebook.com"); // You are in "google.com". Visit "facebook.com"
    browserHistory->visit("youtube.com");  // You are in "facebook.com". Visit "youtube.com"
    browserHistory->visit("leetcode.com"); // You are in "facebook.com". Visit "youtube.com"
    browserHistory->back(1);               // You are in "youtube.com", move back to "facebook.com" return "facebook.com"
    browserHistory->forward(1);            // You are in "youtube.com", move back to "facebook.com" return "facebook.com"
    return 0;
}
