/* script_win.c

  part of rutty
  record and replay putty, scripting the easy way
*/

//extern void *ldisc;  /* defined in window.c */
static Ldisc *ldisc;
//extern HWND hwnd;    /* in winstuff.h */


/* sort of copy of prompt_keyfile in winpgen.c
*/
int prompt_scriptfile(HWND hwnd, char * filename)
{
    OPENFILENAME of;
    memset(&of, 0, sizeof(of));
    of.hwndOwner = hwnd;
    of.lpstrFilter = "所有文件(*.*)\0*\0\0\0";
    of.lpstrCustomFilter = NULL;
    of.nFilterIndex = 1;
    of.lpstrFile = filename;
    *filename = '\0';
    of.nMaxFile = FILENAME_MAX;
    of.lpstrFileTitle = NULL;
    of.lpstrTitle = "选择脚本文件";
    of.Flags = 0;
    return request_file(NULL, &of, FALSE, 1);
}


/* timeout message
*/
void script_fail(char * message)
{
    MessageBox(MainHwnd,message,appname,MB_OK | MB_ICONEXCLAMATION); //
}


/* change script entry in the menu
*/
void script_menu(ScriptData * scriptdata)
{
  int i;
  for (i = 0; i < lenof(popup_menus); i++)
  {
    if(scriptdata->runs)
    {
      ModifyMenu(popup_menus[i].menu, IDM_SCRIPTSEND, MF_BYCOMMAND | MF_ENABLED, IDM_SCRIPTHALT, "停止发送脚本");
    }
    else
    {
      ModifyMenu(popup_menus[i].menu, IDM_SCRIPTHALT, MF_BYCOMMAND | MF_ENABLED, IDM_SCRIPTSEND, "发送脚本文件");
    }
  }
}


/* end of file */
