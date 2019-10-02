#ifndef _uppfun_h_
#define _uppfun_h_

#include <CtrlLib/CtrlLib.h>
using namespace Upp;

#include <string>
#include <map>

//void UMSG(const std::string &msg);
//void do_umsg(const std::string &msg);

std::string GetNewName(const std::string &stitle, const std::string &sdefault="");
std::string GetDTStamp();


//struct ListWidget : public Ctrl
//{
//	typedef ListWidget CLASSNAME;
//	typedef std::map<std::string,std::string> Map;
//	ArrayCtrl A;
//	Map M;
//	void clear()							{ A.Clear(); M.clear(); }
//	ListWidget()							{ clear(); }
//	ListWidget(const ListWidget &LW)		{ clear(); for (auto p:LW.M) M[p.first]=p.second; }
//	ListWidget(const Map &m)				{ clear(); for (auto p:m) M[p.first]=p.second; }
//	~ListWidget()							{ clear(); }
//	ListWidget& Add(const std::string &val, const std::string &key)		{ M[key]=val; return *this; }
//	ListWidget& Add(const Map &m)			{ for (auto p:m) M[p.first]=p.second;  return *this; }
//	void Remove(const std::string &key)		{ M.erase(key); }
//	void Select(const std::string &key);
//	void Select(const Map &m);
//	bool HasSelection()						{ return (A.GetSelectCount()>0); }
//	const Map GetSelection();
//	
//	Event<> WhenClick;
//	Event<> WhenDblClick;
//
//};

//---------------------------------------------------------------------------------------------------
struct ProgressBox : public Ctrl
{
	using CLASSNAME=ProgressBox;
	Label what;
	ProgressIndicator prog;
	Button cancel;
	Ctrl *pPar;
	bool bcancel{false};
	Event<> WhenCancel;
	virtual ~ProgressBox();
	ProgressBox(Ctrl *pParent);
	virtual void Paint(Draw &drw);
	void ShowProgress(int c, int t, std::string w="");
	bool IsCancelled();
	void SetCancel(bool b=true);
	virtual bool Key(dword key, int count);
};



#endif
