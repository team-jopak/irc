#include "Server.hpp"

Server::Server(std::string host, std::string port, std::string password)
    : _host(host), _port(port), _password(password)
{
    init();
}

Server::~Server()
{
    std::cout << "종료" << std::endl;
}

void Server::init()
{
    int on = 1;
    addrinfo hints;
    addrinfo *res;
    addrinfo *tmp_res;
    int socket_fd;

    memset(&hints, 0, sizeof(hints));
    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = 0;
    if (getaddrinfo(_host.c_str(), _port.c_str(), &hints, &res) != 0)
    {
        perror("getaddrinfo() failed");
        exit(-1);
    }

    if ((socket_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1)
    {
        perror("socket() failed");
        exit(-1);
    }

    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on)) == -1)
    {
        perror("setsockopt() failed");
        freeaddrinfo(res);
        close(socket_fd);
        exit(-1);
    }

    if (bind(socket_fd, res->ai_addr, res->ai_addrlen) != 0)
    {
        perror("bind() failed");
        freeaddrinfo(res);
        close(socket_fd);
        exit(-1);
    }

    if (listen(socket_fd, 32) == -1)
    {
        perror("listen() failed");
        freeaddrinfo(res);
        close(socket_fd);
        exit(-1);
    }
    _socket_fd = socket_fd;
}

void Server::server_run()
{
    // poll 초기화
    pollfd tmp_poll_fd = {_socket_fd, POLLIN, 0};
    pollfd cur_poll_fd;

    // 논블록킹으로 초기화
    if (fcntl(_socket_fd, F_SETFL, O_NONBLOCK) == -1)
    {
        perror("fcntl() failed");
        exit(-1);
    }
    // poll 디스크립터 벡터에 저장
    _poll_fd_vec.push_back(tmp_poll_fd);
    std::vector<pollfd>::iterator it_poll_fd;
    std::cout << "Server: " << _host << ":" << _port << std::endl;

    // 서버 실행
    while (42)
    {
        it_poll_fd = _poll_fd_vec.begin();
        if (poll(&(*it_poll_fd), _poll_fd_vec.size(), 5000) == -1)
        {
            perror("poll() failed");
            exit(-1);
        }
        // pollFd 에서 이벤트 발생 조회
        for (std::vector<pollfd>::iterator it = _poll_fd_vec.begin(); it != _poll_fd_vec.end(); it++)
        {
            cur_poll_fd = *it;
            if (cur_poll_fd.revents == POLLHUP)
            {
                std::cout << "pollhup" << std::endl << std::flush;
                break;
            }
            // tmp_poll_fd 돌면서 이벤트가 POLLIN 이면 해당 명령 실행 
            else if ((cur_poll_fd.revents & POLLIN) == POLLIN)
            {
                // 클라이언트인 유저 추가
                if (cur_poll_fd.fd == _socket_fd)
                {
                    accept_user();
                }
                // 이벤트 발생한 유저 메시지 확인
                else
                {
                    recv_message(cur_poll_fd.fd);
                }
                break;
            }
        }
    }
}

int Server::recv_message(int cur_fd)
{
    char buf = '\n';
    std::string tmp_buf;
    int b = 0;
    while (42) // tmp_buf.find("\n")
    {
        int nbytes;
        nbytes = recv(cur_fd, &buf, 1, 0);
        if (nbytes < 0)
        {
            continue;
        }
        else
        {
            tmp_buf += buf;
            if (b > 500)
            {
                tmp_buf = "/QUIT you can't use this server\r\n";
            }
            if (tmp_buf.find("\n") != std::string::npos)
            {
                // 간단한 메세지 보내는 예시(잘 동작하는지 확인용)
                std::cout << tmp_buf << std::endl;
                ssize_t rc;
                rc = send(cur_fd, const_cast<char*>(tmp_buf.c_str()), b, 0);
                // command 시작
                // cmd(tmp_buf, *this) // buf, Server 클래스를 매개변수로 보내기
                break;
            }
        }
        b++;
    }
    tmp_buf.clear();
    return 0;
}

int Server::accept_user()
{
    int         user_fd;
    sockaddr_in user_addr;
    socklen_t   s_size;

    s_size = sizeof(user_addr);
    if ((user_fd = accept(_socket_fd, (sockaddr *)&user_addr, &s_size)) == -1)
    {
        perror("accept() failed");
        exit(-1);
    }
    pollfd new_poll_fd_vec = {user_fd, POLLIN, 0};
    _poll_fd_vec.push_back(new_poll_fd_vec);
    if (fcntl(user_fd, F_SETFL, O_NONBLOCK) == -1)
    {
        perror("fcntl failed");
        exit(-1);
    }
    // User *new_user = new User(user_fd);
    std::string * new_user = new std::string("new");
    _users.push_back(new_user);
    // std::cout << "New client: " << new_user->getSocket() << std::endl;
    std::cout << "New client: " << std::endl;
    return user_fd;
}