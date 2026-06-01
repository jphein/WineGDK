/*
 * Copyright 2024 Rémi Bernon for CodeWeavers
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#include "initguid.h"
#include "private.h"

#include <time.h>

#include "inputdevice.h"
#include "mouinput.h"
#include "inputreading.h"

WINE_DEFAULT_DEBUG_CHANNEL(ginput);

HINSTANCE game_input;

struct game_input
{
    v0_IGameInput v0_IGameInput_iface;
    v1_IGameInput v1_IGameInput_iface;
    v2_IGameInput v2_IGameInput_iface;

    LONG ref;
};

static inline struct game_input *impl_from_v0_IGameInput( v0_IGameInput *iface )
{
    return CONTAINING_RECORD( iface, struct game_input, v0_IGameInput_iface );
}

static HRESULT WINAPI game_input_QueryInterface( v0_IGameInput *iface, REFIID iid, void **out )
{
    struct game_input *impl = impl_from_v0_IGameInput( iface );

    TRACE( "iface %p, iid %s, out %p.\n", iface, debugstr_guid( iid ), out );

    if (IsEqualGUID( iid, &IID_IUnknown ) ||
        IsEqualGUID( iid, &IID_IAgileObject ) ||
        IsEqualGUID( iid, &IID_v0_IGameInput ))
    {
        *out = &impl->v0_IGameInput_iface;
        impl->ref++;
        return S_OK;
    }

    if (IsEqualGUID( iid, &IID_v1_IGameInput ))
    {
        *out = &impl->v1_IGameInput_iface;
        impl->ref++;
        return S_OK;
    }

    if (IsEqualGUID( iid, &IID_v2_IGameInput ))
    {
        *out = &impl->v2_IGameInput_iface;
        impl->ref++;
        return S_OK;
    }


    FIXME( "%s not implemented, returning E_NOINTERFACE.\n", debugstr_guid( iid ) );
    *out = NULL;
    return E_NOINTERFACE;
}

static ULONG WINAPI game_input_AddRef( v0_IGameInput *iface )
{
    struct game_input *impl = impl_from_v0_IGameInput( iface );
    ULONG ref = InterlockedIncrement( &impl->ref );
    TRACE( "iface %p increasing refcount to %lu.\n", iface, ref );
    return ref;
}

static ULONG WINAPI game_input_Release( v0_IGameInput *iface )
{
    struct game_input *impl = impl_from_v0_IGameInput( iface );
    ULONG ref = InterlockedDecrement( &impl->ref );
    TRACE( "iface %p decreasing refcount to %lu.\n", iface, ref );
    return ref;
}

static uint64_t WINAPI game_input_GetCurrentTimestamp( v0_IGameInput *iface )
{
    FIXME( "iface %p, stub GetCurrentTimestamp.\n", iface );
    return (uint64_t)0;
}

static HRESULT WINAPI game_input_GetCurrentReading( v0_IGameInput *iface, GameInputKind kind,
                                                   v0_IGameInputDevice *device, v0_IGameInputReading **reading )
{
    FIXME( "iface %p GetCurrentReading kind=%d device=%p reading_out=%p\n", iface, (int)kind, device, reading );
    if (reading) *reading = NULL;
    return E_NOTIMPL;
}

static HRESULT WINAPI game_input_GetNextReading( v0_IGameInput *iface, v0_IGameInputReading *reference,
                                                 GameInputKind kind, v0_IGameInputDevice *device,
                                                 v0_IGameInputReading **reading )
{
    FIXME( "iface %p GetNextReading reference=%p kind=%d device=%p reading_out=%p\n", iface, reference, (int)kind, device, reading );
    if (reading) *reading = NULL;
    return E_NOTIMPL;
}

static HRESULT WINAPI game_input_GetPreviousReading( v0_IGameInput *iface, v0_IGameInputReading *reference,
                                                     GameInputKind kind, v0_IGameInputDevice *device,
                                                     v0_IGameInputReading **reading )
{
    FIXME( "iface %p GetPreviousReading reference=%p kind=%d device=%p reading_out=%p\n", iface, reference, (int)kind, device, reading );
    if (reading) *reading = NULL;
    return E_NOTIMPL;
}

static HRESULT WINAPI game_input_GetTemporalReading( v0_IGameInput *iface, uint64_t timestamp,
                                                    v0_IGameInputDevice *device, v0_IGameInputReading **reading )
{
    FIXME( "iface %p GetTemporalReading timestamp=%llu device=%p reading_out=%p\n", iface, (unsigned long long)timestamp, device, reading );
    if (reading) *reading = NULL;
    return E_NOTIMPL;
}

static HRESULT WINAPI game_input_RegisterReadingCallback( v0_IGameInput *iface, v0_IGameInputDevice *device,
                                                          GameInputKind kind, float threshold, void *context,
                                                          v0_GameInputReadingCallback callback, GameInputCallbackToken *token )
{
    FIXME( "iface %p RegisterReadingCallback device=%p kind=%d threshold=%f callback=%p token_out=%p\n",
           iface, device, (int)kind, threshold, callback, token );
    if (token) *token = (GameInputCallbackToken)0;
    return E_NOTIMPL;
}

static HRESULT WINAPI game_input_RegisterDeviceCallback( v0_IGameInput *iface, v0_IGameInputDevice *device,
                                                         GameInputKind kind, GameInputDeviceStatus filter,
                                                         GameInputEnumerationKind enum_kind, void *context,
                                                         v0_GameInputDeviceCallback callback, GameInputCallbackToken *token )
{
    FIXME( "iface %p RegisterDeviceCallback device=%p kind=%d filter=%d enum_kind=%d callback=%p token_out=%p\n",
           iface, device, (int)kind, (int)filter, (int)enum_kind, callback, token );
    if (token) *token = (GameInputCallbackToken)0;
    return E_NOTIMPL;
}

static HRESULT WINAPI game_input_RegisterSystemButtonCallback( v0_IGameInput *iface, v0_IGameInputDevice *device,
                                                               GameInputSystemButtons filter, void *context,
                                                               v0_GameInputSystemButtonCallback callback, GameInputCallbackToken *token )
{
    FIXME( "iface %p RegisterSystemButtonCallback device=%p filter=%u callback=%p token_out=%p\n",
           iface, device, (unsigned)filter, callback, token );
    if (token) *token = (GameInputCallbackToken)0;
    return E_NOTIMPL;
}

static HRESULT WINAPI game_input_RegisterKeyboardLayoutCallback( v0_IGameInput *iface, v0_IGameInputDevice *device,
                                                                 void *context, v0_GameInputKeyboardLayoutCallback callback,
                                                                 GameInputCallbackToken *token )
{
    FIXME( "iface %p RegisterKeyboardLayoutCallback device=%p callback=%p token_out=%p\n",
           iface, device, callback, token );
    if (token) *token = (GameInputCallbackToken)0;
    return E_NOTIMPL;
}

static void WINAPI game_input_StopCallback( v0_IGameInput *iface, GameInputCallbackToken token )
{
    FIXME( "iface %p StopCallback token=%llu\n", iface, (unsigned long long)token );
    /* no-op stub */
}

