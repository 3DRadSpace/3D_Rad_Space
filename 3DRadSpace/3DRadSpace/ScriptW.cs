using ScintillaNET;
using System;
using System.IO;
using _3DRadSpaceDll;
using System.Diagnostics;
using System.Drawing;
using System.Windows.Forms;

namespace _3DRadSpace
{
    public partial class ScriptW : Form
    {
        public ScriptW()
        {
            InitializeComponent();
            /*
             * Taken again from GitHub... 
             */
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

        public ScriptW(Script s)
        {
            InitializeComponent();
            /*
             * Taken again from GitHub... 
             */
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
            textBox1.Text = s.Name;
            textBox2.Text = s.ClassName;
            checkBox1.Checked = s.Enabled;
            FilePath = s.Path;
            scintilla1.Text = File.ReadAllText(FilePath);
        }

        public string FilePath { get; set; }
        public GameObject Result { get; set; }

        private void button2_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFile = new OpenFileDialog()
            {
                Filter = "C# Script (*.cs)|*.cs",
                Title = "Open a script",
                Multiselect = false,
                InitialDirectory = Path.GetFullPath(@"Scripts//")
            };
            DialogResult r = openFile.ShowDialog();
            if(r == DialogResult.OK)
            {
                scintilla1.Text = File.ReadAllText(openFile.FileName);
                FilePath = @"Scripts//" + Path.GetFileName(openFile.FileName);
                if(openFile.FileName != Path.GetFullPath(FilePath)) File.Copy(openFile.FileName, FilePath, true);
            }
            openFile.Dispose();
        }
        /*
         * Taken from https://github.com/jacobslusser/scintilla11NET/wiki/Displaying-Line-Numbers
          */
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

        private void button1_Click(object sender, EventArgs e)
        {
            if (FilePath == null)
            {
                File.WriteAllText(@"Scripts//Temp.cs", scintilla1.Text);
                FilePath = @"Scripts//Temp.cs";
            }
            Script script = new Script(null, true, FilePath, textBox2.Text);
            try
            {
                script.Compile(true);
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex + "", "Exception", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            if(script.CompilationStatus)
            {
                MessageBox.Show("Compilation time: " + script.CompilationTime.TotalMilliseconds + " ms", "Compilation succeded!", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveFile = new SaveFileDialog()
            {
                Filter = "C# Script (*.cs)|*.cs",
                Title = "Save a script",
                InitialDirectory = Path.GetFullPath(@"Scripts//")
            };
            DialogResult r = saveFile.ShowDialog();
            if(r == DialogResult.OK)
            {
                FilePath = @"Scripts//" + Path.GetFileName(saveFile.FileName);
                File.WriteAllText(FilePath, scintilla1.Text);
            }
            saveFile.Dispose();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            throw new NotImplementedException("Insert documentation plez");
            ///Process.Start("insert documentation path here..."); Dead code here we go :DDD
        }

        private void button6_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.Cancel;
            Result = null;
            Close();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            if(FilePath == null)
            {
                SaveFileDialog saveFile = new SaveFileDialog()
                {
                    Filter = "C# Script (*.cs)|*.cs",
                    Title = "Save a script",
                    InitialDirectory = Path.GetFullPath(@"Scripts//")
                };
                //Let's force the poor user to save his script :D
                while(saveFile.ShowDialog() != DialogResult.OK) { }
                FilePath = @"Scripts//"+Path.GetFileName(saveFile.FileName);
                File.WriteAllText(FilePath, scintilla1.Text);
                saveFile.Dispose();
            }
            DialogResult = DialogResult.OK;
            Result = new Script(Editor.ValidateTextInput(textBox1.Text), checkBox1.Enabled, FilePath, Editor.ValidateTextInput(textBox2.Text));
            Close();
        }

        private void ScriptW_Load(object sender, EventArgs e)
        {
            scintilla1_TextChanged(sender, e);
        }

        private void ScriptW_SizeChanged(object sender, EventArgs e)
        {
            scintilla1.ClientSize = new Size(ClientSize.Width - 175 - 12, ClientSize.Height - 24);
        }
    }
}
