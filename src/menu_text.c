/* Retail .rodata between the jump tables of scene.c and memory_card.c:
 * menu and message text, referenced only through the pointer tables in .data.
 * The block has no code of its own, so it is a data-only translation unit.
 * The `*` suffixes and the control-glyph characters belong to the text. */
#include "common.h"

const char gMenuCreditsStar[] = "CREDITS*";
static const char sMenuNascarOptionsStar[] = "NASCAR OPTIONS*";
static const char sMenuGameOptionsStar[] = "GAME OPTIONS*";
static const char sMenuDriverInfoStar[] = "DRIVER INFO*";
static const char sMenuChampionshipSeasonStar[] = "CHAMPIONSHIP SEASON*";
static const char sMenuSingleRaceStar[] = "SINGLE RACE*";
static const char sMenuMainMenu[] = "MAIN MENU";
static const char sMenuComputerCarsOnStar[] = "COMPUTER CARS ON*";
static const char sMenuSpeedCompOnStar[] = "SPEED COMP ON*";
static const char sMenuSelectTrackStar[] = "SELECT TRACK*";
static const char sMenuSelectCarStar[] = "SELECT CAR*";
static const char sMenuOnePlayerStar[] = "ONE PLAYER*";
static const char sMenuRaceSetup[] = "RACE SETUP";
static const char sMenuComputerCarsOffStar[] = "COMPUTER CARS OFF*";
static const char sMenuSpeedCompOffStar[] = "SPEED COMP OFF*";
static const char sMenuSelectCarsStar[] = "SELECT CARS*";
static const char sMenuTwoPlayersStar[] = "TWO PLAYERS*";
static const char sMenuExitSeasonStar[] = "EXIT SEASON*";
static const char sMenuNextRaceStar[] = "NEXT RACE*";
static const char sMenuViewStandingsStar[] = "VIEW STANDINGS*";
static const char sMenuViewSeasonInfoStar[] = "VIEW SEASON INFO*";
static const char sMenuSaveSeasonStar[] = "SAVE SEASON*";
static const char sMenuLoadSeasonStar[] = "LOAD SEASON*";
static const char sMenuNewSeasonStar[] = "NEW SEASON*";
static const char sMenuSeasonMenu[] = "SEASON MENU";
static const char sMenuTurboModeOnStar[] = "TURBO MODE ON*";
static const char sMenuSoundFxVolumeStar[] = "SOUND FX VOLUME*";
static const char sMenuCdVolumeStar[] = "CD VOLUME*";
static const char sMenuControllerSetupStar[] = "CONTROLLER SETUP*";
static const char sMenuGameOptions[] = "GAME OPTIONS";
static const char sMenuTurboModeOffStar[] = "TURBO MODE OFF*";
static const char sMenuAnnouncerVolumeStar[] = "ANNOUNCER VOLUME*";
static const char sMenuPhysicsAiSettingsStar[] = "PHYSICS/AI SETTINGS*";
static const char sMenuTimeDisplayOnStar[] = "TIME DISPLAY ON*";
static const char sMenuBestLineOnStar[] = "BEST LINE ON*";
static const char sMenuBreakdownOnStar[] = "BREAKDOWN ON*";
static const char sMenuYellowFlagOnStar[] = "YELLOW FLAG ON*";
static const char sMenuDamageOnStar[] = "DAMAGE ON*";
static const char sMenuRaceLength[] = "RACE LENGTH:";
static const char sMenuNascarOptions[] = "NASCAR OPTIONS";
static const char sMenuTimeDisplayOffStar[] = "TIME DISPLAY OFF*";
static const char sMenuBestLineOffStar[] = "BEST LINE OFF*";
static const char sMenuBreakdownOffStar[] = "BREAKDOWN OFF*";
static const char sMenuYellowFlagOffStar[] = "YELLOW FLAG OFF*";
static const char sMenuDamageOffStar[] = "DAMAGE OFF*";
static const char sMenuDamageLtdStar[] = "DAMAGE LTD*";
static const char sMenuSpeedSensitiveSteering[] = "SPEED-SENSITIVE STEERING:";
static const char sMenuCarBalanceEffect[] = "CAR BALANCE EFFECT:";
static const char sMenuHorsepower[] = "HORSEPOWER:";
static const char sMenuDraftingEffect[] = "DRAFTING EFFECT:";
static const char sMenuOpponentStrength[] = "OPPONENT STRENGTH:";
static const char sMenuSettingsArcadeStar[] = "SETTINGS: ARCADE*";
static const char sMenuPhysicsAiSettings[] = "PHYSICS/AI SETTINGS";
static const char sMenuSettingsSimulationStar[] = "SETTINGS: SIMULATION*";
static const char sMenuSettingsCustomStar[] = "SETTINGS: CUSTOM*";
static const char sMenuToMainMenuStar[] = "TO MAIN MENU*";
static const char sMenuViewRecordsStar[] = "VIEW RECORDS*";
static const char sMenuQualifyStar[] = "QUALIFY*";
static const char sMenuPracticeStar[] = "PRACTICE*";
static const char sMenuCarSetupStar[] = "CAR SETUP*";
static const char sMenuRaceSetupStar[] = "RACE SETUP*";
static const char sMenuSingleRaceWeekend[] = "SINGLE RACE WEEKEND";
static const char sMenuToSeasonMenuStar[] = "TO SEASON MENU*";
static const char sMenuRaceWeekend[] = "RACE WEEKEND";
static const char sMenuSeasonSetup[] = "SEASON SETUP";
static const char sMenuGearRatiosStar[] = "GEAR RATIOS*";
static const char sMenuRearSpoilerStar[] = "REAR SPOILER*";
static const char sMenuAutoTransStar[] = "AUTO TRANS*";
static const char sMenuCarSetup[] = "CAR SETUP";
static const char sMenuManualTransStar[] = "MANUAL TRANS*";
static const char sMenuHighEnd[] = "High end";
static const char sMenuAcceleration[] = "Acceleration";
static const char sMenuOversteer[] = "Oversteer";
static const char sMenuDownforce[] = "Downforce";
static const char sMenuPressure[] = "Pressure";
static const char sMenuPlayer2[] = "Player 2";
static const char sMenuPlayer1[] = "Player 1";
static const char sMenuPitDistance[] = "Pit Distance";
static const char sMenuHandling[] = "Handling";
static const char sMenuTopSpeed[] = "Top Speed";
static const char sMenuAnnouncerVol[] = "Announcer Vol";
static const char sMenuSoundFxVolume[] = "Sound FX Volume";
static const char sMenuCdVolume[] = "CD Volume";
static const char sMenuDevelopmentStar[] = "DEVELOPMENT*";
static const char sMenuProductionStar[] = "PRODUCTION*";
static const char sMenuPressXToExitTo[] = "Press X to exit, }~ to change";
static const char sMenuXSaveClearToChangeText[] =
    "X = save, ^ = clear, `{}~ to change, \\ = cancel";