static bool WINAPI game_input_UnregisterCallback( v0_IGameInput *iface, GameInputCallbackToken token, uint64_t timeout_ms )
{
    FIXME( "iface %p UnregisterCallback token=%llu timeout_ms=%llu\n", iface, (unsigned long long)token, (unsigned long long)timeout_ms );
    return false;
}

static HRESULT WINAPI game_input_CreateDispatcher( v0_IGameInput *iface, IGameInputDispatcher **dispatcher )
{
    FIXME( "iface %p CreateDispatcher dispatcher_out=%p\n", iface, dispatcher );
    if (dispatcher) *dispatcher = NULL;
    return E_NOTIMPL;
}

static HRESULT WINAPI game_input_CreateAggregateDevice( v0_IGameInput *iface, GameInputKind kind, v0_IGameInputDevice **device )
{
    FIXME( "iface %p CreateAggregateDevice kind=%d device_out=%p\n", iface, (int)kind, device );
    if (device) *device = NULL;
    return E_NOTIMPL;
}

static HRESULT WINAPI game_input_FindDeviceFromId( v0_IGameInput *iface, const APP_LOCAL_DEVICE_ID *value, v0_IGameInputDevice **device )
{
    FIXME( "iface %p FindDeviceFromId value=%p device_out=%p\n", iface, value, device );
    if (device) *device = NULL;
    return E_NOTIMPL;
}

static HRESULT WINAPI game_input_FindDeviceFromObject( v0_IGameInput *iface, IUnknown *value, v0_IGameInputDevice **device )
{
    FIXME( "iface %p FindDeviceFromObject unknown=%p device_out=%p\n", iface, value, device );
    if (device) *device = NULL;
    return E_NOTIMPL;
}

static HRESULT WINAPI game_input_FindDeviceFromPlatformHandle( v0_IGameInput *iface, HANDLE value, v0_IGameInputDevice **device )
{
    FIXME( "iface %p FindDeviceFromPlatformHandle handle=%p device_out=%p\n", iface, value, device );
    if (device) *device = NULL;
    return E_NOTIMPL;
}

static HRESULT WINAPI game_input_FindDeviceFromPlatformString( v0_IGameInput *iface, const WCHAR *value, v0_IGameInputDevice **device )
{
    FIXME( "iface %p FindDeviceFromPlatformString value=%p device_out=%p\n", iface, value, device );
    if (device) *device = NULL;
    return E_NOTIMPL;
}

static HRESULT WINAPI game_input_EnableOemDeviceSupport( v0_IGameInput *iface, uint16_t vid, uint16_t pid,
                                                         uint8_t iface_num, uint8_t collection )
{
    FIXME( "iface %p EnableOemDeviceSupport vid=0x%04x pid=0x%04x iface=%u collection=%u\n",
           iface, (unsigned)vid, (unsigned)pid, (unsigned)iface_num, (unsigned)collection );
    return E_NOTIMPL;
}

