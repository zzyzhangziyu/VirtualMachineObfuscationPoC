#include "../../include/drivers/sysbus.hpp"

#ifdef _WIN32_DEV_ENVIRONMENT
    class WIN32: public SYSBUS {
        public:
            WIN32();
            ~WIN32();
            int createDirectory();
            int deleteDirectory();
            int moveDirectory();
            int copyDirectory();
            int createFile();
            int deleteFile();
            int moveFile();
            int copyFile();

        private:
            int rmtree(const char *path);

    };

    WIN32::WIN32() { }

    WIN32::~WIN32() { }

    int WIN32::createDirectory(std::string dirName, int dirMode)
    {
        if (CreateDirectoryA(dirName.c_str(), NULL)) return DIR_CREATED;
        else if (ERROR_ALREADY_EXISTS == GetLastError()) return DIR_EXIST;
        else return OTHER_ERROR;
    }

    int WIN32::deleteDirectory()
    {
        /*
            bool DeleteDirectory(LPCTSTR lpszDir, bool noRecycleBin = true)
{
  int len = _tcslen(lpszDir);
  TCHAR *pszFrom = new TCHAR[len+2];
  _tcscpy(pszFrom, lpszDir);
  pszFrom[len] = 0;
  pszFrom[len+1] = 0;
  
  SHFILEOPSTRUCT fileop;
  fileop.hwnd   = NULL;    // no status display
  fileop.wFunc  = FO_DELETE;  // delete operation
  fileop.pFrom  = pszFrom;  // source file name as double null terminated string
  fileop.pTo    = NULL;    // no destination needed
  fileop.fFlags = FOF_NOCONFIRMATION|FOF_SILENT;  // do not prompt the user
  
  if(!noRecycleBin)
    fileop.fFlags |= FOF_ALLOWUNDO;

  fileop.fAnyOperationsAborted = FALSE;
  fileop.lpszProgressTitle     = NULL;
  fileop.hNameMappings         = NULL;

  int ret = SHFileOperation(&fileop);
  delete [] pszFrom;  
  return (ret == 0);
}

int main() 
{
  DeleteDirectory("d:\\Test", false);
  
        */
    }
#endif