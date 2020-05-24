using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using _3DRadSpaceDll;

namespace _3DRadSpace
{
    public partial class GameSettingsW : Form
    {
        public GameSettingsW()
        {
            InitializeComponent();
        }
        public GameSettings Result;
        private void button1_Click(object sender, EventArgs e)
        {
            Result = new GameSettings()
            {
                Fullscreen = checkBox1.Checked,
                GameScreen = new Microsoft.Xna.Framework.Point()
                {
                    X = Convert.ToInt32((Editor.ValidateNumberTextInput(textBox1.Text)),
                    Y = Convert.ToInt32((Editor.ValidateNumberTextInput(textBox2.Text))
                },
                MaximumFramerate = Convert.ToInt32((Editor.ValidateNumberTextInput(textBox3.Text))
            };
            DialogResult = DialogResult.OK;
            Close();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.Cancel;
            Result = null;
            Close();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            //open docs...
        }
    }
}
