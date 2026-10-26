void TrackReadData(TrackResource *trackData, s32 file) {
    /* Only the first byte is accessed in the retail function. */
    char scratch[0x220];
    VECTOR maxBounds;
    VECTOR minBounds;
    VECTOR point;
    char errorBuffer[0x40];
    u8 *sectionHeader;
    u8 *objectData;
    s32 objectFaceCount;
    s32 faceCount;
    s32 nodeCount;
    u8 *copy16Data;
    u8 *positionData;
    u8 *nodeData;
    u8 *sectionData;
    u8 *errorText;
    s32 specialFaceColor;
    /* Reserve seven spill homes between the color and object offsets. */
    s32 spillPad0;
    s32 spillPad1;
    s32 spillPad2;
    s32 spillPad3;
    s32 spillPad4;
    s32 spillPad5;
    s32 spillPad6;

    s32 nextObjectOffset;
    s32 prevObjectOffset;
    s32 faceCodeSave;
    u8 *vertexOffset;
    u8 *faceOffset;
    u8 *objectOffset;
    register s32 copy16Offset;
    register s32 positionOffset;
    register u8 *outputVertices;
    u8 *vertices;
    register SVECTOR *outputVertex;
    register s32 minimumZ;
    u8 *outputRecord;
    u8 *section;
    s32 vertexCount;
    s32 vertexIndex;
    s32 faceMode;
    register s32 lastCorner;
    register s32 nextDataOffset;
    register s32 randomValue;
    register s32 shadeBase;
    s32 nodesOffset;
    s32 sectionsOffset;
    u8 *sectionHeaderData;
    register u8 *outputZ;
    FileVertex *inputVertex;
    u8 *data;
    register TrackSection *sec;
    TrackFileHeader *fileData;
    s32 sectionCount;
    s32 fileSize;
    register u32 nodeScale;
    register char *initText;
    s32 positionZ;
    s32 value0;
    s32 value1;
    s32 value2;
    register s32 objectFlags;
    register u32 typeA;
    register u32 typeC;
    register s16 *callFirst;
    register u8 *callHead;
    register u8 *callFaces;
    register s32 lastObjectOffset;
    s32 scaledY;
    s32 scaledX;
    s32 workValue;
    s32 vertexSlot;
    s32 uvSlot;
    s32 faceCode;
    register s32 runtimeFaceOffset;
    s32 shade;
    s32 i;
    s32 nodeOffset;
    s32 rawX;
    s32 rawY;
    s32 rawZ;
    s32 scaledZ;
    register s32 positionByteOffset;
    u8 *inputIndex;
    u8 *inputUv;
    u8 *diskFace;
    s32 count;
    register s32 objectPolygonCount;
    register s32 faceColor;
    register u8 *flagObject;
    u8 faceFlags;
    u8 byteValue;
    u8 modeFlags;
    u8 *allocatedVertices;
    u8 *allocatedFaces;
    u8 *allocatedNodes;
    u8 *allocatedObjects;
    TrackCallback *node;
    u8 *objectFaceIndices;
    Face *face;
    u8 *nodeDataStart;
    u8 *sectionObject;
    u8 *unusedCursor;
    u8 *inputCopy16;
    u8 *inputPosition;
    u8 *inputNode;
    register u8 *faceFields;
    TrackFileObject *diskObject;
    u8 *outputIndex;
    u8 *outputUv;
    register u32 boundLimit;

    fileSize = FileSeek(file, 0, 2);
    fileData = (TrackFileHeader *)LOAD_BELOW_TOP(fileSize);
    FileSeek(file, 0, 0);
    FileRead(fileData, fileSize, 1, file);
    vertexOffset = (u8 *)fileData->vertexOffset;
    faceOffset = (u8 *)fileData->faceOffset;
    objectOffset = (u8 *)fileData->objectOffset;
    copy16Offset = fileData->copy16Offset;
    positionOffset = fileData->positionOffset;
    nodesOffset = fileData->nodesOffset;
    sectionsOffset = fileData->sectionsOffset;
    vertexCount = fileData->vertexCount;
    asm volatile(""
                 :
                 : "g"(vertexOffset), "g"(faceOffset), "g"(objectOffset),
                   "g"(copy16Offset), "g"(positionOffset), "g"(nodesOffset),
                   "g"(sectionsOffset), "g"(vertexCount)
                 : "memory");
    /* Inverse of 135 for the aligned 540-byte node records. */
    nodeScale = 0xE1A8C537;
    nodeDataStart = (u8 *)fileData + nodesOffset;
    sectionHeaderData = (u8 *)fileData + sectionsOffset;
    trackData->vertexCount = (s32)vertexCount;
    nodeData = nodeDataStart;
    sectionHeader = sectionHeaderData;
    /* lh faceCount, unk2: a signed halfword load; nodeScale is unchanged. */
    faceCount = *(s16 *)&fileData->unk2;
    nodeCount =
        (s32)((u32)(sectionHeaderData - nodeDataStart) * nodeScale) >> 2;
    initText = gTrackInitMessage;
    asm("" : "=r"(initText) : "0"(initText));
    data = (u8 *)fileData + (s32)vertexOffset;
    diskFace = (u8 *)fileData + (s32)faceOffset;
    trackData->faceCount = (s32)faceCount;
    diskObject = (TrackFileObject *)((u8 *)fileData + (s32)objectOffset);
    trackData->objectCount = (s32)fileData->objectCount;
    copy16Data = (u8 *)fileData + copy16Offset;
    positionData = (u8 *)fileData + positionOffset;
    func_8001D218(initText, vertexOffset, faceOffset, objectOffset);
    allocatedVertices = HeapAlloc(vertexCount * 8);
    D_800BE97C[0] = allocatedVertices;
    sectionData = sectionHeader + 4;
    if (allocatedVertices == NULL) {
        SystemShowFatalError(&gErrorTrackVertexAllocation);
    }
    allocatedFaces = HeapAlloc(faceCount * 0x2C);
    D_800A3A40 = allocatedFaces;
    if (allocatedFaces == NULL) {
        SystemShowFatalError(&gErrorTrackFaceAllocation);
    }
    D_800BE984[0] = 0;
    D_800BE970[0] = (s32)vertexCount;
    allocatedNodes = HeapAlloc(nodeCount * 0x21C);
    D_800A39A4 = allocatedNodes;
    if (allocatedNodes == NULL) {
        SystemShowFatalError(&gErrorTrackSpecialObjectAllocation);
    }
    i = 0;
    allocatedObjects = HeapAlloc(trackData->objectCount * 0x90);
    objectData = allocatedObjects;
    trackData->objects = allocatedObjects;
    func_8001D218(gTrackReadVerticesMessage);
    boundLimit = 0x7FFF0000;
    outputVertices = trackData->vertices;
    boundLimit |= 0xFFFF;
    D_800AE84C[0] = 0;
    D_800AE848[0] = 0;
    D_800AE844[0] = 0;
    minBounds.vz = boundLimit;
    minBounds.vy = boundLimit;
    minBounds.vx = boundLimit;
    maxBounds.vz = 0x80000001;
    maxBounds.vy = 0x80000001;
    maxBounds.vx = 0x80000001;
    if (vertexCount > 0) {
        inputVertex = (FileVertex *)data;
    readVertexBounds:
        value0 = inputVertex->x;
        scaledX = value0 >> 2;
        if (value0 < 0) {
            scaledX = (s32)(value0 + 3) >> 2;
        }
        point.vx = scaledX;
        value1 = inputVertex->y;
        scaledY = value1 >> 2;
        if (value1 < 0) {
            scaledY = (s32)(value1 + 3) >> 2;
        }
        point.vy = scaledY;
        rawZ = inputVertex->z;
        if (rawZ < 0) {
            rawZ += 3;
        }
        value2 = rawZ >> 2;
        point.vz = value2;
        if (scaledX < minBounds.vx) {
            minBounds.vx = scaledX;
        }
        if (scaledY < minBounds.vy) {
            minBounds.vy = scaledY;
        }
        if (value2 < minBounds.vz) {
            minBounds.vz = value2;
        }
        if (maxBounds.vx < scaledX) {
            maxBounds.vx = scaledX;
        }
        if (maxBounds.vy < scaledY) {
            maxBounds.vy = scaledY;
        }
        if (maxBounds.vz < value2) {
            maxBounds.vz = value2;
        }
        i += 1;
        inputVertex++;
        if (i < vertexCount)
            goto readVertexBounds;
    }
    value2 = minBounds.vx;
    value1 = maxBounds.vx;
    workValue = maxBounds.vy;
    D_800AE84C[0] = 0;
    D_800AE844[0] = (s32)((s32)(value2 + value1) / 2);
    D_800AE848[0] = (s32)(minBounds.vy + workValue) / 2;
    i = 0;
    if (vertexCount > 0) {
        outputVertex = (SVECTOR *)outputVertices;
        workValue = (s32)(data + 8);
        do {
            rawX = ((Vec3 *)data)->x;
            if (rawX < 0) {
                rawX += 3;
            }
            outputVertex->vx = (s16)((rawX >> 2) - D_800AE844[0]);
            rawY = ((Vec3 *)(workValue - 8))->y;
            if (rawY < 0) {
                rawY += 3;
            }
            outputVertex->vy = (s16)((rawY >> 2) - D_800AE844[1]);
            scaledZ = ((Vec3 *)(workValue - 8))->z;
            if (scaledZ < 0) {
                scaledZ += 3;
            }
            workValue += 0xC;
            data += 0xC;
            i += 1;
            outputVertex->vz = (s16)((scaledZ >> 2) - D_800AE844[2]);
            outputVertex++;
        } while (i < vertexCount);
    }
    i = 0;
    func_8001D218(gTrackReadFacesMessage);
    scratch[0] = 0;
    vertices = trackData->vertices;
    if (faceCount > 0) {
        errorText = (u8 *)errorBuffer;
        faceCode = 0x40;
        runtimeFaceOffset = 0;
        faceFields = diskFace + 0x13;
        do {
            face = D_800A3A40 + runtimeFaceOffset;
            *(u8 **)&face->next = (void *)trackData->faces;
            trackData->faces = face;
            count = ((DiskFace *)diskFace)->vertexCount;
            face->vertexCount = count;
            if ((u32)count >= 5U) {
                faceCodeSave = faceCode;
                sprintf((char *)errorText, gTrackFaceErrorFormat, i);
                GraphicsRenderFrame((s32)errorText);
            }
            *(s32 *)&face->r0 = ((DiskFace *)(faceFields - 0x13))->color;
            byteValue = ((DiskFace *)(faceFields - 0x13))->type;
            face->flags = 0;
            face->type = byteValue;
            *(u16 *)&face->angle =
                (u16)((DiskFace *)(faceFields - 0x13))->angle;
            if (((DiskFace *)(faceFields - 0x13))->unk3 != 0) {
                faceFlags = face->flags;
                face->flags = (u8)(faceFlags | 1);
                if (((DiskFace *)(faceFields - 0x13))->unk3 == 1) {
                    face->flags = (u8)(faceFlags | 3);
                }
            } else {
                *(u16 *)&face->angle = (u16) * (u16 *)(faceFields + (-7));
                if ((s16)((DiskFace *)(faceFields - 0x13))->angle == faceCode) {
                    face->flags = (u8)(face->flags | 4);
                }
            }
            face->depth = 0;
            if (*(s8 *)(faceFields + (-17)) != 0x7F) {
                face->flags = (u8)(face->flags | 0x80);
                if ((u8) * (s8 *)(faceFields + (-17)) == 0x81) {
                    face->depth = (s8)faceCode;
                }
                if ((u8) * (s8 *)(faceFields + (-17)) == 0x82) {
                    face->depth = 0;
                } else {
                    face->depth = (s8)faceCode;
                }
            } else {
                face->depth = (s8)faceCode;
                faceMode = (s16)((DiskFace *)(faceFields - 0x13))->angle;
                switch (faceMode) {
                case 1:
                    modeFlags = face->flags | 8;
                    break;
                case 2:
                    modeFlags = face->flags | 0x28;
                    break;
                default:
                    goto faceFlagsDone;
                }
                face->flags = modeFlags;
            }
        faceFlagsDone:
            vertexSlot = 0;
            if (count > 0) {
                inputIndex = diskFace;
                outputIndex = face;
                do {
                    vertexIndex = ((DiskFace *)inputIndex)->vertex[0];
                    inputIndex += 2;
                    vertexSlot += 1;
                    ((Face *)outputIndex)->vertex[0] =
                        (SVECTOR *)(vertices + (vertexIndex * 8));
                    outputIndex += 4;
                } while (vertexSlot < count);
            }
            if (vertexSlot == 3) {
                face->vertex[3] = face->vertex[0];
            }
            uvSlot = 0;
            inputUv = diskFace;
            outputUv = face;
        readFaceUv:
            ((Face *)outputUv)->u0 = ((DiskFace *)inputUv)->uv[0][0];
            byteValue = ((DiskFace *)inputUv)->uv[0][1];
            uvSlot += 1;
            inputUv += 2;
            ((Face *)outputUv)->v0 = byteValue;
            outputUv += 4;
            if (uvSlot < 3) {
                goto readFaceUv;
            }
            if ((u8)face->vertexCount >= 4U) {
                face->u2 = ((DiskFace *)(faceFields - 0x13))->uv[3][0];
                face->v2 = ((DiskFace *)(faceFields - 0x13))->uv[3][1];
                face->u3 = ((DiskFace *)(faceFields - 0x13))->uv[2][0];
                face->v3 = ((DiskFace *)(faceFields - 0x13))->uv[2][1];
            }
            faceFields += 0x1C;
            diskFace += 0x1C;
            i += 1;
            runtimeFaceOffset += 0x2C;
        } while (i < faceCount);
    }
    count = trackData->objectCount;
    vertices = trackData->vertices;
    shade = 0x80;
    i = 0;
    if (count > 0) {
        sec = (TrackSection *)objectData;
        specialFaceColor = 0x4A4A4A;
        nextObjectOffset = 0x90;
        prevObjectOffset = -0x90;
        do {
            *(u8 **)&sec->prev = objectData + prevObjectOffset;
            *(u8 **)&sec->next = (void *)(objectData + nextObjectOffset);
            objectFlags = *(u32 *)&sec->angle;
            typeA = diskObject->type;
            sec->type = typeA;
            typeC = diskObject->unk2;
            objectFlags &= 0xFFFEFFFF;
            *(s16 *)&sec->section = i;
            *(u32 *)&sec->angle = objectFlags;
            sec->unkC = typeC;
            typeA = diskObject->unk4;
            *(u32 *)&sec->angle =
                (objectFlags & 0xFF01FFFF) | ((typeA & 0x7F) << 17);
            typeA = diskObject->unk6;
            do {
                objectFaceIndices = (u8 *)(diskObject + 1);
            } while (0);

            sec->angle = typeA;
            *(FileVertex *)&sec->x = diskObject->position;
            callFaces = D_800A3A40;
            callFirst = (s16 *)objectFaceIndices;
            callHead = (u8 *)&sec->unk20;
            sec->callbacks = 0;
            sec->unk50 = 0;
            sec->culled = 0;
            sec->unk24 = 0;
            sec->unk20 = NULL;
            sec->unk2C = 0;
            *(s32 *)&sec->firstQuad = 0;
            sec->unk34 = -1;
            objectFaceCount = func_800157B0(callFirst, callHead, callFaces);
            face = sec->unk20;
            objectPolygonCount = 0;
            if ((face != NULL) && !(face->flags & 0x80)) {
                flagObject = (u8 *)sec;
                faceColor = 0x808080;
                do {
                    if (*(s32 *)&face->r0 == specialFaceColor) {
                        *(u32 *)&((TrackSection *)flagObject)->angle |= 0x10000;
                    } else {
                        *(s32 *)&face->r0 = faceColor;
                    }
                    face = *(u8 **)&face->next;
                    objectPolygonCount += 1;
                } while ((face != NULL) && !(face->flags & 0x80));
            }
            *(s8 *)&sec->unk13 = objectPolygonCount;
            func_80015870((u8 *)&sec->unk20, (u8 *)&sec->firstQuad);
            randomValue = RandomScaledGet(3);
            shadeBase = shade - 1;
            shade = shadeBase + randomValue;
            if (shade >= 0x81) {
                shade = 0x80;
            } else if (shade < 0x50) {
                shade = 0x50;
            }
            func_80015930((u8 *)sec, trackData, shade);
            nextDataOffset = diskObject->corner[3];
            sec->unk78[0] = vertices + nextDataOffset * 8;
            nextDataOffset = diskObject->corner[2];
            sec->unk78[1] = vertices + nextDataOffset * 8;
            nextDataOffset = diskObject->corner[0];
            sec->unk78[2] = vertices + nextDataOffset * 8;
            nextDataOffset = diskObject->corner[1];
            sec->unk78[3] = vertices + nextDataOffset * 8;
            nextObjectOffset += 0x90;
            prevObjectOffset += 0x90;
            nextDataOffset = diskObject->corner[4];
            sec->unk78[4] = vertices + nextDataOffset * 8;
            i += 1;
            lastCorner = diskObject->corner[5];
            nextDataOffset = objectFaceCount * 2 + 2;
            diskObject =
                (TrackFileObject *)(objectFaceIndices + nextDataOffset);
            lastCorner = (s32)vertices + lastCorner * 8;
            sec->unk78[5] = (u8 *)lastCorner;
            sec++;
        } while (i < count);
        asm volatile(""
                     :
                     : "g"(spillPad0), "g"(spillPad1), "g"(spillPad2),
                       "g"(spillPad3), "g"(spillPad4), "g"(spillPad5),
                       "g"(spillPad6));
    }
    {
        u8 *objects;
        i -= 1;
        value0 = trackData->objectCount;
        lastObjectOffset = i * 8;
        inputCopy16 = copy16Data;
        lastObjectOffset += i;
        i = 0;
        trackData->objectCount = value0 - 1;
        objects = objectData;
        outputRecord = (u8 *)D_800BE72C;
        lastObjectOffset *= 16;
        *(u8 **)&((TrackSection *)objects)->prev =
            objects + (lastObjectOffset - 0x90);
        *(u8 **)&((TrackSection *)(lastObjectOffset + (s32)objects - 0x90))
             ->next = objects;
    }
    do {
        *(TrackCopy16 *)outputRecord = *(TrackCopy16 *)inputCopy16;
        outputRecord += 0x10;
        i += 1;
        inputCopy16 += 0x10;
    } while (i < 0x14);
    i = 0;
    minimumZ = 0xFA0;
    outputZ = &D_800B1350;
    inputPosition = positionData;
    positionByteOffset = 0;
copyStart:
    *(s32 *)((u8 *)D_800B1348 + positionByteOffset) =
        ((Vec3 *)inputPosition)->x;
    *(s32 *)((u8 *)D_800B134C + positionByteOffset) =
        ((Vec3 *)inputPosition)->y;
    positionZ = ((Vec3 *)inputPosition)->z;
    *(s32 *)outputZ = positionZ;
    if (positionZ < 0xFA0) {
        *(s32 *)outputZ = minimumZ;
    }
    outputZ += 0x58;
    inputPosition += 0xC;
    i += 1;
    positionByteOffset += 0x58;
    if (i < 0x14)
        goto copyStart;
    i = 0;
    if (nodeCount > 0) {
        nodeOffset = 0;
        inputNode = nodeData;
        do {
            *(TrackCallback *)((u8 *)(nodeOffset + (s32)D_800A39A4)) =
                *(TrackCallback *)inputNode;
            node = (TrackCallback *)(nodeOffset + (s32)D_800A39A4);
            node->next = ((TrackSection *)objectData)[node->section].callbacks;
            ((TrackSection *)objectData)[node->section].callbacks = node;
            inputNode += 0x21C;
            i += 1;
            nodeOffset += 0x21C;
        } while (i < nodeCount);
    }
    sectionCount = *(s32 *)sectionHeader;
    D_800A2F80[0] = sectionCount;
    if (sectionCount == 0) {
        D_800A39E0[0] = 0;
        D_800A376C[0] = 0;
    } else {
        register s32 firstIndex;
        s32 lastIndex;
        firstIndex = ((DiskSection *)sectionData)->section;
        lastIndex = sectionCount * 0x1C;
        lastIndex = ((DiskSection *)(lastIndex + (s32)sectionData))[-1].section;
        D_800A39E0[0] = firstIndex;
        D_800A376C[0] = lastIndex;
    }
    i = 0;
    if (D_800A2F80[0] > 0) {
        section = sectionData;
    readSection:
        sectionObject =
            (u8 *)(((DiskSection *)section)->section * 0x90 + (s32)objectData);
        outputRecord = ((DiskSection *)section)->unkC;
        *(DiskSection *)&((TrackSection *)sectionObject)->unk34 =
            *(DiskSection *)section;
        i += 1;
        section += 0x1C;
        if (i < D_800A2F80[0])
            goto readSection;
    }
    func_8001D218(gTrackReadSuccessMessage);
}
