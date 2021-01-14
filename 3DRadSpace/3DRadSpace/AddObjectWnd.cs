using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Lib3DRadSpace_DX;

namespace _3DRadSpace
{
    public partial class AddObjectWnd : Form
    {
        public AddObjectWnd()
        {
            InitializeComponent();
        }

        private void AddObjectWnd_Load(object sender, EventArgs e)
        {
            listView1.LargeImageList = new ImageList();
            listView1.LargeImageList.ImageSize = new Size(50, 50);
            listView1.LargeImageList.Images.Add("camera",Image.FromFile("EngineData\\OBJ_Camera.png"));
            listView1.LargeImageList.Images.Add("script",Image.FromFile("EngineData\\OBJ_Script.png"));
            listView1.LargeImageList.Images.Add("skinmesh",Image.FromFile("EngineData\\OBJ_Skinmesh.png"));
            listView1.LargeImageList.Images.Add("sprite",Image.FromFile("EngineData\\OBJ_Sprite.png"));
            listView1.LargeImageList.Images.Add("textprint", Image.FromFile("EngineData\\OBJ_TextPrint.png"));
            listView1.LargeImageList.Images.Add("skybox",Image.FromFile("EngineData\\OBJ_Skybox.png"));
            listView1.LargeImageList.Images.Add("soundeffect",Image.FromFile("EngineData\\OBJ_Sound.png"));
            listView1.LargeImageList.Images.Add("soundsource",Image.FromFile("EngineData\\OBJ_SoundSource.png"));
            listView1.LargeImageList.Images.Add("eol",Image.FromFile("EngineData\\OBJ_EOL.png"));
            listView1.LargeImageList.Images.Add("eok",Image.FromFile("EngineData\\OBJ_EOK.png"));
            listView1.LargeImageList.Images.Add("timer",Image.FromFile("EngineData\\OBJ_Timer.png"));
            listView1.LargeImageList.Images.Add("fog",Image.FromFile("EngineData\\OBJ_Fog.png"));
            listView1.LargeImageList.Images.Add("exitfade", Image.FromFile("EngineData\\OBJ_Exitfade.png"));
            listView1.LargeImageList.Images.Add("counter", Image.FromFile("EngineData\\OBJ_Counter.png"));
            listView1.LargeImageList.Images.Add("fpvcam", Image.FromFile("EngineData\\OBJ_FPVCamera.png"));
            listView1.LargeImageList.Images.Add("rigidbody", Image.FromFile("EngineData\\OBJ_Rigidbody.png"));
            listView1.LargeImageList.Images.Add("gforce", Image.FromFile("EngineData\\OBJ_GForce.png"));
            listView1.LargeImageList.Images.Add("force", Image.FromFile("EngineData\\OBJ_Force.png"));
            listView1.LargeImageList.Images.Add("group", Image.FromFile("EngineData\\OBJ_Group.png"));
            listView1.LargeImageList.Images.Add("empty", Image.FromFile("EngineData\\OBJ_Empty.png"));
            listView1.Items[0].ImageKey = "camera";
            listView1.Items[1].ImageKey = "script";
            listView1.Items[2].ImageKey = "skinmesh";
            listView1.Items[3].ImageKey = "sprite";
            listView1.Items[4].ImageKey = "textprint";
            listView1.Items[5].ImageKey = "skybox";
            listView1.Items[6].ImageKey = "soundeffect";
            listView1.Items[7].ImageKey = "soundsource";
            listView1.Items[8].ImageKey = "eol";
            listView1.Items[9].ImageKey = "eok";
            listView1.Items[10].ImageKey = "timer";
            listView1.Items[11].ImageKey = "fog";
            listView1.Items[12].ImageKey = "exitfade";
            listView1.Items[13].ImageKey = "counter";
            listView1.Items[14].ImageKey = "fpvcam";
            listView1.Items[15].ImageKey = "rigidbody";
            listView1.Items[16].ImageKey = "gforce";
            listView1.Items[17].ImageKey = "force";
            listView1.Items[18].ImageKey = "group";
            listView1.Items[19].ImageKey = "empty";
        }
        public BaseGameObject Result;
        private void listView1_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            switch(listView1.SelectedIndices[0])
            {
                case 0:
                    break;
                case 1:
                    ScriptWnd wnd = new ScriptWnd();
                    if(wnd.ShowDialog() == DialogResult.OK) Result = wnd.Result;
                    Close();
                    break;
                default: break;
            }
        }
    }
}
