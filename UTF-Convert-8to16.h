//
// Created by 정찬형 on 4/16/24.
// Feat : Make UTF-8-Identifier, testConvert8to16 and testConvert8to16 by 장효제 on 4/18/24.

#ifndef INC_05_UNICODE_ORG_CONVERTUTF_C_UTF_CONVERT_8TO16_H
#define INC_05_UNICODE_ORG_CONVERTUTF_C_UTF_CONVERT_8TO16_H

#include <stdio.h>      // stderr 및 fprintf을 사용할려고
#include <stddef.h>     // size_t을 사용할려고
#include "ConvertUTF.h" //  UTF8, UTF16 등에 대한 정의가 포함

int utf8_to_utf16(const UTF8* sourcestart, const UTF8* sourceend, UTF16* targetstart, UTF16* targetend);
#endif
