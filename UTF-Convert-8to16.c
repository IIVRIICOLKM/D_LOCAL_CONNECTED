// Created by 정찬형 on 4/16/24.
// Feat : Make UTF-8-Identifier, testConvert8to16 and testConvert8to16 by 장효제 on 4/18/24.
//
#include "UTF-Convert-8to16.h"

int main(void)
{
    UTF8 utf8_string[] = u8"가나다라";

    UTF16 utf16_buffer[50];

    printf("%d ", utf8_string[3]);

    int result = utf8_to_utf16(utf8_string, utf8_string + sizeof(utf8_string), utf16_buffer, utf16_buffer + sizeof(utf16_buffer) / sizeof(UTF16));

    if (result < 0)
        printf("변환 과정에서 에러 발생");
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
            // 1바이트 문자 (ASCII 문자)
            codepoint = first_byte;
            extra_bytes_needed = 0;
        }
        else if ((first_byte & 0xE0) == 0xC0) {
            // 2바이트 문자
            codepoint = first_byte & 0x1F;
            extra_bytes_needed = 1;
        }
        else if ((first_byte & 0xF0) == 0xE0) {
            // 3바이트 문자
            codepoint = first_byte & 0x0F;
            extra_bytes_needed = 2;
        }
        else if ((first_byte & 0xF8) == 0xF0) {
            // 4바이트 문자
            codepoint = first_byte & 0x07;
            extra_bytes_needed = 3;
        }
        else {
            // 잘못된 UTF-8 문자 형식
            return -1;  // 에러 처리: 유효하지 않은 UTF-8 형식
        }
        // 추가 바이트 처리
        for (unsigned int i = 0; i < extra_bytes_needed; ++i) {
            if ((sourcestart++ >= sourceend) || ((*sourcestart & 0xC0) != 0x80)) {
                return -1;  // 에러 처리: 유효하지 않은 UTF-8 형식
            }
            codepoint = (codepoint << 6) | (*sourcestart & 0x3F);
        }
        // UTF-16으로 변환
        if (target >= targetend) {
            return -1;  // 에러 처리: 버퍼 공간 부족
        }
        if (codepoint <= 0xFFFF) {
            // BMP (Basic Multilingual Plane)에 속하는 경우
            *target++ = (UTF16)codepoint;
        }
        
        else {
            return -1;  // 에러 처리: 유효하지 않은 유니코드 코드 포인트
        }

        // 다음 바이트로 이동
        ++sourcestart;
    }
    // 변환된 UTF-16 문자열 길이 반환
    return target - targetstart;}

/*else if (codepoint <= 0x10FFFF) {
            // Supplementary plane에 속하는 경우 (UTF-16 surrogate pair 사용)
            if (target + 1 >= targetend) {
                return -1;  // 에러 처리: 버퍼 공간 부족
            }
            codepoint -= 0x10000;
            *target++ = (UTF16)((codepoint >> 10) + 0xD800);
            *target++ = (UTF16)((codepoint & 0x3FF) + 0xDC00);
        } 4바이트 처리과정*/ 