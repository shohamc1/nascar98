/*
 * The port's software GTE (see port_gte.h): 32 data and 32 control
 * registers. Commands do no maths yet; each logs its first use.
 */
#include "host.h"
#include "port_gte.h"

s32 sprintf(char *, char *, ...);

static u32 sData[32];
static u32 sControl[32];

u32 PortGteRead(int reg)
{
    return sData[reg & 31];
}

void PortGteWrite(int reg, u32 value)
{
    sData[reg & 31] = value;
}

u32 PortGteReadControl(int reg)
{
    return sControl[reg & 31];
}

void PortGteWriteControl(int reg, u32 value)
{
    sControl[reg & 31] = value;
}

/* COMMAND is the whole COP2 word; its low six bits pick the operation. */
void PortGteCommand(u32 command)
{
    static u8 sLogged[64];
    char line[48];

    if (!sLogged[command & 63]) {
        sLogged[command & 63] = 1;
        sprintf(line, "gte: command %X has no maths yet", command);
        HostLog(line);
    }
}
