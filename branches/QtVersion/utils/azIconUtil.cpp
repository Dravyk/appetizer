/*
  Copyright (C) 2008-2010 Laurent Cozic. All right reserved.
  Use of this source code is governed by a GNU/GPL license that can be
  found in the LICENSE file.
*/

#include "../stable.h"

#include "azIconUtil.h"


azIconData azIconUtil::getFolderItemIcon(std::wstring filePath, int iconSize) {
  azIconData output;

  // Note: certain functions, like SHGetImageList don't exist in Windows 2000,
  // so we need to load them dynamically, otherwise we get this error and the app doesn't start:
  // "The ordinal 737 could not be located in the dynamic link library Shell32.dll"

  HINSTANCE shell32Library_ = LoadLibrary(_T("SHELL32.DLL"));
  SHGetImageListType SHGetImageListFunction_ = (SHGetImageListType)GetProcAddress(shell32Library_, "SHGetImageList");

  if (shell32Library_ && SHGetImageListFunction_) {

    // Get the icon index using SHGetFileInfo
    SHFILEINFOW sfi = {0};

    SHGetFileInfo(filePath.c_str(), -1, &sfi, sizeof(sfi), SHGFI_SYSICONINDEX);

    // If iIcon is 0, we get a weird default icon representing a hand,
    // so don't continue.
    if (sfi.iIcon > 0) {
      // Retrieve the system image list.
      // To get the 48x48 icons, use SHIL_EXTRALARGE
      // To get the 256x256 icons (Vista only), use SHIL_JUMBO
      HIMAGELIST* imageList;
      int imageType;
      if (iconSize == 16) {
        imageType = SHIL_SMALL;
      } else if (iconSize == 48) {
        imageType = SHIL_EXTRALARGE;
      } else if (iconSize == 256) {
        imageType = SHIL_JUMBO;
      } else {
        imageType = SHIL_LARGE; // 32
      }
      HRESULT hResult = SHGetImageListFunction_(imageType, IID_IImageList, (void**)&imageList);

      if (hResult == S_OK) {
        // Get the icon we need from the list. Note that the HIMAGELIST we retrieved
        // earlier needs to be casted to the IImageList interface before use.
        HICON hIcon;
        hResult = ((IImageList*)imageList)->GetIcon(sfi.iIcon, ILD_TRANSPARENT, &hIcon);

        if (hResult == S_OK) {
          output.hIcon = hIcon;
          output.filePath = filePath;
          output.index = 0;
        }
      }

    }

  }

  return output;
}
