#include "FileUtils.h"
#include <QFileInfo>

FileUtils* FileUtils::m_pIns = NULL;

FileUtils::FileUtils()
{
	m_strRoot = "";
}

FileUtils::~FileUtils()
{

}

FileUtils* FileUtils::ins()
{
	if (m_pIns == NULL)
	{
		m_pIns = new FileUtils;
	}

	return m_pIns;
}

void FileUtils::des()
{
	delete m_pIns;
}

void FileUtils::init(const QString& name)
{
	m_strRoot = name;
	QFileInfo info(m_strRoot);
	m_strRoot = info.canonicalFilePath();
	QString str = m_strRoot.right(1);
	if (str != "/" ||  str != "\\")
	{
		m_strRoot.append("/");
	}
}

QString FileUtils::getPath(const QString& name)
{
	return m_strRoot + name;
}

std::string FileUtils::getPath(const std::string& name)
{
	return m_strRoot.toStdString() + name;
}
