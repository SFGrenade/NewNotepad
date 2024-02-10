#include "main.hpp"


char* strconcat( char const* s1, char const* s2 ) {
  char* result = (char*)calloc( strlen( s1 ) + strlen( s2 ) + 1, sizeof( char ) );  // +1 for the null-terminator
  // in real code you would check for errors in malloc here
  strcpy( result, s1 );
  strcat( result, s2 );
  return result;
}

// void MyLog( std::string message ) {
//   fprintf( fileOut, ( message + "\n" ).c_str() );
//   fflush( fileOut );
// }

void MyLog( char const* format, ... ) {
  va_list ap;
  char buffer[2048] = { 0 };
  sprintf( buffer, format, ap );
  char* formatWithNewline = strconcat( buffer, "\n" );
  fprintf( fileOut, formatWithNewline );
  free( formatWithNewline );
  fflush( fileOut );
}

void MessageBoxInfo( std::string const& title, std::string const& message ) {
  if( !MessageBoxA( NULL, message.c_str(), title.c_str(), MB_OK | MB_ICONINFORMATION ) ) {
    LPSTR formatString;
    FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | 0xFF, NULL, GetLastError(), 0, (LPTSTR)&formatString, 1, NULL );
    MyLog( "Error when for message box '%s': %s", title.c_str(), formatString );
  }
}

void MessageBoxError( std::string const& title, std::string const& message ) {
  if( !MessageBoxA( NULL, message.c_str(), title.c_str(), MB_OK | MB_ICONEXCLAMATION ) ) {
    LPSTR formatString;
    FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | 0xFF, NULL, GetLastError(), 0, (LPTSTR)&formatString, 1, NULL );
    MyLog( "Error when for message box '%s': %s", title.c_str(), formatString );
  }
}

