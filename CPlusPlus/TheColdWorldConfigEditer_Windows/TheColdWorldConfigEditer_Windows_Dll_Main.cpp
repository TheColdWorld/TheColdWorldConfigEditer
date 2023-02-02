/*
    Copyright ©) 2022-2023  TheColdWorld
    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
    USA
*/
#include "pch.h"
#include "TheColdWorldConfigEditer_Windows_Dll_Header.h"
#include "structures.h"
namespace std
{
    inline std::wstring to_wstring(const std::string& input)
    {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        return converter.from_bytes(input);
    }
    inline std::string to_string(const std::wstring& input)
    {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        return converter.to_bytes(input);
    }
    /// <summary>
    /// 
    /// </summary>
    /// <param name="str">要分割的字符串</param>
    /// <param name="pattern">分隔符</param>
    /// <returns>std::vector</returns>
    vector<wstring> split(const wstring& str,const wstring& pattern)
    {
        vector<wstring> res;
        if (str == L"")
        {
            return vector<wstring>(res);
        }
        //在字符串末尾也加入分隔符，方便截取最后一段
        wstring strs = str + pattern;
        uint64 pos = strs.find(pattern);

        while (pos != strs.npos)
        {
            wstring temp = strs.substr(0, pos);
            res.push_back(temp);
            //去掉已分割的字符串,在剩下的字符串中进行分割
            strs = strs.substr(pos + 1, strs.size());
            pos = strs.find(pattern);
        }
        return vector<wstring>(res);
    }
}
TheColdWorldConfigEditer::For_String::Headers::Headers(const Headers& Others)
{
    this->_HeaderArray = std::vector<Header>(Others._HeaderArray);
    this->_HeaderNameArray = std::vector<std::wstring>(Others._HeaderNameArray);
    this->_Serializedstring = std::wstring(Others._Serializedstring);
    this->_SerializedstringArray = std::vector<std::wstring>(Others._SerializedstringArray);
}
TheColdWorldConfigEditer::For_String::Headers::Headers(const std::vector<std::wstring> SerializedstringArray)
{
    std::vector<std::vector<uint64>> tmp1;
    for (uint64 i = 0; i < SerializedstringArray.size(); i++)
    {
        if (SerializedstringArray[i][SerializedstringArray[i].length() - 1] == L':')
        {
            if (SerializedstringArray[i + 1] == L"{")
            {
                bool findable = false;
                for (uint64 ii = i; ii < SerializedstringArray.size() && !findable; ii++)
                {
                    if (SerializedstringArray[ii] == L"}")
                    {
                        std::vector<uint64> ttmp;
                        ttmp.push_back(uint64(i));
                        ttmp.push_back(uint64(ii));
                        tmp1.push_back(std::vector<uint64>(ttmp));
                        i = ii;
                        findable = true;
                    }
                }
            }
        }
    }
    std::vector<std::wstring> tmp2; 
    for (uint64 i = 0; i < tmp1.size(); i++)
    {
        tmp2.clear();
        for (uint64 ii = tmp1[i][0]; ii < tmp1[i][1]+1; ii++)
        {
            tmp2.push_back(std::wstring(SerializedstringArray[ii]));
        }
        Header tmp3(tmp2);
        this->_HeaderArray.push_back(Header(tmp3, this));
    }
    this->Update();
    return;
}
TheColdWorldConfigEditer::For_String::Headers::Headers(const std::wstring Serializedstring)
{
    std::vector<std::wstring> WstrArray = std::split(Serializedstring, L"\n");
    std::vector<std::vector<uint64>> tmp1;
    for (uint64 i = 0; i < WstrArray.size(); i++)
    {
        if (WstrArray[i][WstrArray[i].length() - 1] == L':')
        {
            if (WstrArray[i + 1] == L"{")
            {
                bool findable = false;
                for (uint64 ii = i; ii < WstrArray.size() && !findable; ii++)
                {
                    if (WstrArray[ii] == L"}")
                    {
                        std::vector<uint64> ttmp;
                        ttmp.push_back(uint64(i));
                        ttmp.push_back(uint64(ii));
                        tmp1.push_back(std::vector<uint64>(ttmp));
                        i = ii;
                        findable = true;
                    }
                }
            }
        }
    }
    std::vector<std::wstring> tmp2;
    for (uint64 i = 0; i < tmp1.size(); i++)
    {
        tmp2.clear();
        for (uint64 ii = tmp1[i][0]; ii < tmp1[i][1] + 1; ii++)
        {
            tmp2.push_back(std::wstring(WstrArray[ii]));
        }
        Header tmp3(tmp2);
        this->_HeaderArray.push_back(Header(tmp3, this));
    }
    this->Update();
    return;
}
TheColdWorldConfigEditer::For_String::Header& TheColdWorldConfigEditer::For_String::Headers::operator[](const std::wstring& HeaderName)
{
    this->Update();
    uint64 SIndex; bool Finded = false;
    for (uint64 i = 0; i < this->_HeaderNameArray.size(); i++)
    {
        if (this->_HeaderNameArray[i] == HeaderName)
        {
            SIndex = i;
            Finded = true;
            break;
        }
    }
    if (!Finded) throw new NotFindedExpection(L"未找到Header");
    else return _HeaderArray[SIndex];
}
 void TheColdWorldConfigEditer::For_String::Headers::Update()
{
     this->_HeaderNameArray.clear();
     for (uint64 i = 0; i < this->_HeaderArray.size(); i++)
     {
         this->_HeaderNameArray.push_back(std::wstring(this->_HeaderArray[i].Name()));
     }
     this->_Serializedstring.clear();
     for (uint64 i = 0; i < this->_HeaderArray.size(); i++)
     {
         this->_Serializedstring += std::wstring(this->_HeaderArray[i].Serializedstring() + L"\n");
     }
     this->_Serializedstring += std::wstring(this->_HeaderArray[this->_HeaderArray.size() - 1].Serializedstring());
     this->_SerializedstringArray = std::split(this->_Serializedstring, L"\n");
    return;
}
 TheColdWorldConfigEditer::For_String::Headers::~Headers()
 {
     this->_Serializedstring.clear();
     this->_SerializedstringArray.clear();
     this->_HeaderNameArray.clear();
     this->_HeaderArray.clear();
 }
