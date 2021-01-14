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
using System.Diagnostics;
using System.IO;
using ScintillaNET;

namespace _3DRadSpace
{
    public partial class ScriptWnd : Form
    {
        public BaseGameObject Result;

        void InitializeScintila()
        {
            ScriptWnd_Resize(null, null);
            scintilla1.StyleResetDefault();
            scintilla1.Styles[Style.Default].Font = "Consolas";
            scintilla1.Styles[Style.Default].Size = 10;
            scintilla1.StyleClearAll();

            // Configure the CPP (C#) lexer styles
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
            scintilla1.Lexer = Lexer.Cpp;

            // Set the keywords
            scintilla1.SetKeywords(0, "abstract as base break case catch checked continue default delegate do else event explicit extern false finally fixed for foreach goto if implicit in interface internal is lock namespace new null object operator out override params private protected public readonly ref return sealed sizeof stackalloc switch this throw true try typeof unchecked unsafe using virtual while");
            scintilla1.SetKeywords(1, "bool byte char class const decimal double enum float int long sbyte short static string struct uint ulong ushort void");
        }

        public ScriptWnd()
        {
            InitializeComponent();
            InitializeScintila();
        }
        public ScriptWnd(Script a)
        {
            InitializeComponent();
            InitializeScintila();
            TXTBOXobject_name.Text = a.Name;
            TXTBOX_className.Text = a.MainClass;
        }

        private void ScriptWnd_Resize(object sender, EventArgs e)
        {
            scintilla1.Size = new Size(Size.Width-scintilla1.Location.X-25, Size.Height - 50);
        }

        private void okButton_Click(object sender, EventArgs e)
        {
            Result = new Script(TXTBOXobject_name.Text, CBOX_enabled.Checked, TXTBOX_className.Text,scintilla1.Text);
            DialogResult = DialogResult.OK;
            Close();
        }

        private void cancelButton_Click(object sender, EventArgs e)
        {
            Result = null;
            DialogResult = DialogResult.Cancel;
            Close();
        }

        private void helpButton_Click(object sender, EventArgs e)
        {
            //todo: open 3DRadSpace wiki page about the script object.
            //Process.Start("");
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Stopwatch watch = Stopwatch.StartNew();
            Script a = new Script(TXTBOXobject_name.Text, CBOX_enabled.Checked, TXTBOX_className.Text, scintilla1.Text );
            if (a.CompileWithoutAssembly(out string[] errs) == false)
            {
                File.WriteAllLines(@"ScriptErrors.log", errs);
                Process.Start(@"ScriptErrors.log");
            }
            else MessageBox.Show("Compilation sucessfully completed! \r\n Time: " + watch.ElapsedMilliseconds+" ms", "Compilation sucessful!", MessageBoxButtons.OK, MessageBoxIcon.Information);
            watch.Stop();
        }
        
		int maxLineNumberCharLength;
        void scintilla1_TextChanged(object sender, EventArgs e)
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

        private void scintilla1_CharAdded(object sender, CharAddedEventArgs e)
        {
            // Find the word start
            var currentPos = scintilla1.CurrentPosition;
            var wordStartPos = scintilla1.WordStartPosition(currentPos, true);

            // Display the autocompletion list
            var lenEntered = currentPos - wordStartPos;
            if (lenEntered > 0)
            {
                if (!scintilla1.AutoCActive)
                    scintilla1.AutoCShow(lenEntered, "abstract as base break case catch checked continue default delegate do else event explicit extern false finally fixed for foreach goto if implicit in interface internal is lock namespace new null object operator out override params private protected public readonly ref return sealed sizeof stackalloc switch this throw true try typeof unchecked unsafe using virtual while");
            }
        }
    }
}
