/*
  Copyright (C) 2008 Laurent Cozic. All right reserved.
  Use of this source code is governed by a GNU/GPL license that can be
  found in the LICENSE file.
*/

#include "../stdafx.h"

#include "ImageButton.h"


DEFINE_EVENT_TYPE(wxeEVT_CLICK)



BEGIN_EVENT_TABLE(ImageButton, BitmapControl)
  EVT_LEFT_UP(ImageButton::OnMouseUp)
  EVT_LEFT_DOWN(ImageButton::OnMouseDown)
  EVT_MOTION(ImageButton::OnMouseOver)
  EVT_LEAVE_WINDOW(ImageButton::OnMouseLeave)
  EVT_MOUSE_CAPTURE_LOST(ImageButton::OnMouseCaptureLost)
END_EVENT_TABLE()


ImageButton::ImageButton(wxWindow *owner, int id, wxPoint point, wxSize size):
BitmapControl(owner, id, point, size) {
  state_ = _T("Up");  

  downIconOffset_ = wxPoint(0,0);
  rotatedIconBitmap_ = NULL;
  iconBitmap_ = NULL;
  pressed_ = false;  
  gridIsExplicitelySet_ = false;
  
  nineSlicesPainterUp_ = NULL;
  nineSlicesPainterOver_ = NULL;
  nineSlicesPainterDown_ = NULL;
  nineSlicesPainterDisabled_ = NULL;

  bitmapUp_ = NULL;
  bitmapOver_ = NULL;
  bitmapDown_ = NULL;
  bitmapDisabled_ = NULL;

  overlayColorUp_ = wxNullColour;
  overlayColorOver_ = wxNullColour;
  overlayColorDown_ = wxNullColour;
  overlayColorDisabled_ = wxNullColour;
}


const wxPoint& ImageButton::GetDownIconOffset() {
  return downIconOffset_;
}


void ImageButton::SetDownIconOffset(const wxPoint& point) {
  if (point.x == downIconOffset_.x && point.y == downIconOffset_.y) return;
  downIconOffset_ = wxPoint(point.x, point.y);
}


bool ImageButton::Enable(bool enable) {
  bool result = BitmapControl::Enable(enable);

  if (enable) {
    state_ = _T("Up");
  } else {
    state_ = _T("Disabled");
  }

  InvalidateControlBitmap();

  return result;
}


void ImageButton::FitToImage() {
  if (filePathPrefix_ != wxEmptyString) {
    wxBitmap tempBitmap(filePathPrefix_ + _T("Up.png"), wxBITMAP_TYPE_PNG);
    if (!tempBitmap.IsOk()) return;
    SetSize(tempBitmap.GetWidth(), tempBitmap.GetHeight());
  } else {
    if (bitmapUp_ && bitmapUp_->IsOk()) {
      SetSize(bitmapUp_->GetWidth(), bitmapUp_->GetHeight());
    }
  }
}


void ImageButton::SetGrid(int left, int top, int width, int height) {
  gridIsExplicitelySet_ = true;
  grid_.SetLeft(left);
  grid_.SetTop(top);
  grid_.SetWidth(width);
  grid_.SetHeight(height);
  InvalidateControlBitmap();
}


void ImageButton::SetGrid(const wxRect& rect) {
  SetGrid(rect.GetLeft(), rect.GetTop(), rect.GetWidth(), rect.GetHeight());
}


void ImageButton::SetIcon(wxBitmap* iconBitmap, bool ownIt) {
  if (iconBitmap_ == iconBitmap) return;
  if (ownIcon_) wxDELETE(iconBitmap_);
  iconBitmap_ = iconBitmap;
  ownIcon_ = ownIt;
  wxDELETE(rotatedIconBitmap_);
  InvalidateControlBitmap();
}


void ImageButton::LoadImage(const wxString& filePathPrefix) {
  if (filePathPrefix_ == filePathPrefix) return;

  filePathPrefix_ = filePathPrefix;

  wxDELETE(bitmapUp_);
  wxDELETE(bitmapOver_);
  wxDELETE(bitmapDown_);
  wxDELETE(bitmapDisabled_);
  wxDELETE(nineSlicesPainterUp_);
  wxDELETE(nineSlicesPainterOver_);
  wxDELETE(nineSlicesPainterDown_);
  wxDELETE(nineSlicesPainterDisabled_);

  // FIXME: Currently the loaded image MUST have an alpha channel otherwise the
  // blit operations will fail.  If the loaded bitmap is fully opaque, the alpha
  // value of at least one pixel must be set to 254 or less.

  InvalidateControlBitmap();
}


