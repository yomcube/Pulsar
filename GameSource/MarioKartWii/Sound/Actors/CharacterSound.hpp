#ifndef _CHARACTERSOUND_
#define _CHARACTERSOUND_
#include <kamek.hpp>
#include <MarioKartWii/Race/RaceData.hpp>
#include <MarioKartWii/Sound/Other/RandomAudioMgr.hpp>
#include <MarioKartWii/Sound/Actors/RaceActor.hpp>

using namespace nw4r;
class DriverController;
enum CharacterSoundType {
    CHARACTER_SOUND_USE_ITEM = 0x0,
    CHARACTER_SOUND_THROW_ITEM = 0x1,
    CHARACTER_SOUND_USE_STAR_MEGA = 0x2,
    CHARACTER_SOUND_HIT_ITEM = 0x3,
    CHARACTER_SOUND_BOOST = 0x6,
    CHARACTER_SOUND_NO_STUNTTRICK = 0x8, //when you don't trick on a trickable surface
    CHARACTER_SOUND_NO_FLIPTRICK = 0xA, //when you don't trick off a boost ramp
    CHARACTER_SOUND_STUNT_1FLIP = 0xB,
    CHARACTER_SOUND_2FLIPS = 0xC,
    CHARACTER_SOUND_NO_FLIP_LANDING = 0xD, //from landing without tricking
    CHARACTER_SOUND_WHEELIE = 0xf,
    CHARACTER_SOUND_WHEELIE_LOW_SPEED = 0x10,
    CHARACTER_SOUND_HIT_WALL = 0x11,
    CHARACTER_SOUND_HITBY_OBJECT = 0x12,
    CHARACTER_SOUND_HITBY_EXPLOSION = 0x13,
    CHARACTER_SOUND_HITBY_FIRE = 0x14,
    CHARACTER_SOUND_HITBY_BANANA = 0x15,
    CHARACTER_SOUND_RESPAWN = 0x1A,
    CHARACTER_SOUND_DRAFT = 0x1C
};

class CharacterSound;
class RandomCharacterSoundPicker : public RandomSoundPicker { //one per type
    RandomCharacterSoundPicker(); //808676e0
    ~RandomCharacterSoundPicker() override; //808639e8 vtable 808dbe18
    CharacterSound* sound; //2c
}; //0x30

class CharacterSound : public RaceAnimAudioActor {
    CharacterSound(); //80863928

    //AUDIOACTOR
    //SoundActor vtable 808dbbf0
    ~CharacterSound() override; //80866c08
    //AudioActor vtable 808dbc0c
    //~CharacterSound thunk 80866d0c func 80866c08

    //LinkedRaceActor vtable 808dbc6c at 0x94 
    void Link(void* pointer, u16 objectId) override; //thunk 80866d3c func 80863a9c pointer is KartModel
    void Unlink() override; //thunk 80866d34 func 80863ff8
    void Update() override; //thunk 80866d2c func 80864000
    bool StartSound(u32 soundId) override; //40 thunk 80866d24 func 80865618
    bool HoldSound(u32 soundId) override; //44 thunk 80866d1c func 808656c4
    void StopSound(int fadeOutFrames) override; //4c thunk 80866d14 func 80855984

    void PlayCharacterSound(CharacterSoundType type); //80864914
    void PlayCharacterSoundConditional(CharacterSoundType type); //808646f0, conditional to prevent too much overlapping
    //big switch depending on type to then call PlayCharacterSound
    void PlayCharacterCollisionSound(DamageType type); //80865448
    u32 GetCharacterGroupId(); //80866388
    u32 GetCharacterCannonGroupId(); //80866404

    CharacterSoundType requestedType; //0xFC can be used to request but can also just call 808646f0
    u32 delay; //0x100 if request, delay until request is executed
    u8 unknown_0x104[0x150 - 0x104];
    RandomCharacterSoundPicker randomSoundPickers[0x1D]; //0x150 use type enum
    DriverController* model; //0x6c0
    u32 wiiRemoteChannelx2; //0x6c4 only if controller is wheel/nunchuck ofc
    CharacterSoundType prevType; //0x6c8
    u32 unknown_0x6CC[4];
    u8 unknown_0x6dc[0x6e4 - 0x6dc];
    float unknown_0x6e4;
    Team team; //0x6e8
    u8 playerId; //0x6ec only if not a ghost
    u8 hudSlotId; //0x6ed same
    u8 padding;
    u32 unkwown_0x6f0[2];
    u8 unknown_0x6f8;
    bool isNotLocal; //0x6f9
    bool isLocal; //0x6fa
    bool isMii; //0x6fb
    bool isGhost; //0x6fc
    bool isReplay; //0x6fd
    u8 unknown_0x6fe;
    bool unknown_0x6ff;
    u8 unknown_0x700[8];
    static u32 charactersGroupIds[24]; //808afb58
}; //0x708
size_assert(CharacterSound, 0x708);
#endif