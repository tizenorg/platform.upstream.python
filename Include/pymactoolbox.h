/*
** pymactoolbox.h - globals defined in mactoolboxglue.c
*/
#ifndef Py_PYMACTOOLBOX_H
#define Py_PYMACTOOLBOX_H
#ifdef __cplusplus
	extern "C" {
#endif

#include <Carbon/Carbon.h>

#ifndef __LP64__
#include <QuickTime/QuickTime.h>
#endif /* !__LP64__ */

/*
** Helper routines for error codes and such.
*/
__attribute__ ((visibility ("default"))) char *PyMac_StrError(int);			/* strerror with mac errors */
__attribute__ ((visibility ("default"))) extern PyObject *PyMac_OSErrException;		/* Exception for OSErr */
__attribute__ ((visibility ("default"))) PyObject *PyMac_GetOSErrException(void);	/* Initialize & return it */
__attribute__ ((visibility ("default"))) PyObject *PyErr_Mac(PyObject *, int);		/* Exception with a mac error */
__attribute__ ((visibility ("default"))) PyObject *PyMac_Error(OSErr);			/* Uses PyMac_GetOSErrException */
#ifndef __LP64__ 
extern OSErr PyMac_GetFullPathname(FSSpec *, char *, int); /* convert
							      fsspec->path */
#endif /* __LP64__ */

/*
** These conversion routines are defined in mactoolboxglue.c itself.
*/
__attribute__ ((visibility ("default"))) int PyMac_GetOSType(PyObject *, OSType *);	/* argument parser for OSType */
__attribute__ ((visibility ("default"))) PyObject *PyMac_BuildOSType(OSType);		/* Convert OSType to PyObject */

__attribute__ ((visibility ("default"))) PyObject *PyMac_BuildNumVersion(NumVersion);/* Convert NumVersion to PyObject */

__attribute__ ((visibility ("default"))) int PyMac_GetStr255(PyObject *, Str255);	/* argument parser for Str255 */
__attribute__ ((visibility ("default"))) PyObject *PyMac_BuildStr255(Str255);		/* Convert Str255 to PyObject */
__attribute__ ((visibility ("default"))) PyObject *PyMac_BuildOptStr255(Str255);		/* Convert Str255 to PyObject,
						   NULL to None */

__attribute__ ((visibility ("default"))) int PyMac_GetRect(PyObject *, Rect *);		/* argument parser for Rect */
__attribute__ ((visibility ("default"))) PyObject *PyMac_BuildRect(Rect *);		/* Convert Rect to PyObject */

__attribute__ ((visibility ("default"))) int PyMac_GetPoint(PyObject *, Point *);	/* argument parser for Point */
__attribute__ ((visibility ("default"))) PyObject *PyMac_BuildPoint(Point);		/* Convert Point to PyObject */

__attribute__ ((visibility ("default"))) int PyMac_GetEventRecord(PyObject *, EventRecord *); /* argument parser for
							EventRecord */
__attribute__ ((visibility ("default"))) PyObject *PyMac_BuildEventRecord(EventRecord *); /* Convert EventRecord to
						    PyObject */

__attribute__ ((visibility ("default"))) int PyMac_GetFixed(PyObject *, Fixed *);	/* argument parser for Fixed */
__attribute__ ((visibility ("default"))) PyObject *PyMac_BuildFixed(Fixed);		/* Convert Fixed to PyObject */
__attribute__ ((visibility ("default"))) int PyMac_Getwide(PyObject *, wide *);		/* argument parser for wide */
__attribute__ ((visibility ("default"))) PyObject *PyMac_Buildwide(wide *);		/* Convert wide to PyObject */

/*
** The rest of the routines are implemented by extension modules. If they are
** dynamically loaded mactoolboxglue will contain a stub implementation of the
** routine, which imports the module, whereupon the module's init routine will
** communicate the routine pointer back to the stub.
** If USE_TOOLBOX_OBJECT_GLUE is not defined there is no glue code, and the
** extension modules simply declare the routine. This is the case for static
** builds (and could be the case for MacPython CFM builds, because CFM extension
** modules can reference each other without problems).
*/

#ifdef USE_TOOLBOX_OBJECT_GLUE
/*
** These macros are used in the module init code. If we use toolbox object glue
** it sets the function pointer to point to the real function.
*/
#define PyMac_INIT_TOOLBOX_OBJECT_NEW(object, rtn) { \
	extern PyObject *(*PyMacGluePtr_##rtn)(object); \
	PyMacGluePtr_##rtn = _##rtn; \
}
#define PyMac_INIT_TOOLBOX_OBJECT_CONVERT(object, rtn) { \
	extern int (*PyMacGluePtr_##rtn)(PyObject *, object *); \
	PyMacGluePtr_##rtn = _##rtn; \
}
#else
/*
** If we don't use toolbox object glue the init macros are empty. Moreover, we define
** _xxx_New to be the same as xxx_New, and the code in mactoolboxglue isn't included.
*/
#define PyMac_INIT_TOOLBOX_OBJECT_NEW(object, rtn)
#define PyMac_INIT_TOOLBOX_OBJECT_CONVERT(object, rtn)
#endif /* USE_TOOLBOX_OBJECT_GLUE */

/* macfs exports */
#ifndef __LP64__
int PyMac_GetFSSpec(PyObject *, FSSpec *);	/* argument parser for FSSpec */
PyObject *PyMac_BuildFSSpec(FSSpec *);		/* Convert FSSpec to PyObject */
#endif /* !__LP64__ */

__attribute__ ((visibility ("default"))) int PyMac_GetFSRef(PyObject *, FSRef *);	/* argument parser for FSRef */
__attribute__ ((visibility ("default"))) PyObject *PyMac_BuildFSRef(FSRef *);		/* Convert FSRef to PyObject */

/* AE exports */
__attribute__ ((visibility ("default"))) extern PyObject *AEDesc_New(AppleEvent *); /* XXXX Why passed by address?? */
__attribute__ ((visibility ("default"))) extern PyObject *AEDesc_NewBorrowed(AppleEvent *);
__attribute__ ((visibility ("default"))) extern int AEDesc_Convert(PyObject *, AppleEvent *);

/* Cm exports */
__attribute__ ((visibility ("default"))) extern PyObject *CmpObj_New(Component);
__attribute__ ((visibility ("default"))) extern int CmpObj_Convert(PyObject *, Component *);
__attribute__ ((visibility ("default"))) extern PyObject *CmpInstObj_New(ComponentInstance);
__attribute__ ((visibility ("default"))) extern int CmpInstObj_Convert(PyObject *, ComponentInstance *);

/* Ctl exports */
#ifndef __LP64__
extern PyObject *CtlObj_New(ControlHandle);
extern int CtlObj_Convert(PyObject *, ControlHandle *);
#endif /* !__LP64__ */

/* Dlg exports */
#ifndef __LP64__
extern PyObject *DlgObj_New(DialogPtr);
extern int DlgObj_Convert(PyObject *, DialogPtr *);
extern PyObject *DlgObj_WhichDialog(DialogPtr);
#endif /* !__LP64__ */

/* Drag exports */
#ifndef __LP64__
extern PyObject *DragObj_New(DragReference);
extern int DragObj_Convert(PyObject *, DragReference *);
#endif /* !__LP64__ */

/* List exports */
#ifndef __LP64__
extern PyObject *ListObj_New(ListHandle);
extern int ListObj_Convert(PyObject *, ListHandle *);
#endif /* !__LP64__ */

/* Menu exports */
#ifndef __LP64__
extern PyObject *MenuObj_New(MenuHandle);
extern int MenuObj_Convert(PyObject *, MenuHandle *);
#endif /* !__LP64__ */

/* Qd exports */
#ifndef __LP64__
extern PyObject *GrafObj_New(GrafPtr);
extern int GrafObj_Convert(PyObject *, GrafPtr *);
extern PyObject *BMObj_New(BitMapPtr);
extern int BMObj_Convert(PyObject *, BitMapPtr *);
extern PyObject *QdRGB_New(RGBColor *);
extern int QdRGB_Convert(PyObject *, RGBColor *);
#endif /* !__LP64__ */

/* Qdoffs exports */
#ifndef __LP64__
extern PyObject *GWorldObj_New(GWorldPtr);
extern int GWorldObj_Convert(PyObject *, GWorldPtr *);
#endif /* !__LP64__ */

/* Qt exports */
#ifndef __LP64__
extern PyObject *TrackObj_New(Track);
extern int TrackObj_Convert(PyObject *, Track *);
extern PyObject *MovieObj_New(Movie);
extern int MovieObj_Convert(PyObject *, Movie *);
extern PyObject *MovieCtlObj_New(MovieController);
extern int MovieCtlObj_Convert(PyObject *, MovieController *);
extern PyObject *TimeBaseObj_New(TimeBase);
extern int TimeBaseObj_Convert(PyObject *, TimeBase *);
extern PyObject *UserDataObj_New(UserData);
extern int UserDataObj_Convert(PyObject *, UserData *);
extern PyObject *MediaObj_New(Media);
extern int MediaObj_Convert(PyObject *, Media *);
#endif /* !__LP64__ */

/* Res exports */
__attribute__ ((visibility ("default"))) extern PyObject *ResObj_New(Handle);
__attribute__ ((visibility ("default"))) extern int ResObj_Convert(PyObject *, Handle *);
__attribute__ ((visibility ("default"))) extern PyObject *OptResObj_New(Handle);
__attribute__ ((visibility ("default"))) extern int OptResObj_Convert(PyObject *, Handle *);

/* TE exports */
#ifndef __LP64__
extern PyObject *TEObj_New(TEHandle);
extern int TEObj_Convert(PyObject *, TEHandle *);
#endif /* !__LP64__ */

/* Win exports */
#ifndef __LP64__
extern PyObject *WinObj_New(WindowPtr);
extern int WinObj_Convert(PyObject *, WindowPtr *);
extern PyObject *WinObj_WhichWindow(WindowPtr);
#endif /* !__LP64__ */

/* CF exports */
__attribute__ ((visibility ("default"))) extern PyObject *CFObj_New(CFTypeRef);
__attribute__ ((visibility ("default"))) extern int CFObj_Convert(PyObject *, CFTypeRef *);
__attribute__ ((visibility ("default"))) extern PyObject *CFTypeRefObj_New(CFTypeRef);
__attribute__ ((visibility ("default"))) extern int CFTypeRefObj_Convert(PyObject *, CFTypeRef *);
__attribute__ ((visibility ("default"))) extern PyObject *CFStringRefObj_New(CFStringRef);
__attribute__ ((visibility ("default"))) extern int CFStringRefObj_Convert(PyObject *, CFStringRef *);
__attribute__ ((visibility ("default"))) extern PyObject *CFMutableStringRefObj_New(CFMutableStringRef);
__attribute__ ((visibility ("default"))) extern int CFMutableStringRefObj_Convert(PyObject *, CFMutableStringRef *);
__attribute__ ((visibility ("default"))) extern PyObject *CFArrayRefObj_New(CFArrayRef);
__attribute__ ((visibility ("default"))) extern int CFArrayRefObj_Convert(PyObject *, CFArrayRef *);
__attribute__ ((visibility ("default"))) extern PyObject *CFMutableArrayRefObj_New(CFMutableArrayRef);
__attribute__ ((visibility ("default"))) extern int CFMutableArrayRefObj_Convert(PyObject *, CFMutableArrayRef *);
__attribute__ ((visibility ("default"))) extern PyObject *CFDictionaryRefObj_New(CFDictionaryRef);
__attribute__ ((visibility ("default"))) extern int CFDictionaryRefObj_Convert(PyObject *, CFDictionaryRef *);
__attribute__ ((visibility ("default"))) extern PyObject *CFMutableDictionaryRefObj_New(CFMutableDictionaryRef);
__attribute__ ((visibility ("default"))) extern int CFMutableDictionaryRefObj_Convert(PyObject *, CFMutableDictionaryRef *);
__attribute__ ((visibility ("default"))) extern PyObject *CFURLRefObj_New(CFURLRef);
__attribute__ ((visibility ("default"))) extern int CFURLRefObj_Convert(PyObject *, CFURLRef *);
__attribute__ ((visibility ("default"))) extern int OptionalCFURLRefObj_Convert(PyObject *, CFURLRef *);

#ifdef __cplusplus
	}
#endif
#endif
