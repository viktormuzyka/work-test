#include <windows.h>    
#include <iostream>    
#include <memory>      
#include <cassert>


class Guard
{
    HANDLE m_handle;
public:
    Guard(const HANDLE file) :m_handle(file) { std::cout << "1" << std::endl; }
 
    #if 0
    
    operator const HANDLE&() const noexcept
    {
        std::cout << "2" << std::endl;
        return m_handle;
    }
 
    const HANDLE& handle() const noexcept
    {
        std::cout << "3" << std::endl;
        return m_handle;
    }
    #endif
 
    ~Guard()
    {
        std::cout << "4" << std::endl;
        if(m_handle != INVALID_HANDLE_VALUE)
        {
            const bool success = ::CloseHandle(m_handle)!=0;
            (void)success;
            assert(success);
        }
    }
};
 
struct CustomDeleter
{
    void operator()(HANDLE* handle) const noexcept
    {
        std::cout << "5" << std::endl;
        if (*handle != INVALID_HANDLE_VALUE)
        {
            std::cout << "6" << std::endl;
            const bool success = ::CloseHandle(*handle) != 0;
            (void)success;
            assert(success);
        }
    }
};
 
int main()
{
    HANDLE hFile 
        = CreateFile("avada.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    if(hFile == INVALID_HANDLE_VALUE)
        return 
            ::std::cerr << "error: can not open file 'avada.txt'", 
            -1;

    std::unique_ptr<HANDLE, CustomDeleter> smart(&hFile);

    DWORD size;
    const bool success 
        = ::WriteFile(hFile, "Hello World", 11, &size, NULL) != 0;
    if(!success)
        return 
            ::std::cerr << "error: can not write to file 'avada.txt'", 
            -1;
}
