using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Diagnostics;
using System.Threading;

namespace _3DRadSpace
{
    public partial class PlayTestingLauncher : Form
    {
        public PlayTestingLauncher()
        {
            InitializeComponent();
        }
        public static string ProjectPath = "";
        private void PlayTestingLauncher_Load(object sender, EventArgs e)
        {
            progressBar1.Maximum = 100;
            progressBar1.Minimum = 0;
            progressBar1.Value = 0;
            label2.Text = "Status: Writing project.";
            string[] ProjectData = { ProjectPath, @"False", null };
            File.WriteAllLines(@"settings.data", ProjectData);
            progressBar1.Value = 50;
            label2.Text = "Status: Starting project.";
            Process.Start(@"3DRadSpacePlayer.exe");
            progressBar1.Value = 100;
            label2.Text = "Status: Done";
            Thread.Sleep(500);
            this.Close();
        }
    }
}
