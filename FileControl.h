#pragma once
#include "Paint.h"

	using namespace System;
	using namespace System::IO;
	using namespace System::Runtime::Serialization;
	using namespace System::Xml;
	using namespace PaintSystem;

	//�����, ����������� �����������/��������� ������
	ref class FileControl
	{
	public:
		//��������
		Pole^ Load(String^ url);
		//����������
		bool Save(Pole ^area, String^ url);
	};

