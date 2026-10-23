#include "common.h"
#include "libpress.h"
#include "fixed_addrs.h"
#include <psxsdk/libgpu.h>
#include <psxsdk/libsnd.h>
#include <psxsdk/libetc.h>
#include <psxsdk/libcd.h>
#include <psxsdk/libgte.h>
#include <psxsdk/libapi.h>
#include <psxsdk/libspu.h>
#include <psxsdk/kernel.h>
#include "game.h"
#include "pad_axis.h"
#include "input.h"
#include "menu.h"

void func_8006BD68(void);

extern s32 strlen(char *);
extern s16 gMusicVolumew15[] asm("gMusicVolume.NON_MATCHING");
extern s16 gCdVolumew15[] asm("gCdVolume.NON_MATCHING");
extern u8 D_800A36E1w15[] asm("D_800A36E1.NON_MATCHING");
extern s8 gPadTypew18c[] asm("gPadType.NON_MATCHING");

extern void HeapFree(void *ptr);
extern s8 D_800A3860S8[] asm("D_800A3860");
extern s32 D_800A37D0[];
extern char *strcpy(char *, const char *);
extern u8 gPlayerDriver[];
extern char *strcat(char *, char *);
extern u8 *D_800AE178[];
extern s32 D_8009A31C[];
extern void MenuUpdateObjectPosition(MenuObj *first, u8 friction);
extern void MenuDrawObjectList(MenuObj *first, s32 value);
extern u8 gSelectedTrack[];
extern void MenuFontSetS32(s32, s32) asm("MenuFontSet");
extern s32 MenuTextCenterOffset(s16, s32);
asm(".globl MenuDrawStringW");
void GraphicsQueueDrawEnvironment(u8 arg0, s32 arg1, s32 arg2, s32 arg3,
                                  s32 arg4, s32 arg5);
u8 RaceFindDriverPosition(u8 value);
void CardCloseFile(s32 handle);
u8 CardDeleteFile(char *path);
void CardTestAndDisableEvents(void);
void CardEnableAndTestEvents(void);
s32 CardCheckStatus(s32 slot, u8 returnOnBusy);
s32 CardFindFirstFile(char *path, struct DIRENTRY *entry);
s32 CardFormat(s32 slot);
s32 func_80059F0C(s32 slot);
s32 CardOpenFile(char *path, s32 flags);
s32 CardReadSectors(struct DIRENTRY *entry, s32 firstSector, s32 sectorCount,
                    s32 slot, s32 buffer);
s32 CardWriteSectors(struct DIRENTRY *entry, s32 firstSector, s32 sectorCount,
                     s32 slot, s32 buffer);
s32 CardCountOtherFileBlocks(s32 slot, char *excludedName);
s16 MenuCharWidth(s8 arg0);
void MenuSetAllObjectOrderingDepths(s16 value);
void func_8005E4A4(u8 *table);
void MenuFormatLapCount(u8 arg0);
void MenuSetTrackLabel(s32 index);
void func_80062D38(s32 arg0, s32 arg1, u8 *arg2);
void func_80062F6C(s32 arg0, s32 arg1);
void func_800641EC(void);
void MenuSetTextObject(MenuObj *obj, u8 a, u8 b, s32 c, u8 d, s32 e);

void func_80067F34(s32 page, s32 track) {
    extern char *D_8009A474[];
    extern s32 D_8009AC80[];
    MenuObj *obj;
    MenuObj *next;
    u8 *name;
    u8 *entry;
    s32 value;
    s32 w;
    s32 sum;
    s32 sum2;
    s32 recordOff;
    s32 i;
    s32 j;
    s32 k;
    s32 idx;
    char *string;
    s32 cnt;
    char buf[0x48];

    obj = *(MenuObj **)((u8 *)D_800A3668Absolute - 0x5C + (page & 0xFF) * 4);
    MenuFontSetS32(2, 3);
    strcpy(buf, D_8009A474[0]);
    strcat(buf, (char *)D_8009A31C[track & 0xFF]);
    w = MenuStringWidth(buf);
    sum = (0x140 - w) / 2;
    obj->x = sum;
    obj->targetX = sum;
    obj->drawOffsetX = obj->x;
    next = obj->next;
    w = MenuStringWidth(D_8009A474[0]);
    {
        s32 hdrH;
        MenuTextPacket *pktH;
        hdrH = next->orderingDepth;
        sum2 = (u16)obj->x + w;
        next->x = sum2;
        next->drawOffsetX = sum2;
        string = (char *)D_8009A31C[track & 0xFF];
        pktH = next->primitive;
        pktH->unk1 = 2;
        pktH->unk2 = 3;
        pktH->unk3 = 0;
        cnt = ((u8 *)D_800A3A54)[4];
        pktH->orderingDepth = hdrH;
        pktH->text = (s32)string;
        next->orderingDepth = hdrH;
    }
    obj = *(MenuObj **)((u8 *)D_800A3854Absolute + (page & 0xFF) * 4 + 4);
    i = 0;
    if (cnt > 0) {
        recordOff = (track & 0xFF) * 0xC;
        do {
            j = 0;
            do {
                s32 hdrL;
                MenuTextPacket *pktL;
                s32 flagL;
                s32 t;
                switch (j) {
                case 0:
                    k = 0;
                    entry = (u8 *)gDriverNames;
                    name = (u8 *)(i * 0xE8) +
                           (u32) * (u8 **)((u8 *)D_800A3668Absolute - 0x74);
                    do {
                        if (strcmp((char *)name, *(char **)entry) == 0) {
                            break;
                        }
                        k++;
                        entry += 4;
                    } while (k < 0x18);
                    asm("" : "=r"(idx) : "0"(k));
                    value = D_8009AC80[idx & 0xFF];
                    break;
                case 1:
                    value =
                        *(i * 0xE8 + *(u8 **)((u8 *)D_800A3668Absolute - 0x74) +
                          recordOff + 0x1C);
                    break;
                case 2:
                    value =
                        *(i * 0xE8 + *(u8 **)((u8 *)D_800A3668Absolute - 0x74) +
                          recordOff + 0x1D);
                    break;
                case 3:
                    value =
                        *(i * 0xE8 + *(u8 **)((u8 *)D_800A3668Absolute - 0x74) +
                          recordOff + 0x1E);
                    break;
                case 4:
                    value =
                        *(i * 0xE8 + *(u8 **)((u8 *)D_800A3668Absolute - 0x74) +
                          recordOff + 0x1F);
                    break;
                case 5:
                    value = *(s32 *)(i * 0xE8 +
                                     *(u8 **)((u8 *)D_800A3668Absolute - 0x74) +
                                     recordOff + 0x20);
                    break;
                }
                flagL = 0;
                if (j != 0) {
                    t = j != 5;
                    flagL = t;
                    asm("" : : "r"(t));
                }
                hdrL = obj->orderingDepth;
                pktL = obj->primitive;
                pktL->unk1 = 2;
                pktL->unk2 = 3;
                pktL->text = value;
                pktL->unk3 = flagL;
                pktL->orderingDepth = hdrL;
                obj->orderingDepth = hdrL;
                obj = obj->next;
                j++;
            } while (j < 6);
            i++;
        } while (i < ((u8 *)D_800A3A54)[4]);
    }
}

void CardMenuCreateRecordTable(u8 track) {
    extern char *D_8009A474[];
    extern s8 D_800A3944;
    extern s8 D_800A39DC;
    extern MenuObj *D_800A3870;
    extern u8 D_800A3894;
    extern MenuObj *D_800A37D4;
    extern s16 MenuStringWidth(u8 * text);
    extern MenuObj *MenuCreateFlatRect(s32, s32, s32, s32, s32, s32, s32, s32,
                                       s32, s32);
    extern MenuObj *MenuCreateTextObject(s32, s32);
    extern s32 D_8009A478[];
    extern s16 D_8009B1AC[];
    extern s16 D_8009B1BA[];
    extern s32 D_8009A48C[];
    extern u8 D_800A3A58Lui asm("D_800A3A58Absolute");
    extern MenuObj *D_800A3900Obj asm("D_800A3900.NON_MATCHING");
    /* Sized, so [0] goes through $gp; [page] needs the lui alias. */
    extern MenuObj *D_800A360C[2];
    extern MenuObj *D_800A360CArr[] asm("D_800A360C.NON_MATCHING");
    extern MenuObj *D_800A3858Arr[] asm("D_800A3858.NON_MATCHING");
    extern MenuObj *D_800A3918Arr[] asm("D_800A3918.NON_MATCHING");
    MenuObj *tail;
    MenuObj *obj;
    s32 i;
    s32 j;
    s32 page;
    s32 y;
    s32 w;
    s32 colX;
    s32 x;
    char buf[0x40];

    i = 0;
    do {
        tail =
            MenuCreateFlatRect(0, 0x27, 0x140, 0xC8, 0, 0x10, 0x10, 0x10, 1, 1);
        if (i == 0) {
            D_800A3900Obj = tail;
        } else {
            D_800A3900Obj->next = tail;
        }
        tail->orderingDepth = 0x3FD;
        i++;
    } while (i < 2);

    if (D_800A3A58Lui == 0) {
        tail = MenuCreateTextObject(0x64, 0x66);
        D_800A360C[0] = tail;
        tail->drawOffsetX = 0;
        tail->orderingDepth = 0x32;
        {
            s32 str;
            MenuTextPacket *pkt;
            str = D_8009A48C[0];
            pkt = tail->primitive;
            pkt->unk1 = 2;
            pkt->unk2 = 3;
            pkt->text = str;
            pkt->unk3 = 0;
            pkt->orderingDepth = 0x32;
            tail->orderingDepth = 0x32;
        }
        return;
    }

    for (page = 0; page < 2; page++) {
        tail = MenuCreateTextObject(0, 0x2A);
        D_800A360CArr[page] = tail;
        MenuFontSetS32(2, 3);
        strcpy(buf, D_8009A474[0]);
        strcat(buf, (char *)D_8009A31C[track]);
        w = (s16)MenuStringWidth(buf);
        x = (0x140 - w) / 2;
        tail->x = x;
        tail->targetX = x;
        tail->orderingDepth = 0x32;
        tail->red = 0x80;
        tail->green = 0x80;
        tail->blue = 0xC0;
        {
            s32 hdr;
            s32 str;
            MenuTextPacket *pkt;
            hdr = tail->orderingDepth;
            str = (s32)D_8009A474[0];
            pkt = tail->primitive;
            pkt->unk1 = 2;
            pkt->unk2 = 3;
            pkt->text = str;
            pkt->unk3 = 0;
            pkt->orderingDepth = hdr;
            tail->orderingDepth = hdr;
        }
        w = (s16)MenuStringWidth(D_8009A474[0]);
        obj = MenuCreateTextObject(tail->x + w, 0x2A);
        obj->drawOffsetX = obj->x;
        obj->orderingDepth = 0x32;
        obj->red = 0x80;
        obj->green = 0x80;
        obj->blue = 0xC0;
        {
            s32 str;
            MenuTextPacket *pkt;
            s32 hdr;
            str = D_8009A31C[track];
            pkt = obj->primitive;
            hdr = obj->orderingDepth;
            pkt->unk1 = 2;
            pkt->unk2 = 3;
            pkt->text = str;
            pkt->unk3 = 0;
            pkt->orderingDepth = hdr;
            obj->orderingDepth = hdr;
        }
        tail->next = obj;
        tail = obj;

        /* Column headings, alternating between two rows and colours. */
        for (i = 0; i < 5; i++) {
            colX = D_8009B1BA[i];
            if (!(i & 1)) {
                y = 0x39;
            } else {
                y = 0x48;
            }
            obj = MenuCreateTextObject(colX, y);
            obj->drawOffsetX = colX;
            obj->orderingDepth = 0x32;
            if (i & 1) {
                obj->red = 0xFF;
                obj->green = 0x80;
                obj->blue = 0x40;
            } else {
                obj->red = 0xC8;
                obj->green = 0x40;
                obj->blue = 0x20;
            }
            {
                s32 str;
                MenuTextPacket *pkt;
                s32 hdr;
                str = D_8009A478[i];
                pkt = obj->primitive;
                hdr = obj->orderingDepth;
                pkt->unk1 = 2;
                pkt->unk2 = 3;
                pkt->text = str;
                pkt->unk3 = 0;
                pkt->orderingDepth = hdr;
                obj->orderingDepth = hdr;
            }
            tail->next = obj;
            tail = obj;
        }

        /* One row of six cells per saved record. */
        y = 0;
        for (i = 0; i < D_800A3A58Lui; i++, y += 15) {
            for (j = 0; j < 6; j++) {
                obj = MenuCreateTextObject(D_8009B1AC[j], y);
                if (i == 0 && j == 0) {
                    D_800A3858Arr[page] = obj;
                } else {
                    tail->next = obj;
                }
                obj->drawOffsetX = obj->x;
                obj->orderingDepth = 0;
                switch (j) {
                case 1:
                case 2:
                case 3:
                case 4:
                    obj->kind = 5;
                    if (j & 1) {
                        obj->red = 0xC8;
                        obj->green = 0x40;
                        obj->blue = 0x20;
                    } else {
                        obj->red = 0xFF;
                        obj->green = 0x80;
                        obj->blue = 0x40;
                    }
                    break;
                case 5:
                    obj->kind = 6;
                    obj->red = 0xC8;
                    obj->green = 0x40;
                    obj->blue = 0x20;
                    break;
                }
                {
                    u8 flag;
                    MenuTextPacket *pkt;
                    s32 hdr;
                    flag = (j != 0 && j != 5);
                    pkt = obj->primitive;
                    hdr = obj->orderingDepth;
                    pkt->unk1 = 2;
                    pkt->unk2 = 3;
                    pkt->text = 0;
                    pkt->unk3 = flag;
                    pkt->orderingDepth = hdr;
                    obj->orderingDepth = hdr;
                }
                tail = obj;
            }
            if (i == D_800A3A58Lui - 1) {
                D_800A3918Arr[page] = tail;
            }
        }
    }

    func_80067F34(0, track);
    D_800A3944 = 0;
    D_800A39DC = 0;
    D_800A3870 = 0;
    D_800A3894 = track;
    D_800A37D4 = D_800A360C[0];
    MenuSetAllObjectOrderingDepths(1000);
}

void func_800686FC(s32 arg0, s32 arg1) {
    extern s32 D_800A3914[];
    extern MenuObj *D_800A37D4;
    extern MenuObj *D_800A3870;
    extern s8 D_800A3944;
    extern s8 D_800A39DC;
    extern MenuObj *D_800A3900Ptr asm("D_800A3900.NON_MATCHING");
    extern MenuObj *D_800A360CHead asm("D_800A360C");
    extern MenuObj *D_800A3858;

    MenuDrawObjectList(D_800A3900Ptr, 0xFF);
    if ((arg0 & 0xFF) == 9 && ((u8 *)D_800A3A54)[4] != 0) {
        if (D_800A37D4 != 0) {
            MenuUpdateObjectPosition(D_800A37D4, 1);
            MenuDrawObjectList(D_800A37D4, 0xFF);
        }
        if (D_800A3870 != 0) {
            MenuUpdateObjectPosition(D_800A3870, 1);
            MenuDrawObjectList(D_800A3870, 0xFF);
        }
    } else {
        MenuDrawObjectList(D_800A360CHead, 0xFF);
    }
    if (D_800A3914[0] != 0) {
        MenuDrawObjectList((MenuObj *)D_800A3914[0], 0xFF);
    }
    switch ((arg0 & 0xFF) - 9) {
    case 0:
        if (((u8 *)D_800A3A54)[4] != 0) {
            GraphicsQueueDrawEnvironment(arg1 & 0xFF, 0, 0x57, 0x140, 0x7B,
                                         0xA);
        }
        break;
    case 1:
        GraphicsQueueDrawEnvironment(arg1 & 0xFF, 0, 0x9D, 0x140, 0x35, 0xA);
        break;
    case 3:
    case 7:
    case 8:
        GraphicsQueueDrawEnvironment(arg1 & 0xFF, 0, 0x39, 0x140, 0x99, 0xA);
        break;
    }
    switch (arg0 & 0xFF) {
    case 0xA:
    case 0xC:
        goto hideIt;
    }
    if ((u8)(arg0 - 0x10) < 2) {
    hideIt:
        MenuDrawObjectList(D_800A3858, 0xFF);
    } else if ((arg0 & 0xFF) == 9) {
        if (((u8 *)D_800A3A54)[4] != 0) {
            if (D_800A37D4 != 0) {
                MenuUpdateObjectPosition(D_800A3854Absolute[D_800A3944 + 1], 1);
                MenuDrawObjectList(D_800A3854Absolute[D_800A3944 + 1], 0xFF);
            }
            if (D_800A3870 != 0) {
                MenuUpdateObjectPosition(D_800A3854Absolute[D_800A39DC + 1], 1);
                MenuDrawObjectList(D_800A3854Absolute[D_800A39DC + 1], 0xFF);
            }
        }
    }
}

