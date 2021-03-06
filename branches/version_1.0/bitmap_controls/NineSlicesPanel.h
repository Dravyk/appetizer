/*
  Copyright (C) 2008 Laurent Cozic. All right reserved.
  Use of this source code is governed by a GNU/GPL license that can be
  found in the LICENSE file.
*/

#include "../precompiled.h"

#ifndef __NineSlicesPanel_H
#define __NineSlicesPanel_H

#include "../imaging/NineSlicesPainter.h"
#include "BitmapControl.h"

class NineSlicesPanel: public BitmapControl {

  private:

    wxString filePath_;
    NineSlicesPainter* nineSlicesPainter_;
    bool gridIsExplicitelySet_;
    wxRect grid_;

  public:

    NineSlicesPanel(wxWindow *owner, int id, wxPoint point, wxSize size);
    ~NineSlicesPanel();
    void LoadImage(const wxString& filePath);
    void UpdateControlBitmap();
    void SetGrid(int left, int top, int width, int height);
    void SetGrid(const wxRect& rect);

};

#endif // __NineSlicesPanel_H