static void WINAPI game_input_SetFocusPolicy( v0_IGameInput *iface, GameInputFocusPolicy policy )
{
    FIXME( "iface %p SetFocusPolicy policy=%d\n", iface, (int)policy );
    /* no-op stub */
}

static const struct v0_IGameInputVtbl game_input_vtbl =
{
    /* IUnknown methods */
    game_input_QueryInterface,
    game_input_AddRef,
    game_input_Release,
    /* v0_IGameInput methods */
    game_input_GetCurrentTimestamp,
    game_input_GetCurrentReading,
    game_input_GetNextReading,
    game_input_GetPreviousReading,
    game_input_GetTemporalReading,
    game_input_RegisterReadingCallback,
    game_input_RegisterDeviceCallback,
    game_input_RegisterSystemButtonCallback,
    game_input_RegisterKeyboardLayoutCallback,
    game_input_StopCallback,
    game_input_UnregisterCallback,
    game_input_CreateDispatcher,
    game_input_CreateAggregateDevice,
    game_input_FindDeviceFromId,
    game_input_FindDeviceFromObject,
    game_input_FindDeviceFromPlatformHandle,
    game_input_FindDeviceFromPlatformString,
    game_input_EnableOemDeviceSupport,
    game_input_SetFocusPolicy
};

static inline struct game_input *impl_from_v1_IGameInput( v1_IGameInput *iface )
{
    return CONTAINING_RECORD( iface, struct game_input, v1_IGameInput_iface );
}

static HRESULT WINAPI game_input1_QueryInterface( v1_IGameInput *iface, REFIID iid, void **out )
{
    struct game_input *impl = impl_from_v1_IGameInput( iface );

    TRACE( "iface %p, iid %s, out %p.\n", iface, debugstr_guid( iid ), out );

    if (IsEqualGUID( iid, &IID_IUnknown ) ||
        IsEqualGUID( iid, &IID_IAgileObject ) ||
        IsEqualGUID( iid, &IID_v0_IGameInput ))
    {
        *out = &impl->v0_IGameInput_iface;
        impl->ref++;
        return S_OK;
    }

    if (IsEqualGUID( iid, &IID_v1_IGameInput ))
    {
        *out = &impl->v1_IGameInput_iface;
        impl->ref++;
        return S_OK;
    }

    if (IsEqualGUID( iid, &IID_v2_IGameInput ))
    {
        *out = &impl->v2_IGameInput_iface;
        impl->ref++;
        return S_OK;
    }

    FIXME( "%s not implemented, returning E_NOINTERFACE.\n", debugstr_guid( iid ) );
    *out = NULL;
    return E_NOINTERFACE;
}

static ULONG WINAPI game_input1_AddRef( v1_IGameInput *iface )
{
    struct game_input *impl = impl_from_v1_IGameInput( iface );
    ULONG ref = InterlockedIncrement( &impl->ref );
    TRACE( "iface %p increasing refcount to %lu.\n", iface, ref );
    return ref;
}

static ULONG WINAPI game_input1_Release( v1_IGameInput *iface )
{
    struct game_input *impl = impl_from_v1_IGameInput( iface );
    ULONG ref = InterlockedDecrement( &impl->ref );
    TRACE( "iface %p decreasing refcount to %lu.\n", iface, ref );
    return ref;
};

static uint64_t WINAPI game_input1_GetCurrentTimestamp( v1_IGameInput *iface )
{
    TRACE( "iface %p, stub GetCurrentTimestamp.\n", iface );
    return (uint64_t)0;
}

static HRESULT WINAPI game_input1_GetCurrentReading( v1_IGameInput *iface, GameInputKind kind,
                                                   v1_IGameInputDevice *device, v1_IGameInputReading **reading )
{
    FIXME( "iface %p GetCurrentReading kind=%d device=%p reading_out=%p\n", iface, (int)kind, device, reading );
    if (reading) *reading = NULL;
    return E_NOTIMPL;
}

static HRESULT WINAPI game_input1_GetNextReading( v1_IGameInput *iface, v1_IGameInputReading *reference,
                                                 GameInputKind kind, v1_IGameInputDevice *device,
                                                 v1_IGameInputReading **reading )
{
    FIXME( "iface %p GetNextReading reference=%p kind=%d device=%p reading_out=%p\n", iface, reference, (int)kind, device, reading );
    if (reading) *reading = NULL;
    return E_NOTIMPL;
}

static HRESULT WINAPI game_input1_GetPreviousReading( v1_IGameInput *iface, v1_IGameInputReading *reference,
                                                     GameInputKind kind, v1_IGameInputDevice *device,
                                                     v1_IGameInputReading **reading )
{
    FIXME( "iface %p GetPreviousReading reference=%p kind=%d device=%p reading_out=%p\n", iface, reference, (int)kind, device, reading );
    if (reading) *reading = NULL;
    return E_NOTIMPL;
}

