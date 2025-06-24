// Triển khai các hàm từ .h

#include "keyboard.h"

// Khởi tạo Driver
KeyboardDriver::KeyboardDriver()
: dataport(0x60), commandport(0x64) // set port I/O
{
    // 1. Xóa dữ liệu rác còn trong bộ đệm của controller
    while (commandport.Read() &0x1)
    {
        dataport.Read();
    }
    // 2. (Bật cổng 1) active interrupts của bàn phím
    commandport.Write(0xAE);

    // Cho phép controller gửi ngắt bàn phím
    commandport.Write(0x20);            // 3. Lấyy trạng thái hiện tại
    uint8_t status = (dataport.Read() | 1) & ~0x10; // 4. Bật ngắt, tắt dịch mã
    commandport.Write(0x60);            // 5. Ghi trạng thái mới -> áp dụng thay đổi
    dataport.Write(status);

    // 6. Active keyboard -> Bắt đầu quét phím
    dataport.Write(0xF4);
}

KeyboardDriver::~KeyboardDriver () {}

// Hàm đọc 1 kí tự
char KeyboardDriver::ReadChar () 
{
    while (true)
    {
        // Nếu bàn phím được nhấn
        if (commandport.Read() & 0x1)
        {
            // Lấy scancode của từ vừa nhập.
            uint8_t scancode = dataport.Read();
            // Bỏ qua nếu đó là phím thả (>= 0x80).
            if (scancode < 0x80)
            {
                // Nếu là nhấn -> chuyển scancode thành kí tự rồi return.
                return ConvertScanCode(scancode);
            }
        }
    }
}

// Hàm đọc một chuỗi 
void KeyboardDriver::GetString(char *buffer, int maxlen)
{
    int idx = 0;
    // giới hạn kí tự đượcc nhập 
    while (idx < maxlen -1)
    {
        // Đọc từng kí tự từ chuỗi input 
        char c = ReadChar();
        // Dừng lại nếu nhấn enter
        if (c == '\n')
        {
            break;
        }
        // Chỉ nhận kí tự in ra đc (printable ASCII)
        if (c >= ' ' && c <= '~')
        {
            buffer[idx++] = c;
        }
    }
    // Kết thúc một chuỗi bằng '\0'
    buffer[idx] = '\0';  
}

// hàm chuyển mã quét bàn phím (scancode) thành ASCII
int KeyboardDriver::ConvertScanCode(uint8_t scancode)
{
    switch(scancode)
    {
        case 0x1C: return '\n'; // Enter
        case 0x39: return ' ';  // Space
        
        case 0x02: return '1';
        case 0x03: return '2';
        case 0x04: return '3';
        case 0x05: return '4';
        case 0x06: return '5';
        case 0x07: return '6';
        case 0x08: return '7';
        case 0x09: return '8';
        case 0x0A: return '9';
        case 0x0B: return '0';
        case 0x0C: return '-';
        case 0x0D: return '=';
        default: return 0;
    }
}