TheColdWorldConfigEditer::For_String::Value::Value(std::wstring Value) { this->_Value = std::wstring(Value); }
TheColdWorldConfigEditer::For_String::Value::Value(const Value& Others, Key* FatherPointer) { this->_Value = std::wstring(Others._Value); this->HaveFatherAble = true; this->FatherPotinter = FatherPointer; }
 void TheColdWorldConfigEditer::For_String::Value::operator=(const Value& WillReplaceValue)
{
     this->_Value.clear();
     this->_Value = std::wstring(WillReplaceValue._Value);
     this->RefResh();
    return;
}
const std::wstring TheColdWorldConfigEditer::For_String::Value::ToString()
{
    return  _Value;
}
int32 TheColdWorldConfigEditer::For_String::Value::ToInt32()
{
    std::string::size_type sz;
    return std::stoi(_Value,&sz,10);
}
int64 TheColdWorldConfigEditer::For_String::Value::ToInt64()
{
    std::string::size_type sz;
    return std::stoll(_Value,&sz,10);
}
uint64 TheColdWorldConfigEditer::For_String::Value::ToUInt64()
{
    std::string::size_type sz;
    return  std::stoull(_Value,&sz,10);
}
double TheColdWorldConfigEditer::For_String::Value::ToDouble()
{
    std::string::size_type sz;
    return  std::stod(_Value, &sz);
}
bool TheColdWorldConfigEditer::For_String::Value::ToBool()
{
    std::wstring wstr;
    std::transform(_Value.begin(), _Value.end(), wstr.begin(), towupper);
    if (wstr == L"true") return true;
    else if (wstr == L"false")return false;
    else throw new WrongValueExpection(L" 在转换Value->Bool出错");
}
TheColdWorldConfigEditer::For_String::Value::~Value()
{
    _Value.clear();
}
void TheColdWorldConfigEditer::For_String::Value::RefResh()
{
    if (this->HaveFatherAble) this->FatherPotinter->Update();
    return;
}
const std::wstring TheColdWorldConfigEditer::For_String::Key::ToString()
{
    return std::wstring(_Serializedstring);
}
const std::wstring TheColdWorldConfigEditer::For_String::Key::Serializedstring()
{
    return std::wstring(_Serializedstring);
}
TheColdWorldConfigEditer::For_String::Key::Key(std::wstring KeyName, Value value) 
{
    this->_Name = std::wstring(KeyName);
    this->_Value = Value(value);
    this->_Serializedstring = std::wstring(KeyName + L"=" + value.ToString());
}
TheColdWorldConfigEditer::For_String::Key::Key(std::wstring& Serializedstring)
{
    std::vector<std::wstring> tmp = std::split(Serializedstring, L"=");
    switch (tmp.size())
    {
    case 0:
    {throw new NotSerializationExpection(L"在反序列化Key时出错"); }
    case 1:
    {
        this->_Name = std::wstring(tmp[0]);
        this->_Value = Value(L"");
    }
    break;
    case 2:
    {
        this->_Name = std::wstring(tmp[0]);
        this->_Value = Value(tmp[1]);
    }
    break;
    default:
    {
        this->_Name = std::wstring(tmp[0]);
        std::wstring tmp1;
        for (int64 i = 1; i < tmp.size() - 1; i++)
        {
            tmp1 += tmp[i] + L"=";
        }
        tmp1 += tmp[tmp.size() - 1];
        this->_Value = Value(tmp1);
    }
    break;
    }
    this->_Serializedstring = std::wstring(Serializedstring);
}
TheColdWorldConfigEditer::For_String::Key::Key(const Key& Others, Header* fatherPotinter)
{
    this->_Name = std::wstring(Others._Name);
    this->_Serializedstring = std::wstring(Others._Serializedstring);
    this->_Value = Value(Others._Value,this);
    this->HaveFather = true;
    this->FatherPointer = new Header(*fatherPotinter);
}
TheColdWorldConfigEditer::For_String::Value& TheColdWorldConfigEditer::For_String::Key::value(){return _Value;}
TheColdWorldConfigEditer::For_String::Key& TheColdWorldConfigEditer::For_String::Key::operator=(const Key& WillreplaceKey)
{
    this->_Name = std::wstring(WillreplaceKey._Name);
    if (WillreplaceKey.HaveFather && !this->HaveFather)
    {
        this->HaveFather = true;
        this->FatherPointer = new TheColdWorldConfigEditer::For_String::Header(*WillreplaceKey.FatherPointer);
    }
    this->_Value = TheColdWorldConfigEditer::For_String::Value(WillreplaceKey._Value, this);
    this->Refresh();
    return *this;
}
void TheColdWorldConfigEditer::For_String::Key::value(Value& NewValue)
{
    this->_Value.~Value();
    this->_Value =  Value(NewValue,this);
    this->Refresh();
    return;
}
const std::wstring TheColdWorldConfigEditer::For_String::Key::Name()
{
    return  std::wstring(_Name);
}
 void TheColdWorldConfigEditer::For_String::Key::Name(std::wstring NewName)
{
     _Name = NewName;
     Refresh();
     return;
}
 void TheColdWorldConfigEditer::For_String::Key::Refresh()
 {
     this->_Serializedstring = std::wstring(this->_Name + L"=" + this->_Value.ToString());
     if (this->HaveFather)
     {
         this->FatherPointer->Update();
     } 
     return;
 }
 void TheColdWorldConfigEditer::For_String::Key::Update()
 {
     this->_Serializedstring = std::wstring(this->_Name + L"=" + this->_Value.ToString());
     if (this->HaveFather) this->FatherPointer->Update();
     return ;
 }