/* The original toolchain padded this odd-length jump table with one zero
 * word; the C switch regenerates the table, this restores the pad. */
void __maspsx_include_asm_hack_jtblpad_800686FC() {
    __asm__(".section .rodata # maspsx-keep \n"
            "    .word 0 # maspsx-keep\n"
            "    .section .text # maspsx-keep\n");
}

void func_8006894C(s32 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4) {
    extern MenuObj *D_800A360C[];
    extern MenuObj *D_800A3858Absolute[] asm("D_800A3858.NON_MATCHING");
    MenuObj *node;
    MenuObj *other;
    s32 index;
    s32 v1;

    index = arg0 & 0xFF;
    node = D_800A360C[arg0 & 0xFF];
    if (node != NULL) {
        do {
            node->velocityX = arg3;
            node->x = node->drawOffsetX + arg1;
            node->targetX = node->drawOffsetX + arg2;
            node = node->next;
            index = arg0 & 0xFF;
        } while (node != NULL);
    }
    node = D_800A3858Absolute[arg0 & 0xFF];
    if (arg4 != 0) {
        other = (u8 *)D_800A3858Absolute[(arg0 ^ 1) & 0xFF];
        v1 = other->y;
        v1 -= other->targetY;
    } else {
        v1 = 0;
    }
    if (node != NULL) {
        do {
            node->x = node->drawOffsetX + arg1;
            if (arg4 != 0) {
                node->y = node->targetY + v1;
            }
            node->velocityX = arg3;
            node->targetX = node->drawOffsetX + arg2;
            node = node->next;
        } while (node != NULL);
    }
}

void func_80068A3C(MenuObj *head, MenuObj *other, s32 delta, s32 limit,
                   s32 mid) {
    s16 base;

    if (delta > 0) {
        base = head->y;
        if (limit < base + delta) {
            delta = limit - base;
        }
    } else {
        if (delta < 0) {
            if ((s32)other->y + delta < mid) {
                delta = mid - other->y;
            }
        }
    }
    if (delta != 0) {
        if (head != 0) {
            do {
                head->y += delta;
                head = head->next;
            } while (head != 0);
        }
    }
}

extern s32 D_800A3830Absolute[];
extern s32 D_800A3830Absolute2[];
extern s32 D_800A37F0Absolute[];
extern s32 D_800A37F0Absolute2[];
extern s32 D_800A37F0Absolute3[];
extern u8 gScreenStateNM[] asm("gScreenState.NON_MATCHING");
extern u8 D_800A3A58NM[] asm("D_800A3A58.NON_MATCHING");
extern s16 D_800B9B84NM[] asm("D_800B9B84.NON_MATCHING");
extern MenuObj *D_800A3858NM[] asm("D_800A3858.NON_MATCHING");
extern u8 *D_800A3918NM[] asm("D_800A3918.NON_MATCHING");
extern u8 *D_800A3918NB[] asm("D_800A3918.NON_MATCHING");
void func_80068AC4(s32 arg0, s32 arg1, s32 arg2) {
    extern u8 D_800A3944Unsigned asm("D_800A3944");
    s32 zero;
    s32 delta;
    s32 threshold;
    s32 delta2;
    s32 sum;
    s32 posflag;
    s32 limit;
    s32 limitSave;
    s32 dneg;
    s32 val;
    s32 idx;
    MenuObj *head;
    u8 *other;
    MenuObj *walk;
    threshold = 5;
    if (arg0 & (~arg1)) {
        D_800A3830Absolute2[0] = 0;
        limitSave = 1;
    } else {
        D_800A3830Absolute[0] = D_800A3830Absolute2[0] + 1;
        if (threshold < D_800A3830Absolute[0]) {
            D_800A37F0Absolute[0] =
                D_800A37F0Absolute2[0] + (D_800A37F0Absolute2[0] / 2);
            if (0x41 <= D_800A37F0Absolute[0]) {
                limitSave = 0x40;
            } else {
                goto noStore;
            }
        } else {
            return;
        }
    }
    D_800A37F0Absolute3[0] = limitSave;
noStore:
    if (arg2 & 0xFF) {
        delta = D_800A37F0Absolute3[0];
    } else {
        dneg = D_800A37F0Absolute3[0];
        delta = -dneg;
    }

    val = gScreenStateNM[0];
    if ((val & 0xFF) == 9) {
        limit = 0x7B;
    } else if ((val & 0xFF) == 0xA) {
        limit = 0x35;
    } else if (((val & 0xFF) == 0xC) || ((val - 0x10) < 2U)) {
        limit = 0x99;
    }
    limit = limit - 0xD;
    if (gScreenStateNM[0] == 9) {
        if (D_800A3A58NM[0] == 0) {
            return;
        }
    }
    if (gScreenStateNM[0] == 0xC) {
        if (D_800B9B84NM[0] == 0) {
            return;
        }
    }
    idx = 0;
    if (gScreenStateNM[0] == 9) {
        idx = D_800A3944Unsigned;
    }
    head = D_800A3858NM[idx];
    if ((head->y) >= 0) {
        if ((*((s16 *)(D_800A3918NM[idx] + 8))) < limit) {
            return;
        }
    }
    other = D_800A3918NB[idx];
    delta2 = delta;
    zero = (s32)0;
    if (delta2 > 0) {
        sum = (head->y) + delta2;
        posflag = zero < ((s32)sum);
        if (posflag != 0) {
            delta2 = -(head->y);
        }
    } else if (delta2 < 0) {
        if (((*((s16 *)(other + 8))) + delta2) < limit) {
            delta2 = limit - (*((s16 *)(other + 8)));
        }
    }
    if (delta2 == 0) {
        return;
    }
    walk = head;
    if (walk != 0) {
        do {
            walk->y += delta2;
            walk = walk->next;
        } while (walk != 0);
    }
}

extern MenuObj *D_800A3900Obj asm("D_800A3900.NON_MATCHING");
extern MenuObj *D_800A360CHead asm("D_800A360C");
extern MenuObj *D_800A3858;
extern MenuObj *D_800A3918;
MenuObj *MenuCreateFlatRect(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
MenuObj *MenuCreateTextObject(s32, s32);

/* One of the 17 rows of the records table at D_800B9BB4. */
typedef struct RecordRow {
    u8 initials[4]; /* 0x00: four characters, blank-filled */
    s16 unk4;
    s16 unk6;
    s32 unk8; /* 0x08: starts at 0x7FFFFFFF, likely a best time */
} RecordRow;

void func_80068CE4(void) {
    extern char *D_8009A498[];
    extern char *D_8009A4B0[];
    extern s32 D_8009B1C4[];
    extern char D_800B9B54[];
    extern s8 D_800B9B6E[];
    extern u8 D_800B9BB4[];
    MenuObj *obj;
    MenuObj *tail;
    /* One packet pointer per section: a single shared pointer takes one
     * register, retail uses a different one in each section. */
    MenuTextPacket *titlePkt;
    MenuTextPacket *subPkt;
    MenuTextPacket *rowPkt;
    MenuTextPacket *hdrPkt;
    MenuTextPacket *cellPkt;
    u8 *record;
    char buf[0x40];
    s32 value;
    s32 flag;
    s32 w;
    s32 label;
    s32 titleW;
    s32 titleX;
    s32 x;
    s32 y;
    s32 i;
    s32 j;
    for (i = 0; i < 2; i++) {
        tail =
            MenuCreateFlatRect(0, 0x27, 0x140, 0xC8, 0, 0x10, 0x10, 0x10, 1, 1);
        if (i == 0) {
            D_800A3900Obj = tail;
        } else {
            D_800A3900Obj->next = tail;
        }
        tail->orderingDepth = 0x3FD;
    }

    tail = MenuCreateTextObject(0, 0x2A);
    D_800A360CHead = tail;
    MenuFontSetS32(2, 3);
    strcpy(buf, D_800B9B54);
    strcat(buf, D_8009A498[0]);
    /* After the call, so the li lands in the call's delay slot. */
    y = 0x39;
    titleW = MenuStringWidth(buf);
    titleX = (0x140 - titleW) / 2;
    tail->x = titleX;
    tail->targetX = titleX;
    tail->orderingDepth = 0x32;
    titlePkt = tail->primitive;
    titlePkt->unk1 = 2;
    titlePkt->unk2 = 3;
    titlePkt->text = (s32)D_800B9B54;
    titlePkt->unk3 = 0;
    titlePkt->orderingDepth = 0x32;
    tail->orderingDepth = 0x32;
    titleW = MenuStringWidth(D_800B9B54);
    obj = MenuCreateTextObject(tail->x + titleW, 0x2A);
    obj->orderingDepth = 0x32;
    value = (s32)D_8009A498[0];
    subPkt = obj->primitive;
    subPkt->unk1 = 2;
    subPkt->unk2 = 3;
    subPkt->text = value;
    subPkt->unk3 = 0;
    subPkt->orderingDepth = 0x32;
    obj->orderingDepth = 0x32;
    tail->next = obj;
    tail = obj;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 2; j++) {
            obj = MenuCreateTextObject((j != 0) ? (0xF0) : (0x40), y);
            obj->orderingDepth = 0x32;
            if (j != 0) {
                switch (i) {
                case 0:
                    value = D_800B9B6E[0];
                    break;

                case 1:
                    value = D_800B9B6E[1];
                    break;

                case 2:
                    value = D_800B9B6E[2];
                    break;

                case 3:
                    value = D_800B9B6E[3];
                    break;

                case 4:
                    value = D_800B9B6E[4];
                    break;
                }

                obj->kind = 5;
            } else {
                value = (s32)D_8009A498[i + 1];
            }

            w = obj->orderingDepth;
            rowPkt = obj->primitive;
            rowPkt->unk1 = 2;
            rowPkt->unk2 = 3;
            rowPkt->text = value;
            rowPkt->unk3 = j;
            rowPkt->orderingDepth = w;
            obj->orderingDepth = w;
            tail->next = obj;
            tail = obj;
        }

        y += 0xF;
    }

    for (i = 0; i < 4; i++) {
        x = D_8009B1C4[i];
        switch (i) {
        case 1:
            x += 4;
            break;

        case 2:
            x += 8;
            break;

        case 3:
            x += 0xA;
            break;
        }

        obj = MenuCreateTextObject(x, 0x89);
        obj->orderingDepth = 0x32;
        label = (s32)D_8009A4B0[i];
        hdrPkt = obj->primitive;
        hdrPkt->unk1 = 2;
        hdrPkt->unk2 = 3;
        hdrPkt->text = label;
        hdrPkt->unk3 = ((u32)(i - 1)) < 2;
        hdrPkt->orderingDepth = 0x32;
        obj->orderingDepth = 0x32;
        tail->next = obj;
        tail = obj;
    }

    y = 0;
    for (i = 0; i < 0x11; i++) {
        record = &D_800B9BB4[i * 0xC];
        for (j = 0; j < 4; j++) {
            obj = MenuCreateTextObject(D_8009B1C4[j], y);
            if ((i == 0) && (j == 0)) {
                D_800A3858 = obj;
            } else {
                tail->next = obj;
            }
            obj->orderingDepth = 0;
            switch (j) {
            case 1:
            case 2:
                obj->kind = 5;
                break;

            case 3:
                obj->kind = 6;
                break;
            }
            flag = 0;
            switch (j) {
            case 0:
                value = D_8009A31C[i];
                break;

            case 1:
                value = ((RecordRow *)record)->unk4;
                flag = 1;
                break;

            case 2:
                value = ((RecordRow *)record)->unk6;
                flag = 1;
                break;

            case 3:
                value = ((RecordRow *)record)->unk8;
                break;
            }

            cellPkt = obj->primitive;
            cellPkt->unk1 = 2;
            cellPkt->unk2 = 3;
            cellPkt->text = value;
            cellPkt->unk3 = flag;
            cellPkt->orderingDepth = 0;
            obj->orderingDepth = 0;
            tail = obj;
        }

        if (i == 0x10) {
            D_800A3918 = tail;
        }
        y += 0xF;
    }

    MenuSetAllObjectOrderingDepths(0x3E8);
}

/* The original toolchain padded this odd-length jump table with one zero
 * word; the C switch regenerates the table, this restores the pad. */
void __maspsx_include_asm_hack_jtblpad_80068CE4() {
    __asm__(".section .rodata # maspsx-keep \n"
            "    .word 0 # maspsx-keep\n"
            "    .section .text # maspsx-keep\n");
}

/* Builds the championship standings table: rank, driver name, points,
 * gap to the leader, and a highlight behind the player's row. */
static __inline__ void MenuSetText(MenuObj *obj, s32 text, s32 flag, s32 two,
                                   s32 three) {
    MenuTextPacket *pkt;
    s32 h;
    pkt = obj->primitive;
    h = obj->orderingDepth;
    pkt->unk1 = two;
    pkt->unk2 = three;
    pkt->text = text;
    pkt->unk3 = flag;
    pkt->orderingDepth = h;
    obj->orderingDepth = h;
}