static HRESULT WINAPI game_input1_RegisterReadingCallback( v1_IGameInput *iface, v1_IGameInputDevice *device,
                                                          GameInputKind kind, void *context,
                                                          v1_GameInputReadingCallback callback, GameInputCallbackToken *token )
{
    FIXME( "iface %p RegisterReadingCallback device=%p kind=%d callback=%p token_out=%p\n",
           iface, device, (int)kind, callback, token );
    if (token) *token = (GameInputCallbackToken)0;
    return E_NOTIMPL;
}

static HRESULT WINAPI game_input1_RegisterDeviceCallback( v1_IGameInput *iface, v1_IGameInputDevice *device,
                                                         GameInputKind kind, GameInputDeviceStatus filter,
                                                         GameInputEnumerationKind enum_kind, void *context,
                                                         v1_GameInputDeviceCallback callback, GameInputCallbackToken *token )
{
    FIXME( "iface %p RegisterDeviceCallback device=%p kind=%d filter=%d enum_kind=%d callback=%p token_out=%p\n",
           iface, device, (int)kind, (int)filter, (int)enum_kind, callback, token );
    if (token) *token = (GameInputCallbackToken)0;
    return E_NOTIMPL;
}

static HRESULT WINAPI game_input1_RegisterSystemButtonCallback( v1_IGameInput *iface, v1_IGameInputDevice *device,
                                                               GameInputSystemButtons filter, void *context,
                                                               v1_GameInputSystemButtonCallback callback, GameInputCallbackToken *token )
{
    FIXME( "iface %p RegisterSystemButtonCallback device=%p filter=%u callback=%p token_out=%p\n",
           iface, device, (unsigned)filter, callback, token );
    if (token) *token = (GameInputCallbackToken)0;
    return E_NOTIMPL;
}

static HRESULT WINAPI game_input1_RegisterKeyboardLayoutCallback( v1_IGameInput *iface, v1_IGameInputDevice *device,
                                                                 void *context, v1_GameInputKeyboardLayoutCallback callback,
                                                                 GameInputCallbackToken *token )
{
    FIXME( "iface %p RegisterKeyboardLayoutCallback device=%p callback=%p token_out=%p\n",
           iface, device, callback, token );
    if (token) *token = (GameInputCallbackToken)0;
    return E_NOTIMPL;
}

static void WINAPI game_input1_StopCallback( v1_IGameInput *iface, GameInputCallbackToken token )
{
    FIXME( "iface %p StopCallback token=%llu\n", iface, (unsigned long long)token );
    /* no-op stub */
}

static bool WINAPI game_input1_UnregisterCallback( v1_IGameInput *iface, GameInputCallbackToken token )
{
    FIXME( "iface %p UnregisterCallback token=%llu\n", iface, (unsigned long long)token );
    return false;
}

static HRESULT WINAPI game_input1_CreateDispatcher( v1_IGameInput *iface, IGameInputDispatcher **dispatcher )
{
    FIXME( "iface %p CreateDispatcher dispatcher_out=%p\n", iface, dispatcher );
    if (dispatcher) *dispatcher = NULL;
    return E_NOTIMPL;
}

static HRESULT WINAPI game_input1_FindDeviceFromId( v1_IGameInput *iface, const APP_LOCAL_DEVICE_ID *value, v1_IGameInputDevice **device )
{
    FIXME( "iface %p FindDeviceFromId value=%p device_out=%p\n", iface, value, device );
    if (device) *device = NULL;
    return E_NOTIMPL;
}

static HRESULT WINAPI game_input1_FindDeviceFromPlatformString( v1_IGameInput *iface, const WCHAR *value, v1_IGameInputDevice **device )
{
    FIXME( "iface %p FindDeviceFromPlatformString value=%p device_out=%p\n", iface, value, device );
    if (device) *device = NULL;
    return E_NOTIMPL;
}

static void WINAPI game_input1_SetFocusPolicy( v1_IGameInput *iface, GameInputFocusPolicy policy )
{
    FIXME( "iface %p SetFocusPolicy policy=%d\n", iface, (int)policy );
    /* no-op stub */
}

static const struct v1_IGameInputVtbl game_input1_vtbl =
{
    /* IUnknown methods */
    game_input1_QueryInterface,
    game_input1_AddRef,
    game_input1_Release,
    /* v0_IGameInput methods */
    game_input1_GetCurrentTimestamp,
    game_input1_GetCurrentReading,
    game_input1_GetNextReading,
    game_input1_GetPreviousReading,
    game_input1_RegisterReadingCallback,
    game_input1_RegisterDeviceCallback,
    game_input1_RegisterSystemButtonCallback,
    game_input1_RegisterKeyboardLayoutCallback,
    game_input1_StopCallback,
    game_input1_UnregisterCallback,
    game_input1_CreateDispatcher,
    game_input1_FindDeviceFromId,
    game_input1_FindDeviceFromPlatformString,
    game_input1_SetFocusPolicy
};

