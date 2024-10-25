
# Output ( Bài 1 Tuần 8 )
![alt text](<Screenshot 2024-10-25 at 14.23.48.png>)
# ( Bài 2 Tuần 8 ) Mô tả giải thuật  Josephus với danh sách liên kết vòng

## 1. Khởi tạo danh sách vòng với `N` người chơi
- Tạo một danh sách liên kết vòng với `N` nút, mỗi nút đại diện cho một người chơi được đánh số từ `1` đến `N`.
- Liên kết nút cuối cùng trở lại nút đầu tiên để tạo thành vòng tròn.

## 2. Mô phỏng quy trình truyền bóng và loại bỏ

### Bắt đầu:
- Bắt đầu với người chơi số `1`.

### Vòng lặp chính:
- Lặp lại quá trình sau cho đến khi chỉ còn một người chơi duy nhất:
  
  - **Đếm tới người thứ `M` trong vòng tròn**:
    - Duyệt qua danh sách liên kết vòng từ người chơi hiện tại, đi qua `M-1` người tiếp theo.

  - **Loại bỏ người chơi thứ `M`**:
    - Cập nhật con trỏ của người trước đó để bỏ qua người chơi thứ `M` và trỏ đến người kế tiếp của người này.
    - Giải phóng bộ nhớ của người bị loại bỏ.

  - **Chuyển sang người chơi kế tiếp**:
    - Người ngay sau người bị loại sẽ bắt đầu cho lượt chơi tiếp theo.

## 3. Trả về người chơi còn lại
- Khi chỉ còn một người chơi trong danh sách, đó là người chiến thắng.
# Output ( Bài 2 Tuần 8 )
![alt text](<Screenshot 2024-10-25 at 14.41.54.png>)