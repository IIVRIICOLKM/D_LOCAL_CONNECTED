//
// Created by ������ on 4/16/24.
// Feat : Make UTF-8-Identifier, testConvert8to16 and testConvert8to16 by ��ȿ�� on 4/18/24.

#ifndef INC_05_UNICODE_ORG_CONVERTUTF_C_UTF_CONVERT_8TO16_H
#define INC_05_UNICODE_ORG_CONVERTUTF_C_UTF_CONVERT_8TO16_H

#include <stdio.h>      // stderr �� fprintf�� ����ҷ���
#include <stddef.h>     // size_t�� ����ҷ���
#include "ConvertUTF.h" //  UTF8, UTF16 � ���� ���ǰ� ����

int utf8_to_utf16(const UTF8* sourcestart, const UTF8* sourceend, UTF16* targetstart, UTF16* targetend);
#endif