static const char sMenuPressXToSelectToText[] =
    "Press X to select, `{ to change, \\ to cancel";
static const char sMenuPressXToExitTo2[] = "Press X to exit, `{ to scroll";
static const char sMenuPressXToExit[] = "Press X to exit";
static const char sMenuPressXToSelectToText2[] =
    "Press X to select, }~ to change, \\ to cancel";
static const char sMenuPressXToSelectTo[] = "Press X to select, }~ to change";
static const char sMenuPressXToSelect[] = "Press X to select";
static const char sMenuPressIToExitTo[] = "Press I to exit, }~ to change";
static const char sMenuISaveClearToChangeText[] =
    "I = save, ^ = clear, `{ }~ to change, II = cancel";
static const char sMenuPressIToSelectToText[] =
    "Press I to select, `{ to change, II to cancel";
static const char sMenuPressIToExitTo2[] = "Press I to exit, `{ to scroll";
static const char sMenuPressIToExit[] = "Press I to exit";
static const char sMenuPressIToSelectToText2[] =
    "Press I to select, }~ to change, II to cancel";
static const char sMenuPressIToSelectTo[] = "Press I to select, }~ to change";
static const char sMenuPressIToSelect[] = "Press I to select";
static const char sMenuTurboModeOn[] = "TURBO MODE ON";
static const char sMenuRanchTower[] = "Ranch Tower";
static const char sMenuTalladega[] = "Talladega";
static const char sMenuCedarWoods[] = "Cedar Woods";
static const char sMenuWatkinsGlen[] = "Watkins Glen";
static const char sMenuWillowLane[] = "Willow Lane";
static const char sMenuCalifornia[] = "California";
static const char sMenuMichigan[] = "Michigan";
static const char sMenuPineRidge[] = "Pine Ridge";
static const char sMenuCharlotte[] = "Charlotte";
static const char sMenuSearsPoint[] = "Sears Point";
static const char sMenuSaltBasin[] = "Salt Basin";
static const char sMenuSuzukaCircuit[] = "Suzuka Circuit";
static const char sMenuRanchTowerRaceway[] = "Ranch Tower Raceway";
static const char sMenuTalladegaSuperspeedway[] = "Talladega Superspeedway";
static const char sMenuCedarWoodsRaceway[] = "Cedar Woods Raceway";
static const char sMenuWatkinsGlenInternational[] =
    "Watkins Glen International";
