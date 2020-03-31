/*
using System.Collections.Generic;
using MonoGame.Framework.Content.Pipeline.Builder;
using Microsoft.Xna.Framework.Content.Pipeline;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using System.IO;

namespace _3DRadSpaceDll
{
    class MyLogger : ContentBuildLogger
    {
        public MyLogger()
        {

        }
        public override void LogImportantMessage(string message, params object[] messageArgs)
        {
            string line = "[IMPORTANT]"+message+ " ";
            for(int i =0; i < messageArgs.Length;i++)
            {
                line += messageArgs[i] + " ";
            }
            line += "\r\n";
            File.AppendAllText(@"BULIDLOG.log", line);
        }

        public override void LogMessage(string message, params object[] messageArgs)
        {
            string line = "[INFO]"+message + " ";
            for (int i = 0; i < messageArgs.Length; i++)
            {
                line += messageArgs[i] + " ";
            }
            line += "\r\n";
            File.AppendAllText(@"BULIDLOG.log", line);
        }

        public override void LogWarning(string helpLink, ContentIdentity contentIdentity, string message, params object[] messageArgs)
        {
            string line = "[WARNING]"+message + " ";
            for (int i = 0; i < messageArgs.Length; i++)
            {
                line += messageArgs[i] + " ";
            }
            line += "\r\n";
            File.AppendAllText(@"BULIDLOG.log", line);
        }
    }
    /// <summary>
    /// 
    /// </summary>
    public static class XNBConverter
    {
        /// <summary>
        /// 
        /// </summary>
        /// <param name="path"></param>
        /// <param name="outputpath"></param>
        public static void ConvertModel(string path,string outputpath)
        {
            
            OpaqueDataDictionary keyValues = new OpaqueDataDictionary();
            keyValues.Add("ColorKeyColor",new Color(0,0,0,0) );
            keyValues.Add("ColorKeyEnabled", true);
            keyValues.Add("DefaultEffect", "BasicEffect");
            keyValues.Add("GenerateMipmaps", true);
            keyValues.Add("GenerateTangentFrames", false);
            keyValues.Add("PremultiplyTextureAlpha", true);
            keyValues.Add("PremultiplyVertexColors", true);
            keyValues.Add("ResizeTexturesToPowerOfTwo", false);
            keyValues.Add("RotationX", 0);
            keyValues.Add("RotationY", 0);
            keyValues.Add("RotationZ", 0);
            keyValues.Add("Scale", 1);
            keyValues.Add("SwapWindingOrder", false);
            keyValues.Add("TextureFormat","Compressed");
            
            ContentBuildLogger logger = new MyLogger();
            PipelineManager pipeline = new PipelineManager(null, null, null)
            {
                RethrowExceptions = true,
                CompressContent = true,
                Logger = logger,
                Platform = TargetPlatform.Windows,
                Profile = GraphicsProfile.Reach
            };
            PipelineBuildEvent ev = pipeline.BuildContent(path, outputpath,"XImporter","ModelProcessor",keyValues);
            ev.Save(outputpath+".log");
        }
    }
}
*/