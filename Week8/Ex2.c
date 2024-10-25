#include <stdio.h>
#include <stdlib.h>

// Định nghĩa cấu trúc Nut cho danh sách liên kết vòng
struct Nut {
    int nguoiChoi;          // Lưu số của người chơi
    struct Nut* tiepTheo;   // Con trỏ đến người tiếp theo trong vòng
};

// Hàm tạo một nút mới với người chơi được chỉ định
struct Nut* taoNut(int nguoiChoi) {
    struct Nut* nutMoi = (struct Nut*)malloc(sizeof(struct Nut));
    nutMoi->nguoiChoi = nguoiChoi;
    nutMoi->tiepTheo = NULL;
    return nutMoi;
}

// Hàm khởi tạo danh sách liên kết vòng với N người chơi
struct Nut* taoVongTron(int N) {
    struct Nut *dau = taoNut(1);  // Người chơi đầu tiên
    struct Nut *hienTai = dau;
    for (int i = 2; i <= N; i++) {
        hienTai->tiepTheo = taoNut(i);
        hienTai = hienTai->tiepTheo;
    }
    hienTai->tiepTheo = dau;  // Đóng vòng tròn bằng cách trỏ người cuối về đầu
    return dau;
}

// Hàm thực hiện loại bỏ theo luật Josephus
int josephus(int N, int M) {
    struct Nut* dau = taoVongTron(N);
    struct Nut* truoc = NULL;
    struct Nut* hienTai = dau;

    // Lặp lại cho đến khi còn lại một người
    while (hienTai->tiepTheo != hienTai) {  // Khi chỉ còn một người
        for (int dem = 1; dem < M; dem++) {  // Đếm tới M người
            truoc = hienTai;
            hienTai = hienTai->tiepTheo;
        }
        // Loại bỏ người chơi thứ M
        truoc->tiepTheo = hienTai->tiepTheo;
        printf("Nguoi choi %d bi loai.\n", hienTai->nguoiChoi);
        free(hienTai);  // Giải phóng bộ nhớ của người chơi bị loại
        hienTai = truoc->tiepTheo;  // Bắt đầu từ người kế tiếp
    }
    int nguoiThang = hienTai->nguoiChoi;
    free(hienTai);  // Giải phóng bộ nhớ của người chiến thắng
    return nguoiThang;
}

int main() {
    int N, M;
    printf("Nhap so nguoi choi N: ");
    scanf("%d", &N);
    printf("Nhap vi tri nguoi bi loai M: ");
    scanf("%d", &M);

    int nguoiThang = josephus(N, M);
    printf("Nguoi chien thang cuoi cung la nguoi choi so %d.\n", nguoiThang);

    return 0;
}