void CardMenuCreateStandingsTable(void) {
    extern s16 D_800B9B84[];
    extern char D_800B9B54[];
    extern char *D_8009A490[];
    extern char *D_8009A494[];
    extern s32 D_8009B1D4[];
    extern s8 D_800A374C[];
    extern MenuObj *D_800A3900;
    extern MenuObj *sMenuHead[2] asm("D_800A360C");
    extern MenuObj *sMenuList[2] asm("D_800A3858");
    extern MenuObj *D_800A3918;
    MenuObj *obj;
    MenuObj *tail;
    MenuObj *mine;
    MenuTextPacket *pkt;
    struct {
        char buf[0x3F];
        u8 previous;
        u8 order[24];
    } rows;
    char pad[0x30];
    s32 value;
    s32 flag;
    s32 h;
    s32 m;
    s32 best;
    s16 bestScore;
    s16 cur;
    u8 tmp;
    s32 y;
    s32 i;
    s32 j;
    s32 one;
    s32 two;
    s32 three;
    /* Keep these address loads inside the row loop. */
    register s16 *scores asm("s6");
    u8 *previousBase;
    u8 *previous;
    s32 rowScore;
    for (i = 0; i < 2; i++) {
        tail =
            MenuCreateFlatRect(0, 0x27, 0x140, 0xC8, 0, 0x10, 0x10, 0x10, 1, 1);
        if (i == 0) {
            D_800A3900 = tail;
        } else {
            D_800A3900->next = tail;
        }
        tail->orderingDepth = 0x3FD;
    }

    one = 1;
    tail = MenuCreateTextObject(0, 0x2A);
    sMenuHead[0] = tail;
    MenuFontSetS32(2, 3);
    h = (0x140 - MenuStringWidth(D_8009A490[0])) / 2;
    tail->x = h;
    tail->targetX = h;
    tail->orderingDepth = 0x32;
    MenuSetText(tail, (s32)D_8009A490[0], 0, 2, 3);
    if (D_800B9B84[0] == 0) {
        obj = MenuCreateTextObject(
            MenuTextCenterOffset(0x140, (s32)D_8009A494[0]), 0x66);
        obj->drawOffsetX = 0;
        obj->orderingDepth = 0x32;
        MenuSetText(obj, (s32)D_8009A494[0], 0, 2, 3);
        sMenuList[0] = obj;
    } else {
        for (i = 23; i >= 0; i--) {
            rows.order[i] = i;
        }

        for (i = 0; i < 23; i++) {
            cur = D_800B9B84[rows.order[i]];
            bestScore = 0;
            for (j = i + 1; j < 24; j++) {
                if (bestScore < D_800B9B84[rows.order[j]]) {
                    bestScore = D_800B9B84[rows.order[j]];
                    best = j;
                }
            }

            if (bestScore > cur) {
                tmp = rows.order[i];
                rows.order[i] = rows.order[best];
                rows.order[best] = tmp;
            }
        }

        two = 2;
        three = 3;
        y = 0;
        for (i = 0; i < 24; i++) {
            j = 0;
            previousBase = (u8 *)&rows + 0x3F;
            previous = previousBase + i;
            scores = D_800B9B84;
            for (; j < 4; j++) {
                /* Keep the list tail live across the object call. */
                asm("" : : "r"(tail));
                obj = MenuCreateTextObject(D_8009B1D4[j], y);
                if ((i == 0) && (j == 0)) {
                    sMenuList[0] = obj;
                } else {
                    tail->next = obj;
                }
                obj->orderingDepth = 0;
                flag = one;
                if (j != flag) {
                    obj->kind = 5;
                }
                flag = 0;
                if (j == one)
                    goto nameColumn;
                if (j < 2) {
                    if (j == 0)
                        goto rankColumn;
                    goto setColumnText;
                }
                if (j == two)
                    goto pointsColumn;
                if (j == three)
                    goto gapColumn;
                goto setColumnText;
            rankColumn:
                value = 1;
                if (i != 0) {
                    value = i + 1;
                    if (scores[rows.order[i]] == scores[*previous]) {
                        value = 0;
                    }
                }
                flag = 1;
                goto setColumnText;
            nameColumn:
                value = (s32)gDriverNames[rows.order[i]];
                if (strcmp((char *)value, D_800B9B54) == 0) {
                    D_800A374C[0] = i;
                    mine = obj;
                    if ((i != 0) &&
                        (scores[rows.order[i]] == scores[*previous])) {
                        rowScore = scores[rows.order[i]];
                        for (m = i - 1; m >= 0; m--) {
                            if (rowScore != scores[rows.order[m]]) {
                                break;
                            }
                        }

                        if (m < 0) {
                            D_800A374C[0] = 0;
                        } else {
                            D_800A374C[0] = m + 1;
                        }
                    }
                }
                goto setColumnText;
            pointsColumn:
                value = scores[rows.order[i]];
                flag = 1;
                goto setColumnText;
            gapColumn:
                flag = 1;
                if (i == 0) {
                    value = 0;
                } else {
                    value = scores[rows.order[i]] - scores[rows.order[0]];
                }
            setColumnText:

                tail = obj;
                MenuSetText(obj, value, flag, two, three);
            }

            if (i == 23) {
                D_800A3918 = obj;
            }
            y += 0xF;
        }

        obj =
            MenuCreateFlatRect(0, mine->y - 2, 0x140, 0xF, 0, 0, 0, 0xFF, 1, 1);
        obj->orderingDepth = mine->orderingDepth + 2;
        tail->next = obj;
    }
    MenuSetAllObjectOrderingDepths(0x3E8);
}

typedef struct UnkBlockOffsets {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} UnkBlockOffsets;
extern UnkBlockOffsets *D_800A3A30;
extern void *D_800A336C;
extern s32 D_800A3370, D_800A3374, D_800A3378Small;

void CardMenuLoadResources(void) {
    s32 block;

    block = (s32)FileLoadOffsetTable(0xB, (void **)gPadType + 3, 0);
    D_800A336C = (void *)block;
    if (block != 0) {
        D_800A3370 = block + D_800A3A30->unk0;
        D_800A3374 = block + D_800A3A30->unk4;
        D_800A3378Small = block + D_800A3A30->unk8;
        func_800641EC();
    }
}

void CardMenuFreeResources(void) {
    if (D_800A336C != 0)
        HeapFree(D_800A336C);
    D_800A336C = 0;
    D_800A3370 = 0;
    D_800A3374 = 0;
    D_800A3378Small = 0;
}

extern s8 *D_8009AD58[];

void func_800697EC(u8 mode) {
    MenuObj *obj;
    MenuObj *prev;
    /* One packet pointer per section, so each is a block-local pseudo. */
    MenuTextPacket *titlePkt;
    MenuTextPacket *rowPkt;
    s8 *buf;
    s8 *p;
    /* u16, so `i + 1` stays a copy (no biv) and the test below is a shift. */
    u16 i;
    s32 x;
    s32 w;
    s32 title;
    s32 width;
    /* Packet bytes held in locals: retail sets the first at the loop top and
     * hoists the second, and that pins the schedule. */
    s32 pktType;
    s32 pktMode;
    s32 j;
    s8 c;
    /* Unused, but retail's frame has 0x40 bytes of locals. */
    char unused[0x40];

    j = 0;
    do {
        prev =
            MenuCreateFlatRect(0, 0x27, 0x140, 0xC8, 0, 0x10, 0x10, 0x10, 1, 1);
        if (j == 0) {
            D_800A3900Obj = prev;
        } else {
            D_800A3900Obj->next = prev;
        }
        prev->orderingDepth = 0x3FD;
        j += 1;
    } while (j < 2);

    prev = MenuCreateTextObject(0, 0x2A);
    D_800A360CHead = prev;
    MenuFontSetS32(2, 3);
    w = MenuTextCenterOffset(0x140, (s32)D_8009AD58[mode]);
    prev->x = w;
    prev->targetX = w;
    prev->orderingDepth = 0x32;
    title = (s32)D_8009AD58[mode];
    titlePkt = prev->primitive;
    titlePkt->unk1 = 2;
    titlePkt->unk2 = 3;
    titlePkt->text = title;
    titlePkt->unk3 = 0;
    titlePkt->orderingDepth = 0x32;
    prev->orderingDepth = 0x32;
    if (mode == 0) {
        buf = (s8 *)D_800A3370;
    } else {
        buf = (s8 *)D_800A3374;
    }
    MenuFontSetS32(2, 4);
    width = MenuFontLineHeight();
    i = 0;
    x = 0;
    while (1) {
        pktType = 2;
        p = buf + (s16)i;
        c = *p;
        if (c == '%') {
            D_800A3918 = prev;
            break;
        }
        if (c == '\n') {
            x += width / 4;
        } else {
            obj = MenuCreateTextObject(0, x);
            if (*p == '*') {
                p = buf + ((s16)i + 1);
                obj->red = 0xF0;
                obj->green = 0x40;
                obj->blue = 0x40;
            }
            pktMode = 4;
            w = MenuTextCenterOffset(0x140, (s32)p);
            rowPkt = obj->primitive;
            obj->drawOffsetX = w;
            obj->x = w;
            obj->targetX = w;
            obj->orderingDepth = 0;
            rowPkt->unk1 = pktType;
            rowPkt->unk2 = pktMode;
            rowPkt->text = (s32)p;
            rowPkt->unk3 = 0;
            rowPkt->orderingDepth = 0;
            obj->orderingDepth = 0;
            if ((i << 16) == 0) {
                D_800A3858 = obj;
            } else {
                prev->next = obj;
            }
            prev = obj;
        }
        x += width;
        if (buf[(s16)i] != 0) {
            do {
                i++;
            } while (buf[(s16)i] != 0);
        }
        i++;
    }
    MenuSetAllObjectOrderingDepths(0x3E8);
}

inline u8 func_80069A90(s32 itemCode) {
    switch (itemCode & 0xFF) {
    case 0:
    case 1:
    case 3:
    case 6:
    case 15:
        return 0;
    case 2:
    case 4:
    case 5:
    case 7:
    case 8:
    case 11:
        return 1;
    case 10:
        return 3;
    case 12:
    case 16:
    case 17:
        return 4;
    case 34:
    case 36:
    case 40:
        return 5;
    case 35:
        return 6;
    case 9:
    case 14:
    case 33:
        return 7;
    default:
        return 0xFF;
    }
}

/* The original toolchain padded this odd-length jump table with one zero
 * word; the C switch regenerates the table, this restores the pad. */
void __maspsx_include_asm_hack_jtblpad_80069A90() {
    __asm__(".section .rodata # maspsx-keep \n"
            "    .word 0 # maspsx-keep\n"
            "    .section .text # maspsx-keep\n");
}

void MenuUpdateItemRow(s32 itemCode) {
    extern void *D_800A3914View[] asm("D_800A3914");
    extern s8 gPadLayout[];
    extern s32 D_8009A2D4[];
    extern s32 D_8009A2F4[];
    u8 group8;
    s32 group;
    s32 index;
    s32 value;
    MenuObj *obj;
    u8 *child;
    switch (itemCode & 0xFF) {
    case 0:

    case 1:

    case 3:

    case 6:

    case 15:
        group = 0;
        break;

    case 2:

    case 4:
        do {
        } while (0);

    case 5:

    case 7:

    case 8:

    case 11:
        group = 1;
        break;

    case 10:
        group = 3;
        break;

    case 12:

    case 16:

    case 17:
        group = 4;
        break;

    case 34:

    case 36:

    case 40:
        group = 5;
        break;

    case 35:
        group = 6;
        break;

    case 9:

    case 14:

    case 33:
        group = 7;
        break;

    default:
        group = 0xFF;
        break;
    }

    group = group & 0xff;
    group8 = group;
    index = group8;
    if (group == 0xFF) {
        MenuObj *retObj;
        retObj = (MenuObj *)D_800A3914View[0];
        if (retObj != 0) {
            retObj->orderingDepth = -0x32;
            return;
        }
    }
    MenuFontSetS32(2, 2);
    if (gPadType[0] == 2) {
        value = MenuTextCenterOffset(0x140, D_8009A2F4[index]);
    } else {
        value = MenuTextCenterOffset(0x140, D_8009A2D4[index]);
    }
    obj = (MenuObj *)D_800A3914View[0];
    obj->x = value;
    obj->orderingDepth = 0x32;
    child = obj->primitive;
    if ((gPadType[0] == 2) && (gPadLayout[0] != 6)) {
        *((s32 *)(child + 8)) = D_8009A2F4[index];
    } else {
        *((s32 *)(child + 8)) = D_8009A2D4[index];
    }
    asm(".rdata");
    asm(".long 0");
    asm(".text");
}

/* func_80069A90 is inline in the original: this function expands it (its
 * switch table is jtbl_8008FBBC). `index` is a u8 copy of `group`; the first
 * lookup reads `group`, the others read `index`. Each arm of the last test
 * holds its own copy of the row setup, so the locals stay block-local. */
void MenuCreateItemRow(s32 itemCode) {
    extern void *D_800A3914View[] asm("D_800A3914");
    extern u8 *D_800A3910f[] asm("D_800A3910");
    extern u8 *D_800A3918n[] asm("D_800A3918");
    extern s8 gPadLayout[];
    extern s32 D_8009A2D4[];
    extern s32 D_8009A2F4[];
    s32 group;
    u8 index;
    s32 text;
    u8 *obj;
    group = func_80069A90(itemCode);
    index = group;
    if (group == 0xFF) {
        D_800A3914View[0] = 0;
        return;
    }
    MenuFontSetS32(2, 2);
    if ((gPadType[0] == 2) && (gPadLayout[0] != 6)) {
        text = D_8009A2F4[group];
    } else {
        text = D_8009A2D4[index];
    }
    obj = (u8 *)MenuCreateTextObject(MenuTextCenterOffset(0x140, text), 0xDC);
    D_800A3914View[0] = obj;
    if (((itemCode & 0xFF) != 0xC) && ((u32)((itemCode - 9) & 0xFF) >= 2U) &&
        ((u32)((itemCode - 0x10) & 0xFF) >= 2U)) {
        *((s16 *)(obj + 0xE)) = 2;
        *((u16 *)(obj + 6)) = *((u16 *)(obj + 6)) - 0x140;
    }
    {
        u8 *fields = D_800A3910f[1];
        u8 *next;
        fields[2] = 0xFF;
        next = D_800A3918n[-1];
        *((s16 *)(fields + 0x1A)) = 0x32;
        next[3] = 0x80;
    }
    ((u8 *)D_800A3914View[0])[4] = 0x40;
    if ((gPadType[0] == 2) && (gPadLayout[0] != 6)) {
        MenuObj *rowA;
        u8 *pktA;
        s32 textA;
        s32 timerA;
        rowA = (MenuObj *)D_800A3914View[0];
        timerA = rowA->orderingDepth;
        textA = D_8009A2F4[index];
        pktA = rowA->primitive;
        pktA[1] = 2;
        pktA[2] = 2;
        *((s32 *)(pktA + 8)) = textA;
        pktA[3] = 0;
        *((s32 *)(pktA + 4)) = timerA;
        rowA->orderingDepth = timerA;
    } else {
        MenuObj *rowB;
        u8 *pktB;
        s32 textB;
        s32 timerB;
        rowB = (MenuObj *)D_800A3914View[0];
        timerB = rowB->orderingDepth;
        textB = D_8009A2D4[index];
        pktB = rowB->primitive;
        pktB[1] = 2;
        pktB[2] = 2;
        *((s32 *)(pktB + 8)) = textB;
        pktB[3] = 0;
        *((s32 *)(pktB + 4)) = timerB;
        rowB->orderingDepth = timerB;
    }
}

extern char *D_800A35F4;
extern char *D_800A3604;
extern char *D_800A366C;
extern char *D_800A3978;
extern char *D_800A3A0C;

void CardMenuSetSaveDataPointers(void) {
    D_800A366C = (char *)0x80010000;
    D_800A3978 = (char *)0x8001000C;
    D_800A3A0C = (char *)0x80010AEC;
    D_800A35F4 = (char *)0x8001000C;
    D_800A3604 = (char *)0x80010000;
}

extern u8 D_800A3938;
extern u8 gCardMenuMessage;
extern u8 gCardSlot;

s32 func_80069EB8(void) {
    u8 status;
    u8 formatResult;
    u8 result;

    status = CardCheckStatus(gCardSlot, 0);
    D_800A3938 = status;
    if (status == 1) {
        result = 1;
    } else if (status == 2) {
        result = 2;
    } else {
        formatResult = CardFormat(gCardSlot);
        if (formatResult != 0) {
            gCardMenuMessage = 0;
            return 1;
        }
        result = 4;
    }
    gCardMenuMessage = result;
    return 0;
}

s32 CardResolveSlot(void) {
    u8 slot;
    u8 status;

    gCardMenuMessage = 0;
    if (gCardSlot == 0xFF) {
        slot = 0;
    } else {
        slot = gCardSlot;
    }
    status = CardCheckStatus(slot, 0);
    D_800A3938 = status;
    if (status == 1) {
        gCardMenuMessage = 1;
        return 0;
    }
    if (status == 2) {
        if (gCardSlot == 0xFF) {
            status = CardCheckStatus(1, 0);
            D_800A3938 = status;
        }
        switch (D_800A3938) {
        case 1:
            gCardMenuMessage = 1;
            return 0;
        case 2:
            gCardMenuMessage = 2;
            return 0;
        case 0:
        case 3:
            gCardSlot = 1;
            break;
        }
    } else {
        gCardSlot = slot;
    }
    status = func_80059F0C(gCardSlot);
    D_800A3938 = status;
    if (status == 2) {
        gCardMenuMessage = 2;
        return 0;
    }
    if (status == 1) {
        gCardMenuMessage = 3;
        return 0;
    }
    if (status == 3) {
        gCardMenuMessage = 0xD;
        return 0;
    }
    return 1;
}

