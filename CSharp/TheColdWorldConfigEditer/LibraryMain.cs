namespace TheColdWorldConfigEditer_Csharp
{
    public static class Static_For_File
    {
        /// <summary>
        /// 寻找某个头的所有键
        /// </summary>
        /// <param name="FilePath">文件路径</param>
        /// <param name="findHeader">头</param>
        /// <param name="result">键</param>
        /// <returns>是否取到结果<br/>是为true,否则为false</returns>
        public static bool FindAllKey(in string FilePath, in string findHeader, out string[] result)
        {
                FileEditer._out_.Header header = new FileEditer._out_.Header(FilePath, findHeader);
                result = new string[header.header.Length];
                for (int i = 0; i < result.Length; i++)
                {
                    result[i] = header.header.Keys[i].SerializedString;
                }
                return true;
        }
        /// <summary>
        /// 寻找某个头的某个键的值<br/>
        /// </summary>
        /// <param name="FilePath">文件路径</param>
        /// <param name="findHeader">头</param>
        /// <param name="findKey">键</param>
        /// <param name="value">值</param>
        /// <returns>是否取到结果<br/>是为true,否则为false</returns>
        public static bool FindValue(in string FilePath, in string findHeader, in string findKey, out string value)
        {
                string[] temp1;
                if (!FindAllKey(FilePath, findHeader, out temp1))
                {
                    value = null;
                    return false;
                }
                else
                {
                    FileEditer._out_.Key key = new FileEditer._out_.Key(FilePath, findHeader, findKey);
                    value = key.key.Value.ToString();
                    return true;
                }
            
        }
        /// <summary>
        /// 寻找某个头的某个键的值<br/>
        /// </summary>
        /// <param name="FilePath">文件路径</param>
        /// <param name="findHeader">头</param>
        /// <param name="findKey">键</param>
        /// <param name="value">值</param>
        /// <returns>是否取到结果<br/>是为true,否则为false</returns>
        public static bool FindValue(in string FilePath, in string findHeader, in string findKey, out int value)
        {
                string[] temp1;
                if (!FindAllKey(FilePath, findHeader, out temp1))
                {
                    value = int.MaxValue;
                    return false;
                }
                else
                {
                    FileEditer._out_.Key key = new FileEditer._out_.Key(FilePath, findHeader, findKey);
                    value = key.key.Value.ToInt();
                    return true;
                }
            
        }
        /// <summary>
        /// 寻找某个头的某个键的值<br/>
        /// </summary>
        /// <param name="FilePath">文件路径</param>
        /// <param name="findHeader">头</param>
        /// <param name="findKey">键</param>
        /// <param name="value">值</param>
        /// <returns>是否取到结果<br/>是为true,否则为false</returns>
        public static bool FindValue(in string FilePath, in string findHeader, in string findKey, out double value)
        {
                string[] temp1;
                if (!FindAllKey(FilePath, findHeader, out temp1))
                {
                    value = double.NaN;
                    return false;
                }
                else
                {
                    FileEditer._out_.Key key = new FileEditer._out_.Key(FilePath, findHeader, findKey);
                    value = key.key.Value.ToDouble();
                    return true;
                }
        }
        /// <summary>
        /// 寻找某个头的某个键的值<br/>
        /// </summary>
        /// <param name="FilePath">文件路径</param>
        /// <param name="findHeader">头</param>
        /// <param name="findKey">键</param>
        /// <param name="value">值</param>
        /// <returns>是否取到结果<br/>是为true,否则为false</returns>
        public static bool FindValue(in string FilePath, in string findHeader, in string findKey, out bool value)
        {
                string[] temp1;
                if (!FindAllKey(FilePath, findHeader, out temp1))
                {
                    value = false;
                    return false;
                }
                else
                {
                    FileEditer._out_.Key key = new FileEditer._out_.Key(FilePath, findHeader, findKey);
                    value = key.key.Value.ToBool();
                    return true;
                }
        }
    }
    public class For_String
    {
        public class Headers
        {
            /// <summary>
            /// 构造函数:反序列化
            /// </summary>
            /// <param name="Serializedstring">序列化后的字符串</param>
            public Headers(string Serializedstring)
            {
                string[] SerializedstringArray = Serializedstring.Split(new string[] { "\n" }, System.StringSplitOptions.None);
                int Headers = 0;
                for (int i = 0; i < SerializedstringArray.Length; i++)
                {
                    if (SerializedstringArray[i][SerializedstringArray[i].Length - 1] == ':')
                    {
                        if (SerializedstringArray[i + 1][SerializedstringArray[i + 1].Length - 1] != '{') continue;
                        else
                        {
                            Headers++;
                        }
                    }
                }
                HeadersArray = new Header[Headers];
                int[][] Temp1 = new int[Headers][];
                for (int i = 0, k = 0; i < SerializedstringArray.Length; i++)
                {
                    if (SerializedstringArray[i][SerializedstringArray[i].Length - 1] == ':')
                    {
                        if (SerializedstringArray[i + 1][SerializedstringArray[i + 1].Length - 1] != '{') continue;
                        else
                        {
                            Temp1[k] = new int[2];
                            Temp1[k][0] = i;
                            for (; i < SerializedstringArray.Length; i++)
                            {
                                if (SerializedstringArray[i] == "}") { Temp1[k][1] = i; k++; break; }
                            }
                        }
                    }
                }
                for (int i = 0; i < Temp1.Length; i++)
                {
                    string[] Temp2 = new string[Temp1[i][1] - Temp1[i][0] + 1];
                    for (int ii = Temp1[i][0], k = 0; ii < Temp1[i][1] + 1; ii++, k++)
                    {
                        Temp2[k] = SerializedstringArray[ii];
                    }
                    HeadersArray[i] = new Header(Temp2,this);
                }
                Refresh();
            }
            /// <summary>
            /// 构造函数:反序列化
            /// </summary>
            /// <param name="SerializedstringArray">序列化后的字符串数组</param>
            public Headers(string[] SerializedstringArray)
            {
                int Headers = 0;
                for (int i = 0; i < SerializedstringArray.Length; i++)
                {
                    if (SerializedstringArray[i][SerializedstringArray[i].Length - 1] == ':')
                    {
                        if (SerializedstringArray[i + 1][SerializedstringArray[i + 1].Length - 1] != '{') continue;
                        else
                        {
                            Headers++;
                        }
                    }
                }
                HeadersArray = new Header[Headers];
                int[][] Temp1 =new int[Headers][];
                for (int i = 0,k=0; i < SerializedstringArray.Length; i++)
                {
                    if (SerializedstringArray[i][SerializedstringArray[i].Length - 1] == ':')
                    {
                        if (SerializedstringArray[i + 1][SerializedstringArray[i + 1].Length - 1] != '{') continue;
                        else
                        {
                            Temp1[k] = new int[2];
                            Temp1[k][0] = i;
                            for (; i < SerializedstringArray.Length; i++)
                            {
                                if (SerializedstringArray[i]=="}") { Temp1[k][1] = i;k++; break; }
                            }
                        }
                    }
                }
                for (int i = 0; i < Temp1.Length; i++)
                {
                    string[] Temp2 = new string[Temp1[i][1] - Temp1[i][0] + 1];
                    for (int ii = Temp1[i][0],k=0; ii < Temp1[i][1]+1; ii++,k++)
                    {
                        Temp2[k] = SerializedstringArray[ii];
                    }
                    HeadersArray[i] = new Header(Temp2,this);
                }
                Refresh();
            }
            /// <summary>
            /// 构造函数:序列化
            /// </summary>
            /// <param name="Headers"></param>
            public Headers(Header[] Headers)
            {
                HeadersArray = new Header[Headers.Length];
                for (int i = 0; i < Headers.Length; i++)
                {
                    HeadersArray[i] = new(Headers[i].SerializedString, this);
                }
                Refresh();
            }
            /// <summary>
            /// 将此项序列化
            /// </summary>
            /// <returns>序列化后的字符串</returns>
            public override string ToString() { return _SerializedString; }
            /// <summary>
            /// 将此项序列化
            /// </summary>
            /// <returns>序列化后的字符串数组</returns>
            public string[] ToStringArray() { return _SerializedStringArray; }
            /// <summary>
            /// 从头数组中取得对应名字的头
            /// </summary>
            /// <param name="KeyName">头的名字</param>
            /// <returns>输入名字对应的头<br/>找不到就返回 null</returns>
            public ref Header GetHeader(string HeaderName)
            {
                int Index = 0;bool Finded = false;
                for (; Index < HeaderNameList.Length; Index++)
                {
                    if (HeaderNameList[Index] == HeaderName) { Finded = true; break; }
                }
                if (Finded) return ref HeadersArray[Index];
                else throw new ItemNotFoundExpection("Header \'" + HeaderName + "\' not found");
            }
            /// <summary>
            /// 替换某个头的所有内容
            /// </summary>
            /// <param name="WillReplaceHeaderName">将要替换的头的名字</param>
            /// <param name="WillReplaceItem">将要替换成的头</param>
            public void Replace(string WillReplaceHeaderName, Header WillReplaceItem)
            {
                int Index = 0;bool Finded = false;
                for (; Index < Length; Index++)
                {
                    if (HeadersArray[Index].Name == WillReplaceHeaderName)
                    {
                        Finded = true;break;
                    }
                }
                if(Finded)
                {
                    HeadersArray[Index].Replace(new(WillReplaceItem.SerializedString, this));
                    Refresh();
                    return;
                }
                else
                {
                    throw new ItemNotFoundExpection("Header \'" + WillReplaceHeaderName + "\' not found");
                }
            }
            /// <summary>
            /// 添加头<br/>
            ///  如果有同名的就替换，否则在末尾新增
            /// </summary>
            /// <param name="AddHeader"></param>
            /// <returns>是否成功<br/>成功为 true，否则为 false</returns>
            public void Add(in Header AddHeader)
            {
                int index = 0;bool Replaceable=false;
                for (; index < Length; index++)
                {
                    if (HeadersArray[index].Name==AddHeader.Name) { Replaceable = true;break; }
                }
                if (Replaceable)
                {
                    HeadersArray[index].Replace(new(AddHeader.SerializedString, this));
                }
                else
                {
                    Header[] Temp = new Header[Length];
                    for (int i = 0; i < Length; i++)
                    {
                        Temp[i] = HeadersArray[i];
                    }
                    Temp[Length] = new(AddHeader.SerializedString,this);
                    HeadersArray = Temp;
                    Refresh();
                    return;
                }
                
            }
            public void Delete(Header WillDelete)
            {
                ArrayEditer.DeleteArrayFirstFindedItem(HeadersArray, WillDelete);
                Refresh();
            }
            /// <summary>
            /// 将序列化后的字符串覆盖输入文件
            /// </summary>
            /// <param name="FilePath"></param>
            public void WriteToFile(string FilePath)
            {
                Refresh();
                FileEditer._in_.FileWrite.Write(FilePath, this);
            }
            public void Refresh()
            {
                HeaderNameList = new string[Length];
                for (int i = 0; i < Length; i++)
                {
                    HeaderNameList[i] = HeadersArray[i].Name;
                }
                _SerializedString = string.Empty;
                for (int i = 0; i < Length - 1; i++)
                {
                    _SerializedString += HeadersArray[i].SerializedString+"\n";
                }
                _SerializedString += HeadersArray[Length - 1];
                SerializedStringArray = _SerializedString.Split(new string[] { "\n" }, System.StringSplitOptions.None);
                }
            /// <summary>
            /// 其中头的数量
            /// </summary>
            public int Length { get { return HeadersArray.Length; } }
            private Header[] HeadersArray;
            private string[] HeaderNameList;
            /// <summary>
            /// 序列化的字符串，等价于this.ToString()
            /// </summary>
            public string SerializedString { get { return _SerializedString; } private set { _SerializedString = value; } }
            private string _SerializedString;
            /// <summary>
            /// 序列化的字符串数组，等价于this.ToStringArray()
            /// </summary>
            public string[] SerializedStringArray { get { return _SerializedStringArray; } private set { _SerializedStringArray = value; } }
            private string[] _SerializedStringArray;
            public ref Header this[string HeaderName] 
            {
                get 
                {
                    int Index = 0; bool Finded = false;
                    for (; Index < HeaderNameList.Length; Index++)
                    {
                        if (HeaderNameList[Index] == HeaderName) { Finded = true; break; }
                    }
                    if (Finded) return ref HeadersArray[Index];
                    else throw new ItemNotFoundExpection("Header \'" + HeaderName + "\' not found");
                }
            }
        }
        public class Header
        {
            /// <summary>
            /// 构造函数:反序列化
            /// </summary>
            /// <param name="SerializedstringArray">序列化后的字符串</param>
            /// <exception cref="NotSerializationExpection"></exception>
            public Header(string Serializedstring)
            {
                _SerializedString = Serializedstring;
                _SerializedStringArray = _SerializedString.Split(new string[] { "\n"},System.StringSplitOptions.None);
                if (_SerializedStringArray[0][_SerializedStringArray[0].Length - 1] != ':') throw new NotSerializationExpection("在反序列化头时出错");
                if (_SerializedStringArray[1] != "{") throw new NotSerializationExpection("在反序列化头时出错");
                if (_SerializedStringArray[_SerializedStringArray.Length - 1] != "}") throw new NotSerializationExpection("在反序列化头时出错");
                _Name = _SerializedStringArray[0].Replace(":", string.Empty);
                Keys = new Key[_SerializedStringArray.Length - 3];
                for (int i = 2, k = 0; i < _SerializedStringArray.Length - 1; i++, k++)
                {
                    Keys[k] = new Key(_SerializedStringArray[i],this);
                }
                KeysNameList = new string[Keys.Length];
                for (int i = 0; i < Keys.Length; i++)
                {
                    KeysNameList[i] = Keys[i].Name;
                }
            }
            /// <summary>
            /// 构造函数:反序列化
            /// </summary>
            /// <param name="SerializedstringArray">序列化后的字符串数组</param>
            /// <exception cref="NotSerializationExpection"></exception>
            public Header(string[] SerializedstringArray)
            {
                _SerializedStringArray = SerializedstringArray;
                if (_SerializedStringArray[0][_SerializedStringArray[0].Length - 1] != ':') throw new NotSerializationExpection("在反序列化头时出错");
                if (_SerializedStringArray[1] != "{") throw new NotSerializationExpection("在反序列化头时出错");
                if (_SerializedStringArray[_SerializedStringArray.Length - 1] != "}") throw new NotSerializationExpection("在反序列化头时出错");
                _Name = _SerializedStringArray[0].Replace(":", string.Empty);
                Keys = new Key[_SerializedStringArray.Length - 3];
                for (int i = 2,k=0; i < _SerializedStringArray.Length - 1; i++,k++)
                {
                    Keys[k] = new Key(_SerializedStringArray[i],this);
                }
                KeysNameList = new string[Keys.Length];
                for (int i = 0; i < Keys.Length; i++)
                {
                    KeysNameList[i] = Keys[i].Name;
                }
                _SerializedString = string.Empty;
                for (int i = 0; i < _SerializedStringArray.Length - 1; i++)
                {
                    _SerializedString += _SerializedStringArray[i] + "\n";
                }
                _SerializedString += _SerializedStringArray[_SerializedStringArray.Length - 1];
            }
            /// <summary>
            /// 构造函数:序列化
            /// </summary>
            /// <param name="HeaderName">头名</param>
            /// <param name="keys">序列化的头所带的所有项</param>
            public Header(string HeaderName, Key[] keys)
            {
                _Name = HeaderName;
                Keys = new Key[keys.Length];
                for (int i = 0; i < keys.Length; i++)
                {
                    Keys[i] = new(keys[i].SerializedString, this);
                }
                Refresh();
            }
            /// <summary>
            /// 构造函数:反序列化:带上一级
            /// </summary>
            /// <param name="SerializedstringArray">序列化后的字符串</param>
            /// <param name="Father">上一级(通常是this)</param>
            /// <exception cref="NotSerializationExpection"></exception>
            public Header(string Serializedstring,Headers Father)
            {
                _SerializedString = Serializedstring;
                _SerializedStringArray = _SerializedString.Split(new string[] { "\n" }, System.StringSplitOptions.None);
                if (_SerializedStringArray[0][_SerializedStringArray[0].Length - 1] != ':') throw new NotSerializationExpection("在反序列化头时出错");
                if (_SerializedStringArray[1] != "{") throw new NotSerializationExpection("在反序列化头时出错");
                if (_SerializedStringArray[_SerializedStringArray.Length - 1] != "}") throw new NotSerializationExpection("在反序列化头时出错");
                _Name = _SerializedStringArray[0].Replace(":", string.Empty);
                Keys = new Key[_SerializedStringArray.Length - 3];
                for (int i = 2, k = 0; i < _SerializedStringArray.Length - 1; i++, k++)
                {
                    Keys[k] = new Key(_SerializedStringArray[i], this);
                }
                KeysNameList = new string[Keys.Length];
                for (int i = 0; i < Keys.Length; i++)
                {
                    KeysNameList[i] = Keys[i].Name;
                }
                HaveFather = true;
                FatherRef = Father;
            }
            /// <summary>
            /// 构造函数:反序列化:带上一级
            /// </summary>
            /// <param name="SerializedstringArray">序列化后的字符串数组</param>
            /// <exception cref="NotSerializationExpection"></exception>
            public Header(string[] SerializedstringArray,Headers Father)
            {
                _SerializedStringArray = SerializedstringArray;
                if (_SerializedStringArray[0][_SerializedStringArray[0].Length - 1] != ':') throw new NotSerializationExpection("在反序列化头时出错");
                if (_SerializedStringArray[1] != "{") throw new NotSerializationExpection("在反序列化头时出错");
                if (_SerializedStringArray[_SerializedStringArray.Length - 1] != "}") throw new NotSerializationExpection("在反序列化头时出错");
                _Name = _SerializedStringArray[0].Replace(":", string.Empty);
                Keys = new Key[_SerializedStringArray.Length - 3];
                for (int i = 2, k = 0; i < _SerializedStringArray.Length - 1; i++, k++)
                {
                    Keys[k] = new Key(_SerializedStringArray[i], this);
                }
                KeysNameList = new string[Keys.Length];
                for (int i = 0; i < Keys.Length; i++)
                {
                    KeysNameList[i] = Keys[i].Name;
                }
                _SerializedString = string.Empty;
                for (int i = 0; i < _SerializedStringArray.Length - 1; i++)
                {
                    _SerializedString += _SerializedStringArray[i] + "\n";
                }
                _SerializedString += _SerializedStringArray[_SerializedStringArray.Length - 1];
                HaveFather = true;
                FatherRef = Father;
            }
            /// <summary>
            /// 构造函数:序列化:带上一级 
            /// </summary>
            /// <param name="HeaderName">头名</param>
            /// <param name="keys">将要序列化的头所带的所有项</param>
            /// <param name="Father">上一级(通常是this)</param>
            public Header(string HeaderName, Key[] keys,Headers Father)
            {
                _Name = HeaderName;
                Keys = new Key[keys.Length];
                for (int i = 0; i < keys.Length; i++)
                {
                    keys[i] = new(keys[i].SerializedString, this);
                }
                Refresh();
                HaveFather = true;
                FatherRef = Father;
            }
            /// <summary>
            /// 将此项序列化
            /// </summary>
            /// <returns>序列化后的字符串</returns>
            public override string ToString() { return _SerializedString; }
            /// <summary>
            /// 将此项序列化
            /// </summary>
            /// <returns>序列化后的字符串数组</returns>
            public string[] ToStringArray() { return _SerializedStringArray; }
            /// <summary>
            /// 头名
            /// </summary>
            public string Name { get { return _Name; } private set { _Name = value; } }
            private string _Name;
            /// <summary>
            /// 从头中取得对应名字的项
            /// </summary>
            /// <param name="KeyName">项的名字</param>
            /// <returns>输入名字对应的项<br/>找不到就返回 null</returns>
            public ref Key GetKey(string KeyName)
            {
                int Val = 0;bool Finded = false;
                for (; Val < KeysNameList.Length; Val++)
                {
                    if (KeysNameList[Val]==KeyName) { Finded = true;break; }
                }
                if (Finded)
                {
                    return ref Keys[Val];
                }
                else throw new ItemNotFoundExpection("Key \'" + KeyName + "\' not found");
            }
            /// <summary>
            /// 替换头
            /// </summary>
            /// <<param name="header">将要输入的头</param>
            public void Replace(in Header header)
            {
                Keys = new Key[header.Length];
                for (int i = 0; i < header.Length; i++)
                {
                    Keys[i] = new(header.Keys[i].SerializedString, this);
                }
                Refresh();
            }
            /// <summary>
            /// 将序列化后的字符串覆盖输入文件
            /// </summary>
            /// <param name="FilePath"></param>
            public void WriteToFile(string FilePath)
            {
                Refresh();
                FileEditer._in_.FileWrite.Write(FilePath, this);
            }
            /// <summary>
            /// 向头中添加项<br/>
            ///  如果有同名的就替换，否则在末尾新增
            /// </summary>
            /// <param name="WillAddKey">要添加或替换的项</param>
            /// <returns>是否成功<br/>成功为 true，否则为 false</returns>
            public bool Add(in Key WillAddKey)
            {
                int index = 0; bool Replaceable=false;
                for (; index < Length; index++)
                {
                    if (Keys[index].Name == WillAddKey.Name) { Replaceable = true; break; }
                }
                if (Replaceable)
                {
                    Keys[index] = new(WillAddKey.SerializedString,this);
                    Refresh();
                    return true;
                }
                else
                {
                    Key[] Temp = new Key[Length];
                    for (int i = 0; i < Length; i++)
                    {
                        Temp[i] = Keys[i];
                    }
                    Temp[Length] = new(WillAddKey.SerializedString,this);
                    Keys = Temp;
                    Refresh();
                    return true;
                }

            }
            /// <summary>
            /// 刷新序列化字符串<br/>已实现上层刷新
            /// </summary>
            public void Refresh()
            {
                KeysNameList = new string[Length];
                for (int i = 0; i < Length; i++)
                {
                    KeysNameList[i] = Keys[i].Name;
                }
                _SerializedString = string.Empty;
                _SerializedString += _Name + ":\n{\n";
                for (int i = 0; i < Length; i++)
                {
                    _SerializedString += Keys[i].SerializedString + "\n";
                }
                _SerializedString += "}";
                SerializedStringArray = _SerializedString.Split(new string[] { "\n" }, System.StringSplitOptions.None);
                if (HaveFather) FatherRef.Refresh();
            }
            /// <summary>
            /// 键的数量
            /// </summary>
            public int Length { get { return Keys.Length; } }
            private string[] KeysNameList;
            public Key[] Keys;
            /// <summary>
            /// 序列化的字符串，等价于.ToString()
            /// </summary>
            public string SerializedString { get { return _SerializedString; } private set { _SerializedString = value; } }
            private string _SerializedString;
            /// <summary>
            /// 序列化的字符串数组，等价于.ToStringArray()
            /// </summary>
            public string[] SerializedStringArray { get { return _SerializedStringArray; } private set { _SerializedStringArray = value; } }
            private string[] _SerializedStringArray;
            public ref Key this[string KeyName]
            {
                get
                {
                    int Val = 0; bool Finded = false;
                    for (; Val < KeysNameList.Length; Val++)
                    {
                        if (KeysNameList[Val] == KeyName) { Finded = true; break; }
                    }
                    if (Finded)
                    {
                        return ref Keys[Val];
                    }
                    else throw new ItemNotFoundExpection("Key \'" + KeyName + "\' not found");
                }
            }
            private bool HaveFather = false;
            private Headers FatherRef = null;
        }
        public class Key
        {
            /// <summary>
            /// 构造函数:反序列化
            /// </summary>
            /// <param name="Serializedstring">经过序列化的字符串</param>
            /// <exception cref="NotSerializationExpection"></exception>
            public Key(in string Serializedstring)
            {
                _SerializedString = Serializedstring;
                string[] array = _SerializedString.Split(new string[] { "=" }, System.StringSplitOptions.None);
                switch (array.Length)
                {
                    case 0: { throw new NotSerializationExpection("在Key的反序列化时出错"); }
                    case 1:
                        {
                            _Name = array[0];
                            _Value = new Value(string.Empty,this);
                        }
                        break;
                    case 2:
                        {
                            _Name = array[0];
                            _Value = new Value(array[1],this);
                        }
                        break;
                    default:
                        {
                            _Name = array[0];
                            string ValueStr = string.Empty;
                            for (int i = 1; i < array.Length - 1; i++)
                            {
                                ValueStr += array[i] + "=";
                            }
                            ValueStr += array[array.Length - 1];
                            _Value = new Value(ValueStr,this);
                        }
                        break;
                }
            }
            /// <summary>
            /// 构造函数:反序列化:带上一级
            /// </summary>
            /// <param name="Serializedstring">经过序列化的字符串</param>
            /// <param name="Father">上一级应用(通常是this)</param>
            /// <exception cref="NotSerializationExpection"></exception>
            public Key(in string Serializedstring,Header Father)
            {
                _SerializedString = Serializedstring;
                string[] array = _SerializedString.Split(new string[] { "=" }, System.StringSplitOptions.None);
                switch (array.Length)
                {
                    case 0: { throw new NotSerializationExpection("在Key的反序列化时出错"); }
                    case 1:
                        {
                            _Name = array[0];
                            _Value = new Value(string.Empty,this);
                        }
                        break;
                    case 2:
                        {
                            _Name = array[0];
                            _Value = new Value(array[1],this);
                        }
                        break;
                    default:
                        {
                            _Name = array[0];
                            string ValueStr = string.Empty;
                            for (int i = 1; i < array.Length - 1; i++)
                            {
                                ValueStr += array[i] + "=";
                            }
                            ValueStr += array[array.Length - 1];
                            _Value = new Value(ValueStr,this);
                        }
                        break;
                }
                HaveFather = true;
                FatherRef = Father;
            }
            /// <summary>
            /// 构造函数:序列化
            /// </summary>
            /// <param name="KeyName">要序列化的项名</param>
            /// <param name="Value">作为这个项的值</param>
            public Key(string KeyName,Value Value)
            {
                _Name = KeyName;
                _Value = new(Value.ToString(),this);
                _SerializedString = KeyName + "=" + Value.ToString();
            }
            /// <summary>
            /// 构造函数:序列化:带上一级
            /// </summary>
            /// <param name="KeyName">要序列化的项名</param>
            /// <param name="Value">作为这个项的值</param>
            /// <param name="Father">上一级引用(通常是this)</param>
            public Key(string KeyName, Value Value ,Header Father)
            {
                _Name = KeyName;
                _Value = new(Value.ToString(),this);
                _SerializedString = KeyName + "=" + Value.ToString();
                HaveFather = true;
                FatherRef = Father;
            }
            /// <summary>
            /// 将此项序列化
            /// </summary>
            /// <returns>序列化后的字符串</returns>
            public override string ToString() { return _SerializedString; }
            /// <summary>
            /// 项名
            /// </summary>
            public string Name { get { return _Name; } private set { _Name = value; } }
            private string _Name;
            /// <summary>
            /// 将值替换
            /// </summary>
            /// <param name="key">将要替换的键</param>
            /// <returns></returns>
            public void Replace(Key key)
            {
                _Value = new(key.Value.ToString(),this);
                _Name = key.Name;
                Refresh();
            }
            public void Refresh()
            {
                _SerializedString = _Name + "=" + _Value.ToString();
                if (HaveFather) FatherRef.Refresh();
            }
            /// <summary>
            /// 此项对应的值
            /// </summary>
            public ref Value Value { get { return ref _Value; } }
            private Value _Value;
            /// <summary>
            /// 序列化的字符串，等价于.ToString()
            /// </summary>
            public string SerializedString{ get { return _SerializedString; } private set { _SerializedString = value; }  }
            private string _SerializedString;
            private bool HaveFather;
            private Header FatherRef=null;
        }
        public class Value
        {
            public Value(string Value)
            {
                _Value = Value;
            }
            public Value(string Value, Key Father)
            {
                _Value = Value;
                HaveFather = true;
                FatherRef = Father;
            }
            public void Replace(Value Value)
            {
                _Value = Value.ToString();
                if (HaveFather) FatherRef.Refresh();
            }
            public override string ToString() { return _Value; }
            public int ToInt() { return System.Convert.ToInt32(_Value); }
            public long ToLong() { return System.Convert.ToInt64(_Value); }
            public short ToShort() { return System.Convert.ToInt16(_Value); }
            public uint ToUint() { return System.Convert.ToUInt32(_Value); }
            public ulong ToUlong() { return System.Convert.ToUInt64(_Value); }
            public ushort ToUshort() { return System.Convert.ToUInt16(_Value); }
            public double ToDouble() { return System.Convert.ToDouble(_Value); }
            public bool ToBool() { return System.Convert.ToBoolean(_Value); }
            public byte[] ToBytes() { return System.Text.Encoding.UTF8.GetBytes(_Value);} 
            private string _Value;
            bool HaveFather = false;
            Key FatherRef = null;
        }
        public static string GetRandonString(ulong StringLength)
        {
            if (StringLength == 0) return "";
            System.Random random = new();
            char[] CharArray = {
                '1','2','3','4','5','6','7','8','9','0',
                'A','B','C','D','E','F','G','H','I','J','K','L' ,'M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
                'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'
            };
            string Return = string.Empty;
            for (ulong i = 0; i < StringLength; i++)
            {
                Return += CharArray[random.NextInt64(0, CharArray.Length)];
            }
            return new string(Return);
        }
    }
    public class FileEditer
    {
        public class _out_
        {
            public class Headers
            { 
                public Headers(string FilePath)
                {
                    _headers = new For_String.Headers(System.IO.File.ReadAllLines(FilePath));
                }
                public For_String.Headers headers { get { return _headers; } private set { _headers = value; } }
                private For_String.Headers _headers;
            }
            public class Header
            {
                public Header(string FilePath, string HeaderName)
                {
                    Headers headers = new Headers(FilePath);
                    _header = headers.headers.GetHeader(HeaderName);
                }
                public For_String.Header header { get { return _header; } set { _header = value; } }
                private For_String.Header _header;
            }
            public class Key
            {
                public Key(string FilePath, string HeaderName, string KeyName)
                {
                    Header header = new Header(FilePath, HeaderName);
                    _key = header.header.GetKey(KeyName);
                }
                public For_String.Key key { get { return _key; } set { _key = value; } }
                private For_String.Key _key;
            }
        }
        public static class _in_
        {
           public static class FileWrite
            {
                public static void Write(string FilePath,string WriteStr)
                {
                    using (System.IO.FileStream fs = new System.IO.FileStream(FilePath, System.IO.FileMode.CreateNew))
                    {
                        fs.Position = 0;
                        fs.Write(System.Text.Encoding.UTF8.GetBytes(WriteStr));
                        fs.Flush();
                    }
                }
                public static void Write(string FilePath, string[] WriteLines)
                {
                    string WriteStr = string.Empty;
                    for (int i = 0; i < WriteLines.Length - 1; i++) WriteStr += WriteLines[i];
                    WriteStr += WriteLines[WriteLines.Length - 1];
                    using (System.IO.FileStream fs = new System.IO.FileStream(FilePath, System.IO.FileMode.CreateNew))
                    {
                        fs.Position = 0;
                        fs.Write(System.Text.Encoding.UTF8.GetBytes(WriteStr));
                        fs.Flush();
                    }
                }
                public static void Write(string FilePath, For_String.Headers Headers)
                {
                    using (System.IO.FileStream fs = new System.IO.FileStream(FilePath, System.IO.FileMode.CreateNew))
                    {
                        fs.Position = 0;
                        fs.Write(System.Text.Encoding.UTF8.GetBytes(Headers.SerializedString));
                        fs.Flush();
                    }
                }
                public static void Write(string FilePath, For_String.Header Header)
                {
                    using (System.IO.FileStream fs = new System.IO.FileStream(FilePath, System.IO.FileMode.CreateNew))
                    {
                        fs.Position = 0;
                        fs.Write(System.Text.Encoding.UTF8.GetBytes(Header.SerializedString));
                        fs.Flush();
                    }
                }
            }
        }
    }

    public static class ArrayEditer
    {
       public static string[] DeleteArrayFirstFindedItem(string[] array,string Deleteitem)
        {
            System.Collections.ArrayList Arraylist = new System.Collections.ArrayList(array);
            Arraylist.Remove(Deleteitem);
            return (string[])Arraylist.ToArray(typeof(string));
        }
        public static For_String.Header[] DeleteArrayFirstFindedItem(For_String.Header[] array, For_String.Header Deleteitem)
        {
            System.Collections.ArrayList Arraylist = new System.Collections.ArrayList(array);
            Arraylist.Remove(Deleteitem);
            return (For_String.Header[])Arraylist.ToArray(typeof(For_String.Header));
        }
        public static For_String.Key[] DeleteArrayFirstFindedItem(For_String.Key[] array, For_String.Key Deleteitem)
        {
            System.Collections.ArrayList Arraylist = new System.Collections.ArrayList(array);
            Arraylist.Remove(Deleteitem);
            return (For_String.Key[])Arraylist.ToArray(typeof(For_String.Key));
        }
        public static int[] DeleteArrayFirstFindedItem(int[] array, int Deleteitem)
        {
            System.Collections.ArrayList Arraylist = new System.Collections.ArrayList(array);
            Arraylist.Remove(Deleteitem);
            return (int[])Arraylist.ToArray(typeof(int));
        }
        public static double[] DeleteArrayFirstFindedItem(double[] array, double Deleteitem)
        {
            System.Collections.ArrayList Arraylist = new System.Collections.ArrayList(array);
            Arraylist.Remove(Deleteitem);
            return (double[])Arraylist.ToArray(typeof(double));
        }
        public static long[] DeleteArrayFirstFindedItem(long[] array, long Deleteitem)
        {
            System.Collections.ArrayList Arraylist = new System.Collections.ArrayList(array);
            Arraylist.Remove(Deleteitem);
            return (long[])Arraylist.ToArray(typeof(long));
        }
        public static string[] DeleteArrayFindedAllItem(string[] array, string Deleteitem)
        {
            System.Collections.ArrayList Arraylist = new System.Collections.ArrayList(array);
            while (Arraylist.Contains(Deleteitem)) { Arraylist.Remove(Deleteitem); }
            return (string[])Arraylist.ToArray(typeof(string));
        }
        public static For_String.Header[] DeleteArrayFindedAllItem(For_String.Header[] array, For_String.Header Deleteitem)
        {
            System.Collections.ArrayList Arraylist = new System.Collections.ArrayList(array);
            while(Arraylist.Contains(Deleteitem)) { Arraylist.Remove(Deleteitem); }
            return (For_String.Header[])Arraylist.ToArray(typeof(For_String.Header));
        }
        public static For_String.Key[] DeleteArrayFindedAllItem(For_String.Key[] array, For_String.Key Deleteitem)
        {
            System.Collections.ArrayList Arraylist = new System.Collections.ArrayList(array);
            while (Arraylist.Contains(Deleteitem)) { Arraylist.Remove(Deleteitem); }
            return (For_String.Key[])Arraylist.ToArray(typeof(For_String.Key));
        }
        public static int[] DeleteArrayFindedAllItem(int[] array, int Deleteitem)
        {
            System.Collections.ArrayList Arraylist = new System.Collections.ArrayList(array);
            while (Arraylist.Contains(Deleteitem)) { Arraylist.Remove(Deleteitem); }
            return (int[])Arraylist.ToArray(typeof(int));
        }
        public static double[] DeleteArrayFindedAllItem(double[] array, double Deleteitem)
        {
            System.Collections.ArrayList Arraylist = new System.Collections.ArrayList(array);
            while (Arraylist.Contains(Deleteitem)) { Arraylist.Remove(Deleteitem); }
            return (double[])Arraylist.ToArray(typeof(double));
        }
        public static long[] DeleteArrayFindedAllItem(long[] array, long Deleteitem)
        {
            System.Collections.ArrayList Arraylist = new System.Collections.ArrayList(array);
            while (Arraylist.Contains(Deleteitem)) { Arraylist.Remove(Deleteitem); }
            return (long[])Arraylist.ToArray(typeof(long));
        }
    }

    public class NotSerializationExpection : System.ApplicationException
    {
        public NotSerializationExpection(string Message) : base(Message) { }
    }
    public class ItemNotFoundExpection : System.ApplicationException
    {
        public ItemNotFoundExpection(string message) : base(message) { }
    }
}
