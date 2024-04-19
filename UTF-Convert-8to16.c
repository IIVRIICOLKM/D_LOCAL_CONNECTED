// Created by ������ on 4/16/24.
// Feat : Make UTF-8-Identifier, testConvert8to16 and testConvert8to16 by ��ȿ�� on 4/18/24.
//
#include "UTF-Convert-8to16.h"

int main(void)
{
    UTF8 utf8_string[] = u8"�����ٶ�";

    UTF16 utf16_buffer[50];

    printf("%d ", utf8_string[3]);

    int result = utf8_to_utf16(utf8_string, utf8_string + sizeof(utf8_string), utf16_buffer, utf16_buffer + sizeof(utf16_buffer) / sizeof(UTF16));

    if (result < 0)
        printf("��ȯ �������� ���� �߻�");
    else
    {
        printf("\nUTF-16 string: ");
        for (int i = 0; i < result - 1; i++)
            printf("%04x ", utf16_buffer[i]);
        printf("\n");
    }
    return 0;
}

int utf8_to_utf16(const UTF8* sourcestart, const UTF8* sourceend, UTF16* targetstart, UTF16* targetend) {
    UTF16* target = targetstart;

    while (sourcestart < sourceend) {
        unsigned int codepoint;
        unsigned int extra_bytes_needed;
        UTF8 first_byte = *sourcestart;

        if (first_byte < 0x80) {
            // 1����Ʈ ���� (ASCII ����)
            codepoint = first_byte;
            extra_bytes_needed = 0;
        }
        else if ((first_byte & 0xE0) == 0xC0) {
            // 2����Ʈ ����
            codepoint = first_byte & 0x1F;
            extra_bytes_needed = 1;
        }
        else if ((first_byte & 0xF0) == 0xE0) {
            // 3����Ʈ ����
            codepoint = first_byte & 0x0F;
            extra_bytes_needed = 2;
        }
        else if ((first_byte & 0xF8) == 0xF0) {
            // 4����Ʈ ����
            codepoint = first_byte & 0x07;
            extra_bytes_needed = 3;
        }
        else {
            // �߸��� UTF-8 ���� ����
            return -1;  // ���� ó��: ��ȿ���� ���� UTF-8 ����
        }
        // �߰� ����Ʈ ó��
        for (unsigned int i = 0; i < extra_bytes_needed; ++i) {
            if ((sourcestart++ >= sourceend) || ((*sourcestart & 0xC0) != 0x80)) {
                return -1;  // ���� ó��: ��ȿ���� ���� UTF-8 ����
            }
            codepoint = (codepoint << 6) | (*sourcestart & 0x3F);
        }
        // UTF-16���� ��ȯ
        if (target >= targetend) {
            return -1;  // ���� ó��: ���� ���� ����
        }
        if (codepoint <= 0xFFFF) {
            // BMP (Basic Multilingual Plane)�� ���ϴ� ���
            *target++ = (UTF16)codepoint;
        }
        
        else {
            return -1;  // ���� ó��: ��ȿ���� ���� �����ڵ� �ڵ� ����Ʈ
        }

        // ���� ����Ʈ�� �̵�
        ++sourcestart;
    }
    // ��ȯ�� UTF-16 ���ڿ� ���� ��ȯ
    return target - targetstart;}

/*else if (codepoint <= 0x10FFFF) {
            // Supplementary plane�� ���ϴ� ��� (UTF-16 surrogate pair ���)
            if (target + 1 >= targetend) {
                return -1;  // ���� ó��: ���� ���� ����
            }
            codepoint -= 0x10000;
            *target++ = (UTF16)((codepoint >> 10) + 0xD800);
            *target++ = (UTF16)((codepoint & 0x3FF) + 0xDC00);
        } 4����Ʈ ó������*/ 