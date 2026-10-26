void HudUpdateTrafficGapData(void) {
    register s32 len;
    register Car *car;
    Car *e0;
    register s32 prod2;
    s32 prod1;
    s32 refDist;
    s32 rel;
    s32 e01d6;
    s32 car1d6;
    s32 e0dist;
    s32 cardist;
    s32 other1d6;
    s32 otherdist;
    char *name2;
    s32 t1;
    s32 t2;

    e0 = (u8 *)D_800A35E0[0];
    len = gTrackSectionCount[0];
    e01d6 = e0->lap;
    /* mult e01d6, len: mflo below reads the product. */
    car = gPlayerCar[0];
    car1d6 = car->lap;
    prod1 = e01d6 * len; /* mflo */
    /* mult car1d6, len: mflo below reads the product. */
    e0dist = e0->segment;
    cardist = car->segment;
    D_800A34C0 = 0; /* sw $zero, %gp_rel(D_800A34C0)($gp) */
    D_800A34BC = 0; /* sw $zero, %gp_rel(D_800A34BC)($gp) */
    refDist = prod1 + e0dist;
    prod2 = car1d6 * len; /* mflo */
    cardist = (u32)prod2 - -(u32)cardist;
    if (refDist - cardist < len) {
        if (car->place >= 2) {
            e0 = (u8 *)((CarLink *)car->order.node.next)->car;
            t1 = car->unk264;
            t2 = e0->unk264;
            car = (Car *)e0->name;
            D_800A34BC = t1 - t2;
            strcpy(D_800A8A4C, (char *)car);
            D_800A34B4 = (s32)strtok(D_800A8A4C, gTextSpaceDelimiter);
            D_800A34B4 = (s32)strtok((char *)0, gTextSpaceDelimiter);
        }
        asm volatile("" : : : "memory");
        if (*(s32 *)&gPlayerCar[0]->order.node.previous != 0) {
            e0 = (u8 *)((CarLink *)gPlayerCar[0]->order.node.previous)->car;
            len = gTrackSectionCount[0];
            other1d6 = e0->lap;
            /* mult other1d6, len: mflo below reads the product. */
            otherdist = e0->segment;
            otherdist = other1d6 * len + otherdist; /* mflo $7; addu */
            if (refDist - otherdist < len) {
                rel = e0->unk264;
                if (gPlayerCar[0]->place != 1) {
                    rel -= gPlayerCar[0]->unk264;
                }
                name2 = e0->name;
                D_800A34C0 = rel;
                strcpy(D_800A8A60, name2);
                D_800A34B8 = (s32)strtok(D_800A8A60, gTextSpaceDelimiter);
                D_800A34B8 = (s32)strtok((char *)0, gTextSpaceDelimiter);
            }
        }
    }
}
