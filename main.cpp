#include <iostream>
#include <filesystem>
#include "woodpecker.hpp"
#include "ZMLChecker.h"

TEST("DynamicStack int Test",1) {
    DynamicStack<int> *dynamicStack = new DynamicStack<int>();
    CHECK_EQ(1, dynamicStack->isEmpty());
    for(int i=0;i<10;i++){
        dynamicStack->push(i);
    }
    CHECK_EQ(0, dynamicStack->isEmpty());
    CHECK_EQ(9,dynamicStack->top());
    dynamicStack->pop();
    CHECK_EQ(8, dynamicStack->pop());
    delete dynamicStack;
}
TEST("DynamicStack string Test", 1){
    DynamicStack<string> *dynamicStack2 = new DynamicStack<string>();
    for(int i=0;i<10;i++){
        dynamicStack2->push("string - " + to_string(i));
    }
    CHECK_EQ("string - 9",dynamicStack2->top());
    dynamicStack2->pop();
    CHECK_EQ("string - 8", dynamicStack2->pop());
    delete dynamicStack2;
}
TEST("ZMLChecker ROOT ZML TAG CHECK",1) {
    ZMLChecker checker = ZMLChecker();
    CHECK_EQ(0,checker.checkInput("no tag"));
    CHECK_EQ(0,checker.checkInput("<AAA>no zml tag<AAA>"));
    CHECK_EQ(1,checker.checkInput("<ZML><ZML>"));
    CHECK_EQ(1,checker.checkInput("<ZML>valid zml string<ZML>"));
    CHECK_EQ(0,checker.checkInput("<ZML><AAA>not valid<AAA><ZML><ZML>only one root allowed<ZML>"));
}
TEST("ZMLChecker BASIC TAG CHECK",1) {
    ZMLChecker checker = ZMLChecker();
    CHECK_EQ(0,checker.checkInput("<ZML><123>numbers are not tags<123><ZML>"));
    CHECK_EQ(0,checker.checkInput("<ZML><abc>not capital<abc><ZML>"));
    CHECK_EQ(0,checker.checkInput("<ZML><&*/>special characters<&*/><ZML>"));
    CHECK_EQ(0,checker.checkInput("<ZML><AAAA>length<AAAA><ZML>"));
    CHECK_EQ(0,checker.checkInput("<ZML><badTags>whatever<badTags<3v3NW0r._se><><><>random string <3v3NW0r._se><ZML"));
}
TEST("ZMLChecker NESTED TAGS CHECK",1) {
    ZMLChecker checker = ZMLChecker();
    CHECK_EQ(1,checker.checkInput("<ZML>1<AAA>2<BBB>3valid nested3<BBB>2<AAA>1<ZML>"));
    CHECK_EQ(0,checker.checkInput("<ZML>invalid nested<AAA><BBB><AAA><BBB><ZML>"));
    CHECK_EQ(0,checker.checkInput("<ZML><AAA>invalid<AAA><AAA><ZML>"));
    CHECK_EQ(1, checker.checkInput("<ZML><AAA>a text<AAA>valid<BBB>b text<BBB><ZML>"));
}
TEST("ZMLChecker <OOO> TAG CHECK",1) {
    ZMLChecker checker = ZMLChecker();
    CHECK_EQ(1, checker.checkInput("<ZML><AAA><OOO>last tag<OOO><AAA><ZML>"));
    CHECK_EQ(0, checker.checkInput("<ZML><AAA><OOO><XXX>error<XXX><OOO><AAA><ZML>"));
    CHECK_EQ(1, checker.checkInput("<ZML><AAA><BBB><OOO><OOO><BBB><OOO>multiple ooo<OOO><CCC><DDD><DDD><CCC><AAA><ZML>"));
}
TEST("ZMLChecker LONG",1) {
    ZMLChecker checker = ZMLChecker();
    CHECK_EQ(1, checker.checkInput("<ZML><AAA><BBB><CCC><OOO>some<OOO><CCC><BBB><OOO>body<OOO><CCC><DDD><DDD><CCC>...<AAA><ZML>"));
    CHECK_EQ(1, checker.checkInput("<ZML><AAA><BBB><CCC><DDD><EEE><FFF><GGG><HHH><PPP>hardcode this I dare you<PPP><QQQ><QQQ><RRR><RRR><SSS>random long text with some weird text in it |Ä&@}}Đ[]|ÄÍ$ß÷¤×°`ˇ^°˘´˝¸¨<SSS><HHH><GGG><FFF><EEE><DDD><CCC><BBB><AAA><ZML>"));
    CHECK_EQ(0,checker.checkInput("<ZML><AAA>never<AAA><BBB><OOO>gonna<OOO><BBB><OOO>give<OOO><AAA>you<AAA><UUU><ZML>up<ZML><UUU><ZML>"));
}
TEST("EXTRAS_WHITESPACE",1) {
    ZMLChecker checker = ZMLChecker();
    CHECK_EQ(0, checker.checkInput("               <ZML>wh i te sp a ce begin<ZML>"));
    CHECK_EQ(0, checker.checkInput("<ZML>wh i te sp a ce end<ZML>     "));
    CHECK_EQ(0, checker.checkInput("               <ZML>wh i te sp a ce both   <ZML>    "));
}
TEST("EXTRAS_ALLKINDSOFTAGS",1) {
    ZMLChecker checker = ZMLChecker();
    CHECK_EQ(0,checker.checkInput("<ZML><<AA><<AA><ZML>"));
    CHECK_EQ(0,checker.checkInput("<ZML><<<A><<<A><ZML>"));
    CHECK_EQ(0,checker.checkInput("<ZML><&&&><&&&><ZML>"));
    CHECK_EQ(0,checker.checkInput("<ZML><***><***><ZML>"));
    CHECK_EQ(0,checker.checkInput("<ZML><<<>>><ZML>"));
}


WOODPECKER_TEST_MAIN(-1, -1)

