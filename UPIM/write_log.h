#ifndef RC_WriteLog_H
#define RC_WriteLog_H

#pragma once
#include <string>
#ifdef _WIN32
//#include <boost/lexical_cast.hpp>
//#define TOSTR(a) boost::lexical_cast<std::string>((a))
//glog
#define GOOGLE_GLOG_DLL_DECL           // ʹ�þ�̬glog�������
#define GLOG_NO_ABBREVIATED_SEVERITIES // û�����������,��˵��Ϊ��Windows.h��ͻ
#include <glog/logging.h>
//glog
#endif

#endif

