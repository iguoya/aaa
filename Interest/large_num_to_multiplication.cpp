#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

void swap(string &, string &);
int ctoi(char );
char itoc(int );

int main() {
    string num1, num2;
    cout<<"input two num:\n";
    cin >>num1>>num2;
    cout<<"input over, num1:"<<num1<<",num2:"<<num2<<endl;
    //num1 = "9999999999999999999999999999";
    //num2 = "99999999999999999999";
    if(num1.size() > num2.size()) {
	swap(num1, num2);
    }
    cout<<"process over, num1:"<<num1<<",num2:"<<num2<<endl;
    int num1_size = num1.size();
    int num2_size = num2.size();

    vector<string> svec(num1_size);
    int new_num = 0;

    int ix, ij;
    string *ps = NULL;

    for(ix = num1_size-1; ix != -1 ; --ix) {
	int n = num2_size;
	int rest_num = 0;
	ps = new string(num2_size+1, '0');
	svec[ix] = *ps;
	//	cout<<"ix:"<<ix<<",ps:"<<ps<<"--"<<&svec[ix]<<svec[ix]<<endl;
	delete ps;
	for(ij = num2_size-1; ij != -1; ij--) {
	    int t_num = ctoi(num1[ix])*ctoi(num2[ij]);
	    t_num += rest_num;
	    new_num = t_num%10;
	    rest_num = t_num/10;
	    svec[ix][n] = itoc(new_num);
	    svec[ix][n-1] = itoc(rest_num);
	    n--;
	}
	/*
	cout<<"******"<<endl;
	cout<<" over sver[ij]:"<<ix<<":"<<svec[ix]<<endl;
	cout<<"******"<<endl;
	*/
    }

    const int total_len = num1_size + num2_size;
    string s_sum;
    ps = new string(total_len, '0');
    s_sum = *ps;
    delete ps;
    
    char p[num1_size][total_len];
	
    for (int i = 0; i < num1_size; i++) {
	for(int j = 0; j< total_len; j++){
	    p[i][j] = '0';
	}
    }

    int j = 0;    
    for (vector<string>::size_type id = svec.size()-1; id != -1; id--) {
	int s_size = svec[id].size();
	int t = total_len - 1;
	for (int i = s_size - 1; i != -1; i--) {
	    p[j][t-j] = svec[id][i];
	    t--;
	}
	j++;
    }
    
    for (int i = 0; i < num1_size; i++) {
	for(int j = 0; j< total_len; j++){
	    cout<<p[i][j]<<"--";
	}
	cout<<endl;
    }
    
    new_num = 0;
    int t = 0;
    for (int i = total_len-1; i != -1; i--) {
	for(int j = 0; j<num1_size; j++) {
	    new_num += ctoi(p[j][i]);
	}
	s_sum[total_len-1-t] = itoc(new_num % 10);
	t++;
	new_num = new_num / 10;
	//       	cout << new_num%10<<":"<<new_num<<endl;
    }
    
    cout <<"total sum :"<< s_sum<<endl;
}
char itoc(int i) {
    return (char)i+48;
}
int ctoi(char c) {
    return c-48;
}
void swap(string &s1, string &s2) {
    string t = s1;
    s1 = s2;
    s2 = t;
}
