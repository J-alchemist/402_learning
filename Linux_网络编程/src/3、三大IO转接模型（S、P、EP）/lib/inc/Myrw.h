#ifndef MYRW_H
#define MYRW_H


ssize_t ReadNbyte(int fd, void *vptr, size_t n);		//Readn
ssize_t WriteNbyte(int fd, const void *vptr, size_t n); //Writen
static ssize_t My_read(int fd, char *ptr);				//my_read
ssize_t Readline(int fd, void *vptr, size_t maxlen);



void perr_exit(const char *s);
int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr);
ssize_t Read(int fd, void *ptr, size_t nbytes);
int Bind(int fd, const struct sockaddr *sa, socklen_t salen);
int Connect(int fd, const struct sockaddr *sa, socklen_t salen);
int Listen(int fd, int backlog);
int Socket(int family, int type, int protocol);
ssize_t Write(int fd, const void *ptr, size_t nbytes);
int Close(int fd);




#endif

