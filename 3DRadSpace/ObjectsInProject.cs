using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _3DRadSpace
{
    public partial class ObjectsInProject : Form
    {
        public ObjectsInProject()
        {
            InitializeComponent();
        }

        private void ObjectsInProject_Load(object sender, EventArgs e)
        {
            this.Location = new Point(25, 25);
        }

        private void list_objects_MouseDoubleClick(object sender, MouseEventArgs e)
        {

        }
    }
}