TheColdWorldConfigEditer::For_String::Key::~Key()
{
    this->_Value.~Value();
    FatherPointer = nullptr;
    this->_Name.clear();
    this->_Serializedstring.clear();
}
const std::vector<std::wstring> TheColdWorldConfigEditer::For_String::Headers::SerializedstringArray() { return std::vector<std::wstring>(this->_SerializedstringArray); }
const std::wstring TheColdWorldConfigEditer::For_String::Headers::Serializedstring() { return std::wstring(this->_Serializedstring); }
void TheColdWorldConfigEditer::For_String::Header::Refresh()
{
    this->_KeyNameArray.clear();
    for (uint64 i = 0; i < this->_KeyArray.size(); i++)
    { this->_KeyNameArray.push_back(std::wstring(this->_KeyArray[i].Name())); }
    this->_Serializedstring = std::wstring(this->_Name + L":\n{\n");
    for (uint64 i = 0; i < this->_KeyArray.size(); i++)
    {
        this->_Serializedstring += std::wstring(this->_KeyArray[i].Serializedstring() + L"\n");
    }
    this->_Serializedstring += std::wstring(L"}");
    this->_SerializedstringArray.clear();
    this->_SerializedstringArray = std::split(_Serializedstring, L"\n"); 
    if (this->HaveFather) this->FatherPointer->Update();
}
void TheColdWorldConfigEditer::For_String::Header::Update()
{
    this->_KeyNameArray.clear();
    for (uint64 i = 0; i < this->_KeyArray.size(); i++)
    {
        this->_KeyNameArray.push_back((std::wstring(this->_KeyArray[i].Name())));
    }
    this->_Serializedstring = std::wstring(this->_Name + L":\n{\n");
    for (uint64 i = 0; i < this->_KeyArray.size(); i++)
    {
        this->_Serializedstring += std::wstring(this->_KeyArray[i].Serializedstring() + L"\n");
    }
    this->_Serializedstring += std::wstring(L"}");
    this->_SerializedstringArray.clear();
    this->_SerializedstringArray = std::split(_Serializedstring, L"\n");
    return;
}
TheColdWorldConfigEditer::For_String::Header::Header(std::wstring Serializedstring)
{
    std::vector<std::wstring> __SerializedstringArray = std::split(Serializedstring, L"\n");
    if (__SerializedstringArray[0][__SerializedstringArray[0].length() - 1] != L':') throw new NotSerializationExpection(L"在反序列化Header时出错");
    if (__SerializedstringArray[1][__SerializedstringArray[1].length() - 1] != L'{') throw new NotSerializationExpection(L"在反序列化Header时出错");
    if (__SerializedstringArray[__SerializedstringArray.size() - 1][__SerializedstringArray[__SerializedstringArray.size() - 1].length() - 1] != L'}') throw new NotSerializationExpection(L"在反序列化Header时出错");
    this->_Name = std::wstring(__SerializedstringArray[1]);
    this->_Name.pop_back();
    for (uint64 i = 2; i < __SerializedstringArray.size() - 1; i++)
    {
        std::vector<std::wstring> tmp = std::split(__SerializedstringArray[i], L"=");
        if (tmp.size() == 0) continue;
        else
        {
           this-> _KeyNameArray.push_back(std::wstring(tmp[0]));
            Key ktmp(__SerializedstringArray[i]);
            this->_KeyArray.push_back(Key(ktmp,this));
        }
    }
    this->Refresh();
    return;
}
TheColdWorldConfigEditer::For_String::Header::Header(std::vector<std::wstring> SerializedstringArray)
{
    if (SerializedstringArray[0][SerializedstringArray[0].length() - 1] != L':') throw new NotSerializationExpection(L"在反序列化Header时出错");
    if (SerializedstringArray[1][SerializedstringArray[1].length() - 1] != L'{') throw new NotSerializationExpection(L"在反序列化Header时出错");
    if (SerializedstringArray[SerializedstringArray.size() - 1][SerializedstringArray[SerializedstringArray.size() - 1].length() - 1] != L'}') throw new NotSerializationExpection(L"在反序列化Header时出错");
    this->_Name = std::wstring(SerializedstringArray[0]);
    this->_Name.pop_back();
    for (uint64 i = 2; i < SerializedstringArray.size() - 1; i++)
    {
        std::vector<std::wstring> tmp = std::split(SerializedstringArray[i], L"=");
        if (tmp.size() == 0) continue;
        else
        {
            this->_KeyNameArray.push_back(std::wstring(tmp[0]));
            Key ktmp(SerializedstringArray[i]);
            this->_KeyArray.push_back(Key(ktmp, this));
            memset(&ktmp, 0, sizeof(ktmp));
        }
    }
    this->Refresh();
    return;
}
TheColdWorldConfigEditer::For_String::Header::Header(std::wstring Name, std::vector<Key>& KeyArray)
{
    this->_Name = std::wstring(Name);
    this->_KeyArray = std::vector<Key>();
    for(uint64 i=0;i< KeyArray.size();i++)
    {
        _KeyArray.push_back(Key(KeyArray[i], this));
    }
    this->Refresh();
    return;
}
TheColdWorldConfigEditer::For_String::Header::Header(const Header& Header, Headers* FartherPointer)
{
    this->_KeyArray = std::vector<Key>();
    for (uint64 i = 0; i < Header._KeyArray.size() - 1; i++)
    {
        _KeyArray.push_back(Key(Header._KeyArray[i], this));
    }
    this->_Name = std::wstring(Header._Name);
    this->_KeyNameArray = std::vector<std::wstring>(Header._KeyNameArray);
    this->_Serializedstring = std::wstring(Header._Serializedstring);
    this->_SerializedstringArray = std::vector<std::wstring>(Header._SerializedstringArray);
    this->HaveFather = true;
    this->FatherPointer = FartherPointer;
}
void TheColdWorldConfigEditer::For_String::Header::Add(Key& NewKey)
{
    uint64 index; bool findable = false;
    for (uint64 i = 0; i < this->_KeyNameArray.size(); i++)
    {
        if (this->_KeyNameArray[i] == NewKey.Name())
        {
            index = i; findable = true; break;
        }
    }
    if (findable)
    {
       this->_KeyArray[index] = Key(NewKey,this);
    }
    else
    {
       this-> _KeyArray.push_back(Key(NewKey, this));
    }
   this-> Refresh();
    return;
}
void TheColdWorldConfigEditer::For_String::Header::Delete(std::wstring WillDeleteKeyName)
{
    std::vector<Key>::iterator index;
    for (index = this->_KeyArray.begin(); index != this->_KeyArray.end();)
    {
        if (index->Name() == WillDeleteKeyName)
        {
            index= this->_KeyArray.erase(index);
            break;
        }
        else
        {
            ++index;
        }
    }
    this->Refresh();
    return;
}
uint64 TheColdWorldConfigEditer::For_String::Header::Length()
{
    return uint64(this->_KeyArray.size());
}
TheColdWorldConfigEditer::For_String::Key& TheColdWorldConfigEditer::For_String::Header::operator[](const std::wstring& KeyName)
{
    this->Refresh();
    uint64 index; bool findable = false;
    for (uint64 i = 0; i < this->_KeyNameArray.size(); i++)
    {
        if (this->_KeyNameArray[i] == KeyName)
        {
            index = i; findable = true; break;
        }
    }
    if (findable)
    {
        return this->_KeyArray[index];
    }
    else throw new NotFindedExpection(L"未找到Key");
}
TheColdWorldConfigEditer::For_String::Header& TheColdWorldConfigEditer::For_String::Header::operator=(const Header ReplaceHeader)
{
    this->_KeyArray = std::vector<Key>(ReplaceHeader._KeyArray);
    this->_Name =std::wstring (ReplaceHeader._Name);
    this->_KeyNameArray =std::vector<std::wstring>(ReplaceHeader._KeyNameArray);
    this->_Serializedstring = std::wstring(ReplaceHeader._Serializedstring);
    this->_SerializedstringArray =std::vector<std::wstring>(ReplaceHeader._SerializedstringArray);
    return *this;
}
const std::wstring TheColdWorldConfigEditer::For_String::Header::Serializedstring()
{
    return std::wstring(this->_Serializedstring);
}
const std::vector<std::wstring> TheColdWorldConfigEditer::For_String::Header::SerializedstringArray()
{
    return  std::vector<std::wstring>(this->_SerializedstringArray);
}
const std::wstring TheColdWorldConfigEditer::For_String::Header::ToString()
{
    return  std::wstring(this->_Serializedstring);
}
const std::wstring TheColdWorldConfigEditer::For_String::Header::Name()
{
    return std::wstring(this->_Name);
}
TheColdWorldConfigEditer::For_String::Header::~Header()
{
    this->_KeyNameArray.clear();
    this->_KeyArray.clear();
    this->_Serializedstring.clear();
    this->_SerializedstringArray.clear();
    this->FatherPointer = nullptr;
}
TheColdWorldConfigEditer::NotSerializationExpection::NotSerializationExpection(std::wstring Message) : exception(std::to_string(Message).c_str()){}
TheColdWorldConfigEditer::NotFindedExpection::NotFindedExpection(std::wstring Message) : exception(std::to_string(Message).c_str()) {}
TheColdWorldConfigEditer::WrongValueExpection::WrongValueExpection(std::wstring Message) : exception(std::to_string(Message).c_str()) {}
std::wstring TheColdWorldConfigEditer::For_String::RandonString(uint64 StringLength)
{
    if (StringLength == 0) return L"";
    static wchar_t StringArray[62] = {
        L'1',L'2',L'3',L'4',L'5',L'6',L'7',L'8',L'9',L'0',
        L'A',L'B',L'C',L'D',L'E',L'F',L'G',L'H',L'I',L'J',L'K',L'L' ,L'M',L'N',L'O',L'P',L'Q',L'R',L'S',L'T',L'U',L'V',L'W',L'X',L'Y',L'Z',
        L'a',L'b',L'c',L'd',L'e',L'f',L'g',L'h',L'i',L'j',L'k',L'l',L'm',L'n',L'o',L'p',L'q',L'r',L's',L't',L'u',L'v',L'w',L'x',L'y',L'z'
    };
    std::wstring Returns = L"";
    for (uint64 i = 0; i < StringLength; i++)
    {
        Returns += StringArray[rand() % 62];
    }
    return std::wstring(Returns);
}