static inline struct game_input *impl_from_v2_IGameInput( v2_IGameInput *iface )
{
    return CONTAINING_RECORD( iface, struct game_input, v2_IGameInput_iface );
}

static HRESULT WINAPI game_input2_QueryInterface( v2_IGameInput *iface, REFIID iid, void **out )
{
    struct game_input *impl = impl_from_v2_IGameInput( iface );

    TRACE( "iface %p, iid %s, out %p.\n", iface, debugstr_guid( iid ), out );

    if (IsEqualGUID( iid, &IID_IUnknown ) ||
        IsEqualGUID( iid, &IID_IAgileObject ) ||
        IsEqualGUID( iid, &IID_v0_IGameInput ))
    {
        *out = &impl->v0_IGameInput_iface;
        impl->ref++;
        return S_OK;
    }

    if (IsEqualGUID( iid, &IID_v1_IGameInput ))
    {
        *out = &impl->v1_IGameInput_iface;
        impl->ref++;
        return S_OK;
    }

    if (IsEqualGUID( iid, &IID_v2_IGameInput ))
    {
        *out = &impl->v2_IGameInput_iface;
        impl->ref++;
        return S_OK;
    }

    FIXME( "%s not implemented, returning E_NOINTERFACE.\n", debugstr_guid( iid ) );
    *out = NULL;
    return E_NOINTERFACE;
}

static ULONG WINAPI game_input2_AddRef( v2_IGameInput *iface )
{
    struct game_input *impl = impl_from_v2_IGameInput( iface );
    ULONG ref = InterlockedIncrement( &impl->ref );
    TRACE( "iface %p increasing refcount to %lu.\n", iface, ref );
    return ref;
}

static ULONG WINAPI game_input2_Release( v2_IGameInput *iface )
{
    struct game_input *impl = impl_from_v2_IGameInput( iface );
    ULONG ref = InterlockedDecrement( &impl->ref );
    TRACE( "iface %p decreasing refcount to %lu.\n", iface, ref );
    return ref;
};

static uint64_t WINAPI game_input2_GetCurrentTimestamp( v2_IGameInput *iface )
{
    TRACE( "iface %p, stub GetCurrentTimestamp.\n", iface );
    return (uint64_t)0;
}

/* --- Gamepad reading via XInput ---------------------------------------------
 * Bedrock's Ore-UI/menu polls GetCurrentReading(GameInputKindGamepad); the
 * original code returned E_NOTIMPL there, so a connected controller did nothing.
 * XInput reads the pad from the Linux kernel via Wine (independent of the display
 * server), so this also works under Wayland. Dynamically loaded to avoid a link
 * dependency. */
typedef struct { WORD wButtons; BYTE bLeftTrigger; BYTE bRightTrigger;
                 SHORT sThumbLX; SHORT sThumbLY; SHORT sThumbRX; SHORT sThumbRY; } XI_GAMEPAD;
typedef struct { DWORD dwPacketNumber; XI_GAMEPAD Gamepad; } XI_STATE;
typedef DWORD (WINAPI *PFN_XInputGetState)( DWORD, XI_STATE * );

/* Map an XInput state into GameInputGamepadState. */
static void map_xinput( const XI_STATE *xi, GameInputGamepadState *gs )
{
    int gb = GameInputGamepadNone;
    memset( gs, 0, sizeof(*gs) );
    if ( xi->Gamepad.wButtons & 0x0010 ) gb |= GameInputGamepadMenu;   /* START */
    if ( xi->Gamepad.wButtons & 0x0020 ) gb |= GameInputGamepadView;   /* BACK */
    if ( xi->Gamepad.wButtons & 0x1000 ) gb |= GameInputGamepadA;
    if ( xi->Gamepad.wButtons & 0x2000 ) gb |= GameInputGamepadB;
    if ( xi->Gamepad.wButtons & 0x4000 ) gb |= GameInputGamepadX;
    if ( xi->Gamepad.wButtons & 0x8000 ) gb |= GameInputGamepadY;
    if ( xi->Gamepad.wButtons & 0x0001 ) gb |= GameInputGamepadDPadUp;
    if ( xi->Gamepad.wButtons & 0x0002 ) gb |= GameInputGamepadDPadDown;
    if ( xi->Gamepad.wButtons & 0x0004 ) gb |= GameInputGamepadDPadLeft;
    if ( xi->Gamepad.wButtons & 0x0008 ) gb |= GameInputGamepadDPadRight;
    if ( xi->Gamepad.wButtons & 0x0100 ) gb |= GameInputGamepadLeftShoulder;
    if ( xi->Gamepad.wButtons & 0x0200 ) gb |= GameInputGamepadRightShoulder;
    if ( xi->Gamepad.wButtons & 0x0040 ) gb |= GameInputGamepadLeftThumbstick;
    if ( xi->Gamepad.wButtons & 0x0080 ) gb |= GameInputGamepadRightThumbstick;
    gs->buttons = gb;
    gs->leftTrigger      = xi->Gamepad.bLeftTrigger  / 255.0f;
    gs->rightTrigger     = xi->Gamepad.bRightTrigger / 255.0f;
    gs->leftThumbstickX  = xi->Gamepad.sThumbLX / 32767.0f;
    gs->leftThumbstickY  = xi->Gamepad.sThumbLY / 32767.0f;
    gs->rightThumbstickX = xi->Gamepad.sThumbRX / 32767.0f;
    gs->rightThumbstickY = xi->Gamepad.sThumbRY / 32767.0f;
}

