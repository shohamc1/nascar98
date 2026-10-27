void func_80053D40(void) {
    s32 newPad[2];
    s32 oldPad[2];
    u8 playerUnlockSteps[2];
    s32 one;
    s32 two;
    s32 mode13;
    u8 exitLoop;
    u8 displayPhase;
    s32 idleFrames;
    s32 animationStartX;
    s32 animationEndX;
    s32 animationStepX;
    s32 animationReverseStepX;
    s32 *previousPadCursor;
    register s32 *currentPadCursor;
    s32 argument0;
    s32 menuPhase;
    s32 animateX;
    s32 animateY;
    s32 animateStep;
    register MenuObj **animationNodeSlot;
    s32 padBits;
    s32 previousPadInverse;
    s32 nextIdleFrames;
    s32 cardMenuCode;
    s32 nextBufferIndex;
    s32 padBits0;
    s32 playerPadBits;
    s32 sequenceValue;
    s32 unlockPhase;
    s32 itemUp;
    s32 itemDown;
    s32 cardOperation;
    s32 menuDirection;
    s32 activePlayer;
    s32 index;
    s32 player;
    s32 screenResult;
    register s32 unlockStep;
    s32 unlockDirectionBits;
    s32 dialogScreen;
    s32 actionSound;
    s32 returnChannel;
    u32 *orderingTable;
    u8 *screenTable;
    register u8 *sequenceCursor;
    u8 *selectionCursor;
    s32 screenResultByte;
    u8 pulseTick;
    u8 transitionPhase;
    u8 nextItemUp;
    u8 nextItemDown;
    u8 nextScreen;
    u8 pulsePhase;
    u8 selection;
    u8 currentSelection;
    u8 sequencePhase;
    u8 itemCursorUp;
    u8 itemCursorDown;
    u8 secondPlayerEnabled;
    u8 menuCode;
    s32 wrappedItemUp;

    playerUnlockSteps[0] = 0;
    playerUnlockSteps[1] = 0;
    MenuObjResetPoolMainLoop();
    func_8005DAD4MainLoop();
    func_8005DFA0MainLoop();
    idleFrames = 0;
    if ((u8)gSelectedTrackMainLoop < 0x11U) {
        screenTable = D_800AE178MainLoopSite1[gSelectedTrackMainLoop];
    } else {
        screenTable = *D_800AE178MainLoopSite2;
    }
    activePlayer = 0;
    func_8005E4A4MainLoop(screenTable);
    one = 1;
    two = 2;
    D_800A3608MainLoop = 0;
    exitLoop = 0;
    do {
        {
            s32 randomScale;
            /* The original call retains the incoming a0 and ignores the result. */
            asm("" : "=r"(randomScale));
            RandomScaledGetMainLoop(randomScale);
        }
        func_80057DE8MainLoop();
        func_80057E10MainLoop();
        MenuObjRestorePoolCursorMainLoop();
        argument0 = gScreenStateMainLoop;
        asm("" : "=r"(argument0) : "0"(argument0));
        if (argument0 == 0xFC) {
            PadResetAndInitializeBuffersMainLoop(0);
            func_8006DA40MainLoop();
            D_800A3928MainLoop = 0;
        } else if (argument0 == 9) {
            if (*D_800A3A58MainLoopSite3 == 0) {
                CardEnableAndTestEventsMainLoop();
                if (CardResolveSlotMainLoop() & 0xFF) {
                    CardLoadSaveTableMainLoop(0);
                }
                CardTestAndDisableEventsMainLoop();
            }
            CardMenuCreateRecordTableMainLoop((s32)gSelectedTrackMainLoop);
        } else if (argument0 == 0xA) {
            func_80068CE4MainLoop();
        } else if (argument0 == 0xC) {
            CardMenuCreateStandingsTableMainLoop();
        } else if (argument0 == 0xE) {
            func_80064208MainLoop();
        } else if ((u32)(gScreenStateMainLoop - 0x10) < 2U) {
            func_800697ECMainLoop(argument0 - 0x10);
        } else {
            func_80056C84MainLoop(argument0, activePlayer);
            func_8005C124MainLoop(gScreenStateMainLoop, D_800A3059MainLoop);
        }
        MenuCreateItemRowMainLoop(gScreenStateMainLoop);
        func_80056F04MainLoop((s32)gScreenStateMainLoop);
        switch (gScreenStateMainLoop) {
        case 0:
            idleFrames = 0;
            goto initializePads;
        case 7:
            secondPlayerEnabled = 0;
            argument0 = activePlayer & 0xFF;
            if (((D_800A3950MainLoop == 0xFB) || (D_800A3950MainLoop == 3)) &&
                (D_800A3644MainLoop != 0)) {
                secondPlayerEnabled = 1;
            }
            func_8005ED74MainLoop(argument0, secondPlayerEnabled);
            /* End the old register lifetime before setting the pad index. */
            asm volatile("" : "=r"(index));
            index = 0;
            if (D_800A3950MainLoop == 0xFB) {
            case 1:
                index = 0;
                CardMenuBuildFileListMainLoop();
                currentPadCursor = &newPad[0];
            } else {
                goto resetPadArray;
            }
            break;
        case 2:
        case 8:
            index = 0;
            D_800A3980MainLoop =
                DriverFindIndexByIdMainLoop(gPlayerDriverMainLoop);
            D_800A3981MainLoopSite5[0] =
                DriverFindIndexByIdMainLoop(D_800A36E1MainLoopSite4[0]);
            currentPadCursor = &newPad[0];
            break;
        case 5:
            index = 0;
            func_800606D4MainLoop();
            func_80063180MainLoop((s32)D_800A3076MainLoop);
            currentPadCursor = &newPad[0];
            break;
        case 13:
            func_80060FD8MainLoop();
            /* End the old register lifetime before setting the pad index. */
            asm volatile("" : "=r"(index));
            D_800A3684MainLoopSmall = 0;
            index = 0;
            if (D_800A3644MainLoop != 0) {
                *D_800A3685MainLoopSite6 = 0;
            } else {
                *D_800A3685MainLoopSite7 = two;
            }
            goto resetPadArray;
        case 3:
        case 6:
            RaceBuildQualifyingGridMainLoop(gSelectedTrackMainLoop);
        default:
        initializePads:
            index = 0;
        resetPadArray:
            /* Keep pointer setup in the common reset path. */
            asm volatile("" : "=r"(currentPadCursor));
            currentPadCursor = &newPad[0];
            break;
        }
        previousPadCursor = &oldPad[0];
    readInitialPads:
        InputGetPadButtonsMainLoop(index & 0xFF, previousPadCursor);
        *currentPadCursor = 0;
        currentPadCursor++;
        index += 1;
        previousPadCursor++;
        if (index < 2) {
            goto readInitialPads;
        }
        screenResult = 0;
        D_800A305CMainLoop = 0;
        unlockStep = 0;
        if (gScreenStateMainLoop == 0xC) {
            displayPhase = 0;
        } else {
            displayPhase = 0xFF;
            SetDispMaskMainLoop(1);
        }
        if (!(screenResult & 0xFF)) {
            mode13 = 13;
            do {
                CdStopIfPlaybackChangedMainLoop();
                nextIdleFrames = idleFrames + 1;
                idleFrames = nextIdleFrames;
                if ((gScreenStateMainLoop == 0) && (nextIdleFrames >= 0x709)) {
                    screenResult = 1;
                    gScreenStateMainLoop = 0xFD;
                }
                pulseTick = D_800A3724MainLoop - 1;
                D_800A3724MainLoop = pulseTick;
                if (!(pulseTick & 0xFF)) {
                    pulsePhase = D_800A305AMainLoop + 1;
                    D_800A305AMainLoop = pulsePhase;
                    if ((u32)(pulsePhase & 0xFF) >= 0x15U) {
                        D_800A305AMainLoop = 0;
                    }
                    {
                        register s32 pulseValue;
                        s32 magnitude;
                        s32 intensity;
                        pulseValue = D_800A305AMainLoop;
                        /* Intensity is 64 + 8 * abs(pulseValue - 10), modulo 256. */
                        /* addiu; bgez with sll in the delay slot; ori; subu; sll; addiu; andi */
                        magnitude = pulseValue - 10;
                        if (magnitude < 0) {
                            magnitude = 10 - pulseValue;
                        }
                        magnitude = magnitude * 8 + 64;
                        intensity = magnitude & 255;
                        MenuSetShadeColorsMainLoop(intensity, intensity, 0x19U);
                    }
                    D_800A3724MainLoop = 3;
                }
                nextBufferIndex = D_800A305CMainLoop == 0;
                orderingTable =
                    (nextBufferIndex << 0xC) + gOrderingTablesMainLoopSite8;
                D_800A305CMainLoop = nextBufferIndex;
                gOrderingTableBankMainLoopSite9[0] = nextBufferIndex;
                gOrderingTableMainLoopSite10[0] = orderingTable;
                ClearOTagRMainLoop(orderingTable, 0x400);
                GraphicsSelectPrimitiveBufferMainLoop(
                    (s32)(u8)D_800A305CMainLoop);
                func_80057DFCMainLoop();
                func_80057DD4MainLoop();
                func_80053C00MainLoop((s32)(u8)D_800A305CMainLoop,
                                      activePlayer & 0xFF);
                DrawSyncMainLoop(0);
                VSyncMainLoop(0);
                GraphicsPutCurrentEnvironmentsMainLoop();
                if (displayPhase == one) {
                    SetDispMaskMainLoop(1);
                    displayPhase = 2;
                }
                D_800A3710MainLoop = -(D_800A305CMainLoop != 0) & 0x140;
                LoadImageMainLoop(&D_800A3710MainLoop, D_800A35F0MainLoop);
                DrawOTagMainLoop(
                    (u32 *)((u8 *)gOrderingTableMainLoopSite11[0] + 0xFFC));
                if (displayPhase == 0) {
                    displayPhase = 1;
                }
                PadResetAndInitializeBuffersMainLoop(0);
                if (newPad[0] != 0) {
                    idleFrames = 0;
                }
                if (gScreenStateMainLoop == 5) {
                    padBits0 = func_80041B7CMainLoop(0);
                    newPad[0] = padBits0;
                    if ((padBits0 & 0x20) && (D_800A3076MainLoop == 0)) {
                        unlockPhase = unlockStep & 0xFF;
                        if (padBits0 & 0xF000) {
                            if (unlockPhase == one) {
                                goto sequenceOne;
                            }
                            if (unlockPhase < 2) {
                                unlockDirectionBits = padBits0 & 0x1000;
                                if (unlockPhase == 0) {
                                    goto advanceUnlockStep;
                                }
                                goto sequenceDone;
                            }
                            if (unlockPhase == two) {
                                goto sequenceTwo;
                            }
                            if (unlockPhase == 3) {
                                goto sequenceLast;
                            }
                            goto sequenceDone;
                        sequenceOne:
                            unlockDirectionBits = padBits0 & 0x8000;
                            goto advanceUnlockStep;
                        sequenceTwo:
                            unlockDirectionBits = padBits0 & 0x4000;
                        advanceUnlockStep:
                            if (unlockDirectionBits != 0) {
                                unlockStep++;
                            }
                            goto sequenceDone;
                        sequenceLast:
                            if (padBits0 & 0x2000) {
                                D_800A3076MainLoop = one;
                                func_80063180MainLoop(1);
                                SoundPlaySlotMainLoop(0, 8);
                                goto resetUnlockStep;
                            }
                        sequenceDone:;
                        }
                    } else {
                    resetUnlockStep:
                        unlockStep = 0;
                    }
                } else if ((gScreenStateMainLoop == two) &&
                           (D_800A3059MainLoop == one)) {
                    index = 0;
                    sequenceCursor = &playerUnlockSteps[0];
                    selectionCursor = &gPlayerDriverMainLoop;
                readPlayerUnlockSequence:
                    if ((index != one) || (D_800A3644MainLoop != 0)) {
                        selection = *selectionCursor;
                        if ((selection == 5) || (selection == two)) {
                            playerPadBits = func_80041B7CMainLoop(index);
                            (&newPad[0])[index] = playerPadBits;
                            if (playerPadBits & 0x40) {
                                if (playerPadBits & 0x5000) {
                                    sequencePhase = *sequenceCursor;
                                    sequenceValue = sequencePhase & 0xFF;
                                    if (sequenceValue == 0) {
                                        goto playerSequenceFirst;
                                    }
                                    if (sequenceValue == one) {
                                        goto playerSequenceSecond;
                                    }
                                    sequenceCursor++;
                                    goto playerSequenceNext;
                                playerSequenceFirst:
                                    if (playerPadBits & 0x1000) {
                                        *sequenceCursor = sequencePhase + 1;
                                    }
                                    goto advancePlayerUnlockSequence;
                                playerSequenceSecond:
                                    if (!(playerPadBits & 0x4000)) {
                                        goto advancePlayerUnlockSequence;
                                    }
                                    currentSelection = *selectionCursor;
                                    if (currentSelection == two) {
                                        func_80063C34MainLoop(2, 0x19);
                                        func_80063AE0MainLoop(index, 2);
                                        D_800A3065MainLoop ^= 1;
                                        *sequenceCursor = 0;
                                        goto advancePlayerUnlockSequence;
                                    }
                                    if (currentSelection == 5) {
                                        func_80063C34MainLoop(5, 0x18);
                                        func_80063AE0MainLoop(index, 5);
                                        D_800A3064MainLoop ^= 1;
                                    }
                                    goto resetPlayerUnlockSequence;
                                } else {
                                    goto advancePlayerUnlockSequence;
                                }
                            } else {
                            resetPlayerUnlockSequence:
                                *sequenceCursor = 0;
                                goto advancePlayerUnlockSequence;
                            }
                        } else {
                        advancePlayerUnlockSequence:
                            sequenceCursor += 1;
                        }
                    playerSequenceNext:
                        index += 1;
                        selectionCursor += 1;
                        if (index < 2) {
                            goto readPlayerUnlockSequence;
                        }
                    }
                }
                if ((gScreenStateMainLoop == mode13) &&
                    (D_800A3684MainLoopSmall == two) &&
                    (ListHasClearFlagsMainLoop(
                         *gPadPictureMenuListsMainLoopSite13) != 0) &&
                    ((D_800A3644MainLoop == 0) ||
                     ((*D_800A3685MainLoopSite12 == two) &&
                      (ListHasClearFlagsMainLoop(*D_800A37DCMainLoopSite14) !=
                       0)))) {
                    screenResult = 1;
                } else {
                    player = 0;
                    asm("" : "=r"(player) : "0"(player));
                    index = player & 0xFF;
                    do {
                        if ((index == 0) || (D_800A3644MainLoop != 0)) {
                            (&newPad[0])[index] = func_80041B7CMainLoop(index);
                            if ((gScreenStateMainLoop == 7) &&
                                (activePlayer == one)) {
                                if (index != 0) {
                                    newPad[0] = newPad[1];
                                    oldPad[0] = oldPad[1];
                                    goto handlePlayerInput;
                                }
                                goto nextPlayer;
                            }
                            if (player & 0xFF) {
                                if (gScreenStateMainLoop != two) {
                                    if (gScreenStateMainLoop == mode13) {
                                        goto handlePlayerInput;
                                    }
                                    goto nextPlayer;
                                }
                                goto handlePlayerSelection;
                            }
                        handlePlayerInput:
                        handlePlayerSelection:
                            if (gScreenStateMainLoop == mode13) {
                                index = player & 0xFF;
                                if (newPad[index] &
                                    ((u16)~oldPad[index] & 0x800)) {
                                    transitionPhase =
                                        D_800A3684MainLoopSite15[index];
                                    if (transitionPhase == 0) {
                                        SoundPlaySlotMainLoop(0, 3);
                                        if (PadTypeNeedsCalibrationMainLoop(
                                                (s32)(u8)gPadTypeMainLoopSite16
                                                    [index]) &
                                            0xFF) {
                                            func_80062874MainLoop(index, 1);
                                            D_800A3684MainLoopSite17[index] =
                                                one;
                                            func_8006DE68MainLoop(
                                                (u32)index,
                                                (u32)(u8)gPadTypeMainLoopSite18
                                                    [index]);
                                            func_80062F04MainLoop(
                                                index,
                                                gPadTypeMainLoopSite20[index],
                                                gPadLayoutMainLoopSite19
                                                    [index]);
                                            animationStartX = -0x140;
                                            animationNodeSlot =
                                                D_800A3888MainLoopSite21;
                                            animationNodeSlot =
                                                (MenuObj *
                                                     *)((index * 4) +
                                                        (u32)animationNodeSlot);
                                            if (index != 0) {
                                                animationStartX = 0x140;
                                            }
                                            animationStepX = 4;
                                            if (index != 0) {
                                                animationStepX = -4;
                                            }
                                            ListSetFieldsAndEnableMainLoop(
                                                *animationNodeSlot,
                                                animationStartX, 0,
                                                animationStepX);
                                        } else {
                                            func_80062874MainLoop(index, 0);
                                            D_800A3684MainLoopSite22[index] =
                                                two;
                                            goto updateSelectionPanel;
                                        }
                                    } else if (transitionPhase == one) {
                                        SoundPlaySlotMainLoop(0, 3);
                                        PadCalibrateCenterMainLoop(
                                            (u32)index,
                                            (u32)(u8)
                                                gPadTypeMainLoopSite24[index],
                                            (u32)(u8)gPadLayoutMainLoopSite23
                                                [index]);
                                        func_80062874MainLoop(index, 0);
                                        animationEndX = 0x140;
                                        animationNodeSlot =
                                            D_800A3888MainLoopSite25;
                                        animationNodeSlot =
                                            (MenuObj **)((index * 4) +
                                                         (u32)
                                                             animationNodeSlot);
                                        if (index != 0) {
                                            animationEndX = -0x140;
                                        }
                                        animationReverseStepX = -4;
                                        if (index != 0) {
                                            animationReverseStepX = 4;
                                        }
                                        ListSetFieldsAndEnableMainLoop(
                                            *animationNodeSlot, 0,
                                            animationEndX,
                                            animationReverseStepX);
                                        D_800A3684MainLoopSite26[index] = two;
                                        D_800A36E4MainLoopSite27[index] = one;
                                    updateSelectionPanel:
                                        if ((D_800A3684MainLoopSmall != 0) &&
                                            (*D_800A3685MainLoopSite28 != 0)) {
                                            ListSetFieldsAndEnableMainLoop(
                                                *D_800A37F8MainLoopSite29, 0,
                                                0x140, 4);
                                        }
                                    }
                                } else if ((PadTypeNeedsCalibrationMainLoop(
                                                (s32)(u8)gPadTypeMainLoopSite31
                                                    [index]) &
                                            0xFF) &&
                                           (D_800A3684MainLoopSite30[index] ==
                                            one)) {
                                    PadCalibrateRangeMainLoop(
                                        (u32)index,
                                        (u32)(u8)gPadTypeMainLoopSite33[index],
                                        (u32)(u8)
                                            gPadLayoutMainLoopSite32[index]);
                                }
                            }
                            {
                                register s32 previousPadZero;
                                register s32 currentPadZero;
                                /* Read both pads before forming the pressed-edge mask. */
                                /* lw; lw; nor */
                                previousPadZero = oldPad[0];
                                currentPadZero = newPad[0];
                                previousPadInverse = ~previousPadZero;
                                if (currentPadZero &
                                    ((u16)previousPadInverse & 0x40)) {
                                    s32 confirmPivot;
                                    s32 confirmMode;
                                    screenResult = func_80056B5CMainLoop(
                                        (s32)D_800A3059MainLoop,
                                        (s32)gScreenStateMainLoop,
                                        (s32)D_800A3950MainLoop);
                                    if (screenResult & 0xFF) {

                                        if ((u32)(gScreenStateMainLoop -
                                                  0x10) >= 2U) {
                                            SoundPlaySlotMainLoop(0, 3);
                                        }
                                    } else {
                                        confirmPivot = 0x24;
                                        confirmMode = gScreenStateMainLoop;
                                        if (confirmMode == confirmPivot) {
                                            goto confirmMode24;
                                        }
                                        if (confirmMode < 0x25) {
                                            if (confirmMode == 0x21) {
                                                goto confirmMode21;
                                            }
                                            if (confirmMode < 0x22) {
                                                if (confirmMode == one) {
                                                    goto confirmMode1;
                                                }
                                                if (confirmMode == 5) {
                                                    goto confirmMode5;
                                                }
                                                goto finishInput;
                                            }
                                            if (confirmMode == 0x22) {
                                                goto confirmMode22;
                                            }
                                            if (confirmMode == 0x23) {
                                                goto confirmMode23;
                                            }
                                            goto finishInput;
                                        }
                                        if (confirmMode == 0x27) {
                                            goto confirmMode25;
                                        }
                                        if (confirmMode < 0x28) {
                                            if (confirmMode == 0x25) {
                                                goto confirmMode25;
                                            }
                                            if (confirmMode == 0x26) {
                                                goto confirmMode26;
                                            }
                                            goto finishInput;
                                        }
                                        if (confirmMode == 0x28) {
                                            goto confirmMode28;
                                        }
                                        if (confirmMode != 0xFC) {
                                            goto finishInput;
                                        }
                                    confirmModeFC:
                                        {
                                            s32 exitPhase;
                                            s32 exitChannel;
                                            s32 exitTone;
                                            exitPhase = D_800A3928MainLoop;
                                            if (exitPhase == 0) {
                                                goto confirmExitStatus;
                                            }
                                            exitChannel = 0;
                                            if (exitPhase == one) {
                                                goto confirmExitSound;
                                            }
                                            goto finishInput;
                                        confirmExitStatus:
                                            exitPhase =
                                                gCardMenuMessageMainLoop[0];
                                            exitChannel = 0;
                                            if (exitPhase != mode13) {
                                                goto confirmExitSound;
                                            }
                                            exitTone = 4;
                                            goto confirmExit;
                                        confirmExitSound:
                                            exitTone = 3;
                                        confirmExit:
                                            screenResult = 1;
                                            SoundPlaySlotMainLoop(exitChannel,
                                                                  exitTone);
                                            goto finishInput;
                                        }
                                    confirmMode1:
                                        SoundPlaySlotMainLoop(0, 3);
                                        if ((D_800A3059MainLoop == two &&
                                             D_800A3950MainLoop != 0) ||
                                            D_800A3059MainLoop == one) {
                                            CardEnableAndTestEventsMainLoop();
                                            if ((CardProbeSlotsMainLoop() &
                                                 0xFF) == two) {
                                                gScreenStateMainLoop = 0x28;
                                                CardMenuCenterSelectedTextMainLoop(
                                                    5);
                                                menuCode = 1;
                                            } else {
                                                menuCode =
                                                    CardLoadNameListMainLoop(
                                                        0xFF);
                                            }
                                            func_80057008MainLoop(menuCode &
                                                                  0xFF);
                                            CardTestAndDisableEventsMainLoop();
                                            func_80057160MainLoop(1);
                                        } else if (D_800A3059MainLoop == 6) {
                                            if (D_800B9B84MainLoop[0] == 0) {
                                                screenResult = 1;
                                                goto finishInput;
                                            }
                                            CardMenuCenterSelectedTextMainLoop(
                                                2);
                                            gCardMenuMessageMainLoop[0] = 0x15;
                                            CardMenuShowMessageMainLoop(0);
                                            animateX = -0x78;
                                            animateY = 0;
                                            animateStep = 2;
                                            dialogScreen = 0x25;
                                            goto showConfirmDialog;
                                        } else if (D_800A3059MainLoop == 0 &&
                                                   D_800A3950MainLoop != 0) {
                                            CardMenuCenterSelectedTextMainLoop(
                                                4);
                                            gCardMenuMessageMainLoop[0] = 0x18;
                                            CardMenuShowMessageMainLoop(0);
                                            animateX = -0x78;
                                            animateY = 0;
                                            animateStep = 2;
                                            dialogScreen = 0x27;
                                        showConfirmDialog:
                                            gScreenStateMainLoop = dialogScreen;
                                            CardMenuSetColorNodeLayoutMainLoop(
                                                animateX, animateY,
                                                animateStep);
                                            MenuNegateLinkedObjectValuesMainLoop(
                                                0);
                                        }
                                        goto finishInput;
                                    confirmMode5:
                                        if ((u32)(D_800A3059MainLoop - 2) <
                                            2U) {
                                            SoundPlaySlotMainLoop(0, 3);
                                            if (D_800A3059MainLoop == 3) {
                                                SoundRunSlotEnvelopeMainLoop(0,
                                                                             1);
                                                func_8003CCE0MainLoop(0);
                                                D_800A2F9CMainLoop[0] = 0;
                                            }
                                            MenuCenterTextMainLoop(
                                                D_800A3059MainLoop - 2);
                                            MenuSetVolumeMainLoop(
                                                (s16)D_800A3690MainLoop
                                                    [D_800A3059MainLoop],
                                                D_800A3059MainLoop - 2);
                                            MenuSetLinkedObjectLayoutMainLoop(
                                                -0x78, 0, 2);
                                            gScreenStateMainLoop = 0x21;
                                            MenuUpdateItemRowMainLoop(0x21);
                                        }
                                        goto finishInput;
                                    confirmMode21:
                                        SoundPlaySlotMainLoop(0, 3);
                                        MenuSetLinkedObjectLayoutMainLoop(
                                            0, -0x78, -2);
                                        gScreenStateMainLoop = 5;
                                        MenuUpdateItemRowMainLoop(5);
                                        if (D_800A3059MainLoop == 3) {
                                            SoundRunSlotEnvelopeMainLoop(2, 1);
                                            CdEnablePlaybackAndSetVolumeMainLoop();
                                        }
                                        goto finishInput;
                                    confirmMode28:
                                        SoundPlaySlotMainLoop(0, 3);
                                        CardEnableAndTestEventsMainLoop();
                                        cardMenuCode = CardLoadNameListMainLoop(
                                            D_800A358CMainLoop[0]);
                                        gScreenStateMainLoop = one;
                                        func_80057008MainLoop(cardMenuCode &
                                                              0xFF);
                                        CardTestAndDisableEventsMainLoop();
                                        func_80057160MainLoop(0);
                                        goto finishInput;
                                    confirmMode22:
                                        SoundPlaySlotMainLoop(0, 3);
                                        gScreenStateMainLoop = 0x23;
                                        CardMenuAppendTrackNameMainLoop();
                                        func_8006C9F8MainLoop();
                                        gCardMenuMessageMainLoop[0] = 0;
                                        MenuUpdateItemRowMainLoop(
                                            gScreenStateMainLoop);
                                        goto finishInput;
                                    confirmMode23:
                                        {
                                            s32 scanPhase;
                                            scanPhase = D_800A3928MainLoop;
                                            returnChannel = 0;
                                            if (scanPhase == 0) {
                                                goto confirmScan;
                                            }
                                            actionSound = 3;
                                            if (scanPhase == one) {
                                                goto returnMainMenu;
                                            }
                                            goto finishInput;
                                        confirmScan:
                                            {
                                                SoundPlaySlotMainLoop(0, 3);
                                                if (func_8006D178MainLoop() ==
                                                    0) {
                                                    SoundStopSlotMainLoop(0);
                                                } else {
                                                    MenuHideCurrentObjectMainLoop();
                                                    if (gCardMenuMessageMainLoop
                                                            [0] == 0) {
                                                        if (CardMenuCheckTrackNameCapacityMainLoop() ==
                                                            one) {
                                                            goto refreshCardMenu;
                                                        }
                                                        if (gCardMenuMessageMainLoop
                                                                [0] == 0) {
                                                            goto updateCardStatus;
                                                        }
                                                    }
                                                    if (gCardMenuMessageMainLoop
                                                            [0] == 0x10) {
                                                    updateCardStatus:
                                                        CardEnableAndTestEventsMainLoop();
                                                        if (!(CardResolveSlotMainLoop() &
                                                              0xFF)) {
                                                            CardMenuShowMessageMainLoop(
                                                                0);
                                                            if (gCardMenuMessageMainLoop
                                                                    [0] !=
                                                                mode13) {
                                                                D_800A3928MainLoop =
                                                                    one;
                                                            }
                                                        }
                                                        CardTestAndDisableEventsMainLoop();
                                                        if (gCardMenuMessageMainLoop
                                                                [0] == mode13) {
                                                            goto finishInput;
                                                        }
                                                    }
                                                    if (gCardMenuMessageMainLoop
                                                            [0] == mode13) {
                                                        SoundStopSlotMainLoop(
                                                            0);
                                                        goto playBackSound;
                                                    }
                                                    goto checkCardMenuReady;
                                                }
                                            }
                                            goto finishInput;
                                        }
                                    confirmMode24:
                                        SoundPlaySlotMainLoop(0, 3);
                                        menuPhase = D_800A3928MainLoop;
                                        if (menuPhase == one) {
                                            goto confirmStageOne;
                                        }
                                        if (menuPhase < 2) {
                                            if (menuPhase == 0) {
                                                goto confirmStageZero;
                                            }
                                            goto finishInput;
                                        }
                                        if (menuPhase == two) {
                                            goto confirmStageTwo;
                                        }
                                        goto finishInput;
                                    confirmStageZero:
                                        gCardMenuMessageMainLoop[0] = 0x17;
                                        cardOperation = 0;
                                        goto startCardOperation;
                                    confirmStageOne:
                                        if (func_8006D258MainLoop() == one) {
                                            gCardMenuMessageMainLoop[0] = 0x12;
                                        }
                                        D_800A3928MainLoop = two;
                                    refreshCardMenu:
                                        CardMenuShowMessageMainLoop(0);
                                        goto finishInput;
                                    confirmStageTwo:
                                        CardMenuSetColorNodeLayoutMainLoop(
                                            0, -0x78, -2);
                                        if (D_800A3968MainLoop[0] != 0) {
                                            D_800A3950MainLoop = 0x24;
                                        }
                                        goto finishMainMenuReturn;
                                    confirmMode25:
                                        SoundPlaySlotMainLoop(0, 3);
                                        CardMenuSetColorNodeLayoutMainLoop(
                                            0, -0x78, -2);
                                        screenResult = 1;
                                        gScreenStateMainLoop = screenResult;
                                        goto finishInput;
                                    confirmMode26:
                                        SoundPlaySlotMainLoop(0, 3);
                                        CardMenuSetColorNodeLayoutMainLoop(
                                            0, -0x78, -2);
                                        gScreenStateMainLoop = 7;
                                        RaceBuildQualifyingGridMainLoop(
                                            gSelectedTrackMainLoop);
                                        screenResult = 0xFF;
                                        goto finishInput;
                                    }
                                    goto finishInput;
                                }
                                if (currentPadZero &
                                    ((u16)previousPadInverse & 0x10)) {
                                    if (gScreenStateMainLoop == 7) {

                                        if (D_800A3950MainLoop == 0xFB) {
                                            SoundPlaySlotMainLoop(0, 4);
                                            gScreenStateMainLoop = 0x26;
                                            gCardMenuMessageMainLoopSite51[0] =
                                                0x16;
                                            CardMenuShowMessageMainLoop(0);
                                            CardMenuCenterSelectedTextMainLoop(
                                                3);
                                            CardMenuSetColorNodeLayoutMainLoop(
                                                -0x78, 0, 2);
                                        }
                                    } else {
                                        screenResult = func_80056B0CMainLoop(
                                            (s32)gScreenStateMainLoop,
                                            (s32)D_800A3950MainLoop);
                                        if (screenResult & 0xFF) {
                                            SoundPlaySlotMainLoop(0, 4);

                                        } else {
                                            goto storePadStates;
                                        }
                                    }
                                    goto finishInput;
                                }
                                if (currentPadZero &
                                    ((u16)previousPadInverse & 0x80)) {
                                    s32 cancelPivot;
                                    s32 cancelMode;
                                    cancelPivot = 0x25;
                                    cancelMode = gScreenStateMainLoop;
                                    switch (cancelMode) {
                                    case 0xFC:
                                        if (gCardMenuMessageMainLoop[0] !=
                                                two &&
                                            D_800A3928MainLoop == 0) {
                                            s32 cardStatus;
                                            SoundPlaySlotMainLoop(0, 3);
                                            CardEnableAndTestEventsMainLoop();
                                            CardResolveSlotMainLoop();
                                            cardStatus =
                                                func_80069EB8MainLoop() & 0xFF;
                                            if (cardStatus == 0) {
                                                cardStatus = 4;
                                            } else {
                                                cardStatus = 0x13;
                                            }
                                            gCardMenuMessageMainLoop[0] =
                                                cardStatus;
                                            CardTestAndDisableEventsMainLoop();
                                            cardOperation = 1;
                                        startCardOperation:
                                            CardMenuShowMessageMainLoop(
                                                cardOperation);
                                            D_800A3928MainLoop = one;
                                        }
                                        break;
                                    case 0x23:
                                        if (D_800A3928MainLoop == 0) {
                                            if (gCardMenuMessageMainLoop[0] ==
                                                    mode13 ||
                                                (u32)(gCardMenuMessageMainLoop
                                                          [0] -
                                                      0x19) < 2U) {
                                                SoundPlaySlotMainLoop(0, 3);
                                                CardEnableAndTestEventsMainLoop();
                                                if (!(func_80069EB8MainLoop() &
                                                      0xFF)) {
                                                    gCardMenuMessageMainLoop
                                                        [0] = 4;
                                                    CardMenuShowMessageMainLoop(
                                                        0);
                                                    D_800A3928MainLoop = one;
                                                    MenuUpdateItemRowMainLoop(
                                                        0xA);
                                                } else {
                                                    CardTestAndDisableEventsMainLoop();
                                                checkCardMenuReady:
                                                    if (gCardMenuMessageMainLoop
                                                            [0] == 0) {
                                                        CardMenuWriteSaveSlotMainLoop();
                                                        CardMenuShowMessageMainLoop(
                                                            0);
                                                        D_800A3928MainLoop =
                                                            one;
                                                        MenuUpdateItemRowMainLoop(
                                                            0xA);
                                                    }
                                                }
                                            } else {
                                                goto playBackSound;
                                            }
                                        }
                                        break;
                                    case 0x24:
                                    playBackSound:
                                        returnChannel = 0;
                                        actionSound = 4;
                                    returnMainMenu:
                                        SoundPlaySlotMainLoop(returnChannel,
                                                              actionSound);
                                        CardMenuSetColorNodeLayoutMainLoop(
                                            0, -0x78, -2);
                                    finishMainMenuReturn:
                                        gScreenStateMainLoop = one;
                                        MenuUpdateItemRowMainLoop(1);
                                        break;
                                    case 0x22:
                                    case 0x28:
                                        goto playBackSound;
                                    case 0x25:
                                    case 0x27:
                                        SoundPlaySlotMainLoop(0, 4);
                                        CardMenuSetColorNodeLayoutMainLoop(
                                            0, -0x78, -2);
                                        gScreenStateMainLoop = one;
                                        break;
                                    case 0x26:
                                        SoundPlaySlotMainLoop(0, 4);
                                        CardMenuSetColorNodeLayoutMainLoop(
                                            0, -0x78, -2);
                                        gScreenStateMainLoop = 7;
                                        break;
                                    }
                                    goto finishInput;
                                }
                                /* End the old register lifetime before setting the pad index. */
                                index = player & 0xFF;
                                padBits = newPad[index];
                                if (padBits &
                                    ((u16)previousPadInverse & 0x20)) {

                                    if (gScreenStateMainLoop == 0x23) {
                                        func_8006CE64MainLoop();
                                    }
                                    goto finishInput;
                                }
                                if (padBits & 0x1000) {
                                    register s32 padEdgeUp;
                                    s32 blockedModeUp;
                                    s32 cardModeUp;
                                    s32 rawModeUp;
                                    s32 modeUp;
                                    blockedModeUp = 0x21;
                                    /* Retain the raw mode byte and its comparison value. */
                                    rawModeUp = (u8)gScreenStateMainLoop;
                                    modeUp = rawModeUp & 255;
                                    if ((modeUp != blockedModeUp) &&
                                        (modeUp != 0xFC) &&
                                        ((u32)(rawModeUp - 0x25) >= 2U) &&
                                        (modeUp != mode13) &&
                                        (modeUp != 0x27) && (modeUp != 0xE)) {
                                        if (((u32)(rawModeUp - 9) < 2U) ||
                                            (modeUp == 0xC) ||
                                            ((u32)(rawModeUp - 0x10) < 2U)) {
                                            func_80068AC4MainLoop(newPad[0],
                                                                  oldPad[0], 1);

                                            goto finishInput;
                                        }
                                        cardModeUp = 0x23;
                                        if (modeUp == cardModeUp) {
                                            if (D_800A3928MainLoop == one) {
                                                goto nextPlayer;
                                            }
                                            if (D_800A3770MainLoopSite57[0] !=
                                                0) {
                                                goto nextPlayer;
                                            }
                                            menuDirection = 1;
                                            goto moveCardCursor;
                                        }
                                        padEdgeUp = previousPadInverse & 0x1000;
                                        if (currentPadZero & padEdgeUp) {
                                            if ((modeUp == 0x22) ||
                                                (modeUp == 0x24) ||
                                                (modeUp == 0x28)) {
                                                if (D_800A3770MainLoopSite58
                                                        [0] == 0) {
                                                    if (func_8006C700MainLoop(
                                                            0,
                                                            gScreenStateMainLoop ==
                                                                0x22) &
                                                        0xFF) {
                                                        SoundPlaySlotMainLoop(
                                                            0, 0);

                                                    } else {
                                                        goto storePadStates;
                                                    }
                                                    goto finishInput;
                                                }
                                            } else {
                                                SoundPlaySlotMainLoop(0, 0);
                                                wrappedItemUp =
                                                    D_800A3059MainLoop;
                                                if (wrappedItemUp == 0) {
                                                    wrappedItemUp =
                                                        D_800A38E8MainLoopSite59
                                                            [0] -
                                                        1;
                                                } else {
                                                    wrappedItemUp -= 1;
                                                }
                                                do {
                                                    D_800A3059MainLoop =
                                                        wrappedItemUp;
                                                } while (0);

                                                if (gScreenStateMainLoop ==
                                                    two) {

                                                    if (D_800A3988MainLoopSmall ==
                                                        0) {
                                                        if ((u32)(D_800A3059MainLoopPostUp -
                                                                  4) < 2U) {
                                                            D_800A3059MainLoopPostUp =
                                                                3;

                                                        } else {
                                                            goto storePadStates;
                                                        }
                                                    }
                                                    goto finishInput;
                                                }
                                                if ((gScreenStateMainLoop ==
                                                     one) &&
                                                    (D_800A3950MainLoop == 0)) {

                                                    if ((u32)(D_800A3059MainLoopPostUp -
                                                              2) < 4U) {
                                                        D_800A3059MainLoopPostUp =
                                                            one;

                                                    } else {
                                                        goto finishInput;
                                                    }
                                                } else {
                                                    if (gScreenStateMainLoop ==
                                                        3) {

                                                        if (D_800A3644MainLoop !=
                                                            0) {
                                                            itemUp =
                                                                D_800A3059MainLoopPostUp &
                                                                0xFF;
                                                            if (itemUp == 3) {
                                                                D_800A3059MainLoopPostUp -=
                                                                    2;

                                                            } else if (itemUp ==
                                                                       two) {
                                                                D_800A3059MainLoopPostUp -=
                                                                    1;

                                                            } else {
                                                                goto storePadStates;
                                                            }
                                                        }
                                                        goto finishInput;
                                                    }
                                                    if (gScreenStateMainLoop ==
                                                        4) {
                                                        itemCursorUp =
                                                            D_800A3059MainLoopPostUp;

                                                        if (D_800A3988MainLoopSite60
                                                                [itemCursorUp &
                                                                 0xFF] &
                                                            0x80) {
                                                            do {
                                                                nextItemUp =
                                                                    itemCursorUp -
                                                                    1;
                                                                D_800A3059MainLoopPostUp =
                                                                    nextItemUp;
                                                                itemCursorUp =
                                                                    nextItemUp;
                                                            } while (
                                                                D_800A3988MainLoopSite61
                                                                    [nextItemUp &
                                                                     0xFF] &
                                                                0x80);
                                                        }
                                                        goto finishInput;
                                                    }

                                                    if (gScreenStateMainLoop ==
                                                        5) {

                                                        if (D_800A3059MainLoopPostUp ==
                                                            5) {

                                                            if (D_800A3076MainLoop ==
                                                                0) {
                                                                D_800A3059MainLoopPostUp -=
                                                                    1;
                                                            }
                                                            goto finishInput;
                                                        }
                                                    } else {
                                                        goto finishInput;
                                                    }
                                                }
                                                goto updatePreviousPad;
                                            }
                                        } else {
                                            goto storePadStates;
                                        }
                                        goto nextPlayer;
                                    }
                                    goto nextPlayer;
                                }
                                if (padBits & 0x4000) {
                                    register s32 padEdgeDown;
                                    s32 blockedModeDown;
                                    s32 cardModeDown;
                                    s32 rawModeDown;
                                    register s32 modeDown;
                                    blockedModeDown = 0x21;
                                    /* Retain the raw mode byte and its comparison value. */
                                    rawModeDown = (u8)gScreenStateMainLoop;
                                    modeDown = rawModeDown & 255;
                                    if ((modeDown != blockedModeDown) &&
                                        (modeDown != 0xFC) &&
                                        ((u32)(rawModeDown - 0x25) >= 2U) &&
                                        (modeDown != mode13) &&
                                        (modeDown != 0x27) &&
                                        (modeDown != 0xE)) {
                                        if (((u32)(rawModeDown - 9) < 2U) ||
                                            (modeDown == 0xC) ||
                                            ((u32)(rawModeDown - 0x10) < 2U)) {
                                            func_80068AC4MainLoop(newPad[0],
                                                                  oldPad[0], 0);

                                            goto finishInput;
                                        }
                                        cardModeDown = 0x23;
                                        if (modeDown == cardModeDown) {
                                            if (D_800A3928MainLoop == one) {
                                                goto nextPlayer;
                                            }
                                            if (D_800A3770MainLoopSite62[0] !=
                                                0) {
                                                goto nextPlayer;
                                            }
                                            menuDirection = 0;
                                        moveCardCursor:
                                            player += 1;
                                            /* guess: the asm passes leftover a1 and a2; func_8006CB80 tests
                                             * arg1 & ~arg2 as a pad edge, so give it the pad states. */
                                            func_8006CB80MainLoop(menuDirection, newPad[0], oldPad[0]);
                                            oldPad[0] = newPad[0];
                                        } else {
                                            padEdgeDown =
                                                previousPadInverse & 0x4000;
                                            if (currentPadZero & padEdgeDown) {
                                                if ((modeDown == 0x22) ||
                                                    (modeDown == 0x24) ||
                                                    (modeDown == 0x28)) {
                                                    if (D_800A3770MainLoopSite63
                                                            [0] == 0) {
                                                        if (func_8006C700MainLoop(
                                                                1,
                                                                gScreenStateMainLoop ==
                                                                    0x22) &
                                                            0xFF) {
                                                            SoundPlaySlotMainLoop(
                                                                0, 1);

                                                        } else {
                                                            goto storePadStates;
                                                        }
                                                        goto finishInput;
                                                    }
                                                } else {
                                                    SoundPlaySlotMainLoop(0, 1);
                                                    if ((D_800A3059MainLoop &
                                                         0xFF) ==
                                                        (D_800A38E8MainLoopSite64
                                                             [0] -
                                                         1)) {
                                                        D_800A3059MainLoop = 0;
                                                    } else {
                                                        D_800A3059MainLoop += 1;
                                                    }
                                                    if (gScreenStateMainLoop ==
                                                        two) {

                                                        if (D_800A3988MainLoopSmall ==
                                                            0) {

                                                            if (D_800A3059MainLoopPostDown ==
                                                                4) {
                                                                /* Keep the two skip paths separate until the store. */
                                                                asm volatile(
                                                                    ""
                                                                    :
                                                                    :
                                                                    : "memory");
                                                                goto skipLockedItems;
                                                            }
                                                        }
                                                        goto finishInput;
                                                    }
                                                    if ((gScreenStateMainLoop ==
                                                         one) &&
                                                        (D_800A3950MainLoop ==
                                                         0)) {
                                                        if ((u32)(D_800A3059MainLoopPostDown -
                                                                  2) < 4U) {
                                                        skipLockedItems:
                                                            D_800A3059MainLoopPostDown =
                                                                6;

                                                        } else {
                                                            goto storePadStates;
                                                        }
                                                        goto finishInput;
                                                    }
                                                    if (gScreenStateMainLoop ==
                                                        3) {

                                                        if (D_800A3644MainLoop !=
                                                            0) {
                                                            itemDown =
                                                                D_800A3059MainLoopPostDown &
                                                                0xFF;
                                                            if (itemDown ==
                                                                two) {
                                                                D_800A3059MainLoopPostDown +=
                                                                    2;

                                                            } else if (
                                                                itemDown ==
                                                                gScreenStateMainLoop) {
                                                                D_800A3059MainLoopPostDown +=
                                                                    1;

                                                            } else {
                                                                goto storePadStates;
                                                            }
                                                        }
                                                        goto finishInput;
                                                    }
                                                    if (gScreenStateMainLoop ==
                                                        4) {
                                                        itemCursorDown =
                                                            D_800A3059MainLoopPostDown;

                                                        if (D_800A3988MainLoopSite65
                                                                [itemCursorDown &
                                                                 0xFF] &
                                                            0x80) {
                                                            do {
                                                                nextItemDown =
                                                                    itemCursorDown +
                                                                    1;
                                                                D_800A3059MainLoopPostDown =
                                                                    nextItemDown;
                                                                itemCursorDown =
                                                                    nextItemDown;
                                                            } while (
                                                                D_800A3988MainLoopSite66
                                                                    [nextItemDown &
                                                                     0xFF] &
                                                                0x80);
                                                        }
                                                        goto finishInput;
                                                    }

                                                    if (gScreenStateMainLoop !=
                                                        5) {
                                                        goto finishInput;
                                                    }
                                                    if (D_800A3059MainLoopPostDown !=
                                                        gScreenStateMainLoop) {
                                                        goto finishInput;
                                                    }
                                                    if (D_800A3076MainLoop !=
                                                        0) {
                                                        goto finishInput;
                                                    }
                                                    D_800A3059MainLoopPostDown =
                                                        0;
                                                    goto updatePreviousPad;
                                                }
                                            } else {
                                                goto storePadStates;
                                            }
                                            goto nextPlayer;
                                        }
                                    } else {
                                        goto nextPlayer;
                                    }
                                } else {
                                    if (padBits & 0x8000) {
                                        if (gScreenStateMainLoop == mode13 &&
                                            (padBits &
                                             ((u16)~oldPad[index] & 0x8000))) {
                                            if (!(PadTypeNeedsCalibrationMainLoop(
                                                      (u8)gPadTypeMainLoopSite68
                                                          [index]) &
                                                  0xFF) ||
                                                D_800A3684MainLoopSite67
                                                        [index] != one) {
                                                if (D_800A3684MainLoopSite69
                                                        [index] == 0) {
                                                    SoundPlaySlotMainLoop(0, 2);
                                                    {
                                                        s32 variantCount;
                                                        s32 variantValue;
                                                        s32 countMinusOne;
                                                        s32 variantRemainder;
                                                        variantCount =
                                                            D_800A3080MainLoopSite70
                                                                [gPadTypeMainLoopSite71
                                                                     [index]];
                                                        variantValue =
                                                            gPadLayoutMainLoopSite72
                                                                [index];
                                                        countMinusOne =
                                                            variantCount - 1;
                                                        variantValue +=
                                                            countMinusOne;
                                                        variantRemainder =
                                                            variantValue %
                                                            variantCount;
                                                        gPadLayoutMainLoopSite72
                                                            [index] =
                                                                variantRemainder;
                                                    }
                                                }
                                            }
                                        } else if (gScreenStateMainLoop ==
                                                       two &&
                                                   D_800A3059MainLoop == one) {
                                            MenuHandleOptionsInputMainLoop(
                                                2, 1, 1, newPad[player & 0xFF],
                                                oldPad[player & 0xFF],
                                                player & 0xFF);
                                        } else {
                                            MenuHandleOptionsInputMainLoop(
                                                gScreenStateMainLoop,
                                                D_800A3059MainLoop, 1,
                                                newPad[0], oldPad[0],
                                                activePlayer);
                                        }
                                    } else if (padBits & 0x2000) {
                                        if (gScreenStateMainLoop == mode13 &&
                                            (padBits &
                                             ((u16)~oldPad[index] & 0x2000))) {
                                            if (!(PadTypeNeedsCalibrationMainLoop(
                                                      (u8)gPadTypeMainLoopSite74
                                                          [index]) &
                                                  0xFF) ||
                                                D_800A3684MainLoopSite73
                                                        [index] != one) {
                                                if (D_800A3684MainLoopSite75
                                                        [index] == 0) {
                                                    SoundPlaySlotMainLoop(0, 2);
                                                    gPadLayoutMainLoopSite76[index] =
                                                        (gPadLayoutMainLoopSite76
                                                             [index] +
                                                         1) %
                                                        D_800A3080MainLoopSite77
                                                            [gPadTypeMainLoopSite78
                                                                 [index]];
                                                }
                                            }
                                        } else if (gScreenStateMainLoop ==
                                                       two &&
                                                   D_800A3059MainLoop == one) {
                                            MenuHandleOptionsInputMainLoop(
                                                2, 1, 0, newPad[player & 0xFF],
                                                oldPad[player & 0xFF],
                                                player & 0xFF);
                                        } else {
                                            MenuHandleOptionsInputMainLoop(
                                                gScreenStateMainLoop,
                                                D_800A3059MainLoop, 0,
                                                newPad[0], oldPad[0],
                                                activePlayer);
                                        }
                                    }
                                storePadStates:
                                finishInput:

                                updatePreviousPad:
                                    oldPad[player & 0xFF] =
                                        newPad[player & 0xFF];
                                    goto nextPlayer;
                                }
                            }
                        } else {
                        nextPlayer:
                            player += 1;
                        }
                        index = (u8)player;
                    } while ((u32)(player & 0xFF) < 2U);
                }
            } while (!(screenResult & 0xFF));
        }
        DrawSyncMainLoop(0);
        if (gScreenStateMainLoop == 7) {
            func_80057DE8MainLoop();
        }
        screenResultByte = screenResult & 0xFF;
        if (gScreenStateMainLoop != 0xFD) {
            nextScreen = MenuUpdateScreenStateMainLoop(
                gScreenStateMainLoop, &D_800A3950MainLoop, screenResultByte);
            gScreenStateMainLoop = nextScreen;
            if ((nextScreen & 0xFF) == 7) {
                activePlayer = 0;
            }
            if ((D_800A3950MainLoop == 7) && !(activePlayer & 0xFF) &&
                (D_800A3644MainLoop != 0) && (*D_800A3A25MainLoopSite79 != 0) &&
                (screenResultByte != 0xFF)) {
                activePlayer = 1;
                D_800A3950MainLoop = nextScreen;
                gScreenStateMainLoop = 7;
                D_800A3059MainLoop = 0;
            }
        }
        if ((gScreenStateMainLoop == 0xFF) || (gScreenStateMainLoop == 0xFD) ||
            (gScreenStateMainLoop == 0xF8)) {
            exitLoop = 1;
        }
    } while (exitLoop == 0);
    VSyncMainLoop(0);
    VSyncMainLoop(0);
    do {

    } while (func_8003F4FCMainLoop(0) & 0xFF);
}