s32 CardProbeSlots(void) {
    s32 count;
    s32 i;
    s8 result;
    s32 status;

    count = 0;
    i = 0;
    do {
        result = CardCheckStatus((u8)i, 0);
        D_800A3938 = result;
        status = result & 0xFF;
        if (status == 1) {
            gCardMenuMessage = status;
            return 0;
        }
        if (status != 2) {
            count++;
            gCardSlot = i;
        }
        i++;
    } while ((u8)i < 2);
    if ((count & 0xFF) == 2) {
        gCardSlot = 0;
    }
    gCardMenuMessage = 0;
    return count & 0xFF;
}

extern char gCardFileName[];
u8 CardGetOtherFileBlocks(void) {
    return CardCountOtherFileBlocks(gCardSlot, gCardFileName);
}

extern char D_800B0A2C[];
extern u8 D_800A3968;
extern s32 gMemoryCardPort0PathPrefix[2];
extern s32 gMemoryCardPort1PathPrefix[2];
extern void *memcpy(void *, const void *, size_t);
s32 CardLoadNameList(u8 requestedSlot) {
    u8 slot;
    u8 status;
    u32 count;
    u8 sectors;
    s32 i;
    char *src;
    char path[0x40];
    struct DIRENTRY entry;

    slot = requestedSlot == 0xFF ? 0 : requestedSlot;
    D_800A3968 = 0;
    gCardMenuMessage = 0;
    status = CardCheckStatus(slot, 0);
    D_800A3938 = status;
    if (status == 1) {
        gCardMenuMessage = 1;
        return 0;
    }
    if (status == 2) {
        if (requestedSlot == 0xFF) {
            status = CardCheckStatus(1, 0);
            D_800A3938 = status;
        }
        switch (D_800A3938) {
        case 1:
            gCardMenuMessage = 1;
            return 0;
        case 2:
            gCardMenuMessage = 2;
            return 1;
        case 0:
        case 3:
            gCardSlot = 1;
            break;
        }
    } else {
        gCardSlot = slot;
    }
    status = func_80059F0C(gCardSlot);
    D_800A3938 = status;
    if (gCardSlot == 0) {
        memcpy(path, gMemoryCardPort0PathPrefix, 6);
    } else {
        memcpy(path, gMemoryCardPort1PathPrefix, 6);
    }
    strcat(path, gCardFileName);
    if ((CardFindFirstFile(path, &entry) & 0xFF) == 0) {
        return 1;
    }
    if ((CardReadSectors(&entry, 0x1A, 1, gCardSlot, (s32)D_800A3A0C) & 0xFF) ==
        0) {
        gCardMenuMessage = 7;
        return 0;
    }
    D_800A3968 = *(s32 *)D_800A3A0C;
    count = D_800A3968;
    if (count >= 0x10) {
        D_800A3968 = 0;
        gCardMenuMessage = 0xB;
        if ((CardDeleteFile(path) & 0xFF) == 0) {
            gCardMenuMessage = 0xC;
        }
        return 0;
    }
    sectors = (count * 0x13C + 0x83) >> 7;
    if ((CardReadSectors(&entry, 0x1A, sectors, gCardSlot, (s32)D_800A3A0C) &
         0xFF) != 0) {
        src = D_800A3A0C + 4;
        for (i = 0; i < D_800A3968; i++) {
            strcpy(D_800B0A2C + i * 0x10, src + i * 0x13C);
        }
    } else {
        gCardMenuMessage = 7;
        return 0;
    }
    return 1;
}

extern u8 D_800A3A58;
extern char D_8009B1E4[];

s32 CardWriteSaveSlot(char *record, u8 overwrite, u8 index) {
    typedef struct {
        s32 words[0x3A];
    } SaveEntry;
    typedef struct {
        s32 words[0x4F];
    } SaveSlot;
    char path[0x40];
    struct DIRENTRY entry;
    SaveEntry blank;
    u8 sectors;
    s32 fd;
    s32 i;
    s32 j;
    u8 *p;
    SaveSlot *slots;

    gCardMenuMessage = 0;
    if ((CardCountOtherFileBlocks(gCardSlot, gCardFileName) & 0xFF) == 0xF) {
        gCardMenuMessage = 0x1E;
        return 0;
    }
    if (gCardSlot == 0) {
        memcpy(path, gMemoryCardPort0PathPrefix, 6);
    } else {
        memcpy(path, gMemoryCardPort1PathPrefix, 6);
    }
    strcat(path, gCardFileName);
    if ((CardFindFirstFile(path, &entry) & 0xFF) == 0) {
        fd = CardOpenFile(path, 0x200);
        if (fd == -1) {
            gCardMenuMessage = 5;
            return 0;
        }
        CardCloseFile(fd);
        if ((CardFindFirstFile(path, &entry) & 0xFF) == 0) {
            gCardMenuMessage = 0xA;
            return 0;
        }
        if ((CardWriteSectors(&entry, 0, 4, gCardSlot, (s32)D_8009B1E4) &
             0xFF) == 0) {
            gCardMenuMessage = 8;
            return 0;
        }
        if (D_800A3A58 == 0) {
            ((s8 *)&blank)[0] = -1;
            for (j = 0; j < 17; j++) {
                p = (u8 *)&blank + j * 0xC;
                p[0x1D] = 0;
                p[0x1E] = 0;
                p[0x1F] = 0;
                p[0x1C] = 0;
                *(s32 *)&p[0x20] = 0x7FFFFFFF;
            }
        }
        if (D_800A3978 == 0) {
            gCardMenuMessage = 0xE;
            return 0;
        }
        if (D_800A3A58 == 0) {
            D_800A366C[0] = 0;
            D_800A366C[1] = 0;
            D_800A366C[2] = 0;
            D_800A366C[3] = 0;
            for (i = 0; i < 6; i++) {
                (D_800A366C + i)[4] = 0;
            }
            D_800A366C[0xA] = 0;
            D_800A366C[0xB] = 0;
            for (i = 0; i < 12; i++) {
                *(SaveEntry *)(D_800A3978 + i * 0xE8) = blank;
                if (i == 0) {
                    ((u8 *)&blank)[0] = 0;
                }
            }
        }
        if ((CardWriteSectors(&entry, 4, 0x16, gCardSlot, (s32)D_800A366C) &
             0xFF) == 0) {
            gCardMenuMessage = 8;
            return 0;
        }
    }
    slots = (SaveSlot *)(D_800A3A0C + 4);
    if (overwrite != 0) {
        slots[index] = *(SaveSlot *)record;
    } else {
        *(s32 *)D_800A3A0C = ++D_800A3968;
        slots[D_800A3968 - 1] = *(SaveSlot *)record;
    }
    sectors = (D_800A3968 * 0x13C + 0x83) >> 7;
    if ((CardWriteSectors(&entry, 0x1A, sectors, gCardSlot, (s32)D_800A3A0C) &
         0xFF) == 0) {
        gCardMenuMessage = 8;
        return 0;
    }
    return 1;
}

extern s32 D_800A35B0;
extern void func_8006B464(void);
s32 CardLoadSaveTable(u8 updateDriverRecords) {
    u8 slot;
    u8 status;
    u16 c;
    s32 i;
    u8 *row;
    char path[0x40];
    struct DIRENTRY entry;

    D_800A3A58 = 0;
    gCardMenuMessage = 0;
    if (gCardSlot == 0xFF) {
        slot = 0;
    } else {
        slot = gCardSlot;
    }
    status = CardCheckStatus(slot, 0);
    D_800A3938 = status;
    if (status == 1) {
        gCardMenuMessage = 1;
        return 0;
    }
    if (status == 2) {
        if (gCardSlot == 0xFF) {
            status = CardCheckStatus(1, 0);
            D_800A3938 = status;
        }
        switch (D_800A3938) {
        case 1:
            gCardMenuMessage = 1;
            return 0;
        case 2:
            gCardMenuMessage = 2;
            return 1;
        case 0:
        case 3:
            gCardSlot = 1;
            break;
        }
    } else {
        gCardSlot = slot;
    }
    status = func_80059F0C(gCardSlot);
    D_800A3938 = status;
    if (gCardSlot == 0) {
        memcpy(path, gMemoryCardPort0PathPrefix, 6);
    } else {
        memcpy(path, gMemoryCardPort1PathPrefix, 6);
    }
    strcat(path, gCardFileName);
    if ((CardFindFirstFile(path, &entry) & 0xFF) == 0) {
        return 1;
    }
    if ((CardReadSectors(&entry, 4, 1, gCardSlot, (s32)D_800A366C) & 0xFF) ==
        0) {
        return 1;
    }
    c = *(u8 *)D_800A3978;
    if ((u8)c == 0xFF) {
        return 1;
    }
    if (c != 0 && (c < 0x20 || c > 0x5A)) {
        gCardMenuMessage = 0xB;
        if ((CardDeleteFile(path) & 0xFF) == 0) {
            gCardMenuMessage = 0xC;
        }
        return 0;
    }
    D_800A35B0 = (s32)D_800A366C;
    if ((CardReadSectors(&entry, 5, 0x15, gCardSlot, (s32)D_800A366C + 0x80) &
         0xFF) != 0) {
        D_800A3A58 = 0;
        D_800A3604 = (char *)D_800A35B0;
        D_800A35F4 = (char *)D_800A35B0 + 0xC;
        row = (u8 *)D_800A35F4;
        for (i = 0; i < 12; i++) {
            if ((u8)(row[0] + 1) >= 2) {
                D_800A3A58++;
            }
            row += 0xE8;
        }
        if (updateDriverRecords != 0) {
            func_8006B464();
        }
    } else {
        gCardMenuMessage = 7;
        return 0;
    }
    return 1;
}

s32 func_8006AA70(void) {
    extern s32 gMemoryCardPort0PathPrefix[2];
    extern s32 gMemoryCardPort1PathPrefix[2];
    extern char D_8009B1E4[];
    extern void *memcpy(void *, const void *, size_t);
    char path[0x40];
    struct DIRENTRY entry;
    u8 created;
    s32 fd;
    s32 result;
    u8 *clear;

    gCardMenuMessage = 0;
    if (gCardSlot == 0) {
        memcpy(path, gMemoryCardPort0PathPrefix, 6);
    } else {
        memcpy(path, gMemoryCardPort1PathPrefix, 6);
    }
    strcat(path, gCardFileName);
    result = CardFindFirstFile(path, &entry);
    created = 0;
    if ((result & 0xFF) == 0) {
        fd = CardOpenFile(path, 0x200);
        if (fd == -1) {
            gCardMenuMessage = 5;
            return 0;
        }
        CardCloseFile(fd);
        created = 1;
        if ((CardFindFirstFile(path, &entry) & 0xFF) == 0) {
            gCardMenuMessage = 0xA;
            return 0;
        }
    }
    if (created != 0) {
        if ((CardWriteSectors(&entry, 0, 4, gCardSlot, (s32)D_8009B1E4) &
             0xFF) == 0) {
            gCardMenuMessage = 8;
            return 0;
        }
    }
    if ((CardWriteSectors(&entry, 4, 0x16, gCardSlot, (s32)D_800A3604) &
         0xFF) == 0) {
        gCardMenuMessage = 8;
        return 0;
    }
    if (created != 0) {
        *(s32 *)D_800A3A0C = 0;
        clear = (u8 *)D_800A3A0C;
        clear[4] = 0;
        clear[0x14] = 0;
        clear[0x34] = 0;
        if ((CardWriteSectors(&entry, 0x1A, 3, gCardSlot, (s32)D_800A3A0C) &
             0xFF) == 0) {
            gCardMenuMessage = 8;
            return 0;
        }
    }
    return 1;
}

void func_8006ABF8(void) {
    char *p;
    char *q;
    char *row;
    s32 i;
    s32 j;
    s32 k;

    i = 0;
    do {
        row = D_800A35F4 + i * 0xE8;
        row[0] = 0;
        row[0x19] = 0;
        j = 0;
        do {
            /* Preserve GCC 2.7.2 pointer-induction lowering. */
            p = row - (-j);
            k = 3;
            q = p + 3;
            p[0x1C] = 0;
            p[0x1D] = 0;
            p[0x1E] = 0;
            p[0x1F] = 0;
            *(s32 *)&p[0x20] = -1;
            do {
                q[0x24] = 0x20;
                k--;
                q--;
            } while (k >= 0);
            j += 0xC;
        } while (j < 0xCC);
        i++;
    } while (i < 0xC);
    D_800A3A58 = 0;
}

void CardMenuSetDriverIndexFromName(s32 playerIndex) {
    char *label;
    s32 mask;
    s32 index;

    index = 0;
    mask = playerIndex & 0xFF;
    do {
        label = gDriverNames[index];
        if (strcmp(D_800BB9B4 + mask * 0x18, label) == 0) {
            gPlayerDriver[mask] = index;
            return;
        }
        index += 1;
    } while (index < 0x18);
}

u8 DriverFindIndexById(u8 value) {
    s32 i;
    for (i = 0; i < 0x18; i++) {
        if (value == D_8009AD40[i])
            return i;
    }
}

/* Memory card menu state. */

s32 CardFindSavedDriverRecord(char *name) {
    s32 i;

    if (D_800A3A58 == 0) {
        return 0xFF;
    }
    i = 0;
    while (i < D_800A3A58) {
        if (strcmp(name, D_800A35F4 + i * 0xE8) == 0) {
            return i & 0xFF;
        }
        i++;
    }
    return 0xFF;
}

extern u8 D_800A3068w17[] asm("D_800A3068.NON_MATCHING");
extern u8 D_800A3069w17[] asm("D_800A3069.NON_MATCHING");
extern u8 gPadTypew17[] asm("gPadType.NON_MATCHING");
extern u8 gPadLayoutw17[] asm("gPadLayout.NON_MATCHING");
extern u8 D_800BBA24w17[] asm("D_800BBA24.NON_MATCHING");

/* A 0x0C entry in a memory-card slot's record table at D_800A35F4. */
typedef struct {
    u8 count[4]; /* 0x00 */
    u32 best;    /* 0x04 */
    u32 unk8;
} CardRecord;

void func_8006ADC4(u8 arg0, char *arg1, u8 arg2, u8 arg3, s32 arg4, u8 arg5,
                   u8 arg6, u8 arg7) {
    typedef struct {
        s32 words[0x3A];
    } SaveEntry;

    s32 count;
    s32 iv;
    s32 k;
    s32 i;
    s32 one;
    u32 d3;
    u32 lt5;
    u32 lt10;
    u32 d7;
    u32 lt11;
    u32 table;
    u32 d0;
    u32 d0x16;
    s32 off;
    u8 *rec;
    u8 *src;
    u32 sum;

    if (D_800A3A58 != 0) {
        count = D_800A3A58 - 1;
        if (D_800A3A58 == 0xC) {
            count = 10;
        } else {
            D_800A3A58 = D_800A3A58 + 1;
        }
        i = count;
        if (i >= 0) {
            k = i * 29;
            iv = k << 3;
            do {
                *(SaveEntry *)(iv + (u32)D_800A35F4 + 0xE8) =
                    *(SaveEntry *)(iv + (u32)D_800A35F4);
                i--;
                iv -= 0xE8;
            } while (i >= 0);
        }
    } else {
        D_800A3A58 = D_800A3A58 + 1;
    }

    strcpy(D_800A35F4, arg1);

    i = 0;
    one = 1;
    d3 = arg3;
    lt5 = d3 < 5;
    lt10 = d3 < 10;
    d7 = arg7;
    lt11 = d7 < 11;
    table = (u32)D_800BBA24w17;
    D_800A35F4[0x19] = D_800A3068w17[arg0 * 2] | (D_800A3069w17[arg0 * 2] << 1);
    d0 = arg0;
    d0x16 = d0 << 4;
    off = 0x1C;

outer:
    do {
        rec = D_800A35F4 + off;
        if (i == arg2) {
            if (arg5 == 0) {
                if ((d3 = d3) == 0 && arg6 == 0) {
                    ((CardRecord *)rec)->count[1] = one;
                } else {
                    ((CardRecord *)rec)->count[1] = 0;
                }
                if (d7 == 2) {
                    ((CardRecord *)rec)->count[2] = 0;
                    ((CardRecord *)rec)->count[3] = 0;
                } else {
                    if (lt5 != 0) {
                        ((CardRecord *)rec)->count[2] = one;
                    } else {
                        ((CardRecord *)rec)->count[2] = 0;
                    }
                    if ((lt10 = lt10) != 0 && lt11 == 0) {
                        ((CardRecord *)rec)->count[3] = one;
                    } else {
                        ((CardRecord *)rec)->count[3] = 0;
                    }
                }
                ((CardRecord *)rec)->count[0] = one;
            } else {
                ((CardRecord *)rec)->count[0] = 0;
                ((CardRecord *)rec)->count[1] = 0;
                ((CardRecord *)rec)->count[2] = 0;
                ((CardRecord *)rec)->count[3] = 0;
            }
            *(s32 *)&((CardRecord *)rec)->best = arg4;
        } else {
            ((CardRecord *)rec)->count[0] = 0;
            ((CardRecord *)rec)->count[1] = 0;
            ((CardRecord *)rec)->count[2] = 0;
            ((CardRecord *)rec)->count[3] = 0;
            *(s32 *)&((CardRecord *)rec)->best = 0x7FFFFFFF;
        }
        sum = (d0x16 + d0) * 4 + table;
        src = (u8 *)(i * 4 + sum);
        for (count = 0; count < 4; count++) {
            *(rec + count + 8) = src[count];
        }
        i++;
        off += 0xC;
    } while (0);
    if (i < 17) {
        goto outer;
    }

    D_800A35F4[0x1A] = gPadTypew17[arg0];
    D_800A35F4[0x1B] = gPadLayoutw17[arg0];
}

