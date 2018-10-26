#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <arpa/inet.h>


#include <string.h>
#include <fcntl.h>

using std::cout;
using std::string;

const int PORT = 5000;
const int MAXCONNECTIONS = 100;

int main(int argc, char *argv[]) {
    std::cout<<"running...\n";
    //create, bind, listen
    int m_sock;
    m_sock = socket(AF_INET, SOCK_STREAM, 0);

    m_addr.sin_family = AF_INET;
    m_addr.sin_addr.s_addr = INADDR_ANY;
    m_addr.sin_port = htons(PORT);
    bind(m_sock, (struct sockaddr *) &m_addr, sizeof(m_addr));

    listen(m_sock, MAXCONNECTIONS);

    while(true) {
        int new_sock = socket
    }
    

    
}
