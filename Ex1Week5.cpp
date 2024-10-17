// Bài 1:  Nhập vào n đối tượng có màu đỏ (red), trắng (white) và xanh (blue), sắp xếp theo trật tự như sau: các đối tượng cùng mầu nằm kế tiếp nhau và theo thứ tự đỏ, trắng, xanh.
// Input {xanh, đỏ, xanh, đỏ, đỏ, trắng, đỏ, xanh, trắng}
// Output {đỏ, đỏ, đỏ, đỏ, trắng, trắng, xanh, xanh, xanh}
// Gợi ý:
// Có thể mã hóa các mầu bằng các số nguyên 0, 1, 2 để biểu diễn lần lượt mầu đỏ, trắng và xanh tương ứng.
// Chú ý: Không sử dụng các thư viện hàm sắp xếp có sẵn để giải quyết bài toán trên khi cài đặt chương trình

// Ý tưởng
// Tạo 1 mảng lưu các giá trị màu, song song với đó tạo mọt mảng lưu các giá trị số tương ứng với các màu
// "0" -> do, "1" -> trang, "2" -> xanh
// Dùng thuật toán sắp xếp mảng số theo giá tị tăng dần, đồng thời sắp xếp các màu tương ứng
// In ra và bài toán hoàn thành
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int getValue(const string& color) {
    if (color == "do") return 0;      
    if (color == "xanh") return 1;    
    if (color == "trang") return 2;   
    return -1; 
}


void BubbleSort(int n, vector<int>& a, vector<string>& colors) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);   //doi gia tri
                swap(colors[j], colors[j + 1]); //doi mau tuong ung
            }
        }
    }
}

int main() {
    vector<string> color; //mang mau
    vector<int> number;   //mang gia tri
    string input;

    cout << "Nhap cac mau (nhap Enter de ket thuc): " << endl;
    while (true) {
        getline(cin, input);
        if (input.empty()) break; // Enter -> stop
        color.push_back(input); // them mau sau khi nhap
        number.push_back(getValue(input)); // them gia tri sau khi nhap mau
    }
    if (number.empty()) {
        cout << "Khong co mau nao duoc nhap." << endl;
        return 0;
    }
    BubbleSort(number.size(), number, color);
    cout << "Danh sach mau da sap xep: ";
    for (const auto& c : color) {
        cout << c << " ";
    }
    cout << endl;
    return 0;
}
