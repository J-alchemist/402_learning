#include <boost/asio.hpp> 
#include <string> 

using namespace std;
using namespace boost;
/*等待连接*/
boost::asio::io_service io_service; 
boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), 80); 
boost::asio::ip::tcp::acceptor acceptor(io_service, endpoint); 
boost::asio::ip::tcp::socket sock(io_service); 
std::string data = "HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\nHello, world!"; //格式

void write_handler(const boost::system::error_code &ec, std::size_t bytes_transferred) 
{ 
} 

void accept_handler(const boost::system::error_code &ec) 
{ 
  if (!ec) 
  { 
    boost::asio::async_write(sock, boost::asio::buffer(data), write_handler); //在缓冲区的所有字节都被发送后才调用关联的函数
//async_write_some();//
  } 
} 
//-----------------
int main(int argc, char** argv) 
{ 

  acceptor.listen(); //接收状态
  acceptor.async_accept(sock, accept_handler); //等待初始连接
  io_service.run();


}


 