typedef struct {
    s32 words[0x3A];
} CardMoveRecord;

void CardMenuMoveRecordToFront(s32 recordIndex) {
    CardMoveRecord buf;
    s32 n;

    if ((recordIndex & 0xFF) == 0) {
        return;
    }
    buf = ((CardMoveRecord *)D_800A35F4)[recordIndex & 0xFF];
    n = (recordIndex & 0xFF) - 1;
    while (n >= 0) {
        ((CardMoveRecord *)D_800A35F4)[n + 1] =
            ((CardMoveRecord *)D_800A35F4)[n];
        n--;
    }
    *(CardMoveRecord *)D_800A35F4 = buf;
}

void func_8006B1CC(u8 arg0, s32 arg1, u8 arg2, u8 arg3, u32 arg4, u8 arg5,
                   u8 arg6, u8 arg7) {
    u8 j;
    u8 *tbl;
    u8 i;
    s32 slot;
    u8 driver;
    u32 seven;
    s32 m;
    u8 *rec;
    u8 *src;
    s32 row;
    s32 p;
    s32 sum;
    s32 slotM;

    slot = arg1;
    rec = (u8 *)D_800A35F4 + (slot & 0xFF) * 0xE8 + (arg2 * 0xC + 0x1C);
    driver = arg0;
    seven = arg7;
    if (arg5 == 0) {
        ((CardRecord *)rec)->count[0] = ((CardRecord *)rec)->count[0] + 1;
        if (arg3 == 0) {
            if (arg6 == 0) {
                ((CardRecord *)rec)->count[1] =
                    ((CardRecord *)rec)->count[1] + 1;
            }
        }
        if (seven >= 6) {
            if (arg3 < 5) {
                ((CardRecord *)rec)->count[2] =
                    ((CardRecord *)rec)->count[2] + 1;
            }
        }
        if (seven >= 0xB) {
            if (arg3 < 0xA) {
                ((CardRecord *)rec)->count[3] =
                    ((CardRecord *)rec)->count[3] + 1;
            }
        }
    }
    if (arg4 < ((CardRecord *)rec)->best) {
        ((CardRecord *)rec)->best = arg4;
    }
    i = 0;
    row = (slot & 0xFF) * 0xE8;
    tbl = D_800BBA24w17;
    p = driver * 0x11;
outer:
    do {
        j = 0;
        rec = (u8 *)D_800A35F4;
        rec += row;
        m = i;
        rec += m * 0xC + 0x1C;
        sum = p * 4 + (u32)tbl;
        src = (u8 *)(m * 4 + sum);
        do {
            *(rec + j + 8) = src[j];
            j++;
        } while (j < 4);
        i++;
    } while (0);
    if (i < 17) {
        goto outer;
    }
    slotM = slot & 0xFF;
    D_800A35F4[slotM * 0xE8 + 0x19] =
        D_800A3068w17[driver * 2] | (D_800A3069w17[driver * 2] << 1);
    D_800A35F4[slotM * 0xE8 + 0x1A] = gPadTypew17[driver];
    D_800A35F4[slotM * 0xE8 + 0x1B] = gPadLayoutw17[driver];
}

extern u8 D_800BBA24[];
void func_8006B3E0(s32 arg0, s32 arg1, s32 arg2) {
    s32 i;
    u8 *tbl;
    u8 *src;
    u8 *walk;
    u8 *dst;
    u8 *q;
    s32 off;
    s32 mask2;
    i = 0;
    mask2 = arg2 & 0xFF;
    arg0 &= 0xFF;
    tbl = D_800BBA24;
    src = tbl + arg0 * 0x44;
    arg1 &= 0xFF;
    walk = (u8 *)D_800A35F4 + arg1 * 0xE8;
    off = mask2 * 0xC;
    off += 0x1C;
    dst = walk + off;
    do {
        q = dst + i;
        q[8] = *(src + mask2 * 4 + i);
        i += 1;
    } while (i < 4);
}

extern u8 *volatile D_800A3604Vol asm("D_800A3604.NON_MATCHING");
extern u8 D_800A306D[];
extern u8 D_800A3078[];
extern u8 gMusicVolumeScaledR[] asm("gMusicVolumeScaled.NON_MATCHING");
extern u8 gStereoEnabledR[] asm("gStereoEnabled.NON_MATCHING");

void func_8006B464(void) {
    u8 *rec;
    s32 b0;
    s32 a1;
    u32 bB;
    s32 b2;
    u8 *rec2;
    s32 i;

    rec = D_800A3604Vol;
    b0 = rec[0];
    a1 = b0 & 3;
    do {
    } while (0);
    D_800A3073[-4] = ((u8)b0 >> 2) & 1;
    D_800A3073[-5] = a1;
    D_800A3073[-7] = ((u8)b0 >> 6) & 1;
    D_800A3073[-3] = (u8)b0 >> 7;
    bB = rec[0xB];
    D_800A3073[-2] = bB & 1;
    if ((bB & 1) != 0) {
        if (a1 != 1) {
            D_800A3073[-2] = 0;
        }
    }
    D_800A3073[-1] = (bB >> 1) & 1;
    rec2 = D_800A3604Vol;
    gCdVolumew15[0] = rec2[1];
    b2 = rec2[2];
    gMusicVolumew15[0] = b2;
    gMusicVolumeScaledR[0] = b2 * 127 / 100;
    if (D_800A306D[-1] != 0) {
        gStereoEnabledR[0] = 0;
    } else {
        gStereoEnabledR[0] = 1;
    }
    D_800A3078[0] = D_800A3604Vol[3];
    i = 0;
    do {
        D_800A331CAbsolute[i] = (D_800A3604Vol + i)[4];
        i += 1;
    } while (i < 6);
    D_800A37D0[0] = D_800A3604Vol[0xA];
}

/*
 * Retail re-reads the D_800A3604 pointer (gp) before every
 * store, so the pointer variable is volatile here. The D_800A306C-3072/75
 * bytes are untracked; reached as D_800A3073[-N]/[+2] (already declared
 * in this TU).
 */
extern u16 gCdVolumeAbsolute[];

void CardMenuSaveSettings(void) {
    s32 i;

    D_800A3604Vol[0] = D_800A3073[-3] << 7 | D_800A3073[-7] << 6 |
                       D_800A3073[-6] << 5 | D_800A3073[-4] << 2 |
                       D_800A3073[-5];
    D_800A3604Vol[0xB] =
        D_800A3073[2] << 2 | D_800A3073[-1] << 1 | D_800A3073[-2] & 1;
    D_800A3604Vol[1] = gCdVolumeAbsolute[0];
    D_800A3604Vol[2] = gCdVolumeAbsolute[1];
    D_800A3604Vol[3] = D_800A3078[0];
    for (i = 0; i < 6; i++) {
        (D_800A3604Vol + i)[4] = D_800A331CAbsolute[i];
    }
    D_800A3604Vol[0xA] = D_800A37D0[0];
}

extern s32 D_800B0B1C[];
extern s32 D_800B0B1CNM[] asm("D_800B0B1C.NON_MATCHING");

void CardUpdateDriverRecords(u8 arg0, s8 arg1, u8 arg2, u8 arg3) {
    CardMoveRecord buf;
    u8 *p;
    char *name;
    s32 i;
    s32 top;
    s32 j;
    s32 n;
    s32 value;
    s32 flags;
    u8 slot;
    u8 idx;
    u8 isNew;

    CardEnableAndTestEvents();
    if (CardResolveSlot() & 0xFF) {
        CardLoadSaveTable(0);
    }
    CardTestAndDisableEvents();
    i = arg1;
    if (i >= 0) {
        top = i;
        p = gPlayerDriver + i;
        do {
            isNew = 0;
            idx = RaceFindDriverPosition(*p);
            name = gDriverNames[*p];
            if (D_800A3A58 == 0) {
                slot = 0xFF;
            } else {
                j = 0;
                while (j < D_800A3A58) {
                    if (strcmp(name, D_800A35F4 + j * 0xE8) == 0) {
                        slot = j;
                        goto found;
                    }
                    j++;
                }
                slot = 0xFF;
            }
        found:
            if (slot == 0xFF) {
                isNew = 1;
            }
            if (arg2 != 0 && top != 0) {
                value = 0x7FFFFFFF;
            } else {
                value = D_800AE1EC[idx];
            }
            if (top != 0) {
                if (arg3 != 0) {
                    flags = 2;
                } else {
                    flags = 8;
                }
            } else {
                flags = 0x18;
            }
            if (isNew) {
                func_8006ADC4(i, gDriverNames[*p], gSelectedTrack[0], idx,
                              value, arg0, D_800B0B1C[idx] == -1, flags);
            } else {
                func_8006B1CC(i, slot, gSelectedTrack[0], idx, value, arg0,
                              D_800B0B1CNM[idx] == -1, flags);
                if (slot != 0) {
                    buf = ((CardMoveRecord *)D_800A35F4)[slot];
                    n = slot - 1;
                    while (n >= 0) {
                        ((CardMoveRecord *)D_800A35F4)[n + 1] =
                            ((CardMoveRecord *)D_800A35F4)[n];
                        n--;
                    }
                    *(CardMoveRecord *)D_800A35F4 = buf;
                }
            }
            i--;
            p--;
        } while (i >= 0);
    }
    CardMenuSaveSettings();
    CardEnableAndTestEvents();
    CardResolveSlot();
    func_8006AA70();
    CardTestAndDisableEvents();
}

extern u8 D_800B9BB4[];

extern s8 D_800B9B6E[];
void func_8006BA68(void) {
    u8 *base;
    u8 *entry;
    u8 *byte;
    s32 i;
    s32 k;
    s32 ffff;
    s32 fill;
    s32 magic;

    func_8006BD68();
    i = 0x17;
    base = D_800B9B6E;
    entry = base + 0x44;
    base[0] = 0;
    D_800B9B6F[0] = 0;
    D_800B9B70[0] = 0;
    D_800B9B71[0] = 0;
    D_800B9B72[0] = 0;
    do {
        *(s16 *)entry = 0;
        i -= 1;
        entry -= 2;
    } while (i >= 0);
    i = 0;
    ffff = 0xFF;
    magic = 0x7FFFFFFF;
    fill = 0x20;
    do {
        entry = D_800B9BB4 + i * 0xC;
        k = 3;
        byte = entry + 3;
        ((RecordRow *)entry)->unk4 = ffff;
        ((RecordRow *)entry)->unk6 = ffff;
        ((RecordRow *)entry)->unk8 = magic;
        do {
            *byte = fill;
            k -= 1;
            byte -= 1;
        } while (k >= 0);
        i += 1;
    } while (i < 0x11);
}

/* Loads the settings record at D_800B9B73 into the menu globals (the
 * inverse of func_8006BD68 below) and spreads the 17 four-character rows
 * into D_800BBA24, keeping the selected row in D_800A3860. */
void func_8006BB1C(void) {
    u8 *rec;
    u8 *row;
    u8 *table;
    u8 *src;
    u8 *dst;
    u8 flags;
    u32 v74;
    u32 v82;
    s32 level;
    s32 gear;
    s32 entry;
    s32 i;
    extern u8 D_800B9B73[];
    extern u8 D_800B9B74[];
    extern u8 D_800B9B75[];
    extern u8 D_800B9B76[];
    extern u8 D_800B9B77[];
    extern u8 D_800B9B78[];
    extern u8 D_800B9B79[];
    extern u8 D_800B9B7F[];
    extern u8 D_800B9B80[];
    extern u8 D_800B9B81[];
    extern u8 D_800B9B82[];
    extern u8 D_800BBA24[];
    extern u8 D_800A306C[];
    extern u8 D_800A306E[];
    extern u8 D_800A306F[];
    extern u8 D_800A3070[];
    extern u8 D_800A3071[];
    extern u8 D_800A3071NM[] asm("D_800A3071.NON_MATCHING");
    extern u8 D_800A3072[];
    extern u8 D_800A308C[];
    extern s8 gPadLayout[];
    extern s32 D_800A37D0[];
    extern u8 gMusicVolumeScaled[];
    extern u8 gStereoEnabled[];

    level = D_800B9B73[0];
    flags = D_800B9B75[0];
    v74 = D_800B9B74[0];
    v82 = D_800B9B82[0];
    gPlayerDriver[0] = level;
    level = flags & 3;
    gSelectedTrack[0] = v74;
    D_800A306F[0] = (flags >> 2) & 1;
    D_800A3069[0] = (flags >> 3) & 1;
    D_800A3068[0] = (flags >> 4) & 1;
    D_800A306C[0] = (flags >> 6) & 1;
    D_800A306E[0] = level;
    D_800A3070[0] = flags >> 7;
    D_800A3071[0] = v82 & 1;
    if ((v82 & 1) != 0 && level != 1) {
        D_800A3071NM[0] = 0;
    }

    gCdVolumew15[0] = D_800B9B76[0];
    gear = D_800A306C[0];
    D_800A3072[0] = (v82 >> 1) & 1;
    gMusicVolumew15[0] = D_800B9B77[0];
    gMusicVolumeScaled[0] = (D_800B9B77[0] * 0x7F) / 100;
    if (gear != 0) {
        gStereoEnabled[0] = 0;
    } else {
        gStereoEnabled[0] = 1;
    }

    D_800A3078[0] = D_800B9B78[0];
    for (i = 0; i < 6; i++) {
        D_800A331C[i] = D_800B9B79[i];
    }

    if (D_800B9B7F[0] == gPadTypew18c[0]) {
        D_800A308C[0] = gPadTypew18c[0];
        gPadLayout[0] = D_800B9B80[0];
    } else {
        gPadLayout[0] = 0;
    }

    rec = D_800B9B81;
    D_800A37D0[0] = rec[0];
    entry = 0;
    table = D_800BBA24;
    row = rec + 0x33;
outer:
    i = 0;
    src = row;
    dst = table;
inner:
    *dst = *src;
    if (entry == gSelectedTrack[0]) {
        D_800A3860S8[i] = *src;
    }
    src++;
    i++;
    dst++;
    if (i < 4) {
        goto inner;
    }
    table += 4;
    entry++;
    row += 0xC;
    if (entry < 0x11) {
        goto outer;
    }
}

