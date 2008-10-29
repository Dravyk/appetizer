#ifndef __Controller_H
#define __Controller_H

#include "wx/wx.h" 
#include "MainFrame.h"
#include "Constants.h"
#include "User.h"
#include "boost/shared_ptr.hpp"
#include <wx/stopwatch.h>


class Controller {

  public:

    Controller();      
    UserSP GetUser();
    void SetDraggedFolderItem(int folderItemId);
    FolderItemSP GetDraggedFolderItem();
    long GetTimer();

    /**
     * GLOBAL EVENTS
     */

    void User_FolderItemCollectionChange();
    void User_FolderItemChange(FolderItemSP folderItem);
    void User_LocaleChange();
    void User_IconSizeChange();

  private:
      
    UserSP user_;
    wxString applicationDrive_;
    int draggedFolderItemId_;
    wxStopWatch stopWatch_;

};

typedef boost::shared_ptr<Controller> ControllerSP;

#endif
