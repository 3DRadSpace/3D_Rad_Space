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
using _3DRadSpaceDll.ActionScript;

namespace _3DRadSpace
{
    public partial class EventOpcodeEditor : Form
    {
        public EventOpcodeEditor()
        {
            Result = new OpCodeCall[50];
            InitializeComponent();
        }

        public OpCodeCall[] Result;

        private void EventOpcodeEditor_Load(object sender, EventArgs e)
        {

        }
    }
}
