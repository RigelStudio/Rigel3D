/************************************************************ 
  Copyright (C), 2014-2017, SSIT Tech. Co., Ltd. 
  文件名: FileUtils.h
  作者: lyk
  版本: V1.0.0
  日期: 2016/09/23
  模块描述:获取路径接口
  主要函数及其功能:
  历史修改记录:
***********************************************************/
#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <string>
#include "Export.h"

/* 本类的功能：根据相对路径获取文件的绝对路径
 *   
 * 本类是一个单件
 * 在程序中需要进行模型，图片文件查找的地方使用
 */ 
class DLL_EXPORT FileUtils
{
public:
	/*
	 * @return FileUtils*:单例类实例
	 * @see    des()
	 * @note   获取唯一实例:FileUtils::ins()->init("D:/project/");
	 */
	static FileUtils* ins();

	/*
	* @see    ins()
	* @note   销毁唯一实例
	*/
	static void des();

	/*
	* @param name:根目录名称
	* @see   getPath()
	* @note  初始化根目录
	*/
	void init(const std::string& name);

	/*
	* @param name:文件名称或者相对路径
	* @return 文件的绝对路径
	* @see   init()
	* @note  根据给定的文件名称，或者绝对文件路径
	* std::string strImagePath = FileUtils::ins()->getPath("image.png");
	*/

	std::string getPath(const std::string& name);

private:
	FileUtils();
	~FileUtils();

private:
	static FileUtils* m_pIns;
	std::string m_strRoot;
};

#endif // FILEUTILS_H
