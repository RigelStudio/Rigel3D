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

#include <QString>
#include "Export.h"

////////////////////////////////////////////////
// 使用方式为在main函数的入口处，调用init,
// 所得目录即为根目录，之后获取的目录都以此为基目录
// FileUtils::ins()->init("D:/project/");
////////////////////////////////////////////////
class MECORE_EXPORT FileUtils
{
public:
	static FileUtils* ins();
	static void des();

	void init(const QString& name);
	QString getPath(const QString& name);

private:
	FileUtils();
	~FileUtils();

private:
	static FileUtils* m_pIns;
	QString m_strRoot;
};

#endif // FILEUTILS_H
