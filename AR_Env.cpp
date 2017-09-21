#include "stdafx.h"
#include <string>
#include <windows.h>
#include "Capture.h"
#include<iostream>
#include "afxdialogex.h"
#define STRSAFE_NO_DEPRECATE
#include <strsafe.h> // for String... functions
#include <crtdbg.h> // for _ASSERTE 
#include <atlstr.h>
#define DLL1_API extern "C" _declspec(dllexport)
#include "AR_Env.h"
using namespace std;
#pragma warning(disable:4996)
#pragma once 
/**
* Camera 初始化
* @param module 模块类型    无模块：-1 ，IR模块：0，SLAM模块：1，CR模块：2，MARKER模块：3，WP模块：4
* @param mCameraID 相机ID  后置相机：0，前置相机：1
* @return false失败，true成功
*/
CCapture * cap;
int m_CameraId = -1;
int m_moudle = -2;
HANDLE handle;
bool start_preview = false;
HANDLE hMutex;
typedef void(*capCallBackFunc)(LPVOID lParam);

void userUpdateCb(LPVOID lParam)
{
    char* cur_buffer = (char*)(lParam);
    if (!cur_buffer)
    {
        cout << "此时的buffer为空" << endl;
        return;
    }
    cout << "此时的buffer长度为" << strlen(cur_buffer) << endl;
    /*
    dump_temp("file.txt", (char*)cur_buffer, cap->GetPreHeight()*cap->GetPreWidth() * 3);
    */

    //use IR_MEMROY
}

DWORD WINAPI ClientThread(LPVOID lpParam)
{
    bool start_preview_temp = false;
    while (1)
    {
        WaitForSingleObject(hMutex, INFINITE);
        start_preview_temp = start_preview;
        ReleaseMutex(hMutex);
        if (start_preview_temp)
            break;
    }
    if (!FAILED(cap->Preview(m_CameraId)))
        return 1;
    return 0;
}

bool init(int module, int mCameraID)
{
    hMutex = CreateMutex(nullptr,false,nullptr);
    cap = new CCapture();
    m_CameraId = mCameraID;
    m_moudle = module;
    start_preview = false;
    if (FAILED(cap->InitCaptureGraphBuilder()))
    {
        return false;
    }
    //初始化子线程，预览时候函数调用
    handle = CreateThread(NULL, 0, ClientThread, NULL, 0, NULL);
    if (!handle)
        return false;
    return true;
}

/**
* 开始预览
* @return false失败，true成功
*/
bool startPreview()
{
    WaitForSingleObject(hMutex, INFINITE);
    start_preview = true;
    ReleaseMutex(hMutex);
    return true;
}
/**
* 更新相机预览画面
*/
void UpdatePreview()
{
    cap->SetCallBKFun(userUpdateCb);
}

/**
* 获取相机预览时的图片高度
* @return 图片高度
*/
int getCameraPreviewHeight()
{
    return cap->GetPreHeight();
}

/**
* 获取相机预览时的图片宽度
* @return 图片宽度
*/
int getCameraPreviewWidth()
{
    return cap->GetPreWidth();
}

/**
* 停止相机的预览和画面的渲染
*/
void stop()
{
    WaitForSingleObject(hMutex, INFINITE);
    start_preview = false;
    ReleaseMutex(hMutex);
 //   cap->StopCapture();
}

//释放相机资源
void release()
{
    WaitForSingleObject(hMutex, INFINITE);
    start_preview = false;
    ReleaseMutex(hMutex);
    CloseHandle(handle);
    delete cap;
}
