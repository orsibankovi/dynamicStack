#ifndef KHF02_V2_ZMLCHECKER_H
#define KHF02_V2_ZMLCHECKER_H

#include "DynamicStack.h"
#include <cstring>
#include <cctype>
using namespace std;


class ZMLChecker {
public:
    ZMLChecker();
    ~ZMLChecker();
    static bool checkInput(string input);
};

ZMLChecker::ZMLChecker() {

}

ZMLChecker::~ZMLChecker() {

}

bool ZMLChecker::checkInput(string input) {
    DynamicStack<string> stack = DynamicStack<string>();
    bool check = false;
    int pos2;
    string tag;
    int zml_count = 0;

    for (size_t i = 0; i < input.size()-4; ++i) {
        if (input[i]=='<' and input[i+1]=='Z' and input[i+2]== 'M' and input[i+3] == 'L' and input[i+4]=='>'){
            zml_count++;
        }
    }

    if (input.size()>=10 and input.substr(0, 5) == "<ZML>" and input.substr(input.size()-5)== "<ZML>" and zml_count == 2) {
        for (size_t i = 0; i < input.size()-4; i++){
            if (input[i] == '<'){
                if (isalpha(input[i+1]) and (toupper(input[i+1]) == input[i+1]) and isalpha(input[i+2]) and (toupper(input[i+2]) == input[i+2]) and isalpha(input[i+3]) and (toupper(input[i+3]) == input[i+3])){
                    pos2 = input.find(">", i);
                    tag = input.substr(i, pos2-i + 1);
                    if (tag.size()==5){
                        if (!stack.isEmpty() and stack.top()==tag){
                            stack.pop();
                        } else if (!stack.isEmpty() and stack.top()=="<OOO>" and tag != "<OOO>"){
                            { return false; }
                        } else {
                            stack.push(tag);
                            }
                    } else { return false; }
                } else { return false; }
            }
        }
        if (stack.isEmpty()){check = true;}
        stack.print();
    }
    return check;
}


#endif //KHF02_V2_ZMLCHECKER_H