/* Map a DirectInput DIJOYSTATE2 into GameInputGamepadState. Generic HID gamepads
 * (Stadia, PS3, clones) appear via DInput, NOT XInput. Axis range is the DInput
 * default 0..65535 (center 32768). Button order is the common DInput layout
 * (0=A/cross, 1=B/circle, 2=X/square, 3=Y/triangle); refined once we observe the
 * actual pad. POV hat 0 drives the d-pad (cohtml menu navigation needs this). */
static void map_dijoystate( const DIJOYSTATE2 *js, GameInputGamepadState *gs )
{
    int gb = GameInputGamepadNone;
    DWORD pov = js->rgdwPOV[0];
    memset( gs, 0, sizeof(*gs) );

    if ( (pov & 0xFFFF) != 0xFFFF )
    {
        if ( pov >= 31500 || pov <= 4500 )  gb |= GameInputGamepadDPadUp;
        if ( pov >= 4500  && pov <= 13500 ) gb |= GameInputGamepadDPadRight;
        if ( pov >= 13500 && pov <= 22500 ) gb |= GameInputGamepadDPadDown;
        if ( pov >= 22500 && pov <= 31500 ) gb |= GameInputGamepadDPadLeft;
    }
    if ( js->rgbButtons[0] & 0x80 ) gb |= GameInputGamepadA;
    if ( js->rgbButtons[1] & 0x80 ) gb |= GameInputGamepadB;
    if ( js->rgbButtons[2] & 0x80 ) gb |= GameInputGamepadX;
    if ( js->rgbButtons[3] & 0x80 ) gb |= GameInputGamepadY;
    if ( js->rgbButtons[4] & 0x80 ) gb |= GameInputGamepadLeftShoulder;
    if ( js->rgbButtons[5] & 0x80 ) gb |= GameInputGamepadRightShoulder;
    if ( js->rgbButtons[6] & 0x80 ) gb |= GameInputGamepadView;   /* Select */
    if ( js->rgbButtons[7] & 0x80 ) gb |= GameInputGamepadMenu;   /* Start */
    if ( js->rgbButtons[8] & 0x80 ) gb |= GameInputGamepadLeftThumbstick;
    if ( js->rgbButtons[9] & 0x80 ) gb |= GameInputGamepadRightThumbstick;
    gs->buttons = gb;

    /* normalize axes 0..65535 (center 32768) -> -1..1; DInput Y is down-positive */
    gs->leftThumbstickX  = (js->lX  - 32768) / 32768.0f;
    gs->leftThumbstickY  = -(js->lY - 32768) / 32768.0f;
    gs->rightThumbstickX = (js->lRx - 32768) / 32768.0f;
    gs->rightThumbstickY = -(js->lRy - 32768) / 32768.0f;
}

static HRESULT read_gamepad( v2_IGameInputDevice *device, uint64_t timestamp, v2_IGameInputReading **reading )
{
    static PFN_XInputGetState pXInputGetState = NULL;
    static BOOL loaded = FALSE;
    GameInputGamepadState gs;
    XI_STATE xi;
    DWORD idx;

    /* 1) XInput first (Xbox-compatible pads). */
    if ( !loaded )
    {
        HMODULE h;
        loaded = TRUE;
        if ( !(h = LoadLibraryA( "xinput1_4.dll" )) )
            if ( !(h = LoadLibraryA( "xinput1_3.dll" )) )
                h = LoadLibraryA( "xinput9_1_0.dll" );
        if ( h ) pXInputGetState = (PFN_XInputGetState)GetProcAddress( h, "XInputGetState" );
        TRACE( "XInput module=%p XInputGetState=%p\n", h, pXInputGetState );
    }
    if ( pXInputGetState )
    {
        for ( idx = 0; idx < 4; idx++ )
        {
            memset( &xi, 0, sizeof(xi) );
            if ( pXInputGetState( idx, &xi ) == ERROR_SUCCESS )
            {
                map_xinput( &xi, &gs );
                return game_input_reading_CreateForGamepadDevice( device, gs, timestamp, reading );
            }
        }
    }

    /* 2) DirectInput8 fallback (Stadia / PS3 / generic HID pads). The device created
     *    in device_provider_create has a DIJOYSTATE2 DInput device attached. */
    {
        LPDIRECTINPUTDEVICE8W dev = NULL;
        DIJOYSTATE2 js;
        HRESULT hr = game_input_device_AcquireDInputDevice( device, &dev );
        if ( FAILED( hr ) || !dev ) return E_FAIL;

        dev->lpVtbl->Poll( dev );
        memset( &js, 0, sizeof(js) );
        hr = dev->lpVtbl->GetDeviceState( dev, sizeof(js), &js );
        if ( hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED )
        {
            dev->lpVtbl->Acquire( dev );
            dev->lpVtbl->Poll( dev );
            hr = dev->lpVtbl->GetDeviceState( dev, sizeof(js), &js );
        }
        if ( FAILED( hr ) ) return hr;

        map_dijoystate( &js, &gs );
        return game_input_reading_CreateForGamepadDevice( device, gs, timestamp, reading );
    }
}

