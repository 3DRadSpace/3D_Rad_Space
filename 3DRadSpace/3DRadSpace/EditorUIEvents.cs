using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Lib3DRadSpace_DX;
using System.Windows.Forms;

namespace _3DRadSpace
{
    public partial class Main
    {
        private void F_new_Click(object sender, EventArgs e)
        {
            DeleteAllObjects();
        }
        void DeleteAllObjects()
        {
            CurrentProject.GameObjects.Clear();
            VisualObjectsList.Items.Clear();
        }
        private void F_open_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofn = new OpenFileDialog()
            {
                Filter = "3DRadSpace Project(*.3drsp)|*.3drsp",
                Multiselect = false,
                Title = "Open a 3DRadSpace project"
            };
            if(ofn.ShowDialog() == DialogResult.OK)
            {
                
            }
            ofn.Dispose();
        }
    }
}
