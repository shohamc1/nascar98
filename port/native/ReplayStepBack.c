/* The matching C drops func_800442C8's frame; the asm leaves it in a1. */
void ReplayStepBack(void) {
    Car *node;
    register u8 *rec;
    u8 *p;
    s32 current;
    s32 count;
    u8 *baseAddr;
    s32 offset;
    u32 bits;
    u32 w2;
    s32 d;
    s32 dm1;
    register u16 val;
    s32 v90;
    s32 t114;
    s32 i;

    current = gReplayIndexSmall;
    if (current != D_800A3804Small) {
        d = gReplayLengthSmall;
        dm1 = d - 1;
        gReplayIndexSmall = (current + dm1) % d;
    } else {
        D_800A2ED4[0] = 1;
        SoundStopConditionalSlots(0);
    }
    count = gReplayIndexSmall * (D_800A2E94[0] + 6);
    node = gCarListw15[0];
    if (node != 0) {
        offset = count * 20;
        do {
            if (node->type >= 0) {
                rec = (u8 *)gReplayBufferSmall;
                rec = (u8 *)(offset + (s32)rec);
                node->pos.x = ((ReplayFrame *)rec)->x;
                node->pos.y = ((ReplayFrame *)rec)->y;
                func_800442C8(node, (ReplayFrame *)rec);
                val = *(u16 *)(u8 *)(offset + gReplayBufferSmall + 0xE);
                node->reverseSpeed = val & 0x7F;
                baseAddr = (u8 *)gReplayBufferSmall;
                v90 = (val >> 7) << 17;
                node->speed = v90;
                bits = *(s32 *)(u8 *)(offset + (s32)baseAddr + 8);
                node->fineHeading = (bits >> 22) * 4;
                val = bits >> 22;
                node->steering = ((bits >> 14) & 0xFF) - 0x80;
                node->gearIndex = (bits & 0x3F) >> 4;
                node->unk3B9 = (bits & 0xF) >> 3;
                node->sliding = (bits & 7) >> 2;
                node->unk102 = val;
                node->heading = val;
                if ((bits & 3) == 1) {
                    D_800A3960w15[0] = gPlayerCar[0];
                } else if ((bits & 3) == 2) {
                    D_800A3960w15[0] = gPlayerCar[0]->next;
                } else {
                    D_800A3960w15[0] = 0;
                }
                w2 = *(s32 *)(u8 *)(offset + gReplayBufferSmall + 0x10);
                node->unkFE = ((w2 >> 20) - 0x800) * 2;
                for (i = 0; i < 4; i++) {
                    node->wheel[i].unk0 = (u16)node->unkFE;
                }
                t114 = node->heading;
                node->unk388 = (w2 << 12) >> 22;
                node->unk38A = w2 & 0x3FF;
                func_8001F2C4(t114, 0, 0);
                func_8001F828((s32 *)node);
                MatrixStoreObjectBasis(node);
                node->unk228 = 0;
                node->movementHeading = (u16)node->heading;
                CarUpdateEngineRpm(node);
                offset += 0x14;
                count += 1;
            }
            node = node->next;
        } while (node != 0);
    }
    func_8003667C((u8 *)gReplayBufferSmall + count * 20);
    ReplayReadEffects((u8 *)gReplayBufferSmall + (count * 20 + 0x50));
}
