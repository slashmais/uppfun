
#include "uppfun.h"
#include <utilfuncs/utilfuncs.h>

//#include <thread>


//struct UMsg : public TopWindow
//{
//	typedef UMsg CLASSNAME;
//	virtual ~UMsg() {}
//	void showmsg(const std::string &msg) const { PromptOK(DeQtf(msg.c_str())); }
//};
//
//void do_umsg(const std::string &msg)
//{
//	UMsg u;
//	u.Execute();
//	u.showmsg(msg);
//}
//
//void UMSG(const std::string &msg)
//{
//	std::thread(do_umsg, msg).detach();
//}


//==============================================================================================(GetNewName)
std::string GetNewName(const std::string &stitle, const std::string &sdefault)
{
	std::string s;
	struct NNDlg : public TopWindow
	{
		//using CLASSNAME=NNDlg; enable for THISFN, Event<>,..
		EditString e;
		Button k;
		Button c;
		std::string sN;

		virtual ~NNDlg(){}
		NNDlg(const std::string &st, const std::string &sd)
		{
			SetRect(Size(350, 70));
			Title(st.c_str());
			Add(e.HSizePosZ().TopPos(0,20));
			e.SetData(sd.c_str());
			Add(k.SetLabel(t_("OK")).RightPosZ(140, 60).TopPosZ(30, 20));
			Add(c.SetLabel(t_("Cancel")).RightPosZ(70, 60).TopPosZ(30, 20));
			k.WhenAction << [&]{ sN=e.GetData().ToString().ToStd(); TRIM(sN); Close(); };
			c.WhenAction << [&]{ sN=""; Close(); };
		}
		bool Key(dword key, int) { if (key==K_ENTER) { k.WhenAction(); return true; } else if (key==K_ESCAPE) { c.WhenAction(); return true; } return false; }
	};
	NNDlg dlg(stitle, sdefault);
	dlg.Execute();
	s=dlg.sN;
	return s;
}

std::string GetDTStamp()
{
	std::string s{};
	struct DTDlg : public TopWindow
	{
		//using CLASSNAME=NNDlg; enable for THISFN, Event<>,..
		Label x;
		EditString e;
		Button n;
		Button k;
		Button c;
		std::string sN;

		virtual ~DTDlg(){}
		DTDlg()
		{
			SetRect(Size(350, 110));
			Title("Specify Date-time-stamp");
			Add(x.SetLabel(t_("Format: yyyymmddHHMMSS")).HSizePosZ(3,3).TopPos(3, 20));
			Add(e.HSizePosZ(3,3).TopPos(23,20));
			Add(n.SetLabel(t_("Use Now")).RightPosZ(170, 60).TopPosZ(50, 20));
			Add(k.SetLabel(t_("OK")).RightPosZ(100, 60).TopPosZ(50, 20));
			Add(c.SetLabel(t_("Cancel")).RightPosZ(30, 60).TopPosZ(50, 20));
			n.WhenAction << [&]{ sN=ymdhms_stamp(); Close(); };
			k.WhenAction << [&]{ sN=e.GetData().ToString().ToStd(); TRIM(sN); Close(); };
			c.WhenAction << [&]{ sN=""; Close(); };
			e.Clear();
			k.Enable(false);
			e.WhenAction << [&]
					{
						auto vdt=[](std::string s)->bool
								{
									if (s.empty()||(s.size()!=14)) return false;
									int y=stot<uint32_t>(s.substr(0, 4));
									int m=stot<uint32_t>(s.substr(4, 2));
									bool b=is_leap_year(y);
									int d=stot<uint32_t>(s.substr(6, 2));
									if (y<1970) return false;
									if (m>12) return false;
									if ((b&&(m==2)&&(d>29))||(!b&&(m==2)&&(d>28))) return false;
									if (((m==1)||(m==3)||(m==5)||(m==7)||(m==8)||(m==10)||(m==12))&&(d>31)) return false;
									if (((m==4)||(m==6)||(m==9)||(m==11))&&(d>30)) return false;
									if (stot<uint32_t>(s.substr(8, 2))>23) return false;
									if (stot<uint32_t>(s.substr(10, 2))>59) return false;
									if (stot<uint32_t>(s.substr(12, 2))>59) return false;
									return true;
								};
						k.Enable(vdt(e.GetData().ToString().ToStd()));
					};
		}
		bool Key(dword key, int) { if (key==K_ENTER) { k.WhenAction(); return true; } else if (key==K_ESCAPE) { c.WhenAction(); return true; } return false; }
	};
	DTDlg dlg;
	dlg.Execute();
	s=dlg.sN;
	return s;
}


//==============================================================================================(ListWidget)

//void ListWidget::Select(const std::string &key)
//{
//}
//
//void ListWidget::Select(const Map &m)
//{
//}
//
//const Map ListWidget::GetSelection()
//{
//}


//==============================================================================================
ProgressBox::~ProgressBox()
{
	pPar->RemoveChild(this);
}

ProgressBox::ProgressBox(Ctrl *pParent)
{
	pPar=pParent;
	Size sz=pPar->GetSize();
	SetRect((sz.cx-400)/2, (sz.cy-100)/2, 400, 100);
	bcancel=false;
	AddFrame(ThinInsetFrame());
	Add(what.HSizePosZ(8, 12).TopPosZ(8, 19));
	Add(prog.HSizePosZ(8, 12).TopPosZ(32, 12));
	Add(cancel.SetLabel(t_("Cancel")).RightPosZ(12, 60).BottomPosZ(12, 20));
	cancel.WhenAction = [&]{ bcancel=true; if (WhenCancel) WhenCancel(); };
	pPar->Add(*this);
	pPar->Sync();
}

void ProgressBox::Paint(Draw &drw) { drw.DrawRect(GetSize(), SColorFace()); }
void ProgressBox::ShowProgress(int c, int t, std::string w)
 {
  what.SetLabel(w.c_str());
   prog.Set(c, t);
  }
bool ProgressBox::IsCancelled() { return bcancel; }
void ProgressBox::SetCancel(bool b) { cancel.Enable(b); }
bool ProgressBox::Key(dword key, int count) { if (key==K_ESCAPE) { cancel.WhenAction(); return true; } return false; }

