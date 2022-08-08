#pragma once

#include <map>
#include <vector>

// 层次文档编写
class HierarchyFileWriter
{
	VSL_DECLARE_NOT_COPYABLE(HierarchyFileWriter)
public:
	explicit HierarchyFileWriter();
	virtual ~HierarchyFileWriter();

protected:
	// 开始
	void StartHierarchyWriter(const std::wstring&);

	//添加item
	bool addHierarchyItem(const std::wstring&, const std::wstring&);

	// 删除item
	bool deleteHierarchyItem(const std::wstring&);

	//刷新
	bool flush();

	//清理
	void clear();

private:

	// (key, val) == (path in vs, path on disk)
	std::map<std::wstring, std::wstring> m_hierarchyCache;

	static const std::wstring hierarchyFileName;

	std::wstring hierarchyFilePath;

};

