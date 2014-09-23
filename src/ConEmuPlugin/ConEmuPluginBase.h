﻿
/*
Copyright (c) 2009-2014 Maximus5
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. The name of the authors may not be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE AUTHOR ''AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#pragma once

#include <windows.h>
#include "../common/common.hpp"

struct ConEmuPluginMenuItem;

typedef DWORD GetPanelDirFlags;
const GetPanelDirFlags
	gpdf_NoPlugin = 1,
	gpdf_NoHidden = 2,
	gpdf_Active   = 4,
	gpdf_Passive  = 0
;

class CPluginBase
{
public:
	CPluginBase();
	virtual ~CPluginBase();

	int ShowMessageGui(int aiMsg, int aiButtons);
	void PostMacro(const wchar_t* asMacro, INPUT_RECORD* apRec);
	bool isMacroActive(int& iMacroActive);
	void UpdatePanelDirs();
	bool RunExternalProgram(wchar_t* pszCommand);
	bool ProcessCommandLine(wchar_t* pszCommand);
	void ShowPluginMenu(PluginCallCommands nCallID = pcc_None);
	int ProcessSynchroEvent(int Event, void *Param);

public:
	virtual BOOL    CheckBufferEnabled() = 0;
	virtual BOOL    ExecuteSynchro() = 0;
	virtual void    ExitFAR(void) = 0;
	virtual void    FillUpdateBackground(struct PaintBackgroundArg* pFar) = 0;
	virtual int     GetActiveWindowType() = 0;
	virtual DWORD   GetEditorModifiedState() = 0;
	virtual int     GetMacroArea() = 0;
	virtual LPCWSTR GetMsg(int aiMsg, wchar_t* psMsg = NULL, size_t cchMsgMax = 0) = 0;
	virtual LPWSTR  GetPanelDir(GetPanelDirFlags Flags) = 0;
	virtual void    GetPluginInfo(void* piv) = 0; // PluginInfo* versioned
	virtual LPCWSTR GetWindowTypeName(int WindowType) = 0;
	virtual void    GuiMacroDlg() = 0;
	virtual bool    InputBox(LPCWSTR Title, LPCWSTR SubTitle, LPCWSTR HistoryName, LPCWSTR SrcText, wchar_t*& DestText) = 0;
	virtual bool    IsMacroActive() = 0;
	virtual void    LoadPanelDirs() = 0;
	#if 0
	virtual bool    LoadPlugin(wchar_t* pszPluginPath) = 0;
	#endif
	virtual HANDLE  Open(const void* apInfo) = 0;
	virtual bool    OpenEditor(LPCWSTR asFileName, bool abView, bool abDeleteTempFile, bool abDetectCP = false, int anStartLine = 0, int anStartChar = 1) = 0;
	virtual void    PostMacroApi(const wchar_t* asMacro, INPUT_RECORD* apRec) = 0;
	virtual void    ProcessDragFrom() = 0;
	virtual void    ProcessDragTo() = 0;
	virtual int     ProcessEditorEvent(int Event, void *Param) = 0;
	virtual int     ProcessEditorInput(LPCVOID Rec) = 0;
	virtual int     ProcessSynchroEvent(void* p) = 0;
	virtual int     ProcessViewerEvent(int Event, void *Param) = 0;
	virtual void    RedrawAll() = 0;
	virtual BOOL    ReloadFarInfo() = 0;
	virtual void    SetStartupInfo(void *aInfo) = 0;
	virtual void    SetWindow(int nTab) = 0;
	virtual int     ShowMessage(int aiMsg, int aiButtons) = 0;
	virtual int     ShowMessage(LPCWSTR asMsg, int aiButtons, bool bWarning) = 0;
	virtual int     ShowPluginMenu(ConEmuPluginMenuItem* apItems, int Count) = 0;
	virtual void    ShowUserScreen(bool bUserScreen) = 0;
	virtual void    StopWaitEndSynchro() = 0;
	virtual void    WaitEndSynchro() = 0;
};

CPluginBase* Plugin();

// Exports
#if defined(__GNUC__)
extern "C" {
#endif
int WINAPI GetMinFarVersion();
int WINAPI GetMinFarVersionW();
int WINAPI ProcessSynchroEventW(int Event,void *Param);
INT_PTR WINAPI ProcessSynchroEventW3(void* p);
#if defined(__GNUC__)
}
#endif
// Exports