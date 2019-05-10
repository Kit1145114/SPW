/*!
 *@brief	プリコンパイル済みヘッダー。
 */
#pragma once

#define UseNetwork

 //photonがWinSock2使ってるみたいで、windows.hより先にincludeしないとエラー出るのでここに書かせてもらいます
#include <WinSock2.h>
#include <windows.h>
#include <d3d11.h>
#include "resource.h"

#include "tkEngine/tkEnginePreCompile.h"
using namespace tkEngine;