static const char sMenuPoconoRaceway[] = "Pocono Raceway";
static const char sMenuWillowLaneRaceway[] = "Willow Lane Raceway";
static const char sMenuCaliforniaSpeedway[] = "California Speedway";
static const char sMenuMichiganSpeedway[] = "Michigan Speedway";
static const char sMenuPineRidgeRaceway[] = "Pine Ridge Raceway";
static const char sMenuCharlotteMotorSpeedway[] = "Charlotte Motor Speedway";
static const char sMenuSearsPointRaceway[] = "Sears Point Raceway";
static const char sMenuSaltBasinRaceway[] = "Salt Basin Raceway";
static const char sMenuBristolMotorSpeedway[] = "Bristol Motor Speedway";
static const char sMenuTexasMotorSpeedway[] = "Texas Motor Speedway";
static const char sMenuBelmontInternationalRaceway[] =
    "Belmont International Raceway";
static const char sMenuAtlantaMotorSpeedway[] = "Atlanta Motor Speedway";
static const char sMenuNascarSuzukaThunderSpecial100[] =
    "NASCAR Suzuka Thunder Special 100";
static const char sMenuDustbowl500[] = "Dustbowl 500";
static const char sMenuSearsDieHard500[] = "Sears Die Hard 500";
static const char sMenuCyclone300[] = "Cyclone 300";
static const char sMenuTheRaceAtTheGlen[] = "The Race at the Glen";
static const char sMenuPennsylvania500[] = "Pennsylvania 500";
static const char sMenuPressStart300[] = "Press Start 300";
static const char sMenuNapaSCalifornia500[] = "NAPA's California 500";
static const char sMenuMills400[] = "Mills 400";
static const char sMenuStormfront400[] = "Stormfront 400";
static const char sMenuCocaCola600[] = "Coca-Cola 600";
static const char sMenuSaveMart300[] = "Save Mart 300";
static const char sMenuSaltFlat400[] = "Salt Flat 400";
static const char sMenuFoodCity500[] = "Food City 500";
static const char sMenuInterstateBatteries500[] = "Interstate Batteries 500";
static const char sMenuEaSports500[] = "EA Sports 500";
static const char sMenuPrimestar500[] = "Primestar 500";
static const char sMenuProvisional[] = "Provisional";
static const char sMenuPressStart[] = "Press Start";
static const char sMenuPosition[] = "Position";
static const char sMenuProvisionalGrid[] = "Provisional Grid";
static const char sMenuPressStartToQualify[] = "Press Start to Qualify";
static const char sMenuPressStartToPractice[] = "Press Start to Practice";
static const char sMenuRoadCourse[] = "Road Course";
static const char sMenuTrackSize[] = "Track Size: ";
static const char sMenuTrackType[] = "Track Type: ";
static const char sMenuLoading[] = "Loading...";
static const char sMenuEaSportsNascarChallenge[] = "EA Sports NASCAR Challenge";
static const char sMenuPressStartToRace[] = "Press Start to Race";
static const char sMenuStartingGrid[] = "Starting Grid";
static const char sMenu1390Miles2238[] = "1.390 Miles/2.238 Km";
static const char sMenu2184Miles3516[] = "2.184 Miles/3.516 Km";
static const char sMenu266Miles4282[] = "2.66 Miles/4.282 Km";
static const char sMenu2181Miles3511[] = "2.181 Miles/3.511 Km";
static const char sMenu245Miles3445[] = "2.45 Miles/3.445 Km";
static const char sMenu25Miles4025[] = "2.5 Miles/4.025 Km";
static const char sMenu2166Miles3487[] = "2.166 Miles/3.487 Km";
static const char sMenu20Miles322[] = "2.0 Miles/3.22 Km";
static const char sMenu2167Miles3488[] = "2.167 Miles/3.488 Km";
static const char sMenu252Miles4057[] = "2.52 Miles/4.057 Km";
static const char sMenu2180Miles3509[] = "2.180 Miles/3.509 Km";
static const char sMenu0533Mile0858[] = "0.533 Mile/0.858 Km";
static const char sMenu15Miles2415[] = "1.5 Miles/2.415 Km";
static const char sMenu1594Miles2566[] = "1.594 Miles/2.566 Km";
static const char sMenu1522Miles2451[] = "1.522 Miles/2.451 Km";
static const char sMenuSeasonHasNotYetBegun[] = "Season has not yet begun";
static const char sMenuChampionshipStandings[] = "Championship Standings";
static const char sMenuNoRecordsAvailable[] = "No Records Available";
static const char sMenuBestLap[] = "Best Lap";
static const char sMenuRecordsSetFor[] = "Records Set for ";
static const char sMenuFinishes[] = "Finishes";
static const char sMenuTop10Finishes[] = "Top 10 Finishes";
static const char sMenuTop5Finishes[] = "Top 5 Finishes";
static const char sMenuSSeasonInfo[] = "'s Season Info";
static const char sMenuSelectSlot[] = "Select Slot";
static const char sMenuNewSeason[] = "New Season";
static const char sMenuCancelQualify[] = "Cancel Qualify";
static const char sMenuExitSeason[] = "Exit Season";
static const char sMenuLoadSeason[] = "Load Season";
static const char sMenuSaveSeason[] = "Save Season";
static const char sMenuAccelBrake[] = "Accel/Brake";
static const char sMenuSteerLeftRight[] = "Steer Left/Right";
static const char sMenuSteerRight[] = "Steer Right";
static const char sMenuSteerLeft[] = "Steer left";
static const char sMenuAccelerate[] = "Accelerate";
static const char sMenuChangeView[] = "Change View";
static const char sMenuSteerRight2[] = "Steer right";
static const char sMenuDownshift[] = "Downshift";
static const char sMenuMenuControl[] = "menu control";
static const char sMenuToggleDisplay[] = "Toggle Display";
static const char sMenuMemoryCardInSlot2Text[] =
    "Memory card in \nSlot 2 is full.\nPlease free up a \n"
    "slot if you want\nto save. \nPress X to exit";
