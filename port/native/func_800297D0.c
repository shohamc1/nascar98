void func_800297D0(Car *car) {
    /* Called without its car argument; a0 still holds it. */
    extern void func_80031264NoArgs(Car *) asm("func_80031264");
    extern void func_800294A8(void *);
    extern s32 CarHandleWallCollision(Car *);
    extern s32 D_800A2EC8NM[] __asm__("D_800A2EC8");

    func_80031264NoArgs(car);
    car->unk375 = 1;
    func_800294A8(car);
    if (gSessionTypeAbsolute[0] <= 0) {
        if (func_80025A38(car) != 0) {
            car->segment = TrackFindSectionForward(car->pos.x, car->pos.y,
                                                   &car->regionIndex);
        }
    }
    if (car->collisionPending != 0 || car->segment == -1) {
        SoundPlaySlotAtVolume(car, 7, 8);
        if (*(s32 *)&car->callback == (s32)func_80025730 &&
            D_800A2EC8NM[0] == 0) {
            car->pos.x = car->unkC;
            car->pos.y = car->unk10;
            car->pos.z = car->unk14;
            car->speed = car->speed / 2;
            car->movementHeading = ((u16)car->movementHeading + 0x200) & 0x3FF;
        }
        CarHandleWallCollision(car);
        car->collisionPending = 0;
        car->unk375 = 0;
    }
}
