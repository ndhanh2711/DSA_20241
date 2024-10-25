// Bài 2: Thiết kế giải thuật và cài đặt để tạo ra (1) một mảng số nửa nguyên tố (Blum) nhỏ hơn một số N cho trước và thực hiện hai yêu cầu sau
// -(2) Tìm ra tất cả các cặp số Blum có tổng cũng là một số Blum nhỏ hơn N
// -(3) Kiểm tra xem một số Blum M có tồn tại trong dãy số Blum được tạo ra hay không.


//Liệt kê tất cả các số nửa nguyên tố và lưu chúng lại trong 1 vector
// Dùng sàng số nguyên tố Eratosthenes để lấy ra mảng số nguyên tố nhỏ hơn N
// Sau đó lưu các giá trị nửa nguyên tố nhỏ hơn N được tạo ra tử mảng đó
// (1) Từ đây có được mảng số nửa nguyên tố nhỏ hơn N
// (2) Duyệt tổng từng cặp, nếu tổng bằng giá trị có trong mảng thì in ra
// (3) Kiểm tra số M có trong dãy hay không bằng cách kiểm tra arr[M] = 1 hay không
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

// Hàm sử dụng sàng số nguyên tố Eratosthenes
vector<int> sieveOfEratosthenes(int n) {
    vector<bool> isPrime(n + 1, true);
    isPrime[0] = isPrime[1] = false; // 0 và 1 không phải là số nguyên tố

    for (int p = 2; p * p <= n; p++) {
        if (isPrime[p]) {
            for (int i = p * p; i <= n; i += p) {
                isPrime[i] = false; // Đánh dấu các bội số của p là không phải số nguyên tố
            }
        }
    }

    vector<int> primes;
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
        }
    }
    return primes;
}

// Hàm tạo danh sách nửa nguyên tố
unordered_set<int> generateSemiPrimes(const vector<int>& primes, int N) {
    unordered_set<int> semiPrimes;
    for (size_t i = 0; i < primes.size(); i++) {
        for (size_t j = i; j < primes.size(); j++) { // i = j để cho phép lặp lại
            int semiPrime = primes[i] * primes[j];
            if (semiPrime < N) { // Kiểm tra xem nửa nguyên tố có nhỏ hơn N không
                semiPrimes.insert(semiPrime);
            }
        }
    }
    return semiPrimes;
}

// Hàm kiểm tra xem số có phải nửa nguyên tố không
bool isSemiPrime(int num, const unordered_set<int>& semiPrimes) {
    return semiPrimes.find(num) != semiPrimes.end();
}

// Hàm tìm các cặp số nửa nguyên tố
void findSemiPrimePairs(int n, const unordered_set<int>& semiPrimes) {
    cout << "Cac cap so nua nguyen to co tong la so nua nguyen to:" << endl;
    for (const int& semiPrime1 : semiPrimes) {
        for (const int& semiPrime2 : semiPrimes) {
            int sum = semiPrime1 + semiPrime2;
            if (isSemiPrime(sum, semiPrimes)) {
                cout << "(" << semiPrime1 << ", " << semiPrime2 << ")" << endl;
            }
        }
    }
}

// Hàm in ra các số nửa nguyên tố
void printSemiPrimes(const unordered_set<int>& semiPrimes) {
    cout << "Cac so nua nguyen to:" << endl;
    for (const int& semiPrime : semiPrimes) {
        cout << semiPrime << " ";
    }
    cout << endl;
}

int main() {
    int n;
    cout << "Nhap so N: ";
    cin >> n;

    // Tạo danh sách các số nguyên tố
    vector<int> primes = sieveOfEratosthenes(n);
    
    // Tạo danh sách các số nửa nguyên tố nhỏ hơn N
    unordered_set<int> semiPrimes = generateSemiPrimes(primes, n);

    // In ra các số nửa nguyên tố
    printSemiPrimes(semiPrimes);
    
    // Tìm các cặp số nửa nguyên tố có tổng là số nửa nguyên tố
    findSemiPrimePairs(n, semiPrimes);

    cout << "Nhap M de kiem tra so nua nguyen to: ";
    int M;
    cin >> M;
    if (M < n && semiPrimes.count(M) > 0) { // Sử dụng .count() để kiểm tra sự tồn tại
        cout << "M co ton tai";
    } else {
        cout << "M khong ton tai";
    }
    return 0;
}