static const char sMenuMemoryCardInSlot1Text[] =
    "Memory card in \nSlot 1 is full.\nPlease free up a \n"
    "slot if you want\nto save. \nPress X to exit";
static const char sMenuMemoryCardInSlot2Text2[] =
    "Memory card in \nSlot 2 is full.\nPlease free up a \n"
    "slot if you want\nexhibition stats\nsaved. \nPress X to exit";
static const char sMenuMemoryCardInSlot1Text2[] =
    "Memory card in \nSlot 1 is full.\nPlease free up a \n"
    "slot if you want\nexhibition stats\nsaved. \nPress X to exit";
static const char sMenuPleaseInsertMemoryCardIfText[] =
    "Please insert \nmemory card if \nyou want \nexhibition stats \n"
    "saved. \nPress X to exit";
static const char sMenuMemoryCardInSlot2Text3[] =
    "Memory Card \nin slot 2\nis unformatted.  \nPress \\ to format, \n"
    "X to cancel";
static const char sMenuMemoryCardInSlot1Text3[] =
    "Memory Card \nin slot 1\nis unformatted.  \nPress \\ to format, \n"
    "X to cancel";
static const char sMenuAllPreviouslyUnsavedDataWillText[] =
    "All previously \nunsaved data \nwill be lost.\nAre you sure you \n"
    "want to begin a\nnew season? \nX=Yes, \\= No";
