#include "utils.h"

int atoi (const char *str) 
{
    int result = 0;
    int sign = 1;
    int i = 0;
    
    // Xử lý dấu
    if (str[0] == '-')
    {
        sign =-1;
        i++;
    }
   
    while (str[i] != '\0')
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            // (str[i] - '0'): chuyển kí tự thứ i -> số 
            result = result * 10 + (str[i] - '0');
        }
        i++; 
    }

    return sign * result;
}

void itoa(int num, char* str)
{
    int i = 0;
    bool isNegative = false;

    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }
   
    if (num < 0)
    {
        isNegative = true;
        num = -num;
    }
    
    while (num != 0)
    {
        int rem = num % 10;     // Tách từng số từ phải vào
        str[i++] = rem + '0';   // Chuyển số vừa tách về kí tự.
        num = num / 10;         // Loại số vừa chuyển khỏi số.
    }
    
    if (isNegative)
    {
        str[i++] = '-';
    }
    
    str[i] = '\0';

    // Đảo ngược chuỗi 
    int start = 0;
    int end = i-1;
    while (start < end)
    {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;

        start++;
        end--;
    }
}

// Newton-raphson aglorithsm để tìm căn bậc 2
double sqrt(double x)
{
    if (x<0)
    {
        return -1;  //error case
    }
    if (x == 0)
    {
        return 0;
    }
    
    double result = x;          // Chọn đại số x để làm kết quả
    double precision = 0.00001; // Sai số

    while ((result - x/result) > precision) // kiểm tra điều kiện bằng sai số 
    {
        // mới = (cũ + x/cũ) / 2
        result = (result + x/result) / 2;
    }
    
    return result;
}

bool isValidNumber(const char* str)
{
    // Rỗng
    if (str[0] == '\0')
    {
        return false;
    }
    // Nếu là âm thì bỏ qua dấu 
    int i = 0;
    if (str[0] == '-')
    {
        i++;
    }
    // Kiểm tra từng kí tự 
    while (str[i] != '\0')
    {
        if (str[i] < '0' || str[i] > '9')
        {
            return false;
        }
        i++;
    }
    return true;
}