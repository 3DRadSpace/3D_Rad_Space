using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _3DRadSpaceDll
{
    class Project
    {
        public static void Write()
        {

            for(int i =0; i < Main.Objects.Count;i++)
            {
                GameObject obj = Main.Objects[i];
                switch (obj)
                {
                    case Camera cam:
                        break;
                }
            }
        }
    }
}
