#ifndef QuiBaseUiExport_h__
#define QuiBaseUiExport_h__

#if defined(WIN32)
#ifdef  QuiBaseUi_EXPORTS
#define QuiBaseUi_EXPORT __declspec(dllexport)
#else
#define  QuiBaseUi_EXPORT __declspec(dllimport)
#endif

#pragma warning( disable: 4251 )

#elif __linux__
#define QuiBaseUi_EXPORT

#else
#define QuiBaseUi_EXPORT 
#endif
#endif // ExtendStructureExport_h__
