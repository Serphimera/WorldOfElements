// Copyright 2015 Nethersoft (Sebastian Kenter). All rights reserved.

#pragma once

#ifdef __clang__
#pragma clang diagnostic ignored "-Woverloaded-virtual"
#endif

#if _EG_WINDOWS_PLATFORM
#include "AllowWindowsPlatformTypes.h"
#pragma warning (disable: 4263)
#pragma warning (disable: 4264)
#endif
#include "Photon-cpp/inc/PhotonListener.h"
#include "Photon-cpp/inc/PhotonPeer.h"
#if _EG_WINDOWS_PLATFORM
#pragma warning (default: 4263)
#pragma warning (default: 4264)
#include "HideWindowsPlatformTypes.h"
#endif