#include "Event.h"


string Event::route(string msg) {
    //  cout<<msg<<std::endl;
//    Json::Reader reader;
    //  Json::Value value;
    
    map<string, string> m_msg = parse_msg(msg);

    if(m_msg["action"] == "get_users") {
	return get_users();
    }
    return "";
}

string Event::get_users() {
    string sql;
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    Json::Value root;
    
    conn = connect_db();
    sql = "select username from user";

//    root["users"] = "";
    mysql_query(conn, sql.c_str());
    
    res = mysql_store_result(conn);
    while((row = mysql_fetch_row(res)) != NULL) {
	root["users"].append(string(row[0]));
    }
    mysql_free_result(res);
    mysql_close(conn);
//    cout<<root.toStyledString();
    return root.toStyledString();
}
map<string, string> Event::parse_msg(string msg) {
   
    Json::Reader reader;
    Json::Value value;

    map<string, string> map_msg;
    if(reader.parse(msg, value)) {
	string action = value["action"].asString();
	    if(action=="get_users"){
		map_msg.insert(make_pair("action",value["action"].asString()));
	    }
    }

    // for(map<string, string>::iterator it = map_msg.begin();
    // 	it != map_msg.end(); ++it) {
    // 	cout<<it->first<<"--"<<it->second<<endl;
    // }
    return map_msg;
}

MYSQL * Event::connect_db() {
    MYSQL *conn;

    string server = "localhost";
    string user = "root";
    string password = "root";
    string database = "chatroom";

    conn = mysql_init(NULL);
    try {
	if(!mysql_real_connect(conn, server.c_str(), user.c_str(),
			       password.c_str(), database.c_str(), 0, NULL, 0)) {
	    throw runtime_error(mysql_error(conn));
	}
    } catch (runtime_error err){
	cout<<err.what()<<endl;
	return NULL;
    }
    // mysql_free_result(res);
    // mysql_close(conn);
    return conn;
}