static const char sMenuAllPreviouslyUnsavedDataWillText2[] =
    "All previously \nunsaved data \nwill be lost.\nAre you sure you \n"
    "want to load?\nX = Yes, \\= No";
static const char sMenuYouWillLoseYourQualifyingText[] =
    "You will lose your \nqualifying position.\nAre you sure you\n"
    "want to exit?\nX = Yes, \\ = No";
static const char sMenuAreYouSureYouWantText[] =
    "Are you sure \nyou want to end \nthe season? \nX = Yes, \\ = No";
static const char sMenuNoPreviouslySavedSeason[] =
    "No previously \nsaved season";
static const char sMenuMemoryCardSuccessfullyFormattedPressText[] =
    "Memory card \nsuccessfully \nformatted. \nPress X to exit";
static const char sMenuSeasonSuccessfullyLoaded[] =
    "Season successfully \nloaded";
static const char sMenuSeasonSuccessfullySaved[] =
    "Season successfully \nsaved";
static const char sMenuSaveOverAPreviouslySavedText[] =
    "Save over a \npreviously \nsaved season? \nX = Yes, \\ = No";
static const char sMenuCardInSlotHasBeenText[] =
    "Card in slot \nhas been replaced. \nPress X to exit.";
static const char sMenuUnableToAllocateLoadSave[] =
    "Unable to allocate \nload/save buffer";
static const char sMenuMemoryCardIsUnformattedPressText[] =
    "Memory Card \nis unformatted.  \nPress \\ to format, \nX to cancel";
static const char sMenuUnableToDeleteCorruptFile[] =
    "Unable to delete \ncorrupt file";
static const char sMenuDataInPreviouslySavedFileText[] =
    "Data in previously saved \nfile is corrupt";
static const char sMenuUnableToFindSavedFile[] = "Unable to find \nsaved file";
static const char sMenuUnableToCreateTemporaryBuffer[] =
    "Unable to create \ntemporary buffer";
static const char sMenuUnableToWriteToCard[] = "Unable to write \nto card";
static const char sMenuUnableToReadFromCard[] = "Unable to read \nfrom card";
static const char sMenuUnableToOpenFile[] = "Unable to open file";
static const char sMenuUnableToCreateFileCardText[] =
    "Unable to create \nfile.  Card may \nbe full";
static const char sMenuErrorOccurredWhileTryingToText[] =
    "Error occurred while \ntrying to format.\n Press X to exit";
static const char sMenuErrorOccurredWhileCheckingForText[] =
    "Error occurred while \nchecking for format";
static const char sMenuMemoryCardNotPresent[] = "Memory card \nnot present";
static const char sMenuErrorOccurredWhileCheckingFor[] =
    "Error occurred while \nchecking for card";
static const char sMenuNoError[] = "No Error";
static const char sMenuMemoryCardInSlot2Text4[] =
    "Memory card in \nSlot 2 is full.\nPlease free up a \n"
    "slot if you want\nto save. \nPress I to exit";
static const char sMenuMemoryCardInSlot2Text5[] =
    "Memory card in \nSlot 2 is full.\nPlease free up a \n"
    "slot if you want\nexhibition stats\nsaved. \n"
    "Press I to exitMemory card in \nSlot 1 is full.\nPlease free up a \n"
    "slot if you want\nto save. \nPress I to exit";
static const char sMenuMemoryCardInSlot1Text4[] =
    "Memory card in \nSlot 1 is full.\nPlease free up a \n"
    "slot if you want\nexhibition stats\nsaved. \nPress I to exit";
static const char sMenuPleaseInsertMemoryCardIfText2[] =
    "Please insert \nmemory card if \nyou want \nexhibition stats \n"
    "saved. \nPress I to exit";
static const char sMenuMemoryCardInSlot2Text6[] =
    "Memory Card \nin slot 2\nis unformatted.  \nPress II to format, \n"
    "I to cancel";
static const char sMenuMemoryCardInSlot1Text5[] =
    "Memory Card \nin slot 1\nis unformatted.  \nPress II to format, \n"
    "I to cancel";
