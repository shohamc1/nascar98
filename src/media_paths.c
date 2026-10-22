/* Retail .rodata between the jump tables of media.c and libgcc's clz table:
 * file paths, referenced only through the pointer tables in .data. The block
 * has no code of its own, so it is a data-only translation unit. */
#include "common.h"

const char gVideoSuzuka1[] = "VIDEO\\SUZUKA1.WVE";
static const char sVideoRtower[] = "VIDEO\\RTOWER.WVE";
static const char sVideoTaledega[] = "VIDEO\\TALEDEGA.WVE";
static const char sVideoCedar[] = "VIDEO\\CEDAR.WVE";
static const char sVideoWatkins[] = "VIDEO\\WATKINS.WVE";
static const char sVideoPocono[] = "VIDEO\\POCONO.WVE";
static const char sVideoWillow[] = "VIDEO\\WILLOW.WVE";
static const char sVideoFontana[] = "VIDEO\\FONTANA.WVE";
static const char sVideoMichigan[] = "VIDEO\\MICHIGAN.WVE";
static const char sVideoPridge[] = "VIDEO\\PRIDGE.WVE";
static const char sVideoCharlot1[] = "VIDEO\\CHARLOT1.WVE";
static const char sVideoSears[] = "VIDEO\\SEARS.WVE";
static const char sVideoBasin[] = "VIDEO\\BASIN.WVE";
static const char sVideoBristol[] = "VIDEO\\BRISTOL.WVE";
static const char sVideoTexas[] = "VIDEO\\TEXAS.WVE";
static const char sVideoBelmont[] = "VIDEO\\BELMONT.WVE";
static const char sVideoAtlantaa[] = "VIDEO\\ATLANTAA.WVE";
static const char sMenuartOvrly16Suzuka[] = "MENUART\\OVRLY\\16SUZUKA.TIM";
static const char sMenuartOvrly15Rancht[] = "MENUART\\OVRLY\\15RANCHT.TIM";
static const char sMenuartOvrly14Tallad[] = "MENUART\\OVRLY\\14TALLAD.TIM";
static const char sMenuartOvrly13Cedarw[] = "MENUART\\OVRLY\\13CEDARW.TIM";
static const char sMenuartOvrly12Wtknsg[] = "MENUART\\OVRLY\\12WTKNSG.TIM";
static const char sMenuartOvrly11Pocono[] = "MENUART\\OVRLY\\11POCONO.TIM";
static const char sMenuartOvrly10Willow[] = "MENUART\\OVRLY\\10WILLOW.TIM";
static const char sMenuartOvrly09Califo[] = "MENUART\\OVRLY\\09CALIFO.TIM";
static const char sMenuartOvrly08Michig[] = "MENUART\\OVRLY\\08MICHIG.TIM";
static const char sMenuartOvrly07Pinerd[] = "MENUART\\OVRLY\\07PINERD.TIM";
static const char sMenuartOvrly06Charlo[] = "MENUART\\OVRLY\\06CHARLO.TIM";
static const char sMenuartOvrly05Sears[] = "MENUART\\OVRLY\\05SEARS.TIM";
static const char sMenuartOvrly04Sbasin[] = "MENUART\\OVRLY\\04SBASIN.TIM";
static const char sMenuartOvrly03Bristo[] = "MENUART\\OVRLY\\03BRISTO.TIM";
static const char sMenuartOvrly02Texas[] = "MENUART\\OVRLY\\02TEXAS.TIM";
static const char sMenuartOvrly01Belmon[] = "MENUART\\OVRLY\\01BELMON.TIM";
static const char sMenuartOvrly00Atlant[] = "MENUART\\OVRLY\\00ATLANT.TIM";
static const char sWves3rd[] = "WVES\\3RD.WVE";
static const char sWves2nd[] = "WVES\\2ND.WVE";
static const char sWves1st[] = "WVES\\1ST.WVE";
static const char sWvesHs[] = "WVES\\HS.WVE";
static const char sWvesSfs[] = "WVES\\SFS.WVE";