static HRESULT WINAPI game_input2_GetCurrentReading( v2_IGameInput *iface, GameInputKind kind,
                                                   v2_IGameInputDevice *device, v2_IGameInputReading **reading )
{
    HRESULT status = S_OK;

    TRACE( "iface %p kind %d device %p reading %p\n", iface, kind, device, reading );

    if ( kind == GameInputKindMouse )
    {
        // TODO: Using HID to read mouse values is finicky
        //status = mouse_input_device_ReadCurrentStateFromHID( device, GetTickCount64(), reading );
        status = mouse_input_device_ReadCurrentStateFromDInput8( device, GetTickCount64(), reading );
    }
    else if ( kind == GameInputKindGamepad )
    {
        status = read_gamepad( device, GetTickCount64(), reading );
    }
    else
    {
        FIXME("requested unsupported device kind %d!\n", (int)kind);
        return E_NOTIMPL;
    }

    return status;
}

static HRESULT WINAPI game_input2_GetNextReading( v2_IGameInput *iface, v2_IGameInputReading *reference,
                                                 GameInputKind kind, v2_IGameInputDevice *device,
                                                 v2_IGameInputReading **reading )
{
    FIXME( "iface %p GetNextReading reference=%p kind=%d device=%p reading_out=%p\n", iface, reference, (int)kind, device, reading );
    if (reading) *reading = NULL;
    return E_NOTIMPL;
}

static HRESULT WINAPI game_input2_GetPreviousReading( v2_IGameInput *iface, v2_IGameInputReading *reference,
                                                     GameInputKind kind, v2_IGameInputDevice *device,
                                                     v2_IGameInputReading **reading )
{
    FIXME( "iface %p GetPreviousReading reference=%p kind=%d device=%p reading_out=%p\n", iface, reference, (int)kind, device, reading );
    if (reading) *reading = NULL;
    return E_NOTIMPL;
}

static HRESULT WINAPI game_input2_RegisterReadingCallback( v2_IGameInput *iface, v2_IGameInputDevice *device,
                                                          GameInputKind kind, void *context,
                                                          v2_GameInputReadingCallback callback, GameInputCallbackToken *token )
{
    FIXME( "iface %p RegisterReadingCallback device=%p kind=%d callback=%p token_out=%p\n",
           iface, device, (int)kind, callback, token );
    if (token) *token = (GameInputCallbackToken)0;
    return E_NOTIMPL;
}

static HRESULT WINAPI game_input2_RegisterDeviceCallback( v2_IGameInput *iface, v2_IGameInputDevice *device,
                                                         GameInputKind kind, GameInputDeviceStatus filter,
                                                         GameInputEnumerationKind enum_kind, void *context,
                                                         v2_GameInputDeviceCallback callback, GameInputCallbackToken *token )
{
    HRESULT status = S_OK;

    FIXME( "iface %p, device %p, kind %#x, filter %#x, enum_kind %d, context %p, callback %p, token %p semi-stub!\n", iface, device, kind, filter, enum_kind, context, callback, token );
    
    status = RegisterDeviceCallback( device, kind, enum_kind, context, callback, token );

    return status;
}

static HRESULT WINAPI game_input2_RegisterSystemButtonCallback( v2_IGameInput *iface, v2_IGameInputDevice *device,
                                                               GameInputSystemButtons filter, void *context,
                                                               v2_GameInputSystemButtonCallback callback, GameInputCallbackToken *token )
{
    FIXME( "iface %p RegisterSystemButtonCallback device=%p filter=%u callback=%p token_out=%p\n",
           iface, device, (unsigned)filter, callback, token );
    if (token) *token = (GameInputCallbackToken)0;
    return E_NOTIMPL;
}

static HRESULT WINAPI game_input2_RegisterKeyboardLayoutCallback( v2_IGameInput *iface, v2_IGameInputDevice *device,
                                                                 void *context, v2_GameInputKeyboardLayoutCallback callback,
                                                                 GameInputCallbackToken *token )
{
    FIXME( "iface %p RegisterKeyboardLayoutCallback device=%p callback=%p token_out=%p\n",
           iface, device, callback, token );
    if (token) *token = (GameInputCallbackToken)0;
    return E_NOTIMPL;
}

