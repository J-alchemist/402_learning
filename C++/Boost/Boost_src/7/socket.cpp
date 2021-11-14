#include <boost/asio.hpp> 
#include <boost/array.hpp> 
#include <iostream> 
#include <string> 

using namespace std;
using namespace boost;

boost::asio::io_service io_service; //io服务
boost::asio::ip::tcp::resolver resolver(io_service);//域名解析器，网址->ip 
boost::asio::ip::tcp::socket  sock(io_service); //io对象
boost::array<char, 4096> buffer; //缓冲区

void read_handler(const boost::system::error_code &ec, std::size_t bytes_transferred) //每当有一个或多个字节被接收并保存至缓冲区时，read_handler函数就会被调用。
{ 
  if (!ec) //async_read_some与read_handler循环调用，读出、打印
  { 
// 准确的字节数通过 std::size_t 类型的参数 bytes_transferred 给出
    cout << std::string(buffer.data(), bytes_transferred) << endl; 
    sock.async_read_some(boost::asio::buffer(buffer), read_handler); 
  } 
} 

void connect_handler(const boost::system::error_code &ec) 
{ 
  if (!ec) 
  { 
    boost::asio::write(sock, boost::asio::buffer("GET / HTTP 1.1\r\nHost: highscore.de\r\n\r\n")); //写入
    sock.async_read_some(boost::asio::buffer(buffer), read_handler); //读取
	//至少一个字节之后调用相关联的句柄。 该句柄需要计算还剩余多少字节，并反复调用 async_write_some() 直至所有字节发送完毕
	//sock.async_read();//在缓冲区的所有字节都被发送后才调用关联的函数		
  } 
} 
// const boost::system::error_code 域名解析成功与否标志
// boost::asio::ip::tcp::resolver::iterator 服务器地址
void resolve_handler(const boost::system::error_code &ec, boost::asio::ip::tcp::resolver::iterator it) //一旦域名解析成功或被某个错误中断，会被调用
{ 
  if (!ec) //域名解析成功ec=0
  { 
    sock.async_connect(*it, connect_handler); //建立连接
  } 
} 
int main(int argc, char** argv) 
{ 

	   boost::asio::ip::tcp::resolver::query query("www.highscore.de", "80"); //查询www.highscore.de，80端口
	   resolver.async_resolve(query, resolve_handler); //async_resolve解析域名，成功与否的信息传递给resolve_handler进行处理
	   io_service.run(); 

	   return 0;


}


 