static const char sMenuAllPreviouslyUnsavedDataWillText3[] =
    "All previously \nunsaved data \nwill be lost.\nAre you sure you \n"
    "want to begin a\nnew season? \nI=Yes, II= No";
static const char sMenuAllPreviouslyUnsavedDataWillText4[] =
    "All previously \nunsaved data \nwill be lost.\nAre you sure you \n"
    "want to load?\nI = Yes, II = No";
static const char sMenuYouWillLoseYourQualifyingText2[] =
    "You will lose your \nqualifying position.\nAre you sure you\n"
    "want to exit?\nI = Yes, II = No";
static const char sMenuAreYouSureYouWantText2[] =
    "Are you sure \nyou want to end \nthe season? \nI = Yes, II = No";
static const char sMenuMemoryCardSuccessfullyFormattedPressText2[] =
    "Memory card \nsuccessfully \nformatted. \nPress I to exit";
static const char sMenuSaveOverAPreviouslySavedText2[] =
    "Save over a \npreviously \nsaved season? \nI = Yes, II = No";
static const char sMenuCardInSlotHasBeenText2[] =
    "Card in slot \nhas been replaced. \nPress I to exit.";
static const char sMenuMemoryCardIsUnformattedPressText2[] =
    "Memory Card \nis unformatted.  \nPress II \nto format, \nI to cancel";
static const char sMenuErrorOccurredWhileTryingToText2[] =
    "Error occurred while \ntrying to format.\n Press I to exit";
static const char sMenuSteering[] = "Steering";
static const char sMenuToCalibrateTheSteeringMoveText[] =
    "To calibrate the steering, move the left \n"
    "joystick left and right several times.\n"
    "To calibrate acceleration and braking, move \n"
    "the right joystick up and down several times.\n"
    "Release both joysticks and press Start \nwhen done.";
static const char sMenuToCalibrateTheNegconTwistText[] =
    "To calibrate the NeGcon, twist the controller \n"
    "in each direction several times.\n"
    "To calibrate the buttons, press each of \n"
    "the red buttons several times.\n"
    "Release all and press Start when done.";
static const char sMenuToCalibrateTheSteeringWheelText[] =
    "To calibrate the steering wheel, turn the \n"
    "wheel in each direction several times.\n"
    "To calibrate the pedals, push down on \neach pedal several times.\n"
    "Release all and press Start when done.";
static const char sMenuToSwitchConfigurationsStartToText[] =
    "}~ to switch configurations, Start to exit.";
