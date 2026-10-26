void GraphicsDrawRaceViews(void) {
    MATRIX rotation;
    Car *drawCar;
    s32 bank;
    Car *mainCamera;
    Car *secondCamera;
    Car *insetCamera;
    s32 secondTable;
    s32 tableOffset;
    s32 ticks;
    s32 bankAfterDraw;
    s32 bankAfterInset;
    Car *car;
    Car *insetCar;
    Car *focusCar;

    focusCar = gPlayerCarFrame[0];
    func_8002FFB8(1);
    if (D_800A2EDAFrame != 0) {
        focusCar = D_800A2E9CFrame;
        if (D_800A2EC0Frame >= 0x349) {
            if ((focusCar->cameraMode) != 5) {
                (focusCar->cameraAngle) =
                    (s32)(((focusCar->heading) + 0x200) & 0x3FF);
            }
            (focusCar->cameraMode) = 5;
        } else if (D_800A2EC0Frame >= 0x169) {
            (focusCar->cameraMode) = 3;
        }
        if (D_800A2EC0Frame == ((D_800A2EC0Frame / 120) * 0x78)) {
            if (RandomScaledGet(0x18) < 0) {
                D_800A2E9CFrame =
                    (Car *)(D_800A3984Frame[0] +
                            ((-RandomScaledGet(0x18) + 1) * 0x500));
            } else {
                D_800A2E9CFrame =
                    (Car *)(D_800A3984Frame[0] +
                            ((RandomScaledGet(0x18) + 1) * 0x500));
            }
        }
    }
    ticks = GetRCnt(RCntCNT1);
    D_800A2EA0Frame = focusCar;
    D_800B9D54Frame[0] = ticks - D_800B9D54Frame[0];
    mainCamera = D_800A38ACFrame1[0];
    if (focusCar != mainCamera) {
        mainCamera->segment = (u16)focusCar->segment; /* s16 field, u16 lvalue cast */
    } else {
        (*(u16 *)&((Car *)D_800A38ACFrame2[0])->segment) =
            TrackFindSectionForward((focusCar->pos.x), (focusCar->pos.y),
                                    &focusCar->regionIndex);
    }
    MatrixSetIdentity((s32 *)D_800A38ACFrame3[0]);
    if (D_800A2ED8Frame != 0) {
        CameraUpdateForCar((Car *)D_800A38ACFrameCam1A[0], focusCar,
                           D_800A2EC4Frame + 4);
    } else {
        CameraUpdateForCar((Car *)D_800A38ACFrameCam1B[0], focusCar,
                           focusCar->cameraMode);
    }
    MatrixLoadObjectBasis((s32 *)D_800A38ACFrame5[0]);
    MatrixBuildRotationFromTransform((s32 *)D_800A38ACFrame6[0],
                                     (s32 *)&rotation);
    rotation.t[2] = 0;
    rotation.t[1] = 0;
    rotation.t[0] = 0;
    SetTransMatrix(&rotation);
    SetRotMatrix(&rotation);
    func_8002EEFC(focusCar);
    CameraUpdateHorizon();
    D_800A37B0Frame = D_800A2E98Frame;
    D_800A2EBCFrame = 0;
    if (D_800A3075Frame[0] != 0) {
        D_800A2F08Frame = 0x352;
    } else {
        D_800A2F08Frame = 0x44C;
    }
    D_800A2E98Frame = 0;
    if (gSplitScreenModeFrame == 2) {
        D_800A2F0CFrame = 0x4E2;
        D_800A2F10Frame = 0x44C;
        D_800A2F08Frame = (D_800A2F08Frame * 0x46) / 100;
        SetGeomScreen(0xD0);
        D_800A2E8CFrame = 0x23;
        GraphicsSetGeomOffsetForMode(gOrderingTableBankFrame1[0] == 0, 0);
        D_800A2F3CFrame1[0] = 0x46;
        SceneDrawView(gPlayerCarFrame[0]);
        car = D_800A3558Frame[0];
        if (car != NULL) {
            do {
                if ((car->type) >= 0) {
                    (car->unk1E2) = (u16)((u16)car->unk1E6);
                    (car->unk1E4) = (u16)((u16)car->unk1E8);
                }
                car = ((u8 *)car->next);
            } while (car != NULL);
        }
        focusCar = gPlayerCarFrame[0]->next;
        D_800A2F0CFrame = 0xA28;
        D_800A2F10Frame = 0x992;
        D_800A2ED9Frame = 1;
        D_800A2EA0Frame = focusCar;
        secondCamera = D_800A38ACFrame7[0];
        if (focusCar != secondCamera) {
            secondCamera->segment = (u16)focusCar->segment; /* s16 field, u16 lvalue cast */
        } else {
            (*(u16 *)&((Car *)D_800A38ACFrame8[0])->segment) =
                TrackFindSectionForward((focusCar->pos.x), (focusCar->pos.y),
                                        &focusCar->regionIndex);
        }
        MatrixSetIdentity((s32 *)D_800A38ACFrame9[0]);
        if (D_800A2ED8Frame != 0) {
            CameraUpdateForCar((Car *)D_800A38ACFrameCam2A[0], focusCar,
                               D_800A2EC4Frame + 4);
        } else {
            CameraUpdateForCar((Car *)D_800A38ACFrameCam2B[0], focusCar,
                               focusCar->cameraMode);
        }
        MatrixLoadObjectBasis((s32 *)D_800A38ACFrame11[0]);
        MatrixBuildRotationFromTransform((s32 *)D_800A38ACFrame12[0],
                                         (s32 *)&rotation);
        rotation.t[2] = 0;
        rotation.t[1] = 0;
        rotation.t[0] = 0;
        SetTransMatrix(&rotation);
        SetRotMatrix(&rotation);
        func_8002EEFC(focusCar);
        GraphicsSetGeomOffsetForMode(gOrderingTableBankFrame2[0] == 0, 1);
        drawCar = (Car *)gPlayerCarFrame[0]->next;
        bank = gOrderingTableBankFrame3Read[0] + 1;
        secondTable = gOrderingTableFrame1[0] + 0x1000;
        D_800A2F3CFrame2[0] = 0x3C;
        gOrderingTableBankFrame3[0] = bank;
        gOrderingTableFrame2[0] = secondTable;
        SceneDrawView(drawCar);
        D_800A2ED9Frame = 0;
        bankAfterDraw = gOrderingTableBankFrame4[0] - 1;
        gOrderingTableBankFrame5[0] = bankAfterDraw;
        gOrderingTableFrame3[0] = gOrderingTableFrame3Read[0] - 0x1000;
        GraphicsSetGeomOffsetForMode(bankAfterDraw == 0, 2);
        D_800A2F3CFrame3[0] = 0x46;
    } else if ((D_800A2EC4Frame != 0) && (D_800A2EC8Frame == 0)) {
        D_800A2F10Frame = 0x578;
        D_800A2F0CFrame = 0x708;
        D_800A2F08Frame = (D_800A2F08Frame * 0x41) / 100;
        SetGeomScreen(0xD0);
        D_800A2E8CFrame = 0x23;
        GraphicsSetGeomOffsetForMode(gOrderingTableBankFrame6[0] == 0, 3);
        D_800A2F3CFrame4[0] = 0x82;
        SceneDrawView(gPlayerCarFrame[0]);
        insetCar = D_800A3558Frame[0];
        if (insetCar != NULL) {
            do {
                if ((insetCar->type) >= 0) {
                    (insetCar->unk1E2) = (u16)((u16)insetCar->unk1E6);
                    (insetCar->unk1E4) = (u16)((u16)insetCar->unk1E8);
                }
                insetCar = ((u8 *)insetCar->next);
            } while (insetCar != NULL);
        }
        D_800A2ED8Frame = 1;
        SetGeomScreen(0x64);
        D_800A2E8CFrame = 0xA;
        GraphicsSetGeomOffsetForMode(gOrderingTableBankFrame7[0] == 0, 4);
        D_800A2F3CFrame5[0] = 0x1E;
        D_800A2F0CFrame = 0xA28;
        D_800A2F10Frame = 0x9C4;
        D_800A2F08Frame = (D_800A2F08Frame * 0x23) / 100;
        func_8002F674();
        focusCar = D_800A2E9CFrame;
        D_800A2EA0Frame = focusCar;
        insetCamera = D_800A38ACFrame13[0];
        if (focusCar != insetCamera) {
            insetCamera->segment = (u16)focusCar->segment; /* s16 field, u16 lvalue cast */
        } else {
            (*(u16 *)&((Car *)D_800A38ACFrame14[0])->segment) =
                TrackFindSectionForward((focusCar->pos.x), (focusCar->pos.y),
                                        &focusCar->regionIndex);
        }
        MatrixSetIdentity((s32 *)D_800A38ACFrame15[0]);
        if (D_800A2ED8Frame != 0) {
            CameraUpdateForCar((Car *)D_800A38ACFrameCam3A[0], focusCar,
                               D_800A2EC4Frame + 4);
        } else {
            CameraUpdateForCar((Car *)D_800A38ACFrameCam3B[0], focusCar,
                               focusCar->cameraMode);
        }
        MatrixLoadObjectBasis((s32 *)D_800A38ACFrame17[0]);
        MatrixBuildRotationFromTransform((s32 *)D_800A38ACFrame18[0],
                                         (s32 *)&rotation);
        rotation.t[2] = 0;
        rotation.t[1] = 0;
        rotation.t[0] = 0;
        SetTransMatrix(&rotation);
        SetRotMatrix(&rotation);
        func_8002EEFC(focusCar);
        gOrderingTableBankFrame8[0] = gOrderingTableBankFrame8Read[0] + 1;
        gOrderingTableFrame4[0] = gOrderingTableFrame4Read[0] + 0x1000;
        func_8002FFB8(1);
        SceneDrawView(D_800A2E9CFrame);
        bankAfterInset = gOrderingTableBankFrame9[0] - 1;
        gOrderingTableBankFrame10[0] = bankAfterInset;
        gOrderingTableFrame5[0] = gOrderingTableFrame5Read[0] - 0x1000;
        GraphicsSetGeomOffsetForMode(bankAfterInset == 0, 3);
        D_800A2F3CFrame6[0] = 0x82;
        D_800A2ED8Frame = 0;
    } else {
        D_800A2F0CFrame = 0xA28;
        D_800A2F10Frame = 0x898;
        SetGeomScreen(0xD0);
        D_800A2F3CFrame7[0] = 0x82;
        D_800A2E8CFrame = D_800A3774Frame + 0x32;
        tableOffset = gOrderingTableFrame6[0] + 0x28;
        gOrderingTableFrame7[0] = tableOffset;
        SceneDrawView(focusCar);
        gOrderingTableFrame8[0] = gOrderingTableFrame8Read[0] - 0x28;
    }
    D_800B9D5CFrame[0] = GetRCnt(RCntCNT1) - D_800B9D5CFrame[0];
}
