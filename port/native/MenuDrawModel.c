void MenuDrawModel(s32 advanceSpin, s32 semiTrans, s32 fullScreenMode) {
    SVECTOR angles;
    VECTOR trans;
    s32 *ot;
    POLY_F4 *cursor;
    POLY_F4 *tmpl;
    ModelQuad *q;
    s32 i;
    s32 otz;
    s32 x;
    s32 y;
    s32 depth;

    cursor = (POLY_F4 *)((u8 *)gPrimitiveCursor[0]);
    ot = (s32 *)gOrderingTable[0];
    if (fullScreenMode & 0xFF) {
        x = 0xA0;
        y = 0x64;
        depth = 0xC8;
        switch (gSelectedTrack[0]) {
        case 1:
            x = 0x9B;
            depth = 0x12C;
            break;
        case 4:
            depth = 0x12C;
            y = 0x73;
            break;
        case 10:
            x = 0xA0;
            break;
        case 7:
        case 11:
            depth = 0x12C;
            y = 0x6E;
            if (gSelectedTrack[0] != 0xB) {
                break;
            }
        case 9:
        set69:
            y = 0x69;
            break;
        case 12:
            x = 0x96;
            goto set69;
        case 14:
            depth = 0xFA;
        case 2:
        case 3:
        case 5:
        case 13:
        case 15:
            y = 0x6E;
            break;
        case 16:
            x = 0x96;
            y = 0x64;
            break;
        }
        SetGeomOffset(x, y);
        angles.vy = D_8009AFA8[gSelectedTrack[0]];
        angles.vx = 0x4B0;
        angles.vz = 0;
    } else if (cursor) {
        /* The two arms are identical: cross-jumping merges them. The copy
         * lengthens otz's live range so the allocator ranks it below i and q,
         * as in the original. */
        SetGeomOffset(D_800A3634->x, D_800A3634->y);
        angles.vy = D_800A3344;
        angles.vx = 0xC8;
        angles.vz = 0;
    } else {
        SetGeomOffset(D_800A3634->x, D_800A3634->y);
        angles.vy = D_800A3344;
        angles.vx = 0xC8;
        angles.vz = 0;
    }
    RotMatrix(&angles, &D_800A8C70);
    SetRotMatrix(&D_800A8C70);
    if (advanceSpin & 0xFF) {
        if (depth) { /* identical arms, see above */
            D_800A3344 = (D_800A3344 + 0x10) % 0x1000;
        } else {
            D_800A3344 = (D_800A3344 + 0x10) % 0x1000;
        }
    }
    trans.vx = 0;
    trans.vy = 0;
    if (fullScreenMode & 0xFF) {
        trans.vz = depth;
    } else {
        trans.vz = 0x1C2;
    }
    TransMatrix(&D_800A8C70, &trans);
    SetTransMatrix(&D_800A8C70);
    q = (ModelQuad *)D_800A393C;
    tmpl = D_800A399C[0];
    for (i = 0; i < D_800A38DC; i++) {
        gte_ldv3c(&q->v[0]);
        gte_rtpt();
        if ((semiTrans & 0xFF) == 0) {
            SetSemiTrans(tmpl, q->v[3].pad);
        } else {
            SetSemiTrans(tmpl, 1);
        }
        gte_avsz3();
        /* mfc2 otz, $7: the average Z from avsz3. */
        otz = PortGteRead(7);
        if (q->v[3].pad != 0) {
            otz += 0x10;
        }
        if (q->v[0].pad == 0 && q->v[1].pad == 0x46 && q->v[2].pad == 0x9A) {
            if (fullScreenMode & 0xFF) {
                continue;
            }
            otz -= 0x20;
        }
        if (otz < 0) {
            otz = 0;
        }
        gte_stsxy3((u8 *)tmpl + 8, (u8 *)tmpl + 0xC, (u8 *)tmpl + 0x10);
        gte_ldv0(&q->v[3]);
        gte_rtps();
        gte_stsxy((u8 *)tmpl + 0x14);
        *cursor = *tmpl;
        AddPrim((u8 *)ot + ((otz >> 2) << 2), cursor);
        q++;
        tmpl++;
        cursor++;
    }
    gPrimitiveCursor[0] = (u32)cursor;
}
