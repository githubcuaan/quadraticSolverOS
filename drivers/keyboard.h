#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include "../kernel/core/types.h"
#include "port.h" // Chứa class Port8bit - cho phép đọc/ghi từ cổng I/O

/*lớp KeyboardDriver: 
    - Tương tác trực tiếp với bàn phím thông qua cổng I/O.

    - Đọc phím nhấn, chuyển đổi mã phím (scan code) thành ký tự, lấy chuỗi nhập từ người dùng.*/
class KeyboardDriver
{
    Port8Bit dataport;      //Đọc mã phím (scancode)
    Port8Bit commandport;   //Gửi lệnh, đọc trạng thái.
private:
    int ConvertScanCode(uint8_t scancode);
public:
    KeyboardDriver();
    ~KeyboardDriver();

    // ReadChar(): đọc một ký tự từ bàn phím → thường là vòng lặp đọc từ dataport và dịch mã scancode sang ký tự.
    char ReadChar();
    
    // GetString(...): đọc nhiều ký tự vào buffer, dừng khi nhấn Enter, hoặc khi đạt maxLen - 1. Kết thúc bằng '\0'.
    void GetString(char *buffer, int maxLen);
};

#endif