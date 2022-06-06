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

class async_tcp_connection : public boost::enable_shared_from_this<async_tcp_connection>
{
public:
    async_tcp_connection(boost::asio::io_service& io_service)
        : socket_(io_service), file_size(0)
    {
    }
    void start()
    {
        if (debugmode)
        {
            boost::mutex::scoped_lock lk(debug_mutex);
            debug_global << __FUNCTION__ << std::endl;
        }
        async_read_until(socket_, request_buf, "\n\n", boost::bind(&async_tcp_connection::handle_read_request, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    }
    boost::asio::ip::tcp::socket& socket()
    {
        return socket_;
    }
private:
    boost::asio::streambuf request_buf;
    std::ofstream output_file;
    boost::asio::ip::tcp::socket socket_;
    size_t file_size;
    boost::array<char, 40960> buf;
    void handle_read_request(const boost::system::error_code& err, std::size_t bytes_transferred)
    {
        if (err)
        {
            return handle_error(__FUNCTION__, err);
        }
        if (debugmode)
        {
            boost::mutex::scoped_lock lk(debug_mutex);
            debug_global << __FUNCTION__ << "(" << bytes_transferred << ")" << ", in_avail = " << request_buf.in_avail() << ", size = " << request_buf.size() << ", max_size = " << request_buf.max_size() << ".\n";
        }
        std::istream request_stream(&request_buf);
        std::string file_path;
        request_stream >> file_path;
        request_stream >> file_size;
        request_stream.read(buf.c_array(), 2);
        if (debugmode)
        {
            boost::mutex::scoped_lock lk(debug_mutex);
            debug_global << file_path << " size is " << file_size << ", tellg = " << request_stream.tellg() << std::endl;
        }
        size_t pos = file_path.find_last_of('\\');
        if (pos != std::string::npos)
        {
            file_path = file_path.substr(pos + 1);
        }
        output_file.open(file_path + ".received", std::ios_base::binary);
        if (!output_file)
        {
            if (debugmode)
            {
                boost::mutex::scoped_lock lk(debug_mutex);
                debug_global << __LINE__ << "Failed to open: " << file_path << std::endl;
            }
            return;
        }
        do
        {
            request_stream.read(buf.c_array(), (std::streamsize)buf.size());
            if (debugmode)
            {
                boost::mutex::scoped_lock lk(debug_mutex);
                debug_global << __FUNCTION__ << " write " << request_stream.gcount() << " bytes.\n";
            }
            output_file.write(buf.c_array(), request_stream.gcount());
        } while (request_stream.gcount() > 0);
        async_read(socket_, boost::asio::buffer(buf.c_array(), buf.size()), boost::bind(&async_tcp_connection::handle_read_file_content, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    }

    void handle_read_file_content(const boost::system::error_code& err, std::size_t bytes_transferred)
    {
        if (bytes_transferred > 0)
        {
            output_file.write(buf.c_array(), (std::streamsize)bytes_transferred);
            if (debugmode)
            {
                boost::mutex::scoped_lock lk(debug_mutex);
                debug_global << __FUNCTION__ << " recv " << output_file.tellp() << " bytes." << std::endl;
            }
            if (output_file.tellp() >= (std::streamsize)file_size)
            {
                return;
            }
        }
        if (err)
        {
            return handle_error(__FUNCTION__, err);
        }
        async_read(socket_, boost::asio::buffer(buf.c_array(), buf.size()), boost::bind(&async_tcp_connection::handle_read_file_content, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    }

    void handle_error(const std::string& function_name, const boost::system::error_code& err)
    {
        if (debugmode)
        {
            boost::mutex::scoped_lock lk(debug_mutex);
            debug_global << __FUNCTION__ << " in " << function_name << " due to " << err << " " << err.message() << std::endl;
        }
    }
};

class async_tcp_server
{
public:
    typedef boost::shared_ptr<async_tcp_connection> ptr_async_tcp_connection;

    async_tcp_server(unsigned short port) :acceptor_(io_service_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port), true)
    {
        ptr_async_tcp_connection new_connection_(new async_tcp_connection(io_service_));
        acceptor_.async_accept(new_connection_->socket(), boost::bind(&async_tcp_server::handle_accept, this, new_connection_, boost::asio::placeholders::error));
        io_service_.run();
    }
    void handle_accept(ptr_async_tcp_connection current_connection, const boost::system::error_code& e)
    {
        if (debugmode)
        {
            boost::mutex::scoped_lock lk(debug_mutex);
            debug_global << __FUNCTION__ << " " << e << ", " << e.message() << std::endl;
        }
        if (!e)
        {
            current_connection->start();
        }
    }

    ~async_tcp_server()
    {
        io_service_.stop();
    }
private:
    boost::asio::io_service io_service_;
    boost::asio::ip::tcp::acceptor acceptor_;
};

void rec_data(void)
{
    try
    {
        {
            boost::mutex::scoped_lock lk(debug_mutex);
            std::cout << "Receiving data...\n";
        }
        async_tcp_server recv_file_tcp_server(8888);
        if (debugmode)
        {
            boost::mutex::scoped_lock lk(debug_mutex);
            debug_global << "Received\n";
        }
    }
    catch (std::exception const& e)
    {
        std::cerr << e.what() << "\n";
    };
};

int main()
{
    rec_data();
}
