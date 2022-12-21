#pragma once
#include "Paint.h"

	using namespace System;
	using namespace System::IO;
	using namespace System::Runtime::Serialization;
	using namespace System::Xml;
	using namespace PaintSystem;

	//Класс, управляющий сохранением/загрузкой данных
	ref class FileControl
	{
	public:
		//Загрузка
		Pole^ Load(String^ url);
		//Сохранение
		bool Save(Pole ^area, String^ url);
	};

