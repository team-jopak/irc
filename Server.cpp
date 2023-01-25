#include "Server.hpp"

Server::Server(std::string host, std::string port, std::string password)
    : host_(host), port_(port), password_(password)
{
    int on = 1;
    struct addrinfo hints;
    struct addrinfo *res;
    struct addrinfo *resaux;
    int socketFd;

    memset(&hints, 0, sizeof(hints));
    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = 0;
    if (getaddrinfo(host_.c_str(), port_.c_str(), &hints, &res) != 0)
    {
        perror("getaddrinfo() failed")
        close(listen_sd);
        exit(-1);
    }

    if ((socketFd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1)
    {
        perror("socket() failed");
        exit(-1);
    }

    if (setsockopt(socketFd, SOL_SOCKET, SO_REUSEADDR, (char *)*on, sizeof(on)) == -1)
    {
        perror("setsockopt() failed");
        freeaddrinfo(res);
        close(socketFd);
        exit(-1);
    }

    if (bind(socketFd, res->ai_addr, res->ai_addrlen) != 0)
    {
        perror("bind() failed");
        freeaddrinfo(res);
        close(socketFd);
        exit(-1);
    }

    if (listen(socketFd, MAX_CONNECTIONS) == -1)
    {
        perror("listen() failed");
        freeaddrinfo(res);
        close(socketFd);
        exit(-1);
    }
    socket_ = socketFd;
    run();
}

Server::run()
{
    // poll 초기화
    pollfd fd = (socket_, POLLIN, 0);
    pollfd curPollFd;

    // 논블록킹으로 초기화
    if (fcntl(socket_, F_SETFL, O_NONBLOCK) == -1)
    {
        perror("fcntl() failed");
        exit(-1);
    }
    // poll 디스크립터 벡터에 저장
    pollFdVec_.push_back(fd);
    std::vector<pollfd>::iterator itFd;
    std::cout << "Server: " << host_ << ":" << port_ << std::endl;

    // 서버 실행
    while (1)
    {
        itFd = pollFdVec.begin();
        if (poll(&(*itFd), pollFdVec.size(), 5000) == -1)
        {
            perror("poll() failed");
            exit(-1);
        }

        // fd 돌면서 이벤트가 POLLIN 이면 해당 명령 실행 
        for (std::vector<pollFd>::iterator it = pollFdVec.begin(); it != pollFdVec.end(); it++)
        {
            curPollFd = *it;
            if (curPollFd.revents == POLLHUP)
            {
                std::cout << "pollhup" << std::endl << std::flush;
                break;
            }
            else if ((curPollFd.revents & POLLIN) == POLLIN)
            {
                // 클라이언트 유저 추가
                if (curPollFd.fd == socket_)
                {
                    acceptUser();
                }
                // 이벤트 발생한 유저 메시지 확인
                else
                {
                    recvMessage(curPollFd.fd);
                }
                break;
            }
        }
    }
}

int Server::recvMessage(int fd)
{
    char buf = '\n';
    std::string tmpBuf;
    int a = 0;
    while (tmpBuf.find("\n"))
    {
        int nbytes;
        nbytes = recv(fd, &buf, 1, 0);
        if (nbytes < 0)
        {
            continue;
        }
        else
        {
            tmpBuf += buf;
            if (a > 500)
            {
                tmpBuf = "/QUIT you can't flood this server\r\n";
            }
            if (tmpBuf.find("\n") != std::string::npos)
            {
                // command 시작
                // Command cmd(tmpBuf, fd, *this) // buf, fd, server클래스 멤버들 
                break;
            }
        }
        a++;
    }
    tmpBuf.clear();
    return 0;
}

int Server::acceptUser()
{
    // int         client_d;
    // sockaddr_in client_addr;
    // socklen_t   s_size;

    // s_size = sizeof(client_addr);
    // if (client__d = accept(socket_, (sockaddr *)&client_addr, &s_size) == -1)
    // {
    //     perror("accept() failed");
    //     exit(-1);
    // }
    // pollFdvec newPollFdVec = (client_d, POLLIN, 0);
    // pollFdVec.push_back(newPollFdVec);
    // if (fcntl(client_d, F_SETFL, O_NONBLOCK) == -1)
    // {
    //     perror("fcntl failed");
    //     exit(-1);
    // }
    // User *newUser = new User(client_d);
    // users_.push_back(newUser);
    // std::cout << "New client: " << newUser->getSocket() << std::endl;
    // return client_d;
}