void ImageButton::LoadImages(wxBitmap* bitmapUp, wxBitmap* bitmapOver, wxBitmap* bitmapDown, wxBitmap* bitmapDisabled) {
  filePathPrefix_ = wxEmptyString;

  wxDELETE(bitmapUp_);
  wxDELETE(bitmapOver_);
  wxDELETE(bitmapDown_);
  wxDELETE(bitmapDisabled_);
  wxDELETE(nineSlicesPainterUp_);
  wxDELETE(nineSlicesPainterOver_);
  wxDELETE(nineSlicesPainterDown_);
  wxDELETE(nineSlicesPainterDisabled_);

  bitmapUp_ = bitmapUp;
  bitmapOver_ = bitmapOver;
  bitmapDown_ = bitmapDown;
  bitmapDisabled_ = bitmapDisabled;

  InvalidateControlBitmap();
}


void ImageButton::SetStateColors(wxColour colorUp, wxColour colorOver, wxColour colorDown, wxColour colorDisabled) {
  overlayColorUp_ = colorUp;
  overlayColorOver_ = colorOver;
  overlayColorDown_ = colorDown;
  overlayColorDisabled_ = colorDisabled;
}


void ImageButton::UpdateControlBitmap() {
  BitmapControl::UpdateControlBitmap();
  if (!controlBitmap_) return;

  NineSlicesPainter* painter = NULL;

  if (filePathPrefix_ != wxEmptyString) {
  
    wxString filePath = filePathPrefix_ + state_ + _T(".png");

    if (!wxFileName::FileExists(filePath)) filePath = filePathPrefix_ + _T("Up.png");
    
    // Lazily create the painters
    if (state_ == _T("Disabled")) {
      if (!nineSlicesPainterDisabled_) {
        nineSlicesPainterDisabled_ = new NineSlicesPainter();
        nineSlicesPainterDisabled_->LoadImage(filePath);
      }
      painter = nineSlicesPainterDisabled_;
    } else if (state_ == _T("Down")) {
      if (!nineSlicesPainterDown_) {
        nineSlicesPainterDown_ = new NineSlicesPainter();
        nineSlicesPainterDown_->LoadImage(filePath);
      }
      painter = nineSlicesPainterDown_;
    } else if (state_ == _T("Over")) {
      if (!nineSlicesPainterOver_) {
        nineSlicesPainterOver_ = new NineSlicesPainter();
        nineSlicesPainterOver_->LoadImage(filePath);
      }
      painter = nineSlicesPainterOver_;
    } else { // default to "Up" state
      if (!nineSlicesPainterUp_) {
        nineSlicesPainterUp_ = new NineSlicesPainter();
        nineSlicesPainterUp_->LoadImage(filePath);
      }
      painter = nineSlicesPainterUp_;
    }

  } else if (bitmapUp_ != NULL) {

    // Lazily create the painters

    if (state_ == _T("Disabled")) {
      if (!bitmapDisabled_) bitmapDisabled_ = new wxBitmap(*bitmapUp_);
      if (overlayColorDisabled_ != wxNullColour) Imaging::DrawColorOverlay(*bitmapDisabled_, overlayColorDisabled_);

      if (!nineSlicesPainterDisabled_) {
        nineSlicesPainterDisabled_ = new NineSlicesPainter();
        nineSlicesPainterDisabled_->LoadImage(new wxBitmap(*bitmapDisabled_));
      }
      painter = nineSlicesPainterDisabled_;
    }
    
    if (state_ == _T("Down")) {
      if (!bitmapDown_) bitmapDown_ = new wxBitmap(*bitmapUp_);
      if (overlayColorDown_ != wxNullColour) Imaging::DrawColorOverlay(*bitmapDown_, overlayColorDown_);

      if (!nineSlicesPainterDown_) {
        nineSlicesPainterDown_ = new NineSlicesPainter();
        nineSlicesPainterDown_->LoadImage(new wxBitmap(*bitmapDown_));
      }
      painter = nineSlicesPainterDown_;
    }
    
    if (state_ == _T("Over")) {
      if (!bitmapOver_) bitmapOver_ = new wxBitmap(*bitmapUp_);
      if (overlayColorOver_ != wxNullColour) Imaging::DrawColorOverlay(*bitmapOver_, overlayColorOver_);

      if (!nineSlicesPainterOver_) {
        nineSlicesPainterOver_ = new NineSlicesPainter();
        nineSlicesPainterOver_->LoadImage(new wxBitmap(*bitmapOver_));
      }
      painter = nineSlicesPainterOver_;
    } 

    if (!painter) { // Default to "up" state
      if (!nineSlicesPainterUp_) {
        nineSlicesPainterUp_ = new NineSlicesPainter();
        nineSlicesPainterUp_->LoadImage(new wxBitmap(*bitmapUp_));
      }
      painter = nineSlicesPainterUp_;
    }

  }

  if (!painter) return;

  if (gridIsExplicitelySet_) painter->SetGrid(grid_.GetLeft(), grid_.GetTop(), grid_.GetWidth(), grid_.GetHeight());
  painter->SetRotation(GetBitmapRotation());  

  wxMemoryDC destDC;
  destDC.SelectObject(*controlBitmap_);  
  wxString n = GetName();
  painter->Draw(&destDC, 0, 0, GetClientRect().GetWidth(), GetClientRect().GetHeight());
  
  if (iconBitmap_) {
    
    wxPoint iconOffset(0,0);
    if (state_ == _T("Down")) iconOffset = downIconOffset_;

    wxASSERT_MSG(iconBitmap_->IsOk(), _T("Invalid icon"));
    
    if (GetBitmapRotation() != 0) {

      if (!rotatedIconBitmap_) {
        wxImage tempImage = iconBitmap_->ConvertToImage();
        tempImage = tempImage.Rotate90(GetBitmapRotation() == 90);
        rotatedIconBitmap_ = new wxBitmap(tempImage);
      }

      destDC.DrawBitmap(
        *rotatedIconBitmap_,
        (GetSize().GetWidth() - rotatedIconBitmap_->GetWidth()) / 2 + iconOffset.x,
        (GetSize().GetHeight() - rotatedIconBitmap_->GetHeight()) / 2 + iconOffset.y);

    } else {    
      destDC.DrawBitmap(
        *iconBitmap_,
        (GetSize().GetWidth() - iconBitmap_->GetWidth()) / 2 + iconOffset.x,
        (GetSize().GetHeight() - iconBitmap_->GetHeight()) / 2 + iconOffset.y);
    }
  }  
  
  destDC.SelectObject(wxNullBitmap);
}


