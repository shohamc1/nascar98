void SceneInitRoadStrip(void) {
    u8 first[2];
    SVECTOR rotation;
    VECTOR result;
    long flag;
    s8 slot;
    u16 nextSection;
    s32 slotIndex;
    s8 **base;
    u8 *firstSlot;
    u8 *firstBase;
    u16 section;
    s32 sectionIndex;
    s8 index;
    s8 *(*quadSlots)[];
    s8 side;
    register s8 otherSide;
    TrackSection *node;
    SceneRoadQuad *quad;
    register s32 *origin;
    s32 row;
    register s16 x;
    s16 y;
    s32 z;
    Car *car;
    register s16 *sectionPtr;
    register s16 *sectionBase;
    s32 lookBehind;
    s32 sectionPosition;
    s32 count;

    do {
        quadSlots = &D_800A3444;
    } while (0);

    first[0] = 1;
    first[1] = 1;
    PushMatrix();
    slot = 0;
    if (D_800A3424 != 0) {
        firstBase = first;
        origin = D_800AE844;
        do {
            sectionBase = D_800A3440;
            sectionPtr = sectionBase + slot;
            if (slot != 0) {
                car = D_800A3428View;
            } else {
                car = gPlayerCar[0];
            }
            section = (u16)car->segment;
            lookBehind = D_800A3438;
            *sectionPtr = section;
            sectionPosition =
                ((s16)section + lookBehind - 1) % gTrackSectionCount[0];
            count = D_800A343C;
            node = gTrackSections[0] + sectionPosition;
            index = 0;
            if (count > 0) {
                s32 slotBits;
                s32 slotOffset;

                slotBits = (u32)(u8)slot << 24;
                slotIndex = slotBits >> 24;
                slotOffset = slotIndex * 4;
                /* la base, D_800A3444 */
                base = (s8 **)D_800A3444;
                /* Unsigned negation preserves the address-add operand order. */
                base = (s8 **)(slotOffset - -(u32)base);
                firstSlot = firstBase + slotIndex;
                do {
                    s32 sectionValue;
                    register s8 *quadBase;
                    TrackSection *nodes;
                    SVECTOR *rotationPtr;
                    TrackSection *previousNode;

                    previousNode = node->prev;
                    section = node->section;
                    nextSection = previousNode->section;
                    quadBase = *base;
                    rotation.vx = 0;
                    rotationPtr = &rotation;
                    nodes = gTrackSections[0];
                    sectionValue = (s16)section;
                    rotation.vy = nodes[sectionValue].angle * 4;
                    sectionIndex = sectionValue;
                    quad = (SceneRoadQuad *)quadBase + index;
                    rotation.vz = 0;
                    RotMatrix(rotationPtr, D_800992FC);
                    SetRotMatrix(D_800992FC);
                    SetTransMatrix(D_800992FC);
                    side = 0;
                    rotation.vy = 0;
                    row = slotIndex * 12;
                sideLoop:
                    {
                        otherSide = side + 2;
                        rotation.vx = side ? -150 : 150;
                        RotTrans(&rotation, &result, &flag);
                        if (*firstSlot != 0) {
                            register u8 *firstPoint;
                            register SceneRoadPoint *firstCache;
                            s32 cameraZ;

                            x = (D_800AE15C[0][sectionIndex].x + result.vz >>
                                 2) -
                                origin[0];
                            firstPoint = (u8 *)quad + side * sizeof(SVECTOR);
                            firstCache = (SceneRoadPoint *)((u8 *)D_800A45C0 +
                                                            (side * 6 + row));
                            firstCache->x = x;
                            ((SVECTOR *)(firstPoint + 0x30))->vx = x;
                            y = (D_800AE15C[0][sectionIndex].y + result.vx >>
                                 2) -
                                origin[1];
                            firstCache->y = y;
                            ((SVECTOR *)(firstPoint + 0x30))->vy = y;
                            cameraZ = origin[2];
                            if (side) {
                                z = gTrackSections[0][sectionIndex].height0 -
                                    0x4000;
                            } else {
                                z = gTrackSections[0][sectionIndex].height1 -
                                    0x4000;
                            }
                            firstCache->z = (z >> 2) - cameraZ;
                            ((SVECTOR *)(firstPoint + 0x30))->vz =
                                firstCache->z =
                                    ((volatile SceneRoadPoint *)firstCache)->z;
                            if (side) {
                                *firstSlot = 0;
                            }
                        } else {
                            register u8 *oldPoint;
                            register s32 oldOffset;

                            oldOffset = side * 6 + row;
                            oldPoint = (u8 *)quad + side * sizeof(SVECTOR);
                            ((SVECTOR *)(oldPoint + 0x30))->vx =
                                *(s16 *)((u8 *)D_800A45D8X + oldOffset);
                            ((SVECTOR *)(oldPoint + 0x30))->vy =
                                *(s16 *)((u8 *)D_800A45DA + oldOffset);
                            ((SVECTOR *)(oldPoint + 0x30))->vz =
                                *(s16 *)((u8 *)D_800A45DC + oldOffset);
                        }
                        {
                            register u8 *nextPoint;
                            register SceneRoadPoint *nextCache;
                            s32 cacheOffset;
                            s32 cameraZ;
                            s32 nextSectionIndex;

                            nextSectionIndex = (s16)nextSection;
                            x = (D_800AE15C[0][nextSectionIndex].x +
                                     result.vz >>
                                 2) -
                                origin[0];
                            cacheOffset = side * 6 + row;
                            asm("" : "=r"(cacheOffset) : "0"(cacheOffset), "r"(x));
                            nextCache = (SceneRoadPoint *)((u8 *)D_800A45D8 +
                                                           cacheOffset);
                            asm("" : "=r"(nextCache) : "0"(nextCache));
                            nextPoint =
                                (u8 *)quad + otherSide * sizeof(SVECTOR);
                            nextCache->x = x;
                            ((SVECTOR *)(nextPoint + 0x30))->vx = x;
                            y = (D_800AE15C[0][nextSectionIndex].y +
                                     result.vx >>
                                 2) -
                                origin[1];
                            nextCache->y = y;
                            ((SVECTOR *)(nextPoint + 0x30))->vy = y;
                            cameraZ = origin[2];
                            if (side) {
                                z = gTrackSections[0][nextSectionIndex]
                                        .height0 -
                                    0x4000;
                            } else {
                                z = gTrackSections[0][nextSectionIndex]
                                        .height1 -
                                    0x4000;
                            }
                            nextCache->z = (z >> 2) - cameraZ;
                            ((SVECTOR *)(nextPoint + 0x30))->vz = nextCache->z =
                                ((volatile SceneRoadPoint *)nextCache)->z;
                        }
                        asm("" : : "r"(node), "r"(index), "r"(section));
                        side++;
                    }
                    if (side < 2) {
                        goto sideLoop;
                    }
                    {
                        s32 previous;
                        register s32 following;
                        s32 currentIndex;
                        s32 last;
                        s8 *previousBase;

                        count = D_800A343C;
                        currentIndex = index;
                        last = count - 1;
                        previous = (currentIndex + last) % count;
                        following = (currentIndex + 1) % count;
                        quad->next = (SceneRoadQuad *)*base + previous;
                        previousBase = *base;
                        index++;
                        quad->section = section;
                        quad->prev = (SceneRoadQuad *)previousBase + following;
                    }
                    node = node->prev;
                } while (index < count);
            }
            {
                s32 tailCount;
                s32 endOffset;

                asm("" : : "r"((u8)slot), "r"(quadSlots) : "memory");
                tailCount = D_800A343C;
                D_800A344C[slot] = (SceneRoadQuad *)(*quadSlots)[slot];
                endOffset = tailCount * 0x58 - 0x58;
                D_800A3454[slot] =
                    (SceneRoadQuad *)((u8 *)(*quadSlots)[slot] + endOffset);
                slot++;
            }
        } while (slot < D_800A3424);
    }
    PopMatrix();
}
