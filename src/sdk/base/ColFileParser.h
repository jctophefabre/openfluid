/**
  \file ColFileParser.h
  \brief header of column file parser

  \author Jean-Christophe FABRE <fabrejc@ensam.inra.fr>
*/

#ifndef __COLFILEPARSER_H__
#define __COLFILEPARSER_H__


#include <wx/wx.h>
#include <wx/textfile.h>

namespace mhydasdk { namespace base {


WX_DEFINE_ARRAY(wxArrayString*, ArrayFileContents);

/**
  Class for column file management and handling
*/
class ColumnFileParser
{

  protected:

  private:

    wxString m_FileName;
    wxString m_Delimiter;
    wxString m_CommentSymbol;

    ArrayFileContents *m_FileContents;

    wxArrayString* tokenizeLine(wxString Line);

    bool checkContents();

    bool isCommentLineStr(wxString LineStr);

    bool isEmptyLineStr(wxString LineStr);

    int m_LinesCount;

    int m_ColsCount;


  public:

    /**
      Constructor
    */
    ColumnFileParser(wxString FileName,  wxString CommentLineSymbol = wxT(""), wxString Delimiter = wxT(" \t\r\n"));

    /**
      Destructor
    */
    ~ColumnFileParser();

    /**
      Loads and checks file
    */
    bool parseFile();

    /**
      Returns the value at a specified row-column, as a string
    */
    wxString getValue(int Line, int Column);

    bool getStringValue(int Line, int Column, wxString *Value);

    /**
      Returns the value at a specified row-column, as an int
    */
    bool getLongValue(int Line, int Column, long* Value);


    /**
      Returns the value at a specified row-column, as a double
    */
    bool getDoubleValue(int Line, int Column, double* Value);

    /**
      Returns the values of a line as astring list
    */
    wxArrayString* getValues(int Line);

    int getLinesCount() const { return m_LinesCount;};

    int getColsCount() const { return m_ColsCount;};


};



} } // namespace mhydasdk::base


#endif


