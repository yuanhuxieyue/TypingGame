#ifndef _UTIL_H_
#define _UTIL_H_

#include "camera.h"

#include <graphics.h>

#pragma comment(lib, "WINMM.lib")
#pragma comment(lib, "MSIMG32.lib")

// 区域类
struct Rect
{
	int x, y; // 区域坐标
	int w, h; // 区域宽高
};

// 负责透明图像绘制
inline void putimage_ex(const Camera& camera, IMAGE* img, const Rect* rect_dst, const Rect* rect_src = nullptr)
{
	static BLENDFUNCTION blend_func = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA }; // 透明度混合参数

	const Vector2& pos_camera = camera.get_position();
	// 参数包括显示在窗口的区域和要裁剪的区域
	AlphaBlend(GetImageHDC(GetWorkingImage()), 
		(int)(rect_dst->x - pos_camera.x), 
		(int)(rect_dst->y - pos_camera.y), 
		rect_dst->w, rect_dst->h, 
		GetImageHDC(img), 
		rect_src ? rect_src->x : 0, 
		rect_src ? rect_src->y : 0,
		rect_src ? rect_src->w : img->getwidth(), 
		rect_src ? rect_src->h : img->getheight(), 
		blend_func);
}

// 对MCI接口的封装，易于使用
inline void load_audio(LPCTSTR path, LPCTSTR id)
{
	static TCHAR str_cmd[512];
	_stprintf_s(str_cmd, _T("open %s alias %s"), path, id); // // 生成 MCI 命令，打开音乐并设置别名
	mciSendString(str_cmd, NULL, 0, NULL);
}

inline void play_audio(LPCTSTR id, bool is_loop = false)
{
	static TCHAR str_cmd[512];
	_stprintf_s(str_cmd, _T("play %s %s from 0"), id, is_loop ? _T("repeat") : _T(""));
	mciSendString(str_cmd, NULL, 0, NULL);
}

inline void stop_audio(LPCTSTR id)
{
	static TCHAR str_cmd[512];
	_stprintf_s(str_cmd, _T("stop %s"), id);
	mciSendString(str_cmd, NULL, 0, NULL);
}

#endif // !_UTIL_H_