void func_8006BD68(void) {
    u8 *dest;
    u8 *rec;
    s32 i;
    s32 srcRow;
    s32 dstRow;
    s32 dst;
    s32 src;
    s32 end;
    extern char *D_8009A31CStr[] asm("D_8009A31C.NON_MATCHING");
    extern u8 gSelectedTrackR[] asm("gSelectedTrack.NON_MATCHING");
    extern u8 D_800A306CR[] asm("D_800A306C.NON_MATCHING");
    extern u8 D_800A306ER[] asm("D_800A306E.NON_MATCHING");
    extern u8 D_800A306FR[] asm("D_800A306F.NON_MATCHING");
    extern u8 D_800A3070R[] asm("D_800A3070.NON_MATCHING");
    extern u8 D_800A3071R[] asm("D_800A3071.NON_MATCHING");
    extern u8 D_800A3072R[] asm("D_800A3072.NON_MATCHING");
    extern u8 D_800A3075[];
    extern s8 gPadLayout[];
    extern u16 gCdVolumeR[] asm("gCdVolume.NON_MATCHING");
    extern u16 gMusicVolume[];
    extern u8 D_800B9B44[];
    extern u8 D_800B9B73[];
    extern u8 D_800B9B74[];
    extern u8 D_800B9B75[];
    extern u8 D_800B9B76[];
    extern u8 D_800B9B77[];
    extern u8 D_800B9B78[];
    extern u8 D_800B9B79[];
    extern u8 D_800B9B7F[];
    extern u8 D_800B9B80[];
    extern u8 D_800B9B81[];
    extern u8 D_800B9B82[];

    dest = D_800B9B44;
    strcpy((char *)dest, D_8009A31CStr[gSelectedTrack[0]]);
    strcpy((char *)dest + 0x10, gDriverNames[gPlayerDriver[0]]);
    D_800B9B73[0] = D_800A36E1[-1];
    D_800B9B74[0] = gSelectedTrackR[0];
    D_800B9B75[0] =
        D_800A306ER[0] |
        (D_800A3070R[0] << 7 | D_800A306CR[0] << 6 | D_800A306D[0] << 5 |
         D_800A3068[0] << 4 | D_800A3069[0] << 3 | D_800A306FR[0] << 2);
    D_800B9B82[0] =
        D_800A3075[0] << 2 | D_800A3072R[0] << 1 | D_800A3071R[0] & 1;
    D_800B9B76[0] = gCdVolumeR[0];
    D_800B9B77[0] = gMusicVolume[0];
    D_800B9B78[0] = D_800A3078[0];
    i = 0;
    do {
        D_800B9B79[i] = D_800A331C[i];
        i += 1;
    } while (i < 6);
    i = 0;
    rec = D_800B9B7F;
    rec[0] = gPadTypew17[0];
    D_800B9B80[0] = gPadLayout[0];
    D_800B9B81[0] = D_800A37D0[0];
    srcRow = (s32)D_800BBA24;
    dstRow = (s32)rec + 0x35;
    do {
        dst = dstRow;
        src = srcRow;
        end = dstRow + 4;
        do {
            *(u8 *)dst = *(u8 *)src;
            dst += 1;
            src += 1;
        } while (dst < end);
        srcRow += 4;
        dstRow += 0xC;
        i += 1;
    } while (i < 0x11);
}

extern s32 D_8009A4C0[];
extern u8 D_800A3A10Obj[] asm("D_800A3A10");
extern u8 *D_800A3908[];
extern MenuObj *D_800A377C[];
extern u8 D_800A358C;
extern u8 D_800A3770;

/* Builds the card file-list screen: a centred title (D_8009A4C0[0]), a
 * four-row frame, two backdrop panels, seven name rows from D_800B0A2C and
 * two scroll markers. Every object is chained through unk1C.
 *
 * The title store goes through a plain u8 array (D_800A3A10Obj) and the
 * title reads are struct members: sched1 can then sink the store below the
 * argument loads, as in retail. */
void CardMenuBuildFileList(void) {
    s32 i;
    s32 x;
    s32 y;
    s32 h;
    MenuObj *prev;
    MenuObj *node;
    u8 *pkt;
    MenuObj *obj;

    MenuFontSet(2, 2);
    y = 0x3C;
    x = MenuStringWidth(D_8009A4C0[0]);
    x = (0x78 - x) / 2;
    prev = MenuCreateTextObject(x, 0x43);
    prev->orderingDepth = 7;
    prev->drawOffsetX = x;
    i = 0;
    *(MenuObj **)D_800A3A10Obj = prev;
    MenuSetTextObject((MenuObj *)prev, 2, 2, D_8009A4C0[0], 0,
                      prev->orderingDepth);
    do {
        node = MenuCreateTexturedRect(0, y, 0x78, 0x18, 9, 1, 0);
        prev->next = (MenuObj *)node;
        pkt = node->primitive;
        node->velocityX = 2;
        node->x = -0x78;
        node->velocityY = 0;
        switch (i) {
        case 0:
            h = 0;
            break;
        case 1:
        case 2:
            h = 0xC;
            break;
        case 3:
            h = 0x18;
            break;
        }
        MenuSetTexturedQuad(pkt, 9, 0, h, (u16)node->width, (u16)node->height);
        i += 1;
        y += node->height;
        prev = (MenuObj *)node;
    } while (i < 4);
    y = 0x3C;
    i = 0;
    do {
        obj = (u8 *)MenuCreateFlatRect(0, y, 0x78, 0x60, 0, 0x20, 0x20, 0x40, 1,
                                       1);
        obj->x = -0x78;
        obj->velocityX = 2;
        obj->orderingDepth = 0xA;
        prev->next = obj;
        prev = obj;
        i += 1;
    } while (i < 2);
    y = 0x55;
    i = 0;
    do {
        obj = (u8 *)MenuCreateTextObject(0, y);
        obj->orderingDepth = 2;
        MenuSetTextObject(obj, 2, 2, (s32)(D_800B0A2C + i * 0x10), 0,
                          obj->orderingDepth);
        obj->drawOffsetX = 0xB;
        obj->velocityX = 2;
        obj->x = -0x6E;
        if (i == 0) {
            D_800A3908[0] = obj;
        }
        prev->next = obj;
        prev = obj;
        i += 1;
        y += 9;
    } while (i < 7);
    i = 0;
    D_800A358C = D_800A3968;
    do {
        s32 width;
        s32 height;
        s32 red;
        s32 green;
        s32 blue;

        if (i == 0) {
            height = 9;
            width = 0x64;
            red = 0;
            green = 0;
            blue = 0xFF;
            y = 0x54;
        } else {
            height = 2;
            width = 8;
            red = 0xC0;
            green = 0xC0;
            blue = 0xC0;
            y = 0x5E;
        }
        obj = (u8 *)MenuCreateFlatRect(0, y, width, height, 0, red, green, blue,
                                       i == 0, 1);
        if (i == 0) {
            D_800A377C[0] = obj;
        }
        prev->next = obj;
        obj->velocityX = 2;
        obj->orderingDepth = 3;
        if (i != 0) {
            obj->orderingDepth = -1;
        }
        prev = obj;
        i += 1;
        obj->drawOffsetX = 0xA;
        obj->x = -0x6E;
    } while (i < 2);
    D_800A3770 = 0;
}

extern char *D_8009A31CStr[] asm("D_8009A31C.NON_MATCHING");
extern s32 D_8009A4D8[];
void func_8006C668(s32 start, s32 arg1);

/* Card-menu mode switch (gScreenState == 0x28) or cursor step: arg0 nonzero
 * steps the cursor, scrolling the row window when it reaches the edge. */
void func_8006C2D0(s32 arg0) {
    s32 i;
    register MenuObj *node;
    MenuText *entry;
    MenuObj *s;
    u8 *sentinel;
    MenuObj *head;
    MenuObj *cursor;
    s32 row;
    s32 row16;
    s32 gear;
    s32 mode;

    if (gScreenState[0] == 0x28) {
        node = D_800A3908[0];
        for (i = 0; i < 2; i++) {
            entry = (u8 *)node->primitive;
            entry->text = D_8009A4D8[i];
            if (node->orderingDepth < 0) {
                node->orderingDepth = -node->orderingDepth;
            }
            node = node->next;
        }
        s = D_800A377C[0];
        if (node != s) {
            sentinel = s;
            do {
                if (node->orderingDepth > 0) {
                    node->orderingDepth = -node->orderingDepth;
                }
                node = node->next;
            } while (node != sentinel);
            s = D_800A377C[0];
        }
        s->unk5 = 0;
        D_800A358C = 0;
    } else {
        if ((arg0 & 0xFF) != 0) {
            if (D_800A3968 < 0xF) {
                strcpy(D_800A3968 * 0x10 + D_800B0A2C,
                       D_8009A31CStr[gSelectedTrack[0]]);
                for (i = D_800A3968 + 1; i < 0xF; i++) {
                    row16 = i * 0x10;
                    *(u8 *)(row16 + D_800B0A2C) = 0;
                }
            }
            row = D_800A3968;
        } else {
            row = D_800A3968 - 1;
        }
        D_800A358C = row;
    }

    if (D_800A358C >= 0xF) {
        D_800A358C = 0xE;
    }
    if ((arg0 & 0xFF) != 0 && gScreenState[0] != 0x28) {
        if (D_800A358C >= 7) {
            D_800A377C[0]->unk5 = 6;
        } else {
            D_800A377C[0]->unk5 = D_800A358C;
        }
        if (D_800A358C < 6) {
            func_8006C668(0, D_800A358C);
        } else {
            func_8006C668((s8)(D_800A358C - 6), D_800A358C);
        }
    } else {
        D_800A377C[0]->unk5 = 0;
        D_800A358C = 0;
        if (gScreenState[0] != 0x28) {
            func_8006C668(0, D_800A3968 - 1);
        }
    }

    cursor = D_800A377C[0];
    gear = (s8)cursor->unk5;
    mode = gScreenState[0];
    cursor->y = gear * 9 + 0x54;
    if (mode != 0x28) {
        head = D_800A3908[0];
        if (head != cursor) {
            do {
                if (head->orderingDepth < 0) {
                    head->orderingDepth = -head->orderingDepth;
                }
                head = head->next;
            } while (head != cursor);
        }
    }
    D_800A3770 = 0;
}

extern MenuObj *D_800A3A10[];
void CardMenuSetColorNodeLayout(s32 low, s32 high, s32 color) {
    MenuObj *node;
    node = D_800A3A10[0];
    while (node != NULL) {
        node->unk5 = color;
        node->velocityX = color;
        node->x = node->drawOffsetX + low;
        node->targetX = node->drawOffsetX + high;
        node = node->next;
    }
}

#ifdef NON_MATCHING
/*
 * w7h: size-exact (0x84) draft; prologue matches incl. the early
 * lui/lw of D_800A3A10 BEFORE addiu sp (put the obj read first).
 * Remaining: store/load order only -- retail reloads *entry after the
 * sll/sra return extension and keeps the second D_800A3A10 lui/lw
 * before the srl/addu/sra divide; ours sinks the reload after it.
 * NOTE: plain asm(""); at this spot makes maspsx emit two hazard nops
 * (+8 bytes) -- do not use it as an order barrier here.
 */
void CardMenuCenterSelectedText(s32 textIndex) {
    s32 *entry;
    MenuText *obj;
    register s32 value asm("v1");

    obj = *(u8 **)&((MenuObj *)D_800A3A10[0])->primitive;
    entry = &D_8009A4C0[textIndex & 0xFF];
    value = MenuStringWidth(*entry);
    value = (0x78 - value) / 2;
    obj->text = *entry;
    *(u16 *)&((MenuObj *)D_800A3A10[0])->drawOffsetX = value;
}
#else
void CardMenuCenterSelectedText(s32 arg0) {
    s32 *entry;
    MenuText *obj;
    s32 value;
    s32 temp;
    s32 *tbl;
    s32 offset;
    s32 elem;
    MenuObj *node;

    obj = (u8 *)D_800A3A10[0]->primitive;
    offset = arg0 & 0xFF;
    tbl = D_8009A4C0;
    entry = tbl + offset;
    value = MenuStringWidth(*entry);
    elem = *entry;
    temp = 0x78 - value;
    node = D_800A3A10[0];
    value = temp / 2;
    obj->text = elem;
    node->drawOffsetX = value;
}

#endif

/* func_8006C700 expands this body twice, while func_8006C2D0 calls the
 * out-of-line copy, so both share one macro. */
#define CARD_MENU_SET_ROWS(startArg, limitArg)                                 \
    {                                                                          \
        s8 first = (startArg);                                                 \
        s32 index;                                                             \
        s32 limit;                                                             \
        u8 *node;                                                              \
        u8 *entry;                                                             \
        u8 *s;                                                                 \
        u8 *sentinel;                                                          \
                                                                               \
        if ((limitArg) < 6) {                                                  \
            limit = (limitArg);                                                \
        } else {                                                               \
            limit = first + 6;                                                 \
        }                                                                      \
        node = D_800A3908[0];                                                  \
        index = first;                                                         \
        if (limit >= index) {                                                  \
            do {                                                               \
                entry = *(u8 **)(node + 0x20);                                 \
                *(u32 *)(entry + 8) = (u32)(D_800B0A2C + index * 0x10);        \
                index++;                                                       \
                node = *(u8 **)(node + 0x1C);                                  \
            } while (limit >= index);                                          \
        }                                                                      \
        s = D_800A377C[0];                                                     \
        if (node != s) {                                                       \
            sentinel = s;                                                      \
            do {                                                               \
                entry = *(u8 **)(node + 0x20);                                 \
                *(u32 *)(entry + 8) = 0;                                       \
                node = *(u8 **)(node + 0x1C);                                  \
            } while (node != sentinel);                                        \
        }                                                                      \
    }

void func_8006C668(s32 start, s32 arg1) CARD_MENU_SET_ROWS(start, arg1)

    s32 func_8006C700(s32 arg0, s32 arg1) {
    s32 result;
    s32 target;
    s32 gear;
    MenuObj *node;
    s32 old;
    s32 start;
    s32 tmp;

    if ((arg1 & 0xFF) != 0) {
        target = D_800A3968;
        if (target == 0xF) {
            target = 0xE;
        }
    } else if (gScreenState[0] == 0x28) {
        target = 1;
    } else {
        target = D_800A3968 - 1;
    }

    node = D_800A377C[0];
    gear = (s8)node->unk5;
    result = 1;
    if ((arg0 & 0xFF) != 0) {
        if (gear >= 6)
            goto scrollForward;
        if (gear >= target)
            goto scrollForward;
        {
            old = D_800A358C;
            tmp = (u16)node->y;
            old = old + 1;
            tmp = tmp + 9;
            node->y = tmp;
            D_800A358C = old;
            gear = gear + 1;
            goto finish;
        }
    scrollForward:
        if (gear == 6 && D_800A358C < target) {
            old = D_800A358C;
            D_800A358C = old + 1;
            start = old - 5;
            CARD_MENU_SET_ROWS(start, target)
        } else {
            result = 0;
        }
    } else if (gear > 0) {
        s32 oldBack;
        s32 tmpBack;

        oldBack = D_800A358C;
        tmpBack = (u16)node->y;
        gear = gear - 1;
        oldBack = oldBack - 1;
        tmpBack = tmpBack - 9;
        D_800A358C = oldBack;
        node->y = tmpBack;
    } else {
        s32 oldTop;
        u8 newTop;

        oldTop = D_800A358C;
        if (oldTop != 0) {
            newTop = oldTop - 1;
            D_800A358C = newTop;
            CARD_MENU_SET_ROWS(oldTop - 1, target)
        } else {
            result = 0;
        }
    }
finish:
    *(s8 *)&D_800A377C[0]->unk5 = gear;
    return result;
}

