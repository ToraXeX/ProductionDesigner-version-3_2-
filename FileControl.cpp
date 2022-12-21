#include "FileControl.h"

    Pole^ FileControl::Load(String^ url)
    {
        NetDataContractSerializer^ formatter = gcnew NetDataContractSerializer();
        XmlReader^ writer = XmlReader::Create(url);
        Pole^ area = (Pole^)formatter->ReadObject(writer);
        writer->Close();
        return area;

    }
    bool FileControl::Save(Pole^ area, String^ url)
    {
        NetDataContractSerializer^ formatter = gcnew NetDataContractSerializer();
        XmlWriterSettings^ setting = gcnew XmlWriterSettings();
        setting->Indent = true;
        XmlWriter^ writer = XmlWriter::Create(url, setting);
        formatter->WriteObject(writer, area);
        writer->Close();
        return true;
    }
