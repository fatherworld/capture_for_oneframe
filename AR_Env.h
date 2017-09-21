#ifndef DLL1_API
#define DLL1_API extern "C" _declspec (dllimport)
#endif
DLL1_API bool init(int module, int mCameraID);
/**
* 创建Render
* @return false失败，true成功
*/

DLL1_API bool createRender();

/**
* 开始预览
* @return false失败，true成功
*/
DLL1_API bool startPreview();

/**
* 更新相机预览画面
*/
DLL1_API void UpdatePreview();

/**
* 设置纹理ID
* @param textureID 纹理ID
*/
DLL1_API void setTexture(int textureID);

/**
* 获取纹理
* @return 纹理数组
*/
DLL1_API int* getTextures();

/**
* 获取屏幕宽度
* @return 屏幕宽度
*/
DLL1_API int getScreenWidth();

/**
* 获取屏幕高度
* @return 屏幕高度
*/
DLL1_API int getScreenHeight();

/**
* 获取相机预览时的图片格式
* @return 格式类型
*/
DLL1_API int getCameraPreviewFormat();

/**
* 获取相机预览时的图片高度
* @return 图片高度
*/
DLL1_API int getCameraPreviewHeight();

/**
* 获取相机预览时的图片宽度
* @return 图片宽度
*/
DLL1_API int getCameraPreviewWidth();

/**
* 获取合适的纹理宽度
* @return 纹理宽度值
*/
DLL1_API int getSupportTextureWidth();

/**
* 获取合适的纹理高度
* @return 纹理高度值
*/
DLL1_API int getSupportTextureHeight();

/**
* 获取camera的旋转角度
* @return
*/
DLL1_API int getCameraRotaion();

/**
* 停止相机的预览和画面的渲染
*/
DLL1_API void stop();

/**
* 停止相机的预览和释放相机的资源
*/
DLL1_API void release();
