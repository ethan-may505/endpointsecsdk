using System;
using System.Collections.Generic;
using System.Text;

namespace sample_code_cs
{
    public class OesisSingleton<T> where T : class, new()
    {
        private static readonly T m_instance = new T();

        // Explicit static constructor to tell C# compiler
        // not to mark type as beforefieldinit
        static OesisSingleton(){}

        public OesisSingleton(){}

        public static T instance
        {
            get
            {
                return m_instance;
            }
        }
    }
}