static void WINAPI game_input2_StopCallback( v2_IGameInput *iface, GameInputCallbackToken token )
{
    FIXME( "iface %p StopCallback token=%llu\n", iface, (unsigned long long)token );
    /* no-op stub */
}

static bool WINAPI game_input2_UnregisterCallback( v2_IGameInput *iface, GameInputCallbackToken token )
{
    FIXME( "iface %p UnregisterCallback token=%llu\n", iface, (unsigned long long)token );
    return TRUE;
}

static HRESULT WINAPI game_input2_CreateDispatcher( v2_IGameInput *iface, IGameInputDispatcher **dispatcher )
{
    FIXME( "iface %p CreateDispatcher dispatcher_out=%p\n", iface, dispatcher );
    if (dispatcher) *dispatcher = NULL;
    return E_NOTIMPL;
}

static HRESULT WINAPI game_input2_FindDeviceFromId( v2_IGameInput *iface, const APP_LOCAL_DEVICE_ID *value, v2_IGameInputDevice **device )
{
    FIXME( "iface %p FindDeviceFromId value=%p device_out=%p\n", iface, value, device );
    if (device) *device = NULL;
    return E_NOTIMPL;
}

static HRESULT WINAPI game_input2_FindDeviceFromPlatformString( v2_IGameInput *iface, const WCHAR *value, v2_IGameInputDevice **device )
{
    FIXME( "iface %p FindDeviceFromPlatformString value=%p device_out=%p\n", iface, value, device );
    if (device) *device = NULL;
    return E_NOTIMPL;
}

static void WINAPI game_input2_SetFocusPolicy( v2_IGameInput *iface, GameInputFocusPolicy policy )
{
    FIXME( "iface %p SetFocusPolicy policy=%d\n", iface, (int)policy );
    /* no-op stub */
}

static const struct v2_IGameInputVtbl game_input2_vtbl =
{
    /* IUnknown methods */
    game_input2_QueryInterface,
    game_input2_AddRef,
    game_input2_Release,
    /* v0_IGameInput methods */
    game_input2_GetCurrentTimestamp,
    game_input2_GetCurrentReading,
    game_input2_GetNextReading,
    game_input2_GetPreviousReading,
    game_input2_RegisterReadingCallback,
    game_input2_RegisterDeviceCallback,
    game_input2_RegisterSystemButtonCallback,
    game_input2_RegisterKeyboardLayoutCallback,
    game_input2_StopCallback,
    game_input2_UnregisterCallback,
    game_input2_CreateDispatcher,
    game_input2_FindDeviceFromId,
    game_input2_FindDeviceFromPlatformString,
    game_input2_SetFocusPolicy
};

static BOOL WINAPI start_monitor_thread( INIT_ONCE *once, void *param, void **context )
{
    HANDLE thread, start_event;

    TRACE( "once %p, param %p, context %p.\n", once, param, context );

    start_event = CreateEventA( NULL, FALSE, FALSE, NULL );
    if (!start_event) ERR( "Failed to create start event, error %lu\n", GetLastError() );

    thread = CreateThread( NULL, 0, DeviceMonitorThread, start_event, 0, NULL );
    if (!thread) ERR( "Failed to create monitor thread, error %lu\n", GetLastError() );
    else
    {
        WaitForSingleObject( start_event, INFINITE );
        CloseHandle( thread );
    }

    CloseHandle( start_event );
    return !!thread;
}

HRESULT WINAPI GameInputCreate( v0_IGameInput **out )
{
    struct game_input *input = NULL;

    static INIT_ONCE init_once = INIT_ONCE_STATIC_INIT;

    TRACE( "out %p\n", out );

    InitOnceExecuteOnce( &init_once, start_monitor_thread, NULL, NULL );

    if (!(input = calloc( 1, sizeof(*input) ))) return E_OUTOFMEMORY;

    input->v0_IGameInput_iface.lpVtbl = &game_input_vtbl;
    input->v1_IGameInput_iface.lpVtbl = &game_input1_vtbl;
    input->v2_IGameInput_iface.lpVtbl = &game_input2_vtbl;
    input->ref = 1;

    *out = &input->v0_IGameInput_iface;

    return S_OK;
}

HRESULT WINAPI DllGetClassObject( REFCLSID clsid, REFIID riid, void **out )
{
    FIXME( "clsid %s, riid %s, out %p stub!\n", debugstr_guid(clsid), debugstr_guid(riid), out );
    return CLASS_E_CLASSNOTAVAILABLE;
}

BOOL WINAPI DllMain( HINSTANCE instance, DWORD reason, void *reserved )
{
    TRACE( "instance %p, reason %lu, reserved %p.\n", instance, reason, reserved );

    switch (reason)
    {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls( instance );
            game_input = instance;
            break;
    }
    return TRUE;
}