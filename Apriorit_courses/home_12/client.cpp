#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <iostream>
#include <fstream>
#include <boost/enable_shared_from_this.hpp>

using boost::asio::ip::tcp;

static bool debugmode = true;
static boost::mutex debug_mutex;
static std::ostream debug_global(std::clog.rdbuf());

class async_tcp_client
{
public:
    async_tcp_client(boost::asio::io_service& io_service, const std::string& server, const std::string& path)
        : resolver_(io_service), socket_(io_service)
    {
        size_t pos = server.find(':');
        if (pos == std::string::npos)
        {
            return;
        }
        std::string port_string = server.substr(pos + 1);
        std::string server_ip_or_host = server.substr(0, pos);
        source_file.open(path, std::ios_base::binary | std::ios_base::ate);
        if (!source_file)
        {
            boost::mutex::scoped_lock lk(debug_mutex);
            std::cout << __LINE__ << "Failed to open " << path << std::endl;
            return;
        }
        size_t file_size = source_file.tellg();
        source_file.seekg(0);
        std::ostream request_stream(&request_);
        request_stream << path << "\n" << file_size << "\n\n";
        {
            boost::mutex::scoped_lock lk(debug_mutex);
            std::cout << "Request size: " << request_.size() << std::endl;
        }
        tcp::resolver::query query(server_ip_or_host, port_string);
        resolver_.async_resolve(query, boost::bind(&async_tcp_client::handle_resolve, this, boost::asio::placeholders::error, boost::asio::placeholders::iterator));
    };
private:
    void handle_resolve(const boost::system::error_code& err, tcp::resolver::iterator endpoint_iterator)
    {
        if (!err)
        {
            tcp::endpoint endpoint = *endpoint_iterator;
            socket_.async_connect(endpoint, boost::bind(&async_tcp_client::handle_connect, this, boost::asio::placeholders::error, ++endpoint_iterator));
        }
        else
        {
            boost::mutex::scoped_lock lk(debug_mutex);
            std::cout << err.message() << '\n';
        }
    };

    void handle_connect(const boost::system::error_code& err, tcp::resolver::iterator endpoint_iterator)
    {
        if (!err)
        {
            boost::asio::async_write(socket_, request_, boost::bind(&async_tcp_client::handle_write_file, this, boost::asio::placeholders::error));
        }
        else if (endpoint_iterator != tcp::resolver::iterator())
        {
            socket_.close();
            tcp::endpoint endpoint = *endpoint_iterator;
            socket_.async_connect(endpoint, boost::bind(&async_tcp_client::handle_connect, this, boost::asio::placeholders::error, ++endpoint_iterator));
        }
        else
        {
            boost::mutex::scoped_lock lk(debug_mutex);
            std::cout << err.message() << '\n';
        };
    }

    void handle_write_file(const boost::system::error_code& err)
    {
        if (!err)
        {
            if (source_file)
                //if(source_file.eof() == false)
            {
                source_file.read(buf.c_array(), (std::streamsize)buf.size());
                if (source_file.gcount() <= 0)
                {
                    boost::mutex::scoped_lock lk(debug_mutex);
                    std::cout << "read file error" << std::endl;
                    return;
                };
                {
                    boost::mutex::scoped_lock lk(debug_mutex);
                    std::cout << "Send " << source_file.gcount() << "bytes, total: " << source_file.tellg() << " bytes.\n";
                }
                boost::asio::async_write(socket_, boost::asio::buffer(buf.c_array(), source_file.gcount()), boost::bind(&async_tcp_client::handle_write_file, this, boost::asio::placeholders::error));
            }
            else
            {
                return;
            }
        }
        else
        {
            boost::mutex::scoped_lock lk(debug_mutex);
            std::cout << err.message() << "\n";
        }
    };


    tcp::resolver resolver_;
    tcp::socket socket_;
    boost::array<char, 1024> buf;
    boost::asio::streambuf request_;
    std::ifstream source_file;
};

void send_data(std::string const& filename, std::string const& adr = "localhost:8888")
{
    try
    {
        boost::asio::io_service io_service;
        {
            boost::mutex::scoped_lock lk(debug_mutex);
            std::cout << "Adress is: " << adr << " and file is: " << filename << '\n';
        }

        if (debugmode)
        {
            boost::mutex::scoped_lock lk(debug_mutex);
            debug_global << adr << '\n';
        }

        async_tcp_client client(io_service, adr, filename);
        io_service.run();
    }
    catch (std::exception const& e)
    {
        std::cerr << e.what() << "\n";
    };
};

int main(int argc, char *argv[])
{	
	if (argc!=2)
		return -1;
    send_data(argv[1]);
    return 0;
}
