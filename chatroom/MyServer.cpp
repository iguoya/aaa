#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#include <unistd.h>

#include "Event.h"

#include <iostream>
#include <cstdlib>
#include <cstring>


using std::cout;
using std::endl;

int PORT = 5000;
const int BACKLOG = 5;


void process_client(int , struct sockaddr_in);

int main()
{
    int listen_fd;
    struct sockaddr_in server_addr;

    int conn_fd;
    struct sockaddr_in client_addr;

    pid_t pid;

    bzero(&server_addr, sizeof(server_addr));
    
    if((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
	cout<<"socket create failed\n";
	exit(1);
    } else {
	cout<<"socket create succeed:\n";
    }
    
    int opt = SO_REUSEADDR;
    setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
	cout<<"bind error\n";
	exit(1);
    } else {
	cout<<"bind succeed\n";
    }

    if(listen(listen_fd, BACKLOG) == -1) {
	cout<<"listen error";
	exit(1);
    } else {
	cout<<"listen succeed\n";
    }

    while(true) {
	socklen_t addr_size = sizeof(client_addr);
	if((conn_fd = accept(listen_fd, (struct sockaddr *)&client_addr, &addr_size)) == -1) {
	    cout<<"accept error\n";
	    exit(1);
	} else {
	    cout<<"connect accept , conn_fd:"<<conn_fd<<endl;
	}

	if((pid = fork()) > 0) {// parent process
	    close(conn_fd);
	    //处理信息接受服务	    
	    continue;//重新接受新的连接
	}
	else
	    if(pid == 0) {
		//处理具体事物
		close(listen_fd);//child process
		process_client(conn_fd, client_addr);
		exit(0);
	    } else {
		cout<<"fork error\n";
		exit(0);
	    }

    }
    close(listen_fd);
}

void process_client(int conn_fd, struct sockaddr_in client_addr)
{
    cout<<"client process.....:"<<getpid()<<endl;
    Event e;
    int recv_num;
    char login_buf[100];
    char recv_buf[100];
    char send_buf[100];
    string msg;
    
    if(recv_num = recv(conn_fd, login_buf, sizeof(login_buf), 0)) {
	login_buf[recv_num] = '\0';
	cout<<"received:"<<login_buf<<endl;
    }

    Json::Reader reader;
    Json::Value v;
    if(reader.parse(string(login_buf), v)) {
	if(!e.identify_user(v["user"].asString(), v["password"].asString())) {
	    //identify fail
	    msg = "false";
	    cout<<"identify fail"<<endl;
	    send(conn_fd, msg.c_str(), msg.size(), 0);
	    close(conn_fd);
	    return;
	}
    } else {
	return;
    }
    

    cout<<"connect succeed\n, "<<getpid()<<endl;
    msg = "true";
    send(conn_fd, msg.c_str(), msg.size(), 0);
    
    //进行后续请求

    while((recv_num = recv(conn_fd, recv_buf, sizeof(recv_buf), 0))) {
	recv_buf[recv_num] = '\0';
	cout<<"received :"<<recv_buf<<endl;
	msg = e.route(string(recv_buf));
	send(conn_fd, msg.c_str(), msg.size(), 0);
	cout<<"now return :msg"<<msg<<endl;
    }
    
    cout<<"client process over.....:process:"<<getpid()<<endl;
}
