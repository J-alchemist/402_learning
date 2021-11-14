#include <boost/asio.hpp> 
#include <iostream> 


using namespace std;
const boost::system::error_code ec;

void handler1(const boost::system::error_code &ec) 
{ 
  cout << "5s over！" << endl; 
} 

void handler2(const boost::system::error_code &ec) 
{ 
  cout << "10s over！" << endl; 
} 

int main(int argc, char** argv) 
{ 
	boost::asio::io_service io_service; //定义了一个 I/O 服务 用于初始化 I/O 对象 timer
	boost::asio::deadline_timer timer1(io_service, boost::posix_time::seconds(5)); 	//5s定时
	timer1.async_wait(handler1); 	//5s后自动调用，非阻塞，此时可以做其他事
	boost::asio::deadline_timer timer2(io_service, boost::posix_time::seconds(10));
	timer2.async_wait(handler2); 

	io_service.run(); 	//操作系统接管控制权
	//阻塞式
	//timer.wait();	
	//handler(ec);
	

	return 0;



} 






