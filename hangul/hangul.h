/* libhangul
 * Copyright (C) 2004 - 2006 Choe Hwanjin
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef _HANGUL_H_
#define _HANGUL_H_

#include <wchar.h>
#include <stdbool.h>
#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/* hangulctype.c */
enum {
    HANGUL_CHOSEONG_FILLER  = 0x115f,   /* hangul choseong filler */
    HANGUL_JUNGSEONG_FILLER = 0x1160    /* hangul jungseong filler */
};

typedef uint32_t ucschar;

bool hangul_is_choseong(ucschar c);
bool hangul_is_jungseong(ucschar c);
bool hangul_is_jongseong(ucschar c);
bool hangul_is_choseong_conjoinable(ucschar c);
bool hangul_is_jungseong_conjoinable(ucschar c);
bool hangul_is_jongseong_conjoinable(ucschar c);
bool hangul_is_syllable(ucschar c);
bool hangul_is_jaso(ucschar c);
bool hangul_is_jamo(ucschar c);

ucschar hangul_jaso_to_jamo(ucschar ch);
ucschar hangul_choseong_to_jamo(ucschar ch);
ucschar hangul_jungseong_to_jamo(ucschar ch);
ucschar hangul_jongseong_to_jamo(ucschar ch);

ucschar hangul_choseong_to_jongseong(ucschar ch);
ucschar hangul_jongseong_to_choseong(ucschar ch);
void    hangul_jongseong_dicompose(ucschar ch, ucschar* jong, ucschar* cho);

ucschar hangul_jaso_to_syllable(ucschar choseong,
				ucschar jungseong,
				ucschar jongseong);

/* hangulinputcontext.c */
typedef struct _HangulJamoCombination HangulJamoCombination;
typedef struct _HangulBuffer          HangulBuffer;
typedef struct _HangulInputContext    HangulInputContext;
typedef bool (*HangulICFilter) (ucschar*, ucschar, ucschar, ucschar, void*);

typedef enum {
    HANGUL_KEYBOARD_2,
    HANGUL_KEYBOARD_32,
    HANGUL_KEYBOARD_3FINAL,
    HANGUL_KEYBOARD_390,
    HANGUL_KEYBOARD_3NOSHIFT,
    HANGUL_KEYBOARD_3YETGUL
} HangulKeyboardType;

enum {
    HANGUL_OUTPUT_SYLLABLE,
    HANGUL_OUTPUT_JAMO
};

enum {
    HANGUL_INPUT_FILTER_JAMO,
    HANGUL_INPUT_FILTER_JASO
};

HangulInputContext* hangul_ic_new(HangulKeyboardType keyboard);
void hangul_ic_delete(HangulInputContext *hic);
bool hangul_ic_process(HangulInputContext *hic, int ascii);
void hangul_ic_reset(HangulInputContext *hic);
bool hangul_ic_backspace(HangulInputContext *hic);
bool hangul_ic_is_empty(HangulInputContext *hic);
int  hangul_ic_dvorak_to_qwerty(int qwerty);

void hangul_ic_set_output_mode(HangulInputContext *hic, int mode);
void hangul_ic_set_keyboard(HangulInputContext *hic,
			    HangulKeyboardType keyboard);
void hangul_ic_set_filter(HangulInputContext *hic,
			  HangulICFilter func, void *user_data);

const ucschar* hangul_ic_get_preedit_string(HangulInputContext *hic);
const ucschar* hangul_ic_get_commit_string(HangulInputContext *hic);
const ucschar* hangul_ic_flush(HangulInputContext *hic);

/* hanja.c */
typedef struct _Hanja Hanja;
typedef struct _HanjaList HanjaList;
typedef struct _HanjaTable HanjaTable;

HanjaTable*  hanja_table_load(const char *filename);
HanjaList*   hanja_table_match_prefix(const HanjaTable* table, const char *key);
HanjaList*   hanja_table_match_suffix(const HanjaTable* table, const char *key);
void         hanja_table_destroy(HanjaTable *table);

int          hanja_list_get_size(const HanjaList *list);
const char*  hanja_list_get_key(const HanjaList *list);
const Hanja* hanja_list_get_nth(const HanjaList *list, int n);
const char*  hanja_list_get_nth_value(const HanjaList *list, int n);
const char*  hanja_list_get_nth_comment(const HanjaList *list, int n);
void         hanja_list_destroy(HanjaList *list);

const char*  hanja_get_key(const Hanja* hanja);
const char*  hanja_get_value(const Hanja* hanja);
const char*  hanja_get_comment(const Hanja* hanja);

#ifdef __cplusplus
}
#endif

#endif /* _HANGUL_H_ */
