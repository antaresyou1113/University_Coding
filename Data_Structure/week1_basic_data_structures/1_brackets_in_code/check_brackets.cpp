#include <iostream>
#include <stack>
#include <string>
using namespace std;
struct Bracket {
    Bracket(char type, int position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main() {
    std::string text;
    getline(std::cin, text);
    int answer = -1;
    std::stack <Bracket> opening_brackets_stack;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            // Process opening bracket, write your code here
            Bracket *tmp = new Bracket(next, position+1);
            opening_brackets_stack.push(*tmp);
        }

        if (next == ')' || next == ']' || next == '}') {
            // Process closing bracket, write your code here
            if(! opening_brackets_stack.empty()){    
                if(!opening_brackets_stack.top().Matchc(next)){
                    answer = position + 1;
                    break;
                }
                opening_brackets_stack.pop();
            }
            else{
                answer = position + 1;
                break;
        }
    }
    }
    if(opening_brackets_stack.empty() && answer == -1){
        cout << "Success" << endl;
    }
    else{
        if(opening_brackets_stack.size() && answer == -1){
            answer = opening_brackets_stack.top().position;
        }
        cout << answer << endl;
    }
    // Printing answer, write your code here

    return 0;
}
