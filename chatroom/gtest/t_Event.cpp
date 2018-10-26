#include "../Event.cpp"
#include <gtest/gtest.h>
class T_Event : public testing::Test {
protected:
    static void SetUpTestCase() {

    }
    static void TearDownTestCase() {

    }
};

TEST_F(T_Event, other_tool) {
    // split fucntion
    Event *T = new Event();
    string a("abc");
    string b("bce");
    vector<string> vs = T->split(a, b);
    EXPECT_EQ(0, vs.size());
    
    a = "abcd";
    b = "bc";
    vs = T->split(a, b);
    EXPECT_EQ("a", vs[0]);
    EXPECT_EQ("d", vs[1]);

    a = "1,2,3";
    b = ",";
    vs = T->split(a, b);
    EXPECT_EQ("1", vs[0]);
    EXPECT_EQ("2", vs[1]);
    EXPECT_EQ("3", vs[2]);
    delete T;
    //end split
}

TEST_F(T_Event, identify_user) {
    using namespace CryptoPP;

    //AES中使用的固定参数是以类AES中定义的enum数据类型出现的，而不是成员函数或变量
    //因此需要用::符号来索引
    // cout << "AES Parameters: " << endl;
    // cout << "Algorithm name : " << AES::StaticAlgorithmName() << endl;      

    // //Crypto++库中一般用字节数来表示长度，而不是常用的字节数
    // cout << "Block size     : " << AES::BLOCKSIZE * 8 << endl;
    // cout << "Min key length : " << AES::MIN_KEYLENGTH * 8 << endl;
    // cout << "Max key length : " << AES::MAX_KEYLENGTH * 8 << endl;
    

    Event *T = new Event();
    string user("tiger");
    string pwd("freebsd");
    EXPECT_TRUE(T->identify_user(user, pwd));
    pwd = "maths";
    EXPECT_FALSE(T->identify_user(user, pwd));

    user = "ak47";
    EXPECT_TRUE(T->identify_user(user, pwd));
    user = "m16";
    EXPECT_TRUE(T->identify_user(user, pwd));
    delete T;
}
TEST_F(T_Event, explain_msg) {
    Event *T = new Event();
    ifstream in;
    //read json file to stream
    in.open("login.json");
    string line;
    string content;
    while(!in.eof()) {
	std::getline(in, line);
	content += line;
    }
//    cout<<<<content<<endl;
    in.close();

    Json::Reader reader;
    Json::Value json_object;

    if(!reader.parse(content, json_object)) {
	cout<<"parse fail\n";
    }
    EXPECT_EQ("tiger", json_object["user"].asString());
    EXPECT_EQ("freebsd", json_object["password"].asString());
//    cout<<json_object["title"]<<endl;

    //test login
    map<string, string> t_msg;
    t_msg = T->parse_msg(content);
    EXPECT_EQ("tiger", t_msg["user"]);
    EXPECT_EQ("freebsd", t_msg["password"]);

    string get_users = "{\"action\":\"get_users\"}";
    t_msg = T->parse_msg(get_users);
    EXPECT_EQ("get_users", t_msg["action"]);

    delete T;    
//    json_test = "b"
    //string data("login%#%abcde");
    //T->route(data);
}
TEST_F(T_Event, get_user) {
    Event *T = new Event();
    Json::Reader reader;
    Json::Value value;
    
    string res = T->get_users();
    reader.parse(res, value);

    EXPECT_EQ("get_users", value["result"].asString());
//    EXPECT_EQ(3, value["users"].size());
    EXPECT_EQ("tiger", value["users"][0].asString());
    EXPECT_NE("tige", value["users"][0].asString());
    
    delete T;
}
int main(int argc, char **argv) {
    //    testing::AddGlobalTestEnvironment(new MFEnvironment);
    testing::InitGoogleTest(&argc, argv);  
    return RUN_ALL_TESTS();  
} 