LRESULT WinProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ) {
  static HWND editControlHandle;

  CHAR lpszLatin[]
      = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras nec venenatis ligula, vel finibus sem. Donec ut orci ut lorem rutrum congue. Nam "
        "blandit suscipit vestibulum. Nullam at porttitor nibh. Sed vitae efficitur odio. Donec tincidunt mollis tortor, id facilisis elit laoreet sed. "
        "Vestibulum eleifend tortor sem, quis ornare tellus tempus scelerisque. In ac hendrerit nibh, sit amet molestie lorem.\r\n"
        "Donec vel lectus mi. Duis tristique tortor in lectus pellentesque, cursus hendrerit tellus fermentum. Etiam nec ex justo. Aenean finibus, sapien "
        "vitae malesuada accumsan, arcu mauris bibendum ipsum, ac blandit urna eros tristique odio. Suspendisse fringilla sapien eget massa lobortis, porta "
        "viverra leo egestas. Curabitur non augue purus. Ut sollicitudin auctor libero in facilisis. Fusce nec auctor urna. Cras accumsan imperdiet "
        "sodales.\r\n"
        "Proin id imperdiet libero. Proin volutpat sem sollicitudin, efficitur nulla eget, pulvinar ante. Aliquam interdum justo lectus, vel pulvinar metus "
        "pellentesque non. Etiam placerat tellus vitae arcu consequat tempus. Nam in ipsum leo. Duis fringilla mauris dictum diam eleifend placerat. Fusce "
        "lacus mauris, bibendum mollis libero id, fringilla condimentum augue. Phasellus interdum sed odio vitae tincidunt. Donec consectetur risus ac cursus "
        "ornare.\r\n"
        "Vivamus condimentum tempus posuere. Sed in est sit amet ex condimentum sodales et non sem. Sed magna lectus, hendrerit in eros a, condimentum "
        "egestas ex. Maecenas euismod blandit neque, et lacinia erat hendrerit quis. Nunc cursus ex dignissim sodales ornare. In gravida finibus lacus, ut "
        "eleifend velit congue nec. Phasellus et ipsum in dui scelerisque tincidunt. Pellentesque sed elementum massa, eu venenatis ante. Mauris placerat "
        "felis ac augue hendrerit, sit amet viverra dui dignissim.\r\n"
        "Aenean ut eros leo. Pellentesque magna turpis, pretium nec mauris sit amet, rhoncus dignissim massa. Sed rhoncus sagittis dapibus. Duis in mollis "
        "ipsum. In sapien lectus, hendrerit ut imperdiet in, pharetra ut quam. In at ante ut dui dapibus venenatis ut condimentum dolor. Quisque ac accumsan "
        "massa, quis tempus tortor. Pellentesque ac lorem lectus. Maecenas vitae nunc nunc.\r\n";

  if( uMsg == WM_CREATE ) {
    editControlHandle = CreateWindowExA( 0,
                                         "Edit",
                                         NULL,
                                         WS_CHILD | WS_VISIBLE | ES_LEFT | ES_MULTILINE | WS_VSCROLL | ES_AUTOVSCROLL | WS_HSCROLL | ES_AUTOHSCROLL | ES_NUMBER,
                                         0,
                                         0,
                                         0,
                                         0,
                                         hWnd,
                                         (HMENU)ID_CONTROL_EDIT,
                                         (HINSTANCE)GetWindowLongPtr( hWnd, GWLP_HINSTANCE ),
                                         NULL );
    SendMessageA( editControlHandle, WM_SETTEXT, 0, (LPARAM)lpszLatin );
    SendMessageA( editControlHandle, ES_READONLY, FALSE, 0 );
    return 0;
  }
  if( uMsg == WM_COMMAND ) {
    WORD command = LOWORD( wParam );
    MyLog( "WinProc - WM_COMMAND with %p", command );
    bool commandHandled = false;
    if( command == ID_MENU_FILE_NEW ) {
      SendMessageA( editControlHandle, WM_CLEAR, 0, 0 );
      SendMessageA( editControlHandle, EM_EMPTYUNDOBUFFER, 0, 0 );
      commandHandled = true;
    }
    if( command == ID_MENU_FILE_OPEN ) {
      MessageBoxInfo( "ToDo", "ToDo: Implement" );
      commandHandled = true;
    }
    if( command == ID_MENU_FILE_SAVE ) {
      MessageBoxInfo( "ToDo", "ToDo: Implement" );
      commandHandled = true;
    }
    if( command == ID_MENU_FILE_SAVEAS ) {
      MessageBoxInfo( "ToDo", "ToDo: Implement" );
      commandHandled = true;
    }
    if( command == ID_MENU_FILE_EXIT ) {
      DestroyWindow( hWnd );
      commandHandled = true;
    }
    if( command == ID_MENU_EDIT_UNDO ) {
      if( SendMessageA( editControlHandle, EM_CANUNDO, 0, 0 ) ) {
        SendMessageA( editControlHandle, EM_UNDO, 0, 0 );
      } else {
        MessageBoxInfo( "Undo notification", "Nothing to undo." );
      }
      commandHandled = true;
    }
    if( command == ID_MENU_EDIT_CUT ) {
      SendMessageA( editControlHandle, WM_CUT, 0, 0 );
      commandHandled = true;
    }
    if( command == ID_MENU_EDIT_COPY ) {
      SendMessageA( editControlHandle, WM_COPY, 0, 0 );
      commandHandled = true;
    }
    if( command == ID_MENU_EDIT_PASTE ) {
      SendMessageA( editControlHandle, WM_PASTE, 0, 0 );
      commandHandled = true;
    }
    if( command == ID_MENU_EDIT_DELETE ) {
      SendMessageA( editControlHandle, WM_CLEAR, 0, 0 );
      commandHandled = true;
    }
    if( command == ID_MENU_EDIT_SEARCHWEB ) {
      MessageBoxInfo( "ToDo", "ToDo: Implement" );
      commandHandled = true;
    }
    if( command == ID_MENU_EDIT_FIND ) {
      MessageBoxInfo( "ToDo", "ToDo: Implement" );
      commandHandled = true;
    }
    if( command == ID_MENU_EDIT_FINDNEXT ) {
      MessageBoxInfo( "ToDo", "ToDo: Implement" );
      commandHandled = true;
    }
    if( command == ID_MENU_EDIT_FINDPREVIOUS ) {
      MessageBoxInfo( "ToDo", "ToDo: Implement" );
      commandHandled = true;
    }
    if( command == ID_MENU_EDIT_REPLACE ) {
      MessageBoxInfo( "ToDo", "ToDo: Implement" );
      commandHandled = true;
    }
    if( command == ID_MENU_EDIT_GOTO ) {
      MessageBoxInfo( "ToDo", "ToDo: Implement" );
      commandHandled = true;
    }
    if( command == ID_MENU_EDIT_SELECTALL ) {
      MessageBoxInfo( "ToDo", "ToDo: Implement" );
      commandHandled = true;
    }
    if( command == ID_MENU_EDIT_TIMEDATE ) {
      MessageBoxInfo( "ToDo", "ToDo: Implement" );
      commandHandled = true;
    }
    if( command == ID_MENU_FORMAT_WORDWRAP ) {
      MessageBoxInfo( "ToDo", "ToDo: Implement" );
      commandHandled = true;
    }
    if( command == ID_MENU_FORMAT_FONT ) {
      MessageBoxInfo( "ToDo", "ToDo: Implement" );
      commandHandled = true;
    }
    if( command == ID_MENU_VIEW_ZOOM_IN ) {
      MessageBoxInfo( "ToDo", "ToDo: Implement" );
      commandHandled = true;
    }
    if( command == ID_MENU_VIEW_ZOOM_OUT ) {
      MessageBoxInfo( "ToDo", "ToDo: Implement" );
      commandHandled = true;
    }
    if( command == ID_MENU_VIEW_ZOOM_DEFAULT ) {
      MessageBoxInfo( "ToDo", "ToDo: Implement" );
      commandHandled = true;
    }
    if( command == ID_MENU_VIEW_STATUSBAR ) {
      MessageBoxInfo( "ToDo", "ToDo: Implement" );
      commandHandled = true;
    }
    if( command == ID_MENU_HELP_VIEWHELP ) {
      MessageBoxInfo( "ToDo", "ToDo: Implement" );
      commandHandled = true;
    }
    if( command == ID_MENU_HELP_SENDFEEDBACK ) {
      MessageBoxInfo( "ToDo", "ToDo: Implement" );
      commandHandled = true;
    }
    if( command == ID_MENU_HELP_ABOUT ) {
      CHAR szFileName[1024];
      GetModuleFileNameA( windowClass.hInstance, szFileName, sizeof( szFileName ) / sizeof( szFileName[0] ) );
      MessageBoxInfo( szFileName, "This program is:" );
      commandHandled = true;
    }
    if( commandHandled ) {
      MyLog( "Lines in the editor: %d", SendMessageA( editControlHandle, EM_GETLINECOUNT, 0, 0 ) );
      return 0;
    }
    return DefWindowProcA( hWnd, uMsg, wParam, lParam );
  }
  if( uMsg == WM_HOTKEY ) {
    MyLog( "WinProc - WM_HOTKEY with %p %p", wParam, lParam );
    bool commandHandled = false;
    if( wParam == ID_MENU_FILE_NEW ) {
      MessageBoxInfo( "ToDo", "ToDo: Implement" );
      commandHandled = true;
    }
    if( wParam == ID_MENU_FILE_OPEN ) {
      MessageBoxInfo( "ToDo", "ToDo: Implement" );
      commandHandled = true;
    }
    if( wParam == ID_MENU_FILE_SAVE ) {
      MessageBoxInfo( "ToDo", "ToDo: Implement" );
      commandHandled = true;
    }
    if( wParam == ID_MENU_FILE_SAVEAS ) {
      MessageBoxInfo( "ToDo", "ToDo: Implement" );
      commandHandled = true;
    }
    if( wParam == ID_MENU_FILE_EXIT ) {
      DestroyWindow( hWnd );
      commandHandled = true;
    }
    if( wParam == ID_MENU_EDIT_UNDO ) {
      if( SendMessageA( editControlHandle, EM_CANUNDO, 0, 0 ) ) {
        SendMessageA( editControlHandle, EM_UNDO, 0, 0 );
      } else {
        MessageBoxInfo( "Undo notification", "Nothing to undo." );
      }
      commandHandled = true;
    }
    if( wParam == ID_MENU_EDIT_CUT ) {
      SendMessageA( editControlHandle, WM_CUT, 0, 0 );
      commandHandled = true;
    }
    if( wParam == ID_MENU_EDIT_COPY ) {
      SendMessageA( editControlHandle, WM_COPY, 0, 0 );
      commandHandled = true;
    }
    if( wParam == ID_MENU_EDIT_PASTE ) {
      SendMessageA( editControlHandle, WM_PASTE, 0, 0 );
      commandHandled = true;
    }
    if( wParam == ID_MENU_EDIT_DELETE ) {
      SendMessageA( editControlHandle, WM_CLEAR, 0, 0 );
      commandHandled = true;
    }
    if( wParam == ID_MENU_EDIT_SEARCHWEB ) {
      MessageBoxInfo( "ToDo", "ToDo: Implement" );
      commandHandled = true;
    }
    if( wParam == ID_MENU_EDIT_FIND ) {
      MessageBoxInfo( "ToDo", "ToDo: Implement" );
      commandHandled = true;
    }
    if( wParam == ID_MENU_EDIT_FINDNEXT ) {
      MessageBoxInfo( "ToDo", "ToDo: Implement" );
      commandHandled = true;
    }
    if( wParam == ID_MENU_EDIT_FINDPREVIOUS ) {
      MessageBoxInfo( "ToDo", "ToDo: Implement" );
      commandHandled = true;
    }
    if( wParam == ID_MENU_EDIT_REPLACE ) {
      MessageBoxInfo( "ToDo", "ToDo: Implement" );
      commandHandled = true;
    }
    if( wParam == ID_MENU_EDIT_GOTO ) {
      MessageBoxInfo( "ToDo", "ToDo: Implement" );
      commandHandled = true;
    }
    if( wParam == ID_MENU_EDIT_SELECTALL ) {
      MessageBoxInfo( "ToDo", "ToDo: Implement" );
      commandHandled = true;
    }
    if( wParam == ID_MENU_EDIT_TIMEDATE ) {
      MessageBoxInfo( "ToDo", "ToDo: Implement" );
      commandHandled = true;
    }
    if( wParam == ID_MENU_FORMAT_WORDWRAP ) {
      MessageBoxInfo( "ToDo", "ToDo: Implement" );
      commandHandled = true;
    }
    if( wParam == ID_MENU_FORMAT_FONT ) {
      MessageBoxInfo( "ToDo", "ToDo: Implement" );
      commandHandled = true;
    }
    if( wParam == ID_MENU_VIEW_ZOOM_IN ) {
      MessageBoxInfo( "ToDo", "ToDo: Implement" );
      commandHandled = true;
    }
    if( wParam == ID_MENU_VIEW_ZOOM_OUT ) {
      MessageBoxInfo( "ToDo", "ToDo: Implement" );
      commandHandled = true;
    }
    if( wParam == ID_MENU_VIEW_ZOOM_DEFAULT ) {
      MessageBoxInfo( "ToDo", "ToDo: Implement" );
      commandHandled = true;
    }
    if( wParam == ID_MENU_VIEW_STATUSBAR ) {
      MessageBoxInfo( "ToDo", "ToDo: Implement" );
      commandHandled = true;
    }
    if( wParam == ID_MENU_HELP_VIEWHELP ) {
      MessageBoxInfo( "ToDo", "ToDo: Implement" );
      commandHandled = true;
    }
    if( wParam == ID_MENU_HELP_SENDFEEDBACK ) {
      MessageBoxInfo( "ToDo", "ToDo: Implement" );
      commandHandled = true;
    }
    if( wParam == ID_MENU_HELP_ABOUT ) {
      CHAR szFileName[1024];
      GetModuleFileNameA( windowClass.hInstance, szFileName, sizeof( szFileName ) / sizeof( szFileName[0] ) );
      MessageBoxInfo( "This program is:", szFileName );
      commandHandled = true;
    }
    if( commandHandled ) {
      return 0;
    }
    return DefWindowProcA( hWnd, uMsg, wParam, lParam );
  }
  if( uMsg == WM_SETFOCUS ) {
    SetFocus( editControlHandle );
    return 0;
  }
  if( uMsg == WM_SIZE ) {
    MoveWindow( editControlHandle, 0, 0, LOWORD( lParam ), HIWORD( lParam ), TRUE );
    return 0;
  }
  if( uMsg == WM_CLOSE ) {
    DestroyWindow( hWnd );
    return 0;
  }
  if( uMsg == WM_DESTROY ) {
    PostQuitMessage( 0 );
    return 0;
  }
  return DefWindowProcA( hWnd, uMsg, wParam, lParam );
}

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE a, PSTR b, int nCmdShow ) {
  fopen_s( &fileOut, "log.log", "w" );
  MyLog( "WinMain(hInstance = %p, a = %p, b = %s, nCmdShow = %d)", hInstance, a, b, nCmdShow );

  HWND windowHandle;
  MSG msg;

  // Step 1: Registering the Window Class
  windowClass.cbSize = sizeof( WNDCLASSEXA );
  windowClass.style = 0;
  windowClass.lpfnWndProc = WinProc;
  windowClass.cbClsExtra = 0;
  windowClass.cbWndExtra = 0;
  windowClass.hInstance = hInstance;
  windowClass.hIcon = LoadIcon( NULL, IDI_APPLICATION );
  windowClass.hCursor = LoadCursor( NULL, IDC_ARROW );
  windowClass.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
  windowClass.lpszMenuName = NULL;
  windowClass.lpszClassName = CLASS_NAME;
  windowClass.hIconSm = LoadIcon( NULL, IDI_APPLICATION );

  if( !RegisterClassExA( &windowClass ) ) {
    MessageBoxError( "Error!", "Window Registration Failed!" );
    return 0;
  }
  MyLog( "Class registered" );

  windowHandle
      = CreateWindowExA( WS_EX_WINDOWEDGE, CLASS_NAME, "New Notepad", WS_TILEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 500, 500, NULL, NULL, hInstance, NULL );

  if( windowHandle == NULL ) {
    MessageBoxError( "Error!", "Window Creation Failed!" );
    return 0;
  }
  MyLog( "Window created" );

  HMENU windowFileMenuHandle = CreateMenu();
  AppendMenuA( windowFileMenuHandle, MF_STRING, ID_MENU_FILE_NEW, "New" );
  AppendMenuA( windowFileMenuHandle, MF_STRING, ID_MENU_FILE_OPEN, "Open..." );
  AppendMenuA( windowFileMenuHandle, MF_STRING, ID_MENU_FILE_SAVE, "Save" );
  AppendMenuA( windowFileMenuHandle, MF_STRING, ID_MENU_FILE_SAVEAS, "Save As..." );
  AppendMenuA( windowFileMenuHandle, MF_SEPARATOR, 0, NULL );
  AppendMenuA( windowFileMenuHandle, MF_STRING, ID_MENU_FILE_EXIT, "Exit" );

  HMENU windowEditMenuHandle = CreateMenu();
  AppendMenuA( windowEditMenuHandle, MF_STRING, ID_MENU_EDIT_UNDO, "Undo" );
  AppendMenuA( windowEditMenuHandle, MF_SEPARATOR, 0, NULL );
  AppendMenuA( windowEditMenuHandle, MF_STRING, ID_MENU_EDIT_CUT, "Cut" );
  AppendMenuA( windowEditMenuHandle, MF_STRING, ID_MENU_EDIT_COPY, "Copy" );
  AppendMenuA( windowEditMenuHandle, MF_STRING, ID_MENU_EDIT_PASTE, "Paste" );
  AppendMenuA( windowEditMenuHandle, MF_STRING, ID_MENU_EDIT_DELETE, "Delete" );
  AppendMenuA( windowEditMenuHandle, MF_SEPARATOR, 0, NULL );
  AppendMenuA( windowEditMenuHandle, MF_STRING, ID_MENU_EDIT_SEARCHWEB, "Search with Bing..." );
  AppendMenuA( windowEditMenuHandle, MF_STRING, ID_MENU_EDIT_FIND, "Find..." );
  AppendMenuA( windowEditMenuHandle, MF_STRING, ID_MENU_EDIT_FINDNEXT, "Find Next" );
  AppendMenuA( windowEditMenuHandle, MF_STRING, ID_MENU_EDIT_FINDPREVIOUS, "Find Previous" );
  AppendMenuA( windowEditMenuHandle, MF_STRING, ID_MENU_EDIT_REPLACE, "Replace..." );
  AppendMenuA( windowEditMenuHandle, MF_STRING, ID_MENU_EDIT_GOTO, "Go To..." );
  AppendMenuA( windowEditMenuHandle, MF_SEPARATOR, 0, NULL );
  AppendMenuA( windowEditMenuHandle, MF_STRING, ID_MENU_EDIT_SELECTALL, "Select Al" );
  AppendMenuA( windowEditMenuHandle, MF_STRING, ID_MENU_EDIT_TIMEDATE, "Time/Date" );

  HMENU windowFormatMenuHandle = CreateMenu();
  AppendMenuA( windowFormatMenuHandle, MF_STRING, ID_MENU_FORMAT_WORDWRAP, "Word Wrap" );
  AppendMenuA( windowFormatMenuHandle, MF_STRING, ID_MENU_FORMAT_FONT, "Font..." );

  HMENU windowViewZoomMenuHandle = CreateMenu();
  AppendMenuA( windowViewZoomMenuHandle, MF_STRING, ID_MENU_VIEW_ZOOM_IN, "Zoom In" );
  AppendMenuA( windowViewZoomMenuHandle, MF_STRING, ID_MENU_VIEW_ZOOM_OUT, "Zoom Out" );
  AppendMenuA( windowViewZoomMenuHandle, MF_STRING, ID_MENU_VIEW_ZOOM_DEFAULT, "Restore Default Zoom" );
  HMENU windowViewMenuHandle = CreateMenu();
  AppendMenuA( windowViewMenuHandle, MF_POPUP, (UINT_PTR)windowViewZoomMenuHandle, "Zoom" );
  AppendMenuA( windowViewMenuHandle, MF_STRING, ID_MENU_VIEW_STATUSBAR, "Status Bar" );

  HMENU windowHelpMenuHandle = CreateMenu();
  AppendMenuA( windowHelpMenuHandle, MF_STRING, ID_MENU_HELP_VIEWHELP, "View Help" );
  AppendMenuA( windowHelpMenuHandle, MF_STRING, ID_MENU_HELP_SENDFEEDBACK, "Send Feedback" );
  AppendMenuA( windowHelpMenuHandle, MF_SEPARATOR, 0, NULL );
  AppendMenuA( windowHelpMenuHandle, MF_STRING, ID_MENU_HELP_ABOUT, "About New Notepad" );

  HMENU windowMenuBarHandle = CreateMenu();
  AppendMenuA( windowMenuBarHandle, MF_POPUP, (UINT_PTR)windowFileMenuHandle, "File" );
  AppendMenuA( windowMenuBarHandle, MF_POPUP, (UINT_PTR)windowEditMenuHandle, "Edit" );
  AppendMenuA( windowMenuBarHandle, MF_POPUP, (UINT_PTR)windowFormatMenuHandle, "Format" );
  AppendMenuA( windowMenuBarHandle, MF_POPUP, (UINT_PTR)windowViewMenuHandle, "View" );
  AppendMenuA( windowMenuBarHandle, MF_POPUP, (UINT_PTR)windowHelpMenuHandle, "Help" );

  SetMenu( windowHandle, windowMenuBarHandle );

  RegisterHotKey( windowHandle, ID_MENU_FILE_NEW, MOD_CONTROL, VK_KEY_N );

  DrawMenuBar( windowHandle );
  ShowWindow( windowHandle, nCmdShow );

  while( GetMessageA( &msg, NULL, 0, 0 ) > 0 ) {
    TranslateMessage( &msg );
    DispatchMessageA( &msg );
  }

  fclose( fileOut );

  return 0;
}
