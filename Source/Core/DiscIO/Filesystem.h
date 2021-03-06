// Copyright 2013 Dolphin Emulator Project
// Licensed under GPLv2
// Refer to the license.txt file included.

#pragma once

#include <cstddef>
#include <cstring>
#include <string>
#include <vector>

#include "Common/CommonTypes.h"

namespace DiscIO
{

class IVolume;

// file info of an FST entry
struct SFileInfo
{
	u64 m_NameOffset;
	u64 m_Offset;
	u64 m_FileSize;
	std::string m_FullPath;

	bool IsDirectory() const { return (m_NameOffset & 0xFF000000) != 0; }

	SFileInfo() : m_NameOffset(0), m_Offset(0), m_FileSize(0)
	{
	}

	SFileInfo(const SFileInfo& rhs) : m_NameOffset(rhs.m_NameOffset),
	    m_Offset(rhs.m_Offset), m_FileSize(rhs.m_FileSize), m_FullPath(rhs.m_FullPath)
	{
	}
};

class IFileSystem
{
public:
	IFileSystem(const IVolume *_rVolume);

	virtual ~IFileSystem();
	virtual bool IsValid() const = 0;
	virtual size_t GetFileList(std::vector<const SFileInfo *> &_rFilenames) = 0;
	virtual u64 GetFileSize(const std::string& _rFullPath) = 0;
	virtual u64 ReadFile(const std::string& _rFullPath, u8* _pBuffer, size_t _MaxBufferSize) = 0;
	virtual bool ExportFile(const std::string& _rFullPath, const std::string& _rExportFilename) = 0;
	virtual bool ExportApploader(const std::string& _rExportFolder) const = 0;
	virtual bool ExportDOL(const std::string& _rExportFolder) const = 0;
	virtual const std::string GetFileName(u64 _Address) = 0;
	virtual bool GetBootDOL(u8* &buffer, u32 DolSize) const = 0;
	virtual u32 GetBootDOLSize() const = 0;

	virtual const IVolume *GetVolume() const { return m_rVolume; }
protected:
	const IVolume *m_rVolume;
};

IFileSystem* CreateFileSystem(const IVolume *_rVolume);

} // namespace
