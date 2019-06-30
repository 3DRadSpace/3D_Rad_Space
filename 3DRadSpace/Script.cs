using System;
using System.IO;
using System.Drawing;
using System.Windows.Forms;
using System.Diagnostics;
using _3DRadSpaceDll;
using ScintillaNET;

namespace _3DRadSpace
{
    public partial class Script : Form
    {
        public Script()
        {
            InitializeComponent();
        }
        public string LoadedScript = "";
        private void Script_Load(object sender, EventArgs e)
        {
            // Taken from https://github.com/jacobslusser/ScintillaNET/wiki/Automatic-Syntax-Highlighting .
            scintilla1.StyleResetDefault();
            scintilla1.Styles[Style.Default].Font = "Consolas";
            scintilla1.Styles[Style.Default].Size = 10;
            scintilla1.StyleClearAll();

            scintilla1.Styles[Style.Cpp.Default].ForeColor = Color.Silver;
            scintilla1.Styles[Style.Cpp.Comment].ForeColor = Color.FromArgb(0, 128, 0); // Green
            scintilla1.Styles[Style.Cpp.CommentLine].ForeColor = Color.FromArgb(0, 128, 0); // Green
            scintilla1.Styles[Style.Cpp.CommentLineDoc].ForeColor = Color.FromArgb(128, 128, 128); // Gray
            scintilla1.Styles[Style.Cpp.Number].ForeColor = Color.Olive;
            scintilla1.Styles[Style.Cpp.Word].ForeColor = Color.Blue;
            scintilla1.Styles[Style.Cpp.Word2].ForeColor = Color.Blue;
            scintilla1.Styles[Style.Cpp.String].ForeColor = Color.FromArgb(163, 21, 21); // Red
            scintilla1.Styles[Style.Cpp.Character].ForeColor = Color.FromArgb(163, 21, 21); // Red
            scintilla1.Styles[Style.Cpp.Verbatim].ForeColor = Color.FromArgb(163, 21, 21); // Red
            scintilla1.Styles[Style.Cpp.StringEol].BackColor = Color.Pink;
            scintilla1.Styles[Style.Cpp.Operator].ForeColor = Color.Purple;
            scintilla1.Styles[Style.Cpp.Preprocessor].ForeColor = Color.Maroon;

            scintilla1.SetKeywords(0, "abstract as base break case catch checked continue default delegate do else event explicit extern false finally fixed for foreach goto if implicit in interface internal is lock namespace new null object operator out override params private protected public readonly ref return sealed sizeof stackalloc switch this throw true try typeof unchecked unsafe using virtual while");
            scintilla1.SetKeywords(1, "bool byte char class const decimal double enum float int long sbyte short static string struct uint ulong ushort void");
            scintilla1_TextChanged(null, null);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrEmpty(LoadedScript))
            {
                File.WriteAllText(@"./CompiledScript/Script.3drss", scintilla1.Text);
                LoadedScript = @"./CompiledScript/Script.3drss";
            }
            else
            {
                File.WriteAllText(LoadedScript, scintilla1.Text);
            }
            MessageBox.Show(LoadedScript+ " \n "+File.ReadAllLines(LoadedScript), "Debug");
            ScriptInterpeter.Run_Start(ScriptInterpeter.Debug(LoadedScript,true));
        }

        private void button3_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFile = new OpenFileDialog()
            {
                Filter = "3DRadSpace Script (*.3drss)| *.3drss",
                InitialDirectory = @"/Scripts/",
                Multiselect = false,
                Title = "Open a saved script to use for your project..."
            };
            openFile.ShowDialog();
            LoadedScript = openFile.FileName;
        }

        private void button6_Click(object sender, EventArgs e)
        {
            Game1.LastObj = "";
            Close();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            if(!string.IsNullOrEmpty(LoadedScript))
            {
                button3_Click(null,null);
            }
            Game1.LastObj = "Script " + _3DRadSpace_EditorClass.ValidateText( textBox1.Text )+ " " + checkBox1.Checked.ToString() + " "+LoadedScript;
            DialogResult = DialogResult.OK;
            Close();
        }
        private void button2_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveFile = new SaveFileDialog()
            {
                Title = "Save a script file.",
                Filter = "3DRadSpace Script (*.3drss)| *.3drss",
                OverwritePrompt = true,
                InitialDirectory = @"/Scripts/",
            };
            DialogResult save = saveFile.ShowDialog();
            if(save == DialogResult.OK)
            {
                File.WriteAllText(saveFile.FileName, scintilla1.Text);
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            Process.Start(@".\Help Files\Script.rtf");
        }

        private void Script_FormClosed(object sender, FormClosedEventArgs e)
        {

        }
        //Taken again fron scintilla documentation
        private void scintilla1_CharAdded(object sender, CharAddedEventArgs e)
        {
            var currentPos = scintilla1.CurrentPosition;
            var wordStartPos = scintilla1.WordStartPosition(currentPos, true);

            var lenEntered = currentPos - wordStartPos;
            if (lenEntered > 0)
            {
                if (!scintilla1.AutoCActive)
                    scintilla1.AutoCShow(lenEntered, "abstract as base break case catch checked continue default delegate do else event explicit extern false finally fixed for foreach goto if implicit in interface internal is lock namespace new null object operator out override params private protected public readonly ref return sealed sizeof stackalloc switch this throw true try typeof unchecked unsafe using virtual while");
            }
        }
        //Taken again fron scintilla documentation
        private int maxLineNumberCharLength;
        private void scintilla1_TextChanged(object sender, EventArgs e)
        {
            // Did the number of characters in the line number display change?
            // i.e. nnn VS nn, or nnnn VS nn, etc...
            var maxLineNumberCharLength = scintilla1.Lines.Count.ToString().Length;
            if (maxLineNumberCharLength == this.maxLineNumberCharLength)
                return;

            // Calculate the width required to display the last line number
            // and include some padding for good measure.
            const int padding = 2;
            scintilla1.Margins[0].Width = scintilla1.TextWidth(Style.LineNumber, new string('9', maxLineNumberCharLength + 1)) + padding;
            this.maxLineNumberCharLength = maxLineNumberCharLength;
        }
    }
}