extern s32 MenuPrefixWidth(u32, u8 *);
/* Expand the cursor helper here and in its caller with the same byte types. */
#define CARD_MENU_CURSOR_BODY(finish, font, size, index, text, cursor, result) \
    {                                                                          \
        MenuFontSet(font, size);                                               \
        if (*text == 0) {                                                      \
            *cursor = MenuCharWidth(0x20);                                     \
            finish(0);                                                         \
        } else {                                                               \
            result = MenuPrefixWidth(index, text);                             \
            *cursor = MenuCharWidth(text[index]);                              \
            finish(result);                                                    \
        }                                                                      \
    }
s32 func_8006C94C(u8 arg0, u8 arg1, u8 arg2, s8 *arg3, s16 *arg4) {
    s32 ret;
    CARD_MENU_CURSOR_BODY(return, arg0, arg1, arg2, arg3, arg4, ret);
}

void MenuHideCurrentObject(void) {
    D_800A377C[0]->next->orderingDepth = -1;
}

/* Keep the raw decrement and the byte index in separate values. */
void func_8006C9F8(void) {
    MenuObj *obj;
    u8 *ptr;
    s8 *entry;
    s32 status;
    s32 val;
    s32 length;
    u8 index;

    obj = (u8 *)D_800A377C[0]->next;
    entry = (s8 *)D_800B0A2C + D_800A358C * 0x10;
    obj->orderingDepth = 1;
    length = strlen((char *)entry);
    obj->unk5 = length;
    if ((s8)length >= 0xF) {
        obj->unk5 = 0xE;
    }
    val = obj->unk5 - 1;
    obj->unk5 = val;
    index = val;
    entry = (s8 *)D_800B0A2C + D_800A358C * 0x10;
    {
        s8 *text = entry;
        s16 *cursor = &obj->width;
        s32 result;
        CARD_MENU_CURSOR_BODY(status =, 2, 2, index, text, cursor, result);
    }
    ptr = *(u8 **)D_800A377C;
    obj->x = status + 0xA;
    obj->y = *(u16 *)&((MenuObj *)ptr)->y + 9;
}
#undef CARD_MENU_CURSOR_BODY

void func_8006CB00(void) {
    s32 value;
    value = D_800A377C[0]->orderingDepth;
    if (value > 0)
        value = -value;
    else if (value == 0)
        value = -255;
    D_800A377C[0]->orderingDepth = value;
}

void func_8006CB40(void) {
    s32 value;
    s8 zero;
    value = D_800A377C[0]->orderingDepth;
    if (value < 0) {
        value = -value;
    } else if (value == (-255)) {
        zero = 0;
        value = zero;
    }
    D_800A377C[0]->orderingDepth = value;
}

void func_8006CB80(s32 arg0, s32 arg1, s32 arg2) {
    s32 threshold;
    s32 limitSave;
    MenuObj *st;
    s32 ch;
    s32 adj;
    s8 *entry;
    u8 idx;
    s32 result;
    extern char cardNames[][16] asm("D_800B0A2C");

    threshold = 0xF;
    if (arg1 & (~arg2)) {
        D_800A3830Absolute2[0] = 0;
        limitSave = 1;
    } else {
        D_800A3830Absolute[0] = D_800A3830Absolute2[0] + 1;
        if (threshold < D_800A3830Absolute[0]) {
            D_800A37F0Absolute[0] =
                D_800A37F0Absolute2[0] + (D_800A37F0Absolute2[0] / 2);
            if (0x9 <= D_800A37F0Absolute[0]) {
                limitSave = 8;
            } else {
                goto noStore;
            }
        } else {
            return;
        }
    }
    D_800A37F0Absolute3[0] = limitSave;
noStore:
    st = (u8 *)D_800A377C[0]->next;
    if ((s8)st->unk5 >= strlen(cardNames[D_800A358C])) {
        cardNames[D_800A358C][(s8)st->unk5] = ' ';
        cardNames[D_800A358C][(s8)st->unk5 + 1] = 0;
        ch = 0x21;
    } else {
        ch = (u8)cardNames[D_800A358C][(s8)st->unk5] - 0x20;
    }
    if ((arg0 & 0xFF) == 0) {
        adj = ch - D_800A37F0Absolute3[0];
        if ((s16)adj >= 0) {
            ch = adj;
        } else {
            ch = adj + 0x5F;
        }
        if ((u16)(ch - 1) < 0xF) {
            ch = 0;
        } else if ((u16)(ch - 0x1A) < 7) {
            ch = 0x19;
        } else if ((u16)(ch - 0x3B) < 6) {
            ch = 0x3A;
        } else if ((s16)ch >= 0x5B) {
            ch = 0x5A;
        }
    } else {
        adj = ch + D_800A37F0Absolute3[0];
        if ((s16)adj < 0x5F) {
            ch = adj;
        } else {
            ch = adj - 0x5F;
        }
        if ((u16)(ch - 1) < 0xF) {
            ch = 0x10;
        } else if ((u16)(ch - 0x1A) < 7) {
            ch = 0x21;
        } else if ((u16)(ch - 0x3B) < 6) {
            ch = 0x41;
        } else if ((s16)ch >= 0x5B) {
            ch = 0;
        }
    }
    ch += 0x20;
    cardNames[D_800A358C][(s8)st->unk5] = ch;
    idx = st->unk5;
    entry = (s8 *)cardNames[D_800A358C];
    MenuFontSetS32(2, 2);
    if (*entry == 0) {
        st->width = MenuCharWidth(0x20);
        result = 0;
    } else {
        result = MenuPrefixWidth(idx, entry);
        st->width = MenuCharWidth(entry[idx]);
    }
    st->x = result + 0xA;
}

extern char D_800B0A2D[];
void func_8006CE64(void) {
    u8 *obj;
    u8 index;
    s32 offset;
    s8 *entry;
    s32 status;
    offset = 0x10 * D_800A358C;
    D_800B0A2C[offset] = 0x41;
    D_800B0A2D[D_800A358C * 0x10] = 0;
    obj = (u8 *)D_800A377C[0]->next;
    *((u8 *)(obj + 5)) = 0;
    entry = ((s8 *)D_800B0A2C) + ((index = D_800A358C) * 0x10);
    MenuFontSetS32(2, 2);
    if ((*entry) == 0) {
        *((s16 *)(obj + 0x16)) = MenuCharWidth(0x20);
        status = 0;
    } else {
        status = MenuPrefixWidth(0, entry);
        *((s16 *)(obj + 0x16)) = MenuCharWidth(*entry);
    }
    *((s16 *)(obj + 6)) = status + 0xA;
}

void CardMenuAppendTrackName(void) {
    if (D_800A358C < D_800A3968) {
        strcpy(D_800B0A2C + D_800A358C * 16,
               (char *)D_8009A31C[gSelectedTrack[0]]);
    }
}

void func_8006CF90(u32 mode) {
    extern u8 gMemoryCardNameInitialCharacter[];
    MenuObj *node;
    MenuObj *st;
    char *entry;
    s8 c;
    s8 t;
    s8 ch;
    u8 idx;
    s32 result;

    node = D_800A377C[0];
    st = node->next;
    mode &= 0xFF;
    if (mode != 0) {
        if ((s8)st->unk5 > 0) {
            st->unk5 = (s8)st->unk5 - 1;
        }
    } else {
        t = (s8)st->unk5;
        c = t;
        if (t < 14) {
            c = c + 1;
            st->unk5 = c;
            if (c == strlen(&D_800B0A2C[D_800A358C * 16])) {
                strcat(&D_800B0A2C[D_800A358C * 16],
                       gMemoryCardNameInitialCharacter);
            }
        }
    }
    idx = st->unk5;
    entry = D_800B0A2C + D_800A358C * 16;
    MenuFontSetS32(2, 2);
    ch = *entry;
    if (ch == 0) {
        st->width = MenuCharWidth(0x20);
        result = 0;
    } else {
        result = MenuPrefixWidth(idx, entry);
        st->width = MenuCharWidth(*(s8 *)(entry + idx));
    }
    st->x = result + 10;
}

s32 CardMenuCheckTrackNameCapacity(void) {
    if (D_800A358C < D_800A3968) {
        gCardMenuMessage = 16;
        return 1;
    } else {
        return 0;
    }
}

extern u8 D_800B9B44[];
void CardMenuWriteSaveSlot(void) {
    s32 isCurrent;
    isCurrent = D_800A358C < D_800A3968;
    strcpy(D_800B9B44, &D_800B0A2C[D_800A358C * 16]);
    CardEnableAndTestEvents();
    if ((CardWriteSaveSlot(D_800B9B44, isCurrent, D_800A358C) & 0xFF) == 1) {
        gCardMenuMessage = 0x11;
    }
    CardTestAndDisableEvents();
}

/* The same 16-byte name slots as D_800B0A2C, typed with a 16-byte stride so
 * that gcc hoists the slot address out of the loop. */
typedef struct {
    s8 s[16];
} Nm;
extern Nm D_800B0A2CNm[] asm("D_800B0A2C");

/* Trims trailing spaces off the current name slot. Returns 0 when the slot
 * holds nothing but spaces. */
s32 func_8006D178(void) {
    u8 i;
    u8 found;

    found = 0;
    i = strlen((char *)D_800B0A2CNm[D_800A358C].s);
    while ((s8)i >= 0 && (found & 0xFF) == 0) {
        switch (D_800B0A2CNm[D_800A358C].s[(s8)i]) {
        default:
            found = 1;
            break;
        case 0:
        case ' ':
            i--;
            break;
        }
    }
    if (found) {
        (D_800B0A2CNm + D_800A358C)->s[(s8)i + 1] = 0;
        return 1;
    }
    return 0;
}

extern u8 D_800B9B73[];
extern u8 D_800B9B74[];
extern void func_8006BB1C(void);

s32 func_8006D258(void) {
    typedef struct {
        s32 words[0x13C / 4];
    } SaveRec;
    extern u8 gSelectedTrackR2[] asm("gSelectedTrack.NON_MATCHING");
    extern u8 gSelectedTrackR3[] asm("gSelectedTrack.NON_MATCHING");
    s32 status;
    s32 match;
    s32 i;
    SaveRec *rec;
    u8 idx;
    u8 *paint;

    CardEnableAndTestEvents();
    status = CardCheckStatus(gCardSlot, 1);
    CardTestAndDisableEvents();
    status &= 0xFF;
    if (status == 3) {
        gCardMenuMessage = 0xF;
        return 0;
    }
    if (status != 0) {
        gCardMenuMessage = 1;
        return 0;
    }
    rec = (SaveRec *)(D_800A3A0C + 4);
    *(SaveRec *)&D_800B9B44[0] = rec[D_800A358C];
    func_8006BB1C();
    idx = D_800B9B74[0];
    paint = D_800AE178[idx];
    gSelectedTrack[0] = idx;
    func_8005E4A4(paint);
    MenuSetTrackLabel(gSelectedTrackR2[0]);
    MenuFormatLapCount(gSelectedTrackR3[0]);
    gPlayerDriver[0] = D_800B9B73[0];
    func_80063AE0(0, gPlayerDriver[0]);
    MenuSetDriverNameLabel(0, D_800A36E1[-1]);
    for (i = 0; i < 0x18; i++) {
        if (D_800A36E1w15[-1] == D_8009AD40[i]) {
            match = i;
            break;
        }
    }
    D_800A3980[0] = match;
    strcpy(D_800BB9B4, gDriverNames[gPlayerDriver[0]]);
    BufferClear17Bytes();
    return 1;
}

#ifdef NON_MATCHING
/* w7i: draft to 0xa4 exact length, 7 rows off: entry order and
 * i/j register naming (target: i in a3 inited FIRST at entry, j in a2;
 * both row-pointer temps outer-loop). src[j + 0x24] keeps the +0x24 in
 * the lbu displacement. */
void CardMenuCopyRecordNames(u8 destinationIndex, u8 sourceIndex) {
    char *src;
    u8 *dst;
    u8 i;
    u8 j;

    for (i = 0; i < 0x11; i++) {
        dst = &D_800BBA24[destinationIndex * 0x44 + i * 4];
        src = D_800A35F4 + sourceIndex * 0xE8 + i * 0xC;
        for (j = 0; j < 4; j++) {
            dst[j] = src[j + 0x24];
        }
    }
}
#else
void CardMenuCopyRecordNames(u8 arg0, u8 arg1) {
    u8 i;
    u8 j;
    u8 *dst;
    u8 *src;
    s32 srcOff;
    s32 row;
    s32 base;
    s32 dstOff;

    i = 0;
    base = (s32)D_800BBA24;
    row = arg0 * 0x44;
outer:
    j = 0;
    dstOff = row + base;
    dst = (u8 *)(i * 4 + dstOff);
    srcOff = arg1 * 0xE8;
    do {
        src = (u8 *)(srcOff + (s32)D_800A35F4);
        src += i * 0xC;
        dst[j] = *(src + j + 0x24);
        j++;
    } while (j < 4);
    i++;
    if (i < 0x11) {
        goto outer;
    }
}

#endif

extern u8 D_800BBA24_nm[] asm("D_800BBA24.NON_MATCHING");
extern u8 D_800A3068_nm[] asm("D_800A3068.NON_MATCHING");
extern u8 D_800A3069_nm[] asm("D_800A3069.NON_MATCHING");
extern u8 gPadLayout_nm[] asm("gPadLayout.NON_MATCHING");
extern u8 D_800A308C_nm[] asm("D_800A308C.NON_MATCHING");
extern s8 gPadType_nm[] asm("gPadType.NON_MATCHING");
void func_8006D4C8(u8 arg0, u8 arg1) {
    u8 i;
    u8 j;
    u8 *dst;
    u8 *src;
    s32 bit;
    s32 srcOff;
    s32 row;
    s32 base;
    s32 dstOff;
    i = 0;
    base = (s32)D_800BBA24_nm;
    row = arg0 * 0x44;
outer:
    j = 0;

    dstOff = row + base;
    dst = (u8 *)((i * 4) + dstOff);
    srcOff = arg1 * 0xE8;
    do {
        src = (u8 *)(srcOff + ((s32)D_800A35F4));
        src += i * 0xC;
        dst[j] = *((src + j) + 0x24);
        j++;
    } while (j < 4);
    i++;
    if (i < 0x11) {
        goto outer;
    }
    bit = ((u8 *)D_800A35F4)[(arg1 * 0xE8) + 0x19] & 1;
    D_800A3068_nm[arg0 * 2] = bit;
    D_800A3069_nm[arg0 * 2] =
        (((u8 *)D_800A35F4)[(arg1 * 0xE8) + 0x19] >> 1) & 1;
    if (((u8 *)D_800A35F4)[(arg1 * 0xE8) + 0x1A] == gPadType_nm[arg0]) {
        gPadLayout_nm[arg0] = ((u8 *)D_800A35F4)[(arg1 * 0xE8) + 0x1B];
        D_800A308C_nm[arg0] = ((u8 *)gPadType_nm)[arg0];
    } else {
        gPadLayout_nm[arg0] = 0;
    }
}

void CardMenuClearNameCharacters(s32 arg) {
    u8 *base;
    u8 *tbl;
    u8 i;
    s32 offset;

    i = 0;
    offset = arg & 0xFF;
    tbl = D_800BBA24;
    base = tbl + offset * 4;
    do {
        base[i] = 0x20;
        D_800A3860[0][i] = 0x20;
        i += 1;
    } while (i < 4);
}

/* w7i: full shape known; closest draft: src row via
 * &D_800BBA24[arg0 * 4 + i * 0x44], D_800A3860 base materialized FIRST,
 * `move a1,zero` (j init) placed before the row math. */
void func_8006D684(u8 arg0) {
    u8 *srcBase;
    s8(*dstBase)[4];
    u8 i;
    u8 j;

    dstBase = D_800A3860;
    srcBase = D_800BBA24;
    i = 0;
    do {
        do {
            if (1) {
                ;
            }
            for (j = 0; j < 4; j++) {
                dstBase[i][j] = (&srcBase[i * 0x44] + arg0 * 4)[j];
            }
            i++;
        } while (i < 2);
    } while (0);
}

