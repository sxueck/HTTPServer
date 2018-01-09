#include "../hf/sxwlhead.h"

using namespace std;

extern int AccRequest(string*);

int main(){
	string sourceCode = "<input type=\"password\"></input>";
	AccRequest(&sourceCode);
}