ImageButton::~ImageButton() {
  if (ownIcon_) wxDELETE(iconBitmap_);

  wxDELETE(rotatedIconBitmap_);
  wxDELETE(bitmapUp_);
  wxDELETE(bitmapOver_);
  wxDELETE(bitmapDown_);
  wxDELETE(bitmapDisabled_);
  wxDELETE(nineSlicesPainterUp_);
  wxDELETE(nineSlicesPainterOver_);
  wxDELETE(nineSlicesPainterDown_);
  wxDELETE(nineSlicesPainterDisabled_);
}


void ImageButton::SetState(const wxString& state) {
  if (state_ == state) return;
  state_ = state;
  InvalidateControlBitmap();
}


wxString ImageButton::GetState() {
  return state_;
}


void ImageButton::OnMouseCaptureLost(wxMouseCaptureLostEvent& evt) {
  // Any MSW application that uses wxWindow::CaptureMouse() must implement an 
  // wxEVT_MOUSE_CAPTURE_LOST event handler as of wxWidgets 2.8.0.
  wxWindow* w = static_cast<wxWindow*>(evt.GetEventObject());
  if (w->HasCapture()) w->ReleaseMouse();
}


void ImageButton::OnMouseDown(wxMouseEvent& evt) {
  wxWindow* w = static_cast<wxWindow*>(evt.GetEventObject());
  w->CaptureMouse();

  pressed_ = true;
  SetState(_T("Down"));
  Update();
}


void ImageButton::OnMouseUp(wxMouseEvent& evt) {
  wxWindow* w = static_cast<wxWindow*>(evt.GetEventObject());
  if (w->HasCapture()) w->ReleaseMouse();

  wxRect zeroRect(0, 0, GetSize().GetWidth(), GetSize().GetHeight());

  pressed_ = false;
  SetState(_T("Up"));
  Update();

  if (zeroRect.Contains(evt.GetPosition())) {
    wxCommandEvent newEvent(wxeEVT_CLICK);
    newEvent.SetEventObject(this);
    GetEventHandler()->ProcessEvent(newEvent);
  }
}


void ImageButton::OnMouseOver(wxMouseEvent& evt) {
  wxWindow* w = static_cast<wxWindow*>(evt.GetEventObject());

  if (pressed_) {
    SetState(_T("Down"));
  } else {
    SetState(_T("Over"));
  }  
}


void ImageButton::OnMouseLeave(wxMouseEvent& evt) {
  SetState(_T("Up"));
}