#include <stdio.h>     
#include <stdlib.h>   
#include <string.h>    

//cấu trúc Ngay để lưu ngày, tháng, năm sinh của sinh viên
struct Ngay {
    int ngay, thang, nam;
};

//cấu trúc Student để lưu thông tin sinh viên
struct Student {
    char StudentCode[8];       // mã số sinh viên
    char FullName[50];        // họ và tên
    int sex;                 // giới tính (0: nữ, 1: nam)
    struct Ngay BirthDay;   // ngày sinh
    char address[50];      // quê quán
    char class[12];       // lớp
    char khoa[20];       // khoa
};

//cấu trúc Node cho danh sách liên kết đơn chứa sinh viên
struct Node {
    struct Student data;     // thông tin sinh viên trong node
    struct Node *link;      // con trỏ liên kết đến node kế tiếp
};

//cấu trúc List chứa con trỏ đầu và cuối danh sách
struct List {
    struct Node *first;      // con trỏ đến node đầu tiên của danh sách
    struct Node *last;      // con trỏ đến node cuối cùng của danh sách
};

//khởi tạo danh sách rỗng
void initList(struct List *list) {
    list->first = NULL;      // khởi tạo con trỏ đầu là NULL
    list->last = NULL;      // khởi tạo con trỏ cuối là NULL
}

// tạo một node mới cho sinh viên
struct Node* createNode(struct Student sv) {
    struct Node *newNode = (struct Node*) malloc(sizeof(struct Node)); // cấp phát bộ nhớ cho node
    newNode->data = sv;                                               // gán dữ liệu sinh viên vào node
    newNode->link = NULL;                                            // khởi tạo liên kết tiếp theo là NULL
    return newNode;                                                 // trả về con trỏ đến node mới
}

// Hàm chèn sinh viên vào danh sách theo thứ tự mã sinh viên
void insertSorted(struct List *list, struct Student sv) {
    struct Node *newNode = createNode(sv);     // tạo node mới chứa sinh viên
    if (list->first == NULL || strcmp(sv.StudentCode, list->first->data.StudentCode) < 0) {
        // trường hợp danh sách rỗng hoặc mã sinh viên mới nhỏ hơn mã đầu tiên
        newNode->link = list->first;        // liên kết node mới vào đầu danh sách
        list->first = newNode;             // cập nhật con trỏ đầu danh sách
    } else {
        // tìm vị trí để chèn node mới vào
        struct Node *current = list->first;
        while (current->link != NULL && strcmp(sv.StudentCode, current->link->data.StudentCode) > 0) {
            current = current->link;          // duyệt danh sách tìm vị trí chèn
        }
        newNode->link = current->link;      // liên kết node mới vào danh sách
        current->link = newNode;           // cập nhật liên kết của node trước
    }
}

// Hàm hiển thị danh sách sinh viên
void printList(struct List list) {
    struct Node *current = list.first;     // con trỏ duyệt danh sách từ đầu
    while (current != NULL) {
        // in ra mã sinh viên, họ tên, ngày sinh
        printf("Mã SV: %s, Họ tên: %s, Ngày sinh: %d/%d/%d\n",
               current->data.StudentCode, current->data.FullName,
               current->data.BirthDay.ngay, current->data.BirthDay.thang, current->data.BirthDay.nam);
        current = current->link;      // di chuyển đến node tiếp theo
    }
}

// Hàm tìm các sinh viên có cùng ngày sinh
void findSameBirthday(struct List list) {
    int found = 0;                         // biến cờ đánh dấu khi tìm thấy sinh viên cùng ngày sinh
    struct Node *current = list.first;    // con trỏ duyệt danh sách từ đầu
    while (current != NULL) {
        struct Node *compare = current->link;   // con trỏ để so sánh với các sinh viên sau đó
        int sameFound = 0;                     // biến cờ để in thông tin sinh viên một lần duy nhất
        while (compare != NULL) {
            if (compare->data.BirthDay.ngay == current->data.BirthDay.ngay &&
                compare->data.BirthDay.thang == current->data.BirthDay.thang &&
                compare->data.BirthDay.nam == current->data.BirthDay.nam) {
                if (!sameFound) {                 // in thông tin sinh viên đầu tiên có ngày sinh trùng
                    printf("Mã SV: %s, Họ tên: %s, Ngày sinh: %d/%d/%d\n",
                           current->data.StudentCode, current->data.FullName,
                           current->data.BirthDay.ngay, current->data.BirthDay.thang, current->data.BirthDay.nam);
                    sameFound = 1;
                }
                printf("Mã SV: %s, Họ tên: %s\n", compare->data.StudentCode, compare->data.FullName); // in thông tin sinh viên trùng
                found = 1;
            }
            compare = compare->link;    // chuyển đến sinh viên kế tiếp
        }
        current = current->link;      // chuyển đến sinh viên tiếp theo trong danh sách
    }
    if (!found) {
        printf("Không tìm thấy sinh viên cùng ngày sinh\n"); 
    }
}

