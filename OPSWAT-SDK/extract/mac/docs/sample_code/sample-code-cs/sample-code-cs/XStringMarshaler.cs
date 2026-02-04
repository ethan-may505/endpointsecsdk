using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;

namespace sample_code_cs
{
    class XStringMarshaler : ICustomMarshaler
    {
        private static ICustomMarshaler _instance = null;
        private Dictionary<IntPtr, object> managedObjects = new Dictionary<IntPtr, object>();

        public static ICustomMarshaler GetInstance(string cookie)
        {
            if (_instance == null)
                _instance = new XStringMarshaler();
            return _instance;
        }
        public static string PtrToString(IntPtr ptr)
        {
            return (string)GetInstance("").MarshalNativeToManaged(ptr);
        }
        public static IntPtr StringToPtr(string str)
        {
            return GetInstance("").MarshalManagedToNative(str);
        }

        public void CleanUpManagedData(object ManagedObj)
        {
            ManagedObj = null;
        }

        public void CleanUpNativeData(IntPtr pNativeData)
        {
            lock (managedObjects)
            {
                if (managedObjects.ContainsKey(pNativeData))
                {
                    managedObjects.Remove(pNativeData);
                }
            }
            Marshal.FreeCoTaskMem(pNativeData);
        }

        public int GetNativeDataSize()
        {
            return -1;
        }

        public IntPtr MarshalManagedToNative(object ManagedObj)
        {
            if (ManagedObj == null || ManagedObj as string == null)
                return IntPtr.Zero;

            if (!(ManagedObj is string))
                throw new MarshalDirectiveException("XPlatformStringMarshaler can only be used on String.");

            string utf16string = ManagedObj as string;
            IntPtr buffer = IntPtr.Zero;
            if (RuntimeInformation.IsOSPlatform(OSPlatform.Windows))
            {
                buffer = Marshal.StringToCoTaskMemUni(utf16string);
            }
            else
            {
                byte[] utf32Buffer = Encoding.Convert(Encoding.Unicode, Encoding.UTF32, Encoding.Unicode.GetBytes(utf16string));
                buffer = Marshal.AllocCoTaskMem(utf32Buffer.Length + 4);
                Marshal.Copy(utf32Buffer, 0, buffer, utf32Buffer.Length);
                Marshal.WriteInt32(buffer + utf32Buffer.Length, 0);
            }

            lock (managedObjects)
            {
                managedObjects.Add(buffer, ManagedObj);
            }
            return buffer;
        }

        public object MarshalNativeToManaged(IntPtr pNativeData)
        {
            if (pNativeData == IntPtr.Zero)
                return null;

            string sOut = string.Empty;
            lock (managedObjects)
            {
                if (managedObjects.ContainsKey(pNativeData))
                {
                    sOut = (string)managedObjects[pNativeData];
                    if (sOut == null)
                        sOut = string.Empty;
                    managedObjects.Remove(pNativeData);
                }
            }
            if (RuntimeInformation.IsOSPlatform(OSPlatform.Windows))
            {
                sOut = Marshal.PtrToStringUni(pNativeData);
            }
            else
            {
                int length = 0;
                while (Marshal.ReadInt32(pNativeData, length) != 0)
                    length += 4;

                if (length > 0)
                {
                    byte[] utf32Buffer = new byte[length];
                    Marshal.Copy(pNativeData, utf32Buffer, 0, utf32Buffer.Length);
                    byte[] utf16Buffer = Encoding.Convert(Encoding.UTF32, Encoding.Unicode, utf32Buffer);

                    try
                    {
                        sOut = Encoding.Unicode.GetString(utf16Buffer);
                    }
                    catch (EncoderFallbackException e)
                    {
                        Console.WriteLine("Encoding Exception type {0}, Error {1}", e.GetType().Name, e.Message);
                        sOut = string.Empty;
                    }
                }
            }

            return sOut;
        }
    }
}
