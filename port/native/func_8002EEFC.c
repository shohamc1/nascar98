void func_8002EEFC(Car *arg0) {
    s32 refX;
    s32 refY;
    s32 refZ;
    s32 level;
    s32 lod;
    Car *node;
    s32 dist;
    s32 delta;
    s32 ySq;
    s32 zSq;

    refX = ((Car *)D_800A38AC[0])->pos.x;
    refY = ((Car *)D_800A38AC[0])->pos.y;
    refZ = ((Car *)D_800A38AC[0])->pos.z;
    node = gCarList;
    if (node == NULL) {
        return;
    }
    level = 4;
    do {
        if (node == arg0 && node->type == 0 && D_800A2ED8 == 0 &&
            node->cameraMode == 0) {
            node->unk374 = level;
            node->model = (Model *)(*(u32 *)&node->shape + 0x110);
        } else {
            delta = node->pos.x;
            dist = delta - refX;
            dist = dist * dist;
            delta = node->pos.y;
            delta = delta - refY;
            ySq = delta * delta;
            delta = node->pos.z;
            delta = delta - refZ;
            zSq = delta * delta;
            dist = dist + ySq;
            dist = MathSqrt(dist + zSq);
            if (dist < 0x7D0) {
                node->unk374 = 0;
            } else if (dist < 0x1770) {
                node->unk374 = 1;
            } else if (dist < 0x2EE0) {
                node->unk374 = 2;
            } else {
                node->unk374 = 3;
            }
            if (D_800A2ED8 != 0) {
                if ((s8)node->unk374 < 3) {
                    node->unk374++; /* s8 field: the lvalue cast is its own width */
                }
            }
            if (node->mode == level) {
                node->unk374 = 0;
            }
            if (node == arg0) {
                node->unk374 = 0;
            }
            lod = (s8)node->unk374;
            node->model = (Model *)(*(u32 *)&node->shape + (lod * 0x44));
        }
        node = node->next;
    } while (node != NULL);
}
