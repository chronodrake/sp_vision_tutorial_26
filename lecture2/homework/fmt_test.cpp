#include<fmt/core.h>
#include<fmt/format.h>
#include<string>

using std::string;
void fmtoutputstr(string output){
    fmt::print("{}", output);

}
int main(){

    string testoutput=fmt::format("{1}{1}{4}{5}{1}{4}\n","T","J","U","I","L","U");
    fmtoutputstr(testoutput);
    testoutput=fmt::format("{{pi}}={0:*^30.{1}f}",3.1415926,2);
    fmtoutputstr(testoutput);
    return 0;
}