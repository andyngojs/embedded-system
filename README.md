# Hệ Thống Nhúng - Embedded System

FEIT - HOU

AVR Programming

### Các phần mềm sử dụng - Softwares

- Proteus (thiết kế, mô phỏng mạch vẽ )

- CodeVisionAVR (Viết code lập trình cho vi điều khiển AVR)

### Nội dung lập trình nhúng AVR - Contents of AVR programming

0. Lập trình cơ bản ngôn ngữ C

1. Hoạt động cổng vào/ra - I/O Ports

2. Quét Led 7 Segment

3. Ngắt ngoài - Interrupt

4. Bộ định thời Timer/Counter

5. Bộ chuyển đổi ADC

6. Lập trình với led matrix

### Tài Liệu Tham Khảo

Hướng dẫn cài đặt công cụ phát triển lập trình AVR: https://www.youtube.com/playlist?list=PL8hCCHkwoQYa71E5tZeYC5ZZ4GLOVx1hV

Học AVR full: [Lập Trình AVR](https://www.youtube.com/playlist?list=PL8hCCHkwoQYa5Khk7FyU9WRJCEwIKyOMf)

Tài liệu học AVR Tiếng Việt: http://www.hocavr.com

Tool lấy mã hiển thị led matrix: https://xantorohara.github.io/led-matrix-editor/

Mã hiển thị Led 7 Segment:

- Hiện thị chữ số không có dấu chấm:

```
unsigned char number[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
```

- Hiện thị chữ số có dấu chấm:

```
unsigned char fullNumber[10] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x10};
```