bool Event::identify_user(string user, string password) {
    using namespace CryptoPP;
    
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    
    int res_num;
    struct tm *tm_ptr;
    time_t the_time;

    unsigned char aesKey[AES::DEFAULT_KEYLENGTH];  //密钥
    //转换密码为unsigned char[]
    unsigned char inBlock[AES::BLOCKSIZE];//password
    unsigned char plainText[AES::BLOCKSIZE];//password
    unsigned char outBlock[AES::BLOCKSIZE]; //加密后的密文块
    unsigned char xorBlock[AES::BLOCKSIZE]; //必须设定为全零
    memset(inBlock, 0, AES::BLOCKSIZE);
    memset(xorBlock, 0, AES::BLOCKSIZE); //置零
    memset(outBlock, 0, AES::BLOCKSIZE); //置零
    
    if(!(conn = connect_db()))
	cout<<"connect db error"<<endl;
	
    string sql = "Select * from user where username = '"+user+"'";

    mysql_query(conn, sql.c_str());
    res = mysql_store_result(conn);
    res_num = mysql_num_rows(res);
    
    if (!res_num) {
	//empty query ,then insert
	char i_sql[1000];
	char current_time[50];
	the_time = time(NULL);
	tm_ptr = gmtime(&the_time);
	strftime(current_time, 50, "%Y-%m-%d %H:%M:%S", tm_ptr);
	// 加密存储密码

	memset(i_sql, 0, sizeof(i_sql));
	//AES中只包含一些固定的数据，而加密解密的功能由AESEncryption和AESDecryption来完成
   
	//加密过程
	AESEncryption aesEncryptor; //加密器
	
	//要加密的数据块 放入 inBlock
	if(password.size() > AES::BLOCKSIZE -1)
	    password.substr(0,AES::BLOCKSIZE);
//	for (int i = 0; i < password.size(); ++i)
//	    inBlock[i] = password[i];

	aesEncryptor.SetKey(aesKey, AESEncryption::DEFAULT_KEYLENGTH );  //设定加密密钥
	aesEncryptor.ProcessAndXorBlock(inBlock, xorBlock, outBlock);  //加密
// end
//	转换为string， 存储生成的加密数据，和key
	string pwd;
	string pwd_key;
	char str[10];

	for (int i = 0; i < AES::BLOCKSIZE; ++i)
	{
//	    cout<<sizeof(str)<<" ";
	    memset(str, 0, sizeof(str));
	    sprintf(str, "%d,", outBlock[i]);
	    pwd += str;
	    memset(str, 0, sizeof(str));
	    sprintf(str, "%d,", aesKey[i]);
	    pwd_key+=str;
	}
//	cout<<"pwd:"<<pwd<<endl;
//	cout<<"key:"<<pwd_key<<endl;
	AESDecryption aesDecryptor;

	sprintf(i_sql, "insert into user values(NULL, '%s','%s', '%s', '%s')",	user.c_str(), pwd.c_str(), current_time, pwd_key.c_str());
	cout<<i_sql<<endl;
	if(!mysql_query(conn, i_sql)) {
	    //success
	    return true;
	} else {
	    cout<<"insert:"<<mysql_error(conn)<<endl;
	    return false;
	}
    }

    //exist user, now indentify
    row = mysql_fetch_row(res);
    mysql_free_result(res);
    mysql_close(conn);

    //解密密码
    AESDecryption aesDecryptor;

    string row_pwd(row[2]);
    string row_key(row[4]);
    string fg(",");
    //    int arr_p
    vector<string> vstr_pwd = split(row_pwd, fg);
    vector<string> vstr_key = split(row_key, fg);
    for(int i = 0; i<AES::BLOCKSIZE; ++i) {
	outBlock[i] = atoi(vstr_pwd[i].c_str());
	aesKey[i] = atoi(vstr_key[i].c_str());
//	cout<<i<<":"<<outBlock[i]<<", "<<aesKey[i]<<endl;
    }
    
    aesDecryptor.SetKey(aesKey, AES::DEFAULT_KEYLENGTH);
    aesDecryptor.ProcessAndXorBlock(outBlock, xorBlock, plainText);
//    cout<<plainText<<endl;
    string decryp_pwd;


    for(int i = 0; plainText[i] != '\0'; ++i) {
	decryp_pwd += plainText[i];
//	cout<<plainText<<" ";
    }
//      cout<<"pwd::"<<decryp_pwd<<" vs "<<password<<endl;
//      cout<<decryp_pwd.size()<<" vs "<<password.size()<<endl;
    if(decryp_pwd == password) {
	return true;
    }
    return false;
}



vector<string> Event::split(string &str, string &idn) {
    // 12,, ,,a2,, 3,, 44
    vector<string> substrs;
    string current_str = str;
    int last_pos = 0;
    while(last_pos + idn.size() <= current_str.size()) {
	int flag = 1;
        int flag_pos = last_pos;
        for(size_t j = 0; j != idn.size(); ++j) {
            if(current_str[flag_pos] != idn[j]) {
		//不匹配，进行下一次匹配
                flag = 0;
		++last_pos;
                break;
            } else {
		//继续匹配
                ++flag_pos;
            }
        }
	
        if (flag == 1) {
//	    cout<<"success"<<endl;
	    //匹配成功，进行分割
//	    cout<<"sp str:"<<current_str.substr(0, last_pos)<<endl;
            substrs.push_back(current_str.substr(0, last_pos));
	    current_str = current_str.substr(last_pos+idn.size(), current_str.size());
//	    cout<<"current:"<<current_str<<endl;
	    last_pos = 0;//准备进行下一轮匹配
        }
    }
    if(current_str.size() != str.size())
	substrs.push_back(current_str);
    // for(vector<string>::size_type i = 0; i != substrs.size(); ++i) {
	
    //     cout<<i<<":"<<substrs[i]<<endl;
    // }
    return substrs;
}
