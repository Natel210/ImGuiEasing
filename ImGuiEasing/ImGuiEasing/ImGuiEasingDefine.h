#pragma once

// presence of DLL EXPORT
#ifndef IMGUIEASING_API
#ifdef IMGUIEASING_EXPORTS
#define IMGUIEASING_API __declspec(dllexport)
#else
#define IMGUIEASING_API __declspec(dllimport)
#endif // IMGUIEASING_EXPORTS
#endif // !IMGUIEASING_API

