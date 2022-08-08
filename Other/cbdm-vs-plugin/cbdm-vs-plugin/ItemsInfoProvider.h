#pragma once
//item 信息供应商
class ItemsInfoProvider
{
public:
	ItemsInfoProvider();
	virtual ~ItemsInfoProvider();

protected:
	// COM 接口
	IVsHierarchy* m_pHierarchy;

private:

	// 层次 
	HRESULT CheckHierarchyPointer();

protected:
	
	//
	HRESULT SetHierarchyPointer(IVsHierarchy* pHierarchy);

	HRESULT GetFirstChildItemId(VSITEMID itemId,  VSITEMID& childItemId, int visibleOnly);

	HRESULT GetItemType(VSITEMID itemId, GUID* type);

	HRESULT IsItemType(VSITEMID itemId, const GUID& compareTo, int& isItemType);

	//HRESULT IsVirtualFolderItem(VSITEMID itemId, int& isVirtual);

	//HRESULT IsProjectItem(VSITEMID itemId, int & isProject);

	HRESULT GetItemName(VSITEMID itemId, BSTR* name);

	HRESULT GetProjectName(BSTR* name);
	
	HRESULT GetProjectPath(BSTR* path);

	HRESULT GetProjectDir(BSTR* dir);

	HRESULT WalkHierarchyItems(VSITEMID itemId, BSTR basePath, 
		std::vector<CAdapt<CComBSTR>>& vsHierarchy, int recursionLevel, bool visibleNodesOnly);

	


	
};