// Hàm xóa các sinh viên có cùng ngày sinh
void removeSameBirthday(struct List *list) {
    struct Node *current = list->first;   // con trỏ duyệt danh sách từ đầu
    struct Node *prev = NULL;            // con trỏ giữ node trước node hiện tại
    while (current != NULL) {
        struct Node *compare = current->link;       // con trỏ so sánh với các sinh viên sau đó
        struct Node *comparePrev = current;        // con trỏ giữ node trước node compare
        int duplicateFound = 0;                   // biến cờ để kiểm tra sinh viên trùng
        while (compare != NULL) {
            if (compare->data.BirthDay.ngay == current->data.BirthDay.ngay &&
                compare->data.BirthDay.thang == current->data.BirthDay.thang &&
                compare->data.BirthDay.nam == current->data.BirthDay.nam) {
                duplicateFound = 1;                    // đánh dấu tìm thấy trùng ngày sinh
                comparePrev->link = compare->link;    // loại bỏ node sinh viên trùng khỏi danh sách
                free(compare);                       // giải phóng bộ nhớ
                compare = comparePrev->link;        // chuyển đến sinh viên tiếp theo
            } else {
                comparePrev = compare;            // lưu lại vị trí của sinh viên trước
                compare = compare->link;
            }
        }
        if (duplicateFound) {                           // nếu sinh viên hiện tại có trùng ngày sinh
            if (prev == NULL) {
                list->first = current->link;          // nếu là sinh viên đầu tiên, cập nhật đầu danh sách
                free(current);                       // giải phóng bộ nhớ
                current = list->first;              // chuyển đến sinh viên tiếp theo
            } else {
                prev->link = current->link;       // liên kết lại danh sách
                free(current);                   // giải phóng bộ nhớ
                current = prev->link;           // chuyển đến sinh viên tiếp theo
            }
        } else {
            prev = current;                  // lưu lại node hiện tại trước khi chuyển tiếp
            current = current->link;
        }
    }
}

int main() {
    struct List list;              // tạo danh sách sinh viên
    initList(&list);               // khởi tạo danh sách rỗng
    
    // Khởi tạo thông tin sinh viên
    struct Student sv1 = {"20224436", "Nguyen Duc Hanh", 1, {27, 11, 2004}, "Thai Binh", "ET-E9 01", "DTVT"};
    struct Student sv2 = {"20224442", "Ta Nguyen Long", 0, {04, 04, 2004}, "Phu Tho", "ET-E9 01", "DTVT"};
    struct Student sv3 = {"20224403", "Le Duc Anh", 1, {18, 06, 2004}, "Ha Nam", "ET-E9 01", "DTVT"};
    struct Student sv4 = {"20224447", "Dang Cong Hoang Nam", 0, {27, 11, 2004}, "Ha Noi", "ET-E8 02", "IT-E0"};
     
     
    insertSorted(&list, sv1);               // chèn sinh viên vào danh sách theo thứ tự mã số
    insertSorted(&list, sv2);
    insertSorted(&list, sv3);
    insertSorted(&list, sv4);
    printf("Danh sách sinh viên:\n");
    printList(list);                   // in danh sách sinh viên
    
    printf("\nCác sinh viên có cùng ngày sinh:\n");
    findSameBirthday(list);         // tìm sinh viên có cùng ngày sinh
    
    printf("\nDanh sách sinh viên sau khi xóa sinh viên cùng ngày sinh:\n");
    removeSameBirthday(&list);   // xóa sinh viên có cùng ngày sinh
    printList(list);            // in danh sách sau khi xóa
    return 0;
}
