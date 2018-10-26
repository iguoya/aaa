#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <stdexcept>
#include <exception>
#include <map>
#include <cstdio>




#include <jsoncpp/json/json.h>
#include <crypto++/aes.h>
#include <unistd.h>
#include <ctime>
#include <mysql/mysql.h>

using std::vector;
using std::list;
using std::string;
using std::map;
using std::cout;
using std::endl;
using std::ifstream;
using std::make_pair;

using std::exception;
using std::runtime_error;



class Event {
 public:
    string route(string );
    string process_login(string &);
    vector<string> split(string&, string &);
    bool  identify_user(string, string);

    static list<string> current_users;
    string db_username;
     string db_pwd;
    static int compare_flag;
    map<string, string> parse_msg(string );
    string get_users();
 private:
    MYSQL * connect_db();

    //    pr
    
};


#endif

