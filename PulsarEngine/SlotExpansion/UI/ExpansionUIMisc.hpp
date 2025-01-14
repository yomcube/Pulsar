#ifndef _EXPANSIONUIMISC_
#define _EXPANSIONUIMISC_
#include <kamek.hpp>
#include <MarioKartWii/System/Identifiers.hpp>
#include <PulsarSystem.hpp>
#include <UI/UI.hpp>

namespace Pulsar {
namespace UI {
int GetTrackBMGId(PulsarId pulsarId);

inline void GetTrackBMG(wchar_t* dest, PulsarId id) {
    const wchar_t* name = UI::GetCustomMsg(GetTrackBMGId(id));
    const wchar_t* ptrSlash = wcschr(name, L'\\');

    int realLength;
    if(ptrSlash == nullptr) realLength = wcslen(name);
    else {
        const wchar_t* ptrSpace = wcschr(name, L'\\') - sizeof(L' ');
        realLength = (ptrSpace - name) / sizeof(wchar_t);
    }
    if(realLength < 0x100) {
        dest[realLength] = L'\0';
        wcsncpy(dest, name, realLength);
    }
    else dest[0] = L'\0';


}
int GetTrackBMGByRowIdx(u32 cupTrackIdx);
int GetCurTrackBMG();
}//namespace UI
}//namespace Pulsar
#endif