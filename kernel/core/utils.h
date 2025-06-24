// xử lý các phép toán và chuyển đổi chuỗi:
#ifndef __UTILS_H
#define __UTILS_H

// Chuyển chuỗi -> số
int atoi(const char *str);

// Chuyển số -> chuỗi
void itoa(int num, char* str);

// Tính căn bậc 2
double sqrt(double x);

// Kiểm tra chuỗi hợp lệ
bool isValidNumber(const char *str);

#endif