static const char sMenuControllerSetup[] = "CONTROLLER SETUP";
static const char sMenuChadLittle[] = "Chad Little";
static const char sMenuJeremyMayfield[] = "Jeremy Mayfield";
static const char sMenuMichaelWaltrip[] = "Michael Waltrip";
static const char sMenuWardBurton[] = "Ward Burton";
static const char sMenuGeoffBodine[] = "Geoff Bodine";
static const char sMenuKylePetty[] = "Kyle Petty";
static const char sMenuRickyCraven[] = "Ricky Craven";
static const char sMenuJeffBurton[] = "Jeff Burton";
static const char sMenuErnieIrvan[] = "Ernie Irvan";
static const char sMenuRustyWallace[] = "Rusty Wallace";
static const char sMenuDaleEarnhardt[] = "Dale Earnhardt";
static const char sMenuBillElliott[] = "Bill Elliott";
static const char sMenuJohnAndretti[] = "John Andretti";
static const char sMenuTedMusgrave[] = "Ted Musgrave";
static const char sMenuHutStricklin[] = "Hut Stricklin";
static const char sMenuDaleJarrett[] = "Dale Jarrett";
static const char sMenuJohnnyBenson[] = "Johnny Benson";
static const char sMenuDavidGreen[] = "David Green";
static const char sMenuMikeSkinner[] = "Mike Skinner";
static const char sMenuBobbyLabonte[] = "Bobby Labonte";
static const char sMenuMarkMartin[] = "Mark Martin";
static const char sMenuSterlingMarlin[] = "Sterling Marlin";
static const char sMenuKennyWallace[] = "Kenny Wallace";
static const char sMenuTerryLabonte[] = "Terry Labonte";
static const char sMenuJeffGordon[] = "Jeff Gordon";
static const char sMenuJMayfield[] = "J. Mayfield";
static const char sMenuMWaltrip[] = "M. Waltrip";
static const char sMenuWBurton[] = "W. Burton";
static const char sMenuGBodine[] = "G. Bodine";
static const char sMenuKPetty[] = "K. Petty";
static const char sMenuRCraven[] = "R. Craven";
static const char sMenuJBurton[] = "J. Burton";
static const char sMenuEIrvan[] = "E. Irvan";
static const char sMenuRWallace[] = "R. Wallace";
static const char sMenuDEarnhardt[] = "D. Earnhardt";
static const char sMenuBElliott[] = "B. Elliott";
static const char sMenuJAndretti[] = "J. Andretti";
static const char sMenuTMusgrave[] = "T. Musgrave";
static const char sMenuHStricklin[] = "H. Stricklin";
static const char sMenuDJarrett[] = "D. Jarrett";
static const char sMenuJBenson[] = "J. Benson";
static const char sMenuDGreen[] = "D. Green";
static const char sMenuMSkinner[] = "M. Skinner";
static const char sMenuBLabonte[] = "B. Labonte";
static const char sMenuMMartin[] = "M. Martin";
static const char sMenuSMarlin[] = "S. Marlin";
static const char sMenuKWallace[] = "K. Wallace";
static const char sMenuTLabonte[] = "T. Labonte";
static const char sMenuJGordon[] = "J. Gordon";
static const char sMenuDevelopmentTeamCredits[] = "Development Team Credits";
static const char sMenuProductionTeamCredits[] = "Production Team Credits";
static const char sMenuQuitPractice[] = "QUIT PRACTICE";
static const char sMenuPracticeStats[] = "PRACTICE STATS";
static const char sMenuResumePractice[] = "RESUME PRACTICE";
static const char sMenuQuitQualifying[] = "QUIT QUALIFYING";
static const char sMenuQualifyingStats[] = "QUALIFYING STATS";
static const char sMenuResumeQualifying[] = "RESUME QUALIFYING";
static const char sMenuQuitRace[] = "QUIT RACE";
static const char sMenuSoundOptions[] = "SOUND OPTIONS";
static const char sMenuNascarTiming[] = "NASCAR TIMING";
static const char sMenuRaceStatistics[] = "RACE STATISTICS";
static const char sMenuInstantReplay[] = "INSTANT REPLAY";
static const char sMenuResumeRace[] = "RESUME RACE";
static const char sMenuChannels[] = "CHANNELS:";
static const char sMenuAnnouncer[] = "ANNOUNCER:";
static const char sMenuSoundEffects[] = "SOUND EFFECTS:";
static const char sMenuAreYouSure[] = "ARE YOU SURE?";
static const char sMenuOutOfRace[] = "OUT OF RACE";
static const char sMenuLowFuel[] = "LOW FUEL";
static const char sMenuQualifyingResults[] = "Qualifying Results";
static const char sMenuRaceResults[] = "Race Results";
static const char sMenuWrongWay[] = "WRONG WAY";
static const char sMenuOutOfFuel[] = "OUT OF FUEL";
static const char sMenuTiresWorn[] = "TIRES WORN";
static const char sMenuPressGasToResume[] = "PRESS GAS TO RESUME";
static const char sMenuBestLap2[] = "BEST LAP";
static const char sMenuLapTime[] = "LAP TIME";
static const char sMenuTimeDifferential[] = "TIME DIFFERENTIAL";
static const char sMenuDemoMode[] = "DEMO MODE";
static const char sMenuRearSpoiler[] = "REAR SPOILER:";
static const char sMenuChangeTires[] = "CHANGE TIRES";
static const char sMenuRearSpoiler2[] = "REAR SPOILER: ";
static const char sMenuNascarTimingScoring[] = "NASCAR Timing & Scoring";
static const char sMenu3rdBestLap[] = "3RD BEST LAP";
static const char sMenu2ndBestLap[] = "2ND BEST LAP";
/* Retail ends this block with one zero word, ahead of memory_card.c's first
 * jump table. No code reads it. */
asm(".rdata\n.long 0\n.text");