void func_8006D708(u8 arg0, u8 arg1, u8 arg2) {
    u8 *rowB;
    u8 *src;
    u8 *dst;
    u8 *tbl;
    u8 *q2;
    u8 *walk;
    u8 *p;
    char *name;
    u8 match;
    u8 i;
    s32 n;
    s32 j;
    s32 off;
    s32 q;
    s32 x;
    s32 x2;
    s32 q3;
    u8 *tbl2;
    u8 *rp;

    if (arg2 == 0) {
        if (arg0 == 1) {
            return;
        }
        rowB = D_800B9BB4 + arg1 * 0xC;
    }
    i = 0;
    x = arg0;
    tbl = D_800BBA24;
    q = (u32)tbl + x * 0x44;
    dst = (u8 *)(arg1 * 4 + q);
    q2 = (u8 *)D_800A3860;
    src = x * 4 + q2;
again:
    dst[i] = src[i];
    if (arg2 == 0) {
        rowB[i] = src[i];
    }
    i++;
    if (i < 4) {
        goto again;
    }
    if (arg2 != 0) {
        name = gDriverNames[gPlayerDriver[arg0]];
        if (D_800A3A58 == 0) {
            match = 0xFF;
        } else {
            n = 0;
            while (n < D_800A3A58) {
                if (strcmp(name, D_800A35F4 + n * 0xE8) == 0) {
                    match = n;
                    goto found;
                }
                n++;
            }
            match = 0xFF;
        }
    found:
        if (match == 0xFF) {
            return;
        }
        j = 0;
        off = arg1;
        x2 = arg0;
        tbl2 = D_800BBA24;
        q3 = (u32)tbl2 + x2 * 0x44;
        src = (u8 *)(off * 4 + q3);
        walk = (u8 *)D_800A35F4 + match * 0xE8;
        p = walk + (off * 0xC + 0x1C);
        do {
            rp = p + j;
            rp[8] = *src;
            src++;
            j++;
        } while (j < 4);
    }
}

extern s32 D_8009AB80[];
extern s32 D_8009AB00[];
void CardMenuShowMessage(s32 arg0) {
    u8 *obj;
    u8 *field20;
    u8 *end;
    u8 menuId;
    s32 val;
    s32 val2;
    obj = D_800A3908[0];
    menuId = gCardMenuMessage;
    field20 = *((u8 **)(obj + 0x20));
    if (menuId == 0x1C) {
        if (gCardSlot != 0) {
            menuId = 0x1D;
        } else {
            menuId = 0x1C;
        }
    } else if (menuId == 0x1E) {
        if (gCardSlot != 0) {
            menuId = 0x1F;
        } else {
            menuId = 0x1E;
        }
    } else if (menuId == 0xD) {
        if (gCardSlot != 0) {
            menuId = 0x1A;
        } else {
            menuId = 0x19;
        }
    }
    if (gPadType[0] == 2) {
        *((s32 *)(field20 + 8)) = D_8009AB80[menuId];
    } else {
        *((s32 *)(field20 + 8)) = D_8009AB00[menuId];
    }
    if ((arg0 & 0xFF) == 0) {
        obj = *((u8 **)(obj + 0x1C));
        if (obj != D_800A377C[0]) {
            end = D_800A377C[0];
            do {
                val = *((s16 *)(obj + 0x1A));
                if (val > 0) {
                    *((s16 *)(obj + 0x1A)) = -(*((s16 *)(obj + 0x1A)));
                }
                obj = *((u8 **)(obj + 0x1C));
            } while (obj != end);
        }
        val2 = D_800A377C[0]->orderingDepth;
        if (val2 > 0) {
            val2 = -val2;
        } else if (val2 == 0) {
            val2 = -0xFF;
        }
        D_800A377C[0]->orderingDepth = val2;
    }
    D_800A3770 = 1;
}

extern u8 *D_8009AB00nm[] asm("D_8009AB00.NON_MATCHING");
extern u8 *D_8009AB80nm[] asm("D_8009AB80.NON_MATCHING");
extern void *D_800A3908nm[] asm("D_800A3908.NON_MATCHING");

void func_8006DA40(void) {
    MenuObj *node;
    MenuObj *prev;
    u8 *pkt;
    u8 *field10;
    u8 idx;
    s32 err;
    s32 height;
    s32 i;
    s32 y;
    y = 0x50;
    i = 0;
    do {
        node = MenuCreateTexturedRect(0x64, y, 0x78, 0x18, 9, 1, 0);
        if (i == 0) {
            D_800A3A10[0] = (MenuObj *)node;
        } else {
            prev->next = node;
        }
        field10 = (u8 *)node + 0x10;
        pkt = node->primitive;
        node->velocityX = 2;
        *((s16 *)field10) = 0;
        node->x = -0x78;
        switch (i) {
        case 0:
            height = 0;
            break;

        case 1:
            height = 0xC;
            break;

        case 2:
            height = 0x18;
            break;
        }

        MenuSetTexturedQuad(pkt, 9, 0, height, (u16)node->width,
                            (u16)node->height);
        y += node->height;
        prev = node;
        i += 1;
    } while (i < 3);
    y = 0x50;
    i = 0;
    do {
        node =
            MenuCreateFlatRect(0x64, y, 0x78, 0x48, 0, 0x20, 0x20, 0x40, 1, 1);
        node->x = -0x78;
        node->velocityX = 2;
        node->orderingDepth = 0xA;
        prev->next = node;
        prev = node;
        i += 1;
    } while (i < 2);
    node = MenuCreateTextObject(0x71, 0x55);
    err = gCardMenuMessage;
    node->orderingDepth = 2;
    if (err == 2) {
        idx = 0x1B;
    } else if (err == 0x1C) {
        idx = 0x1C;
        if (gCardSlot == 1) {
            idx = 0x1D;
        }
    } else if (err == 0xD) {
        idx = 0x19;
        if (gCardSlot == 1) {
            idx = 0x1A;
        }
    }
    if (gPadType_nm[0] == 2) {
        MenuSetTextObject((MenuObj *)node, 2, 2, (s32)D_8009AB80nm[idx], 0,
                          node->orderingDepth);
    } else {
        MenuSetTextObject((MenuObj *)node, 2, 2, (s32)D_8009AB00nm[idx], 0,
                          node->orderingDepth);
    }
    node->velocityX = 2;
    node->drawOffsetX = 0xB;
    node->x = -0x6B;
    D_800A3908nm[0] = node;
    prev->next = node;
}

void MenuUpdateAndDrawObjectLists(void) {
    MenuUpdateObjectPosition(D_800A3A10[0], 1);
    MenuDrawObjectList(((void **)gReplayIndex)[-11], 0xFF);
}

extern u8 D_800AEE3C[];
extern void PadCalibrateCenter(s32 arg0, s32 arg1, u32 arg2);

void func_8006DD28(u32 arg0, u32 arg1) {
    s32 i;
    s32 m;
    u32 n;
    s32 pos;
    extern u8 gPadLayoutUnsigned[] asm("gPadLayout");
    extern u8 D_800A36E4[];

    m = (u8)arg0;
    n = (u8)arg1;
    PadCalibrateCenter(m, n, gPadLayoutUnsigned[m]);
    pos = (m << 3) + m;
    for (i = 0; i < 3; i++) {
        if (i == 2) {
            s32 idx;

            idx = pos + i * 3;
            D_800AEE3C[idx] = 0;
            D_800AEE3D[idx] = 0xFF;
        } else if (n >= 5) {
            if (i == 0) {
                s32 idx;

                idx = pos + i * 3;
                D_800AEE3D[idx] = 0;
                D_800AEE3C[idx] = D_800AEE3E[idx];
            } else {
                s32 idx;

                idx = pos + i * 3;
                D_800AEE3D[idx] = 0xFF;
                D_800AEE3C[idx] = D_800AEE3E[idx];
            }
        } else {
            s32 idx;

            idx = pos + i * 3;
            D_800AEE3C[idx] = 0;
            D_800AEE3D[idx] = 0xFF;
        }
    }
    D_800A36E4[(u8)arg0] = 1;
}

void func_8006DE68(u32 arg0, u32 mode) {
    if ((mode & 0xFF) == 2) {
        s32 i;
        s32 j;
        s32 m;
        s32 pos;
        s32 end;

        i = 0;
        j = 2;
        m = (u8)arg0;
        pos = m << 3;
        pos += m;
        end = pos + 6;
        do {
            if (i == j) {
                D_800AEE3C[end] = 0x78;
                D_800AEE3C[end + 1] = 0x80;
                D_800AEE3C[end + 2] = 0x88;
            } else {
                D_800AEE3C[pos] = 0;
                D_800AEE3C[pos + 1] = 8;
                D_800AEE3C[pos + 2] = 0;
            }
            i++;
            pos += 3;
        } while (i < 3);
    } else {
        s32 n;
        s32 pos;

        n = (u8)arg0;
        pos = n << 3;
        pos += n;
        D_800AEE3C[pos] = 0x80;
        D_800AEE3C[pos + 1] = 0x78;
        D_800AEE3C[pos + 2] = 0x80;
        D_800AEE3C[pos + 3] = 0x80;
        D_800AEE3C[pos + 4] = 0x88;
        D_800AEE3C[pos + 5] = 0x80;
        D_800AEE3C[pos + 6] = 0x78;
        D_800AEE3C[pos + 7] = 0x88;
        D_800AEE3C[pos + 8] = 0x80;
    }
}

/* A mode above 2 falls off the end of the switch, as in retail: the return
 * value is whatever the dispatch left in v0 (2). The narrow `u8 arg3`
 * parameter makes gcc keep a raw copy of a3 for the mode 0 and 1 tests. */
u8 PadReadObjectAxis(u8 *arg0, s32 arg1, s32 arg2, u8 arg3) {
    u8 mode;

    mode = arg1;
    switch (mode) {
    case 0:
        if ((u8)arg2 != 2) {
            return (arg0)[0x3C6];
        } else if (arg3 == 0 || arg3 == (u8)arg2) {
            return (arg0)[0x3C7];
        } else {
            return (arg0)[0x3C6];
        }
    case 1:
        if ((u8)arg2 != 2) {
            return (arg0)[0x3C6];
        } else if (arg3 != 0 && arg3 != (u8)arg2) {
            return (arg0)[0x3C7];
        } else {
            return (arg0)[0x3C6];
        }
    case 2:
        if ((u8)arg2 == mode) {
            if ((u8)(arg3 - 2) < 2) {
                return (u8) ~(arg0)[0x3C5];
            } else {
                return (arg0)[0x3C5];
            }
        } else {
            return (arg0)[0x3C5];
        }
    }
}

/* The calibration table as PadAxisCal records, 9 bytes per pad. */
extern PadAxisCal gPadAxisCal[][3] asm("D_800AEE3C");

/* Widens the calibration range of pad arg0 with a fresh reading of each stick
 * axis (arg1 is the pad type, arg2 the subtype). Type 2 tracks min and max
 * for every axis. Types above 4 update one bound per axis, found by switching
 * on the axis; each case folds to a constant offset into the record. Other
 * types only call the two refresh functions. The K&R definition and the
 * `subtype` local follow PadCalibrateCenter. */
/* clang-format off */
void PadCalibrateRange(arg0, arg1, arg2)
u8 arg0;
u8 arg1;
u32 arg2;
/* clang-format on */
{
    u8 scratch[0x500];
    u8 axes[3];
    u8 subtype;
    s32 i;

    subtype = arg2;
    scratch[0x20B] = arg0;
    PadReadObjectState(scratch);
    if (arg1 == 2) {
        u8 value;

        for (i = 0; i < 3; i++) {
            value = PadReadAxis(scratch, i, arg1, subtype);
            axes[i] = value;
            if (value < gPadAxisCal[arg0][i].min) {
                gPadAxisCal[arg0][i].min = value;
            }
            if (gPadAxisCal[arg0][i].max < axes[i]) {
                gPadAxisCal[arg0][i].max = axes[i];
            }
        }
    } else if (arg1 > 4) {
        u8 value;

        for (i = 0; i < 3; i++) {
            value = PadReadAxis(scratch, i, arg1, subtype);
            axes[i] = value;
            switch (i) {
            case 0:
                if (axes[0] < gPadAxisCal[arg0][0].center) {
                    if (axes[0] < gPadAxisCal[arg0][0].max) {
                        gPadAxisCal[arg0][0].max = axes[0];
                    }
                }
                break;
            case 1:
                if (gPadAxisCal[arg0][1].center < axes[1]) {
                    if (gPadAxisCal[arg0][1].max < axes[1]) {
                        gPadAxisCal[arg0][1].max = axes[1];
                    }
                }
                break;
            case 2:
                if (axes[2] < gPadAxisCal[arg0][2].min) {
                    gPadAxisCal[arg0][2].min = axes[2];
                }
                if (gPadAxisCal[arg0][2].max < axes[2]) {
                    gPadAxisCal[arg0][2].max = axes[2];
                }
                break;
            }
        }
    }
    func_80062D38(arg0, arg1, axes);
    func_80062F6C(arg0, arg1);
}

void func_8006E484(u32 arg0, u32 arg1) {
    s32 i;
    s32 m;
    u32 n;
    s32 pos;
    s32 maxb;
    s32 white;
    s32 lt;
    s32 p;
    s32 d;
    u8 *q;
    u8 *v;
    i = 0;
    m = (u8)arg0;
    pos = (m << 3) + m;
    do {
        maxb = 0x80;
        white = 0xFF;
        n = (u8)arg1;
        lt = n < 5;
        p = 0;
    loop:
        v = (u8 *)(p + ((s32)D_800AEE3C));
        q = (u8 *)(pos + ((s32)v));
        if (i == 2) {
            if (((u32)(q[2] - 0x60)) >= 0x41) {
                q[2] = maxb;
            }
            d = q[1] - q[2];
            if (d < 9) {
                q[1] = white;
            }
            d = q[2] - q[0];
            if (d < 9) {
                q[0] = 0;
            }
        } else if (!lt) {
            if (((u32)((q[2] - 0x40) & 0xFF)) >= 0x81) {
                q[2] = maxb;
            }
            if (i == 0) {
                d = q[2] - q[1];
                if (d >= 0) {
                    if (d < 9) {
                        goto setg;
                    }
                } else {
                    d = q[1] - q[2];
                    if (d < 9) {
                        goto setg;
                    }
                }
                goto nextg;
            setg:
                q[1] = 0;
            nextg:;
                ;
                ;
            } else {
                d = q[1] - q[2];
                if (d >= 0) {
                    if (d < 9) {
                        goto setw;
                    }
                } else {
                    d = q[2] - q[1];
                    if (d < 9) {
                        q[1] = white;
                    }
                }
            }
        } else {
            if (q[2] >= 0x81) {
                q[2] = 0;
            }
            d = q[1] - q[0];
            if (d < 9) {
                q[0] = 0;
            setw:
                q[1] = white;
            }
        }
        i++;
    } while (0);
    p += 3;
    if (i < 3) {
        goto loop;
    }
}

/* Samples pad arg0's three stick axes into the third byte of its
 * calibration entries (D_800AEE3E). The K&R definition keeps retail's
 * entry-move order: arg2's move comes first and the narrow parameters
 * follow. `subtype` is a separate u8 local so the inlined PadReadAxis keeps
 * its own copy of arg2. */
/* clang-format off */
void PadCalibrateCenter(arg0, arg1, arg2)
u8 arg0;
u8 arg1;
u32 arg2;
/* clang-format on */
{
    u8 scratch[0x500];
    s32 i;
    s32 q;
    u8 subtype;

    subtype = arg2;
    scratch[0x20B] = arg0;
    PadReadObjectState(scratch);
    for (i = 0; i < 3; i++) {
        q = (u8)arg0 * 9 + i * 3;
        D_800AEE3E[q] = PadReadAxis(scratch, i, arg1, subtype);
    }
}
